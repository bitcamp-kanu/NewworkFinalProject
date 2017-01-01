#include "DBService.h"

#include "..\Public\DefineSchema.h"
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

	try
	{
		if(WIUtility::IsCommand(pData,"AL")) //테스트 LO 이면
		{
			_Login logData;
			memcpy(&logData,pData,sizeof(_Login));
			cout << "DB Server 수신 " << logData.ToString() << endl;

			if(m_pDbManager->IsUserPassword(logData.id,logData.pass))
			{
				m_pDbManager->InsertSecretKey(logData.id, logData.header.SecretKey);
				logData.header.pakID = 111;
			}
			else
			{
				logData.header.pakID = 110;
			}
			logData.cont++;
			int error = pSockBase->Send((char*)&logData,sizeof(_Login));
		}
		else if (WIUtility::IsCommand(pData, "EC")) //보안키를 확인 한다.
		{
			_SecretKeyChedk sechtKey;
			memcpy(&sechtKey, pData, sizeof(_SecretKeyChedk));
			cout << "DB Server 수신 " << sechtKey.ToString() << endl;
			if(m_pDbManager->IsSecretKey(sechtKey.header.id, sechtKey.header.SecretKey))
			{
				sechtKey.header.pakID = 201; //인증 성공
			}
			else
			{ 
				sechtKey.header.pakID = 200; //인증 실패.
			}

			int error = pSockBase->Send((char*)&sechtKey, sizeof(_SecretKeyChedk));
		}
		else if(WIUtility::IsCommand(pData,"AA")) //테스트 CMD 이면
		{
			_Login logData;
			memcpy(&logData,pData,sizeof(_Login));
			cout << "Work Server 수신 " << logData.ToString() << endl;
			logData.cont++;
			pSockBase->Send((char*)&logData,sizeof(_Login));
		}
		else if(WIUtility::IsCommand(pData,"TL")) //테스트 CMD 이면
		{
			WorkTeset(pSockBase,pData,len);
		}
		else if(WIUtility::IsCommand(pData,"TG")) //테스트 CMD 이면
		{
			WorkTeset(pSockBase,pData,len);
		}
		else if(WIUtility::IsCommand(pData,"TW")) //테스트 CMD 이면
		{
			WorkTeset(pSockBase,pData,len);
		}
	}
	catch (exceptionCS e)
	{
		cout << "Client Socket 이 문제가 발생하였습니다." << endl;
		cout << e.what();
	}
	catch (exceptionRS e)
	{
		cout << "Recvive Socket 이 문제가 발생하였습니다." << endl;
		cout << e.what();
	}
	
	return true;
}

int DBService::WorkTeset(SockBase* pSockBase,char* pData, int len)
{
	_Login logData;
	logData.SetCopyBuff(pData);
	memcpy(&logData,pData,sizeof(_Login));
	if(logData.header.cmd2 == 'L')
	{
		cout << "DBServer: Login Server 에서 데이터 수신" << logData.ToString() << endl;
	}
	else if(logData.header.cmd2 == 'G')
	{
		cout << "DBServer: GateWay Server 에서 데이터 수신" << logData.ToString() << endl;
	}
	else if(logData.header.cmd2 == 'W')
	{
		cout << "DBServer: Work Server 에서 데이터 수신" << logData.ToString() << endl;
	}			

	logData.cont++;
	pSockBase->Send((char*)&logData,sizeof(_Login));
	if(logData.header.cmd2 == 'L')
	{
		cout << "DBServer: Login Server 에 데이터 전송" << logData.ToString() << endl;
	}
	else if(logData.header.cmd2 == 'G')
	{
		cout << "DBServer: GateWay Server 에 데이터 전송" << logData.ToString() << endl;
	}
	else if(logData.header.cmd2 == 'W')
	{
		cout << "DBServer: Work Server 에 데이터 전송" << logData.ToString() << endl;
	}	
	return 0;
}