#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <stdio.h>
#include <io.h>
#include <string.h>

#define n_columns 16 // Кол-во столбцов, константное значение
#define _USE_MATH_DEFINES

//Прототипы функций
int num_score(int **ptr_array, int index,int size); // Функция для подсчета общего количества баллов команды(включая бонус за время)
int find_quest(int** ptr_array, int size, int choose_quest, int choose_result); // Функция для поиска команд по решенной/не решенной конкретной задаче

void table1_on_screen(int** ptr_array, int size, int index); // Функция, которая позволяет вывести на экран всю исходную таблицу или одну конкретную команду
void table2_on_screen(int** ptr_array, int size); // Функция для вывода результирующей таблицы

int sort_2d_array(int** ptr_array,int size, int choose_sort); // Функция для сортировки исходного массива методом Bubble Sort

int input_from_file(char* filename); // Функция, которая открывает файл и возвращает количество команд 
int remake_info_from_table(int** ptr_array, int size); // Функция, позволяющая менять данные в исходном массиве  

int best_comand(int** ptr_array, int size); // Функция, которая возвращает победителя турнира по баллам(лучшую команду)
int worst_comand(int** ptr_array, int size); // Функция, которая возвращает худшую команду по баллам 
//


void main() {
	setlocale(LC_ALL, "RUS"); // Корректный вывод на экран
	srand(time(NULL));
	int choose, choose_2, choose_best_worst, choose_sort, num_quest, result; // переменные для диалога с пользователем
	
	int size=0; // Переменная для записи кол-ва команд 
	FILE* table_l; // переменная для файла


	char* file_name[10]; // переменная в которую записывается имя файла
	char  extension[6] = { ".txt\0" }; // переменная для расширения имени файла
	puts("Введите название файла в пределах 30 символов (без указания расширения файла)");
	scanf("%s", &file_name); // считываем имя файла
	printf("Имя файла: %s\n", file_name); // Выводим на экран имя файла

	size = input_from_file(file_name); // используем функцию, чтобы считать количество команд из файла
	//strcat(file_name, extension); // Объединяем расширение и имя файла для его открытия 

	int** table = (int**)malloc(sizeof(int*) * n_columns);
	for (int i = 0; i < n_columns; i++) {
		*(table + i) = (int*)malloc(sizeof(int) * size); // Объявление динамического двумерного массива на основе считанных из файла данных
	}
	table_l = fopen(file_name, "rt"); // Открываем файд для считывания именно данных
	for (int i = 0; i < size; i++) {
		fscanf(table_l, "%d ", &table[0][i]); // Считываем первый элемент 
		for (int j = 1; j < n_columns - 2; j++) { 
			fscanf(table_l, "%d, ", &table[j][i]); // Считываем элементы между первым и последним 
		}
		fscanf(table_l, "%d\n", &table[14][i]); // Считываем последний элемент
		table[15][i] = num_score(table, i, size); // Дополнительно высчитываем 15 столбец, в котором будут храниться общее кол-во баллов команды 
	}


	while (1) {

		printf("---------------------------------------------------------------------------------------------------\nСпортивное программирование\n\nВыберите один из вариантов:\nВывести таблицы\n	11. Исходную\n	12. Результирующую\n2. Поиск\n3. Сортировка по времени\n4. Изменение данных в таблице\n5. Вывести лучшую/худшую команду\n0. Закончить программу\n");
		scanf_s("%d", &choose); // Считываем действие которое выбрал пользователь 


		switch (choose) {
		case 0: {
			exit(0); // Выход из программы 
		}
		case 11: {
			system("cls"); // Очищение экрана 
			table1_on_screen(table, size, -1, 0); // Вывод исходной таблицы на экран 
			printf("\n");
			break;
		}
		case 12: {
			system("cls"); // Очистка экрана 
			table2_on_screen(table, size); // Вывод результирующей таблицы на экран
			printf("\n");
			break;
		}
		case 2: {
			system("cls");

			printf("Введите номер задачи, по которой хотите произвести поиск (1-12): ");
			scanf_s("%d", &num_quest); // Считываем задачу по которой будет производить поиск 
			printf("Была ли решена задача? (введите номер ответа):\n 1. Да \n 0. Нет\n");
			scanf_s("%d", &result); // Считываем по какому результату мы будем искать команды 

			char* zagolovok[16] = {
		"Id команды",
		" Зад.1",
		" Зад.2",
		" Зад.3",
		" Зад.4",
		"   Зад.5",
		" Зад.6",
		"  Зад.7",
		"   Зад.8",
		"   Зад.9",
		" Зад.10",
		" Зад.11",
		" Зад.12",
		" Время",
		"  Память",
		" Кол-во баллов" }; // Заголовок для вывода экран таблицы в читаемом виде 

			for (int i = 0; i < n_columns; i++) {
				printf("%s", *(zagolovok + i)); // Вывод заголовка 
			}

			for (int i = 0; i < size; i++) { // Перебор индексов всех команд и если они подходят по указанным критериям поиска, то их печать на экран 
				table1_on_screen(table, size, find_quest(table, size, num_quest, result, i), 1); // Передача аргументов в функцию вывода и поиска 
			}
			printf("\n");
			
			break;
		}
		case 3: {
			system("cls");

			printf("Сортировка:\n1. По возрастанию\n2. По убыванию\n");
			scanf_s("%d", &choose_sort); // Выбор как сортировать двумерный массив 

			sort_2d_array(table, size, choose_sort); // Сортировка массива по времени 
			system("cls"); // Очистка экрана 
			table1_on_screen(table, size, -1, 0); // Вывод новой отсортированной исходной таблицы на экран 
			break;
		}
		case 4: {
			system("cls"); // Очистка экрана 

			if (remake_info_from_table(table, size) == 0) { // Замена данных в исходной в таблице, но если были введены неверные данные, то они не меняются
				printf("Данные не были изменены в связи с неверным заполнением, повторите пожалуйста операцию!\n");
			};

			break;
		}
		case 5: {
			system("cls"); // Очистка экрана 
			printf("Какую комнду нужно вывести?\n1. Лучшую\n2. Худшую: ");
			scanf_s("%d", &choose_best_worst); // Выбор какую команду вывести лучшую или худшую
			if (choose_best_worst == 1) printf("Лучшая команда №%d с %d баллами и потратившая всего %d памяти",best_comand(table, size)+1, *(*(table + 15) + best_comand(table, size)), *(*(table + 14) + best_comand(table, size))); // работа с указателями, если введено 1, то вывод лучшей команды посчитанной по функции 
			if (choose_best_worst == 2) printf("Худшая команда №%d c %d баллами и потратившая %d памяти",worst_comand(table, size)+1, *(*(table + 15) + worst_comand(table, size)), *(*(table + 14) + worst_comand(table, size))); // Работа с указателями, если введено 2, то вывод худшей команды посчитанной по функции
			printf("\n\n");
			break;
		}
		default: {
			system("cls"); // Очистка экрана 
			printf("Выберите число из списка!\n"); // Вывод строки если не подошло значение введенное пользователем 
			break;
		}
		}
	}

}


//Функция для подсчет общего количества баллов команды 
int num_score(int **ptr_array, int index,int size) {
	int id_team = *(ptr_array+index), num_score = 0, time_score;

	for (int i = 1; i < 13; i++) {
		num_score += *(*(ptr_array + i) + index); // Считаем баллы за решенные задачи 
	}

	time_score = *(*(ptr_array+13)+index) / 60; // Считаем сколько баллов получили за оставшееся время 
	num_score += time_score; // Прибавляем бонусные баллы за время 

	return num_score; // Возвращаем общее количество баллов 
}
//


//Функции для вывода таблиц на экран 
void table1_on_screen(int** ptr_array, int size, int index, int flag) {
	char *zagolovok[16] = { 
		"Id команды", 
		" Зад.1", 
		" Зад.2", 
		" Зад.3", 
		" Зад.4", 
		"   Зад.5", 
		" Зад.6", 
		"  Зад.7", 
		"   Зад.8", 
		"   Зад.9", 
		" Зад.10", 
		" Зад.11", 
		" Зад.12", 
		" Время", 
		"  Память", 
		" Кол-во баллов\n",}; // Заголовок для более удобного чтения таблицы пользователем 

	if (index == -5) return 0; // Если аргумент индекс равен -5, то возвращаем 0, нужно для функции поиска, чтобы не печатать ненужные команды
	
	if (flag == 0){ // Если флаг равен 0, то не печатаем данное поле, нужно для функции поиска, чтобы много раз заголовок не печатался 
		for (int i = 0; i < n_columns; i++) {
			printf("%s", *(zagolovok + i)); // Вывод заголовка на экран 
		}
	}

	for (int i = 0; i < size; i++) { //Перебор команд 
		if (index > -1) i = index; // Если индекс больше -1, то мы присваиваем i этот самый индекс для работы с конкретной командой 
		printf("\n");
		for (int j = 0; j < n_columns; j++) { // Перебор столбцов 
			if (j != 13) { // Если столбец не время 
				printf("%6d ", *(*(ptr_array + j) + i));// Вывод на экран всех столбцов кроме времени 
			}
			else { // Если столбец времени, то у него особый вывода на эран 
				if (*(*(ptr_array + j) + i) % 60 > 9) { // Если время минут занимаем больше двух разрядов 
					printf("   0%d:%2d", *(*(ptr_array + j) + i) / 60, *(*(ptr_array + j) + i) % 60); // печатать выделяя 2 разряда 
				}
				else { // если время минут занимает меньше двух разрядов 
					printf("   0%d:0%d", *(*(ptr_array + j) + i) / 60, *(*(ptr_array + j) + i) % 60); // Первый разряд поставить 0 для более красивого вывода 
				}
			}
		}
		if (index > -1) return 0; // Если индекс больше -1, то мы заканчиваем программу, тк это нужно для вывода одной конкретной команды, а не для вывода всеей таблицы
	}
	printf("\n");
}
void table2_on_screen(int** ptr_array, int size) {
	printf("Id команды   Кол-во баллов   Память\n"); // Вывод заголовка 
	for (int i = 0; i < size; i++) {
		printf("  %d      %5d         %5d\n", *(*(ptr_array)+i), *(*(ptr_array+15) + i), *(*(ptr_array + 14) + i)); // Печатаем айди команды, общее количество баллов и потраченной памяти
	}
}
//

//Функция для поиска команд по результату определенной задачи
int find_quest(int **ptr_array,int size, int choose_quest, int choose_result, int index) {
	

	if (choose_quest > 12 || choose_quest < 1 || choose_result > 1 || choose_result < 0) { // Проверка на вход верных значений 
		printf("Введены неверные данные!");
		return -1;
	}

	if (*(*(ptr_array + choose_quest) + index) == choose_result) { // Если условия поиска совпадают с значением команды переданного индекса, то возвращаем индекс 
		return index;
	}
	else {
		return -5; // Если у команды переданного индекса результат задачи не подходит возвращаем -5, что выступает в роли флага для завершения операции вывода на экран 
	}
}
//


//Функция для сортировки двумерного массива методом "пузырька"
int sort_2d_array(int **ptr_array,int size, int choose) {
	int tmp; // Переменная для буферного сохранения и переноса значений из переменной в переменную 

	for (int i = 0; i < n_columns; i++) { // перебор столбцов 
		for (int j = 0; j < size-1; j++) { // перебор команд 
			if (((choose == 1) && (ptr_array[13][j] > ptr_array[13][j + 1])) || ((choose == 2) && ((ptr_array[13][j] < ptr_array[13][j + 1])))) { 
				// Если выбрана сортировка по возрастанию(1) и значение след элемента больше значения элемента данной итерации, то замена
				// Если выбрана сортировка по убыванию(2) и значение след элемента меньше значения элемента данной итерации, то замена  
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


//Функция для счета количества команд из файла для создания динамического двумерного массива 
int input_from_file(char* filename) {
	char  extension[6] = { ".txt\0" }; // расширение файла 
	int size = 0; // Количество команд 
	FILE* table_l; // Указатель на открвшийся файл
	
	
	strcat(filename, extension); // Соединения имени файла и его расширения 
	table_l = fopen(filename, "rt"); // открытие файла для чтения 

	while (!feof(table_l)) { // Пока файл не закончился 
		if (fgetc(table_l) == '\n') // Пока есть картеки переноса строки 
		size += 1; // Прибавляем плюс один к количеству команд 
	}
	fclose(table_l); // Закрываем файл 
	return size; // Возвращаем количество команд 
}
//

//function for remake info from table
int remake_info_from_table(int **ptr_array,int size) {
	int choose_team, choose_group, choose_value; // Переменные для выбора команды, столбца и значения изменения 

	table1_on_screen(ptr_array, size, -1, 0); // выводим на экран исходную таблицу, чтобы пользователью было удобнее 
	printf("\n\nВ какой команде нужно поменять значения?(1-%d)\n", size);
	scanf_s("%d", &choose_team); // считываем команду 
	//system("cls");//очиваем экран 
	choose_team = choose_team - 1; // отнимаем 1, чтобы по индексам было красиво и удобно
	if (choose_team > size-1) return 0; // если введено неверный индекс команды, то выходим из функции 
	
	table1_on_screen(ptr_array, size, choose_team, 0); // выводим на экран конкретную команду, которую выбрал пользователь
	printf("\n\nКакой столбец нужно поменять?(1-15)\n");
	scanf_s("%d", &choose_group); // считываем столбец, который пользователь хочет поменять 
	choose_group = choose_group - 1; // отнимаем 1 , чтоыб по индексам было красиво и удобно считать 



	if (choose_group != 13) { // если не столбец времени 
		printf("На какое значение нужно поменять?\n");
		scanf_s("%d", &choose_value); // выбираем на какое значение нужно поменять 

		if ((choose_group == 0) && ((10000 > choose_value) || (choose_value > 99999))) { // если меняем индекс, то проверяем, чтобы у числа было 5 разрядов
			printf("Введите число с 5 разрядами!!\n\n");
			return 0;
		}
		if (((choose_group > 1) && (choose_group < size)) && ((choose_value < 0) || (choose_value > 1))) { // если меняем результат решения задачи. то чтобы это было либо true(1) либо false(0)
			printf("Введите либо 1 либо 0!!\n\n");
			return 0;
		}
		if ((choose_group == 14) && ((choose_value > 100) || (choose_value < 70))) { // Если меняем память, то она должна быть в интервале от 70 до 100
			printf("Введите число от 70 до 100!!\n\n");
			return 0;
		}

		*(*(ptr_array+choose_group)+choose_team) = choose_value; // Если все проверки были пройдены, то мы присваиваем новое значение
		*(*(ptr_array + 15) + choose_team) = num_score(ptr_array, choose_team, size); // пересчитываем общее количество баллов, тк решения задач могли поменяться 
		table1_on_screen(ptr_array, size, -1, 0);
		return 1;
	}
	else { // если меняем время 
		int hours, minutes;
		printf("Ведите кол-во часов и минут через пробел: ");
		scanf_s("%d %d", &hours, &minutes); // считываем время 
		if (((hours > 5) || (hours < 0)) || ((minutes > 60) || (minutes < 0))) { // в диапазоне до 5 часов 
			printf("Введите кол-во часов до 5 и кол-во минут до 60!!\n\n");
			return 0;
		}
		*(*(ptr_array+choose_group)+choose_team) = hours * 60 + minutes; // если проверка пройдена меняем значение
		*(*(ptr_array + 15) + choose_team) = num_score(ptr_array, choose_team, size); // пересчитываем количество баллов тк бонусные баллы за время могли поменяться 

	}
	
	table1_on_screen(ptr_array, size, -1, 0);

}
//

// Функции для поиска лучшего или худшего игрока 
int best_comand(int** ptr_array, int size) {
	int max_score = 0, max_volume = 0, index = 0; // Указываем самые минимальные значения тк ищем максимальные 

	for (int i = 0; i < size; i++) { // перебираем команды 

		if (num_score(ptr_array, i, size) > max_score) { // если кол-во баллов у элемента данной интерации больше, чем максимально то присваиваем 
			max_score = num_score(ptr_array, i, size);
			max_volume = *(*(ptr_array + 14) + i);
			index = i;
		}
		if (num_score(ptr_array, i, size) == max_score) { // если кол-во баллов одинаковое, то сравниваем память
			if (*(*(ptr_array + 14)+i) < max_volume) { // если элемента данной итерации потратил меньше памяти чем максимальное, то переприсваиваем 
				max_score = num_score(ptr_array, i, size);
				max_volume = *(*(ptr_array + 14) + i);
				index = i;
			}
			else {
				continue;
			}
		}
	}

	return index; // в конце возвращаем индекс лучшей команды 
}
int worst_comand(int** ptr_array, int size) {
	int min_score = 1000, min_volume = 1000, index = 0; //Указываем самые максмальные значения тк ищем минимальные

	for (int i = 0; i < size; i++) {

		if (num_score(ptr_array, i, size) < min_score) { // если кол-во баллов у элемента данной интерации меньше, чем минимально то присваиваем
			min_score = *(*(ptr_array+15)+i);
			min_volume = *(*(ptr_array + 14) + i);
			index = i;
		}
		if (num_score(ptr_array, i, size) == min_score) {// если кол-во баллов одинаковое, то сравниваем память
			if (*(*(ptr_array + 14) + i) < min_volume) { // если элемента данной итерации потратил больше памяти чем минимальное, то переприсваиваем
				min_score = *(*(ptr_array + 15) + i);
				min_volume = *(*(ptr_array + 14) + i);
				index = i;
			}
			else {
				continue;
			}
		}
	}

	return index; // Возвращаем индекс худшей команды
}
//
