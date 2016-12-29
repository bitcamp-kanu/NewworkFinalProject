#include "Config.h"

Config* Config::m_pConfig = NULL;
Config::Config(void)
{
	m_strConfigFileName = "DBSevr.cfg";
}


Config::~Config(void)
{
	
}


bool Config::SaveConfig()
{

	m_dbServerIP = "172.0.0.1";
	m_nDbServerPort = 9003;
	return true;

	//WIFile m_pKnFile;
	//m_pKnFile.Open(m_strFileName,"a+");
	//m_pKnFile.WriteLine(string(buff));
}
bool Config::LoadConfig()
{
	return true;
}