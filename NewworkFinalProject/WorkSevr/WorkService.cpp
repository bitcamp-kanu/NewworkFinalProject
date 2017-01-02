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
	try
	{
		if(WIUtility::IsCommand(pData,"AA")) //��ü �л� ��� �̸�
		{
			_WorkDataEx WorkHeader;
			memcpy(&WorkHeader,pData,sizeof(_WorkDataEx));
			
			cout << "DB Server - All Average Data ���ۿ�û " << endl;
			m_pClinetSock->Send((char*)&WorkHeader,sizeof(_WorkDataEx));
			
			char buff[_RECV_BUFFER_SIZE];
			int len = m_pClinetSock->Receive((char*)&buff,sizeof(buff));
			cout << "DB Server - All Average Data ���� " << endl;

			pSockBase->Send((char*)&buff,4096);
			cout << "Client Server - All Average Data ���� " << endl;
		}
		else if(WIUtility::IsCommand(pData,"SC"))
		{

		}
		else if(WIUtility::IsCommand(pData,"SG")) //�л� ���� ���� �̸�
		{
			WorkStudentGrade(pSockBase,pData, len);
		}
		else if(WIUtility::IsCommand(pData,"TW")) //�л� ���� ���� �̸�
		{
			WorkTeset(pSockBase,pData, len);
		}
	}
	catch (exceptionCS e)
	{
		cout << "Client Socket �� ������ �߻��Ͽ����ϴ�." << endl;
		cout << e.what();
	}
	catch (exceptionRS e)
	{
		cout << "Recvive Socket �� ������ �߻��Ͽ����ϴ�." << endl;
		cout << e.what();
	}
	return true;
}
int WorkService::WorkStudentGrade(SockBase* pSockBase,char* pData, int len)
{
	_WorkData WorkData;
	memcpy(&WorkData,pData,sizeof(_WorkData));

	//============================================
	WorkData.Total=WorkData.C + WorkData.CPP + WorkData.CSharp
		+ WorkData.Network + WorkData.Unity;
	WorkData.Ave=WorkData.Total/5;
	//============================================
	cout << "DB Server - WorkData ���� " << WorkData.ToString() << endl;
	WorkData.cont ++;
	m_pClinetSock->Send((char*)&WorkData,sizeof(_WorkData));
	WorkData.cont++;
	m_pClinetSock->Receive((char*)&WorkData,sizeof(_WorkData));
	cout << "DB Server - WorkData ���� " << WorkData.ToString() << endl;
	WorkData.cont++;
	pSockBase->Send((char*)&WorkData,sizeof(_WorkData));
	cout << "Client Server - WorkData ���� " << WorkData.ToString() << endl;
	return 0;
}

int WorkService::WorkTeset(SockBase* pSockBase,char* pData, int len)
{
	_Login logData;
	logData.SetCopyBuff(pData);
	logData.cont++;
	cout << "WorkService: �����͸� �����Ͽ����ϴ�." << logData.ToString() << endl;
	m_pClinetSock->Send((char*)&logData,sizeof(_Login));
	logData.cont++;
	cout << "WorkService: �����͸� DBServer �� �����մϴ�.." << logData.ToString() << endl;
	m_pClinetSock->Receive((char*)&logData,sizeof(_Login));
	logData.cont++;
	cout << "WorkService: DBServer ���� �����͸� �����Ͽ����ϴ�." << logData.ToString() << endl;
	logData.cont++;
	pSockBase->Send((char*)&logData,sizeof(_Login));
	cout << "WorkService: GateWay �� �����͸� ���� �մϴ�." << logData.ToString() << endl;
	return 0;
}
