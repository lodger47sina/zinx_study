#pragma once
#include <zinx.h>
#include <string>

class CmdMsg :
	public UserData
{
public:
    // ���������־
    bool isOpen = true;
    // ����Ϣ������
    bool isCmd = false;
    // Ҫ��ǰ׺
    bool needDatePre = false;
	/*��Ա������ʾҪ���Ե��ַ���*/
	std::string szUserData;
	CmdMsg();
	virtual ~CmdMsg();
};

