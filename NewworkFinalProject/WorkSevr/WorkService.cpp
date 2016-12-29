#include "WorkService.h"
#include "..\Public\WIUtility.h"
#include "..\Public\PublicDefine.h"
#include "..\Public\ClientSocket.h"

WorkService::WorkService(void)
{
	m_pClinetSock = NULL;
}


WorkService::~WorkService(void)
{
}
//DB 서버와 연결할 소켓 정보를 설정 한다.
void WorkService::SetDBSvrConcSocket(ClientSocket* pClinetSock)
{
	this->m_pClinetSock = pClinetSock;
}
int WorkService::ReceiveEvent(SockBase* pSockBase,char* pData, int len)
{
	if(WIUtility::IsCommand(pData,"AA")) //테스트 CMD 이면
	{
		_AverageAll AverageAllData;
		memcpy(&AverageAllData,pData,sizeof(_AverageAll));
		cout << "DB Server - All Average Data 수신 " << AverageAllData.ToString() << endl;
		AverageAllData.cont ++;
		m_pClinetSock->Send((char*)&AverageAllData,sizeof(_AverageAll));
		AverageAllData.cont++;
		m_pClinetSock->Receive((char*)&AverageAllData,sizeof(_AverageAll));
		AverageAllData.cont++;
		pSockBase->Send((char*)&AverageAllData,sizeof(_AverageAll));
	}
	return true;
}