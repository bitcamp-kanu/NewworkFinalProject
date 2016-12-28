#pragma once
#pragma comment(lib,"Ws2_32.lib") //winsock 2.2 라이브러리
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
#include <WinSock2.h> //Winsock 2 버전 Header
#include <string.h>

class IReceiveEvent
{
	virtual int ReceiveEvent(void* pObj,char* pData, int len) = 0;	
};

class SockInfo
{
public:
	SOCKET m_socket;
	SOCKADDR_IN m_sockAddrIn;
	SOCKADDR	m_sockAddr;
public:
	SockInfo()
	{
		memset(&m_socket,0x00,sizeof(SOCKET));
		memset(&m_sockAddrIn,0x00,sizeof(SOCKADDR_IN));
	}

	SockInfo(const SockInfo& item)
	{
		memcpy(&m_socket,&item.m_socket,sizeof(m_socket));
		memcpy(&m_sockAddrIn,&item.m_sockAddrIn,sizeof(m_sockAddrIn));
		memcpy(&m_sockAddr,&item.m_sockAddr,sizeof(m_sockAddr));
	};
	void Release()
	{
		if(m_socket  != 0x00)
		{
			closesocket(m_socket);
			m_socket = 0x00;	
		}
	}
	virtual ~SockInfo()
	{
		
	}
};


class SockBase
{
public:
	SockBase()
	{
	}

	SockBase(const SockBase& item)
	{		
	};
	 ~SockBase()
	{

	}
	 // 데이터를 전송 한다.
	 virtual int Send() = 0;
	 virtual int ReceivtThreadRun() = 0;
};