#include"kdTree.h"

void main()
{
	kdTree T;
	int Low[2] = { 10,10 };
	int High[2] = { 40,80 };
	T = NULL;
	int a[][2] = { {27,28},{30,11},{31,85},{29,16},{40,26},{38,23},{7,39},{32,29},{15,61} };
	int i;
	for (i = 0;i < 9;i++)
	{
		T = Insert(a[i], T);
	}
	PrintRange(Low, High, T);
	while (1);
}