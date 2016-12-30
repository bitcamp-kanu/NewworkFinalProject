#pragma once
// TCP_Echo_Server.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
#pragma comment(lib,"Ws2_32.lib") //winsock 2.2 라이브러리
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501

#include <WinSock2.h> //Winsock 2 버전 Header
//#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <vector>
#include <iostream>
#include "..\Public\baseSocket.h"
#include "ReceiveSocket.h"


using namespace std;

class ServerSocket
{
private:
	enum eMode{eTCP,eUDP};
	eMode m_eMode;
	SockInfo m_oSockInfo;
	
	WSADATA		m_wsadata;
	int			m_iPort;

public:
	ServerSocket(int port = 9000 , ServerSocket::eMode mode = eTCP);
	virtual ~ServerSocket(void);

	void SetPort(int port);
	bool InitWinsock();
	bool InitSock();
	bool Bind();
	int  Listen(int cnt = 5);
	ReceiveSocket*  Accept();
	void ReleaseSocket();
	string GetInof();
};