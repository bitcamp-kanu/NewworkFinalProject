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

	_Login pkLogin('T','L','A',"�α��μ���","��й�ȣ�Դϴ�");
	switch(num)
	{
		case 0:
			port = 9000;
			pkLogin.header.cmd2 = 'L';
			cout << "-----Clinet: Login ������ ���� �մϴ�.";
			break;
		case 1:
			port = 9001;
			pkLogin.header.cmd2 = 'G';
			cout << "-----Clinet: GateWayServer�� ���� �մϴ�.";
			break;
		case 2:
			port = 9002;
			pkLogin.header.cmd2 = 'W';
			cout << "-----Clinet: GateWayServer �� ���� �մϴ�.";
			break;
	}
	
	//port = 9000; //�α��� ����.

	//string str = WIUtility::GetFormatString("%s %d ��", "�α��� ����",1);
	//ClientSocket oSockLogin("127.0.0.1",port);		//�α��� ����.
	//try
	//{
	//	//ClientSocket oSockLogin("127.0.0.1",9000);		//�α��� ����.
	//	oSockLogin.InitWinsock();
	//	oSockLogin.InitSock();
	//	oSockLogin.Connect();
	//}
	//catch (exceptionCS e)
	//{
	//	cout << e.what() << endl;
	//	
	//}	

	ClientSocket oSockGate("127.0.0.1",9001);		//GateWay ����.
	oSockGate.InitWinsock();
	oSockGate.InitSock();
	oSockGate.Connect();

	//char cmd1, char cmd2, int pakID, char* id, char SecretKey, char* ClassId, int ClassNum, char* SName, char SSex, char* STelNo, int C, int CPP, int CSharp, int Network, int Unity, int Total, float Avg
	_SearchStudent _SearchStudent('S', 'G', 0, "", '1', "class001", 1, "�л�1", '1', "", 0, 0, 0, 0, 0, 0, 0.0);

	//TL �α��� ����
	//TG GateServer ����
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