#pragma once
// TCP_Echo_Server.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
#pragma comment(lib,"Ws2_32.lib") //winsock 2.2 ���̺귯��
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501

#include <WinSock2.h> //Winsock 2 ���� Header
#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <vector>
#include <iostream>
#include "..\header\baseSocket.h"

using namespace std;


class ServerSocket
{
private:
	enum eMode{eTCP,eUDP};
	eMode m_eMode;

	SockInfo m_oSockInfo;
	//SOCKADDR_IN m_serverAddress; // �ּҸ� ��� ����ü.
	//SOCKET		m_serverSocket;	//������
	
	//SOCKADDR_IN m_clinetAddress; //UDP ��� �۾��� ���
	
	
	
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
	SockInfo&  Accept();

	void ReleaseSocket();
};

