#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int sluchay()
{
    int n;
    cout << "������� ��������� � �������? - ";    cin >> n;
    int* Dmas = new int[n];

    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        Dmas[i] = rand() % 100;
    }

    for (int i = 0; i < n; i++)
    {
        cout << i+1 << ") " << Dmas[i] << endl;
    }
    cout << "-------------------------------------------" << endl;
    delete [] Dmas;
    return 0;
}

int upor()
{
    int n, a;
    bool f = 1;
    cout << "������� ��������� � �������? - ";    cin >> n;
    int* Dmas = new int[n];

    cout << "����� ������ �������� ������� �������� �������:\n";
    for (int i = 0; i < n; i++)
    {
        cout << i+1 <<" - ";
        cin >> a;
        Dmas[i] = a;
    }
    for (int i = 0; i < n-1;i++)
    {
        if (Dmas[i] > Dmas [i+1]) f = 0;
    }
    if (f == 1)
    {
        cout << "���������� �� �����������";
    }
    else cout << "�� ����������";
    cout << "-------------------------------------------" << endl;
    delete [] Dmas;
    return 0;
}

int rivers()
{
    int n,t,q;
    cout << "������� ��������� � ������� - ";    cin >> n;
    int* Dmas = new int[n];

    srand(time(NULL));
    t = n-1;
    for (int i = 0; i < n; i++)
    {
        Dmas[i] = rand() % 10;
        cout << Dmas[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < n/2; i++)
    {
        q = Dmas[i];
        Dmas[i] = Dmas[t];
        Dmas[t] = q;
        t--;
    }
    for (int i = 0; i < n; i++)
    {
        cout << Dmas[i] << " ";
    }
    cout << endl;
    cout << "-------------------------------------------" << endl;
    delete [] Dmas;
    return 0;
}

int riversV2()
{
    int n,q;
    int P,I,C;
    cout << "������� ��������� � ������� - ";    cin >> n;
    int* Dmas = new int[n];

    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        Dmas[i] = rand() % 10;
        cout << Dmas[i] << " ";
    }
    cout << endl;
    cout << "������� ��������� ������ � ����� �������:" << endl;
    cout << "���. - "; cin >> P; P--;
    cout << "���. - "; cin >> I; I--;
    C = I-P;
    for (int i = 1; i <= C/2; i++)
    {
        q = Dmas[P];
        Dmas[P] = Dmas[I];
        Dmas[I] = q;
        P++;
        I--;
    }
    for (int i = 0; i < n; i++)
    {
        cout << Dmas[i] << " ";
    }
    cout << endl;
    cout << "-------------------------------------------" << endl;
    delete [] Dmas;
    return 0;
}

int sortir()
{
    int n,ch;

    cout    << "����������:\n"
            << "1) ���������\n"
            << "2) �������\n"
            << "3) ���������\n"
            << "����� - ";
    cin >> ch;


    cout << "������� ��������� � ������� - "; cin >> n;
    int* Dmas = new int[n];

    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        Dmas[i] = rand() % 10;
        cout << Dmas[i] << " ";
    }
    cout << endl;

    if (ch == 1)
    {
        int q;
        bool f = 0;
        while (f == 0)
        {
            f = 1;
            for (int i = 0; i < n-1; i++)
        {
            if (Dmas[i]>Dmas[i+1])
            {
              q = Dmas[i];
              Dmas[i] = Dmas[i+1];
              Dmas[i+1] = q;
            }
        }
            for (int i = 0; i < n-1; i++)
        {
            if (Dmas[i]>Dmas[i+1])
            {
                f = 0;
            }
        }
        }

    }
    else if (ch == 2)
    {

        int q,mi;

            for (int i = 0; i<n;i++)
            {
                mi = Dmas[i];
                for (int j=i;j<n;j++)
                {
                    if (Dmas[j]<mi)
                    {
                        q = j;
                        mi = Dmas[j];
                        Dmas[q] = Dmas[i];
                        Dmas[i] = mi;
                    }
                }
            }
    }
    else if (ch == 3)
    {

    int q;

    for(int i=1;i<n;i++)
    {
        for(int j=i;j>0 && Dmas[j-1]>Dmas[j];j--)
        {
            q = Dmas[j];
            Dmas[j] = Dmas[j-1];
            Dmas[j-1] = q;
        }
    }

    }

    for (int i = 0; i < n; i++)
    {
        cout << Dmas[i] << " ";
    }
    cout << endl;
    cout << "-------------------------------------------" << endl;

    delete [] Dmas;
    return 0;
}

int main()
{
    setlocale(0,"");
    bool loop = 1;
    while (loop == 1)
    {
        cout    << "��� ����� �� ������:\n"
                << "1) ���������� � ���������������� �������\n"
                << "2) ���������, ���������� �� ������ M �� �����������\n"
                << "3) ������, ������� �� ������ - reverse �������\n"
                << "4) ����������� ����� ������� �� �������� � �������� P\n"
                << "5) ����������: ���������, �������, �������� (�� ���������)\n" << endl
                << "����� - ";
    int choice;
    cin >> choice;
    switch(choice)
    {
        case 1: sluchay(); break;
        case 2: upor(); break;
        case 3: rivers(); break;
        case 4: riversV2(); break;
        case 5: sortir(); break;
        default: loop = 0;
    }

    }

    return 0;
}
