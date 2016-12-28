#pragma once
#pragma comment(lib,"Ws2_32.lib") //winsock 2.2 ���̺귯��
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
#include <WinSock2.h> //Winsock 2 ���� Header
#include <string.h>
#include "baseSocket.h"
//���� ���Ͽ� Accept �۾����� ���� ����.. 

class ReceiveSocket : public SockBase
{
public:
	IReceiveEvent* m_pRecviveEvent; 
	SockInfo m_oSockInfo;
public:
	ReceiveSocket();
	ReceiveSocket(const ReceiveSocket& item);	
	virtual ~ReceiveSocket();	
	// �����͸� ���� �Ѵ�.
	virtual int Send();
	virtual int ReceivtThreadRun();

	unsigned int  static CALLBACK ThreadRun(void* pData);
	bool CreateThread();
	void Release();
};

