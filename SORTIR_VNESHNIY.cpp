// SORTIR_VNESHNIY.cpp 
// Сортировка сбалансированным слиянием

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

string F1_str = "F1.txt";
string F2_str = "F2.txt";
string F_orig_str = "F_orig.txt";
string F_temp_str = "F_temp.txt";

string menu[] =
{
        "Что нужно сделать:",
        "1) Задать оригинальный файл",
        "2) Выполнить сортировку",
        "3) Показать оригинальный файл",
        "4) Показать отсортированный файл",
        "5) Сделать один шаг и показать файлы 1 и 2"
};

void sborka();

void sozdanie_ochistka(int n)
{
    if (n == 1)
    {
        ofstream F_orig("F_orig.txt");    F_orig.close();
        ofstream F_temp("F_temp.txt");    F_temp.close();
        ofstream F1("F1.txt");            F1.close();
        ofstream F2("F2.txt");            F2.close();
        ofstream F_fin("F_fin.txt");      F_fin.close();
    }
    if (n == 2)
    {
        ofstream F1("F1.txt");            F1.close();
        ofstream F2("F2.txt");            F2.close();
    }
}

void scan_orig()
{
    fstream F_orig("F_orig.txt");
    fstream F_fin("F_fin.txt");
    string stroka;
    int q = 0;
    while (!F_orig.eof())
    {
        getline(F_orig, stroka);
        q++;
    }
    F_fin.clear();
    F_fin.seekg(0);
    for(int i = 1; i <= q; i++)
    {
        getline(F_orig, stroka);
        F_fin << stroka;
        if (i != q) F_fin << endl;
    }
}

void new_orig_file()
{
    sozdanie_ochistka(1);

    fstream F_orig("F_orig.txt");
    fstream F_fin("F_fin.txt");
    string vvod = "Start";
    string orig_stroka = "";

    cout << "Вводите значения. 0 = окончание ввода" << endl;
    getline(cin, vvod);
    if (vvod != "0")
    {
        F_orig << vvod; F_fin << vvod;
    }
    while (vvod != "0")
    {
        getline(cin, vvod);
        if (vvod != "0")
        {
            F_orig << endl; F_fin << endl;
            F_orig << vvod; F_fin << vvod;
        }
    }
    F_orig.close();
}

void print_file(string filename)
{
    fstream F_print(filename);
    string stroka;
    if (F_print.peek() == EOF) cout << "Файл пуст" << endl;
    else
    {
        while (!F_print.eof())
        {
            getline(F_print, stroka);
            cout << stroka << " ";
        }
    }
    cout << endl;
    F_print.close();
}

string vizov_file(string file1, string file2, int index)
{
    if (index == 1) return file1;
    if (index == 2) return file2;
}

void sortir_sbalans_slian_1_shag()
{
    fstream F_fin("F_fin.txt");
    fstream file;

    sozdanie_ochistka(2);

    //fstream F1("F1.txt");
    //fstream F2("F2.txt");

    int el1;
    int el2;

    string stroka;

    getline(F_fin, stroka);
    file.open(F1_str);    file << stroka << endl;   file.close();
    el1 = stoi(stroka);
    //getline(F_fin, stroka);
    //el2 = stoi(stroka);
    int n = 1;
    int seria = 0;
    for (; !F_fin.eof();)
    {
        seria = 1;
        getline(F_fin, stroka);
        if (stoi(stroka) >= el1)
        {
            file.open(vizov_file(F1_str, F2_str, n), ios_base::app);
            file << stroka << endl;
            file.close();
        }
        else
        {
            seria++;
            file.open(vizov_file(F1_str, F2_str, n), ios_base::app);
            file << "+" << endl;
            file.close();
            if (n == 1) n = 2;
            else if (n == 2) n = 1;
            file.open(vizov_file(F1_str, F2_str, n), ios_base::app);
            file << stroka << endl;
            file.close();
        }
        el1 = stoi(stroka);
    }
    cout << "Колличество серий - " << seria << endl;
}

void sortir_sbalans_slian()
{
    fstream F_fin("F_fin.txt");
    fstream file;

    sozdanie_ochistka(2);
    fstream F1("F1.txt");
    fstream F2("F2.txt");

    int el1;
    int el2;

    string stroka;

    getline(F_fin, stroka);
    file.open(F1_str);    file << stroka << endl;   file.close();
    el1 = stoi(stroka);
    //getline(F_fin, stroka);
    //el2 = stoi(stroka);
    int n = 1;
    int seria = 0;
    
    while (seria != 1)
    {
        seria = 1;
        int plus_counter = 0;
        F_fin.clear();
        //F_fin.seekg(0);
        for (; !F_fin.eof();)
        {
            getline(F_fin, stroka);
            if (stoi(stroka) >= el1)
            {
                file.open(vizov_file(F1_str, F2_str, n), ios_base::app);
                file << stroka << endl;
                file.close();
            }
            else
            {
                seria++;
                file.open(vizov_file(F1_str, F2_str, n), ios_base::app);
                file << "+" << endl;
                file.close();
                if (n == 1) n = 2;
                else if (n == 2) n = 1;
                file.open(vizov_file(F1_str, F2_str, n), ios_base::app);
                file << stroka << endl;
                file.close();
            }
            el1 = stoi(stroka);
        }
        sborka();
        
        /*F1.clear();
        F1.seekg(0);

        while (!F1.eof())
        {
            getline(F1, stroka);
            if (stroka == "+") plus_counter++;
        }

        F2.clear();
        F2.seekg(0);
        
        while (!F2.eof())
        {
            getline(F2, stroka);
            if (stroka == "+") plus_counter++;
        }*/

        plus_counter++;
        seria = plus_counter;
        cout << "---" << plus_counter << " ";
        cout << "Колличество серий - " << seria << endl;
    }

}

void sborka()
{
    ifstream F1("F1.txt");
    ifstream F2("F2.txt");
    fstream F_fin("F_fin.txt");
    fstream F_temp("F_temp.txt");

    int f1 = 0; int f2 = 0;

    string stroka;

    while (!F1.eof())
    {
        getline(F1, stroka);
        if (stroka != "+") f1++;
    }
    while (!F2.eof())
    {
        getline(F2, stroka);
        if (stroka != "+") f2++;
    }
    f1--; f2--;
    //cout << f1 << " " << f2;
    int MAX;
    int MIN;
    if (f1 > f2)
    {
        MAX = f1;
        MIN = f2;
    }
    else
    {
        MAX = f2;
        MIN = f1;
    }

    int* f1_mas = new int[MAX] {};
    int* f2_mas = new int[MAX] {};
    F1.clear();
    F1.seekg(0);
    for (int i = 0; i < f1; i++)
    {

        getline(F1, stroka);
        if (stroka != "+") f1_mas[i] = stoi(stroka);
        else
        {
            getline(F1, stroka);
            f1_mas[i] = stoi(stroka);
        }
    }
    F2.clear();
    F2.seekg(0);
    for (int i = 0; i < f2; i++)
    {
        getline(F2, stroka);
        if (stroka != "+") f2_mas[i] = stoi(stroka);
        else
        {
            getline(F1, stroka);
            f1_mas[i] = stoi(stroka);
        }
    }

    for (int i = 0; i < MAX; i++)
    {
        cout << f1_mas[i] << " ";
    }

    for (int i = 0; i < MAX; i++)
    {
        cout << f2_mas[i] << " ";
    }

    for (int i = 0; i < MAX; i++)
    {
        if (f1_mas[i] > f2_mas[i])
        {
            if (f2_mas[i] != 0) F_temp << to_string(f2_mas[i]) << endl;
            F_temp << to_string(f1_mas[i]);
            if (i != MAX) F_temp << endl;
        }
        else
        {
            if (f1_mas[i] != 0) F_temp << to_string(f1_mas[i]) << endl;
            F_temp << to_string(f2_mas[i]);
            if (i != MAX) F_temp << endl;
        }
    }
    F_temp.clear();
    F_temp.seekp(0);

    for (int i = 0; i < MAX + 1; i++)
    {
        getline(F_temp, stroka);
        F_fin << stroka;
        if (i != MAX) F_fin << endl;
    }

    delete f1_mas;
    delete f2_mas;

    F_temp.close();
    F1.close();
    F2.close();
}

int main()
{
    setlocale(0, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //sozdanie_ochistka(1);

    int vibor;
    bool loop = true;
    while (loop == true)
    {
        for (int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++)
        {
            cout << menu[i] << endl;
        }
        cout << "Выбор - "; (cin >> vibor).get();
        switch (vibor)
        {
        case 1: //1) Задать оригинальный файл
            new_orig_file();
            system("pause");
            system("cls");
            break;
        case 2: //2) Выполнить сортировку
            sortir_sbalans_slian();
            system("pause");
            system("cls");
            break;
        case 3: //3) Показать оригинальный файл
            print_file(F_orig_str);
            system("pause");
            system("cls");
            break;
        case 4: //4) Показать отсортированный файл
            scan_orig();
            //sborka();
            //print_file(F_temp_str);
            system("pause");
            system("cls");
            break;
        case 5: //5) Сделать один шаг и показать файлы 1 и 2
            sortir_sbalans_slian_1_shag();
            cout << "Первый файл:" << endl;
            print_file(F1_str);
            cout << "Второй файл:" << endl;
            print_file(F2_str);
            system("pause");
            system("cls");
            break;
        default:
            cout << "Выход из меню";
            loop = false;
        }
    }
}

