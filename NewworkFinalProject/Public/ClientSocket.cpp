#include "ClientSocket.h"
#include "Log.h"
#include "WIUtility.h"
#pragma comment(lib,"Ws2_32.lib")
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
#include <WinSock2.h>
//#include "baseSocket.h"

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
		throw exceptionCS(WIUtility::GetLastErrorMessage().c_str());
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
	m_oSockInfo.m_sockAddrIn.sin_family = AF_INET;
	return true;
}

bool ClientSocket::Connect()
{
	cout << "ClientSocket Connect()." << endl;
	cout << GetInof() << endl;

	if(0 != connect(m_oSockInfo.m_socket 
					,(SOCKADDR*)(&m_oSockInfo.m_sockAddrIn)
					,sizeof(m_oSockInfo.m_sockAddrIn)))
	{
		throw exceptionCS(WIUtility::GetLastErrorMessage().c_str());
		return false;
	}
	return true;
}

int ClientSocket::Send(char* buffer,int len)
{
	int nlen = send(m_oSockInfo.m_socket,buffer,len,0);
	if(nlen <= 0)
	{
		throw exceptionCS(WIUtility::GetLastErrorMessage().c_str());
	}
	return nlen;
}

int  ClientSocket::Receive(char* pBuffer,int len)
{
	int nlen = recv(m_oSockInfo.m_socket,pBuffer,len,0);
	if(nlen <= 0)
	{
		throw exceptionCS(WIUtility::GetLastErrorMessage().c_str());
	}
	return nlen;
}
//Why virtual ???
int ClientSocket::ReceivtThreadRun()
{
	cout << "ClientSocket::ReceivtThreadRun() 사용않함" << endl;	
	return true;
}
string ClientSocket::GetInof()
{
	string str = WIUtility::GetFormatString("IP:[%s] ,Port[%s]"
		,WIUtility::GetSocketIP(m_oSockInfo.m_sockAddrIn)
		,WIUtility::GetSocketPORT(m_oSockInfo.m_sockAddrIn));
	return str;
}