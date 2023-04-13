// LAB 11 V2.cpp

//12.	Записи в линейном списке содержат ключевое поле типа * char(строка символов).
//      Сформировать двунаправ - ленный список.Удалить из него Элементы, с одинаковыми
//      ключевыми полями.Добавить элемент после элемента с заданным ключевым полем.

// 	Порядок выполнения работы
//1.	Написать функцию для создания списка.Функция может создавать пустой список, а затем добавлять в него элементы.
//2.	Написать функцию для печати списка.Функция должна предусматривать вывод сообщения, если список пустой.
//3.	Написать функции для удаления и добавления элементов списка в соответствии со своим вариантом.
//4.	Выполнить изменения в списке и печать списка после каждого изменения.
//5.	Написать функцию для записи списка в файл.
//6.	Написать функцию для уничтожения списка.
//7.	Записать список в файл, уничтожить его и выполнить печать(при печати должно быть выдано сообщение "Спи-сок пустой").
//8.	Написать функцию для восстановления списка из файла.
//9.	Восстановить список и распечатать его.
//10.	Уничтожить список.

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

string menu[10] =
{
        "Что нужно сделать:",
        "1) Создать новый список",
        "2) Вывести список на экран",
        "3) Добавить элемент в список",
        "4) Удалить элемент из списка",
        "5) Удалить из списка одинаковые элементы",
        "6) Добавить элемент после элемента с заданным ключевым полем",
        "7) Записать список в файл",
        "8) Прочитать список из файла",
        "9) Удалить список из памяти"
};

struct elem
{
    string stroka;
    elem* next;
};

elem* head = nullptr;
elem* tail = nullptr;

void delete_all();

void new_spis()
{

    int kol_vo_elem;
    string s;
    delete_all();
    cout << "Сколько элементов будет в списке - "; (cin >> kol_vo_elem).get();
    for (int i = 1; i <= kol_vo_elem; i++)
    {
        elem* d_elem = new elem;
        cout << i << " - ";
        getline(cin, s);    d_elem->stroka = s;
        if (head == nullptr)
        {
            head = d_elem;
            tail = d_elem;

            d_elem->next = nullptr;
            continue;
        }
        d_elem->next = nullptr;
        tail->next = d_elem;
        tail = d_elem;
    }
}

void print_spis()
{
    if (head == nullptr)
    {
        cout << "Список пуст" << endl;
        return;
    }
    elem* d_elem = head;
    for (int i = 1; d_elem != nullptr; i++)
    {
        cout << i << " - " << d_elem->stroka << endl;
        d_elem = d_elem->next;
    }
}

void add_spis()
{
    if (head == nullptr)
    {
        cout << "Список пуст" << endl;
        return;
    }
    print_spis();

    int index;
    string s;
    cout << "Какой по счету должен быть новый элемент - "; (cin >> index).get();
    cout << "Введите новый элемент - ";
    getline(cin, s);

    elem* d_elem = head;
    int q;

    for (int i = 1; d_elem != nullptr; i++)
    {
        q = i;
        d_elem = d_elem->next;
    }

    d_elem = head;

    if (index == 1)
    {
        elem* d_elem = new elem;
        
        d_elem->stroka = s;
        d_elem->next = head;
        head = d_elem;
    }
    else if (index <= q && index > 0)
    {
        for (int i = 1; d_elem != nullptr; i++)
        {

            if (i == index)
            {
                elem* d_elem = new elem;
                d_elem->stroka = s;
                elem* proshl_elem = head;
                for (int j = 1; j != i - 1; j++)
                {
                    proshl_elem = proshl_elem->next;
                }
                d_elem->next = proshl_elem->next;
                proshl_elem->next = d_elem;
            }
            d_elem = d_elem->next;
        }
    }
    else if (index == q + 1 && index > 0)
    {
        elem* d_elem = new elem;
        d_elem->stroka = s;
        d_elem->next = nullptr;
        tail->next = d_elem;
        tail = d_elem;
    }
    else cout << "Значение отрицательное, 0 или превышает все возможные позиции - ОШИБКА" << endl;

    print_spis();
}

void delete_spis()
{
    if (head == nullptr)
    {
        cout << "Список пуст" << endl;
        return;
    }
    print_spis();

    elem* d_elem = head;
    int q;

    for (int i = 1; d_elem != nullptr; i++)
    {
        q = i;
        d_elem = d_elem->next;
    }

    int index;
    cout << "Какой по счету удалить элемент - "; (cin >> index).get();
    elem* proshl_elem = new elem;
    if (index == 1)
    {
        d_elem = head;
        head = head->next;
        delete d_elem;
    }
    else if (index > 1 && index <= q)
    {
        d_elem = head;
        for (int i = 1; d_elem != nullptr; i++)
        {
            if (i == index - 1)
            {
                proshl_elem = d_elem;
            }
            d_elem = d_elem->next;
            if (i == index)
            {
                elem* delete_elem = proshl_elem->next;
                proshl_elem->next = delete_elem->next;
                delete delete_elem;
            }
        }
    }
    else cout << "Значение отрицательное, 0 или превышает все возможные позиции - ОШИБКА" << endl;

    print_spis();
}

void kill(elem* c)
{
    if (c->next == NULL)
    {
        delete c;
        c = NULL;
    }
    else
    {
        elem* q;
        q = c->next;
        *c = *q;
        delete q;
    }

}

void delete_odinak()
{
    if (head == nullptr)
    {
        cout << "Список пуст" << endl;
        return;
    }
    elem* core_elem = head;
    elem* sravn_elem = new elem;
    elem* prosh_elem = new elem;

    elem* kostil= new elem;
    kostil->stroka = "_data";
    kostil->next = nullptr;
    tail->next = kostil;
    tail = kostil;

    while (core_elem != nullptr)
    {
        bool est_sovpadenie = 0;
        sravn_elem = core_elem->next;
        prosh_elem = core_elem;
        while (sravn_elem != nullptr)
        {
            if (core_elem->stroka == sravn_elem->stroka)
            {
                kill(sravn_elem);
                est_sovpadenie = 1;
            }
            else 
            {
                prosh_elem = prosh_elem->next;
                sravn_elem = sravn_elem->next;
            }
        }
        if (core_elem->next == tail)
        {
            prosh_elem = core_elem;
        }
        if (est_sovpadenie) kill(core_elem);
        else core_elem = core_elem->next;

    }
    
    if (!head)
        return;

    if (!head->next)
    {
        delete head;
        head = nullptr;
        return;
    }

    elem* p = head;
    while (p->next->next)
        p = p->next;

    delete p->next;
    p->next = nullptr;

    print_spis();
}

void dobavit_po_kluchu()
{
    if (head == nullptr)
    {
        cout << "Список пуст" << endl;
        return;
    }
    print_spis();

    string s1;
    string s2;
    cout << "После какого ключевого поля добавить объект - "; getline(cin,s1);
    cout << "Запись в объекте - "; getline(cin, s2);
    elem* new_elem = new elem;
    elem* proshl_elem = new elem;
    new_elem->stroka = s2;

    elem* d_elem = head;
    while (d_elem != nullptr)
    {
        if (d_elem->stroka == s1)
        {
            new_elem->next = d_elem->next;
            d_elem->next = new_elem;
        }
        d_elem = d_elem->next;
    }
}

void delete_all()
{
    elem* d_elem = head;
    while (head != nullptr)
    {
        head = head->next;
        delete d_elem;
        d_elem = head;
    }
}

void zapis_v_fail()
{
    if (head == nullptr)
    {
        cout << "Список пуст" << endl;
        return;
    }
    ofstream F1("F1.txt");
    elem* d_elem = head;
    for (int i = 1; d_elem != nullptr; i++)
    {
        F1 << d_elem->stroka;
        if (d_elem->next != nullptr)
        {
            F1 << endl;
        }
        d_elem = d_elem->next;
    }
    F1.close();
}

void chten_iz_faila()
{
    ifstream F1("F1.txt");

    string s;
    delete_all();
    while (!F1.eof())
    {
        elem* d_elem = new elem;
        getline(F1, s); d_elem->stroka = s;
        if (head == nullptr)
        {
            head = d_elem;
            tail = d_elem;
            continue;
        }
        d_elem->next = nullptr;
        tail->next = d_elem;
        tail = d_elem;
    }

    F1.close();
}

int main()
{
    setlocale(0, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    bool loop = true;
    int vibor = 0;

    while (loop == true)
    {
        for (int i = 0; i < 10; i++)
        {
            cout << menu[i] << endl;
        }
        cout << "Выбор - ";
        (cin >> vibor).get();
        switch (vibor)
        {
        case 1:                 //1) Создать новый список
            new_spis();
            system("pause");
            system("cls");
            break;
        case 2:                 //2) Вывести список на экран
            print_spis();
            system("pause");
            system("cls");
            break;
        case 3:                 //3) Добавить элемент в список
            add_spis();
            system("pause");
            system("cls");
            break;
        case 4:                 //4) Удалить элемент из списка
            delete_spis();
            system("pause");
            system("cls");
            break;
        case 5:                 //5) Удалить из списка одинаковые элементы
            delete_odinak();
            system("pause");
            system("cls");
            break;
        case 6:                 //6) Добавить элемент после элемента с заданным ключевым полем
            dobavit_po_kluchu();
            system("pause");
            system("cls");
            break;
        case 7:                 //7) Записать список в файл
            zapis_v_fail();
            cout << "Записаны элементы:" << endl;
            print_spis();
            system("pause");
            system("cls");
            break;
        case 8:                 //8) Прочитать список из файла
            chten_iz_faila();
            cout << "Прочитаны элементы:" << endl;
            print_spis();
            system("pause");
            system("cls");
            break;
        case 9:                 //9) Удалить список из памяти
            delete_all();
            system("pause");
            system("cls");
            break;
        default:
            cout << "Выход из меню";
            loop = false;
        }
    }
}
