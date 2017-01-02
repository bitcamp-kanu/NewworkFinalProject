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


//DB ������ ������ ���� ������ ���� �Ѵ�.
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
	memcpy(&secrKey.header,pData,sizeof(_Header)); //Packet �� Head ������ ���� �Ѵ�.
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
		//����Ű�� �˻� �Ѵ�.
		if(WIUtility::IsCommand(pData,"AL")) //�׽�Ʈ CMD �̸�
		{
			_Login logData;
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
			m_pDBConnectSock->Send((char*)&logData,sizeof(_Login));
			logData.cont++;
			m_pDBConnectSock->Receive((char*)&logData,sizeof(_Login));
			memcpy(&logData,pData,sizeof(_Login));
			cout << "DB Server ��Ŷ ����  " << logData.ToString() << endl;
			logData.cont++;
			pSockBase->Send((char*)&logData,sizeof(_Login));
			cout << "Client Server ��Ŷ ����  " << logData.ToString() << endl;
			
		}
		else if(WIUtility::IsCommand(pData,"US")) //USER ���� ��û
		{
			_DemandUserInfo userInof;
			memcpy(&userInof,pData,sizeof(_DemandUserInfo));
			int secCode = IsSecretKey(pData);
			if(secCode =! 201) //���� ����.
			{
				//������ ���� �ϸ� ���� �ڵ带 �Է� �ϰ� ���� ��Ŷ�� ��ȯ �Ѵ�.
				userInof.header.pakID = secCode;
				pSockBase->Send((char*)&userInof,sizeof(_DemandUserInfo));
				return 0;
			}
			//DB Server �� �����͸� ���� �Ѵ�.
			m_pDBConnectSock->Send((char*)&userInof,sizeof(_DemandUserInfo));
			m_pDBConnectSock->Receive((char*)&userInof,sizeof(_DemandUserInfo));
			pSockBase->Send((char*)&userInof,sizeof(_DemandUserInfo));

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
		}
		else if(WIUtility::IsCommand(pData,"TG")) //Admin Login CMD �̸�
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
		//Recvive �� ���ܻ�Ȳ�� �˷��ش�.
		cout << "Client Socket �� ������ �߻��Ͽ����ϴ�." << endl;
		cout << e.what();
	}
	catch (exceptionRS e)
	{
		//Reveivw �� ������ ����� ???? 
		cout << "Recvive Socket �� ������ �߻��Ͽ����ϴ�." << endl;
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
			cout << "GateWayServer: �����͸� �����Ͽ����ϴ�." << logData.ToString() << endl;
			m_pDBConnectSock->Send((char*)&logData,sizeof(_Login));
			logData.cont++;
			cout << "GateWayServer: �����͸� DBServer �� �����մϴ�.." << logData.ToString() << endl;
			m_pDBConnectSock->Receive((char*)&logData,sizeof(_Login));
			logData.cont++;
			cout << "GateWayServer: DBServer ���� �����͸� �����Ͽ����ϴ�." << logData.ToString() << endl;
			logData.cont++;
			pSockBase->Send((char*)&logData,sizeof(_Login));
			cout << "GateWayServer: Client �� �����͸� ���� �մϴ�." << logData.ToString() << endl;
		}
		else if (logData.header.cmd2 == 'W')
		{
			logData.cont++;
			cout << "GateWayServer: �����͸� �����Ͽ����ϴ�." << logData.ToString() << endl;
			m_pWSConnectSock->Send((char*)&logData,sizeof(_Login));
			logData.cont++;
			cout << "GateWayServer: �����͸� WorkServer �� �����մϴ�.." << logData.ToString() << endl;
			m_pWSConnectSock->Receive((char*)&logData,sizeof(_Login));
			logData.cont++;
			cout << "GateWayServer: Work ���� �����͸� �����Ͽ����ϴ�." << logData.ToString() << endl;
			logData.cont++;
			pSockBase->Send((char*)&logData,sizeof(_Login));
			cout << "GateWayServer: Client �� �����͸� ���� �մϴ�." << logData.ToString() << endl;
		}
		else
		{
			cout << "GateWayService::WorkTeset �߸��� Command �Դϴ�.";
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
	return 0;
	
}