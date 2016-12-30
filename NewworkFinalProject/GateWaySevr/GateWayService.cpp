#include "GateWayService.h"
#include "..\Public\WIUtility.h"
#include "..\Public\PublicDefine.h"
#include "..\Public\ClientSocket.h"

GateWayService::GateWayService(void)
{
	m_pClinetSock = NULL;
}

GateWayService::~GateWayService(void)
{
}

//DB 서버와 연결할 소켓 정보를 설정 한다.
void GateWayService::SetDBSvrConcSocket(ClientSocket* pClinetSock)
{
	m_pClinetSock = pClinetSock;
}
int GateWayService::IsSecretKey(char* pData)
{
	_SecretKeyChedk	secrKey;
	memcpy(&secrKey.header,pData,sizeof(_Header)); //Packet 에 Head 정보를 복사 한다.
	secrKey.header.cmd1 = 'E';
	secrKey.header.cmd1 = 'C';
	m_pClinetSock->Send((char*)&secrKey,sizeof(_SecretKeyChedk));
	m_pClinetSock->Receive((char*)&secrKey,sizeof(_SecretKeyChedk));
	return secrKey.header.SecretKey;
}
int GateWayService::ReceiveEvent(SockBase* pSockBase,char* pData, int len)
{
	cout << "DB Server 보안인증 소켓을 전달 합니다. " << endl;
	//보안키를 검사 한다.
	if(WIUtility::IsCommand(pData,"AL")) //테스트 CMD 이면
	{
		_Login logData;
		try
		{
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
	else if(WIUtility::IsCommand(pData,"US")) //USER 정보 요청
	{
		_DemandUserInfo userInof;
		try
		{
			memcpy(&userInof,pData,sizeof(_DemandUserInfo));
			int secCode = IsSecretKey(pData);
			if(secCode =! 201) //인증 실패.
			{
				//인증에 실패 하면 실패 코드를 입력 하고 들어온 패킷을 반환 한다.
				userInof.header.pakID = secCode;
				pSockBase->Send((char*)&userInof,sizeof(_DemandUserInfo));
				return 0;
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

		try
		{

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