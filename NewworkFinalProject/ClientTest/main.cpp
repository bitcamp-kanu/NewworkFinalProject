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
	if(rand()%2 == 1)
	{
		port = 9000;
	}
	else
	{
		port = 9001;
	}
	port = 9001;
	//string str = WIUtility::GetFormatString("%s %d ��", "�α��� ����",1);
	ClientSocket oSockLogin("127.0.0.1",port);		//�α��� ����.
	//ClientSocket oSockLogin("127.0.0.1",9000);		//�α��� ����.
	oSockLogin.InitWinsock();
	oSockLogin.InitSock();
	oSockLogin.Connect();

	//ClientSocket oSockGate("127.0.0.1",9001);		//GateWay ����.
	//oSockGate.InitWinsock();
	//oSockGate.InitSock();
	//oSockGate.Connect();

	_Login pkLogin('A','L','A',"�α��μ���","��й�ȣ�Դϴ�");
	//if(port == 9001)
	//{
	//	pkLogin.header.cmd2 = '2';
	//}
	while(true)
	{
		if(0 <  oSockLogin.Send((char*)&pkLogin,sizeof(pkLogin)))
		{
			oSockLogin.Receive((char*)&pkLogin,sizeof(pkLogin));
			cout << pkLogin.ToString() << endl;
		}
		Sleep(500);	
	}
}