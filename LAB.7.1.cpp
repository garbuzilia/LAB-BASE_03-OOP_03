#include <iostream>

using namespace std;

/*
12. Создать функции перегрузки (Функции с одинаковыми именами):
а) для деления десятичных дробей;
б) для деления обыкновенных дробей.
*/

float delen (float a, float b)
{
    cout << a << " : " << b << " = " << a/b;
    return 0;
}

int delen (int aVerh, int aNiz, int bVerh, int bNiz)
{
    cout << aVerh << "/" << aNiz << " : "
         << bVerh << "/" << bNiz << " = "
         << aVerh << "*" << bNiz << "/" << aNiz << "*" << bVerh << " = "
         << aVerh*bNiz << "/" << aNiz*bVerh;
    if ((int)((aVerh*bNiz) / (aNiz*bVerh)) > 0)
    {
        cout << " = " << (int)((aVerh*bNiz) / (aNiz*bVerh))
             << " + " << (aVerh*bNiz) - (int)((aVerh*bNiz) / (aNiz*bVerh))*(aNiz*bVerh)
             << "/" << aNiz*bVerh;
    }
    else cout << "";
    return 0;
}

int main()
{
    setlocale(0,"");

    string stroka_A;
    string stroka_B;
    cout << "Введите первый элемент деления - ";  getline(cin, stroka_A);
    cout << "Введите второй элемент деления - ";  getline(cin, stroka_B);

    if ((stroka_A.find("/") != -1) && (stroka_B.find("/") != -1))
    {
        string A_verh, A_niz;
        string B_verh, B_niz;

        A_verh.assign(stroka_A,0,stroka_A.find("/"));
        A_niz.assign(stroka_A,stroka_A.find("/")+1,stroka_A.size());

        B_verh.assign(stroka_B,0,stroka_B.find("/"));
        B_niz.assign(stroka_B,stroka_B.find("/")+1,stroka_B.size());

        int A_verh_int = stoi(A_verh);
        int A_niz_int  = stoi(A_niz);

        int B_verh_int = stoi(B_verh);
        int B_niz_int  = stoi(B_niz);

        cout << "\nРезультат деления - ";
        delen(A_verh_int,A_niz_int,B_verh_int,B_niz_int);
    }
    else if ((stroka_A.find("/") == -1) && (stroka_B.find("/") != -1))
    {
        cout << "ERROR - Дроби разные" << endl;
    }
    else if ((stroka_A.find("/") != -1) && (stroka_B.find("/") == -1))
    {
        cout << "ERROR - Дроби разные" << endl;
    }
    else if ((stroka_A.find("/") == -1) && (stroka_B.find("/") == -1))
    {
        float A_int = stof(stroka_A);
        float B_int = stof(stroka_B);

        cout << "\nРезультат деления - ";
        delen(A_int,B_int);
    }

    return 0;
}
