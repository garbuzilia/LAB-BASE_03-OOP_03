// SORTIR2.cpp 
// Сортировки Шелла и Быстрая сортировка Хоара

#include <iostream>
#include <time.h>

using namespace std;

void vivod(int n, int* x)
{
    for (int i = 0; i < n; i++)
    {
        cout << x[i] << " ";
    }
    cout << endl;
}

void Shell(int n, int *x) //сортировка Шелла
{
    int centr, count;
    centr = n;
    centr = centr / 2;
    while (centr > 0)
    {
        for (int i = 0; i < n - centr; i++)
        {
            int j = i;
            while ( j >= 0 && x[j] > x[j + centr])
            {
                count = x[j];
                x[j] = x[j + centr];
                x[j + centr] = count;
                j--;
            }
        }
        centr = centr / 2;
    }
}

//Быстрая сортировка
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

int main()
{
    setlocale(0, "");
    srand(time(NULL));
    int n = 5, vibor;
    bool loop = 1;
    cout << "Длинна массива - "; cin >> n;
    int* x = new int[n];

    for (int i = 0; i < n; i++)
    {
        x[i] = rand() % 20;
    }

    while (loop == 1)
    {
        cout << "Сортировки:" << endl
            << "1) Сортировка Шелла" << endl
            << "2) Быстрая сортировка" << endl
            << "3) Изменить размер массива" << endl
            << "Выбор - ";
        cin >> vibor;

        if (vibor == 1)
        {

            cout << endl << "Созданный массив" << endl;
            for (int i = 0; i < n; i++)
            {
                x[i] = rand() % 20;
                cout << x[i] << " ";
            }

            cout << endl << endl << "Отсортированный массив" << endl;
            
            Shell(n, x);
            vivod(n, x);
            system("pause");
            system("cls");
        }
        else if (vibor == 2)
        {
            cout << endl << "Созданный массив" << endl;
            for (int i = 0; i < n; i++)
            {
                x[i] = rand() % 20;
                cout << x[i] << " ";
            }
            
            cout << endl << endl << "Отсортированный массив" << endl;
            
            Bistro(0, n - 1, x);
            vivod(n, x);
            system("pause");
            system("cls");
        }
        else if  (vibor == 3)
        {
            cout << "Длинна массива - "; cin >> n;
            cout << endl;
            int* x = new int[n];
            system("cls");
        }

        else if ((vibor > 3) || (vibor < 0))
        {
            loop = 0;
        }
    }
}

