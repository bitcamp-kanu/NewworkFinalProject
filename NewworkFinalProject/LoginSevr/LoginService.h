#pragma once
#include "..\Public\baseSocket.h"
#include "..\Public\ClientSocket.h"
class LoginService : public IReceiveEvent
{

private:
	//Login -> DB Serve �� ������ ����.
	//SockBase* m_pClinetSock;
	ClientSocket* m_pClinetSock;
public:
	virtual int ReceiveEvent(SockBase* pSockBase,char* pData, int len);	
public:
	//DB ������ ������ ���� ������ ���� �Ѵ�.
	void SetDBSvrConcSocket(ClientSocket* pClinetSock);

	int WorkTeset(SockBase* pSockBase,char* pData, int len);
	LoginService(void);
	~LoginService(void);
};

