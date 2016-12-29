

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
	//strHelp.append("HE ����	<ex>HE\n");
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
	cout << "�߸��� ��û�� ���Խ��ϴ�.." << endl;
	LeaveCriticalSection(&criticalSection);
	Packet pack;			
	pack.SetCmd("MG"); //����.
	pack.SetStr("�߸��� ��û �Դϴ�.");
	Encode((char*)&pack,sizeof(Packet),key);
	send(sock,(char*)&pack,sizeof(pack),0);
}
void SendNotFormatCmdMessage(SOCKET& sock, char key)
{
	EnterCriticalSection(&criticalSection);
	cout << "��ɾ� ������ �߸��Ǿ����ϴ�." << endl;
	LeaveCriticalSection(&criticalSection);
	Packet pack;			
	pack.SetCmd("MG"); //����.
	pack.SetStr("��ɾ� ������ �߸��Ǿ����ϴ�.");
	
	Encode((char*)&pack,sizeof(Packet),key);
	send(sock,(char*)&pack,sizeof(pack),0);
}
void SendSucessMessage(SOCKET& sock, char key)
{
	EnterCriticalSection(&criticalSection);
	cout << "����� ���������� ó���Ǿ����ϴ�." << endl;
	LeaveCriticalSection(&criticalSection);
	Packet pack;			
	pack.SetCmd("MG"); //����.
	pack.SetStr("����� ���������� ó���Ǿ����ϴ�.");
	Encode((char*)&pack,sizeof(Packet),key);
	send(sock,(char*)&pack,sizeof(pack),0);
}
void SendMessage(SOCKET& sock , char* msg, char key)
{
	Packet pack;			
	pack.SetCmd("MG"); //����.
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

	//		if(len == SOCKET_ERROR || len == 0) //���� ������ ����.
	//		{
	//			int error = WSAGetLastError();
	//			cout << "RecvThreadFun ���� �����Ͱ� �߸� �Ǿ����ϴ�.";
	//			bExit = true;
	//			break;
	//		}
	//		
	//		Packet pack;			
	//		pack.SetDataCopy((Packet*)buffer);
	//		Decode((char*)&pack,sizeof(Packet),pData->key);

	//		if(IsCommand(pack.header.chCmd,"HE")) //���� ��û �̸�.. 
	//		{
	//			cout << "���� ������ ��û �Ͽ����ϴ�." << endl;
	//			pack.Init();
	//			pack.SetCmd("HE"); //����.
	//			pack.SetStr(strHelp.c_str());
	//			Encode((char*)&pack,sizeof(pack),pData->key);
	//			send(pData->sockInfo.m_socket,(char*)&pack,sizeof(pack),0);
	//			
	//		}
	//		else if(IsCommand(pack.header.chCmd,"ID")) //�ű� ����̸�. 
	//		{
	//			cout << "�ű� ��� ��û�� ���Խ��ϴ�." << endl;
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
	//		else if(IsCommand(pack.header.chCmd,"DD")) //�����̸�
	//		{
	//			cout << "���� ��û�� ���Խ��ϴ�." << endl;
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
	//				SendMessage(pData->sockInfo.m_socket,"���� �Ǿ����ϴ�.",pData->key);
	//			}
	//			else
	//			{
	//				SendMessage(pData->sockInfo.m_socket,"���� : ��ġ�ϴ� �̸��� �����ϴ�.",pData->key);
	//			}
	//		}
	//		else if(IsCommand(pack.header.chCmd,"SD")) //�˻��̸�.
	//		{
	//			cout << "�˻� ��û�� ���Խ��ϴ�." << endl;
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
	//				SendMessage(pData->sockInfo.m_socket,"�˻� �Ǿ����ϴ�.",pData->key);
	//			}
	//			else
	//			{
	//				SendMessage(pData->sockInfo.m_socket,"�˻� : ��ġ�ϴ� �̸��� �����ϴ�.",pData->key);
	//			}
	//		}
	//		else if(IsCommand(pack.header.chCmd,"PD")) //��� ��� ��û �̸�
	//		{
	//			cout << "��ü ������ ��û." << endl;
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
	//		else if(IsCommand(pack.header.chCmd,"FD")) //���������̸�
	//		{
	//			cout << "���� ������ ��û�� ���Խ��ϴ�." << endl;
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
	//				SendMessage(pData->sockInfo.m_socket,"�������� : ��ġ�ϴ� ������ �����ϴ�.",pData->key);
	//			}
	//			
	//			int nSendIndex = 0;
	//			int nRead = 0;
	//			int size = sizeof(pack.buff);

	//			//ù���� ����� ���ϸ� �Դϴ�.
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
	//				nRead = file.Read(pack.buff,sizeof(char),sizeof(pack.buff)); //���� ��ü�� �д´�.					
	//				pack.nlen = nRead;
	//				if(nRead == size ) //������.. 
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
	//ȯ�� ���� ������ �ҷ��´�.
	Config::Instance()->LoadConfig();
	//�α����� ���ϸ��� �����Ѵ�.
	CLog::Instance()->SetFilePath(Config::Instance()->m_strLogFileName);


	InitializeCriticalSection(&criticalSection); //����ȭ ��ü�� �ʱ�ȭ �Ѵ�.
	DBService oDbServcie;


	ServerSocket svrSocket;
	
	vector<ReceiveSocket*> rgpRevcSocket; 

	char buffer[_BUFF_SIZE_];

	
	
	svrSocket.SetPort(Config::Instance()->m_nServerPort);
	svrSocket.InitWinsock();
	svrSocket.InitSock();
	svrSocket.Bind();
	svrSocket.Listen(Config::Instance()->m_nListenCnt);

	cout << "DB Server �Դϴ�." << endl;
	
	ReceiveSocket* pRecvSocket = NULL;
	while(true)
	{
		pRecvSocket = new ReceiveSocket();		
		pRecvSocket= svrSocket.Accept(); //������ ��� ���� Reveive ������ ���� �ȴ�. 
		cout <<"DB Server client �� ���� �Ǿ����ϴ�." << endl;
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
