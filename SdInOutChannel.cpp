#include "SdInOutChannel.h"
#include <iostream>
#include "CmdCheck.h"

using namespace std;

bool StdInChannel::Init()
{
	return true;
}

bool StdInChannel::ReadFd(std::string & _input)
{
	cin >> _input;
	return true;
}

bool StdInChannel::WriteFd(std::string & _output)
{
	return false;
}

void StdInChannel::Fini()
{
}

int StdInChannel::GetFd()
{
	return 0;
}

std::string StdInChannel::GetChannelInfo()
{
	return "stdin";
}

AZinxHandler * StdInChannel::GetInputNextStage(BytesMsg & _oInput)
{
	return CmdCheck::GetInstance();
}

bool StdOutChannel::Init()
{
	return true;
}

bool StdOutChannel::ReadFd(std::string & _input)
{
	return false;
}

bool StdOutChannel::WriteFd(std::string & _output)
{
	cout << _output << endl;
	return true;
}

void StdOutChannel::Fini()
{
}

int StdOutChannel::GetFd()
{
	return 1;
}

std::string StdOutChannel::GetChannelInfo()
{
	return "stdout";
}

AZinxHandler * StdOutChannel::GetInputNextStage(BytesMsg & _oInput)
{
	return nullptr;
}
//----------------------------------
AZinxHandler * MyTcpDate::GetInputNextStage(BytesMsg & _oInput)
{
return CmdCheck::GetInstance();
}


ZinxTcpData *MyFact::CreateTcpDataChannel(int _fd)
{
return new MyTcpDate(_fd);
}

