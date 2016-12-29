

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

#include "..\Public\ServerSocket.h"
#include "..\Public\Protocol.h"
#include "..\Public\baseSocket.h"
#include "..\Public\WIUtility.h"
#include "..\Public\WIFile.h"
#include "..\Public\Log.h"
#include <time.h>
#include "DBService.h"
#include "Config.h"




using namespace std;

int PORT = 9000;
string strHelp;


bool Encode(char* buff,int len , char key)
{
	for(int i = 0; i < len ; i++)
	{
		*(buff+i)  ^= key;
	}
	return true;
}

bool Decode(char* buff,int len,char key)
{
	for(int i = 0; i < len ; i++)
	{
		*(buff+i)  ^= key;
	}
	return true;
}

void InitHelp()
{
	//strHelp.append("HE 도움말	<ex>HE\n");
};

CRITICAL_SECTION criticalSection;
bool IsCommand(char* buffer , char* cmd)
{
	return ((buffer[0] == cmd[0])&&(buffer[1] == cmd[1]));
}
char CreateKey()
{
	srand( (unsigned)time( NULL ) );
	char ch = rand()%127 ;
	return ch;
}
void SendUnKnownCmdMessage(SOCKET& sock , char key)
{

	EnterCriticalSection(&criticalSection);
	cout << "잘못된 요청이 들어왔습니다.." << endl;
	LeaveCriticalSection(&criticalSection);
	Packet pack;			
	pack.SetCmd("MG"); //도움말.
	pack.SetStr("잘못된 요청 입니다.");
	Encode((char*)&pack,sizeof(Packet),key);
	send(sock,(char*)&pack,sizeof(pack),0);
}
void SendNotFormatCmdMessage(SOCKET& sock, char key)
{
	EnterCriticalSection(&criticalSection);
	cout << "명령어 형식이 잘못되었습니다." << endl;
	LeaveCriticalSection(&criticalSection);
	Packet pack;			
	pack.SetCmd("MG"); //도움말.
	pack.SetStr("명령어 형식이 잘못되었습니다.");
	
	Encode((char*)&pack,sizeof(Packet),key);
	send(sock,(char*)&pack,sizeof(pack),0);
}
void SendSucessMessage(SOCKET& sock, char key)
{
	EnterCriticalSection(&criticalSection);
	cout << "명령이 정상적으로 처리되었습니다." << endl;
	LeaveCriticalSection(&criticalSection);
	Packet pack;			
	pack.SetCmd("MG"); //도움말.
	pack.SetStr("명령이 정상적으로 처리되었습니다.");
	Encode((char*)&pack,sizeof(Packet),key);
	send(sock,(char*)&pack,sizeof(pack),0);
}
void SendMessage(SOCKET& sock , char* msg, char key)
{
	Packet pack;			
	pack.SetCmd("MG"); //도움말.
	pack.SetStr(msg);
	Encode((char*)&pack,sizeof(Packet),key);
	send(sock,(char*)&pack,sizeof(pack),0);
}
unsigned __stdcall RecvThreadFun( void* pArguments )
{
	//_ClientData* pData = (_ClientData*)pArguments ;
	//char buffer[_BUFF_SIZE_] = {0};
	//int len = 0;
	//bool bExit = false;
	//if(pData != NULL)
	//{
	//	while(!bExit)
	//	{
	//		memset(buffer,0x00,sizeof(buffer));
	//		len = recv(pData->sockInfo.m_socket,buffer,sizeof(buffer),0);

	//		if(len == SOCKET_ERROR || len == 0) //정상 적이지 않음.
	//		{
	//			int error = WSAGetLastError();
	//			cout << "RecvThreadFun 수신 데이터가 잘못 되었습니다.";
	//			bExit = true;
	//			break;
	//		}
	//		
	//		Packet pack;			
	//		pack.SetDataCopy((Packet*)buffer);
	//		Decode((char*)&pack,sizeof(Packet),pData->key);

	//		if(IsCommand(pack.header.chCmd,"HE")) //도움말 요청 이면.. 
	//		{
	//			cout << "도움말 정보를 요청 하였습니다." << endl;
	//			pack.Init();
	//			pack.SetCmd("HE"); //도움말.
	//			pack.SetStr(strHelp.c_str());
	//			Encode((char*)&pack,sizeof(pack),pData->key);
	//			send(pData->sockInfo.m_socket,(char*)&pack,sizeof(pack),0);
	//			
	//		}
	//		else if(IsCommand(pack.header.chCmd,"ID")) //신규 등록이면. 
	//		{
	//			cout << "신규 등록 요청이 들어왔습니다." << endl;
	//			string cmdStr(pack.buff);
	//			vector<string> vec = WIUtility::Tokenize(cmdStr," ");
	//			if(vec.size() != 3)
	//			{
	//				SendNotFormatCmdMessage(pData->sockInfo.m_socket,pData->key);
	//				continue;;
	//			}
	//			pData->pPersonManager->InsertTelInfo(Person(vec[1],vec[2]));
	//			SendSucessMessage(pData->sockInfo.m_socket,pData->key);

	//		}
	//		else if(IsCommand(pack.header.chCmd,"DD")) //삭제이면
	//		{
	//			cout << "삭제 요청이 들어왔습니다." << endl;
	//			string cmdStr(pack.buff);
	//			vector<string> vecCmd = WIUtility::Tokenize(cmdStr," ");
	//			if(vecCmd.size() != 2)
	//			{
	//				SendNotFormatCmdMessage(pData->sockInfo.m_socket,pData->key);
	//				continue;;
	//			}
	//			vector<Person> vec = pData->pPersonManager->DeleteTelInfo(vecCmd[1]);
	//			if(vec.size() > 0)
	//			{
	//				for(int i = 0 ; i < vec.size() ; i++)
	//				{
	//					pack.SetStr(vec[i].ToString().c_str());
	//					Encode((char*)&pack,sizeof(pack),pData->key);
	//					send(pData->sockInfo.m_socket,(char*)&pack,sizeof(pack),0);
	//				}
	//				SendMessage(pData->sockInfo.m_socket,"삭제 되었습니다.",pData->key);
	//			}
	//			else
	//			{
	//				SendMessage(pData->sockInfo.m_socket,"삭제 : 일치하는 이름이 없습니다.",pData->key);
	//			}
	//		}
	//		else if(IsCommand(pack.header.chCmd,"SD")) //검색이면.
	//		{
	//			cout << "검색 요청이 들어왔습니다." << endl;
	//			string cmdStr(pack.buff);
	//			vector<string> vecCmd = WIUtility::Tokenize(cmdStr," ");
	//			if(vecCmd.size() != 2)
	//			{
	//				SendNotFormatCmdMessage(pData->sockInfo.m_socket,pData->key);
	//				continue;;
	//			}
	//			vector<Person> vec = pData->pPersonManager->SearchTelInfo(vecCmd[1]);
	//			if(vec.size() > 0)
	//			{
	//				for(int i = 0 ; i < vec.size() ; i++)
	//				{
	//					pack.SetStr(vec[i].ToString().c_str());
	//					Encode((char*)&pack,sizeof(pack),pData->key);
	//					send(pData->sockInfo.m_socket,(char*)&pack,sizeof(pack),0);
	//				}
	//				SendMessage(pData->sockInfo.m_socket,"검색 되었습니다.",pData->key);
	//			}
	//			else
	//			{
	//				SendMessage(pData->sockInfo.m_socket,"검색 : 일치하는 이름이 없습니다.",pData->key);
	//			}
	//		}
	//		else if(IsCommand(pack.header.chCmd,"PD")) //등록 목록 요청 이면
	//		{
	//			cout << "전체 데이터 요청." << endl;
	//			pack.Init();
	//			pack.SetCmd("PD");
	//			
	//			vector<Person> vec = pData->pPersonManager->GetAllData();
	//			for(int i = 0 ; i < vec.size() ; i++)
	//			{
	//				pack.SetStr(vec[i].ToString().c_str());
	//				Encode((char*)&pack,sizeof(pack),pData->key);
	//				send(pData->sockInfo.m_socket,(char*)&pack,sizeof(pack),0);
	//			}				
	//		}
	//		else if(IsCommand(pack.header.chCmd,"FD")) //파일전송이면
	//		{
	//			cout << "파일 전송을 요청이 들어왔습니다." << endl;
	//			string cmdStr(pack.buff);
	//			vector<string> vecCmd = WIUtility::Tokenize(cmdStr," ");
	//			if(vecCmd.size() != 2)
	//			{
	//				SendNotFormatCmdMessage(pData->sockInfo.m_socket,pData->key);
	//				continue;;
	//			}
	//			WIFile file;
	//			if(!file.Open(vecCmd[1],"rb"))
	//			{
	//				SendMessage(pData->sockInfo.m_socket,"파일전송 : 일치하는 파일이 없습니다.",pData->key);
	//			}
	//			
	//			int nSendIndex = 0;
	//			int nRead = 0;
	//			int size = sizeof(pack.buff);

	//			//첫번재 명령은 파일명 입니다.
	//			pack.Init();
	//			pack.header.nCmdIndex = nSendIndex++;
	//			pack.header.nCmdSize = 99;
	//			pack.SetCmd("FD");
	//			pack.SetStr(vecCmd[1].c_str());  
	//			Encode((char*)&pack,sizeof(pack),pData->key);
	//			send(pData->sockInfo.m_socket,(char*)&pack,sizeof(pack),0);

	//			while(!file.IsEOF())
	//			{
	//				Sleep(100);
	//				pack.Init();
	//				pack.SetCmd("FD");
	//				nRead = file.Read(pack.buff,sizeof(char),sizeof(pack.buff)); //파일 전체를 읽는다.					
	//				pack.nlen = nRead;
	//				if(nRead == size ) //마지막.. 
	//				{
	//					pack.header.nCmdIndex = nSendIndex++;
	//					pack.header.nCmdSize = 99;
	//				}
	//				else
	//				{
	//					pack.header.nCmdIndex = nSendIndex;
	//					pack.header.nCmdSize = nSendIndex;
	//				}
	//				Encode((char*)&pack,sizeof(pack),pData->key);
	//				send(pData->sockInfo.m_socket,(char*)&pack,sizeof(pack),0);
	//				if(pack.header.nCmdIndex == pack.header.nCmdSize)
	//				{
	//					break;
	//				}	
	//			}
	//		}
	//		else
	//		{
	//			SendUnKnownCmdMessage(pData->sockInfo.m_socket,pData->key);
	//		}
	//		
	//	}
	//}
	_endthreadex(0);

	return 0;
}

void main(int argc, char* argv[])
{
	//환경 설정 파일을 불러온다.
	Config::Instance()->LoadConfig();
	//로그파일 파일명을 설정한다.
	CLog::Instance()->SetFilePath(Config::Instance()->m_strLogFileName);


	InitializeCriticalSection(&criticalSection); //동기화 객체를 초기화 한다.
	DBService oDbServcie;


	ServerSocket svrSocket;
	
	vector<ReceiveSocket*> rgpRevcSocket; 

	char buffer[_BUFF_SIZE_];

	
	
	svrSocket.SetPort(Config::Instance()->m_nServerPort);
	svrSocket.InitWinsock();
	svrSocket.InitSock();
	svrSocket.Bind();
	svrSocket.Listen(Config::Instance()->m_nListenCnt);

	cout << "DB Server 입니다." << endl;
	
	ReceiveSocket* pRecvSocket = NULL;
	while(true)
	{
		pRecvSocket = new ReceiveSocket();		
		pRecvSocket= svrSocket.Accept(); //접속이 들어 오면 Reveive 소켓이 생성 된다. 
		cout <<"DB Server client 가 접속 되었습니다." << endl;
		pRecvSocket->SetIReceiveEvent(&oDbServcie);
		pRecvSocket ->CreateThread();
		rgpRevcSocket.push_back(pRecvSocket);
	}	

	for(int i = 0 ; i < rgpRevcSocket.size(); i++)
	{
		WaitForSingleObject(pRecvSocket ->m_hThread,INFINITE);
	}

	for(int i = 0 ; i < rgpRevcSocket.size(); i++)
	{
		delete rgpRevcSocket[i];
		rgpRevcSocket[i] = NULL;
	}
	return;
}
