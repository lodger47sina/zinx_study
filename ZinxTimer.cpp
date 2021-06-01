#include "ZinxTimer.h"
#include <sys/timerfd.h>

TimerOutMsg TimerOutMsg::single;


bool ZinxTimer::Init(){
    // 创建文件描述符
    bool bRet = false;        
    int iFd = timerfd_create(CLOCK_MONOTONIC,0);
    if(0 <= iFd)
    {
        struct itimerspec period = {
            {1,0},{1,0}
        };
        if(0 == timerfd_settime(iFd,0,&period,NULL))
        {
            bRet = true;
            m_TimerFd = iFd;
        }
    }
    return bRet;
}

/*读取数据， 开发者应该根据目标文件不同，重写这个函数，以实现将fd中的数据读取到参数_string中
  该函数会在数据源所对应的文件有数据到达时被调用*/
bool ZinxTimer::ReadFd(std::string &_input){
    bool bRet = false;
    char buf[8] = {0};
    if(sizeof(buf) == read(m_TimerFd,buf,sizeof(buf))) 
    {
        bRet = true;
        _input.assign(buf,sizeof(buf));
    }
    return bRet;
}

/*写出数据， 开发者应该将数据写出的操作通过重写该函数实现
  该函数会在调用zinxkernel::sendout函数后被调用（通常不是直接调用而是通过多路复用的反压机制调用）*/
bool ZinxTimer::WriteFd(std::string &_output){
    return false;
}

/*通道去初始化，开发者应该在该函数回收相关资源
  该函数会在通道对象从zinxkernel中摘除时调用*/
void ZinxTimer::Fini(){
    close(m_TimerFd);
    m_TimerFd = -1;
}

/*获取文件描述符函数， 开发者应该在该函数返回当前关心的文件，
  一般地，开发者应该在派生类中定义属性用来记录数据来记录当前IO所用的文件，在此函数中只是返回该属性*/
int ZinxTimer::GetFd(){
    return m_TimerFd;
}
/*获取通道信息函数，开发者可以在该函数中返回跟通道相关的一些特征字符串，方便后续查找和过滤*/
std::string ZinxTimer::GetChannelInfo(){
    return "TimerFd";
}

class Output_hello :public AZinxHandler{
public:
    Output_hello(){}
    ~Output_hello(){}
    /*信息处理函数，开发者重写该函数实现信息的处理，当有需要一个环节继续处理时，应该创建新的信息对象（堆对象）并返回指针*/
    virtual IZinxMsg *InternelHandle(IZinxMsg &_oInput){
        auto pchannel = ZinxKernel::Zinx_GetChannel_ByInfo("stdout");
        string output = "hello world";
        ZinxKernel::Zinx_SendOut(output,*pchannel);
        return NULL;

    }

    /*获取下一个处理环节函数，开发者重写该函数，可以指定当前处理环节结束后下一个环节是什么，通过参数信息对象，可以针对不同情况进行分别处理*/
    virtual AZinxHandler *GetNextHandler(IZinxMsg &_oNextMsg){
        return NULL;
    }

}*pout_hello = new Output_hello();

AZinxHandler *ZinxTimer::GetInputNextStage(BytesMsg &_oInput){
    return &TimerOutMsg::GetInstance();
}

IZinxMsg *TimerOutMsg::InternelHandle(IZinxMsg &_oInput){
    /*
    for (auto task:m_task_list)
    {
        task->iCount--;
        // 若计数为0则调用超时处理函数
        if(task->iCount <= 0)
        {
            task->Proc();
            task->iCount = task->GetTimeSec();
        }
    }
    */
    // 移动刻度
    cur_index++;
    cur_index %=10;
    // 判断当前刻度所有节点，指向处理函数或者圈数-1
    for(auto itr = m_timer_wheel[cur_index].begin();itr!= m_timer_wheel[cur_index].end();itr++)
    {
        if((*itr)->iCount <=0)
        {
            (*itr)->Proc();
            auto tmp=(*itr);
            itr=m_timer_wheel[cur_index].erase(itr);
            AddTask(tmp);
        }else{
            (*itr)->iCount--;
            ++itr;
        }
    }
    return NULL;
}

AZinxHandler *TimerOutMsg::GetNextHandler(IZinxMsg &_oNextMsg){
    return NULL;
}

TimerOutMsg::TimerOutMsg(){
    // 创建10个齿
    for (int i=0;i<10;++i)
    {
        list<TimerOutProc*> tmp;
        m_timer_wheel.push_back(tmp);
    }
}
void TimerOutMsg::AddTask(TimerOutProc* _ptask)
{
    /*
    m_task_list.push_back(_ptask);
    _ptask->iCount = _ptask->GetTimeSec();
    */
   /* 
    * 计算当前任务需要放到那个齿上
    * 把任务存到该齿上
    * 计算所需圈数
    */
    int index = (_ptask->GetTimeSec()+cur_index)%10;
    m_timer_wheel[index].push_back(_ptask);
    _ptask->iCount = _ptask->GetTimeSec()/10;
}

void TimerOutMsg::DelTask(TimerOutProc *_ptask)
{
    // m_task_list.remove(_ptask);
    // 遍历时间所有齿，删掉任务    
   for (auto chi:m_timer_wheel)
   {
    for(auto task:chi)   
    {
        if(task == _ptask)
        {
            chi.remove(_ptask);
            return;
        }
    }
   }
}

