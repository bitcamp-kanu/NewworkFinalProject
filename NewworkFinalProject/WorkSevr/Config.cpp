#include "Config.h"

//이분분 꼭 선언 해야함.
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
	//WIFile m_pKnFile;
	//m_pKnFile.Open(m_strFileName,"a+");
	//m_pKnFile.WriteLine(string(buff));
	return true;
}
bool Config::LoadConfig()
{
	return true;
}