#include <iostream>
#include "..\Public\WIDisplay.h"
#include "..\Public\WIUtility.h"

using namespace std;

//�α��� ȭ��
//1. �ܰ� �簢��
void LoginLayout()
{
	//���
	WIUtility::Gotoxy(2, 1);
	cout << "��";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 1);
		cout << "��";
	}
	WIUtility::Gotoxy(144, 1);
	cout << "��";

	//����
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(2, i);
		cout << "��";
	}
	//������
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(144, i);
		cout << "��";
	}
	//�ϴ�
	WIUtility::Gotoxy(2, 40);
	cout << "��";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 40);
		cout << "��";
	}
	WIUtility::Gotoxy(144, 40);
	cout << "��";

	//���� �簢��1
	//���
	WIUtility::Gotoxy(40, 13);
	cout << "��";

	for (int i = 21; i < 55; i++)
	{
		WIUtility::Gotoxy(2 * i, 13);
		cout << "��";
	}
	WIUtility::Gotoxy(110, 13);
	cout << "��";

	//����
	for (int i = 14; i<31; i++)
	{
		WIUtility::Gotoxy(40, i);
		cout << "��";
	}
	////������
	for (int i = 14; i<31; i++)
	{
		WIUtility::Gotoxy(110, i);
		cout << "��";
	}
	//�ϴ�
	WIUtility::Gotoxy(40, 31);
	cout << "��";
	for (int i = 21; i < 55; i++)
	{
		WIUtility::Gotoxy(2 * i, 31);
		cout << "��";
	}
	WIUtility::Gotoxy(110, 31);
	cout << "��";


	//ID �Է�ĭ
	WIUtility::Gotoxy(53, 15);
	cout << "ID";
	WIUtility::Gotoxy(50, 16);
	cout << "��";

	for (int i = 26; i < 50; i++)
	{
		WIUtility::Gotoxy(2 * i, 16);
		cout << "��";
	}
	WIUtility::Gotoxy(100, 16);
	cout << "��";

	//����
	for (int i = 17; i<20; i++)
	{
		WIUtility::Gotoxy(50, i);
		cout << "��";
	}
	//������
	for (int i = 17; i<20; i++)
	{
		WIUtility::Gotoxy(100, i);
		cout << "��";
	}
	//�ϴ�
	WIUtility::Gotoxy(50, 20);
	cout << "��";
	for (int i = 26; i < 50; i++)
	{
		WIUtility::Gotoxy(2 * i, 20);
		cout << "��";
	}
	WIUtility::Gotoxy(100, 20);
	cout << "��";



	//pw �Է�ĭ
	WIUtility::Gotoxy(53, 23);
	cout << "PASSWORD";
	WIUtility::Gotoxy(50, 24);
	cout << "��";

	for (int i = 26; i < 50; i++)
	{
		WIUtility::Gotoxy(2 * i, 24);
		cout << "��";
	}
	WIUtility::Gotoxy(100, 24);
	cout << "��";

	//����
	for (int i = 25; i<28; i++)
	{
		WIUtility::Gotoxy(50, i);
		cout << "��";
	}
	//������
	for (int i = 25; i<28; i++)
	{
		WIUtility::Gotoxy(100, i);
		cout << "��";
	}
	////�ϴ�
	WIUtility::Gotoxy(50, 28);
	cout << "��";
	for (int i = 26; i < 50; i++)
	{
		WIUtility::Gotoxy(2 * i, 28);
		cout << "��";
	}
	WIUtility::Gotoxy(100, 28);
	cout << "��";
}

//����ȭ��
void MainLayout()
{
	//�ܺ� �簢��
	//���
	WIUtility::Gotoxy(2, 1);
	cout << "��";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 1);
		cout << "��";
	}
	WIUtility::Gotoxy(144, 1);
	cout << "��";

	//����
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(2, i);
		cout << "��";
	}
	//������
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(144, i);
		cout << "��";
	}
	//�ϴ�
	WIUtility::Gotoxy(2, 40);
	cout << "��";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 40);
		cout << "��";
	}
	WIUtility::Gotoxy(144, 40);
	cout << "��";

	//��� ������
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 6);
		cout << "��";
	}
	WIUtility::Gotoxy(2, 6);
	cout << "��";
	WIUtility::Gotoxy(144, 6);
	cout << "��";

	//�ϴ� ������
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 35);
		cout << "��";
	}
	WIUtility::Gotoxy(2, 35);
	cout << "��";
	WIUtility::Gotoxy(144, 35);
	cout << "��";
	//��� ����
	WIUtility::Gotoxy(6, 4);
	cout << "�б� �� �Ŵ��� ����" << endl;
	//�ϴ� �޴�
	WIUtility::Gotoxy(7, 38);
	cout << "1.�л����\t\t2.�л�����\t\t3.�л�����\t\t4.��������\t\t5.�л��˻�" << endl;
}

// �л� ���
void MainLayout1()
{
	//�ܺ� �簢��
	//���
	WIUtility::Gotoxy(2, 1);
	cout << "��";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 1);
		cout << "��";
	}
	WIUtility::Gotoxy(144, 1);
	cout << "��";

	//����
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(2, i);
		cout << "��";
	}
	//������
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(144, i);
		cout << "��";
	}
	//�ϴ�
	WIUtility::Gotoxy(2, 40);
	cout << "��";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 40);
		cout << "��";
	}
	WIUtility::Gotoxy(144, 40);
	cout << "��";

	//��� ������
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 6);
		cout << "��";
	}
	WIUtility::Gotoxy(2, 6);
	cout << "��";
	WIUtility::Gotoxy(144, 6);
	cout << "��";

	//�ϴ� ������
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 35);
		cout << "��";
	}
	WIUtility::Gotoxy(2, 35);
	cout << "��";
	WIUtility::Gotoxy(144, 35);
	cout << "��";
	//��� ����
	WIUtility::Gotoxy(7, 4);
	cout << "�л� ���" << endl;
	//�ϴ� �޴�
	WIUtility::Gotoxy(7, 38);
	cout << "1.�л����\t\t2.�л�����\t\t3.�л�����\t\t4.��������\t\t5.�л��˻�" << endl;
	WIUtility::Gotoxy(7, 9);
	cout << "��: " << endl;
	WIUtility::Gotoxy(7, 11);
	cout << "�л� �̸�: " << endl;
	WIUtility::Gotoxy(7, 13);
	cout << "����: " << endl;
	WIUtility::Gotoxy(7, 15);
	cout << "��ȭ��ȣ: " << endl;
	
	
}

//�л� ����
void MainLayout2()
{
	//�ܺ� �簢��
	//���
	WIUtility::Gotoxy(2, 1);
	cout << "��";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 1);
		cout << "��";
	}
	WIUtility::Gotoxy(144, 1);
	cout << "��";

	//����
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(2, i);
		cout << "��";
	}
	//������
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(144, i);
		cout << "��";
	}
	//�ϴ�
	WIUtility::Gotoxy(2, 40);
	cout << "��";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 40);
		cout << "��";
	}
	WIUtility::Gotoxy(144, 40);
	cout << "��";

	//��� ������
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 6);
		cout << "��";
	}
	WIUtility::Gotoxy(2, 6);
	cout << "��";
	WIUtility::Gotoxy(144, 6);
	cout << "��";

	//�ϴ� ������
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 35);
		cout << "��";
	}
	WIUtility::Gotoxy(2, 35);
	cout << "��";
	WIUtility::Gotoxy(144, 35);
	cout << "��";
	//��� ����
	WIUtility::Gotoxy(7, 4);
	cout << "�л� ����" << endl;
	//�ϴ� �޴�
	WIUtility::Gotoxy(7, 38);
	cout << "1.�л����\t\t2.�л�����\t\t3.�л�����\t\t4.��������\t\t5.�л��˻�" << endl;
	WIUtility::Gotoxy(7, 9);
	cout << "��: " << endl;
	WIUtility::Gotoxy(7, 11);
	cout << "�л� �̸�: " << endl;
}

//�л� ����
void MainLayout3()
{
	//�ܺ� �簢��
	//���
	WIUtility::Gotoxy(2, 1);
	cout << "��";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 1);
		cout << "��";
	}
	WIUtility::Gotoxy(144, 1);
	cout << "��";

	//����
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(2, i);
		cout << "��";
	}
	//������
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(144, i);
		cout << "��";
	}
	//�ϴ�
	WIUtility::Gotoxy(2, 40);
	cout << "��";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 40);
		cout << "��";
	}
	WIUtility::Gotoxy(144, 40);
	cout << "��";

	//��� ������
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 6);
		cout << "��";
	}
	WIUtility::Gotoxy(2, 6);
	cout << "��";
	WIUtility::Gotoxy(144, 6);
	cout << "��";

	//�ϴ� ������
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 35);
		cout << "��";
	}
	WIUtility::Gotoxy(2, 35);
	cout << "��";
	WIUtility::Gotoxy(144, 35);
	cout << "��";
	//��� ����
	WIUtility::Gotoxy(7, 4);
	cout << "�л� ����" << endl;
	//�ϴ� �޴�
	WIUtility::Gotoxy(7, 38);
	cout << "1.�л����\t\t2.�л�����\t\t3.�л�����\t\t4.��������\t\t5.�л��˻�" << endl;
	WIUtility::Gotoxy(7, 9);
	cout << "��: " << endl;
	WIUtility::Gotoxy(7, 11);
	cout << "�л� �̸�: " << endl;
	WIUtility::Gotoxy(7, 13);
	cout << "����: " << endl;
	WIUtility::Gotoxy(7, 15);
	cout << "��ȭ��ȣ: " << endl;

}

//���� ����
void MainLayout4()
{
	//�ܺ� �簢��
	//���
	WIUtility::Gotoxy(2, 1);
	cout << "��";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 1);
		cout << "��";
	}
	WIUtility::Gotoxy(144, 1);
	cout << "��";

	//����
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(2, i);
		cout << "��";
	}
	//������
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(144, i);
		cout << "��";
	}
	//�ϴ�
	WIUtility::Gotoxy(2, 40);
	cout << "��";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 40);
		cout << "��";
	}
	WIUtility::Gotoxy(144, 40);
	cout << "��";

	//��� ������
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 6);
		cout << "��";
	}
	WIUtility::Gotoxy(2, 6);
	cout << "��";
	WIUtility::Gotoxy(144, 6);
	cout << "��";

	//�ϴ� ������
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 35);
		cout << "��";
	}
	WIUtility::Gotoxy(2, 35);
	cout << "��";
	WIUtility::Gotoxy(144, 35);
	cout << "��";
	//��� ����
	WIUtility::Gotoxy(7, 4);
	cout << "���� ����" << endl;
	//�ϴ� �޴�
	WIUtility::Gotoxy(7, 38);
	cout << "1.�л����\t\t2.�л�����\t\t3.�л�����\t\t4.��������\t\t5.�л��˻�" << endl;
	WIUtility::Gotoxy(7, 10);
	cout << "��:" << endl;
	WIUtility::Gotoxy(7, 13);
	cout << "�̸�:" << endl;
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

//�л� �˻�
void MainLayout5()
{
	//�ܺ� �簢��
	//���
	WIUtility::Gotoxy(2, 1);
	cout << "��";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 1);
		cout << "��";
	}
	WIUtility::Gotoxy(144, 1);
	cout << "��";

	//����
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(2, i);
		cout << "��";
	}
	//������
	for (int i = 2; i<40; i++)
	{
		WIUtility::Gotoxy(144, i);
		cout << "��";
	}
	//�ϴ�
	WIUtility::Gotoxy(2, 40);
	cout << "��";
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 40);
		cout << "��";
	}
	WIUtility::Gotoxy(144, 40);
	cout << "��";

	//��� ������
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 6);
		cout << "��";
	}
	WIUtility::Gotoxy(2, 6);
	cout << "��";
	WIUtility::Gotoxy(144, 6);
	cout << "��";

	//�ϴ� ������
	for (int i = 2; i < 72; i++)
	{
		WIUtility::Gotoxy(2 * i, 35);
		cout << "��";
	}
	WIUtility::Gotoxy(2, 35);
	cout << "��";
	WIUtility::Gotoxy(144, 35);
	cout << "��";
	//��� ����
	WIUtility::Gotoxy(7, 4);
	cout << "�л� �˻�" << endl;
	//�ϴ� �޴�
	WIUtility::Gotoxy(7, 38);
	cout << "1.�л����\t\t2.�л�����\t\t3.�л�����\t\t4.��������\t\t5.�л��˻�" << endl;
	WIUtility::Gotoxy(10, 8);
	cout << "��\t�̸�\t ����\t ��ȭ��ȣ\t\t C\t C++\t C#\t Network\tUnity\t Total\t Avg" << endl;
}
