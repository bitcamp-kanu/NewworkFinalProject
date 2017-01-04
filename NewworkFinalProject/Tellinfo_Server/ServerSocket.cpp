#include "ServerSocket.h"

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
		printf("%d Bind error\n",WSAGetLastError());
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
SockInfo& ServerSocket::Accept()
{
	char buffer[1024];
	SOCKET sock;
	SockInfo accpetSock;
	int addrlen = sizeof(m_oSockInfo.m_sockAddr);
	accpetSock.m_socket = accept(m_oSockInfo.m_socket
								,&m_oSockInfo.m_sockAddr
								,&addrlen);


	
	//int len = recv(accpetSock.m_socket,buffer,sizeof(buffer),0);
	//if(len == SOCKET_ERROR || len == 0) //���� ������ ����.
	//{
	//	int error = WSAGetLastError();
	//	cout << "RecvThreadFun ���� �����Ͱ� �߸� �Ǿ����ϴ�.";
	//	//bExit = true;
	//	//break;
	//}

	if(accpetSock.m_socket == INVALID_SOCKET) //Ŭ���̾�Ʈ ������ ����Ѵ�.
	{
		printf("Accept Error\n");
		return accpetSock;
	}	
	return accpetSock;
}

//int ServerSocket::Send(char* buff,int size)
//{
//	return send(m_clientSocket,buff,size,0);
//}
//int ServerSocket::Receive(char* buff,int len)
//{
//	return recv(m_clientSocket,buff,len,0);
//}
//int ServerSocket::RecvFfrom(char* buff, int len)
//{
//	//������ ���� Ȯ��.
//	int size = sizeof(m_clinetAddress);
//	return recvfrom(m_serverSocket,buff,len,0,(SOCKADDR*)&m_clinetAddress,&size);
//}
//int ServerSocket::SendTo(char *buffer,int len)
//{
//	return sendto(m_serverSocket,buffer,len,0,(SOCKADDR*)&m_serverAddress,sizeof(m_serverSocket));
//}

void ServerSocket::ReleaseSocket()
{

	//if(m_clientSocket  != 0x00)
	//{
	//	closesocket(m_clientSocket);
	//	m_clientSocket = 0x00;	
	//}
}