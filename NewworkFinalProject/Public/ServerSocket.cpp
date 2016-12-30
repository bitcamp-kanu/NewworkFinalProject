#include "ServerSocket.h"
#include "ReceiveSocket.h"
#include <exception>
#include "../Public/WIUtility.h"
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
	WSACleanup(); //소켓 초기화를 해제한다.
	//현재 채팅을 종료 하고 새로운 채팅을 기다리다.	
}

void ServerSocket::SetPort(int port)
{
	this->m_iPort = port;
}
bool ServerSocket::InitWinsock()
{
	if(WSAStartup(MAKEWORD(2,2),&m_wsadata) != 0) 
	{
		throw exceptionSS(WIUtility::GetLastErrorMessage().c_str());
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
		throw exceptionSS(WIUtility::GetLastErrorMessage().c_str());
		return false;
	}
	return true;
}

bool ServerSocket::Bind()
{	
	//주소설정. Network 는 bigendan 에 맞춘다.
	ZeroMemory(&m_oSockInfo.m_sockAddrIn,sizeof(m_oSockInfo.m_sockAddrIn));	
	m_oSockInfo.m_sockAddrIn.sin_addr.s_addr	= htonl(INADDR_ANY);//자기 자신의 아이피를 할당한다.
	m_oSockInfo.m_sockAddrIn.sin_family		= AF_INET;			//(internetwork: UDP, TCP, etc.) 영역에서 사용할 소켓을 생성한다.
	m_oSockInfo.m_sockAddrIn.sin_port			= htons(m_iPort);		//htons 함수는 u_short를 호스트에서 
	
	//소켓과 주소 정보를 bind 한다. 
	if(bind(m_oSockInfo.m_socket
			,(SOCKADDR*)&m_oSockInfo.m_sockAddrIn
			,sizeof(m_oSockInfo.m_sockAddrIn)) 
			== SOCKET_ERROR) 
	{
		throw exceptionSS(WIUtility::GetLastErrorMessage().c_str());
		return false;
	}
	return true;
}
//UPD 에서는 사용하지 않는다.
int ServerSocket::Listen(int cnt /*= 5*/)
{
	if(listen(m_oSockInfo.m_socket,cnt) != 0)
	{
		throw exceptionSS(WIUtility::GetLastErrorMessage().c_str());
	}
	cout << "Server Listen()." << endl;
	cout << GetInof() << endl;
	return 0;
}
//UPD 에서는 사용하지 않는다.
ReceiveSocket* ServerSocket::Accept()
{
	ReceiveSocket* pRrecvSocket = NULL;
	pRrecvSocket = new ReceiveSocket();
	int addrLen = sizeof(m_oSockInfo.m_sockAddr);

	cout << "Server 소켓을 시작 합니다. " << endl;
	cout << GetInof() << endl;
	
	pRrecvSocket -> m_oSockInfo.m_socket = accept(m_oSockInfo.m_socket
												,&m_oSockInfo.m_sockAddr
												,&addrLen);

	if(pRrecvSocket->m_oSockInfo.m_socket == INVALID_SOCKET) //클라이언트 접속을 대기한다.
	{
		delete pRrecvSocket; //문제가 발생 하면 함수 안에서 메모리를 해제 한다.
		pRrecvSocket = NULL;
		throw exceptionSS(WIUtility::GetLastErrorMessage().c_str());
		return NULL;
	}	
	//정상 반환한 포인터는 사용자 측에서 해제 한다.
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

string ServerSocket::GetInof()
{
	string str = WIUtility::GetFormatString("IP:[%s] ,Port[%d]"
											,WIUtility::GetSocketIP(m_oSockInfo.m_sockAddrIn).c_str()
											,WIUtility::GetSocketPORT(m_oSockInfo.m_sockAddrIn));
	return str;
}