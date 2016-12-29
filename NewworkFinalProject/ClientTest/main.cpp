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

void main()
{
	ClientSocket oSock("127.0.0.1",9000);
	oSock.InitWinsock();
	oSock.InitSock();
	oSock.Connect();

	_Login pkLogin('T','E','A',"도봉산아이디","비밀번호입니다");
	while(true)
	{
		if(0 <  oSock.Send((char*)&pkLogin,sizeof(pkLogin)))
		{
			oSock.Receive((char*)&pkLogin,sizeof(pkLogin));
			cout << pkLogin.ToString() << endl;
		}

		Sleep(1000);
		
	}
}