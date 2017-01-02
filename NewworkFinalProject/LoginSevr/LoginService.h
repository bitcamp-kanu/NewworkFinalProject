#pragma once
#include "..\Public\baseSocket.h"
#include "..\Public\ClientSocket.h"
#include <process.h>
class LoginService : public IReceiveEvent
{

private:
	CRITICAL_SECTION m_cs;
	//Login -> DB Serve 을 연결할 소켓.
	ClientSocket* m_pClinetSock;
public:
	void Lock()
	{
		EnterCriticalSection(&m_cs);

	}
	void UnLock()
	{
		LeaveCriticalSection(&m_cs);
	}
	virtual int ReceiveEvent(SockBase* pSockBase,char* pData, int len);	
public:
	//DB 서버와 연결할 소켓 정보를 설정 한다.
	void SetDBSvrConcSocket(ClientSocket* pClinetSock);

	int WorkTeset(SockBase* pSockBase,char* pData, int len);
	LoginService(void);
	~LoginService(void);
};

