#pragma once
#pragma comment(lib,"Ws2_32.lib")
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501

#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#include <string>
#include "baseSocket.h"
using namespace std;
	
class ClientSocket : public SockBase
{
public:
	enum eMode{eTCP,eUDP};
private:

	SockInfo m_oSockInfo;
	HANDLE m_hThread;
	int		m_nPort;
public:
	ClientSocket(int port = 9000 ,string ip = "127.0.0.1" ,ClientSocket::eMode mode = eTCP);
	virtual ~ClientSocket(void);
	virtual int Send(char* buffer,int len);
	//Why virtual ???
	virtual int ReceivtThreadRun();
	


	void SetPort(int port);
	bool InitWinsock();
	bool InitSock();
	bool Connect();
	int  Receive(char* pBuffer,int lel);
	
	bool CreateThread();
	void Release();
private:
	unsigned int  static CALLBACK ThreadRun(void* pData);
};

