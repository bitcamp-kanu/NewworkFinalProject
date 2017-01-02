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
	char ClassId[20] = { 0 };
	char ClassName[20] = { 0 };
	int ClassNum = 0;
	char UName[20] = { 0 };
	int key; //키보드 입력
	//LoginServer와 연결
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
		char str[20] = { 0 };
		int i = 0;
		while (1)
		{
			if (kbhit())
			{
				str[i] = getch();
				cout << "*";
				if (i==7)
				{
					break;
				}
				i++;
			}
		}
		WIUtility::Gotoxy(1, 41);
		//데이터보내기
		_Login pkLogin('A', 'L', 99, ID, str);
		try
		{
			if (0 < oSock.Send((char*)&pkLogin, sizeof(pkLogin)))
			{
				oSock.Receive((char*)&pkLogin, sizeof(pkLogin));
				if (pkLogin.header.pakID == 111)
				{
					AfxMessageBox("로그인에 성공하였습니다.");
					SecretKey = pkLogin.header.SecretKey;//SecretKey저장
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
		Sleep(1000);
	}
	if (1)//로그인성공
	{
		//GATEWAY SERVER와 연결
				//소켓
		ClientSocket oSock("127.0.0.1", 9001);
		try
		{
			oSock.InitWinsock();
			oSock.InitSock();
			oSock.Connect();
			WIUtility::Gotoxy(130, 4);
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

		_DemandUserInfo UInfo('U', 'S', 99, ID, SecretKey, "0", "0", "0");
		while (1)
		{
			try
			{
				if (0 < oSock.Send((char*)&UInfo, sizeof(UInfo)))
				{
					oSock.Receive((char*)&UInfo, sizeof(UInfo));
					if (UInfo.header.pakID == 201)
					{
						break;
					}
					else
					{
						AfxMessageBox("불러오기에 실패하였습니다.");
					}
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
		WIUtility::Gotoxy(35, 4);//유저정보 출력
		cout << UInfo.ClassId << "\t\t" << UInfo.ClassName << "\t\t" << UInfo.UName;
		//// 학생정보 요청 AA??
		//		//_WorkData(char cmd1,char cmd2,int  pakID,char* id,char* skey, \
		//		char* mClassId, int mClassNum, char* mSName, char mSSex, char* mSTel,\
		//		int mC, int mCPP, int mCSharp, int mNetwork, int mUnity,\
		//		int mTotal, DOUBLE mAve, int mUDate)


		////메인 레이아웃
		system("cls");
		MainLayout();
		//메뉴선택
		while (1)
		{
			char SName[20] = { 0 };
			char SSex = 0;
			char STel[20] = { 0 };
			int C = 0;
			int CPP = 0;
			int CSharp = 0;
			int Network = 0;
			int Unity = 0;
			int Total = 0;
			double Ave = 0;
			char UDate[15] = { 0 };
			kbhit();
			key = getch();
			switch (key)
			{
			case 49://1.학생 등록 SC
				system("cls");
				MainLayout1();
				// 입력받기
				WIUtility::Gotoxy(11, 9);// 반 입력 커서이동
				memset(ClassId, 0, sizeof(ClassId));
				cin >> ClassId;
				WIUtility::Gotoxy(18, 11);// 이름 입력 커서이동
				memset(SName, 0, sizeof(SName));
				cin >> SName;
				WIUtility::Gotoxy(13, 13); // 성별 입력 커서이동
				cin >> SSex;
				WIUtility::Gotoxy(17, 15); //전화번호 입력 커서이동
				memset(STel, 0, sizeof(STel));
				cin >> STel;

				//패킷 구성
				{
				_WorkData SCData('S', 'C', 99, ID, SecretKey,
					ClassId, ClassNum, SName, SSex, STel,
					C, CPP, CSharp, Network, Unity,
					Ave, Total, UDate);
					if (0 < oSock.Send((char*)&SCData, sizeof(SCData)))
					{
						oSock.Receive((char*)&SCData, sizeof(SCData));
						if (SCData.header.pakID == 201) //201 인증 성공
						{
							AfxMessageBox("등록에 성공하였습니다.");
						}
						else
						{
							AfxMessageBox("등록에 실패하였습니다.");
						}
					}
				}
				break;
			case 50: // 2.학생 삭제 SD
				system("cls");
				MainLayout2();
				WIUtility::Gotoxy(11, 9); //반
				memset(ClassId, 0, sizeof(ClassId));
				cin >> ClassId;
				WIUtility::Gotoxy(18, 11); //이름
				memset(SName, 0, sizeof(SName));
				cin >> SName;
				//패킷 구성
				{
				_WorkData SDData('S', 'D', 99, ID, SecretKey,
					ClassId, ClassNum, SName, SSex, STel,
					C, CPP, CSharp, Network, Unity,
					Ave, Total, UDate);
					if (0 < oSock.Send((char*)&SDData, sizeof(SDData)))
					{
						oSock.Receive((char*)&SDData, sizeof(SDData));
						if (SDData.header.pakID == 201) //201 인증 성공
						{
							AfxMessageBox("삭제에 성공하였습니다.");
						}
						else
						{
							AfxMessageBox("삭제에 실패하였습니다.");
						}
					}
				}
				break;
			case 51: //3.학생수정 SU
				system("cls");
				MainLayout3();
				// 입력받기
				WIUtility::Gotoxy(11, 9);// 반 입력 커서이동
				memset(ClassId, 0, sizeof(ClassId));
				cin >> ClassId;
				WIUtility::Gotoxy(18, 11);// 이름 입력 커서이동
				memset(SName, 0, sizeof(SName));
				cin >> SName;
				WIUtility::Gotoxy(13, 13); // 성별 입력 커서이동
				cin >> SSex;
				WIUtility::Gotoxy(17, 15); //전화번호 입력 커서이동
				memset(STel, 0, sizeof(STel));
				cin >> STel;
				//패킷 구성
				{
				_WorkData SUData('S', 'U', 99, ID, SecretKey,
					ClassId, ClassNum, SName, SSex, STel,
					C, CPP, CSharp, Network, Unity,
					Ave, Total, UDate);
					if (0 < oSock.Send((char*)&SUData, sizeof(SUData)))
					{
						oSock.Receive((char*)&SUData, sizeof(SUData));
						if (SUData.header.pakID == 201) //201 인증 성공
						{
							AfxMessageBox("수정에 성공하였습니다.");
						}
						else
						{
							AfxMessageBox("수정에 실패하였습니다.");
						}
					}
				}
				break;
			case 52://4.점수 수정 SG
				system("cls");
				MainLayout4();
				WIUtility::Gotoxy(11, 10);//반
				memset(ClassId, 0, sizeof(ClassId));
				cin >> ClassId;
				WIUtility::Gotoxy(13, 13);//이름
				memset(SName, 0, sizeof(SName));
				cin >> SName;
				WIUtility::Gotoxy(10, 16);//C
				cin >> C;
				WIUtility::Gotoxy(12, 19);//C++
				cin >> CPP;
				WIUtility::Gotoxy(11, 22);//C#
				cin >> CSharp;
				WIUtility::Gotoxy(16, 25);//Network
				cin >> Network;
				WIUtility::Gotoxy(14, 28);//Unity
				cin >> Unity;
				//패킷 구성
				{
				_WorkData SGData('S', 'G', 99, ID, SecretKey,
					ClassId, ClassNum, SName, SSex, STel,
					C, CPP, CSharp, Network, Unity,
					Ave, Total, UDate);
					if (0 < oSock.Send((char*)&SGData, sizeof(SGData)))
					{
						oSock.Receive((char*)&SGData, sizeof(SGData));
						if (SGData.header.pakID == 201) //201 인증 성공
						{
							AfxMessageBox("수정에 성공하였습니다.");
						}
						else
						{
							AfxMessageBox("수정에 실패하였습니다.");
						}
					}
				}
				break;
			case 53://5.학생검색 SS
				system("cls");
				MainLayout2();
				WIUtility::Gotoxy(11, 9); //반
				memset(ClassId, 0, sizeof(ClassId));
				cin >> ClassId;
				WIUtility::Gotoxy(18, 11); //이름
				memset(SName, 0, sizeof(SName));
				cin >> SName;
				{
					_WorkData SSData('S', 'S', 99, ID, SecretKey,
						ClassId, ClassNum, SName, SSex, STel,
						C, CPP, CSharp, Network, Unity,
						Ave, Total, UDate);
					if (0 < oSock.Send((char*)&SSData, sizeof(SSData)))
					{
						oSock.Receive((char*)&SSData, sizeof(SSData));
						if (SSData.header.pakID == 201) //201 인증 성공
						{
							AfxMessageBox("검색에 성공하였습니다.");
						}
						else
						{
							AfxMessageBox("검색에 실패하였습니다.");
						}
					}
					//화면에 출력
					system("cls");
					MainLayout5();
					cout << SSData.ClassId<<"\t"<<SSData.SName<<"\t"<<SSData.SSex<<"\t"<< SSData.STel<<"\t\t"<<SSData.C<<"\t"<< SSData.C++<<"\t"<<SSData.CSharp<<"\t"<<SSData.Network<<"\t"<<SSData.Unity<<"\t"<<SSData.Total<<"\t"<<SSData.Ave << endl;
				}
				break;
			}
		}
	}
}
