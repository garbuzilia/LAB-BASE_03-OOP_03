#include <iostream>
#include <time.h>

using namespace std;

//�������� ��������� ���� ����������: �������, �������, �������, ������� 
 
void vivod(int n, int* x)
{
    for (int i = 0; i < n; i++)
    {
        cout << x[i] << " ";
    }
    cout << endl;
}

//���������� ��������
void Sliyan(int n, int* x)
{
    int i, j, k, t, s, Fin1, Fin2;
    int* tmp = new int[n];
    k = 1;
    while (k < n) 
    {
        t = 0;
        s = 0;
        while (t + k < n) 
        {
            Fin1 = t + k;
            Fin2 = (t + 2 * k < n ? t + 2 * k : n);
            i = t;
            j = Fin1;
            for (; i < Fin1 && j < Fin2; s++) 
            {
                if (x[i] < x[j]) 
                {
                    tmp[s] = x[i];
                    i++;
                }
                else 
                {
                    tmp[s] = x[j];
                    j++;
                }
            }
            for (; i < Fin1; i++, s++)
            {
                tmp[s] = x[i];
            }          
            for (; j < Fin2; j++, s++)
            {
                tmp[s] = x[j];
            }                
            t = Fin2;
        }
        k *= 2;
        for (s = 0; s < t; s++)
            x[s] = tmp[s];
    }
    delete [] tmp;
    
}
//������� ����������
void Bistro(int left, int right, int* x) 
{
    int i, j, m, h;
    i = left;
    j = right;
    m = x[(i + j + 1) / 2];
    do {
        while (x[i] < m) i++;
        while (x[j] > m) j--;
        if (i <= j) {
            swap(x[i], x[j]);
            i++;
            j--;
        }
    } while (i <= j);
    if (left < j)
        Bistro(left, j, x);
    if (i < right)
        Bistro(i, right, x);
    
}
//���������� ���������
void Podschet(int n, int* x)
{
    int Max = x[0];

    for (int i = 0; i < n; i++)
    {
        if (x[i] > Max)
        {
            Max = x[i];
        }
    }

    int* c = new int[Max];

    for (int i = 0; i <= Max; i++) 
    {
        c[i] = 0;
    }

    for (int i = 0; i < n; i++) 
    {
        c[x[i]]++;
    }
        
    for (int j = 0, i = 0; j <= Max; j++) 
    {
        while (c[j] != 0) 
        {
            x[i] = j;
            c[j]--;
            i++;
        }
    }
    
}
//������� ����������
void Blochn(int n, int* x)
{    
    int** buckets = new int* [n];
    for (int i = 0; i < n; i++)
        buckets[i] = new int[n/2];

    int ostatok, temp;
    int count;     

    for (int f = 1; f <= 100; f *= 10)     
    {
        for (int i = 0; i < n / 2; i++)     
            for (int j = 0; j < n; j++)
                buckets[i][j] = -1;
        
        count = 0;     

        for (int i = 0; i < n; i++)     
        {                                      

            temp = x[i] / f;
            ostatok = temp % 10;
            buckets[ostatok][i] = x[i];

        }

        for (int i = 0; i < n / 2; i++)     
        {                                      

            for (int j = 0; j < n; j++)
            {

                if (buckets[i][j] != -1)     
                {

                    x[count] = buckets[i][j];     
                    count++;     
                }
            }
        }
    }    
}

int main()
{
    setlocale(0,"");
    srand(time(NULL));
    int n,vibor; 
    bool loop = 1;
    cout << "������ ������� - "; cin >> n;
    cout << endl;
    int* x = new int[n];
    while (loop == 1)
    {
        cout << "����������:" << endl
            << "1) ���������� ��������" << endl
            << "2) ������� ����������" << endl
            << "3) ���������� ���������" << endl
            << "4) ������� ����������" << endl
            << "5) �������� ������ �������" << endl
            << "����� - ";
        cin >> vibor;
        
        if (vibor == 1)
        {
            cout << endl << "��������� ������" << endl;
            for (int i = 0; i < n; i++)
            {
                x[i] = rand() % 20;
                cout << x[i] << " ";
            }
            cout << endl << endl << "��������������� ������" << endl;
            Sliyan(n, x);
            vivod(n, x);
            system("pause");
            system("cls");
        }
        else if (vibor == 2)
        {
            cout << endl << "��������� ������" << endl;
            for (int i = 0; i < n; i++)
            {
                x[i] = rand() % 20;
                cout << x[i] << " ";
            }
            cout << endl << endl << "��������������� ������" << endl;
            Bistro(0, n - 1, x);
            vivod(n, x);
            system("pause");
            system("cls");
        }
        else if (vibor == 3)
        {
            cout << endl << "��������� ������" << endl;
            for (int i = 0; i < n; i++)
            {
                x[i] = rand() % 20;
                cout << x[i] << " ";
            }
            cout << endl << endl << "��������������� ������" << endl;
            Podschet(n, x);
            vivod(n, x);
            system("pause");
            system("cls");
        }
        else if (vibor == 4)
        {
            while (n < 20)
            {                
                cout << "��� ���� ���������� ����� ������ 20+ ���������" << endl;
                cout << "����� ������ ������� - "; cin >> n;         
                int* x = new int[n];                
            }
            
            cout << endl << "��������� ������" << endl;
            for (int i = 0; i < n; i++)
            {
                x[i] = rand() % 20;
                cout << x[i] << " ";
            }
            cout << endl << endl << "��������������� ������" << endl;
            Blochn(n, x);
            vivod(n, x);
            system("pause");
            system("cls");
            
        }
        if (vibor == 5)
        {
            cout << "������ ������� - "; cin >> n;
            cout << endl;
            int* x = new int[n];
            system("cls");
        }
        else if ((vibor > 5) || (vibor < 0))
        {
            loop = 0;
        }
    }   
    return 0;
}
