#pragma comment(lib,"Ws2_32.lib")
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
#include <WinSock2.h>
#include <windows.h>
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

	//����
	ClientSocket oSock("192.168.0.59", 9000);
	oSock.InitWinsock();
	oSock.InitSock();
	oSock.Connect();
	WIUtility::Gotoxy(2, 2);
	cout << "����Ϸ�";

	//�α���
	//1. �α��η��̾ƿ�
	Display::DrawRect(Point(1, 1), Point(140, 35));
	Display::DrawRect(Point(40, 12), Point(70, 18));
	Display::DrawRect(Point(47, 15), Point(55, 5));
	Display::DrawRect(Point(47, 22), Point(55, 5));
	WIUtility::Gotoxy(48, 14);
	cout << "ID" << endl;
	WIUtility::Gotoxy(48, 21);
	cout << "PASSWORD" << endl;

	//2.�α���
	while (1)
	{
		//ID
		WIUtility::Gotoxy(50, 17);
		cin >> buff;
		sprintf(str, "%s", buff);

		//PW��IDó�� �޳���...
		WIUtility::Gotoxy(50, 24);
		memset(buff, 0, sizeof(buff));
		cin >> buff;
		char str2[20];
		sprintf(str2, "%s", buff);

		_Login pkLogin('A', 'L', '.', str, str2);
		if (0 < oSock.Send((char*)&pkLogin, sizeof(pkLogin)))
		{

			oSock.Receive((char*)&pkLogin, sizeof(pkLogin));
			cout << pkLogin.ToString() << endl;

			if (pkLogin.header.SecretKey = 'T')
				break;
			else
				WIUtility::Gotoxy(48, 10);
			cout << "�ٽ��Է�";
		}
	}

	if (1)//�α��μ���
	{
		////���� ���̾ƿ�
		system("cls");
		Display::DrawRect(Point(1, 1), Point(140, 35));
		Display::DrawXLine(Point(1, 7), 140);
		Display::DrawXLine(Point(1, 30), 140);
		WIUtility::Gotoxy(4, 4);
		cout << "�б� �� �Ŵ��� ����" << endl;

		WIUtility::Gotoxy(4, 9);
		cout << "�л� ���" << endl;
		WIUtility::Gotoxy(4, 11);
		//cout << "�⼮��ȣ\t�̸�\t\tC\t\tC++\t\tC#\t\tNetwork\t\tUnity\t\tTotal\t\tAvg" << endl;
		WIUtility::Gotoxy(4, 31);
		cout << "�޴� ����" << endl;
		WIUtility::Gotoxy(4, 33);
		cout << "1.�л����\t\t2.�л�����\t\t3.�л�����\t\t4.��������\t\t5.�л��˻�\t\t6.�������" << endl;


		//�޴�����
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
				cout << "�л� ���" << endl;
				WIUtility::Gotoxy(4, 9);
				cout << "�л� �̸�: " << endl;
				WIUtility::Gotoxy(4, 33);
				cout << "1.�л����\t\t2.�л�����\t\t3.�л�����\t\t4.��������\t\t5.�л��˻�\t\t6.�������" << endl;
				WIUtility::Gotoxy(15, 9);// Ŀ���̵�
				memset(buff, 0, sizeof(buff));// �Է¹ޱ�
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
				cout << "�л� ����" << endl;
				WIUtility::Gotoxy(4, 33);
				cout << "1.�л����\t\t2.�л�����\t\t3.�л�����\t\t4.��������\t\t5.�л��˻�\t\t6.�������" << endl;
				break;
			case 51:
				system("cls");
				Display::DrawRect(Point(1, 1), Point(140, 35));
				Display::DrawXLine(Point(1, 7), 140);
				Display::DrawXLine(Point(1, 30), 140);
				WIUtility::Gotoxy(4, 4);
				cout << "�л� ����" << endl;
				WIUtility::Gotoxy(4, 33);
				cout << "1.�л����\t\t2.�л�����\t\t3.�л�����\t\t4.��������\t\t5.�л��˻�\t\t6.�������" << endl;
				break;
			case 52:
				system("cls");
				Display::DrawRect(Point(1, 1), Point(140, 35));
				Display::DrawXLine(Point(1, 7), 140);
				Display::DrawXLine(Point(1, 30), 140);
				WIUtility::Gotoxy(4, 4);
				cout << "���� ����" << endl;
				WIUtility::Gotoxy(4, 33);
				cout << "1.�л����\t\t2.�л�����\t\t3.�л�����\t\t4.��������\t\t5.�л��˻�\t\t6.�������" << endl;
				break;
			case 53:
				system("cls");
				Display::DrawRect(Point(1, 1), Point(140, 35));
				Display::DrawXLine(Point(1, 7), 140);
				Display::DrawXLine(Point(1, 30), 140);
				WIUtility::Gotoxy(4, 4);
				cout << "�л� �˻�" << endl;
				WIUtility::Gotoxy(4, 10);
				cout << "�⼮��ȣ\t�̸�\t\tC\t\tC++\t\tC#\t\tNetwork\t\tUnity\t\tTotal\t\tAvg" << endl;
				WIUtility::Gotoxy(4, 33);
				cout << "1.�л����\t\t2.�л�����\t\t3.�л�����\t\t4.��������\t\t5.�л��˻�\t\t6.�������" << endl;
				break;

			case 54:
				system("cls");
				Display::DrawRect(Point(1, 1), Point(140, 35));
				Display::DrawXLine(Point(1, 7), 140);
				Display::DrawXLine(Point(1, 30), 140);
				WIUtility::Gotoxy(4, 4);
				cout << "���� ���" << endl;
				WIUtility::Gotoxy(4, 33);
				cout << "1.�л����\t\t2.�л�����\t\t3.�л�����\t\t4.��������\t\t5.�л��˻�\t\t6.�������" << endl;
				break;
			}
		}

	}


	////�α��ν���
	//else
	//Display::DrawRect(Point(1, 1), Point(140, 35));
//	AfxMessageBox("������ ����");
}
