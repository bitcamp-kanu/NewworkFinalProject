#include "Config.h"
#include <Windows.h>

//�̺к� �� ���� �ؾ���.
Config* Config::m_pConfig = NULL;
Config::Config(void)
{
	m_strConfigFileName = "WORKSevr.cfg";
}


Config::~Config(void)
{
	
}


bool Config::SaveConfig()
{
	//WIFile m_pKnFile;
	/*m_pKnFile.Open(m_strFileName,"a+");
	m_pKnFile.WriteLine(string(buff))*/;
	::WritePrivateProfileStringA("DB_Server","IP","127.0.0.1","C:\\ysu\\WorkSevrWORKSevr.ini");
	m_dbServerIP = "127.0.0.1";
	m_nDbServerPort = 9003;
	return true;
}
bool Config::LoadConfig()
{
	m_nServerPort = 9002;
	m_nListenCnt = 5;

	//������ DB ���� ����. 
	m_dbServerIP = "127.0.0.1";
	m_nDbServerPort = 9003;

	return true;
}