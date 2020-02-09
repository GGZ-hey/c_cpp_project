#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <conio.h>
#include<Windows.h>

#define bool int
#define ture 1
#define false 0

int MAP[4][4] = { 0 };

typedef enum {
	UNKNOW,
	UP,
	DOWN,
	LEFT,
	RIGHT
} Direction;

int score() {
	int i, j;
	int score;
		score=0;
	for (j = 0; j < 4; j++) {
		for (i = 0; i < 4; i++) {
			score += MAP[i][j];
		}
	}
	return(score);
}


void print_Map() {
	int i, j;
	printf("*-------*-------*-------*-------*\n");
	for (j = 0; j < 4; j++) {
		printf("|");
		for (i = 0; i < 4; i++) {
			MAP[i][j] ? printf("%d", MAP[i][j]) : printf(" ");
			printf("\t|");
		}
		printf("\n");
		printf("*-------*-------*-------*-------*\n");
	}
	printf("\n");
	printf("你的得分是   %d   \n", score());
	printf("\n");
	printf("出品人：龚国铮\n");
}

void move(Direction a) {
	int i, j, k;
	switch (a) {
	case UP:
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 3; j++) {
				if (!MAP[i][j]) {
					for (k = j; k < 3; k++) {
						MAP[i][k] = MAP[i][k + 1];
					}
					MAP[i][3] = 0;
				}
			}
		}
		break;

	case DOWN:
		for (i = 0; i < 4; i++) {
			for (j = 3; j > 0; j--) {
				if (!MAP[i][j]) {
					for (k = j; k >0; k--) {
						MAP[i][k] = MAP[i][k - 1];
					}
					MAP[i][0] = 0;

				}
			}
		}
		break;

	case LEFT:
		for (j = 0; j < 4; j++) {
			for (i = 0; i < 3; i++) {
				if (!MAP[i][j]) {
					for (k = i; k < 3; k++) {
						MAP[k][j] = MAP[k + 1][j];
					}
					MAP[3][j] = 0;
				}
			}
		}
		break;

	case RIGHT:
		for (j = 0; j < 4; j++) {
			for (i = 3; i > 0; i--) {
				if (!MAP[i][j]) {
					for (k = i; k > 0; k--) {
						MAP[k][j] = MAP[k - 1][j];
					}
					MAP[0][j] = 0;
				}
			}
		}
		break;
	}
}

void doAction(Direction a) {
	int i, j;
	move(a);
	switch (a) {
	case UP:
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 3; j++) {
				if (MAP[i][j] && MAP[i][j] == MAP[i][j + 1]) {
					MAP[i][j] += MAP[i][j + 1];
					MAP[i][j + 1] = 0;
				}
			}
		}
		break;
	case DOWN:
		for (i = 0; i < 4; i++) {
			for (j = 3; j > 0; j--) {
				if (MAP[i][j] && MAP[i][j] == MAP[i][j - 1]) {
					MAP[i][j] += MAP[i][j - 1];
					MAP[i][j - 1] = 0;
				}
			}
		}
		break;
	case LEFT:
		for (j = 0; j < 4; j++) {
			for (i = 0; i < 3; i++) {
				if (MAP[i][j] && MAP[i][j] == MAP[i + 1][j]) {
					MAP[i][j] += MAP[i + 1][j];
					MAP[i + 1][j] = 0;
				}
			}
		}
		break;
	case RIGHT:
		for (j = 0; j < 4; j++) {
			for (i = 3; i > 0; i--) {
				if (MAP[i][j] && MAP[i][j] == MAP[i - 1][j]){
					MAP[i][j] += MAP[i - 1][j];
					MAP[i - 1][j] = 0;
				}
			}
		}
		break;

	}

	move(a);
}



bool canmove(Direction a) {
	int i, j;
	switch (a)
	{
	case UP:
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (!MAP[i][j]) return (ture);
				else {
					if (MAP[i][j] && MAP[i][j] == MAP[i][j + 1]) {
						return (ture);
					}

				}
			}
		}
		break;

	case DOWN:
		for (i = 0; i < 4; i++) {
			for (j = 3; j > 0; j--) {
				if (!MAP[i][j]) return (ture);
				else {
					if (MAP[i][j] && MAP[i][j] == MAP[i][j - 1]) {
						return(true);
					}

				}
			}
		}
		break;

	case LEFT:
		for (j = 0; j < 4; j++) {
			for (i = 0; i < 3; i++) {
				if (!MAP[i][j]) return (ture);
				else {
					if (MAP[i][j] && MAP[i][j] == MAP[i + 1][j]) { return(ture); }
				}
			}
		}

	case RIGHT:
		for (j = 0; j < 4; j++) {
			for (i = 3; i > 0; i--) {
				if (!MAP[i][j]) return (ture);
				else {
					if (MAP[i][j] && MAP[i][j] == MAP[i - 1][j]) return(ture);
				}
			}
		}
	
	}
	return(false);
}
Direction getnextstep() {
	char a;
	a = _getch();
	if (a != 72 && a != 75 && a != 77 && a != 80)  return UNKNOW;
	switch (a)
	{
	case 72:
		return UP;
	case 80:
			return DOWN;
	case 75:
		return LEFT;
	case 77:
		return RIGHT;
	default:
		return UNKNOW;
	}

}

void PUTNEW(Direction a) 
{
	int *box[16];
	int *target;
	int count = 0;
	int i, j;
	switch (a)
	{
	case UP:
		for (i = 0; i < 4; i++) {
			j = 0;
			while (j < 4) {
				if (MAP[i][j] == 0) {
					box[count] = &MAP[i][j];
					count++;
					break;
				}
				else j++;
			}
		}

	case DOWN:
		for (i = 0; i < 4; i++) {
			j = 3;
			while (j >= 0) {
				if (MAP[i][j] == 0) {
					box[count] = &MAP[i][j];
					count++;
					break;
				}
				else j--;
			}
		}

	case LEFT:
		for (j = 0; j < 4; j++) {
			i = 0;
			while(i<4) {
				if (MAP[i][j] == 0) {
					box[count] = &MAP[i][j];
					count++;
					break;
				}
				else i++;
			}
		}

	case RIGHT:
		for (j = 0; j < 4; j++) {
			i = 3;
			while(i>=0) {
				if (MAP[i][j] == 0) {
					box[count] = &MAP[i][j];
					count++;
					break;
				}
				else i--;
			}
		}
	}

	if (count != 0) {
		target = box[rand() % count];
		*target = 2;
	}

}


void main() {
	Direction next_step;
	srand(time(0));
	PUTNEW(DOWN);
		PUTNEW(DOWN);
	print_Map();
	while (1) {
		if (!canmove(UP) && !canmove(DOWN) && !canmove(LEFT) && !canmove(RIGHT)) break; 
			next_step = getnextstep();
			if (next_step == UNKNOW) continue;
			if (!canmove(next_step)) continue;
			system("cls");
			doAction(next_step);
			PUTNEW(next_step);
			print_Map();
	}
	
	printf("You died!\n");
	while (1);


}