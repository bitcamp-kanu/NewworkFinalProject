// TCP_Echo_Server.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
//InitializeCriticalSection(&criticalSection); //����ȭ ��ü�� �ʱ�ȭ �Ѵ�.
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
			if(len == SOCKET_ERROR || len == 0) //���� ������ ����.
			{
				bExit = true;
				LeaveCriticalSection(&criticalSection);
			}
			else if(IsCommand(pack.header.chCmd,"FD")) //�������� �̸�.
			{
				WIFile file;
				bool bFirst = true;
				while(true)
				{
					if(!bFirst)
					{
						len = recv(pData->socket,buffer,sizeof(buffer),0);
						cout << "�����͸� ������ �Դϴ�." << endl;
						pack.SetDataCopy((Packet*)buffer);
					}
					bFirst = false;
				
					if(pack.header.nCmdIndex == 0) //ù��° ���� ���ڴ� ���ϸ�
					{
						if(!file.Open(string(pack.buff),"wb"))
						{
							cout << "���Ͽ��⿡ �����Ͽ����ϴ�." << pack.buff << endl;
						}
						cout << "������ �����մϴ�. " << pack.buff << endl;
					}
					else
					{
						file.Write(pack.buff,sizeof(char),pack.nlen);
					}

					if(pack.header.nCmdIndex == pack.header.nCmdSize)
					{
						file.Close();
						cout << "������ �Ϸ� �Ǿ����ϴ�.." << endl;
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
	InitializeCriticalSection(&criticalSection); //����ȭ ��ü�� �ʱ�ȭ �Ѵ�.
	_ClientData thData;
	SOCKADDR_IN clientAddress; //������ ������ �ּ� ������ ������ ����ü.
	SOCKET		clientSocket;	//Ŭ���̾�Ʈ ����
	WSADATA		wsadata;
	char		ch;
	char		recvBuffer[_BUFF_SIZE_];
	char		cmdBuffer[_BUFF_SIZE_];
	
	int			len = 0;

	if(argc == 3)
	{
		strcpy(IP,argv[1]);		// �ܺο��� IP , PORT ����.
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

	//������ ���� �ּҷ� ���� ��û.
	len = connect(clientSocket,(SOCKADDR*)(&clientAddress),sizeof(clientAddress));
	if(len != 0) //���� ������ ����.
	{
		cout << "fail connect errorcode => " << len << endl;
		return;
	}

	//Receive Thread �� ���� �Ѵ�.
	thData.hThread = (HANDLE)_beginthreadex(NULL, 0, &RecvThreadFun, &thData, 0, &(thData.threadID) );
	thData.socket = clientSocket;

	memset(&recvBuffer,0x00,sizeof(recvBuffer));
	int offset = 0;	
	while(true)
	{
		EnterCriticalSection(&criticalSection);
		cout << "��ɾ �Է��ϼ��� ���� HE"<< endl;
		LeaveCriticalSection(&criticalSection);
		memset(cmdBuffer,0x00,sizeof(cmdBuffer));
		cin.getline(cmdBuffer,_BUFF_SIZE_);
		if(strlen(cmdBuffer) > 0 )
		{			
			Packet pack;
			pack.Init();
			pack.SetCmd(cmdBuffer);
			pack.SetStr(cmdBuffer); //CMD �� ������ ��ü �����͸� ������.
			pack.nlen = strlen(cmdBuffer);
			int len = send(clientSocket,(char*)&pack,sizeof(pack),0);
		}
		fflush(stdin);
	}
	closesocket(clientSocket);
	cout << "���α׷��� �����մϴ�.." << endl;
	clientSocket = NULL;
	WSACleanup(); //���� �ʱ�ȭ�� �����Ѵ�.

	DeleteCriticalSection(&criticalSection);
	system("pause");

}