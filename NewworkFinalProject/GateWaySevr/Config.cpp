#include "Config.h"

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
	m_nServerPort = 9001;
	m_nListenCnt = 5;

	//연결할 DB 서버 정보. 
	m_dbServerIP = "127.0.0.1";
	m_nDbServerPort = 9003;
	return true;
}