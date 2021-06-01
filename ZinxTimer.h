#pragma once
#include <iostream>
#include <zinx.h>
#include <vector>
#include <list>

using namespace std;

class ZinxTimer
    :public Ichannel
{
public:
    ZinxTimer() {}
    virtual ~ZinxTimer() {}
	/*通道初始化函数，一般地，开发者应该重写这个函数实现打开文件和一定的参数配置
	该函数会在通道对象添加到zinxkernel时被调用*/
	virtual bool Init();

	/*读取数据， 开发者应该根据目标文件不同，重写这个函数，以实现将fd中的数据读取到参数_string中
	该函数会在数据源所对应的文件有数据到达时被调用*/
	virtual bool ReadFd(std::string &_input);

	/*写出数据， 开发者应该将数据写出的操作通过重写该函数实现
	该函数会在调用zinxkernel::sendout函数后被调用（通常不是直接调用而是通过多路复用的反压机制调用）*/
	virtual bool WriteFd(std::string &_output);

	/*通道去初始化，开发者应该在该函数回收相关资源
	该函数会在通道对象从zinxkernel中摘除时调用*/
	virtual void Fini();

	/*获取文件描述符函数， 开发者应该在该函数返回当前关心的文件，
	一般地，开发者应该在派生类中定义属性用来记录数据来记录当前IO所用的文件，在此函数中只是返回该属性*/
	virtual int GetFd();
    /*获取通道信息函数，开发者可以在该函数中返回跟通道相关的一些特征字符串，方便后续查找和过滤*/
	virtual std::string GetChannelInfo();
	/*获取下一个处理环节，开发者应该重写该函数，指定下一个处理环节
	一般地，开发者应该在该函数返回一个协议对象，用来处理读取到的字节流*/
	virtual AZinxHandler *GetInputNextStage(BytesMsg &_oInput);
public:
    int m_TimerFd = -1;
};

class TimerOutProc
{
public:
TimerOutProc(){};
virtual ~TimerOutProc(){};
   virtual void Proc() =0;
   virtual int GetTimeSec() =0;
   // 所剩圈数
   int iCount = -1;
};

class TimerOutMsg :public AZinxHandler{
    //std::list<TimerOutProc*> m_task_list;
    vector<list<TimerOutProc*>> m_timer_wheel;
    int cur_index = 0;
    static TimerOutMsg single;
    TimerOutMsg();
public:

    ~TimerOutMsg(){}
    /*信息处理函数，开发者重写该函数实现信息的处理，当有需要一个环节继续处理时，应该创建新的信息对象（堆对象）并返回指针*/
	virtual IZinxMsg *InternelHandle(IZinxMsg &_oInput);
	/*获取下一个处理环节函数，开发者重写该函数，可以指定当前处理环节结束后下一个环节是什么，通过参数信息对象，可以针对不同情况进行分别处理*/
	virtual AZinxHandler *GetNextHandler(IZinxMsg &_oNextMsg);
    void AddTask(TimerOutProc* _ptask);
    void DelTask(TimerOutProc *_ptask);
    static TimerOutMsg &GetInstance(){
        return single;
    }
};
