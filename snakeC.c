#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>


#define UPDATE 500
#define X 10
#define Y 20

typedef struct{
	int cords[2];
	int dir[2];
} snake;

int getRandomX() {
	return rand() % X;
}

int getRandomY() {
	return rand() % Y;
}

int drawSnake(snake* snake, int size, int x, int y) {
	for (int i = size-1; i >= 0; i--) {
		if (x == snake[i].cords[0] && y == snake[i].cords[1]) {
			printf("O");
			return 1;
		}
	}
	return 0;
}

void drawMap(snake* snake, int *food, int size) {
	system("cls");
	printf("[%d][%d]\n", snake[size - 1].cords[0], snake[size - 1].cords[1]);
	for (int x = 0; x < X; x++) {
		for (int y = 0; y < Y; y++) {
			
			if (x == 0 || y == 0 || x == X - 1 || y == Y - 1) printf("#");
			else if (food[0] == x && food[1] == y) printf("*");
			else if (drawSnake(snake, size, x, y) == 0) printf(" ");

		}
		printf("\n");
	}
}

void changeDirection(snake* snake, int *change, int size, char direction) {
	for (int i = size-1; i >= 0; i--) {
		switch (direction) {
		case 'w':
			if (snake[i].cords[0] == change[0] && snake[i].cords[1] == change[1]) {
				snake[i].dir[0] = -1;
				snake[i].dir[1] = 0;
			}
			break;

		case 'd':
			if (snake[i].cords[0] == change[0] && snake[i].cords[1] == change[1]) {
				snake[i].dir[0] = 0;
				snake[i].dir[1] = 1;
			}
			break;
		case 's':
			if (snake[i].cords[0] == change[0] && snake[i].cords[1] == change[1]) {
				snake[i].dir[0] = 1;
				snake[i].dir[1] = 0;
			}
			break;
		case 'a':
			if (snake[i].cords[0] == change[0] && snake[i].cords[1] == change[1]) {
				snake[i].dir[0] = 0;
				snake[i].dir[1] = -1;
			}
			break;
		}
	}
}

void moveSnake(snake *snake, int size, char direction) {
	
	for (int i = size-1; i >= 0; i--) {
		if (snake[i].cords[0] == 1 && direction == 'w') snake[i].cords[0] = X - 1;
		if (snake[i].cords[0] == X - 2 && direction == 's') snake[i].cords[0] = 0;
		if (snake[i].cords[1] == 1 && direction == 'a') snake[i].cords[1] = Y - 1;
		if (snake[i].cords[1] == Y - 2 && direction == 'd') snake[i].cords[1] = 1;
		snake[i].cords[0] += snake[i].dir[0];
		snake[i].cords[1] += snake[i].dir[1];
		
	}
}

void mainloop(snake *snake, int size, int *food) {
	char dir = 'd';
	int change[2] = { 0, 0 };
	while (1) {
		if (_kbhit()) {
			dir = _getch();
			change[0] = snake[size-1].cords[0];
			change[1] = snake[size-1].cords[1];
		}
		changeDirection(snake, change, size, dir);
		drawMap(snake, food, size);
		moveSnake(snake, size, dir);
		
		Sleep(UPDATE);
	}
}

void init() {
	srand(time(0));
	int size = 3;
	snake *snake = malloc(size * sizeof(*snake));
	int food[2] = { getRandomX(), getRandomY() };
	
	for (int i = size-1; i >= 0; i--) {
		if (snake != NULL) {
			snake[i].cords[0] = 3;
			snake[i].cords[1] = i + 3;
			snake[i].dir[0] = 0;
			snake[i].dir[1] = 1;
		}
	}
	
	mainloop(snake, size, food);
}

int main() {
	init();

	return 0;
}