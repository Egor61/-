#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include<malloc.h>

const char Menu[] = "Выберите пункт меню введя соответсвующую цифру:\n"
"1.Создание новой записи в базе данных\n"
"2.Чтение всех записей\n"
"3.Cортировка записей по колличеству зведз, в порядке убывания \n"
"4.Поиск по Названию проекта\n"
"5.Поиск по колличеству проблем\n"
"6.Сохранение новых записей в файл\n"
"7.Изменение выбранной записи\n"
"8.Выход из программы\n";

struct Git {
	char name[30];
	char description[250];
	int language;
	float stars;
	int forks;
	int problems;
}; typedef struct Git pole_t;

void CreateNewFile(FILE* fdb, char name[]); // ОБьявление функции для создания рабочего текстового файла с заданным именем

pole_t* InitializationOfBaseFromFile(char name[], pole_t* Base_t, int* MassiveSize); // Обьявление функции для первоначального считывания данных из текстового файла

pole_t* IncreaseArraySize(pole_t* Base_t, int oldMassiveSize, int newMassiveSize); // Обьявление функции для перераспределния памяти под массив с проверкой на ошибку выделения памяти

pole_t* AddInfoToEmptyPlace(pole_t* Base_t, int MassiveSize); //  Обьявление функции для добавления данных в новую пустую ячейку массива 

pole_t* EditBaseByNumber(pole_t* Base_t, int EditNumber);

void PrintBase(pole_t* Base_t, int MassiveSize); // Обьявление функции для печати всех полей массива в определнном виде

void SaveToFile(int* MassiveSize, pole_t* Base_t, char name[]); // Обьявление функции для записи изменений совершенных в базе данных в файл 

int CompareToQsort(const pole_t* Base1_t, const pole_t* Base2_t); // Обьявление функциии компаратора для использования алгоритма сортировки qsort

int* SearchByName(pole_t* Base_t, int MassiveSize, char NameForSearch[], int* SearchResults);// Обьявление функции для поиска индексов элементов массива по имени

int* SearchByProblems(pole_t* Base_t, int MassiveSize, int ProblemsForSearch, int* SearchResults);// Обьявление функции для поиска индексов элементов массива по колличеству проблем

int main() {
	setlocale(LC_ALL, 0);// Установка локализации консоли и ее очистка
	system("chcp 1251");
	system("cls");

	FILE* fdb; // Определние переменной для работы с файловым потоком
	pole_t* Base_t; //Обьявление переменных используемых для хранения массива данных

	int* MassiveSize = (int*)malloc(1 * sizeof(int)); // Выделение памяти под перменную предназначенную для начальной инициализации базы из файла
	//int TempSize = 1;

	int StateOfFile = 0;//Обьявление переменных используемых для реализации различных меню
	int ExitState = 0;
	int StateOfSwitch = 0;
	int SaveState = 1;// Обьявление переменной для проверки производилось сохранение базы в файл или нет
	int numedit = 0;

	char name[] = "Base.txt";//Определение переменной содержащей в себе название файла с базой 

	char* NameForSearch[30];// Обьявление перменных используемых для поисковых функции
	int ProblemsForSearch = 0;

	//Проверка существания файла с базой и усспешности его открытия
	if ((fdb = fopen(name, "r")) == NULL) {
		printf("Не удалось найти файл\n Хотите создать новый файл?\n 1.Создать новый файл\n 2. Завершить работу программы");
		scanf("%d", &StateOfFile);
		if (StateOfFile == 1) {
			CreateNewFile(fdb, name);
		}
		else {
			free(MassiveSize);
			return 0;
		}
	}
	fclose(fdb);
	Base_t = (pole_t*)calloc(1, sizeof(pole_t));//Выделение первоначальной ячейки памяти под массив
	Base_t = InitializationOfBaseFromFile(name, Base_t, MassiveSize);// Инициализация массива из файла
	printf("\t Программа для работы с базой данных \"Проекты на GitHub\" \n");
	printf("Выберите пункт меню введя соответсвующую цифру:\n"
		"1.Создание новой записи в базе данных\n"
		"2.Чтение всех записей\n"
		"3.Cортировка записей по колличеству зведз, в порядке убывания \n"
		"4.Поиск по названию проекта\n"
		"5.Поиск по колличеству проблем\n"
		"6.Сохранение новых записей в файл\n"
		"7.Изменение выбранной записи\n"
		"8.Выход из программы\n");

	// Реализация пользователььского меню для взаимодействия с программой с помощью цикла while и оператора switch
	while (ExitState != 1) {
		int TeeporarySize = *MassiveSize;
		int* SearchResults = (int*)calloc(TeeporarySize, sizeof(int));
		//TempSize = *MassiveSize;
		scanf("%d", &StateOfSwitch);
		switch (StateOfSwitch)
		{
		case 1:
			system("cls");;
			printf("%d", *MassiveSize);
			Base_t = IncreaseArraySize(Base_t, *MassiveSize, *MassiveSize + 1);
			*MassiveSize = *MassiveSize + 1;
			Base_t = AddInfoToEmptyPlace(Base_t, TeeporarySize);
			printf("\n%d\n", *MassiveSize);
			printf("Запись добавлена в базу\n");
			printf(Menu);
			SaveState = 0;
			break;
		case 2:
			system("cls");
			PrintBase(Base_t, TeeporarySize);
			getchar();
			printf(Menu);
			break;
		case 3:
			system("cls");
			qsort(Base_t, TeeporarySize, sizeof(pole_t), CompareToQsort);
			PrintBase(Base_t, TeeporarySize);
			printf(Menu);
			SaveState = 0;
			break;
		case 4:
			system("cls");
			printf("Введите навзание проекта для поиска его в базе\n");
			if (scanf("%s", &NameForSearch) != 1) return 1;
			printf("По имени %s найденны следующие записи\n", NameForSearch);
			SearchResults = SearchByName(Base_t, TeeporarySize, NameForSearch, SearchResults);
			for (int i = 0; i < TeeporarySize; i++) {
				int FoundIndex = *SearchResults++;
				if (FoundIndex >= 0 && FoundIndex <= TeeporarySize) {
					printf("Название: %s\nОписание: %s\n", Base_t[FoundIndex].name, Base_t[FoundIndex].description);
					switch (Base_t[FoundIndex].language)
					{
					case 1:
						printf("Язык: C++\t");
						break;
					case 2:
						printf("Язык: C\t");
						break;
					case 3:
						printf("Язык: C#\t");
						break;
					case 4:
						printf("Язык: Python\t");
						break;
					case 5:
						printf("Язык: Java\t");
						break;
					default:
						printf("Другой язык\t");
						break;
					}
					printf("Звезды: %f\tФорки: %d\tПроблемы: %d\n", Base_t[FoundIndex].stars, Base_t[FoundIndex].forks, Base_t[FoundIndex].problems);
				}
			}
			printf(Menu);
			break;
		case 5:
			system("cls");
			printf("Введите колличество проблем для поиска проектов\n");
			if (scanf("%d", &ProblemsForSearch) != 1) return 1;
			printf("Со следующим колличеством проблем %d\nнайденны следующие проекты\n\n", ProblemsForSearch);
			SearchResults = SearchByProblems(Base_t, TeeporarySize, ProblemsForSearch, SearchResults);
			for (int i = 0; i < TeeporarySize; i++) {
				int FoundIndex = *SearchResults++;
				if (FoundIndex >= 0 && FoundIndex <= TeeporarySize) {
					printf("%Название: %s\nОписание: %s\n", Base_t[FoundIndex].name, Base_t[FoundIndex].description);
					switch (Base_t[FoundIndex].language)
					{
					case 1:
						printf("Язык: C++\t");
						break;
					case 2:
						printf("Язык: C\t");
						break;
					case 3:
						printf("Язык: C#\t");
						break;
					case 4:
						printf("Язык: Python\t");
						break;
					case 5:
						printf("Язык: Java\t");
						break;
					default:
						printf("Другой язык\t");
						break;
					}
					printf("Звезды: %f\tФорки: %d\tПроблемы: %d\n\n", Base_t[FoundIndex].stars, Base_t[FoundIndex].forks, Base_t[FoundIndex].problems);
				}
			}
			printf(Menu);
			break;
		case 6:
			if (SaveState == 0) {
				SaveToFile(MassiveSize, Base_t, name);
				printf("Внесенные изменения были сохранены\n");
				SaveState = 1;
			}
			else printf("Нет изменений для сохранения");
			printf(Menu);
			break;
		case 7:

			printf("Выбрана функция изменения изменения поля\n");
			PrintBase(Base_t, TeeporarySize);
			scanf("%d", &numedit);
			Base_t = EditBaseByNumber(Base_t, numedit);
			break;
		case 8:
			if (SaveState == 0) {
				printf("Есть не сохраненные изменения в базе\nПроизвести сохранение изменений\n1. Да\n2. Нет\n");
				scanf("%d", &StateOfFile);
				if (StateOfFile == 1) {
					SaveToFile(MassiveSize, Base_t, name);
					printf("Внесенные изменения были сохранены\n");
				}
			}
			free(Base_t);
			free(SearchResults);
			exit(0);
			break;
		default:
			break;
		}
	}
}

//Определение функции для создания файла с базой в случае его отсуствия
void CreateNewFile(FILE* fdb, char name[]) {
	fdb = fopen(name, "w+");
	fprintf(fdb, "GithubKursProject\n");
	fprintf(fdb, "Kurs Project\n");
	fprintf(fdb, "2\n");
	fprintf(fdb, "5\n");
	fprintf(fdb, "0\n");
	fprintf(fdb, "0\n");
	fprintf(fdb, "\n");
}

//Определение функции для первоначальной инициализации базы из файла 
pole_t* InitializationOfBaseFromFile(char name[], pole_t* Base_t, int* MassiveSize) {
	FILE* fdb;
	int newsize = 1, i = 0;
	fdb = fopen(name, "r");
	while (!feof(fdb)) {
		newsize++;
		if (i > 0)Base_t = (pole_t*)realloc(Base_t, (newsize) * sizeof(pole_t));
		fscanf(fdb, "%s", &Base_t[i].name);
		fscanf(fdb, "%s", &Base_t[i].description);
		fscanf(fdb, "%d", &Base_t[i].language);
		fscanf(fdb, "%f", &Base_t[i].stars);
		fscanf(fdb, "%d", &Base_t[i].forks);
		fscanf(fdb, "%d", &Base_t[i].problems);
		i++;
	}
	newsize = --i;
	*MassiveSize = newsize;
	return Base_t;
}

//Определение функции для печати базы в заданном виде
void PrintBase(pole_t* Base_t, int MassiveSize) {
	for (int i = 0; i < MassiveSize; i++) {
		printf("\n");
		printf("%d.  Имя: %s\n", i, &Base_t[i].name);
		printf("Описание: %s\n", &Base_t[i].description);
		switch (Base_t[i].language)
		{
		case 1:
			printf("Язык: ");
			printf("C++\t");
			break;
		case 2:
			printf("Язык: ");
			printf("C\t");
			break;
		case 3:
			printf("Язык: ");
			printf("C#\t");
			break;
		case 4:
			printf("Язык: ");
			printf("Python\t");
			break;
		case 5:
			printf("Язык: ");
			printf("Java\t");
			break;
		default:
			printf("Другой язык\t");
			break;
		}
		printf("Звезды: %f\t", Base_t[i].stars);
		printf("Форки: %d\t", Base_t[i].forks);
		printf("Проблемы: %d\n", Base_t[i].problems);
	}

}

//Определение функции для сохранения изменений в базе в текстовый файл
void SaveToFile(int* MassiveSize, pole_t* Base_t, char name[]) {
	FILE* fdb;
	fdb = fopen(name, "w+");
	for (int i = 0; i < *MassiveSize; i++) {
		fprintf(fdb, "%s\n", Base_t[i].name);
		fprintf(fdb, "%s\n", Base_t[i].description);
		fprintf(fdb, "%d\n", Base_t[i].language);
		fprintf(fdb, "%f\n", Base_t[i].stars);
		fprintf(fdb, "%d\n", Base_t[i].forks);
		fprintf(fdb, "%d\n", Base_t[i].problems);
		fprintf(fdb, "\n");
	}
	fclose(fdb);
}

//Определение функции компаратора
int CompareToQsort(const pole_t* Base1_t, const pole_t* Base2_t) {
	const struct Git* a = Base1_t, * b = Base2_t;
	float stars1, stars2;
	stars1 = a->stars;
	stars2 = b->stars;
	if (stars1 < stars2) return 1;
	if (stars1 > stars2) return -1;
	if (stars1 == stars2) return 0;
}

//Определение функции для поиска по имени
int* SearchByName(pole_t* Base_t, int MassiveSize, char NameForSearch[], int* SearchResults) {
	int n = 0;
	for (int i = 0; i < MassiveSize; i++) {
		if (strcmp(Base_t[i].name, NameForSearch) == 0) {
			SearchResults[n++] = i;
		}
		else SearchResults[n++] = MassiveSize + 10;
	}
	return SearchResults;
}

//Определение функции для поиска по колличеству проблем
int* SearchByProblems(pole_t* Base_t, int MassiveSize, int ProblemsForSearch, int* SearchResults) {
	int n = 0;
	for (int i = 0; i < MassiveSize; i++) {
		if (Base_t[i].problems == ProblemsForSearch) {
			SearchResults[n++] = i;
		}
		else SearchResults[i] = MassiveSize + 10;
	}
	return SearchResults;
}

//Определение функнции для перевыделения памяти на массив
pole_t* IncreaseArraySize(pole_t* Base_T, int oldMassiveSize, int newMassiveSize) {
	pole_t* newBase_T = (pole_t*)realloc(Base_T, newMassiveSize * sizeof(pole_t));
	if (newBase_T == NULL) {
		printf("\a Ошибка при увелечении размера массива\n");
		return Base_T;
	}
	return newBase_T;
}

//Определение функции для добавления в массив новой записи
pole_t* AddInfoToEmptyPlace(pole_t* Base_t, int MassiveSize) {
	printf("Введите название проекта\n");
	if (scanf("%s", &Base_t[MassiveSize].name) != 1) return 1;

	printf("Введите краткое описание (256 символов)\n");
	if (scanf("%s", &Base_t[MassiveSize].description) != 1) return 1;

	printf("Выберете из списка язык прокета \n");
	printf("1.C++\n2.C\n3.C#\n4.Python\n5.Java\n");
	if (scanf("%d", &Base_t[MassiveSize].language) != 1) return 1;

	printf("Введите колличество звезд у проекта\n");
	if (scanf("%f", &Base_t[MassiveSize].stars) != 1) return 1;

	printf("Введите колличество форков\n");
	if (scanf("%d", &Base_t[MassiveSize].forks) != 1) return 1;

	printf("Введите количество проблем\n");
	if (scanf("%d", &Base_t[MassiveSize].problems) != 1) return 1;
	return Base_t;
}

pole_t* EditBaseByNumber(pole_t* Base_t, int EditNumber) {
	printf("Начальная запись выбранная для редактирования\t Имя: %s\nОписание: %s\n", Base_t[EditNumber].name, Base_t[EditNumber].description);
	switch (Base_t[EditNumber].language)
	{
	case 1:
		printf("Язык: C++\t");
		break;
	case 2:
		printf("Язык: C\t");
		break;
	case 3:
		printf("Язык: C#\t");
		break;
	case 4:
		printf("Язык: Python\t");
		break;
	case 5:
		printf("Язык: Java\t");
		break;
	default:
		printf("Другой язык\t");
		break;
	}
	printf("Звезды: %f\tФорки: %d\t Проблемы: %d\n", Base_t[EditNumber].stars, Base_t[EditNumber].forks, Base_t[EditNumber].problems);
	printf("Введите название проекта\n");
	if (scanf("%s", &Base_t[EditNumber].name) != 1) return 1;

	printf("Введите краткое описание (256 символов)\n");
	if (scanf("%s", &Base_t[EditNumber].description) != 1) return 1;

	printf("Выберете из списка язык прокета \n");
	printf("1.C++\n2.C\n3.C#\n4.Python\n5.Java\n");
	if (scanf("%d", &Base_t[EditNumber].language) != 1) return 1;

	printf("Введите колличество звезд у проекта\n");
	if (scanf("%f", &Base_t[EditNumber].stars) != 1) return 1;

	printf("Введите колличество форков\n");
	if (scanf("%d", &Base_t[EditNumber].forks) != 1) return 1;

	printf("Введите количество проблем\n");
	if (scanf("%d", &Base_t[EditNumber].problems) != 1) return 1;
	return Base_t;
}

