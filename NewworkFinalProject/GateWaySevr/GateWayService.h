#pragma once
#include "..\Public\baseSocket.h"
#include "..\Public\ClientSocket.h"
class GateWayService : public IReceiveEvent
{
private:
	//SockBase* m_pClinetSock;
	ClientSocket* m_pClinetSock;

	//���� ������ �˻� �Ѵ�.
	int IsSecretKey(char* buff);
public:

	virtual int ReceiveEvent(SockBase* pSockBase,char* pData, int len);	
public:
	//DB ������ ������ ���� ������ ���� �Ѵ�.
	void SetDBSvrConcSocket(ClientSocket* pClinetSock);
	GateWayService(void);
	~GateWayService(void);
};