#pragma comment(lib,"Ws2_32.lib")
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
#include "Config.h"
#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <process.h>
#include <iostream>
#include "..\Public\ClientSocket.h"
#include "..\Public\PublicDefine.h"
#include "..\public\ServerSocket.h"
#include "..\public\Log.h"

#include "GateService.h"

void main()
{
	//Config::Instance()->LoadConfig();
	////�α����� ���ϸ��� �����Ѵ�.
	////CLog::Instance()->SetFilePath(Config::Instance()->m_strLogFileName);

	////Recvive �� ������ ����.
	//vector<ReceiveSocket*> rgpRevcSocket;

	//GateService oGateSvc;
	//ServerSocket oServerSock;
	//ClientSocket oSock(Config::Instance()->m_dbServerIP
	//	, Config::Instance()->m_nDbServerPort, ClientSocket::eTCP);


	//oServerSock.SetPort(Config::Instance()->m_nServerPort);
	//oServerSock.InitWinsock();
	//oServerSock.InitSock();
	//oServerSock.Bind();
	//oServerSock.Listen(Config::Instance()->m_nListenCnt);

	//oSock.InitWinsock();
	//oSock.InitSock();
	//oSock.Connect();//DB ������ ���� �Ѵ�.	

	//oGateSvc.SetDBSvrConcSocket(&oSock); // ���� ���� ������ ���� �Ѵ�.
	////_Gate pkGate('T', 'E', 'A', "��������̵�", "��й�ȣ�Դϴ�");


	//cout << "Gate Server �Դϴ�." << endl;

	//ReceiveSocket* pRecvSocket = NULL;
	//while (true)
	//{
	//	pRecvSocket = new ReceiveSocket();
	//	pRecvSocket = oServerSock.Accept(); //������ ��� ���� Reveive ������ ���� �ȴ�. 
	//	cout << "Gate Server client �� ���� �Ǿ����ϴ�." << endl;
	//	pRecvSocket->SetIReceiveEvent(&oGateSvc);
	//	pRecvSocket->CreateThread();
	//	rgpRevcSocket.push_back(pRecvSocket);
	//}

	//for (int i = 0; i < rgpRevcSocket.size(); i++)
	//{
	//	WaitForSingleObject(pRecvSocket->m_hThread, INFINITE);
	//}

	//for (int i = 0; i < rgpRevcSocket.size(); i++)
	//{
	//	delete rgpRevcSocket[i];
	//	rgpRevcSocket[i] = NULL;
	//}


}