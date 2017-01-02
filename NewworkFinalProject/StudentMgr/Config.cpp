#include "Config.h"
#include "..\Public\WIUtility.h"

Config* Config::m_pConfig = NULL;
Config::Config(void)
{
	m_strConfigFileName = "ClientSevr.cfg";
}


Config::~Config(void)
{
	
}


bool Config::SaveConfig()
{
	//WIFile m_pKnFile;
	//m_pKnFile.Open(m_strFileName,"a+");
	//m_pKnFile.WriteLine(string(buff));
	return true;
}
bool Config::LoadConfig()
{
	char buff[1024] = {0};
	char temp[1024] = {0};
	GetCurrentDirectory(1024,buff);
	strcat(buff, "\\");
	strcat(buff, m_strConfigFileName.c_str());

	::GetPrivateProfileStringA("MY_Server","PORT","",temp,255,buff);
	m_nServerPort = atoi(temp);
	::GetPrivateProfileStringA("MY_Server","LIST_cnt","",temp,255,buff);
	m_nListenCnt = atoi(temp);

	::GetPrivateProfileStringA("LOG_Server","IP","",temp,255,buff);
	m_loginServerIP = temp;
	::GetPrivateProfileStringA("LOG_Server","PORT","",temp,255,buff);
	m_nLoginServerPort = atoi(temp);

	::GetPrivateProfileStringA("GT_Server","IP","",temp,255,buff);
	m_gateServerIP = temp;
	::GetPrivateProfileStringA("GT_Server","PORT","",temp,255,buff);
	m_nGateServerPort = atoi(temp);

	return true;
}