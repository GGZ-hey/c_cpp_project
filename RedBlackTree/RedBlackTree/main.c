#include"RedBlack.h"
#include<stdio.h>

void main()
{
	int i;
	int a[] = { 3,21,123,1,32,22,333,31,6,31 };
	RedBlackTree T = NULL;
	T = Initialize();
	for (i = 0;i < 10;i++)
	{
		T = Insert(a[i], T);
	}
	while (1);
}