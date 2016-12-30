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
	if(WIUtility::IsCommand(pData,"AA")) //전체 학생 목록 이면
	{
		_WorkData WorkData;
		
		memcpy(&WorkData,pData,sizeof(_WorkData));
		cout << "DB Server - All Average Data 전송 " << WorkData.ToString() << endl;
		WorkData.cont ++;
		m_pClinetSock->Send((char*)&WorkData,sizeof(_WorkData));
		WorkData.cont++;
		m_pClinetSock->Receive((char*)&WorkData,sizeof(_WorkData));
		cout << "DB Server - All Average Data 수신 " << WorkData.ToString() << endl;
		WorkData.cont++;
		pSockBase->Send((char*)&WorkData,sizeof(_WorkData));
		cout << "Client Server - All Average Data 전송 " << WorkData.ToString() << endl;
	}

	if(WIUtility::IsCommand(pData,"GU")) //학생 점수 수정 이면
	{
		_WorkData WorkData;
		memcpy(&WorkData,pData,sizeof(_WorkData));
		//============================================
		WorkData.Total=WorkData.C + WorkData.CPP + WorkData.CSharp
					+ WorkData.Network + WorkData.Unity;
		WorkData.Ave=WorkData.Total/5;
		//============================================
		cout << "DB Server - WorkData 수신 " << WorkData.ToString() << endl;
		WorkData.cont ++;
		m_pClinetSock->Send((char*)&WorkData,sizeof(_WorkData));
		WorkData.cont++;
		m_pClinetSock->Receive((char*)&WorkData,sizeof(_WorkData));
		cout << "DB Server - WorkData 수신 " << WorkData.ToString() << endl;
		WorkData.cont++;
		pSockBase->Send((char*)&WorkData,sizeof(_WorkData));
		cout << "Client Server - WorkData 전송 " << WorkData.ToString() << endl;
	}
	return true;
}