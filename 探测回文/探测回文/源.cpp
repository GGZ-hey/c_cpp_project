#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int Checkpalindrome(char str[], int a) {
	if (a <= 1) {
		return (1);
	}
	else return(str[0] == str[a - 1] && Checkpalindrome(str + 1, a - 2));
}

int ispalindrome(char str[]) {
	return(Checkpalindrome(str, strlen(str)));
}

int main() {
	char a[20] ;
	scanf_s("%s",a,sizeof(a));
	printf("%s\n", a);
	if (ispalindrome(a))  printf("它是回文");
	else printf("它不是回文");
}