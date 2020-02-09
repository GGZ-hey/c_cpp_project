#ifndef _REDBLACK_H
#define _REDBLACK_H

#define ElementType int

struct RedBlackNode;
typedef struct RedBlackNode *RedBlackTree;

RedBlackTree Initialize(void);
RedBlackTree Insert(ElementType Item, RedBlackTree T);

#endif // !_REDBLACK_H

#pragma once
