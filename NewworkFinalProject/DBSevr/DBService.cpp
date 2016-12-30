#include "DBService.h"

#include "..\Public\WIUtility.h"
#include "..\Public\PublicDefine.h"

#include "DBManager.h"

DBService::DBService(void)
{
	m_pDbManager = new DBManager();
	m_pDbManager->Open();
}


DBService::~DBService(void)
{
}


int DBService::ReceiveEvent(SockBase* pSockBase,char* pData, int len)
{
	if(WIUtility::IsCommand(pData,"AL")) //테스트 LO 이면
	{
		_Login logData;
		memcpy(&logData,pData,sizeof(_Login));
		cout << "DB Server 수신 " << logData.ToString() << endl;

		if(m_pDbManager->IsUserPassword(logData.id,logData.pass))
		{
			logData.header.pakID = 'T';
		}
		else
		{
			logData.header.pakID = 'F';
		}
		
		logData.cont++;
		int error = pSockBase->Send((char*)&logData,sizeof(_Login));

		printf(" %d ",error);
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
