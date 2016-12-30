#pragma comment(lib,"Ws2_32.lib") //winsock 2.2 ���̺귯��
#pragma warning(disable: 4996)
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501

#include <WinSock2.h> //Winsock 2 ���� Header
#include "WIDisplay.h"
#include "WIUtility.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>

using namespace std;

char Display::m_cKey = '*';

//���� ������ �׸���.
void Display::DrawXLine(Point& pt1 , int len)
{
	for(int i = 0 ; i <len ; i++ )
	{	
		WIUtility::Gotoxy(pt1.GetX() + i , pt1.GetY());
		printf("%c",Display::m_cKey);
	}
}
//���� ������ �׸���.
void Display::DrawYLine(Point& pt1 , int len)
{
	for(int i = 0 ; i <len ; i++ )
	{		
		WIUtility::Gotoxy(pt1.GetX() , pt1.GetY() + i);
		printf("%c",Display::m_cKey);
	}
}

void Display::DrawRect(Point& pt ,Point& pt2)
{
	for(int i = 0 ; i <pt2.GetX() ; i++ )
	{	
		int j=pt2.GetY();
		WIUtility::Gotoxy(pt.GetX() + i , pt.GetY());
		printf("%c",Display::m_cKey);
		WIUtility::Gotoxy(pt.GetX() + i+1 , pt.GetY()+j);
		printf("%c",Display::m_cKey);
	}
	for(int i = 0 ; i < pt2.GetY() ; i++ )
	{	
		int j=pt2.GetX();	
		WIUtility::Gotoxy(pt.GetX()  , pt.GetY()+i);
		printf("%c",Display::m_cKey);
		WIUtility::Gotoxy(pt.GetX() + j, pt.GetY()+i+1);
		printf("%c",Display::m_cKey);
	}
}

//2016.12.13 �޼ҵ� �߰�.
void Display::DrawRect(Rect& rect)
{
	Display::DrawXLine(rect.GetStaPos(),rect.GetWidth());
	Point newPt = rect.GetStaPos() + Point(0,rect.GetHeigth()-1);
	Display::DrawXLine(newPt,rect.GetWidth());

	Display::DrawYLine(rect.GetStaPos(),rect.GetHeigth());
	newPt = rect.GetStaPos() + Point(rect.GetWidth()-1,0);
	Display::DrawYLine(newPt,rect.GetHeigth());
}
char Display::IsSaveMenu(int x,int y)
{
	//char buff[255] = {0};
	int key = 0;
	while(true)
	{
		WIUtility::Gotoxy(x,y);
		cout << "                                                         ";
		WIUtility::Gotoxy(x,y);
		cout << "���� �Ͻðڽ��ϱ�. ����(Y) ���(C) �ٽ��Է�(N)";		
		key = getch();
		if(toupper(key) == 'Y' || toupper(key) == 'C' || toupper(key) == 'N')
		{
			WIUtility::Gotoxy(x,y);
			cout << "                                                              "; //������ �����͸� ���� �ϳ�,
			break;
		}
	}
	return toupper(key);
}
char Display::IsSelectMenu(int x,int y)
{
	int key = 0;
	while(true)
	{		
		WIUtility::Gotoxy(x,y);
		key = getch();
		if(toupper(key) == 'Y' || toupper(key) == 'C' || toupper(key) == 'N')
		{
			WIUtility::Gotoxy(x,y);
			cout << "                                                              "; //������ �����͸� ���� �ϳ�,
			break;
		}
	}
	return toupper(key);
}

