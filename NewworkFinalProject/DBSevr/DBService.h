#pragma once
#include "..\Public\baseSocket.h"
class DBService : public IReceiveEvent
{
public:
	virtual int ReceiveEvent(SockBase* pSockBase,char* pData, int len);	
public:
	DBService(void);
	~DBService(void);
};

