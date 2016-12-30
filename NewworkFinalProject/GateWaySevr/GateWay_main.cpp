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

#include "GateWayService.h" //GateWay 서비스... 



void main()
{
	Config::Instance()->LoadConfig();
	CLog::Instance()->SetFilePath(Config::Instance()->m_strLogFileName);
	//Recvive 를 저장할 소켓.
	vector<ReceiveSocket*> rgpRevcSocket;
	GateWayService oGateWaySvc;
	
	ServerSocket oServerSock;
	ClientSocket oSock(Config::Instance()->m_dbServerIP
		, Config::Instance()->m_nDbServerPort, ClientSocket::eTCP);

	try
	{
		oServerSock.SetPort(Config::Instance()->m_nServerPort);
		oServerSock.InitWinsock();
		oServerSock.InitSock();
		oServerSock.Bind();
		oServerSock.Listen(Config::Instance()->m_nListenCnt);

		oSock.InitWinsock();
		oSock.InitSock();
		oSock.Connect();//DB 서버에 연결 한다.	
	}
	catch (exceptionCS e)
	{
		cout << "Client Socket 에서 문제가 발생하였습니다. " << e.what() << endl;
	}
	catch (exceptionRS e)
	{
		cout << "Recevie Socket 에서 문제가 발생하였습니다. " << e.what() << endl;
	}
	catch (exceptionSS e)
	{
		cout << "Server Socket 에서 문제가 발생하였습니다. " << e.what() << endl;
	}
	catch(exception e)
	{
		cout << "알수 없는 오류. " << e.what() << endl;
	}
	
	oGateWaySvc.SetDBSvrConcSocket(&oSock); // 서버 연결 소켓을 설정 한다.
	


	cout << "Gate ServerWay+ 입니다." << endl;
	ReceiveSocket* pRecvSocket = NULL;
	while (true)
	{
		pRecvSocket = new ReceiveSocket();
		pRecvSocket = oServerSock.Accept(); //접속이 들어 오면 Reveive 소켓이 생성 된다. 
		cout << "Gate Server client 가 접속 되었습니다." << endl;
		pRecvSocket->SetIReceiveEvent(&oGateWaySvc);
		pRecvSocket->CreateThread();
		rgpRevcSocket.push_back(pRecvSocket);
	}

	for (unsigned int i = 0; i < rgpRevcSocket.size(); i++)
	{
		WaitForSingleObject(pRecvSocket->m_hThread, INFINITE);
	}

	for (unsigned int i = 0; i < rgpRevcSocket.size(); i++)
	{
		delete rgpRevcSocket[i];
		rgpRevcSocket[i] = NULL;
	}


}