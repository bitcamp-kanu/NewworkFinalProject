#pragma comment(lib,"Ws2_32.lib")
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
#include <afxwin.h>
#include <WinSock2.h>
//#include <windows.h>

#include <stdio.h>
#include <iostream>
#include <process.h>
#include <iostream>
#include "..\Public\ClientSocket.h"
#include "..\Public\PublicDefine.h"
#include "..\public\ServerSocket.h"

#include "..\Public\WIDisplay.h"
#include "..\Public\WIUtility.h"

using namespace std;


void main()
{
	char buff[1024];
	char str[20];

	//소켓
	//ClientSocket oSock("192.168.0.59", 9000);
	ClientSocket oSock("127.0.0.1", 9000);
	oSock.InitWinsock();
	oSock.InitSock();
	oSock.Connect();
	WIUtility::Gotoxy(2, 2);
	cout << "연결완료";

	//로그인
	//1. 로그인레이아웃
	Display::DrawRect(Point(1, 1), Point(140, 35));
	Display::DrawRect(Point(40, 12), Point(70, 18));
	Display::DrawRect(Point(47, 15), Point(55, 5));
	Display::DrawRect(Point(47, 22), Point(55, 5));
	WIUtility::Gotoxy(48, 14);
	cout << "ID" << endl;
	WIUtility::Gotoxy(48, 21);
	cout << "PASSWORD" << endl;

	//2.로그인
	while (1)
	{
		//ID
		WIUtility::Gotoxy(50, 17);
		cin >> buff;
		sprintf(str, "%s", buff);

		//PW도ID처럼 받나용...
		WIUtility::Gotoxy(50, 24);
		memset(buff, 0, sizeof(buff));
		cin >> buff;
		char str2[20];
		sprintf(str2, "%s", buff);

		_Login pkLogin('A', 'L', '.', str, str2);
		try
		{
			if (0 < oSock.Send((char*)&pkLogin, sizeof(pkLogin)))
			{
				oSock.Receive((char*)&pkLogin, sizeof(pkLogin));

				if(pkLogin.header.pakID == 'T')
				{
					AfxMessageBox("로그인에 성공하였습니다.");
				}
				else
				{
					AfxMessageBox("로그인에 실패하였습니다.");
				}
				cout << pkLogin.ToString() << endl;

				if (pkLogin.header.SecretKey = 'T')
					break;
				else
					WIUtility::Gotoxy(48, 10);
				cout << "다시입력";
			}
		}
		catch (exceptionCS e)
		{
			cout << "Client Socket 에서 문제가 발생하였습니다. " << e.what() << endl;
		}
		catch (exception e)
		{
			cout << "오류가 발생하였습니다. " << e.what() << endl;
		}
	}

	if (1)//로그인성공
	{
		////메인 레이아웃
		system("cls");
		Display::DrawRect(Point(1, 1), Point(140, 35));
		Display::DrawXLine(Point(1, 7), 140);
		Display::DrawXLine(Point(1, 30), 140);
		WIUtility::Gotoxy(4, 4);
		cout << "학급 및 매니저 정보" << endl;

		WIUtility::Gotoxy(4, 9);
		cout << "학생 목록" << endl;
		WIUtility::Gotoxy(4, 11);
		//cout << "출석번호\t이름\t\tC\t\tC++\t\tC#\t\tNetwork\t\tUnity\t\tTotal\t\tAvg" << endl;
		WIUtility::Gotoxy(4, 31);
		cout << "메뉴 정보" << endl;
		WIUtility::Gotoxy(4, 33);
		cout << "1.학생등록\t\t2.학생삭제\t\t3.학생수정\t\t4.점수수정\t\t5.학생검색\t\t6.과목별평균" << endl;


		//메뉴선택
		while (1)
		{
			int key;
			kbhit();
			key = getch();
			switch (key)
			{
			case 49:
				system("cls");
				Display::DrawRect(Point(1, 1), Point(140, 35));
				Display::DrawXLine(Point(1, 7), 140);
				Display::DrawXLine(Point(1, 30), 140);
				WIUtility::Gotoxy(4, 4);
				cout << "학생 등록" << endl;
				WIUtility::Gotoxy(4, 9);
				cout << "학생 이름: " << endl;
				WIUtility::Gotoxy(4, 33);
				cout << "1.학생등록\t\t2.학생삭제\t\t3.학생수정\t\t4.점수수정\t\t5.학생검색\t\t6.과목별평균" << endl;
				WIUtility::Gotoxy(15, 9);// 커서이동
				memset(buff, 0, sizeof(buff));// 입력받기
				memset(str, 0, sizeof(str));
				cin >> buff;
				sprintf(str, "%s", buff);
				break;
			case 50:
				system("cls");
				Display::DrawRect(Point(1, 1), Point(140, 35));
				Display::DrawXLine(Point(1, 7), 140);
				Display::DrawXLine(Point(1, 30), 140);
				WIUtility::Gotoxy(4, 4);
				cout << "학생 삭제" << endl;
				WIUtility::Gotoxy(4, 33);
				cout << "1.학생등록\t\t2.학생삭제\t\t3.학생수정\t\t4.점수수정\t\t5.학생검색\t\t6.과목별평균" << endl;
				break;
			case 51:
				system("cls");
				Display::DrawRect(Point(1, 1), Point(140, 35));
				Display::DrawXLine(Point(1, 7), 140);
				Display::DrawXLine(Point(1, 30), 140);
				WIUtility::Gotoxy(4, 4);
				cout << "학생 수정" << endl;
				WIUtility::Gotoxy(4, 33);
				cout << "1.학생등록\t\t2.학생삭제\t\t3.학생수정\t\t4.점수수정\t\t5.학생검색\t\t6.과목별평균" << endl;
				break;
			case 52:
				system("cls");
				Display::DrawRect(Point(1, 1), Point(140, 35));
				Display::DrawXLine(Point(1, 7), 140);
				Display::DrawXLine(Point(1, 30), 140);
				WIUtility::Gotoxy(4, 4);
				cout << "점수 수정" << endl;
				WIUtility::Gotoxy(4, 33);
				cout << "1.학생등록\t\t2.학생삭제\t\t3.학생수정\t\t4.점수수정\t\t5.학생검색\t\t6.과목별평균" << endl;
				break;
			case 53:
				system("cls");
				Display::DrawRect(Point(1, 1), Point(140, 35));
				Display::DrawXLine(Point(1, 7), 140);
				Display::DrawXLine(Point(1, 30), 140);
				WIUtility::Gotoxy(4, 4);
				cout << "학생 검색" << endl;
				WIUtility::Gotoxy(4, 10);
				cout << "출석번호\t이름\t\tC\t\tC++\t\tC#\t\tNetwork\t\tUnity\t\tTotal\t\tAvg" << endl;
				WIUtility::Gotoxy(4, 33);
				cout << "1.학생등록\t\t2.학생삭제\t\t3.학생수정\t\t4.점수수정\t\t5.학생검색\t\t6.과목별평균" << endl;
				break;

			case 54:
				system("cls");
				Display::DrawRect(Point(1, 1), Point(140, 35));
				Display::DrawXLine(Point(1, 7), 140);
				Display::DrawXLine(Point(1, 30), 140);
				WIUtility::Gotoxy(4, 4);
				cout << "과목별 평균" << endl;
				WIUtility::Gotoxy(4, 33);
				cout << "1.학생등록\t\t2.학생삭제\t\t3.학생수정\t\t4.점수수정\t\t5.학생검색\t\t6.과목별평균" << endl;
				break;
			}
		}

	}


	////로그인실패
	//else
	//Display::DrawRect(Point(1, 1), Point(140, 35));
//	AfxMessageBox("정보가 없음");
}
