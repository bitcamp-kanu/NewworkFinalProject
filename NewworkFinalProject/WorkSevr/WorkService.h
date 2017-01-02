#pragma once
#include "..\Public\baseSocket.h"
#include "..\Public\ClientSocket.h"
#include <process.h>
class WorkService : public IReceiveEvent
{

private:
	CRITICAL_SECTION m_cs;
	//Work -> DB Serve �� ������ ����.
	//SockBase* m_pClinetSock;
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
	int WorkTeset(SockBase* pSockBase,char* pData, int len);
	int WorkStudentGrade(SockBase* pSockBase,char* pData, int len);
	//DB ������ ������ ���� ������ ���� �Ѵ�.
	void SetDBSvrConcSocket(ClientSocket* pClinetSock);
	WorkService(void);
	~WorkService(void);
};

