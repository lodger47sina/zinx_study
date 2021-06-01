#pragma once
#include <zinx.h>

class EchoRole
    :public Irole
{
public:
    EchoRole();
    virtual ~EchoRole();
	/*初始化函数，开发者可以重写该方法实现对象相关的初始化，该函数会在role对象添加到zinxkernel时调用*/
	virtual bool Init();
	/*处理信息函数，重写该方法可以对业务数据进行处理，若还需要后续处理流程，则应返回相关数据信息（堆对象）*/
	virtual UserData *ProcMsg(UserData &_poUserData);
	/*去初始化函数，类似初始化函数，该函数会在role对象摘除出zinxkernel时调用*/
	virtual void Fini();
private:

};

class OutputCtrl :public Irole
{
public:
    OutputCtrl();
    virtual ~OutputCtrl();
	/*初始化函数，开发者可以重写该方法实现对象相关的初始化，该函数会在role对象添加到zinxkernel时调用*/
	virtual bool Init();
	/*处理信息函数，重写该方法可以对业务数据进行处理，若还需要后续处理流程，则应返回相关数据信息（堆对象）*/
	virtual UserData *ProcMsg(UserData &_poUserData);
	/*去初始化函数，类似初始化函数，该函数会在role对象摘除出zinxkernel时调用*/
	virtual void Fini();
    Ichannel *pOut = NULL;
};

class DatePreRole :public Irole
{
public:
    DatePreRole();
    virtual ~DatePreRole();
	/*初始化函数，开发者可以重写该方法实现对象相关的初始化，该函数会在role对象添加到zinxkernel时调用*/
	virtual bool Init();
	/*处理信息函数，重写该方法可以对业务数据进行处理，若还需要后续处理流程，则应返回相关数据信息（堆对象）*/
	virtual UserData *ProcMsg(UserData &_poUserData);
	/*去初始化函数，类似初始化函数，该函数会在role对象摘除出zinxkernel时调用*/
	virtual void Fini();
    bool needAdd = false;
};
