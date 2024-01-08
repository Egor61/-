#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include<malloc.h>

const char Menu[] = "�������� ����� ���� ����� �������������� �����:\n"
"1.�������� ����� ������ � ���� ������\n"
"2.������ ���� �������\n"
"3.C��������� ������� �� ����������� �����, � ������� �������� \n"
"4.����� �� �������� �������\n"
"5.����� �� ����������� �������\n"
"6.���������� ����� ������� � ����\n"
"7.��������� ��������� ������\n"
"8.����� �� ���������\n";

struct Git {
	char name[30];
	char description[250];
	int language;
	float stars;
	int forks;
	int problems;
}; typedef struct Git pole_t;

void CreateNewFile(FILE* fdb, char name[]); // ���������� ������� ��� �������� �������� ���������� ����� � �������� ������

pole_t* InitializationOfBaseFromFile(char name[], pole_t* Base_t, int* MassiveSize); // ���������� ������� ��� ��������������� ���������� ������ �� ���������� �����

pole_t* IncreaseArraySize(pole_t* Base_t, int oldMassiveSize, int newMassiveSize); // ���������� ������� ��� ���������������� ������ ��� ������ � ��������� �� ������ ��������� ������

pole_t* AddInfoToEmptyPlace(pole_t* Base_t, int MassiveSize); //  ���������� ������� ��� ���������� ������ � ����� ������ ������ ������� 

pole_t* EditBaseByNumber(pole_t* Base_t, int EditNumber);

void PrintBase(pole_t* Base_t, int MassiveSize); // ���������� ������� ��� ������ ���� ����� ������� � ����������� ����

void SaveToFile(int* MassiveSize, pole_t* Base_t, char name[]); // ���������� ������� ��� ������ ��������� ����������� � ���� ������ � ���� 

int CompareToQsort(const pole_t* Base1_t, const pole_t* Base2_t); // ���������� �������� ����������� ��� ������������� ��������� ���������� qsort

int* SearchByName(pole_t* Base_t, int MassiveSize, char NameForSearch[], int* SearchResults);// ���������� ������� ��� ������ �������� ��������� ������� �� �����

int* SearchByProblems(pole_t* Base_t, int MassiveSize, int ProblemsForSearch, int* SearchResults);// ���������� ������� ��� ������ �������� ��������� ������� �� ����������� �������

int main() {
	setlocale(LC_ALL, 0);// ��������� ����������� ������� � �� �������
	system("chcp 1251");
	system("cls");

	FILE* fdb; // ���������� ���������� ��� ������ � �������� �������
	pole_t* Base_t; //���������� ���������� ������������ ��� �������� ������� ������

	int* MassiveSize = (int*)malloc(1 * sizeof(int)); // ��������� ������ ��� ��������� ��������������� ��� ��������� ������������� ���� �� �����
	//int TempSize = 1;

	int StateOfFile = 0;//���������� ���������� ������������ ��� ���������� ��������� ����
	int ExitState = 0;
	int StateOfSwitch = 0;
	int SaveState = 1;// ���������� ���������� ��� �������� ������������� ���������� ���� � ���� ��� ���
	int numedit = 0;

	char name[] = "Base.txt";//����������� ���������� ���������� � ���� �������� ����� � ����� 

	char* NameForSearch[30];// ���������� ��������� ������������ ��� ��������� �������
	int ProblemsForSearch = 0;

	//�������� ����������� ����� � ����� � ����������� ��� ��������
	if ((fdb = fopen(name, "r")) == NULL) {
		printf("�� ������� ����� ����\n ������ ������� ����� ����?\n 1.������� ����� ����\n 2. ��������� ������ ���������");
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
	Base_t = (pole_t*)calloc(1, sizeof(pole_t));//��������� �������������� ������ ������ ��� ������
	Base_t = InitializationOfBaseFromFile(name, Base_t, MassiveSize);// ������������� ������� �� �����
	printf("\t ��������� ��� ������ � ����� ������ \"������� �� GitHub\" \n");
	printf("�������� ����� ���� ����� �������������� �����:\n"
		"1.�������� ����� ������ � ���� ������\n"
		"2.������ ���� �������\n"
		"3.C��������� ������� �� ����������� �����, � ������� �������� \n"
		"4.����� �� �������� �������\n"
		"5.����� �� ����������� �������\n"
		"6.���������� ����� ������� � ����\n"
		"7.��������� ��������� ������\n"
		"8.����� �� ���������\n");

	// ���������� ������������������ ���� ��� �������������� � ���������� � ������� ����� while � ��������� switch
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
			printf("������ ��������� � ����\n");
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
			printf("������� �������� ������� ��� ������ ��� � ����\n");
			if (scanf("%s", &NameForSearch) != 1) return 1;
			printf("�� ����� %s �������� ��������� ������\n", NameForSearch);
			SearchResults = SearchByName(Base_t, TeeporarySize, NameForSearch, SearchResults);
			for (int i = 0; i < TeeporarySize; i++) {
				int FoundIndex = *SearchResults++;
				if (FoundIndex >= 0 && FoundIndex <= TeeporarySize) {
					printf("��������: %s\n��������: %s\n", Base_t[FoundIndex].name, Base_t[FoundIndex].description);
					switch (Base_t[FoundIndex].language)
					{
					case 1:
						printf("����: C++\t");
						break;
					case 2:
						printf("����: C\t");
						break;
					case 3:
						printf("����: C#\t");
						break;
					case 4:
						printf("����: Python\t");
						break;
					case 5:
						printf("����: Java\t");
						break;
					default:
						printf("������ ����\t");
						break;
					}
					printf("������: %f\t�����: %d\t��������: %d\n", Base_t[FoundIndex].stars, Base_t[FoundIndex].forks, Base_t[FoundIndex].problems);
				}
			}
			printf(Menu);
			break;
		case 5:
			system("cls");
			printf("������� ����������� ������� ��� ������ ��������\n");
			if (scanf("%d", &ProblemsForSearch) != 1) return 1;
			printf("�� ��������� ������������ ������� %d\n�������� ��������� �������\n\n", ProblemsForSearch);
			SearchResults = SearchByProblems(Base_t, TeeporarySize, ProblemsForSearch, SearchResults);
			for (int i = 0; i < TeeporarySize; i++) {
				int FoundIndex = *SearchResults++;
				if (FoundIndex >= 0 && FoundIndex <= TeeporarySize) {
					printf("%��������: %s\n��������: %s\n", Base_t[FoundIndex].name, Base_t[FoundIndex].description);
					switch (Base_t[FoundIndex].language)
					{
					case 1:
						printf("����: C++\t");
						break;
					case 2:
						printf("����: C\t");
						break;
					case 3:
						printf("����: C#\t");
						break;
					case 4:
						printf("����: Python\t");
						break;
					case 5:
						printf("����: Java\t");
						break;
					default:
						printf("������ ����\t");
						break;
					}
					printf("������: %f\t�����: %d\t��������: %d\n\n", Base_t[FoundIndex].stars, Base_t[FoundIndex].forks, Base_t[FoundIndex].problems);
				}
			}
			printf(Menu);
			break;
		case 6:
			if (SaveState == 0) {
				SaveToFile(MassiveSize, Base_t, name);
				printf("��������� ��������� ���� ���������\n");
				SaveState = 1;
			}
			else printf("��� ��������� ��� ����������");
			printf(Menu);
			break;
		case 7:

			printf("������� ������� ��������� ��������� ����\n");
			PrintBase(Base_t, TeeporarySize);
			scanf("%d", &numedit);
			Base_t = EditBaseByNumber(Base_t, numedit);
			break;
		case 8:
			if (SaveState == 0) {
				printf("���� �� ����������� ��������� � ����\n���������� ���������� ���������\n1. ��\n2. ���\n");
				scanf("%d", &StateOfFile);
				if (StateOfFile == 1) {
					SaveToFile(MassiveSize, Base_t, name);
					printf("��������� ��������� ���� ���������\n");
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

//����������� ������� ��� �������� ����� � ����� � ������ ��� ���������
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

//����������� ������� ��� �������������� ������������� ���� �� ����� 
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

//����������� ������� ��� ������ ���� � �������� ����
void PrintBase(pole_t* Base_t, int MassiveSize) {
	for (int i = 0; i < MassiveSize; i++) {
		printf("\n");
		printf("%d.  ���: %s\n", i, &Base_t[i].name);
		printf("��������: %s\n", &Base_t[i].description);
		switch (Base_t[i].language)
		{
		case 1:
			printf("����: ");
			printf("C++\t");
			break;
		case 2:
			printf("����: ");
			printf("C\t");
			break;
		case 3:
			printf("����: ");
			printf("C#\t");
			break;
		case 4:
			printf("����: ");
			printf("Python\t");
			break;
		case 5:
			printf("����: ");
			printf("Java\t");
			break;
		default:
			printf("������ ����\t");
			break;
		}
		printf("������: %f\t", Base_t[i].stars);
		printf("�����: %d\t", Base_t[i].forks);
		printf("��������: %d\n", Base_t[i].problems);
	}

}

//����������� ������� ��� ���������� ��������� � ���� � ��������� ����
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

//����������� ������� �����������
int CompareToQsort(const pole_t* Base1_t, const pole_t* Base2_t) {
	const struct Git* a = Base1_t, * b = Base2_t;
	float stars1, stars2;
	stars1 = a->stars;
	stars2 = b->stars;
	if (stars1 < stars2) return 1;
	if (stars1 > stars2) return -1;
	if (stars1 == stars2) return 0;
}

//����������� ������� ��� ������ �� �����
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

//����������� ������� ��� ������ �� ����������� �������
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

//����������� �������� ��� ������������� ������ �� ������
pole_t* IncreaseArraySize(pole_t* Base_T, int oldMassiveSize, int newMassiveSize) {
	pole_t* newBase_T = (pole_t*)realloc(Base_T, newMassiveSize * sizeof(pole_t));
	if (newBase_T == NULL) {
		printf("\a ������ ��� ���������� ������� �������\n");
		return Base_T;
	}
	return newBase_T;
}

//����������� ������� ��� ���������� � ������ ����� ������
pole_t* AddInfoToEmptyPlace(pole_t* Base_t, int MassiveSize) {
	printf("������� �������� �������\n");
	if (scanf("%s", &Base_t[MassiveSize].name) != 1) return 1;

	printf("������� ������� �������� (256 ��������)\n");
	if (scanf("%s", &Base_t[MassiveSize].description) != 1) return 1;

	printf("�������� �� ������ ���� ������� \n");
	printf("1.C++\n2.C\n3.C#\n4.Python\n5.Java\n");
	if (scanf("%d", &Base_t[MassiveSize].language) != 1) return 1;

	printf("������� ����������� ����� � �������\n");
	if (scanf("%f", &Base_t[MassiveSize].stars) != 1) return 1;

	printf("������� ����������� ������\n");
	if (scanf("%d", &Base_t[MassiveSize].forks) != 1) return 1;

	printf("������� ���������� �������\n");
	if (scanf("%d", &Base_t[MassiveSize].problems) != 1) return 1;
	return Base_t;
}

pole_t* EditBaseByNumber(pole_t* Base_t, int EditNumber) {
	printf("��������� ������ ��������� ��� ��������������\t ���: %s\n��������: %s\n", Base_t[EditNumber].name, Base_t[EditNumber].description);
	switch (Base_t[EditNumber].language)
	{
	case 1:
		printf("����: C++\t");
		break;
	case 2:
		printf("����: C\t");
		break;
	case 3:
		printf("����: C#\t");
		break;
	case 4:
		printf("����: Python\t");
		break;
	case 5:
		printf("����: Java\t");
		break;
	default:
		printf("������ ����\t");
		break;
	}
	printf("������: %f\t�����: %d\t ��������: %d\n", Base_t[EditNumber].stars, Base_t[EditNumber].forks, Base_t[EditNumber].problems);
	printf("������� �������� �������\n");
	if (scanf("%s", &Base_t[EditNumber].name) != 1) return 1;

	printf("������� ������� �������� (256 ��������)\n");
	if (scanf("%s", &Base_t[EditNumber].description) != 1) return 1;

	printf("�������� �� ������ ���� ������� \n");
	printf("1.C++\n2.C\n3.C#\n4.Python\n5.Java\n");
	if (scanf("%d", &Base_t[EditNumber].language) != 1) return 1;

	printf("������� ����������� ����� � �������\n");
	if (scanf("%f", &Base_t[EditNumber].stars) != 1) return 1;

	printf("������� ����������� ������\n");
	if (scanf("%d", &Base_t[EditNumber].forks) != 1) return 1;

	printf("������� ���������� �������\n");
	if (scanf("%d", &Base_t[EditNumber].problems) != 1) return 1;
	return Base_t;
}

