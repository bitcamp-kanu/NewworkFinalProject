#pragma once
// TCP_Echo_Server.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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
	SOCKADDR_IN m_clientAddress; //접속할 서버의 주소 정보를 저장할 구조체.
	SOCKET		m_clientSocket;	//클라이언트 소켓
	WSADATA		m_wsadata;
	int			m_len;
	
	
	int			m_nPort;
	string		m_strRHostIP; //원격 호스트의  아이피.
public:
	ClintSocket(int port = 9000 ,string ip = "127.0.0.1" ,ClintSocket::eMode mode = eTCP);
	virtual ~ClintSocket(void);

	void SetPort(int port);
	bool InitWinsock();
	bool InitSock();
};

