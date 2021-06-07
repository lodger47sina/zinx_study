#include <iostream>
#include <zinx.h>
#include <ZinxTCP.h>
#include "SdInOutChannel.h"
#include "EchoRole.h"

int main()
{
    ZinxKernel::ZinxKernelInit();

    ZinxKernel::Zinx_Add_Channel(*(new StdInChannel()));
    ZinxKernel::Zinx_Add_Channel(*(new StdOutChannel()));
    ZinxKernel::Zinx_Add_Channel(*(new ZinxTCPListen(51111,new MyFact())));

    ZinxKernel::Zinx_Add_Role(*(new EchoRole()));
    ZinxKernel::Zinx_Add_Role(*(new DatePreRole()));
    ZinxKernel::Zinx_Add_Role(*(new OutputCtrl()));

    ZinxKernel::Zinx_Run();

    ZinxKernel::ZinxKernelFini();
    return 0;
}

