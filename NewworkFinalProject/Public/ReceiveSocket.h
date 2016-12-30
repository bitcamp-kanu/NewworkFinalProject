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
	HANDLE m_hThread;
public: 
	//������Ƽ Get,Set �Լ�.
	bool SetIReceiveEvent(IReceiveEvent* pRecviveEvent);
public:
	ReceiveSocket();
	ReceiveSocket(const ReceiveSocket& item , IReceiveEvent* pIRecviveEvent = NULL);	
	virtual ~ReceiveSocket();	

	virtual int Send(char* buffer,int len);
	virtual int ReceivtThreadRun();
	bool CreateThread();
	void Release();
	string GetInof();

private:
	unsigned int  static CALLBACK ThreadRun(void* pData);
};

