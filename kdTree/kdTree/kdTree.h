#ifndef _KDTREE_H
#define _KDTREE_H

#include<stdlib.h>
#include<stdio.h>
struct kdTreeNode;
typedef struct kdTreeNode *kdTree;

typedef int ItemType[2];

kdTree Insert(ItemType Item, kdTree T);
void PrintRange(ItemType Low, ItemType High, kdTree T);

#endif // !_KDTREE_H

#pragma once
