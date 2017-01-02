

// TCP_Echo_Server.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
#pragma comment(lib,"Ws2_32.lib") //winsock 2.2 라이브러리
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501

#include <WinSock2.h> //Winsock 2 버전 Header
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <process.h>

#include "..\Public\ServerSocket.h"
#include "..\Public\Protocol.h"
#include "..\Public\baseSocket.h"
#include "..\Public\WIUtility.h"
#include "..\Public\WIFile.h"
#include "..\Public\Log.h"
#include <time.h>
#include "DBService.h"
#include "Config.h"
#include "DBManager.h"




using namespace std;

void main(int argc, char* argv[])
{
	cout << "--------- DB Server 을 시작 합니다." << endl;
	//DBManager db;
	//db.Open();
	//db.SelectStudent("testid");

	//환경 설정 파일을 불러온다.
	Config::Instance()->LoadConfig();
	//로그파일 파일명을 설정한다.
	CLog::Instance()->SetFilePath(Config::Instance()->m_strLogFileName);


	DBService oDbServcie;
	ServerSocket svrSocket;
	
	vector<ReceiveSocket*> rgpRevcSocket; 

	//char buffer[_BUFF_SIZE_];

	
	
	svrSocket.SetPort(Config::Instance()->m_nServerPort);
	svrSocket.InitWinsock();
	svrSocket.InitSock();
	svrSocket.Bind();
	svrSocket.Listen(Config::Instance()->m_nListenCnt);

	cout << "DB Server 입니다." << endl;
	
	ReceiveSocket* pRecvSocket = NULL;
	while(true)
	{
		pRecvSocket = new ReceiveSocket();		
		pRecvSocket= svrSocket.Accept(); //접속이 들어 오면 Reveive 소켓이 생성 된다. 
		cout <<"DB Server client 가 접속 되었습니다." << endl;
		pRecvSocket->SetIReceiveEvent(&oDbServcie);
		pRecvSocket ->CreateThread();
		rgpRevcSocket.push_back(pRecvSocket);
	}	

	for(int i = 0 ; i < rgpRevcSocket.size(); i++)
	{
		WaitForSingleObject(pRecvSocket ->m_hThread,INFINITE);
	}

	for(int i = 0 ; i < rgpRevcSocket.size(); i++)
	{
		delete rgpRevcSocket[i];
		rgpRevcSocket[i] = NULL;
	}
	return;
}
