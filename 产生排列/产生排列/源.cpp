#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void RecursivePermute(char str[], int k);
void exchange(char *str, int k, int i);

int main() {
	char a[20];
	scanf_s("%s", &a, 20);
	RecursivePermute(a, 0);
}

void RecursivePermute(char str[], int k) {
	int i;
	if (k == strlen(str)) {
		printf("%s\n", str);
	}
	else {
		for (i = k; i < strlen(str); i++) {
			exchange(str, k, i);
			RecursivePermute(str, k + 1);
			exchange(str, k, i);
		}
	}
}

void exchange(char *str, int k, int i) {
	char temp;
	temp = str[k];
	str[k] = str[i];
	str[i] = temp;
}