#include <iostream>
#include <zinx.h>
#include "StdinOutChannel.h"
#include "Echo.h"
#include <ZinxTCP.h>
#include "ZinxTimer.h"

class TimerHello :public TimerOutProc{
public:
    TimerHello(){}
    ~TimerHello(){}
    virtual void Proc(){
        auto pchannel = ZinxKernel::Zinx_GetChannel_ByInfo("stdout");
        std::string output = "hello world";
        ZinxKernel::Zinx_SendOut(output,*pchannel);
    }
    virtual int GetTimeSec(){
        return 3;
    }
};

class TimerBye :public TimerOutProc{
public:
    TimerBye(){}
    ~TimerBye(){}
    virtual void Proc(){
        auto pchannel = ZinxKernel::Zinx_GetChannel_ByInfo("stdout");
        std::string output = "bye";
        ZinxKernel::Zinx_SendOut(output,*pchannel);
    }
    virtual int GetTimeSec(){
        return 5;
    }

};

int main()
{
    ZinxKernel::ZinxKernelInit();

    TimerOutMsg::GetInstance().AddTask(new TimerHello());
    TimerOutMsg::GetInstance().AddTask(new TimerBye());

    ZinxKernel::Zinx_Add_Channel(*(new StdInChannel()));
    ZinxKernel::Zinx_Add_Channel(*(new StdOutChannel()));
    ZinxKernel::Zinx_Add_Channel(*(new ZinxTCPListen(51111,new MyFact())));
    ZinxKernel::Zinx_Add_Channel(*(new ZinxTimer()));

    ZinxKernel::Zinx_Add_Role(*(new EchoRole()));
    ZinxKernel::Zinx_Add_Role(*(new DatePreRole()));
    ZinxKernel::Zinx_Add_Role(*(new OutputCtrl()));

    ZinxKernel::Zinx_Run();

    ZinxKernel::ZinxKernelFini();
    return 0;
}

