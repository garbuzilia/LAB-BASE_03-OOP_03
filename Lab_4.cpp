#include <iostream>
#include <time.h>


using namespace std;

/*
1)	Сформировать одномерный массив целых чисел, используя датчик случайных чисел.
2)	Распечатать полученный массив.
3)	Поменять местами минимальный и максимальный элементы массива.
4)	Удалить из массива все элементы превышающие его сред-нее значение более, чем на 10%.
5)	Распечатать полученный массив.
*/

int main()
{
    setlocale(0,"");

    srand(time(NULL));

    int n;
    int Min,Max;
    int qMin = 0,qMax = 0;
    int summ = 0; float tenpres;
    cout << "Длина масива - ";
    cin >> n;
    int* Dmas = new int[n];
    for (int i = 0; i < n; i++)
    {
        Dmas[i] = rand() % 100;
    }
    Min = Dmas[0];
    Max = Dmas[0];
    for (int i = 0; i < n; i++)
    {
        if (Dmas[i] < Min)  Min = Dmas[i];
        if (Dmas[i] > Max)  Max = Dmas[i];
        summ += Dmas[i];
    }
    tenpres = summ/n*1.1;
    cout << endl;
    cout    << "Мин  = " << Min << endl
            << "Макс = " << Max << endl
            << "Среденее + 10% = " << tenpres <<  endl;
    cout << endl;
    cout << "Оригинал - ";
    for (int i = 0; i < n; i++)
    {
        cout << Dmas[i] << " ";
    }

    cout << endl;

    for (int i = 0; i < n; i++)
    {
        if      (Dmas[i] == Max)    Dmas[i] = Min;
        else if (Dmas[i] == Min)    Dmas[i] = Max;
    }
    cout << "Заменен  - ";
    for (int i = 0; i < n; i++)
    {
        cout << Dmas[i] << " ";
    }

    cout << endl;

    for (int i = 0; i < n; i++)
    {
        if (Dmas[i] >= tenpres)
        {
            for (int j = i;j<n;++j)
            {
                Dmas[j] = Dmas[j+1];
            }
            --n;
        }
    }
    cout << "Удален   - ";
    for (int i = 0; i < n; i++)
    {
        cout << Dmas[i] << " ";
    }

    delete [] Dmas;
    return 0;
}
