#pragma once
// TCP_Echo_Server.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
#pragma comment(lib,"Ws2_32.lib")
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501

#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#include <string>
using namespace std;

class ClintSocket
{
private:
	enum eMode{eTCP,eUDP};
	eMode m_eMode;
	SOCKADDR_IN m_clientAddress; //������ ������ �ּ� ������ ������ ����ü.
	SOCKET		m_clientSocket;	//Ŭ���̾�Ʈ ����
	WSADATA		m_wsadata;
	int			m_len;
	
	
	int			m_nPort;
	string		m_strRHostIP; //���� ȣ��Ʈ��  ������.
public:
	ClintSocket(int port = 9000 ,string ip = "127.0.0.1" ,ClintSocket::eMode mode = eTCP);
	virtual ~ClintSocket(void);

	void SetPort(int port);
	bool InitWinsock();
	bool InitSock();
};

