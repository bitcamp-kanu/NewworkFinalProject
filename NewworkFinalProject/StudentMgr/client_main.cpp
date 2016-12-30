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
	char ID[20];
	char SecretKey;
	//소켓
	//ClientSocket oSock("192.168.0.59", 9000);
	ClientSocket oSock("127.0.0.1", 9000);
	try
	{
		oSock.InitWinsock();
		oSock.InitSock();
		oSock.Connect();
		WIUtility::Gotoxy(130, 2);
		cout << "연결완료";
	}
	catch (exceptionCS e)
	{
		cout << "Client Socket 에서 문제가 발생하였습니다. " << e.what() << endl;
	}
	catch (exception e)
	{
		cout << "오류가 발생하였습니다. " << e.what() << endl;
	}
	//로그인
	while (1)
	{
	//1. 로그인레이아웃
		system("cls");
		Display::DrawRect(Point(1, 1), Point(140, 35));
		Display::DrawRect(Point(40, 12), Point(70, 18));
		Display::DrawRect(Point(47, 15), Point(55, 5));
		Display::DrawRect(Point(47, 22), Point(55, 5));
		WIUtility::Gotoxy(48, 14);
		std::cout << "ID" << endl;
		WIUtility::Gotoxy(48, 21);
		std::cout << "PASSWORD" << endl;
	//2.로그인
	//ID
		WIUtility::Gotoxy(50, 17);
		cin >> buff;
		sprintf(ID, "%s", buff);

	//PW
		WIUtility::Gotoxy(50, 24);
		memset(buff, 0, sizeof(buff));
		cin >> buff;
		char str[20];
		sprintf(str, "%s", buff);
		WIUtility::Gotoxy(1, 38);
	//데이터보내기
		_Login pkLogin('A', 'L', 99, ID, str);
		try
		{
			if (0 < oSock.Send((char*)&pkLogin, sizeof(pkLogin)))
			{
				oSock.Receive((char*)&pkLogin, sizeof(pkLogin));

				SecretKey = pkLogin.header.SecretKey;
				cout << SecretKey;//검사

				if (pkLogin.header.pakID == 111) //111 로그인 성공
				{
					AfxMessageBox("로그인에 성공하였습니다.");
					break;
				}
				else
				{
					AfxMessageBox("로그인에 실패하였습니다.");
				}
				cout << pkLogin.ToString() << endl;
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
		Sleep(2000);
	}

	if (1)//로그인성공
	{
		//GATEWAY SERVER와 연결
		//소켓
		ClientSocket oSock("127.0.0.1", 9000);
		try
		{
			oSock.InitWinsock();
			oSock.InitSock();
			oSock.Connect();
			WIUtility::Gotoxy(130, 2);
			cout << "연결완료";
		}
		catch (exceptionCS e)
		{
			cout << "Client Socket 에서 문제가 발생하였습니다. " << e.what() << endl;
		}
		catch (exception e)
		{
			cout << "오류가 발생하였습니다. " << e.what() << endl;
		}
		//반 이름, 유저정보 요청 
		//_DemandUserInfo(char cmd1, char cmd2, int pakID, char* id, char SecretKey, char* ClassId, char* ClassName, char* UName)
		_DemandUserInfo UInfo('U', 'S', 99, ID, SecretKey, "0","0","0");
		while (1) // 인증성공할때까지 계속 요청
		{
			if (0 < oSock.Send((char*)&UInfo, sizeof(UInfo)))
			{
				oSock.Receive((char*)&UInfo, sizeof(UInfo));
				if (UInfo.header.pakID == 201) //201 인증 성공
				{
					break;
				}
			}
		}

		// 학생정보 요청

//_WorkData(char cmd1,char cmd2,int  pakID,char* id,char* skey, \
char* mClassId, int mClassNum, char* mSName, char mSSex, char* mSTel,\
int mC, int mCPP, int mCSharp, int mNetwork, int mUnity,\
int mTotal, DOUBLE mAve, int mUDate)
	




		////메인 레이아웃
		system("cls");
		Display::DrawRect(Point(1, 1), Point(140, 35));
		Display::DrawXLine(Point(1, 7), 140);
		Display::DrawXLine(Point(1, 30), 140);
		WIUtility::Gotoxy(4, 4);
		cout << "학급 및 매니저 정보" << endl;

		WIUtility::Gotoxy(20, 4);
		cout << UInfo.ClassName << endl;
		cout << UInfo.UName << endl;

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
			char stdname[20] = { 0 };
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
			// 입력받기
				memset(buff, 0, sizeof(buff));
				cin >> buff;
				sprintf(stdname, "%s", buff);




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
				WIUtility::Gotoxy(4, 10);
				cout << "출석번호" << endl;
				WIUtility::Gotoxy(4, 12);
				cout << "이름" << endl;
				WIUtility::Gotoxy(4, 14);
				cout << "C" << endl;
				WIUtility::Gotoxy(4, 16);
				cout << "C++" << endl;
				WIUtility::Gotoxy(4, 18);
				cout << "C#" << endl;
				WIUtility::Gotoxy(4, 20);
				cout << "Network" << endl;
				WIUtility::Gotoxy(4, 22);
				cout << "Unity" << endl;
				WIUtility::Gotoxy(4, 24);
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
				cout << "출석번호\t이름\t성별\t전화번호\t\tC\tC++\tC#\tNetwork\tUnity\tTotal\tAvg" << endl;
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
