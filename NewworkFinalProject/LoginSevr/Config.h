#pragma once
#include <iostream>
#include <string>
using namespace std;
//ȯ�� ���� ������ ������ Ŭ����.
class Config
{
public:
	static Config* m_pConfig;
	string m_strConfigFileName;

	int		m_nServerPort;
	int		m_nListenCnt;

	//������ Ÿ�� ����
	string	m_dbServerIP;
	int		m_nDbServerPort;
	Config(void);
public:
	//�ð��� Get Set �� ���� �Ѵ�. ���� �̷��� �ڵ� �ϸ� �ʵ�.
	//DB ���� ���� �߰�
public:
	~Config(void);
	static Config* Instance()
	{
		if(Config::m_pConfig == NULL)
		{
			Config::m_pConfig = new Config();
		}
		return Config::m_pConfig;
	}

	bool SaveConfig();
	bool LoadConfig();
};

