#include<stdio.h>

void moveSingletower(char start, char finish);
void moveTower(int n, char start, char finish, char temp);

int main() {
	int n;
	printf("请输入你想移动的汉诺塔个数:");
	scanf_s("%d", &n);
	moveTower(n, 'A', 'B', 'C');
}

void moveTower(int n, char start, char finish, char temp) {
	if (n == 1) moveSingletower(start, finish);
	else {
		moveTower(n - 1, start, temp, finish);
		moveSingletower(start, finish);
		moveTower(n - 1, temp, finish, start);
	}
}

void moveSingletower(char start, char finish) {
	printf("%c->%c\n", start, finish);
}