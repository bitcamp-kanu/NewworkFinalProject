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
	memcpy(&secrKey.header, pData, sizeof(_Header)); //Packet �� Head ������ ���� �Ѵ�.
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
		//����Ű�� �˻� �Ѵ�.
		if (WIUtility::IsCommand(pData, "AL")) //�׽�Ʈ CMD �̸�
		{
			_Login logData;
			memcpy(&logData, pData, sizeof(_Login));

			int secCode = IsSecretKey(pData);
			if (secCode = !201) //���� ����.
			{
				//������ ���� �ϸ� ���� �ڵ带 �Է� �ϰ� ���� ��Ŷ�� ��ȯ �Ѵ�.
				logData.header.pakID = secCode;
				Sleep(300);
				pSockBase->Send((char*)&logData, sizeof(_Login));
				return 0;
			}

			cout << "DB Server ��Ŷ ���� " << logData.ToString() << endl;
			logData.cont++;
			Sleep(300);
			this->Lock();
			m_pDBConnectSock->Send((char*)&logData, sizeof(_Login));
			logData.cont++;
			Sleep(300);
			m_pDBConnectSock->Receive((char*)&logData, sizeof(_Login));
			this->UnLock();
			memcpy(&logData, pData, sizeof(_Login));
			cout << "DB Server ��Ŷ ����  " << logData.ToString() << endl;
			logData.cont++;
			Sleep(300);
			pSockBase->Send((char*)&logData, sizeof(_Login));
			cout << "Client Server ��Ŷ ����  " << logData.ToString() << endl;

		}
		else if (WIUtility::IsCommand(pData, "US")) //USER ���� ��û
		{
			_DemandUserInfo userInof;
			memcpy(&userInof, pData, sizeof(_DemandUserInfo));
			int secCode = IsSecretKey(pData);
			if (secCode = !201) //���� ����.
			{
				//������ ���� �ϸ� ���� �ڵ带 �Է� �ϰ� ���� ��Ŷ�� ��ȯ �Ѵ�.
				userInof.header.pakID = secCode;
				Sleep(300);
				pSockBase->Send((char*)&userInof, sizeof(_DemandUserInfo));
				return 0;
			}
			//DB Server �� �����͸� ���� �Ѵ�.
			Sleep(300);
			this->Lock();
			m_pDBConnectSock->Send((char*)&userInof,sizeof(_DemandUserInfo));
			Sleep(300);
			m_pDBConnectSock->Receive((char*)&userInof,sizeof(_DemandUserInfo));
			this->UnLock();
			Sleep(300);
			pSockBase->Send((char*)&userInof,sizeof(_DemandUserInfo));

		}
		else if (WIUtility::IsCommand(pData, "AL")) //Admin Login CMD �̸�
		{
		}
		else if (WIUtility::IsCommand(pData, "SS")) //Student Search
		{
			_Login logData;
			_SearchStudent studentInof;
			memcpy(&studentInof, pData, sizeof(_SearchStudent));
			int secCode = IsSecretKey(pData);
			if (secCode = !201) //���� ����.
			{
				//������ ���� �ϸ� ���� �ڵ带 �Է� �ϰ� ���� ��Ŷ�� ��ȯ �Ѵ�.
				logData.header.pakID = secCode;
				Sleep(300);
				pSockBase->Send((char*)&logData, sizeof(_Login));
				return 0;
			}
			//������ ���� �ϸ� ���� �ڵ带 �Է� �ϰ� ���� ��Ŷ�� ��ȯ �Ѵ�.
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
			if (secCode = !201) //���� ����.
			{
				//������ ���� �ϸ� ���� �ڵ带 �Է� �ϰ� ���� ��Ŷ�� ��ȯ �Ѵ�.
				wordData.header.pakID = secCode;
				Sleep(300);
				pSockBase->Send((char*)&wordData, sizeof(_WorkData));
				return 0;
			}
			//������ ���� �ϸ� ���� �ڵ带 �Է� �ϰ� ���� ��Ŷ�� ��ȯ �Ѵ�.
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
			if (secCode = !201) //���� ����.
			{
				//������ ���� �ϸ� ���� �ڵ带 �Է� �ϰ� ���� ��Ŷ�� ��ȯ �Ѵ�.
				logData.header.pakID = secCode;
				Sleep(300);
				pSockBase->Send((char*)&logData, sizeof(_Login));
				return 0;
			}
			//������ ���� �ϸ� ���� �ڵ带 �Է� �ϰ� ���� ��Ŷ�� ��ȯ �Ѵ�.
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
			if (secCode = !201) //���� ����.
			{
				//������ ���� �ϸ� ���� �ڵ带 �Է� �ϰ� ���� ��Ŷ�� ��ȯ �Ѵ�.
				workData.header.pakID = secCode;
				Sleep(300);
				pSockBase->Send((char*)&workData, sizeof(_WorkData));
				return 0;
			}
			//������ ���� �ϸ� ���� �ڵ带 �Է� �ϰ� ���� ��Ŷ�� ��ȯ �Ѵ�.
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
			if (secCode = !201) //���� ����.
			{
				//������ ���� �ϸ� ���� �ڵ带 �Է� �ϰ� ���� ��Ŷ�� ��ȯ �Ѵ�.
				logData.header.pakID = secCode;
				Sleep(300);
				pSockBase->Send((char*)&logData, sizeof(_Login));
				return 0;
			}
			//������ ���� �ϸ� ���� �ڵ带 �Է� �ϰ� ���� ��Ŷ�� ��ȯ �Ѵ�.
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
		else if (WIUtility::IsCommand(pData, "AA")) //�л��˻� ALL
		{
			_WorkDataEx workPacket;
			memcpy(&workPacket, pData, sizeof(_WorkDataEx));
			int secCode = IsSecretKey(pData);
			if (secCode = !201) //���� ����.
			{
				//������ ���� �ϸ� ���� �ڵ带 �Է� �ϰ� ���� ��Ŷ�� ��ȯ �Ѵ�.
				workPacket.header.pakID = secCode;
				Sleep(300);
				pSockBase->Send((char*)&workPacket, sizeof(_WorkDataEx));
				return 0;
			}
			//���� ����.
			Sleep(300);
			this->Lock();
			m_pWSConnectSock->Send((char*)&workPacket, sizeof(_SearchStudent));
			char buff[_RECV_BUFFER_SIZE] = {0};
			int recv = m_pWSConnectSock->Receive(buff, _RECV_BUFFER_SIZE);
			this->UnLock();
			pSockBase->Send(buff, recv);
			return 0;
		}
		else if (WIUtility::IsCommand(pData, "TG")) //Admin Login CMD �̸�
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

int GateWayService::WorkTeset(SockBase* pSockBase, char* pData, int len)
{
	_Login logData;
	logData.SetCopyBuff(pData);
	try
	{

		if (logData.header.cmd2 == 'G')
		{
			logData.cont++;
			cout << "GateWayServer: �����͸� �����Ͽ����ϴ�." << logData.ToString() << endl;
			m_pDBConnectSock->Send((char*)&logData, sizeof(_Login));
			logData.cont++;
			cout << "GateWayServer: �����͸� DBServer �� �����մϴ�.." << logData.ToString() << endl;
			m_pDBConnectSock->Receive((char*)&logData, sizeof(_Login));
			logData.cont++;
			cout << "GateWayServer: DBServer ���� �����͸� �����Ͽ����ϴ�." << logData.ToString() << endl;
			logData.cont++;
			pSockBase->Send((char*)&logData, sizeof(_Login));
			cout << "GateWayServer: Client �� �����͸� ���� �մϴ�." << logData.ToString() << endl;
		}
		else if (logData.header.cmd2 == 'W')
		{
			logData.cont++;
			cout << "GateWayServer: �����͸� �����Ͽ����ϴ�." << logData.ToString() << endl;
			m_pWSConnectSock->Send((char*)&logData, sizeof(_Login));
			logData.cont++;
			cout << "GateWayServer: �����͸� WorkServer �� �����մϴ�.." << logData.ToString() << endl;
			m_pWSConnectSock->Receive((char*)&logData, sizeof(_Login));
			logData.cont++;
			cout << "GateWayServer: Work ���� �����͸� �����Ͽ����ϴ�." << logData.ToString() << endl;
			logData.cont++;
			pSockBase->Send((char*)&logData, sizeof(_Login));
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