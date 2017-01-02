#include "Config.h"
#include "..\Public\WIFile.h"
#include "..\Public\WIUtility.h"

Config* Config::m_pConfig = NULL;
Config::Config(void)
{
	//파일명은 프로젝트명.cfg
	m_strConfigFileName = "DBSevr.cfg";
}

Config::~Config(void)
{
	
}


bool Config::SaveConfig()
{
	WIFile file;
	//file.Open(m_strConfigFileName);	
	//file.WriteLine()
	return true;
}
bool Config::LoadConfig()
{
	//C:\github\bitcamp_Network_Project\NewworkFinalProject\ClientTest
	m_strConnsetStr = "DSN=Database;Uid=<username>;Pwd=<password>";

	char buff[1024] = {0};
	char temp[1024] = {0};
	GetCurrentDirectory(1024,buff);
	strcat(buff, "\\");
	strcat(buff, m_strConfigFileName.c_str());

	::GetPrivateProfileStringA("MY_Server","PORT","",temp,255,buff);
	m_nServerPort = atoi(temp);
	::GetPrivateProfileStringA("MY_Server","LIST_cnt","",temp,255,buff);
	m_nListenCnt = atoi(temp);

	m_strLogFileName = "DbServer.log";
	WIFile file;
	//file.Open(m_strConfigFileName);	
	//file.ReadLine();
	return true;
}