#include "Splay.h"
#include<stdlib.h>

struct SplayNode
{
	ElementType Element;
	SplayTree Left;
	SplayTree Right;
};
typedef struct SplayNode *Position;
static Position NullNode = NULL;

SplayTree Initialize(void)
{
	if (NullNode == NULL)
	{
		NullNode = malloc(sizeof(struct SplayNode));
		if (NullNode == NULL)
		{
			exit(0);
		}
		NullNode->Left = NullNode->Right = NullNode;
	}
	return NullNode;
}
Position RotateWithLeft(Position P)  //右旋
{
	Position Leftt;
	if (P->Left->Left == NullNode)
		return P;
	else
	{
		Leftt = P->Left;
		P->Left = Leftt->Right;
		Leftt->Right = P;
		P = Leftt;
	}
	return P;
}

Position RotateWithRight(Position P)
{
	Position Rightt;
	if (P->Right->Right == NullNode)
		return P;
	else
	{
		Rightt = P->Right;
		P->Right = Rightt->Left;
		Rightt->Left = P;
		P = Rightt;
	}
	return P;
}

SplayTree
Splay(ElementType Item, Position X) //!!!!!!关键
{
	struct SplayNode Header;
	Position LeftMax,RightMin;//!未初始化
	NullNode = Initialize();
	Header.Left = Header.Right = NullNode;
	LeftMax = RightMin = &Header;  //chu shi hua
	NullNode->Element = Item;

	while (Item!=X->Element)
	{
		if (Item<X->Element)
		{
			if (Item < X->Left->Element)
				X = RotateWithLeft(X);
			if (X->Left == NullNode)
				break;
			//zhi
			RightMin->Left = X;
			RightMin = X;
			X = X->Left;
		}
		else 
		{
			if (Item > X->Left->Element)
				X = RotateWithRight(X);
			if (X->Right == NullNode)
				break;
			//zhi
			LeftMax->Right = X;
			LeftMax = X;
			X = X->Right;
		}
	}
	//Merge
	LeftMax->Right = X->Left;
	RightMin->Left = X->Right;
	X->Left = Header.Right ;
	X->Right = Header.Left ;

	return X;
}




SplayTree Insert(ElementType X, SplayTree T)
{
	static Position NewNode;
	NewNode = malloc(sizeof(struct SplayNode));
	if (NewNode == NULL)
		exit(0);
	NewNode->Left = NewNode->Right = NullNode;
	NewNode->Element = X;
	if (T == NullNode)
	{
		T = NewNode;
	}
	else
	{
		T = Splay(X, T);
		if (X < T->Element)
		{
			NewNode->Left = T->Left;
			NewNode->Right = T;
			T->Left = NullNode;
			T = NewNode;
		}
		else if (X > T->Element)
		{
			NewNode->Right = T->Right;
			NewNode->Left = T;
			T->Right = NullNode;
			T = NewNode;
		}
		else
			return T;
	}
	NewNode = NULL;
	return T;
}

SplayTree Remove(ElementType X, SplayTree T)
{
	Position Tmp;
	if (T != NullNode)
	{
		T = Splay(X, T);
		if (T->Element == X)
		{
			if (T->Left == NullNode)
				Tmp = T->Right;
			else
			{
				Tmp = T->Left;
				Tmp = Splay(X, Tmp);
				Tmp->Right = T->Right;
			}
			free(T); //!!!!!要记得free掉
			T = Tmp;
		}
	}
	return T;
}

SplayTree MakeEmpty(SplayTree T)
{
	if (T == NULL)
	{
		NullNode = Initialize();
		T = NullNode;
		return T;
	}
}