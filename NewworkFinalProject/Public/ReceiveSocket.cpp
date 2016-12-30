#include "ReceiveSocket.h"
#include "baseSocket.h"
#include <iostream>
#include <process.h>
//#include <windows.h>
#include "..\Public\PublicDefine.h"
#include <exception>
#include "Log.h"
#include "..\Public\WIUtility.h"
#include <exception>

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
	int ret  = send(m_oSockInfo.m_socket,buffer,len,0);
	if(ret <= 0)
	{
		throw exceptionRS(WIUtility::GetLastErrorMessage().c_str());
	}
	
	return ret;
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

	cout << "Recvive Sock Start." << endl;
	cout << GetInof() << endl;
	while(true)
	{
		recvLen = 0;
		recvLen = recv(m_oSockInfo.m_socket,buffer,sizeof(buffer),0);
		if(recvLen == 0 || recvLen == -1)
		{
			throw exceptionRS(WIUtility::GetLastErrorMessage().c_str());			
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
	try
	{
		if(pSock != NULL)
		{
			pSock->ReceivtThreadRun();
		}
	}
	catch (exceptionRS e) //여기부터 검사.
	{
		cout << e.what() << endl;
		cout << "데이터 수신 Thread 가 종료 되었습니다." << endl;
	}
	catch(exception e)
	{
		cout << e.what() << endl;
		cout << "데이터 수신 Thread 가 종료 되었습니다." << endl;
	}
	
	return 0;
}
string ReceiveSocket::GetInof()
{
	string str = WIUtility::GetFormatString("IP:[%s] ,Port[%c]"
											,WIUtility::GetSocketIP(m_oSockInfo.m_sockAddrIn).c_str()
											,WIUtility::GetSocketPORT(m_oSockInfo.m_sockAddrIn));
	return str;
}