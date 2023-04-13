// HESH-TABL.cpp : Работа с ХЭШ Таблицами

//Задание
//1.	Создать динамический массив из записей (в соответствии с вариантом), содержащий не менее 100 элементов. Для заполнения элементов массива использовать Ддатчик Случайных Чисел.
//2.	Предусмотреть сохранение массива в файл и загрузку массива из файла.
//3.	Предусмотреть возможность добавления и удаления элементов из массива(файла).
//4.	Выполнить поиск элемента в массиве по ключу в соответствии с вариантом.Для поиска использовать хэш - таблицу.
//5.	Подсчитать количество коллизий при размере хэш - таблицы 40, 75 и 90 элементов.

//Вариант       - 12	
//Даннные       - ФИО, Номер паспорта, Номер телефона
//Ключ (string) - ФИО
//Хэш - функция - H(k) = [M(kAmod1)], 0 < A < 1, mod1 – получение дробной части, [] – получение целой части
//Метод рехеш.  - Метод цепочек

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <Windows.h>
#include <ctime>

using namespace std;

//Константа для Хэш-функции
#define A 0.125 //2^(-3)  
#define DLINNA 100

//Хэш-функция
int hash_function(string Full_name) 
{
	if (DLINNA > 0)
	{
		return DLINNA * fmod(Full_name.size() * A, 1);
	}
	else
	{
		cout << "ERROR" << endl;
		return 0;
	}
}

string two_name[5]		{	"Янко",				"Каганович",		"Яснеева",			"Яблокова",			"Масленник"		};	//Рандом Фамилия
string name[5]			{	"Филипп",			"Аркадий",			"Зоя",				"Клара",			"Кира"			};	//Рандом Имя
string three_name[5]	{	"Валентинов",		"Лукьевич",			"Максимовна",		"Гермоновна",		"Кузьминовна"	};	//Рандом Отчество
string pass_ID[5]		{	"4734 341918",		"4062 208943",		"4838 701329",		"4873 983462",		"4745 919841"	};	//Рандом Паспорт
string phone_num[5]		{	"+7(912)1554317",	"+7(912)6073667",	"+7(912)9387144",	"+7(912)6225233",	"+7(912)9982160"};	//Рандом Телефон

//Стуктура со значениями
typedef struct Person Person;

struct Person
{
	char* FIO;			// ключ
	char* passport_ID;	// значение
	char* phone_number;	// значение
};

typedef struct LinkedList LinkedList;

struct LinkedList
{
	Person* item;
	LinkedList* next;
};

//Стурктура хэш-таблицы
typedef struct HashTable HashTable;

struct HashTable 
{
	Person** items;
	LinkedList** overflow_buckets;
	int size;		//  размер таблицы
	int count;		//  количество элементов в хеш-таблице
};

/// Связный список /////////////////////////////////////////////////

static LinkedList* allocate_list() 
{
	LinkedList* list = (LinkedList*)calloc(1, sizeof(LinkedList));
	return list;
}

static LinkedList* linkedlist_insert(LinkedList* list, Person* item) 
{
	if (!list) 
	{
		LinkedList* head = allocate_list();
		head->item = item;
		head->next = NULL;
		list = head;
		return list;
	}
	else if (list->next == NULL) 
	{
		LinkedList* node = allocate_list();
		node->item = item;
		node->next = NULL;
		list->next = node;
		return list;
	}

	LinkedList* temp = list;
	while (temp->next) 
	{
		temp = temp->next;
	}

	LinkedList* node = allocate_list();
	node->item = item;
	node->next = NULL;
	temp->next = node;

	return list;
}

Person* linkedlist_remove(LinkedList* list) 
{
	if (!list)
		return NULL;
	if (!list->next)
		return NULL;
	LinkedList* node = list->next;
	LinkedList* temp = list;
	temp->next = NULL;
	list = node;
	Person* it = NULL;
	memcpy(temp->item, it, sizeof(Person));
	free(temp->item->FIO);
	free(temp->item->passport_ID);
	free(temp->item->phone_number);
	free(temp->item);
	free(temp);
	return it;
}

void free_linkedlist(LinkedList* list) 
{
	LinkedList* temp = list;
	if (!list)
		return;
	while (list) 
	{
		temp = list;
		list = list->next;
		free(temp->item->FIO);
		free(temp->item->passport_ID);
		free(temp->item->phone_number);
		free(temp->item);
		free(temp);
	}
}

LinkedList** create_overflow_buckets(HashTable* table) 
{
	LinkedList** buckets = (LinkedList**)calloc(table->size, sizeof(LinkedList*));
	for (int i = 0; i < table->size; i++)
		buckets[i] = NULL;
	return buckets;
}

void free_overflow_buckets(HashTable* table) 
{
	LinkedList** buckets = table->overflow_buckets;
	for (int i = 0; i < table->size; i++)
		free_linkedlist(buckets[i]);
	free(buckets);
}


////////////////////////////////////////////////////////////////

//Создание элементов хэш-таблицы
Person* create_item(char* FIO, char* passport_ID, char* phone_number) 
{
	Person* item = (Person*)malloc(sizeof(Person));
	item->FIO = (char*)malloc(strlen(FIO) + 1);
	item->passport_ID  = (char*)malloc(strlen(passport_ID) + 1);
	item->phone_number = (char*)malloc(strlen(phone_number) + 1);

	strcpy(item->FIO, FIO);
	strcpy(item->passport_ID, passport_ID);
	strcpy(item->phone_number, phone_number);

	return item;
}

//Создание самой хэш - таблицы
HashTable* create_table(int size) 
{
	HashTable* table = (HashTable*)malloc(sizeof(HashTable));
	table->size = size;
	table->count = 0;
	table->items = (Person**)calloc(table->size, sizeof(Person*));
	for (int i = 0; i < table->size; i++)
	{
		table->items[i] = NULL;
	}
	table->overflow_buckets = create_overflow_buckets(table);

	return table;
}

//Освобождение элемента хэш-таблицы из памяти
void free_item(Person* item) 
{
	free(item->FIO);
	free(item->passport_ID);
	free(item->phone_number);
	free(item);
}

//Освобождение всей хэш-таблицы из памяти
void free_table(HashTable* table) 
{
	for (int i = 0; i < table->size; i++) 
	{
		Person* item = table->items[i];
		if (item != NULL)
			free_item(item);
	}

	free_overflow_buckets(table);
	free(table->items);
	free(table);
}

//-------------------------------------------------------

void handle_collision(HashTable* table, unsigned long index, Person* item) {
	LinkedList* head = table->overflow_buckets[index];

	if (head == NULL) 
	{
		head = allocate_list();
		head->item = item;
		table->overflow_buckets[index] = head;
		return;
	}
	else 
	{
		table->overflow_buckets[index] = linkedlist_insert(head, item);
		return;
	}
}

void ht_insert(HashTable* table, char* FIO, char* passport_ID, char* phone_number) 
{
	Person* item = create_item(FIO, passport_ID, phone_number);
	int index = hash_function(FIO);
	Person* current_item = table->items[index];

	if (current_item == NULL) 
	{
		if (table->count == table->size) 
		{
			cout << "Таблица переполнена" << endl;
			free_item(item);
			return;
		}

		table->items[index] = item;
		table->count++;
	}
	else 
	{
		if (strcmp(current_item->FIO, FIO) == 0) 
		{
			free(table->items[index]->passport_ID);
			free(table->items[index]->phone_number);

			table->items[index]->passport_ID = (char*)calloc(strlen(passport_ID) + 1, sizeof(char));
			table->items[index]->phone_number = (char*)calloc(strlen(phone_number) + 1, sizeof(char));

			strcpy(table->items[index]->passport_ID, passport_ID);
			strcpy(table->items[index]->phone_number, phone_number);

			free_item(item);
			return;
		}
		else 
		{
			handle_collision(table, index, item);
			return;
		}
	}
}

struct Tuple 
{
	const char* passport;
	const char* telefon;
};


struct Tuple ht_search(HashTable* table, char* FIO)
{
	int index = hash_function(FIO);
	Person* item = table->items[index];

	LinkedList* head = table->overflow_buckets[index];

	struct Tuple tuple = { "", "" };

	while (item != NULL) 
	{
		if (strcmp(item->FIO, FIO) == 0)
		{
			struct Tuple tuple = { item->passport_ID, item->phone_number };
			return tuple;
		}
		if (head == NULL)
			return tuple;
		item = head->item;
		head = head->next;
	}
	return tuple;
}

void ht_delete(HashTable* table, char* key) 
{
	int index = hash_function(key);
	Person* item = table->items[index];
	LinkedList* head = table->overflow_buckets[index];

	if (item == NULL) 
	{
		return;
	}
	else {
		if (head == NULL && strcmp(item->FIO, key) == 0) 
		{
			table->items[index] = NULL;
			free_item(item);
			table->count--;
			return;
		}
		else if (head != NULL) {
			if (strcmp(item->FIO, key) == 0) 
			{
				free_item(item);
				LinkedList* node = head;
				head = head->next;
				node->next = NULL;
				table->items[index] = create_item(node->item->FIO, node->item->passport_ID, node->item->phone_number);
				free_linkedlist(node);
				table->overflow_buckets[index] = head;
				return;
			}

			LinkedList* curr = head;
			LinkedList* prev = NULL;

			while (curr) 
			{
				if (strcmp(curr->item->FIO, key) == 0) 
				{
					if (prev == NULL) 
					{
						// First element of the chain. Remove the chain
						free_linkedlist(head);
						table->overflow_buckets[index] = NULL;
						return;
					}
					else 
					{
						// This is somewhere in the chain
						prev->next = curr->next;
						curr->next = NULL;
						free_linkedlist(curr);
						table->overflow_buckets[index] = head;
						return;
					}
				}
				curr = curr->next;
				prev = curr;
			}
		}
	}
}

void print_search(HashTable* table, char* FIO) {
	char* val;
	struct Tuple tuple = ht_search(table, FIO);
	if (tuple.passport == "")
	{
		cout << "Такого ключа не существует" << endl;
		return;
	}
	else 
	{
		cout << "---------------------------------------------------" << endl;
		cout << FIO << " " << tuple.passport << " " << tuple.telefon << endl;
		cout << "---------------------------------------------------" << endl;
		/*cout << endl << ht_search(table, FIO) << " -\t"
			 << table->items[ht_search(table, FIO)]->FIO << endl
			 << "\t" << table->items[ht_search(table, FIO)]->passport_ID << "\t"
			 << table->items[ht_search(table, FIO)]->phone_number << endl;*/
	}
}

void print_table(HashTable* table) 
{
	int schet_elem = 0;
	int collision = 0;
	for (int i = 0,obsh_index = 1; i < table->size; i++) {
		if (table->items[i])
		{
			schet_elem += 1;
			
			cout << obsh_index <<"\t" << "[" << i << "]" << "[" << 1 << "]   " << "\t" << table->items[i]->FIO << endl;
			
			//Паста для проверки
			/*
			cout << "\t" << table->items[i]->passport_ID << "\t"
			<< table->items[i]->phone_number << endl
			<< "____________________________________________________" << endl;
			*/

			if (table->overflow_buckets[i]) 
			{
				LinkedList* head = table->overflow_buckets[i];
				int vnutr_schet = 2;
				while (head)
				{
					obsh_index += 1;
					cout << obsh_index << "\t" << "[" << i << "]" << "[" << vnutr_schet << "]   " << "\t" << head->item->FIO << endl;

					//Паста для проверки
					/*
					cout << "\t" << head->item->passport_ID << "\t"
						<< head->item->phone_number << endl
						<< "____________________________________________________" << endl;
					*/

					head = head->next;
					vnutr_schet += 1;
					collision += 1;
				}
			}
			obsh_index += 1;
		}

	}
	if (schet_elem == 0) cout << "Таблица пуста" << endl;
	else if (schet_elem != 0) cout << "Коллизий - " << collision << endl;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(time(NULL));
	
	int vibor;
	bool loop = true;
	int kol_vo_elem;

	HashTable* ht = create_table(DLINNA);

	string menu[]
	{
		"Создать и заполнить хэш-таблицу рандобными значениями",
		"Самостоятельно задать хэш-таблицу",
		"Добавить элемент в хэш-таблицу",
		"Найти элемент хэш-таблицы",
		"Удалить элемент из хэш-таблицы",
		"Записать хэш-таблицу в файл (не работает)",
		"Прочитать хэш-таблицу из файла (не работает)",
		"Удалить хэш-таблицу из памяти (не работает)",
		"Вывести хэш-таблицу"
	};

	while (loop == true)
	{
		cout << "Что нужно сделать:" << endl;
		for (int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++)
		{
			cout << i + 1 << ") " << menu[i] << endl;
		}
		cout << "Выбор - "; (cin >> vibor).get();
		if (vibor > 0 && vibor < (sizeof(menu) / sizeof(menu[0])+1))
		{
			if (vibor == 1)				//Создать и заполнить хэш-таблицу рандобными значениями
			{
				cout << "Сколько элементов в хэш-таблице - "; (cin >> kol_vo_elem).get();
				
				for (int i = 0; i < kol_vo_elem; i++)
				{
					string space = " ";
					string FULL_NAME = two_name[rand() % 5] + space + name[rand() % 5] + space + three_name[rand() % 5];
					char* Full_name = &*FULL_NAME.begin();
					char* Pass_ID = &*pass_ID[rand() % 5].begin();
					char* Phone_num = &*phone_num[rand() % 5].begin();
					ht_insert(ht, Full_name, Pass_ID, Phone_num);
				}
				print_table(ht);
				system("pause");
				system("cls");
			}
			if (vibor == 2)				//Самостоятельно задать хэш-таблицу
			
			{
				cout << "Сколько элементов в хэш-таблице - "; (cin >> kol_vo_elem).get();

				for (int i = 0; i < kol_vo_elem; i++)
				{
					string FULL_NAME;
					string PASSPORT;
					string TELEF;

					cout << i+1 << " ----------------------------------" << endl;
					cout << "ФИО - "; getline(cin, FULL_NAME);
					cout << "Номер паспорта - "; getline(cin, PASSPORT);
					cout << "Номер телефона - "; getline(cin, TELEF);

					char* Full_name = &*FULL_NAME.begin();
					char* Pass_ID = &*PASSPORT.begin();
					char* Phone_num = &*TELEF.begin();

					ht_insert(ht, Full_name, Pass_ID, Phone_num);
				}
				print_table(ht);
				system("pause");
				system("cls");
			}
			if (vibor == 3)				//Добавить элемент в хэш-таблицу
			{
				string FULL_NAME;
				string PASSPORT;
				string TELEF;

				cout << "ФИО - "; getline(cin, FULL_NAME);
				cout << "Номер паспорта - "; getline(cin, PASSPORT);
				cout << "Номер телефона - "; getline(cin, TELEF);

				char* Full_name = &*FULL_NAME.begin();
				char* Pass_ID = &*PASSPORT.begin();
				char* Phone_num = &*TELEF.begin();

				ht_insert(ht, Full_name, Pass_ID, Phone_num);

				system("pause");
				system("cls");
			}
			if (vibor == 4)				//Найти элемент хэш - таблицы
			{
				print_table(ht);
				string hash_key;
				cout << "Какой ключ элемента найти - "; getline(cin, hash_key);
				char* Hash_key = &*hash_key.begin();
				print_search(ht, Hash_key);
				system("pause");
				system("cls");
			}
			if (vibor == 5)				//Удалить элемент из хэш-таблицы
			{
				print_table(ht);
				string del_elem;
				cout << "Ключ с каким элементом удалить - "; getline(cin, del_elem);
				char* Del_elem = &*del_elem.begin();

				ht_delete(ht, Del_elem);
				system("pause");
				system("cls");
			}
			if (vibor == 6)				//Записать хэш-таблицу в файл
			{
				system("pause");
				system("cls");
			}
			if (vibor == 7)				//Прочитать хэш-таблицу из файла
			{
				system("pause");
				system("cls");
			}
			if (vibor == 8)				//Удалить хэш-таблицу из памяти
			{
				free_table(ht);
				system("pause");
				system("cls");
			}
			if (vibor == 9)				//Вывести хэш-таблицу
			{
				print_table(ht);
				system("pause");
				system("cls");
			}
		}
		else
		{
			cout << "Выход из программы" << endl;
			loop = false;
		}
	}
	return 0;
}

