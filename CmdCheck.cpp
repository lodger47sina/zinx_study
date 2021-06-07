#include "CmdCheck.h"
#include "CmdMsg.h"
#include "EchoRole.h"
using namespace std;

CmdCheck *CmdCheck::poSingle = new CmdCheck();

CmdCheck::CmdCheck()
{
}


CmdCheck::~CmdCheck()
{
}

UserData * CmdCheck::raw2request(std::string _szInput)
{
    if("exit" == _szInput)
    {
        ZinxKernel::Zinx_Exit();
        return NULL;
    }
	/*赋值原始数据字符串到用户数据中字符串字段*/
	auto pret = new CmdMsg();
	pret->szUserData = _szInput;
	return pret;
}

std::string * CmdCheck::response2raw(UserData & _oUserData)
{
	GET_REF2DATA(CmdMsg, output, _oUserData);
	return new string(output.szUserData);
}

Irole * CmdCheck::GetMsgProcessor(UserDataMsg & _oUserDataMsg)
{
    auto rolelist = ZinxKernel::Zinx_GetAllRole();
	return rolelist.front();
}

Ichannel * CmdCheck::GetMsgSender(BytesMsg & _oBytes)
{
	return ZinxKernel::Zinx_GetChannel_ByInfo("stdout");
}
