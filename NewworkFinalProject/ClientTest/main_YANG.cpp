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
	ClientSocket oSock("127.0.0.1",9002);
	oSock.InitWinsock();
	oSock.InitSock();
	oSock.Connect();

	_AverageAll pkAverageAll('A','A','A',"Work ID","Work Password ");

	while(true)
	{
		if(0 <  oSock.Send((char*)&pkAverageAll,sizeof(pkAverageAll)))
		{
			oSock.Receive((char*)&pkAverageAll,sizeof(pkAverageAll));
			cout << pkAverageAll.ToString() << endl;
		}

		Sleep(1000);

	}
}