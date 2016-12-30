
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
	if(WIUtility::IsCommand(pData,"TE")) //테스트 CMD 이면
	{
		_Login logData;
		try
		{
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
	}
	else if(WIUtility::IsCommand(pData,"AL")) //Admin Login CMD 이면
	{
		_Login logData;
		
		
		try
		{
			memcpy(&logData,pData,sizeof(_Login));
			int ikey = rand()%127 + 1;
			logData.SecretKey = char(ikey);
			logData.SecretKey = 'A';

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
	}
	return true;
}