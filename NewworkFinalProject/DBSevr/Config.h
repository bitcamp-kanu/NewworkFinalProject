#pragma once
#include <iostream>
#include <string>
using namespace std;
//ȯ�� ���� ������ ������ Ŭ����.
class Config
{
public:
	//�ʿ��� ȯ�� ���� ������ �߰� �Ѵ�.
	//DB ���� ����.
	string m_strConnsetStr;
private:
	string m_strConfigFileName;
	static Config* m_pConfig;
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
	//�Լ��� �߰��Ͽ����ϴ�.
};

