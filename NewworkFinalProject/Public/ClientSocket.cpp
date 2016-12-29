#include "ClientSocket.h"
#include "Log.h"
#include "WIUtility.h"
#pragma comment(lib,"Ws2_32.lib")
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
#include <WinSock2.h>

ClientSocket::ClientSocket(string ip/* = "127.0.0.1"*/,int port/* = 9000 */ ,ClientSocket::eMode mode/* = eTCP*/)
{
	memset(&m_owsadata,0x00,sizeof(m_owsadata));
	m_nPort		= port;
	m_strIP		= ip;
	m_hThread	= 0x00;
}

ClientSocket::~ClientSocket(void)
{

}
bool ClientSocket::Init(string ip/* = "127.0.0.1"*/,int port/* = 9000*/ ,ClientSocket::eMode mode/* = eTCP*/)
{
	memset(&m_owsadata,0x00,sizeof(m_owsadata));
	m_nPort		= port;
	m_strIP		= ip;
	m_hThread	= 0x00;
	return true;
}
void ClientSocket::SetPort(int port)
{
	m_nPort = port;
}
bool ClientSocket::InitWinsock()
{
	if(WSAStartup(MAKEWORD(2,2),&m_owsadata) != 0)
	{
		printf("WSAStartUp Error\n");
		return false;
	}
	return true;
}
bool ClientSocket::InitSock()
{
	m_oSockInfo.m_socket = socket(AF_INET,SOCK_STREAM,0); //AF_INET(IPV4), SOCK_STREAM(TCP)
	ZeroMemory(&m_oSockInfo.m_sockAddrIn,sizeof(m_oSockInfo.m_sockAddrIn));
	m_oSockInfo.m_sockAddrIn.sin_port = htons(m_nPort);	
	m_oSockInfo.m_sockAddrIn.sin_addr.s_addr = inet_addr(m_strIP.c_str());
	//m_oSockInfo.m_sockAddrIn.sin_port = htons(9003);	
	//m_oSockInfo.m_sockAddrIn.sin_addr.s_addr = inet_addr("127.0.0.1");
	m_oSockInfo.m_sockAddrIn.sin_family = AF_INET;
	return true;
}

bool ClientSocket::Connect()
{
	
	if(0 != connect(m_oSockInfo.m_socket 
					,(SOCKADDR*)(&m_oSockInfo.m_sockAddrIn)
					,sizeof(m_oSockInfo.m_sockAddrIn)))
	{
		string str = WIUtility::GetFormatString("ErrorCode (%d)", WSAGetLastError());
		//CLog::Instance()->WriteLog(str,__FILE__,__LINE__);
		return false;
	}
	return true;
}

int ClientSocket::Send(char* buffer,int len)
{
	return send(m_oSockInfo.m_socket,buffer,len,0);
}

int  ClientSocket::Receive(char* pBuffer,int len)
{
	return recv(m_oSockInfo.m_socket,pBuffer,len,0);
}
//Why virtual ???
int ClientSocket::ReceivtThreadRun()
{
	return true;
}