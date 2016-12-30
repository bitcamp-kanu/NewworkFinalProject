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
#include <time.h>
#include "..\Public\ClientSocket.h"
#include "..\Public\PublicDefine.h"
#include "..\public\ServerSocket.h"
#include "..\public\Log.h"
#include "..\public\WIUtility.h"

#include "LoginService.h"

void main()
{
	cout << "--------- Login Server �� ���� �մϴ�..----------------" << endl;
	srand(unsigned int(time(NULL)));

	Config::Instance()->LoadConfig();
	//�α����� ���ϸ��� �����Ѵ�.
	//CLog::Instance()->SetFilePath(Config::Instance()->m_strLogFileName);

	//Recvive �� ������ ����.
	vector<ReceiveSocket*> rgpRevcSocket; 

	LoginService oLoginSvc;
	ServerSocket oServerSock;
	ClientSocket oSock(Config::Instance()->m_dbServerIP
					,Config::Instance()->m_nDbServerPort,ClientSocket::eTCP);


	string str = WIUtility::GetLastErrorMessage();
	cout << str.c_str();
	system("puese");


	oServerSock.SetPort(Config::Instance()->m_nServerPort);
	oServerSock.InitWinsock();
	oServerSock.InitSock();
	oServerSock.Bind();
	oServerSock.Listen(Config::Instance()->m_nListenCnt);

	try
	{
		oSock.InitWinsock();
		oSock.InitSock();
		oSock.Connect();//DB ������ ���� �Ѵ�.	
	}
	catch (exception e)
	{
		cout << "DB ���� ������ ������ �߻� �Ͽ� ������ ���� �մϴ�. " << endl;
		cout << "msg: " << e.what() << endl;
		system("pause");
		return;
	}
	
	
	oLoginSvc.SetDBSvrConcSocket(&oSock); // DB ���� ���� ������ ���� �Ѵ�.
	//_Login pkLogin('T','E','A',"��������̵�","��й�ȣ�Դϴ�");
	
	cout << "Login Server �Դϴ�." << endl;

	ReceiveSocket* pRecvSocket = NULL;
	while(true)
	{
		pRecvSocket = new ReceiveSocket();		
		pRecvSocket= oServerSock.Accept(); //������ ��� ���� Reveive ������ ���� �ȴ�. 
		cout <<"Login Server client �� ���� �Ǿ����ϴ�." << endl;
		pRecvSocket->SetIReceiveEvent(&oLoginSvc);
		pRecvSocket ->CreateThread();
		rgpRevcSocket.push_back(pRecvSocket);
	}	

	for(unsigned int i = 0 ; i < rgpRevcSocket.size(); i++)
	{
		WaitForSingleObject(pRecvSocket ->m_hThread,INFINITE);
	}

	for(unsigned int i = 0 ; i < rgpRevcSocket.size(); i++)
	{
		delete rgpRevcSocket[i];
		rgpRevcSocket[i] = NULL;
	}


}