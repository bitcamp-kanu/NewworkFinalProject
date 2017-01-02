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
	try
	{
		if(WIUtility::IsCommand(pData,"AA")) //전체 학생 목록 이면
		{
			_WorkDataEx WorkHeader;
			memcpy(&WorkHeader,pData,sizeof(_WorkDataEx));
			
			cout << "DB Server - All Average Data 전송요청 " << endl;
			m_pClinetSock->Send((char*)&WorkHeader,sizeof(_WorkDataEx));
			
			char buff[_RECV_BUFFER_SIZE];
			int len = m_pClinetSock->Receive((char*)&buff,sizeof(buff));
			cout << "DB Server - All Average Data 수신 " << endl;

			pSockBase->Send((char*)&buff,4096);
			cout << "Client Server - All Average Data 전송 " << endl;
		}
		else if(WIUtility::IsCommand(pData,"SC"))
		{

		}
		else if(WIUtility::IsCommand(pData,"SG")) //학생 점수 수정 이면
		{
			WorkStudentGrade(pSockBase,pData, len);
		}
		else if(WIUtility::IsCommand(pData,"TW")) //학생 점수 수정 이면
		{
			WorkTeset(pSockBase,pData, len);
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
int WorkService::WorkStudentGrade(SockBase* pSockBase,char* pData, int len)
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
	return 0;
}

int WorkService::WorkTeset(SockBase* pSockBase,char* pData, int len)
{
	_Login logData;
	logData.SetCopyBuff(pData);
	logData.cont++;
	cout << "WorkService: 데이터를 수신하였습니다." << logData.ToString() << endl;
	m_pClinetSock->Send((char*)&logData,sizeof(_Login));
	logData.cont++;
	cout << "WorkService: 데이터를 DBServer 로 전송합니다.." << logData.ToString() << endl;
	m_pClinetSock->Receive((char*)&logData,sizeof(_Login));
	logData.cont++;
	cout << "WorkService: DBServer 에서 데이터를 수신하였습니다." << logData.ToString() << endl;
	logData.cont++;
	pSockBase->Send((char*)&logData,sizeof(_Login));
	cout << "WorkService: GateWay 로 데이터를 전송 합니다." << logData.ToString() << endl;
	return 0;
}
