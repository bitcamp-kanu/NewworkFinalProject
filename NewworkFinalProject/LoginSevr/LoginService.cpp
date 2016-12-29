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
		memcpy(&logData,pData,sizeof(_Login));
		cout << "DB Server 수신 " << logData.ToString() << endl;
		logData.cont ++;
		m_pClinetSock->Send((char*)&logData,sizeof(_Login));
		logData.cont++;
		m_pClinetSock->Receive((char*)&logData,sizeof(_Login));
		logData.cont++;
		pSockBase->Send((char*)&logData,sizeof(_Login));
	}
	else if(WIUtility::IsCommand(pData,"AL")) //Admin Login CMD 이면
	{
		_Login logData;
		int key=rand()%127 + 1;

		memcpy(&logData,pData,sizeof(_Login));
		cout << "DB Server 수신 " << logData.ToString() << endl;
		logData.cont ++;
		m_pClinetSock->Send((char*)&logData,sizeof(_Login));
		logData.cont++;
		m_pClinetSock->Receive((char*)&logData,sizeof(_Login));
		logData.cont++;
		pSockBase->Send((char*)&logData,sizeof(_Login));
	}
	return true;
}