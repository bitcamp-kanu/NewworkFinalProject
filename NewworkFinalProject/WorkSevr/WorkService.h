#pragma once
#include "..\Public\baseSocket.h"
#include "..\Public\ClientSocket.h"
class WorkService : public IReceiveEvent
{

private:
	//Work -> DB Serve 을 연결할 소켓.
	//SockBase* m_pClinetSock;
	ClientSocket* m_pClinetSock;
public:
	virtual int ReceiveEvent(SockBase* pSockBase,char* pData, int len);	
public:
	int WorkTeset(SockBase* pSockBase,char* pData, int len);
	int WorkStudentGrade(SockBase* pSockBase,char* pData, int len);
	//DB 서버와 연결할 소켓 정보를 설정 한다.
	void SetDBSvrConcSocket(ClientSocket* pClinetSock);
	WorkService(void);
	~WorkService(void);
};

