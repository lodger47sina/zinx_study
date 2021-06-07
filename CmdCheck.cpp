#include "CmdCheck.h"
#include "CmdMsg.h"
#include "EchoRole.h"
using namespace std;

CmdCheck *CmdCheck::poSingle = new CmdCheck();

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
    if("open" == _szInput)
    {
        pret->isCmd = true;
        pret->isOpen = true;
    }else if("close" == _szInput)
    {
        pret->isCmd = true;
        pret->isOpen = false;
    }else if("date" == _szInput)
    {
        pret->needDatePre = true;
        pret->isCmd = true;
    }else if("cleardate" == _szInput)
    {
        pret->needDatePre = false;
        pret->isCmd = true;
    }
	return pret;
}

std::string * CmdCheck::response2raw(UserData & _oUserData)
{
	GET_REF2DATA(CmdMsg, output, _oUserData);
	return new string(output.szUserData);
}

Irole * CmdCheck::GetMsgProcessor(UserDataMsg & _oUserDataMsg)
{
    szOutChannel = _oUserDataMsg.szInfo;
    if("stdin" == szOutChannel)
    {
        szOutChannel = "stdout";
    }
    auto rolelist = ZinxKernel::Zinx_GetAllRole();
    auto pCmdMsg = dynamic_cast<CmdMsg*>(_oUserDataMsg.poUserData);

    bool isCmd = pCmdMsg->isCmd;
    Irole* pRetRole = NULL;
    for (auto prole:rolelist)
    {
     if(isCmd)   
     {
        auto pOutCtrl = dynamic_cast<OutputCtrl*>(prole);
        if(NULL != pOutCtrl)
        {
            pRetRole = pOutCtrl;
            break;
        }
     }else{
        auto pDate =dynamic_cast<DatePreRole*>(prole);
        if(NULL != pDate)
        {
            pRetRole = pDate;
            break;
        }
     }
    }
	return pRetRole;
}

Ichannel * CmdCheck::GetMsgSender(BytesMsg & _oBytes)
{
	return ZinxKernel::Zinx_GetChannel_ByInfo(szOutChannel);
}
