#pragma once

#include "..\Public\baseSocket.h"
class DBManager;
class DBService : public IReceiveEvent
{
	DBManager* m_pDbManager;
public:
	virtual int ReceiveEvent(SockBase* pSockBase,char* pData, int len);	
public:

	int WorkTeset(SockBase* pSockBase,char* pData, int len);
	DBService(void);
	~DBService(void);
};

