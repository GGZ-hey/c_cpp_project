# include <stdio.h>
# include <malloc.h>
# include <windows.h>
# include <conio.h>
# include <time.h>
# include <stdlib.h>
#include"graphics.h"

#define ESC 27
#define SPACE 32
#define MAX_X 70
#define MAX_Y 35

int max_food;
int sna_length=0;
clock_t now_time;
char sna_dir = 'd';
char temp_condition;
int head_X,head_Y;
double wait_time = 300;

typedef struct Node{
	int x;
	int y;
	struct Node *pNext;

}NODE, *pNode;

typedef struct Queue {
	pNode head;//代表食物
	pNode rear;//代表蛇头
}QUEUE, *pQueue;

pQueue pSnake = (pQueue)malloc(sizeof(QUEUE));//全局为蛇，数据结构为链表

HANDLE Jubing = GetStdHandle(STD_OUTPUT_HANDLE);//获取句柄

/*定义这个数据结构的操作*/

/*1*/ void Enqueue(int x,int y)
{
	pNode pNew = (pNode)malloc(sizeof(Node));
	pNew->x = x;
	pNew->y = y;
	pSnake->rear->pNext = pNew;
	pSnake->rear = pNew;
	pSnake->rear->pNext = NULL;
	sna_length++;

}

/*2*/ void Dequeue() 
{
	pNode p = pSnake->head->pNext;
	pSnake->head->pNext = p->pNext;
	free(p);
	sna_length--;
}

/*3*/  void destory()
{
	pNode p = pSnake->head;
	pNode tem = pSnake->head;;
	while(tem!=NULL)
	{
		tem = p->pNext;
		free(p);
		p = tem;
	}

}



void getx_y(int x, int y)//设定光标位置
{
	COORD loc;
	loc.X = x;
	loc.Y = y;
	SetConsoleCursorPosition(Jubing, loc);//把数据结构与光标联系起来的函数

}

void game_over()//destory是为了引入game_over函数
{

	getx_y(35, 18);
	destory();
	printf("你输啦！哈哈");
	system("pause>nul");
	exit(0);
}

void Setcolor(int color)//设定字体颜色
{
	SetConsoleTextAttribute(Jubing, color);

}

void Hidecursor() 
{
	CONSOLE_CURSOR_INFO cursor_inf = { 1,0 };
	SetConsoleCursorInfo(Jubing, &cursor_inf);

}

void draw_wall() 
{
	int i, j;
	for (i = 1; i < MAX_X; i++) {
		Setcolor(14);
		getx_y(i, 0);
		printf("=");
		getx_y(i, 35);
		printf("=");
		
	}
	for (j = 0; j < MAX_Y; j++) {
		Setcolor(14);
		getx_y(0, j);
		printf("|");
		getx_y(MAX_X, j);
		printf("|");
	}
	Setcolor(15);
}

void information()
{
	int i;
	Setcolor(13);
	for (i = 71; i < 120; i++) {
		getx_y(i, 18);
		printf("-");

	}
	getx_y(85, 8);
	printf("现在长度为%d         ", sna_length);
	getx_y(85, 9);
	printf("还剩   %d   个食物", max_food );
	getx_y(85, 20);
	printf("按空格键可以暂停");
		getx_y(85, 23);
		printf("按ESC可以退出");
		getx_y(85, 29);
		printf("加速按:1");
		getx_y(85, 31);
		printf("减速按:2");
	

}

void rand_food()
{
	pNode p = pSnake->head;
	
	while (1) {
		p->x = rand() % (MAX_X - 1) + 1;
		p->y = rand() % (MAX_Y - 1) + 1;
		pNode p1 = p->pNext;
		while (p1 != NULL) {
			if (p1->x == p->x && p1->y == p->y) {
				break;
			}
			else
				p1 = p1->pNext;
		}
		if (p1 == NULL)
			break;
	}
	max_food--;
	Setcolor(5);
	getx_y(p->x, p->y);
	printf("$");
	fflush(stdout);
	Setcolor(15);
	

	
	
}

void clear_tail()
{
	pNode p = pSnake->head->pNext;
	getx_y(p->x, p->y);
	printf(" ");

}

void judge() 
{
	pNode p1 = pSnake->rear;
	pNode p = pSnake->head->pNext;
	if (max_food + 1 == 0) {
		system("cls");
		Setcolor(14);
		getx_y(30, 15);
		printf("-----You win!-----");
		system("pause>nul");
		exit(0);
}
	while (p != p1) 
	{
		if (p->x == p1->x&&p->y == p1->y) {
			game_over();
		}
		else
			p = p->pNext;

	}
	if (p->x == pSnake->head->x && p->y == pSnake->head->y) {
		rand_food();
		information();
	}//吃食物不出队，只进队
	else
		Dequeue();
}

void printf_snake() {
	int color;

	pNode p = pSnake->head->pNext;

	
	Setcolor(14);
	getx_y(pSnake->head->pNext->x, pSnake->head->pNext->y);
	printf("z");

	while (p != pSnake->rear) {
		color = rand() % 15 + 1;
		if (color == 14) {
			color -= rand() % 13 + 1;
		}
		p = p->pNext;
		Setcolor(color);
		getx_y(p->x, p->y);
		printf("M");
	
	}
	Setcolor(4);
	getx_y(pSnake->rear->x, pSnake->rear->y);
	printf("o");
	Setcolor(15);


}

void head_move(char c)
{
	char ch = 0;
	int x;
	x = 0;
	pNode p= pSnake->head->pNext;
	while (pSnake->rear != p)
		p = p->pNext;
	if (c == 32) {
		x = 1;
		Setcolor(13);
		getx_y(35, 15);
		printf("====暂停====");
		while (ch != 32) {
			ch = _getch();
		}
		c = temp_condition;
		getx_y(25, 15);
		printf("                吃我啊，猪！                    ");
}
	if (x == 1)
		c = temp_condition;
	
	if (sna_length>1&&(temp_condition == 'a'&&c == 'd'  ||  temp_condition == 'd'&&c == 'a'  ||  temp_condition == 's'&&c == 'w' || temp_condition == 'w'&&c == 's'))//注意注意！！%%与||不能混淆，否则出现bug
		c = temp_condition;

	if (c != 'a' && c != 'w' && c != 'd' && c != 's' && c != 27)
		c = temp_condition;
	switch (c)
	{
	case 'a':
		sna_dir = 'a';
		head_X = p->x-1;
		head_Y = p->y;
		if (head_X < 1) {
			game_over();
		}
		break;
	case's':
		sna_dir = 's';
		head_X = p->x;
		head_Y = p->y + 1;
		if (head_Y ==MAX_Y) {
			game_over();
		}
		break;
	case'd':
		sna_dir = 'd';
		head_X = p->x +1;
		head_Y = p->y;
		if (head_X ==MAX_X ) {
			game_over();
		}
		break;
	case'w':
		sna_dir = 'w';
		head_X = p->x;
		head_Y = p->y -1;
		if (head_Y <1) {
			game_over();
		}
		break;
	default:
			break;

	}
	Enqueue(head_X, head_Y);

	if (c == 27) {
		system("cls");
		Setcolor(13);
		getx_y(35, 15);
		printf("退出成功");
		system("pause>nul");
		exit(0);
	}
}

void move_snake()
{
	if (_kbhit())
	{
		temp_condition = sna_dir;
		sna_dir = _getch();
		if (sna_dir == '1')/*实现1加速，2减速*/
		{
			sna_dir = temp_condition;
			if (wait_time >= 40)
				wait_time -= 40;
		}
		if (sna_dir == '2')
		{
			sna_dir = temp_condition;
			if (wait_time <= 800)
				wait_time += 40;
		}
		head_move(sna_dir);
	}
	else
	{
		head_move(sna_dir);
	}
		judge();
		printf_snake();

	}

void con_snake()
{
	if (clock() - now_time >= wait_time) {
		clear_tail();
		move_snake();
		now_time = clock();
	}
}

void Init() //初始化函数（就是玩游戏之前需要什么）
{
	int len;
	int i;

	system("title 猪猪猪猪猪侠");
	system("mode con: cols=120 lines=36");
	pNode(pSnake->head) = (pNode)malloc(sizeof(NODE));
	pSnake->rear = pSnake->head;
	Setcolor(0x3);
	getx_y(40, 15);
	printf("请设定初始蛇的长度:(小于等于35的数值)");
		scanf_s("%d", &len);
		while (len > 35)
		{
			system("cls");
			getx_y(50, 15);
			printf("蛇太长，请重新输入:");
			scanf_s("%d", &len);

		}
		system("cls");
		Setcolor(8);
		getx_y(45, 15);
		printf("请设定初始食物数量:");
		scanf_s("%d", &max_food);
		system("cls");

		Hidecursor();
		for(i=0;i<len;i++)
		{
			Enqueue(i + 20, 18);
		}

		
		draw_wall();
		rand_food();
		information();
}

int main(void)
{
	srand((unsigned)time(NULL));
	Init();
	now_time = clock();
	while (1) 
{
		con_snake();
	}

	return 0;

}