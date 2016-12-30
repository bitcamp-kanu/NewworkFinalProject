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
	////로그파일 파일명을 설정한다.
	////CLog::Instance()->SetFilePath(Config::Instance()->m_strLogFileName);

	////Recvive 를 저장할 소켓.
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
	//oSock.Connect();//DB 서버에 연결 한다.	

	//oGateSvc.SetDBSvrConcSocket(&oSock); // 서버 연결 소켓을 설정 한다.
	////_Gate pkGate('T', 'E', 'A', "도봉산아이디", "비밀번호입니다");


	//cout << "Gate Server 입니다." << endl;

	//ReceiveSocket* pRecvSocket = NULL;
	//while (true)
	//{
	//	pRecvSocket = new ReceiveSocket();
	//	pRecvSocket = oServerSock.Accept(); //접속이 들어 오면 Reveive 소켓이 생성 된다. 
	//	cout << "Gate Server client 가 접속 되었습니다." << endl;
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