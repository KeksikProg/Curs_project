#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <stdio.h>

#define _USE_MATH_DEFINES

//structure
typedef struct {
	int id;
	int tasks[12];
	int time;
	int volume;
	int score;
}team;
//

// Functions for add elements in array
void id_team(team* ptr_array) {
	for (int i = 0; i < 12; i++) {
		ptr_array[i].id = rand() % 1000000;
	}
}

void num_quest(team* ptr_array) {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			ptr_array[i].tasks[j] = rand() % 2;
		}
	}
}

void num_time(team* ptr_array) {
	for (int i = 0; i < 12; i++) {
		ptr_array[i].time = rand() % 300;
	}
}

void num_volume(team* ptr_array) {
	for (int i = 0; i < 12; i++) {
		ptr_array[i].volume = rand() % 100;
	}
}
//


//function for sum score for teams
int num_score(team* ptr_array) {
	int  num_score = 0, time_score;

	for (int i = 0; i < 12; i++) {
		num_score = 0;
		for (int j=0; j < 12; j++){
			num_score += ptr_array[i].tasks[j];
		}
		time_score = ptr_array[i].time / 60;
		num_score += time_score;

		ptr_array[i].score = num_score;
	}
}
//


// func for find num of quest 
int find_quest(team* ptr_array) {
	int num_quest, result;

	printf("������� ����� ������, �� ������� ������ ���������� ����� (1-12): ");
	scanf_s("%d", &num_quest);
	printf("���� �� ������ ������? (������� ����� ������):\n 1. �� \n 0. ���\n");
	scanf_s("%d", &result);

	system("cls");
	printf("Id ������� ���.1 ���.2 ���.3 ���.4 ���.5 ���.6 ���.7 ���.8 ���.9 ���.10 ���.11 ���.12 ���. ������ ���. �������\n");
	for (int i = 0; i < 12; i++) { 
		if (ptr_array[i].tasks[num_quest-1] == result) {
			//printf("\n");
			printf("   %6d ", ptr_array[i].id);

			for (int j = 0; j < 12; j++) {
				printf("%5d ", ptr_array[i].tasks[j]);
			}

			printf("    %6d ", ptr_array[i].volume);
			if (ptr_array[i].time % 60 > 9) {
				printf("        0%d:%2d", ptr_array[i].time / 60, ptr_array[i].time % 60);

			}
			else {
				printf("        0%d:0%0d", ptr_array[i].time / 60, ptr_array[i].time % 60);
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

// func for sort array of structure on time
void sort(team* ptr_array) {
	team tmp;
	int choose;

	printf("����������:\n1. �� ��������\n2. �� �����������\n");
	scanf_s("%d", &choose);

	if (choose == 1) {
		for (int i = 12 - 1; i >= 0; i--) {
			for (int j = 0; j < i; j++) {
				if (ptr_array[j].time < ptr_array[j + 1].time) {
					tmp = ptr_array[j];
					ptr_array[j] = ptr_array[j + 1];
					ptr_array[j + 1] = tmp;
				}
			}
		}
	} 
	if (choose == 2) {
		for (int i = 12 - 1; i >= 0; i--) {
			for (int j = 0; j < i; j++) {
				if (ptr_array[j].time > ptr_array[j + 1].time) {
					tmp = ptr_array[j];
					ptr_array[j] = ptr_array[j + 1];
					ptr_array[j + 1] = tmp;
				}
			}
		}
	}
}
//


//function for table on screen
void table1_on_screen(team* ptr_array) {
	printf("Id ������� ���.1 ���.2 ���.3 ���.4 ���.5 ���.6 ���.7 ���.8 ���.9 ���.10 ���.11 ���.12 ���. ������ ���. �������\n");

	
	for (int i = 0; i < 12; i++) {
		printf("   %6d ", ptr_array[i].id);
		
		for (int j = 0; j < 12; j++) {
			printf("%5d ", ptr_array[i].tasks[j]);
		}

		printf("    %6d ", ptr_array[i].volume);
		if (ptr_array[i].time % 60 > 9) {
			printf("        0%d:%2d", ptr_array[i].time / 60, ptr_array[i].time % 60);

		}
		else {
			printf("        0%d:0%0d", ptr_array[i].time / 60, ptr_array[i].time % 60);
		}
		printf("\n");
	}

}

void table2_on_screen(team* ptr_array) {
	printf("Id �������   ���-�� ������\n");
	for (int i = 0; i < 12; i++) {
		printf("%6d              %2d\n", ptr_array[i].id, ptr_array[i].score);
	}
}
//



void main() {
	setlocale(LC_ALL, "RUS");
	int choose;
	srand(time(NULL));
	team teams[12];
	
	id_team(teams);
	num_quest(teams);
	num_time(teams);
	num_volume(teams);
	num_score(teams);

	
	while (1){

		printf("---------------------------------------------------------------------------------------------------------------------\n���������� ����������������\n\n�������� ���� �� ���������:\n������� �������\n	11. ��������\n	12. ��������������\n2. �����\n3. ���������� �� �����\n0. ��������� ���������\n");
		scanf_s("%d", &choose);


		switch (choose) {
			case 0: { 
				exit(0);
			}
			case 11: {
				system("cls");
				table1_on_screen(teams);
				printf("\n");
				break;
			}
			case 12: {
				system("cls");
				table2_on_screen(teams);
				printf("\n");
				break;
			}
			case 2: {
				system("cls");
				find_quest(teams);
				break;
			}
			case 3: {
				system("cls");
				sort(teams);
				system("cls");
				printf("���������� ���������, ��� ������ ���������� �������� �������� ������� ����� 11\n");
				printf("\n");
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

