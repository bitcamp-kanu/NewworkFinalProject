#pragma comment(lib,"Ws2_32.lib")
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <process.h>
#include <iostream>
#include "..\Public\ClientSocket.h"
#include "..\Public\PublicDefine.h"
#include "..\public\ServerSocket.h"
#include "..\public\WIUtility.h"


void main()
{
	int port = 9000;
	srand((unsigned int)time(NULL));
	int num = rand()%3 ;
	num = 1;

	_Login pkLogin('T','L','A',"로그인서버","비밀번호입니다");
	switch(num)
	{
		case 0:
			port = 9000;
			pkLogin.header.cmd2 = 'L';
			cout << "-----Clinet: Login 서버로 접속 합니다.";
			break;
		case 1:
			port = 9001;
			pkLogin.header.cmd2 = 'G';
			cout << "-----Clinet: GateWayServer로 접속 합니다.";
			break;
		case 2:
			port = 9002;
			pkLogin.header.cmd2 = 'W';
			cout << "-----Clinet: GateWayServer 로 접속 합니다.";
			break;
	}
	
	//port = 9000; //로그인 서버.

	//string str = WIUtility::GetFormatString("%s %d 등", "로그인 서버",1);
	//ClientSocket oSockLogin("127.0.0.1",port);		//로그인 서버.
	//try
	//{
	//	//ClientSocket oSockLogin("127.0.0.1",9000);		//로그인 서버.
	//	oSockLogin.InitWinsock();
	//	oSockLogin.InitSock();
	//	oSockLogin.Connect();
	//}
	//catch (exceptionCS e)
	//{
	//	cout << e.what() << endl;
	//	
	//}	

	ClientSocket oSockGate("127.0.0.1",9001);		//GateWay 서버.
	oSockGate.InitWinsock();
	oSockGate.InitSock();
	oSockGate.Connect();

	//char cmd1, char cmd2, int pakID, char* id, char SecretKey, char* ClassId, int ClassNum, char* SName, char SSex, char* STelNo, int C, int CPP, int CSharp, int Network, int Unity, int Total, float Avg
	_SearchStudent _SearchStudent('S', 'G', 0, "", '1', "class001", 1, "학생1", '1', "", 0, 0, 0, 0, 0, 0, 0.0);

	//TL 로그인 서버
	//TG GateServer 서서
	//TW WorkServer

	while(true)
	{
		if(0 <  oSockGate.Send((char*)&_SearchStudent,sizeof(_SearchStudent)))
		{
			cout << 
				oSockGate.Receive((char*)&_SearchStudent,sizeof(_SearchStudent));
		}
		Sleep(500);	
	}
}