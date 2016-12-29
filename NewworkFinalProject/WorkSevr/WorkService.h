#pragma once
#include "..\Public\baseSocket.h"
#include "..\Public\ClientSocket.h"
class WorkService : public IReceiveEvent
{

private:
	//Work -> DB Serve �� ������ ����.
	//SockBase* m_pClinetSock;
	ClientSocket* m_pClinetSock;
public:
	virtual int ReceiveEvent(SockBase* pSockBase,char* pData, int len);	
public:
	//DB ������ ������ ���� ������ ���� �Ѵ�.
	void SetDBSvrConcSocket(ClientSocket* pClinetSock);
	WorkService(void);
	~WorkService(void);
};
