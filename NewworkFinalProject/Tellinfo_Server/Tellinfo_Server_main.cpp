

// TCP_Echo_Server.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
#pragma comment(lib,"Ws2_32.lib") //winsock 2.2 ���̺귯��
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501

#include <WinSock2.h> //Winsock 2 ���� Header
#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>
#include <process.h>


#include "ServerSocket.h"
#include "PersonManager.h"
#include "..\header\Protocol.h"
#include "..\header\baseSocket.h"
#include "..\header\WIUtility.h"
#include "..\header\WIFile.h"




using namespace std;

int PORT = 9000;

struct _ClientData
{
	SockInfo sockInfo;	
	HANDLE hThread;
	unsigned threadID;	
	PersonManager* pPersonManager;
};

string strHelp;

void InitHelp()
{
	strHelp.append("HE ����	<ex>HE\n");
	strHelp.append("ID ���		<ex>ID ����ȣ 01012341234\n");
	strHelp.append("DD ����		<ex>DD ����ȣ\n");
	strHelp.append("SD �˻�		<ex>SD ����ȣ\n");
	strHelp.append("PD ���		<ex>PD\n");
	strHelp.append("FD ��������  <ex>FT Tellinfo_Server.exe\n"); //��������
	strHelp.append("EX ����		<ex>EX\n");
};

CRITICAL_SECTION criticalSection;
//InitializeCriticalSection(&criticalSection); //����ȭ ��ü�� �ʱ�ȭ �Ѵ�.
//DeleteCriticalSection(&criticalSection);
//EnterCriticalSection(&criticalSection);
//LeaveCriticalSection(&criticalSection);

bool IsCommand(char* buffer , char* cmd)
{
	return ((buffer[0] == cmd[0])&&(buffer[1] == cmd[1]));
}

void SendUnKnownCmdMessage(SOCKET& sock)
{

	EnterCriticalSection(&criticalSection);
	cout << "�߸��� ��û�� ���Խ��ϴ�.." << endl;
	LeaveCriticalSection(&criticalSection);
	Packet pack;			
	pack.SetCmd("MG"); //����.
	pack.SetStr("�߸��� ��û �Դϴ�.");
	send(sock,(char*)&pack,sizeof(pack),0);
}

void SendNotFormatCmdMessage(SOCKET& sock)
{
	EnterCriticalSection(&criticalSection);
	cout << "��ɾ� ������ �߸��Ǿ����ϴ�." << endl;
	LeaveCriticalSection(&criticalSection);
	Packet pack;			
	pack.SetCmd("MG"); //����.
	pack.SetStr("��ɾ� ������ �߸��Ǿ����ϴ�.");
	send(sock,(char*)&pack,sizeof(pack),0);
}

void SendSucessMessage(SOCKET& sock)
{
	EnterCriticalSection(&criticalSection);
	cout << "����� ���������� ó���Ǿ����ϴ�." << endl;
	LeaveCriticalSection(&criticalSection);
	Packet pack;			
	pack.SetCmd("MG"); //����.
	pack.SetStr("����� ���������� ó���Ǿ����ϴ�.");
	send(sock,(char*)&pack,sizeof(pack),0);
}

void SendMessage(SOCKET& sock , char* msg)
{
	Packet pack;			
	pack.SetCmd("MG"); //����.
	pack.SetStr(msg);
	send(sock,(char*)&pack,sizeof(pack),0);
}



unsigned __stdcall RecvThreadFun( void* pArguments )
{
	_ClientData* pData = (_ClientData*)pArguments ;
	char buffer[_BUFF_SIZE_] = {0};
	int len = 0;
	bool bExit = false;
	if(pData != NULL)
	{
		while(!bExit)
		{
			memset(buffer,0x00,sizeof(buffer));
			len = recv(pData->sockInfo.m_socket,buffer,sizeof(buffer),0);
			if(len == SOCKET_ERROR || len == 0) //���� ������ ����.
			{
				int error = WSAGetLastError();
				cout << "RecvThreadFun ���� �����Ͱ� �߸� �Ǿ����ϴ�.";
				bExit = true;
				break;
			}
			
			Packet pack;			
			pack.SetDataCopy((Packet*)buffer);
			if(IsCommand(pack.header.chCmd,"HE")) //���� ��û �̸�.. 
			{
				cout << "���� ������ ��û �Ͽ����ϴ�." << endl;
				pack.Init();
				pack.SetCmd("HE"); //����.
				pack.SetStr(strHelp.c_str());
				send(pData->sockInfo.m_socket,(char*)&pack,sizeof(pack),0);
				
			}
			else if(IsCommand(buffer,"ID")) //�ű� ����̸�. 
			{
				cout << "�ű� ��� ��û�� ���Խ��ϴ�." << endl;
				string cmdStr(pack.buff);
				vector<string> vec = WIUtility::Tokenize(cmdStr," ");
				if(vec.size() != 3)
				{
					SendNotFormatCmdMessage(pData->sockInfo.m_socket);
					continue;;
				}
				pData->pPersonManager->InsertTelInfo(Person(vec[1],vec[2]));
				SendSucessMessage(pData->sockInfo.m_socket);

			}
			else if(IsCommand(buffer,"DD")) //�����̸�
			{
				cout << "���� ��û�� ���Խ��ϴ�." << endl;
				string cmdStr(pack.buff);
				vector<string> vecCmd = WIUtility::Tokenize(cmdStr," ");
				if(vecCmd.size() != 2)
				{
					SendNotFormatCmdMessage(pData->sockInfo.m_socket);
					continue;;
				}
				vector<Person> vec = pData->pPersonManager->DeleteTelInfo(vecCmd[1]);
				if(vec.size() > 0)
				{
					for(int i = 0 ; i < vec.size() ; i++)
					{
						pack.SetStr(vec[i].ToString().c_str());
						send(pData->sockInfo.m_socket,(char*)&pack,sizeof(pack),0);
					}
					SendMessage(pData->sockInfo.m_socket,"���� �Ǿ����ϴ�.");
				}
				else
				{
					SendMessage(pData->sockInfo.m_socket,"���� : ��ġ�ϴ� �̸��� �����ϴ�.");
				}
			}
			else if(IsCommand(buffer,"SD")) //�˻��̸�.
			{
				cout << "�˻� ��û�� ���Խ��ϴ�." << endl;
				string cmdStr(pack.buff);
				vector<string> vecCmd = WIUtility::Tokenize(cmdStr," ");
				if(vecCmd.size() != 2)
				{
					SendNotFormatCmdMessage(pData->sockInfo.m_socket);
					continue;;
				}
				vector<Person> vec = pData->pPersonManager->SearchTelInfo(vecCmd[1]);
				if(vec.size() > 0)
				{
					for(int i = 0 ; i < vec.size() ; i++)
					{
						pack.SetStr(vec[i].ToString().c_str());
						send(pData->sockInfo.m_socket,(char*)&pack,sizeof(pack),0);
					}
					SendMessage(pData->sockInfo.m_socket,"�˻� �Ǿ����ϴ�.");
				}
				else
				{
					SendMessage(pData->sockInfo.m_socket,"�˻� : ��ġ�ϴ� �̸��� �����ϴ�.");
				}
			}
			else if(IsCommand(buffer,"PD")) //��� ��� ��û �̸�
			{
				cout << "��ü ������ ��û." << endl;
				pack.Init();
				pack.SetCmd("PD");
				
				vector<Person> vec = pData->pPersonManager->GetAllData();
				for(int i = 0 ; i < vec.size() ; i++)
				{
					pack.SetStr(vec[i].ToString().c_str());
					send(pData->sockInfo.m_socket,(char*)&pack,sizeof(pack),0);
				}				
			}
			else if(IsCommand(buffer,"FD")) //���������̸�
			{
				cout << "���� ������ ��û�� ���Խ��ϴ�." << endl;
				string cmdStr(pack.buff);
				vector<string> vecCmd = WIUtility::Tokenize(cmdStr," ");
				if(vecCmd.size() != 2)
				{
					SendNotFormatCmdMessage(pData->sockInfo.m_socket);
					continue;;
				}
				WIFile file;
				if(!file.Open(vecCmd[1],"rb"))
				{
					SendMessage(pData->sockInfo.m_socket,"�������� : ��ġ�ϴ� ������ �����ϴ�.");
				}
				
				int nSendIndex = 0;
				int nRead = 0;
				int size = sizeof(pack.buff);

				//ù���� ����� ���ϸ� �Դϴ�.
				pack.Init();
				pack.header.nCmdIndex = nSendIndex++;
				pack.header.nCmdSize = 99;
				pack.SetCmd("FD");
				pack.SetStr(vecCmd[1].c_str());  
				send(pData->sockInfo.m_socket,(char*)&pack,sizeof(pack),0);

				while(!file.IsEOF())
				{
					Sleep(100);
					pack.Init();
					pack.SetCmd("FD");
					nRead = file.Read(pack.buff,sizeof(char),sizeof(pack.buff)); //���� ��ü�� �д´�.					
					pack.nlen = nRead;
					if(nRead == size ) //������.. 
					{
						pack.header.nCmdIndex = nSendIndex++;
						pack.header.nCmdSize = 99;
					}
					else
					{
						pack.header.nCmdIndex = nSendIndex;
						pack.header.nCmdSize = nSendIndex;
					}
					send(pData->sockInfo.m_socket,(char*)&pack,sizeof(pack),0);
					if(pack.header.nCmdIndex == pack.header.nCmdSize)
					{
						break;
					}	
				}
			}
			else
			{
				SendUnKnownCmdMessage(pData->sockInfo.m_socket);
			}
			
		}
	}
	_endthreadex(0);

	return 0;
}

void main(int argc, char* argv[])
{
	InitializeCriticalSection(&criticalSection); //����ȭ ��ü�� �ʱ�ȭ �Ѵ�.
	
	PersonManager perSonManager;

	InitHelp();
	//������ Ŭ���̾�Ʈ ������ ���� �Ѵ�.
	vector<_ClientData*> rgpClients; 
	char buffer[_BUFF_SIZE_];

	ServerSocket svrSocket;
	
	svrSocket.InitWinsock();

	if(argc == 2)
	{
		svrSocket.SetPort(atoi(argv[1]));
	}

	svrSocket.InitSock();
	svrSocket.Bind();
	svrSocket.Listen(5);

	cout << "TellInfo Server �Դϴ�." << endl;
	
	_ClientData* pClientData = NULL;
	while(true)
	{
		pClientData = new _ClientData();
		pClientData->pPersonManager = &perSonManager;
		
		cout << "TellInfo Server ���� ����� �Դϴ�." << endl;
		pClientData->sockInfo = svrSocket.Accept();

		if(pClientData->sockInfo.m_socket == INVALID_SOCKET)
		{
			printf("Accept Error\n");
			return;
		}
		cout << "���ο� Client �� ���� �Ǿ����ϴ�." << endl;
		pClientData->hThread = (HANDLE)_beginthreadex(NULL, 0, &RecvThreadFun, pClientData, 0, &(pClientData->threadID) );
		rgpClients.push_back(pClientData); //���ӵ� Ŭ���̾�Ʈ���߰� �Ѵ�/

	}

	for(int i = 0 ; i < rgpClients.size(); i++)
	{
		rgpClients[i]->sockInfo.Release();
		delete rgpClients[i];
		rgpClients[i] = NULL;
	}
	DeleteCriticalSection(&criticalSection);
	return;
}
