#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <stdio.h>

#define _USE_MATH_DEFINES



// Functions for add elements in array
void id_team(int ptr_array[12]) {
	for (int i = 0; i < 12; i++) {
		ptr_array[i] = rand() % 1000000;
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
	printf("Id ������� ���.1 ���.2 ���.3 ���.4   ���.5 ���.6  ���.7   ���.8   ���.9 ���.10 ���.11 ���.12   ���.�����  ���.������");
	for (int i = 0; i < 12; i++) { //nlines
		printf("\n");
		for (int j = 0; j < 15; j++) { //ncols
			if (j != 13) {
				printf("%6d ", ptr_array[j][i]);//i * ncols + j
			}
			else {
				if (ptr_array[j][i] % 60 > 9){
					printf("      0%d:%2d", ptr_array[j][i] / 60, ptr_array[j][i] % 60);
				}
				else {
					printf("      0%d:0%d", ptr_array[j][i] / 60, ptr_array[j][i] % 60);
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



void main() {
	setlocale(LC_ALL, "RUS");
	system("chcp 1251");
	int choose;
	int table[15][12];
	srand(time(NULL));


	id_team(table);
	num_quest(table);
	num_time(table);
	num_volume(table);


	while (1){

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
				printf(".�����.\n");
				break;
			}
			case 3: {
				system("cls");
				printf("..����������..\n");
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

