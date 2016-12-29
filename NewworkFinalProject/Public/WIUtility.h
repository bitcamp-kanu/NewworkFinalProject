#pragma once
#pragma comment(lib,"Ws2_32.lib") //winsock 2.2 라이브러리
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501

#include <WinSock2.h> //Winsock 2 버전 Header

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;
/*
	class WIUtility
	1. 자주 사용 하는 함수 모음
	2. 모든 함수는 static 로 생성
	   함수 접근시 WIUtility::함수명 형태로 호출 하면 됨.
	   <ex>WIUtility::Gotoxy(10,10);
	   class 를 생성할 필요 없음.
*/

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

class WIUtility
{
public:
	WIUtility(void);
	~WIUtility(void);	
	
	/*
	작성자:DSurfer
	현재 시간을 문자열 형태로 반환 한다.
	YYYYMMDDHHMM -> 2016-12-23 12:01:23
	YYYYMMDDHHMM -> 2016-12-23 12:01
	YYYYMMDD -> 2016-12-23
	*/
	static string GetCurTime(const string& str = "YYYYMMDDHHMMSS");
	
	/*
	작성자:DSurfer
	현재시간을 반환 한다. (20161223121212  형식)
	*/
	static string GetCurTime();
	
	/*
	작성자:DSurfer
	현재시간을 반환 한다. 
	*/
	static void  GetCurTime(int& y,int& m,int& d);

	/*
	작성자:DSurfer
	현재시간을 요일을 반환 한다. (일,월,화,수,목,금)
	*/
	static string GetWeek();
	
	/*
	작성자:DSurfer
	년월일 문자열 형식을 포멧 문자열 형식으로 변환 한다.
	20161224 -> 2016-12-24
	20161224121212 -> 2016-12-24 12:12:12
	*/
	static string ToDateFormat(string day);


	/*
	작성자:turboc
	화면의 모든 내용을 지운다.
	*/
	static void Clrscr();
	
	/*
	작성자:turboc
	Curser 위치를 이동 시킨다.
	*/
	static void Gotoxy(int x, int y);
	
	/*
	작성자:turboc
	현재 커서 위치를 가져온다.
	*/
	static int WhereX();
	
	/*
	작성자:turboc
	현재 커서 위치를 가져온다.
	*/
	static int WhereY();

	/*
	작성자:turboc
	현재 커서를 설정한다.
	*/
	static void SetCursorType(CURSOR_TYPE c);

	/*
	작성자:turboc
	Sleep 를 준다.
	*/
	static void Delay(int n);


	/*
	작성자:turboc
	문자열을 구분자로 분리 한다.
	*/
	static void Tokenize(const string& str,vector<string>& tokens,const string& delimiters = " ");
	static vector<string> Tokenize(const string& str,const string& delimiters = " ");
	

	/*
	작성자:DSurfer
	Text Color 을 설정한다.
	*/
	static void TextColor(int color_number = 7);

	//SOCKADDR_IN 값을 127.0.0.1 형식의 IP 문자열 형태로 변환 한다.
	static string GetSocketIP(const SOCKADDR_IN&  SockAddress);
	//SOCKADDR_IN 값을 Port 값 으로 변환 하낟.
	static int GetSocketPORT(const SOCKADDR_IN&  SockAddress);

	//2016.12.29 SJM GetFormatString 비정적을 정적(static) 으로 수정 
	static string GetFormatString(char* format,...);




	//ErrorCode 를 받아서  string 로 출력 하는 함수. 
	//교체 void ViewError(char* format,...) 코드 참조. 
	//출력 말고 에러 코드만 반환 하면됨. 
	

	//printf 같은 기능을 하는 함수. format("%s %d 위", "대한민국",1 ); 
	//대한민국 1위 문자열을 화면에 출력 하는것이 아니라 string or char * 형태의 값으로 반환 해준다.

	//함수를 추가했습니다. 


	//함수를 추가했음

};

