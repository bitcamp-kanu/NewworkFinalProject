#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
//#include <windows.h>
#include <string>
#include <vector>
using namespace std;

class Point
{
private:
	int m_nX;
	int m_nY;

public:
	Point()
	{
		m_nX = m_nY = 0;
	}
	Point(const int& x,const int& y)
	{
		m_nX = x;
		m_nY = y;

	}
	int GetX()
	{
		return m_nX;
	}
	void SetX(const int x)
	{
		m_nX = x;
	}
	int AddX(int x)
	{
		m_nX += x;
	}

	int GetY()
	{
		return m_nY;
	}
	void SetY(const int y)
	{
		m_nY = y;
	}
	int AddY(int y)
	{
		m_nY += y;
	}

	Point& operator+(Point& pt)
	{
		m_nX  = m_nX + pt.GetX();
		m_nY += pt.GetY();
		return (*this);
	}

};
class Rect
{
private:
	int m_nX;
	int m_nY;
	int m_nWidth;
	int m_nHeight;
public:
	Rect(int x,int y, int width, int height)
	{
		m_nX = x;
		m_nY = y;
		m_nWidth = width;
		m_nHeight = height;
	}

	int GetX()
	{
		return m_nX;
	}
	int GetY()
	{
		return m_nY;
	}
	int GetWidth()
	{
		return m_nWidth;
	}
	int GetHeigth()
	{
		return m_nHeight;
	}
	Point GetStaPos()
	{
		return Point(m_nX,m_nY);
	}

	Rect InnerRect() //사방으로 1직 작은 사각형 반환
	{
		return Rect(m_nX + 1,m_nY + 1,m_nWidth - 2,m_nWidth - 2);
	}
};


class Display
{
private:
	static char m_cKey;
public:
	void static DrawRect(Rect& rect);
	
	void static DrawRect(Point& pt , Point& pt2);
	void static DrawXLine(Point& pt1 , int len);	
	void static DrawYLine(Point& pt1 , int len);

	char static IsSaveMenu(int x,int y);
	char static IsSelectMenu(int x,int y);
};
