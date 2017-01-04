

// TCP_Echo_Server.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
#pragma comment(lib,"Ws2_32.lib") //winsock 2.2 라이브러리
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501

#include <WinSock2.h> //Winsock 2 버전 Header
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
	strHelp.append("HE 도움말	<ex>HE\n");
	strHelp.append("ID 등록		<ex>ID 강백호 01012341234\n");
	strHelp.append("DD 삭제		<ex>DD 강백호\n");
	strHelp.append("SD 검색		<ex>SD 강백호\n");
	strHelp.append("PD 출력		<ex>PD\n");
	strHelp.append("FD 파일전송  <ex>FT Tellinfo_Server.exe\n"); //파일전송
	strHelp.append("EX 종료		<ex>EX\n");
};

CRITICAL_SECTION criticalSection;
//InitializeCriticalSection(&criticalSection); //동기화 객체를 초기화 한다.
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
	cout << "잘못된 요청이 들어왔습니다.." << endl;
	LeaveCriticalSection(&criticalSection);
	Packet pack;			
	pack.SetCmd("MG"); //도움말.
	pack.SetStr("잘못된 요청 입니다.");
	send(sock,(char*)&pack,sizeof(pack),0);
}

void SendNotFormatCmdMessage(SOCKET& sock)
{
	EnterCriticalSection(&criticalSection);
	cout << "명령어 형식이 잘못되었습니다." << endl;
	LeaveCriticalSection(&criticalSection);
	Packet pack;			
	pack.SetCmd("MG"); //도움말.
	pack.SetStr("명령어 형식이 잘못되었습니다.");
	send(sock,(char*)&pack,sizeof(pack),0);
}

void SendSucessMessage(SOCKET& sock)
{
	EnterCriticalSection(&criticalSection);
	cout << "명령이 정상적으로 처리되었습니다." << endl;
	LeaveCriticalSection(&criticalSection);
	Packet pack;			
	pack.SetCmd("MG"); //도움말.
	pack.SetStr("명령이 정상적으로 처리되었습니다.");
	send(sock,(char*)&pack,sizeof(pack),0);
}

void SendMessage(SOCKET& sock , char* msg)
{
	Packet pack;			
	pack.SetCmd("MG"); //도움말.
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
			if(len == SOCKET_ERROR || len == 0) //정상 적이지 않음.
			{
				int error = WSAGetLastError();
				cout << "RecvThreadFun 수신 데이터가 잘못 되었습니다.";
				bExit = true;
				break;
			}
			
			Packet pack;			
			pack.SetDataCopy((Packet*)buffer);
			if(IsCommand(pack.header.chCmd,"HE")) //도움말 요청 이면.. 
			{
				cout << "도움말 정보를 요청 하였습니다." << endl;
				pack.Init();
				pack.SetCmd("HE"); //도움말.
				pack.SetStr(strHelp.c_str());
				send(pData->sockInfo.m_socket,(char*)&pack,sizeof(pack),0);
				
			}
			else if(IsCommand(buffer,"ID")) //신규 등록이면. 
			{
				cout << "신규 등록 요청이 들어왔습니다." << endl;
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
			else if(IsCommand(buffer,"DD")) //삭제이면
			{
				cout << "삭제 요청이 들어왔습니다." << endl;
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
					SendMessage(pData->sockInfo.m_socket,"삭제 되었습니다.");
				}
				else
				{
					SendMessage(pData->sockInfo.m_socket,"삭제 : 일치하는 이름이 없습니다.");
				}
			}
			else if(IsCommand(buffer,"SD")) //검색이면.
			{
				cout << "검색 요청이 들어왔습니다." << endl;
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
					SendMessage(pData->sockInfo.m_socket,"검색 되었습니다.");
				}
				else
				{
					SendMessage(pData->sockInfo.m_socket,"검색 : 일치하는 이름이 없습니다.");
				}
			}
			else if(IsCommand(buffer,"PD")) //등록 목록 요청 이면
			{
				cout << "전체 데이터 요청." << endl;
				pack.Init();
				pack.SetCmd("PD");
				
				vector<Person> vec = pData->pPersonManager->GetAllData();
				for(int i = 0 ; i < vec.size() ; i++)
				{
					pack.SetStr(vec[i].ToString().c_str());
					send(pData->sockInfo.m_socket,(char*)&pack,sizeof(pack),0);
				}				
			}
			else if(IsCommand(buffer,"FD")) //파일전송이면
			{
				cout << "파일 전송을 요청이 들어왔습니다." << endl;
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
					SendMessage(pData->sockInfo.m_socket,"파일전송 : 일치하는 파일이 없습니다.");
				}
				
				int nSendIndex = 0;
				int nRead = 0;
				int size = sizeof(pack.buff);

				//첫번재 명령은 파일명 입니다.
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
					nRead = file.Read(pack.buff,sizeof(char),sizeof(pack.buff)); //파일 전체를 읽는다.					
					pack.nlen = nRead;
					if(nRead == size ) //마지막.. 
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
	InitializeCriticalSection(&criticalSection); //동기화 객체를 초기화 한다.
	
	PersonManager perSonManager;

	InitHelp();
	//접속한 클라이언트 정보를 관리 한다.
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

	cout << "TellInfo Server 입니다." << endl;
	
	_ClientData* pClientData = NULL;
	while(true)
	{
		pClientData = new _ClientData();
		pClientData->pPersonManager = &perSonManager;
		
		cout << "TellInfo Server 접속 대기중 입니다." << endl;
		pClientData->sockInfo = svrSocket.Accept();

		if(pClientData->sockInfo.m_socket == INVALID_SOCKET)
		{
			printf("Accept Error\n");
			return;
		}
		cout << "새로운 Client 가 접속 되었습니다." << endl;
		pClientData->hThread = (HANDLE)_beginthreadex(NULL, 0, &RecvThreadFun, pClientData, 0, &(pClientData->threadID) );
		rgpClients.push_back(pClientData); //접속된 클라이언트를추가 한다/

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
