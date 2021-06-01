#pragma once
#include <zinx.h>
#include <iostream>

using namespace std;

class CmdCheck :public  Iprotocol
{
    CmdCheck();
    virtual ~CmdCheck();
public:
	/*原始数据和业务数据相互函数，开发者重写该函数，实现协议*/
	virtual UserData* raw2request(string _szInput) ;
	/*原始数据和业务数据相互函数，开发者重写该函数，实现协议*/
	virtual string* response2raw(UserData &_oUserData) ;
    /*获取处理角色对象函数，开发者应该重写该函数，用来指定当前产生的用户数据消息应该传递给哪个角色处理*/
	virtual Irole* GetMsgProcessor(UserDataMsg &_oUserDataMsg) ;
	/*获取发送通道函数，开发者应该重写该函数，用来指定当前字节流应该由哪个通道对象发出*/
	virtual Ichannel* GetMsgSender(BytesMsg &_oBytes) ;

    static CmdCheck* GetInstance(){
        return poSingle;
    }
public:
    static CmdCheck* poSingle;
    string szOutChannel;
};

