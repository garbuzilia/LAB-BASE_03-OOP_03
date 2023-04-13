// LAB 10.cpp

//1. Ввести размер массива;
//2.Сформировать массив с помощью операции new или библиотечных функций malloc(calloc);
//3.Заполнить массив(можно с помощью датчика случайных чисел);
//4.Выполнить задание варианта, сформировать новый массив(ы) - результат(ы);
//5.Напечатать массив(ы) - результат(ы);
//6.Удалить динамические массивы с помощью операции delete или библиотечной функции free.

//12.	Сформировать двумерный массив.Удалить из него все строки, в которых встречается заданное число.

#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    setlocale(0, "");
    srand(time(NULL));
    int n, number;
    int counter = 0;
    cout << "Размер массива - "; cin >> n;
    int* Dmas = new int[n];
    
    for (int i = 0; i < n; i++)
    {
        Dmas[i] = rand() % 10;
    }
    for (int i = 0; i < n; i++)
    {
        cout << i+1 << " - " << Dmas[i] << endl;
    }
    cout << "Какое число нужно убрать из массива - "; cin >> number;
    for (int i = 0; i < n; i++)
    {
        if (Dmas[i] == number) counter++;
    }
    int* Dmas_2 = new int[n - counter];
    for (int i = 0, j = 0; i < n; i++)
    {
        if (Dmas[i] != number)
        {
            Dmas_2[j] = Dmas[i];
            j++;
        }
    }
    for (int i = 0; i < n-counter; i++)
    {
        cout << i+1 << " - " << Dmas_2[i] << endl;
    }
    delete[] Dmas;
}