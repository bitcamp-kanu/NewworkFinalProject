#include "PersonManager.h"
#include <iostream>
using namespace std;

PersonManager::PersonManager(void)
{

}
PersonManager::~PersonManager(void)
{
}


void PersonManager::InsertTelInfo(Person& person)
{
	this->m_rgList.push_back(person);
}
vector<Person> PersonManager::DeleteTelInfo(string& name)
{
	vector<Person> vec;
	list<Person>::iterator iter;
	for (iter = m_rgList.begin(); iter != m_rgList.end();)
	{
		if(iter->m_szName == name)
		{
			vec.push_back(*iter);
			iter = m_rgList.erase(iter); //�̳��� ++�� ��� �Ѵ�. ���� �ϸ� ���� ��ġ�� �ڵ� �̵� �ȴ�.
		}
		else
		{
			iter++;
		}
	}
	return vec;
}
vector<Person> PersonManager::SearchTelInfo(string& name)
{
	vector<Person> vec;
	list<Person>::iterator iter;
	for (iter = m_rgList.begin(); iter != m_rgList.end();iter++)
	{
		if(iter->m_szName == name)
		{
			vec.push_back(*iter);
		}
	}
	return vec;
}
vector<Person> PersonManager::GetAllData()
{
	vector<Person> vec;
	list<Person>::iterator iter;
	for (iter = m_rgList.begin(); iter != m_rgList.end();iter++)
	{
		vec.push_back(*iter);
	}
	return vec;
}