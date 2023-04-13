#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <Windows.h>


using namespace std;

/*
12.	��������� "����������� ����":
-	��������;
-	�����;
-	�����������������;
-	����.
������� ������ ������� � �������� ������������������, �������� 2 �������� ����� �������� � �������� �������.
*/

/*
1.	��� ���������� ����� ����� ������������ �������, ����������� ���� ���������,
    ���������� � �������� ����. �������� ��������� ��������� �������� � �����-�����.
    ��� ����� ����� ������������ �������� >> � ������� gets().

2.	��� ����� �������� ����� ����������� ���� �� ������-��� ����������:
-	���� ������� ���������� ���������� �������� (�� ����� 5);
-	����  �� ��������� ��������� � �������� ������-����� ���������;
-	������ � ������������� � ������������� ���������� ����.

3.	��� ������ ��������� �  ���� � ������ ��������� �� ����� ������������ �������
    �������� �����/������ fread � fwrite.

4.	��� ��������/ ���������� ��������� � ����  ��������-���� ��������������� ����.

*/

/* ���������� ������. */

void new_lib();
void show_lib();
void del_time_lib();
void plus_two_to_lib();

FILE* fp;
FILE* ft;

struct MP3_Disc
{
    string name;
    string autor;
    int play_time;
    int price;
};

int main()
{
    setlocale(0, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //int n;
    bool loop = 1;
    int vibor;


    
    while (loop != 0)
    {
        cout << "��� ����� �������:" << endl
            << "1) ������� ����� ���������� ������" << endl
            << "2) ������� ������������ ����������" << endl
            << "3) ������� ������ ������� � �������� ������������������" << endl
            << "4) �������� 2 �������� ����� �������� � �������� �������" << endl;
        cout << "����� - "; cin >> vibor;
        system("cls");
        if (vibor == 1) //������� ����� ���������� ������
        {
            new_lib();
        }
        else if (vibor == 2) //������� ������������ ����������
        {
            show_lib();            
        }
        else if (vibor == 3) //������� ������ ������� � �������� ������������������
        {
            del_time_lib();            
        }
        else if (vibor == 4) //�������� 2 �������� ����� �������� � �������� �������
        {
            plus_two_to_lib();
        }
        else if (vibor < 0 || vibor > 4) loop = 0;
    }
    return 0;
}

void new_lib()
{
    int n;
    cout << "������� ������ - "; cin >> n; cout << endl;
    MP3_Disc* CD = new MP3_Disc[n];
    for (int i = 0; i < n; i++)
    {
        cout << "���� �" << i + 1 << endl;
        cout << "�������� - "; cin.get(); getline(cin, CD[i].name);
        cout << "����� - "; getline(cin, CD[i].autor);
        cout << "����������������� - "; cin >> CD[i].play_time;
        cout << "���� - "; cin >> CD[i].price;
        cout << endl;
    }

    if ((fp = fopen("test", "wb")) == NULL) {
        printf("������ ��� �������� �����.\n");
        exit(1);
    }

    fwrite(&n, sizeof(int), 1, fp);

    for (int i = 0; i < n; i++)
        if (fwrite(&CD[i], sizeof(struct MP3_Disc), 1, fp) != 1)
        {
            cout << "������ ��� ������ �����" << endl;
        }

    fclose(fp);
    system("pause");
    system("cls");
}

void show_lib()
{
    int n;

    if ((fp = fopen("test", "rb")) == NULL)
    {
        printf("������ ��� �������� �����.\n");
        exit(1);
    }

    fread(&n, sizeof(int), 1, fp);
    MP3_Disc* CD = new MP3_Disc[n];
    for (int i = 0; i < n; i++)
    {
        if (fread(&CD[i], sizeof(struct MP3_Disc), 1, fp) != 1)
        {
            cout << "������ ��� ������ �����" << endl;
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << endl
            << "���� �" << i + 1 << endl
            << "�������� - " << CD[i].name << endl
            << "����� - " << CD[i].autor << endl
            << "����������������� - " << CD[i].play_time << endl
            << "���� - " << CD[i].price
            << endl;
    }

    fclose(fp);
    system("pause");
    system("cls");
}

void del_time_lib()
{
    int n;
    bool perviy = 0;
    int ex_time;
    int nomer;


    cout << "����� ����� ����� - "; cin >> ex_time;

    if ((fp = fopen("test", "rb")) == NULL)
    {
        printf("������ ��� �������� �����.\n");
        exit(1);
    }

    fread(&n, sizeof(int), 1, fp);
    MP3_Disc* CD = new MP3_Disc[n];
    for (int i = 0; i < n; i++)
    {
        if (fread(&CD[i], sizeof(struct MP3_Disc), 1, fp) != 1)
        {
            cout << "������ ��� ������ �����" << endl;
        }
    }

    for (int i = 0; (i < n) && (perviy == 0); i++)
    {
        if (CD[i].play_time == ex_time)
        {
            nomer = i;
            perviy = 1;
        }
    }

    if ((ft = fopen("temp", "wb")) == NULL) {
        printf("������ ��� �������� �����.\n");
        exit(1);
    }

    fwrite(&n, sizeof(int), 1, ft);

    for (int i = 0; i < nomer; i++)
        if (fwrite(&CD[i], sizeof(struct MP3_Disc), 1, ft) != 1)
        {
            cout << "������ ��� ������ �����" << endl;
        }

    for (int i = nomer + 1; i < n; i++)
        if (fwrite(&CD[i], sizeof(struct MP3_Disc), 1, ft) != 1)
        {
            cout << "������ ��� ������ �����" << endl;
        }

    fclose(fp);
    fclose(ft);

    if ((ft = fopen("temp", "rb")) == NULL)
    {
        printf("������ ��� �������� �����.\n");
        exit(1);
    }

    fread(&n, sizeof(int), 1, fp);

    n--;

    for (int i = 0; i < n; i++)
    {
        if (fread(&CD[i], sizeof(struct MP3_Disc), 1, ft) != 1)
        {
            cout << "������ ��� ������ �����" << endl;
        }
    }

    if ((fp = fopen("test", "wb")) == NULL) {
        printf("������ ��� �������� �����.\n");
        exit(1);
    }

    fwrite(&n, sizeof(int), 1, fp);

    for (int i = 0; i < n; i++)
        if (fwrite(&CD[i], sizeof(struct MP3_Disc), 1, fp) != 1)
        {
            cout << "������ ��� ������ �����" << endl;
        }

    fclose(fp);
    fclose(ft);

    system("pause");
    system("cls");
}

void plus_two_to_lib()
{
    int n;

    int nomer;
    cout << "����� �������� - "; cin >> nomer; cout << endl;

    if ((fp = fopen("test", "rb")) == NULL)
    {
        printf("������ ��� �������� �����.\n");
        exit(1);
    }

    fread(&n, sizeof(int), 1, fp);
    MP3_Disc* CD = new MP3_Disc[n + 2];
    for (int i = 0; i < n; i++)
    {
        if (fread(&CD[i], sizeof(struct MP3_Disc), 1, fp) != 1)
        {
            cout << "������ ��� ������ �����" << endl;
        }
    }

    for (int i = n; i < n + 2; i++)
    {
        cout << "���� �" << i + 1 << endl;
        cout << "�������� - "; cin.get(); getline(cin, CD[i].name);
        cout << "����� - "; getline(cin, CD[i].autor);
        cout << "����������������� - "; cin >> CD[i].play_time;
        cout << "���� - "; cin >> CD[i].price;
        cout << endl;
    }

    if ((ft = fopen("temp", "wb")) == NULL) {
        printf("������ ��� �������� �����.\n");
        exit(1);
    }

    fwrite(&n, sizeof(int), 1, ft);

    for (int i = 0; i < nomer; i++)
        if (fwrite(&CD[i], sizeof(struct MP3_Disc), 1, ft) != 1)
        {
            cout << "������ ��� ������ �����" << endl;
        }
    for (int i = n; i < n + 2; i++)
        if (fwrite(&CD[i], sizeof(struct MP3_Disc), 1, ft) != 1)
        {
            cout << "������ ��� ������ �����" << endl;
        }
    for (int i = nomer; i < n; i++)
        if (fwrite(&CD[i], sizeof(struct MP3_Disc), 1, ft) != 1)
        {
            cout << "������ ��� ������ �����" << endl;
        }

    fclose(fp);
    fclose(ft);

    if ((ft = fopen("temp", "rb")) == NULL)
    {
        printf("������ ��� �������� �����.\n");
        exit(1);
    }

    fread(&n, sizeof(int), 1, fp);

    n += 2;

    for (int i = 0; i < n; i++)
    {
        if (fread(&CD[i], sizeof(struct MP3_Disc), 1, ft) != 1)
        {
            cout << "������ ��� ������ �����" << endl;
        }
    }

    if ((fp = fopen("test", "wb")) == NULL) {
        printf("������ ��� �������� �����.\n");
        exit(1);
    }

    fwrite(&n, sizeof(int), 1, fp);

    for (int i = 0; i < n; i++)
        if (fwrite(&CD[i], sizeof(struct MP3_Disc), 1, fp) != 1)
        {
            cout << "������ ��� ������ �����" << endl;
        }

    fclose(fp);
    fclose(ft);

    system("pause");
    system("cls");
}