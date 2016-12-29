#include "ClintSocket.h"


ClintSocket::ClintSocket(int port/* = 9000 */,string ip/* = "127.0.0.1"*/ ,ClintSocket::eMode mode/* = eTCP*/)
{
	memset(&m_clientAddress,0x00,sizeof(m_clientAddress));
	memset(&m_clientSocket,0x00,sizeof(m_clientSocket));
	memset(&m_wsadata,0x00,sizeof(m_wsadata));
	m_nPort			= port;
	m_strRHostIP	= ip;
	m_len			= 0;
}

ClintSocket::~ClintSocket(void)
{
}


void ClintSocket::SetPort(int port)
{
	this->m_nPort = port;
}
bool ClintSocket::InitWinsock() //윈속 정보를 초기화 한다.
{
	if(WSAStartup(MAKEWORD(2,2),&m_wsadata) != 0)
	{
		printf("WSAStartUp Error\n");
		return;
	}
	return true;
}
bool ClintSocket::InitSock()
{
	
	return true;
}