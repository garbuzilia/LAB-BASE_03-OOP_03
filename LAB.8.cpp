#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <Windows.h>


using namespace std;

/*
12.	Структура "Музыкальный диск":
-	название;
-	автор;
-	продолжительность;
-	цена.
Удалить первый элемент с заданной продолжительностью, добавить 2 элемента после элемента с заданным номером.
*/

/*
1.	Для заполнения файла можно использовать функцию, формирующую одну структуру,
    указанного в варианте типа. Значения элементов структуры вводятся с клави-атуры.
    Для ввода можно использовать операцию >> и функцию gets().

2.	При вводе структур можно реализовать один из следую-щих механизмов:
-	ввод заранее выбранного количества структур (не менее 5);
-	ввод  до появления структуры с заданным количе-ством признаков;
-	диалог с пользователем о необходимости продолжать ввод.

3.	Для записи структуры в  файл и чтения структуры из файла использовать функции
    блочного ввода/вывода fread и fwrite.

4.	Для удаления/ добавления элементов в файл  использо-вать вспомогательный файл.

*/

/* Сохранение списка. */

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
        cout << "Что нужно сделать:" << endl
            << "1) Собрать новую библиотеку дисков" << endl
            << "2) Вывести существующую библиотеку" << endl
            << "3) Удалить первый элемент с заданной продолжительностью" << endl
            << "4) Добавить 2 элемента после элемента с заданным номером" << endl;
        cout << "Выбор - "; cin >> vibor;
        system("cls");
        if (vibor == 1) //Собрать новую библиотеку дисков
        {
            new_lib();
        }
        else if (vibor == 2) //Вывести существующую библиотеку
        {
            show_lib();            
        }
        else if (vibor == 3) //Удалить первый элемент с заданной продолжительностью
        {
            del_time_lib();            
        }
        else if (vibor == 4) //Добавить 2 элемента после элемента с заданным номером
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
    cout << "Сколько дисков - "; cin >> n; cout << endl;
    MP3_Disc* CD = new MP3_Disc[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Диск №" << i + 1 << endl;
        cout << "Название - "; cin.get(); getline(cin, CD[i].name);
        cout << "Автор - "; getline(cin, CD[i].autor);
        cout << "Продолжительность - "; cin >> CD[i].play_time;
        cout << "Цена - "; cin >> CD[i].price;
        cout << endl;
    }

    if ((fp = fopen("test", "wb")) == NULL) {
        printf("Ошибка при открытии файла.\n");
        exit(1);
    }

    fwrite(&n, sizeof(int), 1, fp);

    for (int i = 0; i < n; i++)
        if (fwrite(&CD[i], sizeof(struct MP3_Disc), 1, fp) != 1)
        {
            cout << "Ошибка при записи файла" << endl;
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
        printf("Ошибка при открытии файла.\n");
        exit(1);
    }

    fread(&n, sizeof(int), 1, fp);
    MP3_Disc* CD = new MP3_Disc[n];
    for (int i = 0; i < n; i++)
    {
        if (fread(&CD[i], sizeof(struct MP3_Disc), 1, fp) != 1)
        {
            cout << "Ошибка при записи файла" << endl;
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << endl
            << "Диск №" << i + 1 << endl
            << "Название - " << CD[i].name << endl
            << "Автор - " << CD[i].autor << endl
            << "Продолжительность - " << CD[i].play_time << endl
            << "Цена - " << CD[i].price
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


    cout << "Какое время нужно - "; cin >> ex_time;

    if ((fp = fopen("test", "rb")) == NULL)
    {
        printf("Ошибка при открытии файла.\n");
        exit(1);
    }

    fread(&n, sizeof(int), 1, fp);
    MP3_Disc* CD = new MP3_Disc[n];
    for (int i = 0; i < n; i++)
    {
        if (fread(&CD[i], sizeof(struct MP3_Disc), 1, fp) != 1)
        {
            cout << "Ошибка при записи файла" << endl;
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
        printf("Ошибка при открытии файла.\n");
        exit(1);
    }

    fwrite(&n, sizeof(int), 1, ft);

    for (int i = 0; i < nomer; i++)
        if (fwrite(&CD[i], sizeof(struct MP3_Disc), 1, ft) != 1)
        {
            cout << "Ошибка при записи файла" << endl;
        }

    for (int i = nomer + 1; i < n; i++)
        if (fwrite(&CD[i], sizeof(struct MP3_Disc), 1, ft) != 1)
        {
            cout << "Ошибка при записи файла" << endl;
        }

    fclose(fp);
    fclose(ft);

    if ((ft = fopen("temp", "rb")) == NULL)
    {
        printf("Ошибка при открытии файла.\n");
        exit(1);
    }

    fread(&n, sizeof(int), 1, fp);

    n--;

    for (int i = 0; i < n; i++)
    {
        if (fread(&CD[i], sizeof(struct MP3_Disc), 1, ft) != 1)
        {
            cout << "Ошибка при записи файла" << endl;
        }
    }

    if ((fp = fopen("test", "wb")) == NULL) {
        printf("Ошибка при открытии файла.\n");
        exit(1);
    }

    fwrite(&n, sizeof(int), 1, fp);

    for (int i = 0; i < n; i++)
        if (fwrite(&CD[i], sizeof(struct MP3_Disc), 1, fp) != 1)
        {
            cout << "Ошибка при записи файла" << endl;
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
    cout << "Номер элемента - "; cin >> nomer; cout << endl;

    if ((fp = fopen("test", "rb")) == NULL)
    {
        printf("Ошибка при открытии файла.\n");
        exit(1);
    }

    fread(&n, sizeof(int), 1, fp);
    MP3_Disc* CD = new MP3_Disc[n + 2];
    for (int i = 0; i < n; i++)
    {
        if (fread(&CD[i], sizeof(struct MP3_Disc), 1, fp) != 1)
        {
            cout << "Ошибка при записи файла" << endl;
        }
    }

    for (int i = n; i < n + 2; i++)
    {
        cout << "Диск №" << i + 1 << endl;
        cout << "Название - "; cin.get(); getline(cin, CD[i].name);
        cout << "Автор - "; getline(cin, CD[i].autor);
        cout << "Продолжительность - "; cin >> CD[i].play_time;
        cout << "Цена - "; cin >> CD[i].price;
        cout << endl;
    }

    if ((ft = fopen("temp", "wb")) == NULL) {
        printf("Ошибка при открытии файла.\n");
        exit(1);
    }

    fwrite(&n, sizeof(int), 1, ft);

    for (int i = 0; i < nomer; i++)
        if (fwrite(&CD[i], sizeof(struct MP3_Disc), 1, ft) != 1)
        {
            cout << "Ошибка при записи файла" << endl;
        }
    for (int i = n; i < n + 2; i++)
        if (fwrite(&CD[i], sizeof(struct MP3_Disc), 1, ft) != 1)
        {
            cout << "Ошибка при записи файла" << endl;
        }
    for (int i = nomer; i < n; i++)
        if (fwrite(&CD[i], sizeof(struct MP3_Disc), 1, ft) != 1)
        {
            cout << "Ошибка при записи файла" << endl;
        }

    fclose(fp);
    fclose(ft);

    if ((ft = fopen("temp", "rb")) == NULL)
    {
        printf("Ошибка при открытии файла.\n");
        exit(1);
    }

    fread(&n, sizeof(int), 1, fp);

    n += 2;

    for (int i = 0; i < n; i++)
    {
        if (fread(&CD[i], sizeof(struct MP3_Disc), 1, ft) != 1)
        {
            cout << "Ошибка при записи файла" << endl;
        }
    }

    if ((fp = fopen("test", "wb")) == NULL) {
        printf("Ошибка при открытии файла.\n");
        exit(1);
    }

    fwrite(&n, sizeof(int), 1, fp);

    for (int i = 0; i < n; i++)
        if (fwrite(&CD[i], sizeof(struct MP3_Disc), 1, fp) != 1)
        {
            cout << "Ошибка при записи файла" << endl;
        }

    fclose(fp);
    fclose(ft);

    system("pause");
    system("cls");
}