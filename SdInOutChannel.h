#pragma once
#include <zinx.h>
#include <ZinxTCP.h>
class StdInChannel :
	public Ichannel
{
public:
	StdInChannel(){}
	virtual ~StdInChannel(){}

	// ͨ�� Ichannel �̳�
	virtual bool Init() override;
	virtual bool ReadFd(std::string & _input) override;
	virtual bool WriteFd(std::string & _output) override;
	virtual void Fini() override;
	virtual int GetFd() override;
	virtual std::string GetChannelInfo() override;
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override;
};

class StdOutChannel :public Ichannel
{
public:
	// ͨ�� Ichannel �̳�
	virtual bool Init() override;
	virtual bool ReadFd(std::string & _input) override;
	virtual bool WriteFd(std::string & _output) override;
	virtual void Fini() override;
	virtual int GetFd() override;
	virtual std::string GetChannelInfo() override;
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override;
};
class MyTcpDate :public ZinxTcpData
{
public:
    MyTcpDate(int _fd):ZinxTcpData(_fd){}
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput);
};
class MyFact :public IZinxTcpConnFact{
public:
	virtual ZinxTcpData *CreateTcpDataChannel(int _fd);

};
