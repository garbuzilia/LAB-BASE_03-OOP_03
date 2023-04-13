//      LAB 9
//1. 	Создать текстовый файл F1 не менее, чем из 10 строк и записать в него информацию
//2. 	Выполнить задание.

//      Вариант 12.
//1) 	Скопировать из файла F1 в файл F2 все строки, кроме той строки, в которой больше всего гласных букв.
//2) 	Напечатать номер этой строки.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>

using namespace std;

string F1_str = "F1.txt";
string F2_str = "F2.txt";

void new_file()
{
    ofstream F1("F1.txt"); // окрываем файл для записи
    ofstream F2("F2.txt"); // окрываем файл для записи

    int n;
    string stroka;
    cout << "Сколько строк будет в файле F1 - ";
    (cin >> n).get();
    for (int i = 1; i <= n; i++)
    {
        cout << i << " строка - ";
        getline(cin, stroka);
        F1 << stroka;
        if (i != n) F1 << "\n";
    }

    F1.close();
    F2.close();
}

void show_file(string filename)
{
    ifstream file(filename);
    string s;
    if (file.peek() == EOF) cout << "Файл пуст" << endl;
    else
    {
        cout << "Строки: " << endl;
        for (int i = 1; !file.eof(); i++)
        {
            getline(file, s);
            if (s == "\0") continue;
            cout << i << " - " << s << endl;
        }
    }
    
    file.close();
}

void F1_to_F2()
{
    ifstream F1("F1.txt");
    ofstream F2("F2.txt");
    string s;

    string Gl_bolsh_eng = "AEIOUY";
    string Gl_malie_eng = "aeiouy";

    string Gl_bolsh_rus = "АОУЫИЕЁЭЮЯ";
    string Gl_malie_rus = "аоуыиеёэюя";

    int Gl_max_counter = 0;
    int Gl_max_i = 0;

    show_file(F1_str);

    if (F1.peek() == EOF)
    {
        cout << "F1 пуст" << endl;
    }
    else
    {
        for (int i = 1; !F1.eof(); i++)
        {
            getline(F1, s);
            int Gl_counter = 0;
            for (int j = 0; j < s.size(); j++)
            {
                for (int m = 0; m < 6; m++)
                {
                    if (s[j] == Gl_malie_eng[m] || s[j] == Gl_bolsh_eng[m])
                    {
                        Gl_counter++;
                    }
                }
                for (int h = 0; h < 10; h++)
                {
                    if (s[j] == Gl_malie_rus[h] || s[j] == Gl_bolsh_rus[h])
                    {
                        Gl_counter++;
                    }
                }
            }

            if (Gl_max_counter < Gl_counter)
            {
                Gl_max_counter = Gl_counter;
                Gl_max_i = i;
            }
        }
    }
    cout << "Строка с наибольшим кол-вом гласных - " << Gl_max_i << endl;
    F1.seekg(0);
    for (int i = 1; !F1.eof(); i++)
    {
        if (i != Gl_max_i)
        {
            getline(F1, s);
            F2 << s;
            if (!F1.eof()) F2 << "\n";
        }
        else getline(F1, s);
    }
    F2.seekp(0);
    show_file(F2_str);

    F1.close();
    F2.close();
}

int main()
{
    setlocale(0, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    


    int choice;
    bool loop = 1;
    while (loop)
    {
        cout << "Что нужно сделать:" << endl
            << "1) Записать в F1 строки для работы программы" << endl
            << "2) Скопировать из файла F1 в файл F2 все строки, кроме той строки, в которой больше всего гласных букв." << endl
            << "3) Показать файл F1" << endl
            << "4) Показать файл F2" << endl
            << "Выбор - "; cin >> choice;

        switch (choice)
        {
        case 1:
            new_file(); 
            system("pause");
            system("cls");
            break;
        case 2:
            F1_to_F2();
            system("pause");
            system("cls");
            break;
        case 3:
            show_file(F1_str); 
            system("pause");
            system("cls");
            break;
        case 4:
            show_file(F2_str); 
            system("pause");
            system("cls");
            break;
        default:
            loop = 0;
        }
    }
}

