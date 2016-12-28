#pragma once
#include <iostream>
#include <string>
using namespace std;
//환경 설정 내용을 관리할 클래스.
class Config
{
public:
	//필요한 환경 설정 정보를 추가 한다.
	//DB 연결 정보.
	string m_strConnsetStr;
private:
	string m_strConfigFileName;
	static Config* m_pConfig;
	Config(void);
public:
	//시간상 Get Set 은 생략 한다. 절대 이렇게 코딩 하면 않됨.
	//DB 접속 내용 추가
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
	//함수를 추가하였습니다.
};

