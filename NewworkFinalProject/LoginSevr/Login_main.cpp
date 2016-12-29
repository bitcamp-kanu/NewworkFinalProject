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
void main()
{
	
	ClientSocket oSock(Config::Instance()->m_dbServerIP
					,Config::Instance()->m_nDbServerPort,ClientSocket::eTCP);
	oSock.InitSock();
	oSock.Connect();
	_Login pkLogin('A','B','A',"도봉산아이디","비밀번호입니다");
	

	

	while(true)
	{
		oSock.Send((char*)&pkLogin,sizeof(_Login));
		oSock.Receive((char*)&pkLogin,sizeof(_Login));
		cout << pkLogin.ToString() << " 수신되었습니다."; //
	}


}