#include <iostream>
#include <time.h>

using namespace std;
/*
12. Написать функцию, для поиска максимального элемента
    в указанной строке двумерного массива. Сдвинуть в дву-мерном
    массиве все строки циклически вправо на коли-чество элементов
    равное максимальному элементу в этой строке.
*/

int maxel(int OdinDmas[], int m)
{
    int Mx = OdinDmas[0];
    int chet = 0;
    for (int i = 0; i < m; i++)
    {
        if (OdinDmas[i] > Mx) Mx = OdinDmas[i];
    }
    //cout << Mx << endl;

    for (int i = 0; i < m; i++)
    {
        if (OdinDmas[i] == Mx) chet++;
    }

    //cout << chet << endl;
    for (int gg = 0; gg < chet; gg++)
    {
    for (int i = m-1; i>0; i--)
    {
        OdinDmas[i] = OdinDmas[i-1];
    }
    OdinDmas[0] = 0;
    }

    for (int i = 0; i < m; i++)
    {
        cout << OdinDmas[i] << "\t";
    }
    cout << "|Макc - " << Mx << ";\tПовтор - " << chet;
    return 0;
}

int main()
{
    setlocale(0,"");
    srand(time(NULL));

    int n ;     int m ;
    int stroka, R;
    cout << "Строки  - "; cin >> n;
    cout << "Столбцы - "; cin >> m;
    cout << "Разброс рандома - "; cin >> R;

    int** Dmas = new int*[n];

    int* OdinDmas = new int[m];

    for (int i = 0; i < n; i++)
        Dmas[i] = new int[m];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            Dmas[i][j] = 1 + rand() % R;
        }
    }

    cout << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << Dmas[i][j] << "\t";
        }
        cout << endl;
    }

    //cin >> stroka;
    for (int stroka = 0; stroka < n; stroka++)
    {

    for (int i = 0; i < m; i++)
    {
        OdinDmas [i] = Dmas[stroka][i];
    }
    /*
    for (int i = 0; i < m; i++)
    {
        cout << OdinDmas[i] << "\t";
    }
    */
    cout << endl;
    maxel(OdinDmas,m);
    }

    delete [] OdinDmas;
    delete [] Dmas;
    return 0;
}
