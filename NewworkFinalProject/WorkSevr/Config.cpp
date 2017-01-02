#include "Config.h"
#include "..\Public\WIUtility.h"
//#include <Windows.h>


//이분분 꼭 선언 해야함.
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

	char buff[1024] = {0};
	GetCurrentDirectory(1024,buff);
	strcat(buff, "\\");
	strcat(buff, m_strConfigFileName.c_str());
	
	::WritePrivateProfileStringA("DB_Server","IP","127.0.0.1",buff);
	::WritePrivateProfileStringA("DB_Server","PORT","9003",buff);
	m_dbServerIP = "127.0.0.1";
	m_nDbServerPort = 9003;
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