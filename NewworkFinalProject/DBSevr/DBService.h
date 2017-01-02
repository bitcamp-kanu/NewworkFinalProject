#pragma once

#include "..\Public\baseSocket.h"
#include <process.h>
class DBManagerEx;
class DBService : public IReceiveEvent
{
	DBManagerEx* m_pDbManagerEx;
public:
	virtual int ReceiveEvent(SockBase* pSockBase,char* pData, int len);	
public:

	int WorkTeset(SockBase* pSockBase,char* pData, int len);
	DBService(void);
	~DBService(void);
};

