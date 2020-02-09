#include<stdio.h>
#include<stdlib.h>

#define Stack_initsize 10

typedef struct {
	int size;
	int count;
	int *top;
}Stack;

int New_Stack(Stack *s) {
	
	s->size = Stack_initsize;
	s->top = NULL;
	s->count = 0;
	return 1;
}

void push(Stack *s, int data) {
	if (s->count> s->size) {
		s->top = (int *)realloc(s->top,(s->size+ Stack_initsize)*sizeof(int));

		if (!s->top) {
			exit(0);
		}

		s->top++;
		s->size += Stack_initsize ;
	}
	if (s->top == NULL) {
		int *c;
		c = new(int);
		*c = data;
		s->top = c;
		s->top++;
	}
	else { *s->top++ = data; }
	s->count++;
}

int Stack_isempty(Stack *s){
	if (s->top == NULL) return(1);
	else return(0);
}

int pop(Stack *s) {
	int a;
	if (Stack_isempty(s)) {
		exit(0);
	}
	s->count--;
	s->top--;
	a=*s->top;
	if (s->count == 0) {
		s->top = NULL;
	}
	return(a);
}

int main() {
	Stack s;
	int a;
	printf("请输入一个非负十进制整数");
	scanf_s("%d", &a);
	New_Stack(&s);
	while (a !=0) {
		push(&s, a % 8);
		a /= 8;
	}
	int b;
	printf("八进制数是\n");
	while (!Stack_isempty(&s)) {
		b = pop(&s);
		printf("%d", b);
	}
	printf("\n");
	while (1);
}