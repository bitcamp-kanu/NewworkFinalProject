#include "Config.h"


Config::Config(void)
{
	m_strConfigFileName = "DBSevr.cfg";
}


Config::~Config(void)
{
	
}


bool Config::SaveConfig()
{
	WIFile m_pKnFile;
	m_pKnFile.Open(m_strFileName,"a+");
	m_pKnFile.WriteLine(string(buff));
}
bool Config::LoadConfig()
{

}