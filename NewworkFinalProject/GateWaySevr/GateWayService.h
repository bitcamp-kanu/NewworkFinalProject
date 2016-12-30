#pragma once
#include "..\Public\baseSocket.h"
#include "..\Public\ClientSocket.h"
class GateWayService : public IReceiveEvent
{
private:
	//SockBase* m_pClinetSock;
	ClientSocket* m_pDBConnectSock;
	ClientSocket* m_pWSConnectSock;

	//���� ������ �˻� �Ѵ�.
	int IsSecretKey(char* buff);
public:

	virtual int ReceiveEvent(SockBase* pSockBase,char* pData, int len);	
	int WorkTeset(SockBase* pSockBase,char* pData, int len);
public:
	//DB ������ ������ ���� ������ ���� �Ѵ�.
	void SetDBSvrConcSocket(ClientSocket* pClinetSock);
	void SetWorkSvrConcSocket(ClientSocket* pClinetSock);
	GateWayService(void);
	~GateWayService(void);
};