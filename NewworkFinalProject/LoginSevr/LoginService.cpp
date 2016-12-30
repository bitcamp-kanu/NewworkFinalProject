
#include "LoginService.h"
#include "..\Public\WIUtility.h"
#include "..\Public\PublicDefine.h"
#include "..\Public\ClientSocket.h"

LoginService::LoginService(void)
{
	m_pClinetSock = NULL;
}


LoginService::~LoginService(void)
{
}
//DB 서버와 연결할 소켓 정보를 설정 한다.
void LoginService::SetDBSvrConcSocket(ClientSocket* pClinetSock)
{
	this->m_pClinetSock = pClinetSock;
}
int LoginService::ReceiveEvent(SockBase* pSockBase,char* pData, int len)
{
	try
	{
		if(WIUtility::IsCommand(pData,"TE")) //테스트 CMD 이면
		{
			_Login logData;
			memcpy(&logData,pData,sizeof(_Login));
			cout << "DB Server 패킷 전송 " << logData.ToString() << endl;
			logData.cont ++;
			m_pClinetSock->Send((char*)&logData,sizeof(_Login));
			logData.cont++;
			m_pClinetSock->Receive((char*)&logData,sizeof(_Login));
			memcpy(&logData,pData,sizeof(_Login));
			cout << "DB Server 패킷 수신  " << logData.ToString() << endl;
			logData.cont++;
			pSockBase->Send((char*)&logData,sizeof(_Login));
			cout << "Client Server 패킷 전송  " << logData.ToString() << endl;
		}
		else if(WIUtility::IsCommand(pData,"AL")) //Admin Login CMD 이면
		{
			_Login logData;
			memcpy(&logData,pData,sizeof(_Login));
			int ikey = rand()%127 + 1;
			logData.header.SecretKey = char(ikey);

			cout << "DB Server 수신 " << logData.ToString() << endl;
			logData.cont ++;
			m_pClinetSock->Send((char*)&logData,sizeof(_Login));
			logData.cont++;
			m_pClinetSock->Receive((char*)&logData,sizeof(_Login));

			cout << "DB Server 패킷 수신  " << logData.ToString() << endl;
			logData.cont++;
			pSockBase->Send((char*)&logData,sizeof(_Login));

			cout << "Client Server 패킷 전송  " << logData.ToString() << endl;

		}
		else if(WIUtility::IsCommand(pData,"TL")) //테스트 CMD 이면
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

int LoginService::WorkTeset(SockBase* pSockBase,char* pData, int len)
{
	_Login logData;
	logData.SetCopyBuff(pData);
	logData.cont++;
	cout << "LoginServer: 데이터를 수신하였습니다." << logData.ToString() << endl;
	m_pClinetSock->Send((char*)&logData,sizeof(_Login));
	logData.cont++;
	cout << "LoginServer: 데이터를 DBServer 로 전송합니다.." << logData.ToString() << endl;
	m_pClinetSock->Receive((char*)&logData,sizeof(_Login));
	logData.cont++;
	cout << "LoginServer: DBServer 에서 데이터를 수신하였습니다." << logData.ToString() << endl;
	logData.cont++;
	pSockBase->Send((char*)&logData,sizeof(_Login));
	cout << "LoginServer: Client 로 데이터를 전송 합니다." << logData.ToString() << endl;
	return 0;
}
	