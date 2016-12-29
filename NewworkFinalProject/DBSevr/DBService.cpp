#include "DBService.h"
#include "..\Public\WIUtility.h"
#include "..\Public\PublicDefine.h"

DBService::DBService(void)
{
}


DBService::~DBService(void)
{
}


int DBService::ReceiveEvent(SockBase* pSockBase,char* pData, int len)
{
	if(WIUtility::IsCommand(pData,"TE")) //�׽�Ʈ CMD �̸�
	{
		_Login logData;
		memcpy(&logData,pData,sizeof(_Login));
		cout << "DB Server ���� " << logData.ToString() << endl;
		logData.cont++;
		pSockBase->Send((char*)&logData,sizeof(_Login));
	}
	else if(WIUtility::IsCommand(pData,"AA")) //�׽�Ʈ CMD �̸�
	{
		_Login logData;
		memcpy(&logData,pData,sizeof(_Login));
		cout << "Work Server ���� " << logData.ToString() << endl;
		logData.cont++;
		pSockBase->Send((char*)&logData,sizeof(_Login));
	}
	return true;
}
