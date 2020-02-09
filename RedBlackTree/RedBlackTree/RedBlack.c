#include "RedBlack.h"
#include<stdlib.h>
#include<math.h>

#define Infinity INT_MAX
#define NegInfinity INT_MIN

typedef enum ColorType{Red,Black} ColorType;
struct RedBlackNode
{
	ElementType Element;
	RedBlackTree Left;
	RedBlackTree Right;
	ColorType Color;
};
typedef struct RedBlackNode *Position;

Position NullNode = NULL;

RedBlackTree Initialize(void)
{
	RedBlackTree T;
	if (NullNode == NULL)
	{
		NullNode = malloc(sizeof(struct RedBlackNode));
		if (NullNode == NULL)
			exit(0);
		NullNode->Color = Black;
		NullNode->Element = Infinity;
		NullNode->Left = NullNode->Right = NullNode;
	}

	T = malloc(sizeof(struct RedBlackNode));
	T->Element = NegInfinity;
	T->Left = T->Right = NullNode;
	T->Color = Black;

	return T;
}
Position RotateWithLeft(Position P)  //右旋
{
	Position Leftt;
	Leftt = P->Left;
	P->Left = Leftt->Right;
	Leftt->Right = P;
	P = Leftt;
	return P;
}

Position RotateWithRight(Position P)
{
	Position Rightt;
	Rightt = P->Right;
	P->Right = Rightt->Left;
	Rightt->Left = P;
	P = Rightt;
	return P;
}
static Position
Rotate(ElementType Item, Position Parent)
{
	if (Item<Parent->Element)
	{
		return Parent->Left = Item < Parent->Left->Element ? RotateWithLeft(Parent->Left) : RotateWithRight(Parent->Left);
	}
	else {
		return Parent->Right = Item < Parent->Right->Element ? RotateWithLeft(Parent->Right) : RotateWithRight(Parent->Right);
	}
}

static Position X, P, GP, GGP;



static void
HandleReorient(ElementType Item,RedBlackTree T)
{
	X->Color = Red;
	X->Left->Color = Black;
	X->Right->Color = Black;
	if (P->Color == Red)
	{
		if (!(Item < GP->Element == Item < P->Element))
		{
			P = Rotate(Item, GP);
		}
		X = Rotate(Item, GGP);
		X->Color = Black;
	}
	T->Right->Color = Black;            //Right子树是树根
}

RedBlackTree Insert(ElementType Item, RedBlackTree T)
{
	X = P = GP = GGP = T;
	NullNode->Element = Item;
	while (X->Element != Item&& X!=NullNode)
	{
		GGP = GP;GP = P;P = X;
		if (Item < X->Element)
			X = X->Left;
		else
			X = X->Right;
		if (X->Right->Color == Red && X->Left->Color == Red)
			HandleReorient(Item, T);
	}
	if (X != NullNode)
		return T;//重复
	X = malloc(sizeof(struct RedBlackNode));
	if (X == NULL)
		exit(0);
	X->Element = Item;
	X->Color = Red;
	X->Left = X->Right = NullNode;

	if (Item < P->Element)
		P->Left = X;
	else
		P->Right = X;
	HandleReorient(Item, T);

	return T;
}
