#include <iostream>
#include <cmath>

using namespace std;

const float pi = 3.14;

float Y(float x)
{
    return -0.5*log(1 - 2*x*cos(pi/3) + pow(x,2));
}

float SS(float x, int n, float sum)
{
    return ((x*n)/(n + 1))*(cos(((n + 1)*pi)/3)/cos((n*pi)/3));
}

float S(float x, int n, float sum)
{
    if (n <= 35)
    {
        sum += SS(x,n+1,sum);
    }
    return abs(sum);
}

int main()
{
    setlocale(0,"RUS");
    float a = 0.1;
    float b = 0.8;
    float x = (b-a)/10;
    float sum = 0;
    int n = 0;
    cout << "Интервал от 0.1 до 0.8 с шагом 0.07; n = 35" << endl;
    for (float i = a; i <= b; i += x)
    {
        cout    << "X=" << i << "\t\t|"
                << "SN=" << S(i,0,sum) << "\t\t|"
                << "Y=" << Y(i) << endl;
    }
    return 0;
}
