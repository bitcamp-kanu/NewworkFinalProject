#include "ReceiveSocket.h"
#include "baseSocket.h"
#include <iostream>
#include <process.h>
#include <Windows.h>

ReceiveSocket::ReceiveSocket(void)
{
	memset(&m_oSockInfo,0x00,sizeof(m_oSockInfo));
	m_pRecviveEvent = NULL;
}
ReceiveSocket::ReceiveSocket(const ReceiveSocket& item)
{
	memcpy(&m_oSockInfo,&item.m_oSockInfo,sizeof(m_oSockInfo));
	m_pRecviveEvent = NULL;
	
};

ReceiveSocket::~ReceiveSocket(void)
{
}
void ReceiveSocket::Release()
{
	this->m_oSockInfo.Release();
}

int ReceiveSocket::Send()
{
	return 0;
}

int ReceiveSocket::ReceivtThreadRun()
{
	return 0;
}
bool ReceiveSocket::CreateThread()
{
	HANDLE h =(HANDLE) _beginthreadex(0,0,ReceiveSocket::ThreadRun,0,0,0);
	return true;
}
unsigned int ReceiveSocket::ThreadRun(void* pData)
{
	ReceiveSocket* pSock = (ReceiveSocket*)pData;
	pSock->ReceivtThreadRun();
	return 0;
}
