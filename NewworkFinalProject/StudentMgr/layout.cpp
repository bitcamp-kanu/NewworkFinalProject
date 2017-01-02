#include <iostream>
#include "..\Public\WIDisplay.h"
#include "..\Public\WIUtility.h"

using namespace std;

//로그인 화면
//1. 외각 사각형
void LoginLayout()
{
	//상단
	WIUtility::Gotoxy(2, 1);
	cout << "┏";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 1);
		cout << "━";
	}
	WIUtility::Gotoxy(144, 1);
	cout << "┓";

	//왼쪽
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(2, i);
		cout << "┃";
	}
	//오른쪽
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(144, i);
		cout << "┃";
	}
	//하단
	WIUtility::Gotoxy(2, 40);
	cout << "┗";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 40);
		cout << "━";
	}
	WIUtility::Gotoxy(144, 40);
	cout << "┛";

	//내부 사각형1
	//상단
	WIUtility::Gotoxy(40, 13);
	cout << "┏";

	for (int i = 21; i < 55; i++)
	{
		WIUtility::Gotoxy(2 * i, 13);
		cout << "━";
	}
	WIUtility::Gotoxy(110, 13);
	cout << "┓";

	//왼쪽
	for (int i = 14; i<31; i++)
	{
		WIUtility::Gotoxy(40, i);
		cout << "┃";
	}
	////오른쪽
	for (int i = 14; i<31; i++)
	{
		WIUtility::Gotoxy(110, i);
		cout << "┃";
	}
	//하단
	WIUtility::Gotoxy(40, 31);
	cout << "┗";
	for (int i = 21; i < 55; i++)
	{
		WIUtility::Gotoxy(2 * i, 31);
		cout << "━";
	}
	WIUtility::Gotoxy(110, 31);
	cout << "┛";


	//ID 입력칸
	WIUtility::Gotoxy(53, 15);
	cout << "ID";
	WIUtility::Gotoxy(50, 16);
	cout << "┏";

	for (int i = 26; i < 50; i++)
	{
		WIUtility::Gotoxy(2 * i, 16);
		cout << "━";
	}
	WIUtility::Gotoxy(100, 16);
	cout << "┓";

	//왼쪽
	for (int i = 17; i<20; i++)
	{
		WIUtility::Gotoxy(50, i);
		cout << "┃";
	}
	//오른쪽
	for (int i = 17; i<20; i++)
	{
		WIUtility::Gotoxy(100, i);
		cout << "┃";
	}
	//하단
	WIUtility::Gotoxy(50, 20);
	cout << "┗";
	for (int i = 26; i < 50; i++)
	{
		WIUtility::Gotoxy(2 * i, 20);
		cout << "━";
	}
	WIUtility::Gotoxy(100, 20);
	cout << "┛";



	//pw 입력칸
	WIUtility::Gotoxy(53, 23);
	cout << "PASSWORD";
	WIUtility::Gotoxy(50, 24);
	cout << "┏";

	for (int i = 26; i < 50; i++)
	{
		WIUtility::Gotoxy(2 * i, 24);
		cout << "━";
	}
	WIUtility::Gotoxy(100, 24);
	cout << "┓";

	//왼쪽
	for (int i = 25; i<28; i++)
	{
		WIUtility::Gotoxy(50, i);
		cout << "┃";
	}
	//오른쪽
	for (int i = 25; i<28; i++)
	{
		WIUtility::Gotoxy(100, i);
		cout << "┃";
	}
	////하단
	WIUtility::Gotoxy(50, 28);
	cout << "┗";
	for (int i = 26; i < 50; i++)
	{
		WIUtility::Gotoxy(2 * i, 28);
		cout << "━";
	}
	WIUtility::Gotoxy(100, 28);
	cout << "┛";
}

//메인화면
void MainLayout()
{
	//외부 사각형
	//상단
	WIUtility::Gotoxy(2, 1);
	cout << "┏";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 1);
		cout << "━";
	}
	WIUtility::Gotoxy(144, 1);
	cout << "┓";

	//왼쪽
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(2, i);
		cout << "┃";
	}
	//오른쪽
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(144, i);
		cout << "┃";
	}
	//하단
	WIUtility::Gotoxy(2, 40);
	cout << "┗";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 40);
		cout << "━";
	}
	WIUtility::Gotoxy(144, 40);
	cout << "┛";

	//상단 가로줄
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 6);
		cout << "━";
	}
	WIUtility::Gotoxy(2, 6);
	cout << "┣";
	WIUtility::Gotoxy(144, 6);
	cout << "┫";

	//하단 가로줄
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 35);
		cout << "━";
	}
	WIUtility::Gotoxy(2, 35);
	cout << "┣";
	WIUtility::Gotoxy(144, 35);
	cout << "┫";
	//상단 제목
	WIUtility::Gotoxy(6, 4);
	cout << "학급 및 매니저 정보" << endl;
	//하단 메뉴
	WIUtility::Gotoxy(7, 38);
	cout << "1.학생등록\t\t2.학생삭제\t\t3.학생수정\t\t4.점수수정\t\t5.학생검색" << endl;
}

// 학생 등록
void MainLayout1()
{
	//외부 사각형
	//상단
	WIUtility::Gotoxy(2, 1);
	cout << "┏";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 1);
		cout << "━";
	}
	WIUtility::Gotoxy(144, 1);
	cout << "┓";

	//왼쪽
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(2, i);
		cout << "┃";
	}
	//오른쪽
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(144, i);
		cout << "┃";
	}
	//하단
	WIUtility::Gotoxy(2, 40);
	cout << "┗";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 40);
		cout << "━";
	}
	WIUtility::Gotoxy(144, 40);
	cout << "┛";

	//상단 가로줄
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 6);
		cout << "━";
	}
	WIUtility::Gotoxy(2, 6);
	cout << "┣";
	WIUtility::Gotoxy(144, 6);
	cout << "┫";

	//하단 가로줄
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 35);
		cout << "━";
	}
	WIUtility::Gotoxy(2, 35);
	cout << "┣";
	WIUtility::Gotoxy(144, 35);
	cout << "┫";
	//상단 제목
	WIUtility::Gotoxy(7, 4);
	cout << "학생 등록" << endl;
	//하단 메뉴
	WIUtility::Gotoxy(7, 38);
	cout << "1.학생등록\t\t2.학생삭제\t\t3.학생수정\t\t4.점수수정\t\t5.학생검색" << endl;
	WIUtility::Gotoxy(7, 9);
	cout << "반: " << endl;
	WIUtility::Gotoxy(7, 11);
	cout << "학생 이름: " << endl;
	WIUtility::Gotoxy(7, 13);
	cout << "성별: " << endl;
	WIUtility::Gotoxy(7, 15);
	cout << "전화번호: " << endl;
	
	
}

//학생 삭제
void MainLayout2()
{
	//외부 사각형
	//상단
	WIUtility::Gotoxy(2, 1);
	cout << "┏";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 1);
		cout << "━";
	}
	WIUtility::Gotoxy(144, 1);
	cout << "┓";

	//왼쪽
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(2, i);
		cout << "┃";
	}
	//오른쪽
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(144, i);
		cout << "┃";
	}
	//하단
	WIUtility::Gotoxy(2, 40);
	cout << "┗";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 40);
		cout << "━";
	}
	WIUtility::Gotoxy(144, 40);
	cout << "┛";

	//상단 가로줄
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 6);
		cout << "━";
	}
	WIUtility::Gotoxy(2, 6);
	cout << "┣";
	WIUtility::Gotoxy(144, 6);
	cout << "┫";

	//하단 가로줄
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 35);
		cout << "━";
	}
	WIUtility::Gotoxy(2, 35);
	cout << "┣";
	WIUtility::Gotoxy(144, 35);
	cout << "┫";
	//상단 제목
	WIUtility::Gotoxy(7, 4);
	cout << "학생 삭제" << endl;
	//하단 메뉴
	WIUtility::Gotoxy(7, 38);
	cout << "1.학생등록\t\t2.학생삭제\t\t3.학생수정\t\t4.점수수정\t\t5.학생검색" << endl;
	WIUtility::Gotoxy(7, 9);
	cout << "반: " << endl;
	WIUtility::Gotoxy(7, 11);
	cout << "학생 이름: " << endl;
}

//학생 수정
void MainLayout3()
{
	//외부 사각형
	//상단
	WIUtility::Gotoxy(2, 1);
	cout << "┏";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 1);
		cout << "━";
	}
	WIUtility::Gotoxy(144, 1);
	cout << "┓";

	//왼쪽
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(2, i);
		cout << "┃";
	}
	//오른쪽
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(144, i);
		cout << "┃";
	}
	//하단
	WIUtility::Gotoxy(2, 40);
	cout << "┗";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 40);
		cout << "━";
	}
	WIUtility::Gotoxy(144, 40);
	cout << "┛";

	//상단 가로줄
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 6);
		cout << "━";
	}
	WIUtility::Gotoxy(2, 6);
	cout << "┣";
	WIUtility::Gotoxy(144, 6);
	cout << "┫";

	//하단 가로줄
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 35);
		cout << "━";
	}
	WIUtility::Gotoxy(2, 35);
	cout << "┣";
	WIUtility::Gotoxy(144, 35);
	cout << "┫";
	//상단 제목
	WIUtility::Gotoxy(7, 4);
	cout << "학생 수정" << endl;
	//하단 메뉴
	WIUtility::Gotoxy(7, 38);
	cout << "1.학생등록\t\t2.학생삭제\t\t3.학생수정\t\t4.점수수정\t\t5.학생검색" << endl;
	WIUtility::Gotoxy(7, 9);
	cout << "반: " << endl;
	WIUtility::Gotoxy(7, 11);
	cout << "학생 이름: " << endl;
	WIUtility::Gotoxy(7, 13);
	cout << "성별: " << endl;
	WIUtility::Gotoxy(7, 15);
	cout << "전화번호: " << endl;

}

//점수 수정
void MainLayout4()
{
	//외부 사각형
	//상단
	WIUtility::Gotoxy(2, 1);
	cout << "┏";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 1);
		cout << "━";
	}
	WIUtility::Gotoxy(144, 1);
	cout << "┓";

	//왼쪽
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(2, i);
		cout << "┃";
	}
	//오른쪽
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(144, i);
		cout << "┃";
	}
	//하단
	WIUtility::Gotoxy(2, 40);
	cout << "┗";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 40);
		cout << "━";
	}
	WIUtility::Gotoxy(144, 40);
	cout << "┛";

	//상단 가로줄
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 6);
		cout << "━";
	}
	WIUtility::Gotoxy(2, 6);
	cout << "┣";
	WIUtility::Gotoxy(144, 6);
	cout << "┫";

	//하단 가로줄
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 35);
		cout << "━";
	}
	WIUtility::Gotoxy(2, 35);
	cout << "┣";
	WIUtility::Gotoxy(144, 35);
	cout << "┫";
	//상단 제목
	WIUtility::Gotoxy(7, 4);
	cout << "점수 수정" << endl;
	//하단 메뉴
	WIUtility::Gotoxy(7, 38);
	cout << "1.학생등록\t\t2.학생삭제\t\t3.학생수정\t\t4.점수수정\t\t5.학생검색" << endl;
	WIUtility::Gotoxy(7, 10);
	cout << "반:" << endl;
	WIUtility::Gotoxy(7, 13);
	cout << "이름:" << endl;
	WIUtility::Gotoxy(7, 16);
	cout << "C:" << endl;
	WIUtility::Gotoxy(7, 19);
	cout << "C++:" << endl;
	WIUtility::Gotoxy(7, 22);
	cout << "C#:" << endl;
	WIUtility::Gotoxy(7, 25);
	cout << "Network:" << endl;
	WIUtility::Gotoxy(7, 28);
	cout << "Unity:" << endl;

}

//학생 검색
void MainLayout5()
{
	//외부 사각형
	//상단
	WIUtility::Gotoxy(2, 1);
	cout << "┏";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 1);
		cout << "━";
	}
	WIUtility::Gotoxy(144, 1);
	cout << "┓";

	//왼쪽
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(2, i);
		cout << "┃";
	}
	//오른쪽
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(144, i);
		cout << "┃";
	}
	//하단
	WIUtility::Gotoxy(2, 40);
	cout << "┗";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 40);
		cout << "━";
	}
	WIUtility::Gotoxy(144, 40);
	cout << "┛";

	//상단 가로줄
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 6);
		cout << "━";
	}
	WIUtility::Gotoxy(2, 6);
	cout << "┣";
	WIUtility::Gotoxy(144, 6);
	cout << "┫";

	//하단 가로줄
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 35);
		cout << "━";
	}
	WIUtility::Gotoxy(2, 35);
	cout << "┣";
	WIUtility::Gotoxy(144, 35);
	cout << "┫";
	//상단 제목
	WIUtility::Gotoxy(7, 4);
	cout << "학생 검색" << endl;
	//하단 메뉴
	WIUtility::Gotoxy(7, 38);
	cout << "1.학생등록\t\t2.학생삭제\t\t3.학생수정\t\t4.점수수정\t\t5.학생검색" << endl;
	WIUtility::Gotoxy(10, 8);
	cout << "반\t이름\t 성별\t 전화번호\t\t C\t C++\t C#\t Network\tUnity\t Total\t Avg" << endl;
}
