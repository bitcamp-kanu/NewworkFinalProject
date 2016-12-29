#include "ClientSocket.h"

ClientSocket::ClientSocket(int port/* = 9000 */,string ip/* = "127.0.0.1"*/ ,ClientSocket::eMode mode/* = eTCP*/)
{
	//memset(&m_clientAddress,0x00,sizeof(m_clientAddress));
	//memset(&m_clientSocket,0x00,sizeof(m_clientSocket));
	//memset(&m_wsadata,0x00,sizeof(m_wsadata));
	//m_nPort			= port;
	//m_strRHostIP	= ip;
	//m_len			= 0;
}

ClientSocket::~ClientSocket(void)
{
}


void ClientSocket::SetPort(int port)
{
	m_nPort = port;
}
bool ClientSocket::InitWinsock()
{
	return true;
}
bool ClientSocket::InitSock()
{
	return true;
}

int ClientSocket::Send(char* buffer,int len)
{
	return true;
}
//Why virtual ???
int ClientSocket::ReceivtThreadRun()
{
	return true;
}