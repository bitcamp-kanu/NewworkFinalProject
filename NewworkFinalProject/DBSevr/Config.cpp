#include "Config.h"
#include "..\Public\WIFile.h"


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
	WIFile file;
	//file.Open(m_strConfigFileName);	
	//file.ReadLine();
	return true;
}