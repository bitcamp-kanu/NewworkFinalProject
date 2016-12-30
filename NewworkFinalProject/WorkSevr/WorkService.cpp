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
//DB ������ ������ ���� ������ ���� �Ѵ�.
void WorkService::SetDBSvrConcSocket(ClientSocket* pClinetSock)
{
	this->m_pClinetSock = pClinetSock;
}
int WorkService::ReceiveEvent(SockBase* pSockBase,char* pData, int len)
{
	if(WIUtility::IsCommand(pData,"AA")) //�׽�Ʈ CMD �̸�
	{
		_AverageAll AverageAllData;
		memcpy(&AverageAllData,pData,sizeof(_AverageAll));
		cout << "DB Server - All Average Data ���� " << AverageAllData.ToString() << endl;
		AverageAllData.cont ++;
		m_pClinetSock->Send((char*)&AverageAllData,sizeof(_AverageAll));
		AverageAllData.cont++;
		m_pClinetSock->Receive((char*)&AverageAllData,sizeof(_AverageAll));
		AverageAllData.cont++;
		pSockBase->Send((char*)&AverageAllData,sizeof(_AverageAll));
	}
	return true;
}