// LAB 11.cpp
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

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


struct spisok
{
    string name;
    spisok* next; //Следующий модуль
    spisok* prev; //Предыдущий модуль
};
spisok* head;
spisok* tail;

void add_list(string value, int position)
{
    spisok* spis_elem = new spisok; //создание нового элемента
    spis_elem->name = value; //присвоение элементу значения
    if (head == NULL) //если список пуст
    {
        spis_elem->next = spis_elem; //установка указателя next
        spis_elem->prev = spis_elem; //установкая указателя prev
        head = spis_elem; //определяется голова списка
    }
    else
    {
        spisok* p = head;
        for (int i = position; i > 1; i--)
        {            
            p = p->next;
        }
               
        p->prev->next = spis_elem;
        spis_elem->prev = p->prev;
        spis_elem->next = p; //добавление элемента
        p->prev = spis_elem;
    }
}

void print_list()
{
    if (head == NULL) cout << "Список пуст\n";
    else
    {
        spisok* a = head;
        cout << "Элементы списка: " << endl;
        int u = 1;
        do
        {
            cout << u << " - " << a->name << endl;
            a = a->next;
            u++;
        } while (a != head);
    }
}

int delete_list(int position)
{
    if (head == NULL) 
    {
        cout << "\nСписок пуст\n\n"; return 0; 
    }
    if (head == head->next) //если это последний элемент в списке
    {
        delete head; //удаление элемента
        head = NULL;
    }
    else
    {
        spisok* a = head;
        for (int i = position; i > 1; i--) a = a->next;
        if (a == head) head = a->next;
        a->prev->next = a->next; //удаление элемента
        a->next->prev = a->prev;
        delete a;
    }
}

FILE* fp;

int main()
{
    setlocale(0, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    bool loop = 1;
    int vibor;

    string vvod;
    int n = 0;
    int tmp;

    while (loop != 0)
    {
        cout << "Что нужно сделать:" << endl
            << "1) Создать новый список" << endl
            << "2) Вывести список на экран" << endl
            << "3) Добавить элементы в список" << endl
            << "4) Удалить элементы из списка" << endl
            << "5) Удалить из списка одинаковые элементы" << endl
            << "6) Добавить элемент после элемента с заданным ключевым полем" << endl
            << "7) Записать список в файл" << endl
            << "8) Прочитать список из файла" << endl
            << "9) Удалить список из памяти" << endl;

        cout << "Выбор - "; (cin >> vibor).get();
        system("cls");
        if (vibor == 1) //1) Создать новый список
        {
            
            if (n > 0)
            {
                for (int i = 1; i <= n; i++)
                {
                    delete_list(1);
                }
            }

            cout << "Сколько элементов в новом списке - "; (cin >> n).get();
            for (int i = 1; i <= n; i++)
            {
                cout << i << " элемент - ";
                getline(cin, vvod);
                add_list(vvod, i);
            }
            system("pause");
            system("cls");
        }
        else if (vibor == 2) //2) Вывести список на экран
        {
            print_list();
            system("pause");
            system("cls");
        }
        else if (vibor == 3) //3) Добавить элементы в список
        {
            int s;

            print_list();
            cout << "Сколько элементов добавить - "; (cin >> tmp).get();
            cout << "После какой позиции - "; (cin >> s).get();

            for (int i = s; i < s+tmp; i++)
            {
                cout << i+1 << " элемент - ";
                getline(cin, vvod);
                add_list(vvod, i+1);
            }
            cout << "Новые - ";
            print_list();
            n += tmp;
            system("pause");
            system("cls");
        } 
        else if (vibor == 4) //4) Удалить элементы из списка
        {        
            int s;

            print_list();
            cout << "Сколько элементов удалить - "; (cin >> tmp).get();
            cout << "C какой позиции - "; (cin >> s).get();

            for (int i = s; i < s + tmp; i++)
            {
                delete_list(s);
            }
            
            n -= tmp;

            cout << "Новые - ";
            print_list();
            system("pause");
            system("cls");
        } 
        else if (vibor == 5) //5) Удалить из списка одинаковые элементы
        {
            string* poisk = new string[n];
            int* na_udalenie = new int[n];
            spisok* a = head;
            int u = 0;
            int lishnee = 0;

            do
            {
                poisk[u] = a->name;
                a = a->next;
                u++;
            } while (a != head);

            for (int i = 0; i < n; i++)
            {
                int count = 0;
                for (int j = 0; j < n; j++)
                {
                    if (poisk[i] == poisk[j])
                    {
                        count++;
                    }
                }
                if (count > 1)
                {
                    na_udalenie[i] = i + 1;
                }
                else na_udalenie[i] = -1;
            }

            for (int i = 0; i < n; i++)
            {
                if (na_udalenie[i] != -1)
                {
                    lishnee++;
                }
            }

            for (int i = 0; i < n; i++)
            {
                if (na_udalenie[i] > 0)
                {
                    delete_list(na_udalenie[i]);
                    for (int j = 0; j < n; j++)
                    {
                        na_udalenie[j] = na_udalenie[j] - 1;
                    }
                }
            }

            n -= lishnee;

            cout << endl;
            system("pause");
            system("cls");
        }
        else if (vibor == 6) //6) Добавить элемент после элемента с заданным ключевым полем
        {
            string key_word;
            bool f = 0;
            print_list();
            cout << "После имени какого поля - "; getline(cin,key_word);
            string* poisk = new string[n];
            spisok* a = head;
            int u = 0;
            do
            {
                poisk[u] = a->name;
                if (poisk[u] == key_word)
                {
                    cout << u+2 << " элемент - ";
                    getline(cin, vvod);
                    add_list(vvod, u+2);
                    f = 1;
                }
                a = a->next;
                u++;
            } while (a != head && f==0);
            n++;
            system("pause");
            system("cls");
        } 
        else if (vibor == 7) //7) Записать список в файл
        {
            
            if ((fp = fopen("test", "wb")) == NULL) {
                printf("Ошибка при открытии файла.\n");
                exit(1);
            }
            fwrite(&n, sizeof(int), 1, fp);

            spisok* a = head;

            if (head == NULL)
            {
                system("cls");
                cout << "Список  пуст!" << endl;
            }
            else
            {
                    do  //запись структуры в файл
                    {
                        fwrite(a, sizeof(spisok), 1, fp);
                        a = a->next;
                    } while (a != head);
                    
            }

            fclose(fp);
            system("pause");
            system("cls");
        }
        else if (vibor == 8) //8) Прочитать список из файла
        {
            if ((fp = fopen("test", "rb")) == NULL) {
                printf("Ошибка при открытии файла.\n");
                exit(1);
            }
            fread(&n, sizeof(int), 1, fp);
            
            spisok* a = new spisok[n];
            for (int i = 1; i <= n; i++)
            {
                if (fread(&a[i].name, sizeof(spisok), 1, fp) != 1)
                {
                    cout << "Ошибка при записи файла" << endl;
                }
                add_list(a[i].name, i);
            }
            
            fclose(fp);
            system("pause");
            system("cls");
        }
        else if (vibor == 9) //9) Удалить список из памяти
        {
            for (int i = 1; i <= n; i++)
            {
                delete_list(i);
            }
        } 
        else if (vibor < 0 || vibor > 9) loop = 0;
    }

}

