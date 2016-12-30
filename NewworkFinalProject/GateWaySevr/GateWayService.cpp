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

//DB ������ ������ ���� ������ ���� �Ѵ�.
void GateWayService::SetDBSvrConcSocket(ClientSocket* pClinetSock)
{
	m_pClinetSock = pClinetSock;
}
int GateWayService::IsSecretKey(char* pData)
{
	_SecretKeyChedk	secrKey;
	memcpy(&secrKey.header,pData,sizeof(_Header)); //Packet �� Head ������ ���� �Ѵ�.
	secrKey.header.cmd1 = 'E';
	secrKey.header.cmd1 = 'C';
	m_pClinetSock->Send((char*)&secrKey,sizeof(_SecretKeyChedk));
	m_pClinetSock->Receive((char*)&secrKey,sizeof(_SecretKeyChedk));
	return secrKey.header.SecretKey;
}
int GateWayService::ReceiveEvent(SockBase* pSockBase,char* pData, int len)
{
	cout << "DB Server �������� ������ ���� �մϴ�. " << endl;
	//����Ű�� �˻� �Ѵ�.
	if(WIUtility::IsCommand(pData,"AL")) //�׽�Ʈ CMD �̸�
	{
		_Login logData;
		try
		{
			memcpy(&logData,pData,sizeof(_Login));

			int secCode = IsSecretKey(pData);
			if(secCode =! 201) //���� ����.
			{
				//������ ���� �ϸ� ���� �ڵ带 �Է� �ϰ� ���� ��Ŷ�� ��ȯ �Ѵ�.
				logData.header.pakID = secCode;
				pSockBase->Send((char*)&logData,sizeof(_Login));
				return 0;
			}

			
			cout << "DB Server ��Ŷ ���� " << logData.ToString() << endl;
			logData.cont ++;
			m_pClinetSock->Send((char*)&logData,sizeof(_Login));
			logData.cont++;
			m_pClinetSock->Receive((char*)&logData,sizeof(_Login));
			memcpy(&logData,pData,sizeof(_Login));
			cout << "DB Server ��Ŷ ����  " << logData.ToString() << endl;
			logData.cont++;
			pSockBase->Send((char*)&logData,sizeof(_Login));
			cout << "Client Server ��Ŷ ����  " << logData.ToString() << endl;
	
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
	}
	else if(WIUtility::IsCommand(pData,"US")) //USER ���� ��û
	{
		_DemandUserInfo userInof;
		try
		{
			memcpy(&userInof,pData,sizeof(_DemandUserInfo));
			int secCode = IsSecretKey(pData);
			if(secCode =! 201) //���� ����.
			{
				//������ ���� �ϸ� ���� �ڵ带 �Է� �ϰ� ���� ��Ŷ�� ��ȯ �Ѵ�.
				userInof.header.pakID = secCode;
				pSockBase->Send((char*)&userInof,sizeof(_DemandUserInfo));
				return 0;
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

	}
	else if(WIUtility::IsCommand(pData,"AL")) //Admin Login CMD �̸�
	{
		int secCode = IsSecretKey(pData);
		if(secCode =! 201) //���� ����.
		{
			//������ ���� �ϸ� ���� �ڵ带 �Է� �ϰ� ���� ��Ŷ��
			//��ȯ �Ѵ�.
			//logData.header.pakID = secCode;
			//pSockBase->Send((char*)&logData,sizeof(_Login));
			return 0;
		}

		try
		{

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
	}
	return true;
}