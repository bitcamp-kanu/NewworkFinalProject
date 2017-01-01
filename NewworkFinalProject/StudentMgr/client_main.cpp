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
#include "layout.h"

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
		LoginLayout();
	//2.로그인
	//ID
		WIUtility::Gotoxy(53, 18);
		cin >> buff;
		sprintf(ID, "%s", buff);
	//PW
		WIUtility::Gotoxy(53, 26);
		memset(buff, 0, sizeof(buff));
		cin >> buff;
		char str[20];
		sprintf(str, "%s", buff);
		WIUtility::Gotoxy(1, 41);
	//데이터보내기
		_Login pkLogin('A', 'L', 99, ID, str);
		try
		{
			if (0 < oSock.Send((char*)&pkLogin, sizeof(pkLogin)))
			{
				oSock.Receive((char*)&pkLogin, sizeof(pkLogin));

				if(pkLogin.header.pakID == 111)
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
		MainLayout();
		//메뉴선택
		while (1)
		{
			int key;
			char stdname[20] = { 0 };
			kbhit();
			key = getch();
			switch (key)
			{
			case 49: //1.학생 등록
				system("cls");
				MainLayout1();
				// 입력받기
				WIUtility::Gotoxy(11, 9);// 반 입력 커서이동
				memset(buff, 0, sizeof(buff));
				cin >> buff;
				sprintf(stdname, "%s", buff);
				WIUtility::Gotoxy(18, 11);// 이름 입력 커서이동
				memset(buff, 0, sizeof(buff));
				cin >> buff;
				sprintf(stdname, "%s", buff);
				WIUtility::Gotoxy(13, 13); // 성별 입력 커서이동
				memset(buff, 0, sizeof(buff));
				cin >> buff;
				sprintf(stdname, "%s", buff);
				WIUtility::Gotoxy(17, 15); //전화번호 입력 커서이동
				memset(buff, 0, sizeof(buff));
				cin >> buff;
				sprintf(stdname, "%s", buff);
			
				break;
			case 50: // 2.학생 삭제
				system("cls");
				MainLayout2();
				WIUtility::Gotoxy(11, 9); //반
				memset(buff, 0, sizeof(buff));
				cin >> buff;
				sprintf(stdname, "%s", buff);
				WIUtility::Gotoxy(18, 11); //이름
				memset(buff, 0, sizeof(buff));
				cin >> buff;
				sprintf(stdname, "%s", buff);
				break;
			case 51: //3.학생수정
				system("cls");
				MainLayout3();
				// 입력받기
				WIUtility::Gotoxy(11, 9);// 반 입력 커서이동
				memset(buff, 0, sizeof(buff));
				cin >> buff;
				sprintf(stdname, "%s", buff);
				WIUtility::Gotoxy(18, 11);// 이름 입력 커서이동
				memset(buff, 0, sizeof(buff));
				cin >> buff;
				sprintf(stdname, "%s", buff);
				WIUtility::Gotoxy(13, 13); // 성별 입력 커서이동
				memset(buff, 0, sizeof(buff));
				cin >> buff;
				sprintf(stdname, "%s", buff);
				WIUtility::Gotoxy(17, 15); //전화번호 입력 커서이동
				memset(buff, 0, sizeof(buff));
				cin >> buff;
				sprintf(stdname, "%s", buff);
				break;
			case 52://4.점수 수정
				system("cls");
				MainLayout4();
				WIUtility::Gotoxy(11, 10);//반
				memset(buff, 0, sizeof(buff));
				cin >> buff;
				sprintf(stdname, "%s", buff);
				WIUtility::Gotoxy(13, 13);//이름
				memset(buff, 0, sizeof(buff));
				cin >> buff;
				sprintf(stdname, "%s", buff);
				WIUtility::Gotoxy(10, 16);//C
				memset(buff, 0, sizeof(buff));
				cin >> buff;
				sprintf(stdname, "%s", buff);
				WIUtility::Gotoxy(12, 19);//C++
				memset(buff, 0, sizeof(buff));
				cin >> buff;
				sprintf(stdname, "%s", buff);
				WIUtility::Gotoxy(11, 22);//C#
				memset(buff, 0, sizeof(buff));
				cin >> buff;
				sprintf(stdname, "%s", buff);
				WIUtility::Gotoxy(16, 25);//Network
				memset(buff, 0, sizeof(buff));
				cin >> buff;
				sprintf(stdname, "%s", buff);
				WIUtility::Gotoxy(14, 28);//Unity
				memset(buff, 0, sizeof(buff));
				cin >> buff;
				sprintf(stdname, "%s", buff);
				break;
			case 53://5.학생검색
				system("cls");
				MainLayout5();
				break;

			}
		}

	}


	////로그인실패
	//else
	//Display::DrawRect(Point(1, 1), Point(140, 35));
//	AfxMessageBox("정보가 없음");
}
