#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32


int max_food = 0;
int sna_length=3;
char tem;
char sna_dir = DOWN;
int head_X, head_Y;
int time=500;

typedef struct food {
	int x;
	int y;
} Food, *pFood;

pFood food = (pFood)malloc(sizeof(Food));

typedef struct Node {
	int x;
	int y;
}NODE ,*PNode;

typedef struct Queue {
	PNode sna_node[15];
	int head;
	int tail;
}QUEUE, *pQueue;

pQueue Snake = (pQueue)malloc(sizeof(QUEUE));

HANDLE jubing = GetStdHandle(STD_OUTPUT_HANDLE);

void Enqueue(int x,int y)
{
	if ((Snake->tail + 1) % 15 == Snake->head) {
		system("cls");
		printf("Snake is too long");
		exit(0);
}
	Snake->sna_node[Snake->tail]->x = x;
	Snake->sna_node[Snake->tail]->y = y;
	Snake->tail = (Snake->tail + 1) % 15;
	sna_length++;
}

void Dequeue()
{
	if (Snake->head == Snake->tail) {
		system("cls");
		printf("Snake is too short");
		exit(0);
}

	Snake->head = (Snake->head + 1) % 15;
	sna_length--;
}

void destroy() {
	free(Snake);
}

void game_over() {
	system("cls");
	destroy();
	printf("----game over----");
	system("pause>nul");
	exit(0);
}

int isdead() {
	PNode sna_head;
	if (Snake->tail != 0) {
		sna_head = Snake->sna_node[Snake->tail - 1];
	}
	else
		sna_head = Snake->sna_node[14];

	int i;
	if (max_food+1  == 0) {
		return 1;
	}

	if (Snake->head < Snake->tail) {
		for (i = Snake->head ; i < Snake->tail-1; i++) {
			if (sna_head->x == Snake->sna_node[i]->x &&  sna_head->y == Snake->sna_node[i]->y) {
				return 1;
			}
		}
	}

	if (Snake->head > Snake->tail&&Snake->tail != 0) {
		for (i = Snake->head ; i < 15; i++) {
			if (sna_head->x == Snake->sna_node[i]->x &&  sna_head->y == Snake->sna_node[i]->y) {
				return 1;
			}
		}
		for (i = 0; i < Snake->tail-1; i++) {
			if (sna_head->x == Snake->sna_node[i]->x &&  sna_head->y == Snake->sna_node[i]->y) {
				return 1;
			}
		}

	}

	 if (Snake->tail == 0) {
		for (i = Snake->head; i < 13; i++) {
			if (sna_head->x == Snake->sna_node[i]->x &&  sna_head->y == Snake->sna_node[i]->y) {
				return 1;
			}
		}
	}

	 if (sna_head->x < 1 || sna_head->x>15 || sna_head->y < 2 || sna_head->y>15) {
		return 1;
	}
		return 0;
		
}

void getx_y(int x,int y) {
	COORD loc;
	loc.X = x;
	loc.Y = y;
	SetConsoleCursorPosition(jubing, loc);
}

void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(jubing, &cursor_info);

}

void information() {
	getx_y(0, 0);
	printf("  还剩下  %d   个食物", max_food+1);
	getx_y(0, 20);
	printf("   按空格键可以暂停");
	getx_y(0, 22);
	printf("  按 1 加速");
	getx_y(0, 23);
	printf("  按 2 减速");
	
}

void draw_wall()
{
	int i, j;
	for (j = 0; j < 17; j++) {
		for (i = 0; i < 17; i++) {
			if (j == 1 && i > 0&&i<16)
				printf("=");
			else if (j == 16 && i > 0&&i<16)
				printf("=");
			else if (j>0&&(i == 0 || i == 16)) {
				printf("|");
			}
			else {
				printf(" ");
			}

		}
		printf("\n");
	}
}

void rand_food()
{
	food->x = rand() % 15 + 1;
	food->y = rand() % 15 + 1;
	max_food--;
	getx_y(food->x, food->y);
	printf("$");
	fflush(stdout);
}

void clear_tail() {
	PNode sna_tail = Snake->sna_node[Snake->head];
	getx_y(sna_tail->x, sna_tail->y);
	printf(" ");
}

void printf_sna() {
	int i;
	PNode sna_head;
	PNode sna_tail = Snake->sna_node[Snake->head];
	if (Snake->tail > 0) {
		sna_head = Snake->sna_node[Snake->tail - 1];
	}
	else
	{
		sna_head = Snake->sna_node[14];
	}

	getx_y(sna_tail->x, sna_tail->y);
	printf("z");
	getx_y(sna_head->x, sna_head->y);
	printf("o");

	if (Snake->head < Snake->tail) {
		for (i = Snake->head+1; i < Snake->tail - 1; i++) {
			getx_y(Snake->sna_node[i]->x, Snake->sna_node[i]->y);
			printf("r");
			}
		}
	

	if (Snake->head > Snake->tail&&Snake->tail != 0) {
		for (i = Snake->head+1; i < 15; i++) {
			getx_y(Snake->sna_node[i]->x, Snake->sna_node[i]->y);
			printf("r");
			}
		
		for (i = 0; i < Snake->tail - 1; i++) {
			getx_y(Snake->sna_node[i]->x, Snake->sna_node[i]->y);
			printf("r");
			}
		}

	if (Snake->tail == 0) {
		for(i = Snake->head + 1;i<14;i++) {
			getx_y(Snake->sna_node[i]->x, Snake->sna_node[i]->y);
			printf("r");
		}
	}

	}

void head(char c)
{
	PNode sna_head;
	char ch=0;
	if (c == 32) {
		getx_y(0, 9);
		printf("         ---暂停---");
		while (ch != 32) {
			ch = _getch();
		}
		c = tem;
	}
	if (Snake->tail > 0) {
		sna_head = Snake->sna_node[Snake->tail - 1];
	}
	else
		sna_head = Snake->sna_node[14];

	if (sna_length > 1 && (tem == 72 && c == 80 || tem == 80 && c == 72 || tem == 75 && c == 77 || tem == 77 && c == 75)) {
		c = tem;
}
	if (c != 72 && c != 75 && c != 77 && c != 80) {
		c = tem;
	}
	switch (c) {
	case 72:
		sna_dir = UP;
		head_X = sna_head->x;
		head_Y = sna_head->y - 1;
		break;
	case 80:
		sna_dir = DOWN;
		head_X = sna_head->x;
		head_Y = sna_head->y + 1;
		break;
	case 75:
		sna_dir = LEFT;
		head_X = sna_head->x - 1;
		head_Y = sna_head->y;
		break;
	case 77:
		sna_dir = RIGHT;
		head_X = sna_head->x + 1;
		head_Y = sna_head->y;
			break;
	}
	Enqueue(head_X, head_Y);

	if (sna_head->x == food->x&&sna_head->y == food->y) {
		rand_food();
		information();
	}
	else
		Dequeue();
}

void move_sna() {
	if (_kbhit()) {
		tem = sna_dir;
		sna_dir = _getch();
		if (sna_dir == '1') {
			sna_dir = tem;
			if (time > 50) {
				time -= 50;
			}
		}
		if (sna_dir == '2') {
			sna_dir = tem;
			if (time < 900) {
				time += 50;
			}
		}
		head(sna_dir);
	}
	else
		head(sna_dir);
}

void play_sna() {
	clear_tail();
	move_sna();
	printf_sna();
	
}

void Init()
{
	int i,j;
	printf("请输入食物数量:");
	scanf_s("%d", &max_food);
	Snake->head = Snake->tail = 0;
	for (j = 0; j < 15; j++) {
		Snake->sna_node[j] = (PNode)malloc(sizeof(Node));
	}
	for (i = 0; i < 8; i++) {
		Enqueue(i + 3, 8);
	}
	system("cls");
	HideCursor();
	draw_wall();
	rand_food();
	information();
}

int main(void)
{
	Init();
	while (1)
	{
		play_sna();
		Sleep(time);
		if (isdead()) {
			break;
		}
	
	}

	game_over();

	
	return(0);
}