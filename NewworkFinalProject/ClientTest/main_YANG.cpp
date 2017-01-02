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

	//_AverageAll pkAverageAll('A','A','A',"Work ID","Work Password ");
	_WorkData WorkData('A','A',111,"id001",'A',"class001",101,"¸¶Â¡°¡",'M',"111-222-3333",44,55,66,77,88,0,0.00,"20170102110425");

	while(true)
	{
		if(0 <  oSock.Send((char*)&WorkData,sizeof(_WorkData)))
		{
			oSock.Receive((char*)&WorkData,sizeof(_WorkData));
			cout << WorkData.ToString() << endl;
		}
		getchar();
		Sleep(1000);

	}
}