#pragma once
#include <zinx.h>
#include <iostream>

using namespace std;

class CmdMsg
    :public UserData
{
public:
    string szUserData; // 要回显得字符串
    // 开启输出标志
    bool isOpen = true;
    // 该消息是命令
    bool isCmd = false;
    // 要加前缀
    bool needDatePre = false;
    CmdMsg();
    virtual ~CmdMsg();
};

