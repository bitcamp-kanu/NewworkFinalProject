#include "Config.h"
#include "..\Public\WIFile.h"

Config* Config::m_pConfig = NULL;
Config::Config(void)
{
	//���ϸ��� ������Ʈ��.cfg
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
	m_strConnsetStr = "DSN=Database;Uid=<username>;Pwd=<password>";
	m_nServerPort = 9003;
	m_nListenCnt = 5;
	m_strLogFileName = "DbServer.log";
	WIFile file;
	//file.Open(m_strConfigFileName);	
	//file.ReadLine();
	return true;
}