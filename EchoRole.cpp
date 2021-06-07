#include "EchoRole.h"
#include "CmdMsg.h"
#include "CmdCheck.h"

using namespace std;

EchoRole::EchoRole()
{
}


EchoRole::~EchoRole()
{
}

bool EchoRole::Init()
{
	return true;
}

UserData * EchoRole::ProcMsg(UserData & _poUserData)
{
	/*д��ȥ*/
	GET_REF2DATA(CmdMsg, input, _poUserData);
	CmdMsg *pout = new CmdMsg(input);
	ZinxKernel::Zinx_SendOut(*pout, *(CmdCheck::GetInstance()));
	return nullptr;
}

void EchoRole::Fini()
{
}
