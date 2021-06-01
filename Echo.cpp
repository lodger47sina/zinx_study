#include "Echo.h"
#include "CmdMsg.h"
#include "CmdCheck.h"

using namespace std;


EchoRole::EchoRole()
{

}
EchoRole::~EchoRole(){

}
bool EchoRole::Init(){
    return true;
}
UserData *EchoRole::ProcMsg(UserData &_poUserData){
    // 写出去
    GET_REF2DATA(CmdMsg,input,_poUserData);
    CmdMsg *pout = new CmdMsg(input);
    ZinxKernel::Zinx_SendOut(*pout,*(CmdCheck::GetInstance()));
    return NULL;
}
void EchoRole::Fini(){

}
//------------------------------------------------------

OutputCtrl::OutputCtrl()
{

}
OutputCtrl::~OutputCtrl()
{

}

bool OutputCtrl::Init()
{
    Irole *pRetRole = NULL;
    for (auto pRole:ZinxKernel::Zinx_GetAllRole()){
        auto pDate = dynamic_cast<DatePreRole*>(pRole);
        if(NULL!=pDate)
        {
            pRetRole = pDate;
            break;
        }
    }
    if(NULL != pRetRole)
    {
        SetNextProcessor(*pRetRole);
    }
    return true;
}
UserData* OutputCtrl::ProcMsg(UserData &_poUserData){
    // 读取用户设置的开关标志
    GET_REF2DATA(CmdMsg,input,_poUserData);
    if(true == input.isOpen)
    {
        // 开启输出
        if(NULL != pOut)
        {
            ZinxKernel::Zinx_Add_Channel(*(pOut));
            pOut = NULL;
        }
    }else{
        // 关闭输出
        auto pchannel = ZinxKernel::Zinx_GetChannel_ByInfo("stdout");
        ZinxKernel::Zinx_Del_Channel(*(pchannel));
        pOut = pchannel;
    }
    return new CmdMsg(input);
}

void OutputCtrl::Fini()
{

}
// ----------------------------------------------------------------------
DatePreRole::DatePreRole()
{

}

DatePreRole::~DatePreRole()
{

}
bool DatePreRole::Init()
{
    Irole *pRetRole = NULL;
    for (auto pRole:ZinxKernel::Zinx_GetAllRole()){
        auto pEcho = dynamic_cast<EchoRole*>(pRole);
        if(NULL!=pEcho)
        {
            pRetRole = pEcho;
            break;
        }
    }
    if(NULL != pRetRole)
    {
        SetNextProcessor(*pRetRole);
    }
    return true;
}
void DatePreRole::Fini()
{
}
UserData* DatePreRole::ProcMsg(UserData &_poUserData)
{
    CmdMsg* pret = NULL;
    GET_REF2DATA(CmdMsg,input,_poUserData);
    if(input.isCmd)
    {
        needAdd = input.needDatePre;
    }else{
        if(true == needAdd)
        {
            time_t tmp;
            time(&tmp);
            string szNew = string(ctime(&tmp)).append(input.szUserData);
            pret = new CmdMsg(input);
            pret->szUserData = szNew;
        }else{
            pret = new CmdMsg(input);
        }
    }
    return pret;
}



