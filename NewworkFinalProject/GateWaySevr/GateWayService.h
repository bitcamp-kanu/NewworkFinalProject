#pragma once
#include "..\Public\baseSocket.h"
#include "..\Public\ClientSocket.h"
#include <process.h>
class GateWayService : public IReceiveEvent
{
private:
	CRITICAL_SECTION m_cs;
	
	//SockBase* m_pClinetSock;
	ClientSocket* m_pDBConnectSock;
	ClientSocket* m_pWSConnectSock;

	//보안 인증을 검사 한다.
	int IsSecretKey(char* buff);
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
	int WorkTeset(SockBase* pSockBase,char* pData, int len);
public:
	//DB 서버와 연결할 소켓 정보를 설정 한다.
	void SetDBSvrConcSocket(ClientSocket* pClinetSock);
	void SetWorkSvrConcSocket(ClientSocket* pClinetSock);
	GateWayService(void);
	~GateWayService(void);
};