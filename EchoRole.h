#pragma once
#include <zinx.h>
class EchoRole :
	public Irole
{
public:
	EchoRole(){}
	virtual ~EchoRole(){}

	// ͨ�� Irole �̳�
	virtual bool Init() override;
	virtual UserData * ProcMsg(UserData & _poUserData) override;
	virtual void Fini() override;
};

class OutputCtrl :public Irole
{
public:
    OutputCtrl(){}
    virtual ~OutputCtrl(){}

	// ͨ�� Irole �̳�
	virtual bool Init() override;
	virtual UserData * ProcMsg(UserData & _poUserData) override;
	virtual void Fini() override;
    Ichannel *pOut = NULL;
};
class DatePreRole :public Irole
{
public:
    DatePreRole(){}
    ~DatePreRole(){}
	// ͨ�� Irole �̳�
	virtual bool Init();
	virtual UserData * ProcMsg(UserData & _poUserData) override;
	virtual void Fini();

    bool needAdd = false;
};
