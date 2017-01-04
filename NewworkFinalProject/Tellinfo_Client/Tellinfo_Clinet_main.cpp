// TCP_Echo_Server.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//
#pragma comment(lib,"Ws2_32.lib")
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501

#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <process.h>
#include "..\header\Protocol.h"
#include "..\header\WIFile.h"


using namespace std;

int PORT = 9000;
char IP[20] = "127.0.0.1"; //Loop Address

CRITICAL_SECTION criticalSection;
//InitializeCriticalSection(&criticalSection); //동기화 객체를 초기화 한다.
//DeleteCriticalSection(&criticalSection);
//EnterCriticalSection(&criticalSection);
//LeaveCriticalSection(&criticalSection);


struct _ClientData
{
	SOCKET socket;
	HANDLE hThread;
	unsigned threadID;	
};

bool IsCommand(char* buffer , char* cmd)
{
	return ((buffer[0] == cmd[0])&&(buffer[1] == cmd[1]));
}
unsigned __stdcall RecvThreadFun( void* pArguments )
{
	_ClientData* pData =(_ClientData*)pArguments;
	int len = 0;
	bool bExit = false;
	char buffer[_BUFF_SIZE_];
	memset(buffer,0x00,sizeof(buffer));

	if(pData != NULL)
	{
		Packet pack;
		while(!bExit)
		{
			memset(&pack,0x00,sizeof(Packet));
			memset(buffer,0x00,sizeof(buffer));
			len = recv(pData->socket,buffer,sizeof(buffer),0);
			
			pack.SetDataCopy((Packet*)buffer);
			if(len == SOCKET_ERROR || len == 0) //정상 적이지 않음.
			{
				bExit = true;
				LeaveCriticalSection(&criticalSection);
			}
			else if(IsCommand(pack.header.chCmd,"FD")) //파일전송 이면.
			{
				WIFile file;
				bool bFirst = true;
				while(true)
				{
					if(!bFirst)
					{
						len = recv(pData->socket,buffer,sizeof(buffer),0);
						cout << "데이터를 수신중 입니다." << endl;
						pack.SetDataCopy((Packet*)buffer);
					}
					bFirst = false;
				
					if(pack.header.nCmdIndex == 0) //첫번째 파일 인자는 파일명
					{
						if(!file.Open(string(pack.buff),"wb"))
						{
							cout << "파일열기에 실패하였습니다." << pack.buff << endl;
						}
						cout << "파일을 생성합니다. " << pack.buff << endl;
					}
					else
					{
						file.Write(pack.buff,sizeof(char),pack.nlen);
					}

					if(pack.header.nCmdIndex == pack.header.nCmdSize)
					{
						file.Close();
						cout << "수신이 완료 되었습니다.." << endl;
						break;
					}
				}
			}
			else
			{
				EnterCriticalSection(&criticalSection);
				cout << pack.buff<< endl;
				LeaveCriticalSection(&criticalSection);
			}
		}
	}
	return 0;

}
void main(int argc, char* argv[])
{
	InitializeCriticalSection(&criticalSection); //동기화 객체를 초기화 한다.
	_ClientData thData;
	SOCKADDR_IN clientAddress; //접속할 서버의 주소 정보를 저장할 구조체.
	SOCKET		clientSocket;	//클라이언트 소켓
	WSADATA		wsadata;
	char		ch;
	char		recvBuffer[_BUFF_SIZE_];
	char		cmdBuffer[_BUFF_SIZE_];
	
	int			len = 0;

	if(argc == 3)
	{
		strcpy(IP,argv[1]);		// 외부에서 IP , PORT 설정.
		PORT = atoi(argv[2]);
	}

	if(WSAStartup(MAKEWORD(2,2),&wsadata) != 0)
	{
		printf("WSAStartUp Error\n");
		return;
	}

	clientSocket = socket(AF_INET,SOCK_STREAM,0); //AF_INET(IPV4), SOCK_STREAM(TCP)
	ZeroMemory(&clientAddress,sizeof(clientAddress));
	clientAddress.sin_port = htons(PORT);	
	clientAddress.sin_addr.s_addr = inet_addr(IP);
	clientAddress.sin_family = AF_INET;

	//설정된 서버 주소로 접속 요청.
	len = connect(clientSocket,(SOCKADDR*)(&clientAddress),sizeof(clientAddress));
	if(len != 0) //정상 적이지 않음.
	{
		cout << "fail connect errorcode => " << len << endl;
		return;
	}

	//Receive Thread 를 생성 한다.
	thData.hThread = (HANDLE)_beginthreadex(NULL, 0, &RecvThreadFun, &thData, 0, &(thData.threadID) );
	thData.socket = clientSocket;

	memset(&recvBuffer,0x00,sizeof(recvBuffer));
	int offset = 0;	
	while(true)
	{
		EnterCriticalSection(&criticalSection);
		cout << "명령어를 입력하세요 도움말 HE"<< endl;
		LeaveCriticalSection(&criticalSection);
		memset(cmdBuffer,0x00,sizeof(cmdBuffer));
		cin.getline(cmdBuffer,_BUFF_SIZE_);
		if(strlen(cmdBuffer) > 0 )
		{			
			Packet pack;
			pack.Init();
			pack.SetCmd(cmdBuffer);
			pack.SetStr(cmdBuffer); //CMD 를 포함한 전체 데이터를 보낸다.
			pack.nlen = strlen(cmdBuffer);
			int len = send(clientSocket,(char*)&pack,sizeof(pack),0);
		}
		fflush(stdin);
	}
	closesocket(clientSocket);
	cout << "프로그램을 종료합니다.." << endl;
	clientSocket = NULL;
	WSACleanup(); //소켓 초기화를 해제한다.

	DeleteCriticalSection(&criticalSection);
	system("pause");

}