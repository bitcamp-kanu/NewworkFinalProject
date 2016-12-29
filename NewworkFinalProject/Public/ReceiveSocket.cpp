#include "ReceiveSocket.h"
#include "baseSocket.h"
#include <iostream>
#include <process.h>
#include <Windows.h>
#include "..\Public\PublicDefine.h"
#include <exception>
#include "Log.h"

ReceiveSocket::ReceiveSocket(void)
{
	memset(&m_oSockInfo,0x00,sizeof(m_oSockInfo));
	m_pRecviveEvent = NULL;
	m_hThread = 0x00;
}

ReceiveSocket::ReceiveSocket(const ReceiveSocket& item , IReceiveEvent* pIRecviveEvent/* = NULL*/)
{
	memcpy(&m_oSockInfo,&item.m_oSockInfo,sizeof(m_oSockInfo));
	m_pRecviveEvent = pIRecviveEvent;
	m_hThread = 0x00;
};

ReceiveSocket::~ReceiveSocket(void)
{
}
void ReceiveSocket::Release()
{
	this->m_oSockInfo.Release();
}

int ReceiveSocket::Send(char* buffer,int len)
{
	return send(m_oSockInfo.m_socket,buffer,len,0);	
}
bool ReceiveSocket::SetIReceiveEvent(IReceiveEvent* pRecviveEvent)
{
	m_pRecviveEvent = pRecviveEvent;
	return true;
}
int ReceiveSocket::ReceivtThreadRun()
{
	char buffer[_RECV_BUFFER_SIZE] = {0};
	int recvLen = 0;
	while(true)
	{
		recvLen = 0;
		recvLen = recv(this->m_oSockInfo.m_socket,buffer,sizeof(buffer),0);
		if(recvLen == 0 || recvLen == -1)
		{

		}
		if(m_pRecviveEvent != NULL)
		{
			m_pRecviveEvent->ReceiveEvent(this,buffer,recvLen);
		}
	}
	return 0;
}
bool ReceiveSocket::CreateThread()
{
	m_hThread =(HANDLE) _beginthreadex(0,0,ReceiveSocket::ThreadRun,this,0,0);
	return true;
}
unsigned int ReceiveSocket::ThreadRun(void* pData)
{
	ReceiveSocket* pSock = (ReceiveSocket*)pData;
	if(pSock != NULL)
	{
		pSock->ReceivtThreadRun();
	}
	return 0;
}
