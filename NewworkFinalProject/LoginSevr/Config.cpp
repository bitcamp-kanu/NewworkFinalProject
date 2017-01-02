#include "Config.h"
#include "..\Public\WIUtility.h"

Config* Config::m_pConfig = NULL;
Config::Config(void)
{
	m_strConfigFileName = "LoginSevr.cfg";
}


Config::~Config(void)
{
	
}


bool Config::SaveConfig()
{
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

	::GetPrivateProfileStringA("DB_Server","IP","",temp,255,buff);
	m_dbServerIP = temp;
	::GetPrivateProfileStringA("DB_Server","PORT","",temp,255,buff);
	m_nDbServerPort = atoi(temp);

	return true;
}