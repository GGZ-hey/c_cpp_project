#include "kdTree.h"

struct kdTreeNode 
{
	ItemType Data;
	kdTree Left;
	kdTree Right;
};

static kdTree
RecrusiveInsert(ItemType Item, kdTree T, int Level)
{
	if (T == NULL)
	{
		T = malloc(sizeof(struct kdTreeNode));
		if (T == NULL)
			exit(0);
		T->Data[0] = Item[0];
		T->Data[1] = Item[1];
		T->Left = T->Right = NULL;
	}
	else if (Item[Level] < T->Data[Level])
		T->Left=RecrusiveInsert(Item, T->Left, !Level);
	else
		T->Right=RecrusiveInsert(Item, T->Right, !Level);
	return T;
}

kdTree Insert(ItemType Item, kdTree T)
{
	return RecrusiveInsert(Item, T, 0);
}

static void
RecrusivePrintRange(ItemType Low, ItemType High, kdTree T,int Level)
{
	if (T != NULL)
	{
		if (Low[0] <= T->Data[0] && T->Data[0] <= High[0] &&
			Low[1] <= T->Data[1] && T->Data[1] <= High[1])
		{
			printf("%d %d\t", T->Data[0], T->Data[1]);
		}
		if (T->Data[Level] >= Low[Level])
			RecrusivePrintRange(Low, High, T->Left, !Level);
		if (T->Data[Level] <= High[Level])
			RecrusivePrintRange(Low, High, T->Right, !Level);
	}
}

void PrintRange(ItemType Low, ItemType High, kdTree T)
{
	RecrusivePrintRange(Low, High, T, 0);
}
