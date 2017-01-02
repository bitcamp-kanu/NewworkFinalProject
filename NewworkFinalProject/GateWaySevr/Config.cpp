#include "Config.h"
#include "..\Public\WIUtility.h"

Config* Config::m_pConfig = NULL;
Config::Config(void)
{
	m_strConfigFileName = "GateWaySevr.cfg";
}


Config::~Config(void)
{

}


bool Config::SaveConfig()
{

	//GateWay 서버 입니다.
	//DB 서버 접속 정보.
	m_dbServerIP = "127.0.0.1";
	m_nDbServerPort = 9003;
	return true;

	//WIFile m_pKnFile;
	//m_pKnFile.Open(m_strFileName,"a+");
	//m_pKnFile.WriteLine(string(buff));
}
bool Config::LoadConfig()
{
	m_strLogFileName = "gateWaySevr.log";

	char buff[1024] = {0};
	char temp[1024] = {0};
	GetCurrentDirectory(1024,buff);
	strcat(buff, "\\");
	strcat(buff, m_strConfigFileName.c_str());

	::GetPrivateProfileStringA("MY_Server","PORT","",temp,255,buff);
	m_nServerPort = atoi(temp);
	::GetPrivateProfileStringA("MY_Server","LIST_cnt","",temp,255,buff);
	m_nListenCnt = atoi(temp);

	::GetPrivateProfileStringA("DB_Server","IP","",temp,255,buff);
	m_dbServerIP = temp;
	::GetPrivateProfileStringA("DB_Server","PORT","",temp,255,buff);
	m_nDbServerPort = atoi(temp);

	::GetPrivateProfileStringA("WK_Server","IP","",temp,255,buff);
	m_workServerIP = temp;
	::GetPrivateProfileStringA("WK_Server","PORT","",temp,255,buff);
	m_nWorkServerPort = atoi(temp);
	
	return true;
}