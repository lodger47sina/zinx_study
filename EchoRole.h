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
    ~OutputCtrl(){}
	// ͨ�� Irole �̳�
	virtual bool Init() override;
	virtual UserData * ProcMsg(UserData & _poUserData) override;
	virtual void Fini() override;
    Ichannel* pOut=NULL;
};
class DatePreRole :public Irole
{
public:
    DatePreRole(){}
    virtual ~DatePreRole(){}
	/*��ʼ�������������߿�����д�÷���ʵ�ֶ�����صĳ�ʼ�����ú�������role������ӵ�zinxkernelʱ����*/
	virtual bool Init();
	/*������Ϣ��������д�÷������Զ�ҵ�����ݽ��д���������Ҫ�����������̣���Ӧ�������������Ϣ���Ѷ���*/
	virtual UserData *ProcMsg(UserData &_poUserData);
	/*ȥ��ʼ�����������Ƴ�ʼ���������ú�������role����ժ����zinxkernelʱ����*/
	virtual void Fini();
    bool needAdd = false;
};
