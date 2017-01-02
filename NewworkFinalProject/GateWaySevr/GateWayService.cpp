#include "GateWayService.h"
#include "..\Public\WIUtility.h"
#include "..\Public\PublicDefine.h"
#include "..\Public\ClientSocket.h"

GateWayService::GateWayService(void)
{
	InitializeCriticalSection(&m_cs);
	m_pDBConnectSock = NULL;
	m_pWSConnectSock = NULL;
}

GateWayService::~GateWayService(void)
{
	DeleteCriticalSection(&m_cs);
}


//DB 서버와 연결할 소켓 정보를 설정 한다.
void GateWayService::SetDBSvrConcSocket(ClientSocket* pClinetSock)
{

	this->m_pDBConnectSock = pClinetSock;
}
void GateWayService::SetWorkSvrConcSocket(ClientSocket* pClinetSock)
{
	m_pWSConnectSock = pClinetSock;
}
int GateWayService::IsSecretKey(char* pData)
{
	_SecretKeyChedk	secrKey;
	memcpy(&secrKey.header, pData, sizeof(_Header)); //Packet 에 Head 정보를 복사 한다.
	secrKey.header.cmd1 = 'E';
	secrKey.header.cmd2 = 'C';
	m_pDBConnectSock->Send((char*)&secrKey, sizeof(_SecretKeyChedk));
	Sleep(300);
	m_pDBConnectSock->Receive((char*)&secrKey, sizeof(_SecretKeyChedk));
	Sleep(300);
	return secrKey.header.SecretKey;
}
int GateWayService::ReceiveEvent(SockBase* pSockBase, char* pData, int len)
{
	try
	{
		//보안키를 검사 한다.
		if (WIUtility::IsCommand(pData, "AL")) //테스트 CMD 이면
		{
			_Login logData;
			memcpy(&logData, pData, sizeof(_Login));

			int secCode = IsSecretKey(pData);
			if (secCode = !201) //인증 실패.
			{
				//인증에 실패 하면 실패 코드를 입력 하고 들어온 패킷을 반환 한다.
				logData.header.pakID = secCode;
				Sleep(300);
				pSockBase->Send((char*)&logData, sizeof(_Login));
				return 0;
			}

			cout << "DB Server 패킷 전송 " << logData.ToString() << endl;
			logData.cont++;
			Sleep(300);
			this->Lock();
			m_pDBConnectSock->Send((char*)&logData, sizeof(_Login));
			logData.cont++;
			Sleep(300);
			m_pDBConnectSock->Receive((char*)&logData, sizeof(_Login));
			this->UnLock();
			memcpy(&logData, pData, sizeof(_Login));
			cout << "DB Server 패킷 수신  " << logData.ToString() << endl;
			logData.cont++;
			Sleep(300);
			pSockBase->Send((char*)&logData, sizeof(_Login));
			cout << "Client Server 패킷 전송  " << logData.ToString() << endl;

		}
		else if (WIUtility::IsCommand(pData, "US")) //USER 정보 요청
		{
			_DemandUserInfo userInof;
			memcpy(&userInof, pData, sizeof(_DemandUserInfo));
			int secCode = IsSecretKey(pData);
			if (secCode = !201) //인증 실패.
			{
				//인증에 실패 하면 실패 코드를 입력 하고 들어온 패킷을 반환 한다.
				userInof.header.pakID = secCode;
				Sleep(300);
				pSockBase->Send((char*)&userInof, sizeof(_DemandUserInfo));
				return 0;
			}
			//DB Server 로 데이터를 전송 한다.
			Sleep(300);
			this->Lock();
			m_pDBConnectSock->Send((char*)&userInof,sizeof(_DemandUserInfo));
			Sleep(300);
			m_pDBConnectSock->Receive((char*)&userInof,sizeof(_DemandUserInfo));
			this->UnLock();
			Sleep(300);
			pSockBase->Send((char*)&userInof,sizeof(_DemandUserInfo));

		}
		else if (WIUtility::IsCommand(pData, "AL")) //Admin Login CMD 이면
		{
		}
		else if (WIUtility::IsCommand(pData, "SS")) //Student Search
		{
			_Login logData;
			_SearchStudent studentInof;
			memcpy(&studentInof, pData, sizeof(_SearchStudent));
			int secCode = IsSecretKey(pData);
			if (secCode = !201) //인증 실패.
			{
				//인증에 실패 하면 실패 코드를 입력 하고 들어온 패킷을 반환 한다.
				logData.header.pakID = secCode;
				Sleep(300);
				pSockBase->Send((char*)&logData, sizeof(_Login));
				return 0;
			}
			//인증에 실패 하면 실패 코드를 입력 하고 들어온 패킷을 반환 한다.
			studentInof.header.pakID = secCode;
			Sleep(300);
			this->Lock();
			m_pDBConnectSock->Send((char*)&studentInof, sizeof(_SearchStudent));
			Sleep(300);
			m_pDBConnectSock->Receive((char*)&studentInof, sizeof(_SearchStudent));
			this->UnLock();
			Sleep(300);
			pSockBase->Send((char*)&studentInof, sizeof(_SearchStudent));
			return 0;
		}
		else if (WIUtility::IsCommand(pData, "SC")) 
		{
			_WorkData wordData;
			memcpy(&wordData, pData, sizeof(_WorkData));
			int secCode = IsSecretKey(pData);
			if (secCode = !201) //인증 실패.
			{
				//인증에 실패 하면 실패 코드를 입력 하고 들어온 패킷을 반환 한다.
				wordData.header.pakID = secCode;
				Sleep(300);
				pSockBase->Send((char*)&wordData, sizeof(_WorkData));
				return 0;
			}
			//인증에 실패 하면 실패 코드를 입력 하고 들어온 패킷을 반환 한다.
			wordData.header.pakID = secCode;
			Sleep(300);
			this->Lock();
			m_pDBConnectSock->Send((char*)&wordData, sizeof(_WorkData));
			//m_pWSConnectSock->Send((char*)&wordData, sizeof(_WorkData));
			Sleep(300);
			m_pDBConnectSock->Receive((char*)&wordData, sizeof(_WorkData));\
			this->UnLock();
			//m_pWSConnectSock->Receive((char*)&wordData, sizeof(_WorkData));
			Sleep(300);
			pSockBase->Send((char*)&wordData, sizeof(_WorkData));
			return 0;
		}
		else if (WIUtility::IsCommand(pData, "SU")) //Student update
		{
			_Login logData;
			_SearchStudent studentInof;
			memcpy(&studentInof, pData, sizeof(_SearchStudent));
			int secCode = IsSecretKey(pData);
			if (secCode = !201) //인증 실패.
			{
				//인증에 실패 하면 실패 코드를 입력 하고 들어온 패킷을 반환 한다.
				logData.header.pakID = secCode;
				Sleep(300);
				pSockBase->Send((char*)&logData, sizeof(_Login));
				return 0;
			}
			//인증에 실패 하면 실패 코드를 입력 하고 들어온 패킷을 반환 한다.
			studentInof.header.pakID = secCode;
			Sleep(300);
			this->Lock();
			m_pDBConnectSock->Send((char*)&studentInof, sizeof(_SearchStudent));
			Sleep(300);
			m_pDBConnectSock->Receive((char*)&studentInof, sizeof(_SearchStudent));\
			this->UnLock();
			Sleep(300);
			pSockBase->Send((char*)&studentInof, sizeof(_SearchStudent));
			return 0;
		}
		else if (WIUtility::IsCommand(pData, "SG")) //Student Grade
		{
			_WorkData workData;
			memcpy(&workData, pData, sizeof(_WorkData));
			int secCode = IsSecretKey(pData);
			if (secCode = !201) //인증 실패.
			{
				//인증에 실패 하면 실패 코드를 입력 하고 들어온 패킷을 반환 한다.
				workData.header.pakID = secCode;
				Sleep(300);
				pSockBase->Send((char*)&workData, sizeof(_WorkData));
				return 0;
			}
			//인증에 실패 하면 실패 코드를 입력 하고 들어온 패킷을 반환 한다.
			workData.header.pakID = secCode;
			this->Lock();
			m_pWSConnectSock->Send((char*)&workData, sizeof(_WorkData));
			Sleep(300);
			m_pWSConnectSock->Receive((char*)&workData, sizeof(_WorkData));
			this->UnLock();
			Sleep(300);
			pSockBase->Send((char*)&workData, sizeof(_WorkData));
			return 0;
		}
		else if (WIUtility::IsCommand(pData, "SD")) //Student delete
		{
			_Login logData;
			_SearchStudent studentInof;
			memcpy(&studentInof, pData, sizeof(_SearchStudent));
			int secCode = IsSecretKey(pData);
			if (secCode = !201) //인증 실패.
			{
				//인증에 실패 하면 실패 코드를 입력 하고 들어온 패킷을 반환 한다.
				logData.header.pakID = secCode;
				Sleep(300);
				pSockBase->Send((char*)&logData, sizeof(_Login));
				return 0;
			}
			//인증에 실패 하면 실패 코드를 입력 하고 들어온 패킷을 반환 한다.
			studentInof.header.pakID = secCode;
			Sleep(300);
			this->Lock();
			m_pDBConnectSock->Send((char*)&studentInof, sizeof(_SearchStudent));
			Sleep(300);
			m_pDBConnectSock->Receive((char*)&studentInof, sizeof(_SearchStudent));
			this->UnLock();
			Sleep(300);
			pSockBase->Send((char*)&studentInof, sizeof(_SearchStudent));
			return 0;
		}
		else if (WIUtility::IsCommand(pData, "AA")) //학생검색 ALL
		{
			_WorkDataEx workPacket;
			memcpy(&workPacket, pData, sizeof(_WorkDataEx));
			int secCode = IsSecretKey(pData);
			if (secCode = !201) //인증 실패.
			{
				//인증에 실패 하면 실패 코드를 입력 하고 들어온 패킷을 반환 한다.
				workPacket.header.pakID = secCode;
				Sleep(300);
				pSockBase->Send((char*)&workPacket, sizeof(_WorkDataEx));
				return 0;
			}
			//인증 성공.
			Sleep(300);
			this->Lock();
			m_pWSConnectSock->Send((char*)&workPacket, sizeof(_SearchStudent));
			char buff[_RECV_BUFFER_SIZE] = {0};
			int recv = m_pWSConnectSock->Receive(buff, _RECV_BUFFER_SIZE);
			this->UnLock();
			pSockBase->Send(buff, recv);
			return 0;
		}
		else if (WIUtility::IsCommand(pData, "TG")) //Admin Login CMD 이면
		{
			WorkTeset(pSockBase, pData, len);
		}
		else if (WIUtility::IsCommand(pData, "TW"))
		{
			WorkTeset(pSockBase, pData, len);
		}
	}
	catch (exceptionCS e)
	{
		//Recvive 로 예외상황을 알려준다.
		cout << "Client Socket 이 문제가 발생하였습니다." << endl;
		cout << e.what();
	}
	catch (exceptionRS e)
	{
		//Reveivw 에 문제가 생기면 ???? 
		cout << "Recvive Socket 이 문제가 발생하였습니다." << endl;
		cout << e.what(); //
	}
	return true;
}

int GateWayService::WorkTeset(SockBase* pSockBase, char* pData, int len)
{
	_Login logData;
	logData.SetCopyBuff(pData);
	try
	{

		if (logData.header.cmd2 == 'G')
		{
			logData.cont++;
			cout << "GateWayServer: 데이터를 수신하였습니다." << logData.ToString() << endl;
			m_pDBConnectSock->Send((char*)&logData, sizeof(_Login));
			logData.cont++;
			cout << "GateWayServer: 데이터를 DBServer 로 전송합니다.." << logData.ToString() << endl;
			m_pDBConnectSock->Receive((char*)&logData, sizeof(_Login));
			logData.cont++;
			cout << "GateWayServer: DBServer 에서 데이터를 수신하였습니다." << logData.ToString() << endl;
			logData.cont++;
			pSockBase->Send((char*)&logData, sizeof(_Login));
			cout << "GateWayServer: Client 로 데이터를 전송 합니다." << logData.ToString() << endl;
		}
		else if (logData.header.cmd2 == 'W')
		{
			logData.cont++;
			cout << "GateWayServer: 데이터를 수신하였습니다." << logData.ToString() << endl;
			m_pWSConnectSock->Send((char*)&logData, sizeof(_Login));
			logData.cont++;
			cout << "GateWayServer: 데이터를 WorkServer 로 전송합니다.." << logData.ToString() << endl;
			m_pWSConnectSock->Receive((char*)&logData, sizeof(_Login));
			logData.cont++;
			cout << "GateWayServer: Work 에서 데이터를 수신하였습니다." << logData.ToString() << endl;
			logData.cont++;
			pSockBase->Send((char*)&logData, sizeof(_Login));
			cout << "GateWayServer: Client 로 데이터를 전송 합니다." << logData.ToString() << endl;
		}
		else
		{
			cout << "GateWayService::WorkTeset 잘못된 Command 입니다.";
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
	return 0;

}