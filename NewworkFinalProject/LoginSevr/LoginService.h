#pragma once
#include "..\Public\baseSocket.h"
#include "..\Public\ClientSocket.h"
class LoginService : public IReceiveEvent
{

private:
	//Login -> DB Serve 을 연결할 소켓.
	//SockBase* m_pClinetSock;
	ClientSocket* m_pClinetSock;
public:
	virtual int ReceiveEvent(SockBase* pSockBase,char* pData, int len);	
public:
	//DB 서버와 연결할 소켓 정보를 설정 한다.
	void SetDBSvrConcSocket(ClientSocket* pClinetSock);

	int WorkTeset(SockBase* pSockBase,char* pData, int len);
	LoginService(void);
	~LoginService(void);
};

