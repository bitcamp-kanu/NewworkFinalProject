

// TCP_Echo_Server.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
#pragma comment(lib,"Ws2_32.lib") //winsock 2.2 ���̺귯��
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501

#include <WinSock2.h> //Winsock 2 ���� Header
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
	cout << "--------- DB Server �� ���� �մϴ�." << endl;
	//DBManager db;
	//db.Open();
	//db.SelectStudent("testid");

	//ȯ�� ���� ������ �ҷ��´�.
	Config::Instance()->LoadConfig();
	//�α����� ���ϸ��� �����Ѵ�.
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

	cout << "DB Server �Դϴ�." << endl;
	
	ReceiveSocket* pRecvSocket = NULL;
	while(true)
	{
		pRecvSocket = new ReceiveSocket();		
		pRecvSocket= svrSocket.Accept(); //������ ��� ���� Reveive ������ ���� �ȴ�. 
		cout <<"DB Server client �� ���� �Ǿ����ϴ�." << endl;
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
