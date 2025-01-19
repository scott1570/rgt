#include "pch.h"
#include "ServiceProxy.h"
#include "ServiceMaster.h"
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996) 



ServiceProxy::ServiceProxy(ServiceMaster *pMaster)
{
	WSADATA wData;
	WSAStartup(MAKEWORD(2, 0), &wData);
	mpMaster = pMaster;
	mbExit = false;
}
ServiceProxy::~ServiceProxy()
{
	mbExit = true;
	WSACleanup();
}

int ServiceProxy::Init(CString ip, WORD wPort)
{
	msocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (msocket == INVALID_SOCKET) {
		return -1;
	}
	
	SOCKADDR_IN sockaddr;
	sockaddr.sin_port = htons(5678);
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	
	if (connect(msocket, (struct sockaddr*)&sockaddr, sizeof(sockaddr) == SOCKET_ERROR))
	{
		return -2;
	}

	DWORD dwid = 0;
	::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)receiveThread, this,0 , &dwid);

}
LPVOID ServiceProxy::receiveThread(LPVOID param)
{
	ServiceProxy* pProxy = (ServiceProxy*)param;
	while (true) {
		if (pProxy->mbExit)
			break;

		OutputDebugString(_T("looping\n"));

		char buffer[256];
		int size = sizeof(buffer);
		int res = pProxy->read_exact(pProxy->msocket, buffer, size);
	}

	return NULL;
}

int ServiceProxy::read_exact(SOCKET s, char* pbuff, int size)
{
	int iResult;
	struct timeval tv;
	fd_set rfds;
	
	FD_ZERO(&rfds);
	FD_SET(s, &rfds);

	tv.tv_sec = (long)2;
	tv.tv_usec = 0;

	iResult = select(s + 1, &rfds, (fd_set*)0, (fd_set*)0, &tv);
	if (iResult > 0)
	{
		return recv(s, pbuff, size, 0);
	}
	
	
	return 0;
}