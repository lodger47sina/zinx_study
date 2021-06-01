#pragma once
#include <iostream>
#include <zinx.h>
#include <ZinxTCP.h>
using namespace std;

class StdInChannel :public Ichannel
{
public:
    StdInChannel();
    virtual ~StdInChannel();

    virtual bool Init();
    virtual bool ReadFd(string &_input);
    virtual bool WriteFd(string &_output);
    virtual void Fini();
    virtual int GetFd();
    virtual string GetChannelInfo();
    virtual AZinxHandler *GetInputNextStage(BytesMsg &_oInput);
};

class StdOutChannel :public Ichannel{
public:
    StdOutChannel();
    virtual ~StdOutChannel();

    virtual bool Init();
    virtual bool ReadFd(string &_input);
    virtual bool WriteFd(string &_output);
    virtual void Fini();
    virtual int GetFd();
    virtual string GetChannelInfo();
    virtual AZinxHandler *GetInputNextStage(BytesMsg &_oInput);
};

class MyTcpData :public ZinxTcpData{
public:
    MyTcpData(int _fd):ZinxTcpData(_fd){}
    virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput);
};

class MyFact :public IZinxTcpConnFact{
public:
    virtual ZinxTcpData *CreateTcpDataChannel(int _fd);
};
