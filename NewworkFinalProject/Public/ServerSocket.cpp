#include "ServerSocket.h"
#include "ReceiveSocket.h"
#include <exception>
#define _BUFF_SIZE_ 4096

ServerSocket::ServerSocket(int port /*= 9000*/, ServerSocket::eMode mode /* = eTCP*/) 
{
	memset(&m_oSockInfo.m_sockAddrIn,0x00,sizeof(m_oSockInfo.m_sockAddrIn));
	memset(&m_oSockInfo.m_socket,0x00,sizeof(m_oSockInfo.m_socket));
	memset(&m_wsadata,0x00,sizeof(m_wsadata));
	
	m_iPort = 9000; 
	m_eMode = mode;
}



ServerSocket::~ServerSocket(void)
{
	ReleaseSocket();
	WSACleanup(); //���� �ʱ�ȭ�� �����Ѵ�.
	//���� ä���� ���� �ϰ� ���ο� ä���� ��ٸ���.	
}

void ServerSocket::SetPort(int port)
{
	this->m_iPort = port;
}
bool ServerSocket::InitWinsock()
{
	if(WSAStartup(MAKEWORD(2,2),&m_wsadata) != 0) 
	{
		printf("WSAStartUp Error\n");
		return false;
	}
	return true;
}
bool ServerSocket::InitSock()
{
	switch(m_eMode)
	{
	case eTCP:
		m_oSockInfo.m_socket = socket(AF_INET,SOCK_STREAM,0);
		break;
	case eUDP:
		m_oSockInfo.m_socket = socket(AF_INET,SOCK_DGRAM,0);
		break;
	}
	if(m_oSockInfo.m_socket == INVALID_SOCKET)
	{
		printf("Socket Error\n");		
		return false;
	}
}

bool ServerSocket::Bind()
{	
	//�ּҼ���. Network �� bigendan �� �����.
	ZeroMemory(&m_oSockInfo.m_sockAddrIn,sizeof(m_oSockInfo.m_sockAddrIn));	
	m_oSockInfo.m_sockAddrIn.sin_addr.s_addr	= htonl(INADDR_ANY);//�ڱ� �ڽ��� �����Ǹ� �Ҵ��Ѵ�.
	m_oSockInfo.m_sockAddrIn.sin_family		= AF_INET;			//(internetwork: UDP, TCP, etc.) �������� ����� ������ �����Ѵ�.
	m_oSockInfo.m_sockAddrIn.sin_port			= htons(m_iPort);		//htons �Լ��� u_short�� ȣ��Ʈ���� 
	
	//���ϰ� �ּ� ������ bind �Ѵ�. 
	if(bind(m_oSockInfo.m_socket
			,(SOCKADDR*)&m_oSockInfo.m_sockAddrIn
			,sizeof(m_oSockInfo.m_sockAddrIn)) 
			== SOCKET_ERROR) 
	{
		//throw exception("Accept Error\n");
		//printf("%d Bind error\n",WSAGetLastError());
		return false;
	}
	return true;
}
//UPD ������ ������� �ʴ´�.
int ServerSocket::Listen(int cnt /*= 5*/)
{
	return listen(m_oSockInfo.m_socket,cnt);  //serverSocket �� ��� �������� ���� �Ѵ�.
}
//UPD ������ ������� �ʴ´�.
ReceiveSocket* ServerSocket::Accept()
{
	ReceiveSocket* pRrecvSocket = NULL;
	//SOCKET sock;
	//SockInfo accpetSock;
	// 
	pRrecvSocket = new ReceiveSocket();
	int addrLen = sizeof(m_oSockInfo.m_sockAddr);
	pRrecvSocket -> m_oSockInfo.m_socket = accept(m_oSockInfo.m_socket
												,&m_oSockInfo.m_sockAddr
												,&addrLen);

	if(pRrecvSocket->m_oSockInfo.m_socket == INVALID_SOCKET) //Ŭ���̾�Ʈ ������ ����Ѵ�.
	{
		delete pRrecvSocket; //������ �߻� �ϸ� �Լ� �ȿ��� �޸𸮸� ���� �Ѵ�.
		pRrecvSocket = NULL;
		throw exception("Accept Error\n");
		return NULL;
	}	
	//���� ��ȯ�� �����ʹ� ����� ������ ���� �Ѵ�.
	return pRrecvSocket;
}

void ServerSocket::ReleaseSocket()
{

	//if(m_clientSocket  != 0x00)
	//{
	//	closesocket(m_clientSocket);
	//	m_clientSocket = 0x00;	
	//}
}