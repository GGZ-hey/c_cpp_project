#include<stdio.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESC 27
#define SPACE 32

#define max_x 21
#define max_y 13

int map[max_x][max_y] = { 0 };
int cur_x, cur_y, score;
int next;
char key;
int Gamespeed = 300;
int mark=0;

int shape[28][6] = {
	{0,-1,0,-2,1,0},{1,0,2,0,0,1},{0,1,0,2,-1,0},{-1,0,-2,0,0,-1},
	{0,1,0,-1,-1,0},{-1,0,1,0,0,-1},{0,1,0,-1,1,0},{-1,0,1,0,0,1},
	{-1,0,0,-1,1,-1},{0,-1,1,0,1,1},{1,0,0,1,-1,1},{0,1,-1,0,-1,-1},
	{-1,0,0,1,1,1},{0,-1,-1,0,-1,1},{1,0,0,-1,-1,-1},{0,1,1,0,1,-1},
	{-1,0,0,-1,0,-2},{0,-1,1,0,2,0},{1,0,0,1,0,2},{0,1,-1,0,-2,0},
	{1,0,1,1,0,1},{ 1,0,1,1,0,1 },{ 1,0,1,1,0,1 },{ 1,0,1,1,0,1 },
	{0,1,0,2,0,3},{-1,0,-2,0,-3,0},{ 0,-1,0,-2,0,-3 },{1,0,2,0,3,0}
};//坐标表方块 七种四变化

void gotoxy(int x, int y) {
	COORD c;
		c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}//移光标函数

void game_over() {
	int flag=0;
		for (int j = 1; j < max_y-1; j++) {
			if (map[1][j] != 0) {
				for (int k = 1; k < max_y-1; k++) {
					if (map[2][k] != 0) {
						for (int l = 1; l < max_y - 1; l++) {
							if (map[3][l] != 0) {
								flag = 1; break;
							}
						}
					}
					if (flag == 1) break;
				}
				
			}
			if(flag==1) break;
		}
	
		if (flag == 1) {
			for (int i = 1; i < max_x-1; i++) {
				gotoxy(1, i);
				for (int j = 1; j < max_y-1; j++) {
					
					printf("□");
				}
				printf("\n");
			}
			gotoxy(8, 8);
			printf("game over!");
			gotoxy(21, 0);
			system("pause>nul");
			exit(0);
		}
}

void show_map(int id) {
	int i, j;
	gotoxy(0, 0);
	if (id != -1) {
		for (i = 0; i < max_x; i++) {
			for (j = 0; j < max_y; j++) {
				if ((i == 0 || i == max_x - 1) && (j == 0 || j == max_y - 1)) printf(" ");
				else if (i == 0 || i == max_x - 1) printf("--");
				else if (j == 0 || j == max_y - 1) printf("|");
				else if (map[i][j] == 2) printf("■");
				else if (
					i == cur_x && j == cur_y ||
					i == cur_x + shape[id][0] && j == cur_y + shape[id][1] ||
					i == cur_x + shape[id][2] && j == cur_y + shape[id][3] ||
					i == cur_x + shape[id][4] && j == cur_y + shape[id][5]
					)  printf("■");
				else if (map[i][j] == 0) printf("  ");

			}
			if (i == 1) printf("              next:");
			if (i == 11) printf("    score:%d", score);
			if (i == 14)printf("    speed:%d", (-Gamespeed+300)/50);
			printf("\n");
		}
	}
	else if (id == -1) {
		for (i = 0; i < max_x; i++) {
			for (j = 0; j < max_y; j++) {
				if ((i == 0 || i == max_x - 1) && (j == 0 || j == max_y - 1)) printf(" ");
				else if (i == 0 || i == max_x - 1) printf("--");
				else if (j == 0 || j == max_y - 1) printf("|");
				else if (map[i][j] == 2) printf("■");
				else printf("  ");
			}
				if (i == 1) printf("              next:");
				if (i == 11) printf("    score:%d", score);
				if (i == 14)printf("    speed:%d", score / 100);
				printf("\n");
			
		}
	}
	for (i = 29; i < 40; i++) {
		for (j = 2; j < 11; j++) {
			gotoxy(i, j);
			printf(" ");
		}
	}
	gotoxy(34, 6);
	printf("■");
	for (i = 0; i < 5; i = i + 2) {
		gotoxy(34 + 2*shape[next][i + 1], 6 + shape[next][i]);
		printf("■");
	}
	gotoxy(0, max_x + 1);
	Sleep(Gamespeed);
}

int can_move(int x, int y, int id) {
	if (map[x][y] !=0) return(0);
	for (int i = 0; i < 5; i = i + 2) {
		if (map[x + shape[id][i]][y + shape[id][i + 1]] !=0)
			return(0);
	}
	return(1);
}

void can_score() {
	int i, j;
	for (i = 1; i < max_x-1; i++) {
		int flag = 0;
		for (j = 1; j < max_y-1; j++) {
			if (map[i][j] != 2)
			{ flag = 1; 
			break; }
		}
		if (flag == 0) {
			mark = 1;
			int k = 3;
			while (k--) {
				gotoxy(1, i);
				for (int ii = 1; ii < max_y - 1; ii++) {

					if (k % 2 == 1) printf("  ");

					else printf("■");

				}
				
				Sleep(100);
			}
			if (i != 1) {
				for (int ii = i; ii > 1;ii--) {
					for (int jj = 1; jj < max_y-1; jj++) {
						map[ii][jj] = map[ii - 1][jj];
					}
				}
			}
			else if (i == 1) {
				for (int jj = 1; jj < max_y - 1; jj++) {
					map[1][jj] = 0;
				}
			}
			show_map(-1);
			score += 10;
			if (score % 100 == 0 && score != 0) Gamespeed -= 50;
		}
		
	}
	
}

void Init(int id) {
	int i, j;
	for (i = 0; i < max_x; i++) {
		for (j = 0; j < max_y; j++) {
			if (i == max_x - 1 || j == 0 || j == max_y - 1) {
				map[i][j] = -1;
			}
		}
	}
	cur_x = 0;
	cur_y = 6;
	show_map(id);
}

void main() {
	int id;
	int set = 1;

	srand(time(0));

	id = rand() % 28;
	id = (id + 28) % 28;

	next = rand() % 28;
	next = (next + 28) % 28;

	Init(id);
	while (1) {
	Here:mark = 0;
		if (set == 0) {
			id = next;
			next = rand() % 28;
			next = (next + 28) % 28;
			cur_x = 0;
			cur_y = 6;
			set = 1;
		}

		if (_kbhit()) {
			key = _getch();
			switch (key) {
			case UP: {
				int tem = id;
				id++;
				if (id % 4 == 0 && id != 0) id = id - 4;
				if (!can_move(cur_x, cur_y, id)) id = tem;
				break;
			}

			case DOWN: {
				if (can_move(cur_x + 1, cur_y, id))  cur_x++; break; }

			case LEFT: {
				if (can_move(cur_x, cur_y - 1, id))  cur_y --; break; }

			case RIGHT: {
				if (can_move(cur_x, cur_y + 1, id)) cur_y ++; break; }

			case ESC: {
				system("pause>nul");
				exit(0);
				break;
			}
			case SPACE:
			{
				while (can_move(cur_x + 1, cur_x, id)) { cur_x++; }
				break;
			}
			case '1':
			{
				Gamespeed -= 50;
				break;
			}
			case '2':
			{
				Gamespeed += 50;
				break;
			}
			}
		}
		else {
			game_over();
			if (can_move(cur_x + 1, cur_y, id)==1) cur_x++;
			else {
				map[cur_x][cur_y] = 2;
				for (int i = 0; i < 5; i = i + 2) {
					map[cur_x + shape[id][i]][cur_y + shape[id][i + 1]] = 2;
					set = 0;
				}
			}
			can_score();
			if (mark != 1) show_map(id);
			goto Here;

		}
	}
	return;
}