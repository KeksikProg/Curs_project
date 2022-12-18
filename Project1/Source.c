#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <stdio.h>
#include <io.h>
#include <string.h>

#define _USE_MATH_DEFINES



// Functions for add elements in array
void id_team(int ptr_array[12]) {
	for (int i = 0; i < 12; i++) {
		ptr_array[i] = 10000 + rand() % (99999 - 10000 + 1);
	}
}

void num_quest(int ptr_array[12][15]) {
	for (int i = 1; i < 13; i++) {
		for (int j = 0; j < 14; j++) {
			ptr_array[i][j] = rand() % 2;
		}
	}
}

void num_time(int ptr_array[12][15]) {
	for (int i = 0; i < 12; i++) {
		ptr_array[13][i] = rand() % 300;
	}
}

void num_volume(int ptr_array[12][15]) {
	for (int i = 0; i < 12; i++) {
		ptr_array[14][i] = rand() % 100;
	}
}
//

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
void table1_on_screen(int ptr_array[12][15]) {
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

void table2_on_screen(int ptr_array[12][15]) {
	printf("Id �������   ���-�� ������\n");
	for (int i = 0; i < 12; i++) {
		printf("%6d              %2d\n", ptr_array[0][i], num_score(ptr_array, i));
	}
}
//


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
				if (ptr_array[13][j] > ptr_array[13][j+1]) {
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

FILE* input_from_file(int ptr_array[12][15]) {
	char  extension[6] = { ".txt\0" };
	char file_name[40]="data";
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
		exit(0);
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


void main() {
	setlocale(LC_ALL, "RUS");
	int choose, choose_2;
	int table[15][12];
	srand(time(NULL));


	

	printf("��� ����� ����������� ������?\n1. ��������\n2. �� �����\n");
	scanf_s("%d", &choose_2);

	switch (choose_2) {
		case 1: {
			id_team(table);
			num_quest(table);
			num_time(table);
			num_volume(table);
			break;
		}
		case 2: {
			input_from_file(table);
			break;
		}
	}


	while (1) {

		printf("���������� ����������������\n\n�������� ���� �� ���������:\n������� �������\n	11. ��������\n	12. ��������������\n2. �����\n3. ���������� �� �����\n0. ��������� ���������\n");
		scanf_s("%d", &choose);


		switch (choose) {
		case 0: {
			exit(0);
		}
		case 11: {
			system("cls");
			table1_on_screen(table);
			printf("\n");
			break;
		}
		case 12: {
			system("cls");
			table2_on_screen(table);
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
			table1_on_screen(table);
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


