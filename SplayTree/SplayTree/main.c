#include"Splay.h"
#include<stdio.h>

void main()
{
	int i;
	int a[] = {3,21,123,1,32,22,333,31,6,31};
	SplayTree T = NULL;
	T = MakeEmpty(T);
	for (i = 0;i < 10;i++)
	{
		T=Insert(a[i], T);
	}
	T = Remove(1, T);
	while (1);
}