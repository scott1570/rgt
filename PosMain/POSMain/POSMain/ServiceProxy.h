#pragma once

#include <winsock2.h>

class ServiceMaster;

class ServiceProxy
{
public:
	ServiceProxy(ServiceMaster* pMaster);
	ServiceProxy();
	~ServiceProxy();
	ServiceMaster* mpMaster;

	SOCKET msocket;
	bool mbExit;

	int Init(CString ip, WORD wPort);
	int read_exact(SOCKET s, char* pbuff, int size);

	static LPVOID receiveThread(LPVOID param);
};

