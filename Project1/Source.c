#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <stdio.h>
#include <io.h>
#include <string.h>

#define _USE_MATH_DEFINES

//functions
int num_score(int ptr_array[12][15], int index);

void tables_on_screen(int ptr_array[12][15], int attr);

int find_quest(int ptr_array[12][15]);

void sort_2d_array(int ptr_array[12][15]);
int input_from_file(int ptr_array[12][15]);

int remake_info_from_table(int ptr_array[12][15]);
//


void main() {
	setlocale(LC_ALL, "RUS");
	int choose, choose_2;
	int table[15][12];
	srand(time(NULL));

	if (input_from_file(table) == 0)  exit(0);

	while (1) {

		printf("---------------------------------------------------------------------------------------------------\n���������� ����������������\n\n�������� ���� �� ���������:\n������� �������\n	11. ��������\n	12. ��������������\n2. �����\n3. ���������� �� �����\n4. ��������� ������ � �������\n5. ������� ���������� �������\n0. ��������� ���������\n");
		scanf_s("%d", &choose);


		switch (choose) {
		case 0: {
			exit(0);
		}
		case 11: {
			system("cls");
			tables_on_screen(table, 1);
			printf("\n");
			break;
		}
		case 12: {
			system("cls");
			tables_on_screen(table, 2);
			printf("\n");
			break;
		}
		case 2: {
			system("cls");
			find_quest(table);
			break;
		}
		case 3: {
			system("cls");
			sort_2d_array(table);
			system("cls");
			tables_on_screen(table, 1);
			break;
		}
		case 4: {
			system("cls");
			remake_info_from_table(table);
			break;
		}
		case 5: {
			system("cls");
			tables_on_screen(table, 3);
			printf("\n\n");
			break;
		}
		default: {
			system("cls");
			printf("�������� ����� �� ������!\n");
			break;
		}
		}
	}

}




//function for sum score for teams
int num_score(int ptr_array[12][15], int index) {
	int id_team = ptr_array[index], num_score = 0, time_score;

	for (int i = 1; i < 13; i++) {
		num_score += ptr_array[i][index];
	}

	time_score = ptr_array[13][index] / 60;
	num_score += time_score;

	return num_score;
}
//


//function for table on screen
void tables_on_screen(int ptr_array[12][15], int attr) {
	if (attr == 1) {
		printf("Id ������� ���.1 ���.2 ���.3 ���.4   ���.5 ���.6  ���.7   ���.8   ���.9 ���.10 ���.11 ���.12 ���.����� ���.������");
		for (int i = 0; i < 12; i++) { //nlines
			printf("\n");
			for (int j = 0; j < 15; j++) { //ncols
				if (j != 13) {
					printf("%6d ", ptr_array[j][i]);//i * ncols + j
				}
				else {
					if (ptr_array[j][i] % 60 > 9) {
						printf("   0%d:%2d", ptr_array[j][i] / 60, ptr_array[j][i] % 60);
					}
					else {
						printf("   0%d:0%d", ptr_array[j][i] / 60, ptr_array[j][i] % 60);
					}
				}
			}
		}
		printf("\n");
	}
	if (attr == 2) {
		printf("Id �������   ���-�� ������   ���-�� ������\n");
		for (int i = 0; i < 12; i++) {
			printf("%6d              %2d		%2d\n", ptr_array[0][i], num_score(ptr_array, i), ptr_array[14][i]);
		}
	}
	if (attr == 3) {
		int max_score = 0, max_volume = 0, index = 0;

		for (int i = 0; i < 12; i++) {

			if (num_score(ptr_array, i) > max_score) {
				max_score = num_score(ptr_array, i);
				max_volume = ptr_array[14][i];
				index = i;
			}
			if (num_score(ptr_array, i) == max_score) {
				if (ptr_array[14][i] < max_volume) {
					max_score = num_score(ptr_array, i);
					max_volume = ptr_array[14][i];
					index = i;
				}
				else {
					continue;
				}
			}
		}

		printf("������ ����� ������ �������:\n");
		printf("Id ������� ���.1 ���.2 ���.3 ���.4   ���.5 ���.6  ���.7   ���.8   ���.9 ���.10 ���.11 ���.12 ���.����� ���.������\n");
		for (int j = 0; j < 15; j++) { //ncols
			if (j != 13) {
				printf("%6d ", ptr_array[j][index]);//i * ncols + j
			}
			else {
				if (ptr_array[j][index] % 60 > 9) {
					printf("   0%d:%2d", ptr_array[j][index] / 60, ptr_array[j][index] % 60);
				}
				else {
					printf("   0%d:0%d", ptr_array[j][index] / 60, ptr_array[j][index] % 60);
				}
			}
		}
		printf("\n\n");
		printf("������� ������� %d ������ � ������������ %d ������\n\n", num_score(ptr_array, index), ptr_array[14][index]);
	}
}



//function for find tasks
int find_quest(int ptr_array[12][15]) {
	int num_quest, result;

	printf("������� ����� ������, �� ������� ������ ���������� ����� (1-12): ");
	scanf_s("%d", &num_quest);
	printf("���� �� ������ ������? (������� ����� ������):\n 1. �� \n 0. ���\n");
	scanf_s("%d", &result);

	system("cls");
	printf("Id ������� ���.1 ���.2 ���.3 ���.4   ���.5 ���.6  ���.7   ���.8   ���.9 ���.10 ���.11 ���.12 ���.������   ���.�����\n");
	for (int i = 0; i < 12; i++) {

		if (ptr_array[num_quest][i] == result) {
			printf("%6d", ptr_array[0][i]);

			for (int k = 1; k < 13; k++) {
				printf("%6d ", ptr_array[k][i]);
			}

			printf("  %6d", ptr_array[13][i]);

			if (ptr_array[14][i] % 60 > 9) {
				printf("          0%d:%2d", ptr_array[14][i] / 60, ptr_array[14][i] % 60);

			}
			else {
				printf("          0%d:0%0d", ptr_array[14][i] / 60, ptr_array[14][i] % 60);
			}
			printf("\n");
		}
		else {
			continue;
		}



	}
	printf("\n\n");
}
//


//function for sort 2d array
void sort_2d_array(int ptr_array[12][15]) {
	int tmp;
	int choose;

	printf("����������:\n1. �� �����������\n2. �� ��������\n");
scanf_s("%d", &choose);

if (choose == 1) {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 12; j++) {
			if (ptr_array[13][j] > ptr_array[13][j + 1]) {
				for (int k = 0; k < 15; k++) {
					tmp = ptr_array[k][j];
					ptr_array[k][j] = ptr_array[k][j + 1];
					ptr_array[k][j + 1] = tmp;
				}
			}
		}
	}
}
if (choose == 2) {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 11; j++) {
			if (ptr_array[13][j] < ptr_array[13][j + 1]) {
				for (int k = 0; k < 15; k++) {
					tmp = ptr_array[k][j];
					ptr_array[k][j] = ptr_array[k][j + 1];
					ptr_array[k][j + 1] = tmp;
				}
			}
		}
	}
}
}
//


//function for input data from file
int input_from_file(int ptr_array[12][15]) {
	char  extension[6] = { ".txt\0" };
	char file_name[40] = "data";
	int size = 0;
	FILE* table_l;


	puts("������� �������� ����� � �������� 30 �������� (��� �������� ���������� �����)");
	scanf("%s", &file_name);
	strcat(file_name, extension);
	printf("��� �����: %s\n", file_name);

	table_l = fopen(file_name, "rt");

	while (!feof(table_l)) {
		if (fgetc(table_l) == '\n')
		size += 1;
	}

	if (size != 12) {
		printf("� ����� ������� ������� ���� ������, ������ ���� 12, � �������� %d, ���� ��� ����� ������� ����� ����� ���������� �������� � �����", size);
		return 0;
	}

	fseek(table_l, 0, SEEK_SET); // �����, ����� ������������� � ������ ������ �����
	for (int i = 0; i < 12; i++) {

		fscanf(table_l, "%d ", &ptr_array[0][i]);
		fscanf(table_l, "%d, ", &ptr_array[1][i]);
		fscanf(table_l, "%d, ", &ptr_array[2][i]);
		fscanf(table_l, "%d, ", &ptr_array[3][i]);
		fscanf(table_l, "%d, ", &ptr_array[4][i]);
		fscanf(table_l, "%d, ", &ptr_array[5][i]);
		fscanf(table_l, "%d, ", &ptr_array[6][i]);
		fscanf(table_l, "%d, ", &ptr_array[7][i]);
		fscanf(table_l, "%d, ", &ptr_array[8][i]);
		fscanf(table_l, "%d, ", &ptr_array[9][i]);
		fscanf(table_l, "%d, ", &ptr_array[10][i]);
		fscanf(table_l, "%d, ", &ptr_array[11][i]);
		fscanf(table_l, "%d, ", &ptr_array[12][i]);
		fscanf(table_l, "%d, ", &ptr_array[13][i]);
		fscanf(table_l, "%d\n", &ptr_array[14][i]);
	}
	return 1;
}
//

//function for remake info from table
int remake_info_from_table(int ptr_array[12][15]) {
	int choose_team, choose_group, choose_value;

	tables_on_screen(ptr_array,1);
	printf("\n\n� ����� ������� ����� �������� ��������?(1-12)\n");
	scanf_s("%d", &choose_team);
	system("cls");
	choose_team = choose_team - 1;
	if (choose_team > 11) return 0;

	printf("Id ������� ���.1 ���.2 ���.3 ���.4   ���.5 ���.6  ���.7   ���.8   ���.9 ���.10 ���.11 ���.12 ���.����� ���.������\n");
	for (int j = 0; j < 15; j++) { //ncols
		if (j != 13) {
			printf("%6d ", ptr_array[j][choose_team]);//i * ncols + j
		}
		else {
			if (ptr_array[j][choose_team] % 60 > 9) {
				printf("   0%d:%2d", ptr_array[j][choose_team] / 60, ptr_array[j][choose_team] % 60);
			}
			else {
				printf("   0%d:0%d", ptr_array[j][choose_team] / 60, ptr_array[j][choose_team] % 60);
			}
		}
	}
	printf("\n\n����� ������� ����� ��������?(1-15)\n");
	scanf_s("%d", &choose_group);
	choose_group = choose_group - 1;



	if (choose_group != 13) {
		printf("�� ����� �������� ����� ��������?\n");
		scanf_s("%d", &choose_value);

		if ((choose_group == 0) && ((10000 > choose_value) || (choose_value > 99999))) {
			printf("������� ����� � 5 ���������!!\n\n");
			return 0;
		}
		if (((choose_group > 1) && (choose_group < 12)) && ((choose_value < 0) || (choose_value > 1))) {
			printf("������� ���� 1 ���� 0!!\n\n");
			return 0;
		}
		if ((choose_group == 14) && ((choose_value > 100) || (choose_value < 70))) {
			printf("������� ����� �� 70 �� 100!!\n\n");
			return 0;
		}

		ptr_array[choose_group][choose_team] = choose_value;
		return 1;
	}
	else {
		int hours, minutes;
		printf("������ ���-�� ����� � ����� ����� ������: ");
		scanf_s("%d %d", &hours, &minutes);
		if (((hours > 5) || (hours < 0)) || ((minutes > 60) || (minutes < 0))) {
			printf("������� ���-�� ����� �� 5 � ���-�� ����� �� 60!!\n\n");
			return 0;
		}
		ptr_array[choose_group][choose_team] = hours * 60 + minutes;

	}
}
//
