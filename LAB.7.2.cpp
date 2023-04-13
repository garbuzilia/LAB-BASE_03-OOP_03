#include <iostream>
#include <stdarg.h>
#include <time.h>
using namespace std;

/*
12. 	�������� ������� � ���������� ������ ���������� ��� ��������
        ����� �� ���������� ������� ��������� � ������������.
        �������� ���������� ������� main, ����-��� ���������� � ����
        ������� �� ����� ���� ��� � ��-��������� ���������� 3, 5, 8.
*/

int perevod(int n, ...)
{
    va_list chisla;
    va_start (chisla,n);
    for (int i = 0; i < n; i++)
    {
        int q = 0; int k = 1; int h = va_arg(chisla,int);
        cout << endl << h << " = ";

        while (h)
    {
        q+=h%8*k;
        h/=8;
        k*=10;
    }
        cout << q << " ";
    }
    va_end(chisla);
    cout << endl;
    return 0;
}

int main()
{
    setlocale(0,"");
    srand(time(NULL));
    int A[8];
    for (int i = 0; i<8;i++)
    {
        A[i] = rand() % 100;
        cout << i+1 << "-�� ����� - " << A[i] << endl;
    }
    cout << endl;
    cout << "����� � ��-��������� ���������� 3 - ";
    perevod(3,A[0],A[1],A[2]);
    cout << "����� � ��-��������� ���������� 5 - ";
    perevod(5,A[0],A[1],A[2],A[3],A[4]);
    cout << "����� � ��-��������� ���������� 8 - ";
    perevod(8,A[0],A[1],A[2],A[3],A[4],A[5],A[6],A[7]);
    return 0;
}
