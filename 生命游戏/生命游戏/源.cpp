#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>

const int DEAD= 0;
const int LIVE =1;
const int map_size = 20;

int map[20][20] = { 0 };



void init() {
	int i, j;
	for (i = 0; i < map_size; i++) {
		for (j = 0; j < map_size; j++) {
			map[i][j] = rand()%2;
		}
	}
}

void show_map() {
	int i,j ;
	for (i = 0; i < map_size; i++) {
		for (j = 0; j < map_size; j++) {
			if (map[i][j] == LIVE) { printf(" *"); }
			else { printf("  "); }
		}
		printf("\n");
	}
}

int judge(int x, int y) {
	int i, j;
	int num=0;
	for (i = x - 1; i <= x + 1; i++) {
		if (i<0 || i>map_size - 1) {
			continue;
		}
		for (j = y - 1; j <= y + 1; j++) {
			if (j<0 || j>map_size - 1) {
				continue;
			}
			if (map[i][j] == 1) num++;
		}
	}
	if (map[x][j] == 1) num--;
	return(num);
}

void run() {
	int i, j;
	int num;
	for (i = 0; i < map_size; i++) {
		for (j = 0; j < map_size; j++) {
			num=judge(i, j);
			if (num == 3) map[i][j] = LIVE;
			else if (num != 2) map[i][j] = DEAD;
		}
	}
}


int main() {
	srand(time(NULL));
	init();
	while (1) {
		run();
		show_map();
		system("cls");
	}
	system("pause");
	while (1);
}
