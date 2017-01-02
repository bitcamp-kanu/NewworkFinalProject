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
	string	m_gateServerIP;
	int		m_nGateServerPort;

	string	m_loginServerIP;
	int		m_nLoginServerPort;

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

