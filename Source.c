#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <stdio.h>
#include <io.h>
#include <string.h>

#define n_columns 16 // ���-�� ��������, ����������� ��������
#define _USE_MATH_DEFINES

//��������� �������
int num_score(int **ptr_array, int index,int size); // ������� ��� �������� ������ ���������� ������ �������(������� ����� �� �����)
int find_quest(int** ptr_array, int size, int choose_quest, int choose_result); // ������� ��� ������ ������ �� ��������/�� �������� ���������� ������

void table1_on_screen(int** ptr_array, int size, int index); // �������, ������� ��������� ������� �� ����� ��� �������� ������� ��� ���� ���������� �������
void table2_on_screen(int** ptr_array, int size); // ������� ��� ������ �������������� �������

int sort_2d_array(int** ptr_array,int size, int choose_sort); // ������� ��� ���������� ��������� ������� ������� Bubble Sort

int input_from_file(char* filename); // �������, ������� ��������� ���� � ���������� ���������� ������ 
int remake_info_from_table(int** ptr_array, int size); // �������, ����������� ������ ������ � �������� �������  

int best_comand(int** ptr_array, int size); // �������, ������� ���������� ���������� ������� �� ������(������ �������)
int worst_comand(int** ptr_array, int size); // �������, ������� ���������� ������ ������� �� ������ 
//


void main() {
	setlocale(LC_ALL, "RUS"); // ���������� ����� �� �����
	srand(time(NULL));
	int choose, choose_2, choose_best_worst, choose_sort, num_quest, result; // ���������� ��� ������� � �������������
	
	int size=0; // ���������� ��� ������ ���-�� ������ 
	FILE* table_l; // ���������� ��� �����


	char* file_name[10]; // ���������� � ������� ������������ ��� �����
	char  extension[6] = { ".txt\0" }; // ���������� ��� ���������� ����� �����
	puts("������� �������� ����� � �������� 30 �������� (��� �������� ���������� �����)");
	scanf("%s", &file_name); // ��������� ��� �����
	printf("��� �����: %s\n", file_name); // ������� �� ����� ��� �����

	size = input_from_file(file_name); // ���������� �������, ����� ������� ���������� ������ �� �����
	//strcat(file_name, extension); // ���������� ���������� � ��� ����� ��� ��� �������� 

	int** table = (int**)malloc(sizeof(int*) * n_columns);
	for (int i = 0; i < n_columns; i++) {
		*(table + i) = (int*)malloc(sizeof(int) * size); // ���������� ������������� ���������� ������� �� ������ ��������� �� ����� ������
	}
	table_l = fopen(file_name, "rt"); // ��������� ���� ��� ���������� ������ ������
	for (int i = 0; i < size; i++) {
		fscanf(table_l, "%d ", &table[0][i]); // ��������� ������ ������� 
		for (int j = 1; j < n_columns - 2; j++) { 
			fscanf(table_l, "%d, ", &table[j][i]); // ��������� �������� ����� ������ � ��������� 
		}
		fscanf(table_l, "%d\n", &table[14][i]); // ��������� ��������� �������
		table[15][i] = num_score(table, i, size); // ������������� ����������� 15 �������, � ������� ����� ��������� ����� ���-�� ������ ������� 
	}


	while (1) {

		printf("---------------------------------------------------------------------------------------------------\n���������� ����������������\n\n�������� ���� �� ���������:\n������� �������\n	11. ��������\n	12. ��������������\n2. �����\n3. ���������� �� �������\n4. ��������� ������ � �������\n5. ������� ������/������ �������\n0. ��������� ���������\n");
		scanf_s("%d", &choose); // ��������� �������� ������� ������ ������������ 


		switch (choose) {
		case 0: {
			exit(0); // ����� �� ��������� 
		}
		case 11: {
			system("cls"); // �������� ������ 
			table1_on_screen(table, size, -1, 0); // ����� �������� ������� �� ����� 
			printf("\n");
			break;
		}
		case 12: {
			system("cls"); // ������� ������ 
			table2_on_screen(table, size); // ����� �������������� ������� �� �����
			printf("\n");
			break;
		}
		case 2: {
			system("cls");

			printf("������� ����� ������, �� ������� ������ ���������� ����� (1-12): ");
			scanf_s("%d", &num_quest); // ��������� ������ �� ������� ����� ����������� ����� 
			printf("���� �� ������ ������? (������� ����� ������):\n 1. �� \n 0. ���\n");
			scanf_s("%d", &result); // ��������� �� ������ ���������� �� ����� ������ ������� 

			char* zagolovok[16] = {
		"Id �������",
		" ���.1",
		" ���.2",
		" ���.3",
		" ���.4",
		"   ���.5",
		" ���.6",
		"  ���.7",
		"   ���.8",
		"   ���.9",
		" ���.10",
		" ���.11",
		" ���.12",
		" �����",
		"  ������",
		" ���-�� ������" }; // ��������� ��� ������ ����� ������� � �������� ���� 

			for (int i = 0; i < n_columns; i++) {
				printf("%s", *(zagolovok + i)); // ����� ��������� 
			}

			for (int i = 0; i < size; i++) { // ������� �������� ���� ������ � ���� ��� �������� �� ��������� ��������� ������, �� �� ������ �� ����� 
				table1_on_screen(table, size, find_quest(table, size, num_quest, result, i), 1); // �������� ���������� � ������� ������ � ������ 
			}
			printf("\n");
			
			break;
		}
		case 3: {
			system("cls");

			printf("����������:\n1. �� �����������\n2. �� ��������\n");
			scanf_s("%d", &choose_sort); // ����� ��� ����������� ��������� ������ 

			sort_2d_array(table, size, choose_sort); // ���������� ������� �� ������� 
			system("cls"); // ������� ������ 
			table1_on_screen(table, size, -1, 0); // ����� ����� ��������������� �������� ������� �� ����� 
			break;
		}
		case 4: {
			system("cls"); // ������� ������ 

			if (remake_info_from_table(table, size) == 0) { // ������ ������ � �������� � �������, �� ���� ���� ������� �������� ������, �� ��� �� ��������
				printf("������ �� ���� �������� � ����� � �������� �����������, ��������� ���������� ��������!\n");
			};

			break;
		}
		case 5: {
			system("cls"); // ������� ������ 
			printf("����� ������ ����� �������?\n1. ������\n2. ������: ");
			scanf_s("%d", &choose_best_worst); // ����� ����� ������� ������� ������ ��� ������
			if (choose_best_worst == 1) printf("������ ������� �%d � %d ������� � ����������� ����� %d ������",best_comand(table, size)+1, *(*(table + 15) + best_comand(table, size)), *(*(table + 14) + best_comand(table, size))); // ������ � �����������, ���� ������� 1, �� ����� ������ ������� ����������� �� ������� 
			if (choose_best_worst == 2) printf("������ ������� �%d c %d ������� � ����������� %d ������",worst_comand(table, size)+1, *(*(table + 15) + worst_comand(table, size)), *(*(table + 14) + worst_comand(table, size))); // ������ � �����������, ���� ������� 2, �� ����� ������ ������� ����������� �� �������
			printf("\n\n");
			break;
		}
		default: {
			system("cls"); // ������� ������ 
			printf("�������� ����� �� ������!\n"); // ����� ������ ���� �� ������� �������� ��������� ������������� 
			break;
		}
		}
	}

}


//������� ��� ������� ������ ���������� ������ ������� 
int num_score(int **ptr_array, int index,int size) {
	int id_team = *(ptr_array+index), num_score = 0, time_score;

	for (int i = 1; i < 13; i++) {
		num_score += *(*(ptr_array + i) + index); // ������� ����� �� �������� ������ 
	}

	time_score = *(*(ptr_array+13)+index) / 60; // ������� ������� ������ �������� �� ���������� ����� 
	num_score += time_score; // ���������� �������� ����� �� ����� 

	return num_score; // ���������� ����� ���������� ������ 
}
//


//������� ��� ������ ������ �� ����� 
void table1_on_screen(int** ptr_array, int size, int index, int flag) {
	char *zagolovok[16] = { 
		"Id �������", 
		" ���.1", 
		" ���.2", 
		" ���.3", 
		" ���.4", 
		"   ���.5", 
		" ���.6", 
		"  ���.7", 
		"   ���.8", 
		"   ���.9", 
		" ���.10", 
		" ���.11", 
		" ���.12", 
		" �����", 
		"  ������", 
		" ���-�� ������\n",}; // ��������� ��� ����� �������� ������ ������� ������������� 

	if (index == -5) return 0; // ���� �������� ������ ����� -5, �� ���������� 0, ����� ��� ������� ������, ����� �� �������� �������� �������
	
	if (flag == 0){ // ���� ���� ����� 0, �� �� �������� ������ ����, ����� ��� ������� ������, ����� ����� ��� ��������� �� ��������� 
		for (int i = 0; i < n_columns; i++) {
			printf("%s", *(zagolovok + i)); // ����� ��������� �� ����� 
		}
	}

	for (int i = 0; i < size; i++) { //������� ������ 
		if (index > -1) i = index; // ���� ������ ������ -1, �� �� ����������� i ���� ����� ������ ��� ������ � ���������� �������� 
		printf("\n");
		for (int j = 0; j < n_columns; j++) { // ������� �������� 
			if (j != 13) { // ���� ������� �� ����� 
				printf("%6d ", *(*(ptr_array + j) + i));// ����� �� ����� ���� �������� ����� ������� 
			}
			else { // ���� ������� �������, �� � ���� ������ ������ �� ���� 
				if (*(*(ptr_array + j) + i) % 60 > 9) { // ���� ����� ����� �������� ������ ���� �������� 
					printf("   0%d:%2d", *(*(ptr_array + j) + i) / 60, *(*(ptr_array + j) + i) % 60); // �������� ������� 2 ������� 
				}
				else { // ���� ����� ����� �������� ������ ���� �������� 
					printf("   0%d:0%d", *(*(ptr_array + j) + i) / 60, *(*(ptr_array + j) + i) % 60); // ������ ������ ��������� 0 ��� ����� ��������� ������ 
				}
			}
		}
		if (index > -1) return 0; // ���� ������ ������ -1, �� �� ����������� ���������, �� ��� ����� ��� ������ ����� ���������� �������, � �� ��� ������ ����� �������
	}
	printf("\n");
}
void table2_on_screen(int** ptr_array, int size) {
	printf("Id �������   ���-�� ������   ������\n"); // ����� ��������� 
	for (int i = 0; i < size; i++) {
		printf("  %d      %5d         %5d\n", *(*(ptr_array)+i), *(*(ptr_array+15) + i), *(*(ptr_array + 14) + i)); // �������� ���� �������, ����� ���������� ������ � ����������� ������
	}
}
//

//������� ��� ������ ������ �� ���������� ������������ ������
int find_quest(int **ptr_array,int size, int choose_quest, int choose_result, int index) {
	

	if (choose_quest > 12 || choose_quest < 1 || choose_result > 1 || choose_result < 0) { // �������� �� ���� ������ �������� 
		printf("������� �������� ������!");
		return -1;
	}

	if (*(*(ptr_array + choose_quest) + index) == choose_result) { // ���� ������� ������ ��������� � ��������� ������� ����������� �������, �� ���������� ������ 
		return index;
	}
	else {
		return -5; // ���� � ������� ����������� ������� ��������� ������ �� �������� ���������� -5, ��� ��������� � ���� ����� ��� ���������� �������� ������ �� ����� 
	}
}
//


//������� ��� ���������� ���������� ������� ������� "��������"
int sort_2d_array(int **ptr_array,int size, int choose) {
	int tmp; // ���������� ��� ��������� ���������� � �������� �������� �� ���������� � ���������� 

	for (int i = 0; i < n_columns; i++) { // ������� �������� 
		for (int j = 0; j < size-1; j++) { // ������� ������ 
			if (((choose == 1) && (ptr_array[13][j] > ptr_array[13][j + 1])) || ((choose == 2) && ((ptr_array[13][j] < ptr_array[13][j + 1])))) { 
				// ���� ������� ���������� �� �����������(1) � �������� ���� �������� ������ �������� �������� ������ ��������, �� ������
				// ���� ������� ���������� �� ��������(2) � �������� ���� �������� ������ �������� �������� ������ ��������, �� ������  
				for (int k = 0; k < n_columns; k++) {
					tmp = ptr_array[k][j];
					ptr_array[k][j] = ptr_array[k][j + 1];
					ptr_array[k][j + 1] = tmp;
				}
			}
		}
	}
	return 1;

}
//


//������� ��� ����� ���������� ������ �� ����� ��� �������� ������������� ���������� ������� 
int input_from_file(char* filename) {
	char  extension[6] = { ".txt\0" }; // ���������� ����� 
	int size = 0; // ���������� ������ 
	FILE* table_l; // ��������� �� ���������� ����
	
	
	strcat(filename, extension); // ���������� ����� ����� � ��� ���������� 
	table_l = fopen(filename, "rt"); // �������� ����� ��� ������ 

	while (!feof(table_l)) { // ���� ���� �� ���������� 
		if (fgetc(table_l) == '\n') // ���� ���� ������� �������� ������ 
		size += 1; // ���������� ���� ���� � ���������� ������ 
	}
	fclose(table_l); // ��������� ���� 
	return size; // ���������� ���������� ������ 
}
//

//function for remake info from table
int remake_info_from_table(int **ptr_array,int size) {
	int choose_team, choose_group, choose_value; // ���������� ��� ������ �������, ������� � �������� ��������� 

	table1_on_screen(ptr_array, size, -1, 0); // ������� �� ����� �������� �������, ����� ������������� ���� ������� 
	printf("\n\n� ����� ������� ����� �������� ��������?(1-%d)\n", size);
	scanf_s("%d", &choose_team); // ��������� ������� 
	//system("cls");//������� ����� 
	choose_team = choose_team - 1; // �������� 1, ����� �� �������� ���� ������� � ������
	if (choose_team > size-1) return 0; // ���� ������� �������� ������ �������, �� ������� �� ������� 
	
	table1_on_screen(ptr_array, size, choose_team, 0); // ������� �� ����� ���������� �������, ������� ������ ������������
	printf("\n\n����� ������� ����� ��������?(1-15)\n");
	scanf_s("%d", &choose_group); // ��������� �������, ������� ������������ ����� �������� 
	choose_group = choose_group - 1; // �������� 1 , ����� �� �������� ���� ������� � ������ ������� 



	if (choose_group != 13) { // ���� �� ������� ������� 
		printf("�� ����� �������� ����� ��������?\n");
		scanf_s("%d", &choose_value); // �������� �� ����� �������� ����� �������� 

		if ((choose_group == 0) && ((10000 > choose_value) || (choose_value > 99999))) { // ���� ������ ������, �� ���������, ����� � ����� ���� 5 ��������
			printf("������� ����� � 5 ���������!!\n\n");
			return 0;
		}
		if (((choose_group > 1) && (choose_group < size)) && ((choose_value < 0) || (choose_value > 1))) { // ���� ������ ��������� ������� ������. �� ����� ��� ���� ���� true(1) ���� false(0)
			printf("������� ���� 1 ���� 0!!\n\n");
			return 0;
		}
		if ((choose_group == 14) && ((choose_value > 100) || (choose_value < 70))) { // ���� ������ ������, �� ��� ������ ���� � ��������� �� 70 �� 100
			printf("������� ����� �� 70 �� 100!!\n\n");
			return 0;
		}

		*(*(ptr_array+choose_group)+choose_team) = choose_value; // ���� ��� �������� ���� ��������, �� �� ����������� ����� ��������
		*(*(ptr_array + 15) + choose_team) = num_score(ptr_array, choose_team, size); // ������������� ����� ���������� ������, �� ������� ����� ����� ���������� 
		table1_on_screen(ptr_array, size, -1, 0);
		return 1;
	}
	else { // ���� ������ ����� 
		int hours, minutes;
		printf("������ ���-�� ����� � ����� ����� ������: ");
		scanf_s("%d %d", &hours, &minutes); // ��������� ����� 
		if (((hours > 5) || (hours < 0)) || ((minutes > 60) || (minutes < 0))) { // � ��������� �� 5 ����� 
			printf("������� ���-�� ����� �� 5 � ���-�� ����� �� 60!!\n\n");
			return 0;
		}
		*(*(ptr_array+choose_group)+choose_team) = hours * 60 + minutes; // ���� �������� �������� ������ ��������
		*(*(ptr_array + 15) + choose_team) = num_score(ptr_array, choose_team, size); // ������������� ���������� ������ �� �������� ����� �� ����� ����� ���������� 

	}
	
	table1_on_screen(ptr_array, size, -1, 0);

}
//

// ������� ��� ������ ������� ��� ������� ������ 
int best_comand(int** ptr_array, int size) {
	int max_score = 0, max_volume = 0, index = 0; // ��������� ����� ����������� �������� �� ���� ������������ 

	for (int i = 0; i < size; i++) { // ���������� ������� 

		if (num_score(ptr_array, i, size) > max_score) { // ���� ���-�� ������ � �������� ������ ��������� ������, ��� ����������� �� ����������� 
			max_score = num_score(ptr_array, i, size);
			max_volume = *(*(ptr_array + 14) + i);
			index = i;
		}
		if (num_score(ptr_array, i, size) == max_score) { // ���� ���-�� ������ ����������, �� ���������� ������
			if (*(*(ptr_array + 14)+i) < max_volume) { // ���� �������� ������ �������� �������� ������ ������ ��� ������������, �� ��������������� 
				max_score = num_score(ptr_array, i, size);
				max_volume = *(*(ptr_array + 14) + i);
				index = i;
			}
			else {
				continue;
			}
		}
	}

	return index; // � ����� ���������� ������ ������ ������� 
}
int worst_comand(int** ptr_array, int size) {
	int min_score = 1000, min_volume = 1000, index = 0; //��������� ����� ����������� �������� �� ���� �����������

	for (int i = 0; i < size; i++) {

		if (num_score(ptr_array, i, size) < min_score) { // ���� ���-�� ������ � �������� ������ ��������� ������, ��� ���������� �� �����������
			min_score = *(*(ptr_array+15)+i);
			min_volume = *(*(ptr_array + 14) + i);
			index = i;
		}
		if (num_score(ptr_array, i, size) == min_score) {// ���� ���-�� ������ ����������, �� ���������� ������
			if (*(*(ptr_array + 14) + i) < min_volume) { // ���� �������� ������ �������� �������� ������ ������ ��� �����������, �� ���������������
				min_score = *(*(ptr_array + 15) + i);
				min_volume = *(*(ptr_array + 14) + i);
				index = i;
			}
			else {
				continue;
			}
		}
	}

	return index; // ���������� ������ ������ �������
}
//
