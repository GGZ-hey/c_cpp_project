#include<stdio.h>

int m[8][8] = { 0 };
int num = 0;

int check(int row, int colum);
void output();
void solve(int row);

int main() {
	solve(1);
	while (1);
	return(1);
}

int check(int row, int colum) {
	if (row == 1) return(1);
	int i, j;
	for (i = 0; i <= row - 2; i++) {
		if (m[i][colum - 1] == 1) {
			return 0;
		}
	}

	for (i = row - 2, j = colum - 2; i >= 0 && j >= 0; i--, j--) {
		if (m[i][j] == 1) {
			return 0;
		}
	}

	for (i = row - 2, j = colum; i >= 0 && j < 8; i--, j++) {
		if (m[i][j] == 1) {
			return 0;
		}
	}

	return 1;
}

void output() {
	int i, j;
	num++;
	printf("\n");
	printf("answer %d\n", num);
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			printf("%-2d", m[i][j]);
		}
		printf("\n");
	}
}

void solve(int row) {
	int i;
	for (i = 0; i < 8; i++) {
		m[row - 1][i] = 1;
		if (check(row, i + 1) == 1) {
			if (row == 8) {
				output();
			}
			else
			{
				solve(row + 1);
			}
		}
		m[row - 1][i] = 0;

	}
}