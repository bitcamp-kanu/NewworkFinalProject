#include "GateWayService.h"
#include "..\Public\WIUtility.h"
#include "..\Public\PublicDefine.h"
#include "..\Public\ClientSocket.h"

GateWayService::GateWayService(void)
{
	m_pDBConnectSock = NULL;
	m_pWSConnectSock = NULL;
}

GateWayService::~GateWayService(void)
{
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
	memcpy(&secrKey.header,pData,sizeof(_Header)); //Packet 에 Head 정보를 복사 한다.
	secrKey.header.cmd1 = 'E';
	secrKey.header.cmd2 = 'C';
	m_pDBConnectSock->Send((char*)&secrKey,sizeof(_SecretKeyChedk));
	m_pDBConnectSock->Receive((char*)&secrKey,sizeof(_SecretKeyChedk));
	return secrKey.header.SecretKey;
}
int GateWayService::ReceiveEvent(SockBase* pSockBase,char* pData, int len)
{
	try
	{
		//보안키를 검사 한다.
		if(WIUtility::IsCommand(pData,"AL")) //테스트 CMD 이면
		{
			_Login logData;
			memcpy(&logData,pData,sizeof(_Login));

			int secCode = IsSecretKey(pData);
			if(secCode =! 201) //인증 실패.
			{
				//인증에 실패 하면 실패 코드를 입력 하고 들어온 패킷을 반환 한다.
				logData.header.pakID = secCode;
				pSockBase->Send((char*)&logData,sizeof(_Login));
				return 0;
			}

			cout << "DB Server 패킷 전송 " << logData.ToString() << endl;
			logData.cont ++;
			m_pDBConnectSock->Send((char*)&logData,sizeof(_Login));
			logData.cont++;
			m_pDBConnectSock->Receive((char*)&logData,sizeof(_Login));
			memcpy(&logData,pData,sizeof(_Login));
			cout << "DB Server 패킷 수신  " << logData.ToString() << endl;
			logData.cont++;
			pSockBase->Send((char*)&logData,sizeof(_Login));
			cout << "Client Server 패킷 전송  " << logData.ToString() << endl;
			
		}
		else if(WIUtility::IsCommand(pData,"US")) //USER 정보 요청
		{
			_DemandUserInfo userInof;
			memcpy(&userInof,pData,sizeof(_DemandUserInfo));
			int secCode = IsSecretKey(pData);
			if(secCode =! 201) //인증 실패.
			{
				//인증에 실패 하면 실패 코드를 입력 하고 들어온 패킷을 반환 한다.
				userInof.header.pakID = secCode;
				pSockBase->Send((char*)&userInof,sizeof(_DemandUserInfo));
				return 0;
			}
			//DB Server 로 데이터를 전송 한다.
			m_pDBConnectSock->Send((char*)&userInof,sizeof(_DemandUserInfo));
			m_pDBConnectSock->Receive((char*)&userInof,sizeof(_DemandUserInfo));
			pSockBase->Send((char*)&userInof,sizeof(_DemandUserInfo));

		}
		else if(WIUtility::IsCommand(pData,"AL")) //Admin Login CMD 이면
		{
			int secCode = IsSecretKey(pData);
			if(secCode =! 201) //인증 실패.
			{
				//인증에 실패 하면 실패 코드를 입력 하고 들어온 패킷을
				//반환 한다.
				//logData.header.pakID = secCode;
				//pSockBase->Send((char*)&logData,sizeof(_Login));
				return 0;
			}
		}
		else if(WIUtility::IsCommand(pData,"TG")) //Admin Login CMD 이면
		{
			WorkTeset(pSockBase,pData,len);
		}
		else if(WIUtility::IsCommand(pData,"TW"))
		{
			WorkTeset(pSockBase,pData,len);
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

int GateWayService::WorkTeset(SockBase* pSockBase,char* pData, int len)
{
	_Login logData;	
	logData.SetCopyBuff(pData);
	try
	{

		if(logData.header.cmd2 == 'G')
		{
			logData.cont++;
			cout << "GateWayServer: 데이터를 수신하였습니다." << logData.ToString() << endl;
			m_pDBConnectSock->Send((char*)&logData,sizeof(_Login));
			logData.cont++;
			cout << "GateWayServer: 데이터를 DBServer 로 전송합니다.." << logData.ToString() << endl;
			m_pDBConnectSock->Receive((char*)&logData,sizeof(_Login));
			logData.cont++;
			cout << "GateWayServer: DBServer 에서 데이터를 수신하였습니다." << logData.ToString() << endl;
			logData.cont++;
			pSockBase->Send((char*)&logData,sizeof(_Login));
			cout << "GateWayServer: Client 로 데이터를 전송 합니다." << logData.ToString() << endl;
		}
		else if (logData.header.cmd2 == 'W')
		{
			logData.cont++;
			cout << "GateWayServer: 데이터를 수신하였습니다." << logData.ToString() << endl;
			m_pWSConnectSock->Send((char*)&logData,sizeof(_Login));
			logData.cont++;
			cout << "GateWayServer: 데이터를 WorkServer 로 전송합니다.." << logData.ToString() << endl;
			m_pWSConnectSock->Receive((char*)&logData,sizeof(_Login));
			logData.cont++;
			cout << "GateWayServer: Work 에서 데이터를 수신하였습니다." << logData.ToString() << endl;
			logData.cont++;
			pSockBase->Send((char*)&logData,sizeof(_Login));
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