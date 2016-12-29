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
	if(WIUtility::IsCommand(pData,"TE")) //테스트 CMD 이면
	{
		_Login logData;
		memcpy(&logData,pData,sizeof(_Login));
		cout << "DB Server 수신 " << logData.ToString() << endl;
		logData.cont++;
		pSockBase->Send((char*)&logData,sizeof(_Login));
	}
	else if(WIUtility::IsCommand(pData,"AA")) //테스트 CMD 이면
	{
		_Login logData;
		memcpy(&logData,pData,sizeof(_Login));
		cout << "Work Server 수신 " << logData.ToString() << endl;
		logData.cont++;
		pSockBase->Send((char*)&logData,sizeof(_Login));
	}
	return true;
}
