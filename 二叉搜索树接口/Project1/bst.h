#pragma once
#ifndef _bst_h
#define _bst_h

typedef int(*cmpFnT)(const void *p1, const void *p2);

typedef struct bstCDT *bstADT;

typedef void(*nodeFnT)(void *np, void *clientData);//与节点相关的函数（如删除节点）

typedef void(*nodeInitFnT)(void *np, void *kp, void *clientData);//节点初始化函数

//树的操作
//构造器函数
bstADT NewBst(int size, cmpFnT cmpfn, nodeInitFnT nodeInitfnT);//创建新树
void FreeBst(bstADT bst, nodeFnT freeNodeFn);//释放内存
void *FindBSTNode(bstADT bst, void *kp);
void *InsertBSTNode(bstADT bst, void *kp, void *clientData);//在某个位置(kp)插入节点
void *DeleteBSTNode(bstADT bst, void *kp);

//遍历数
typedef enum{InOrder,PreOrder,PostOrder} traversalOrderT;
void MapBst(nodeFnT fn, bstADT bst, traversalOrderT order, void *clientData);

//选择器函数
void *BstRoot(bstADT bst);
void *BstLeftChild(bstADT bst,void *np);
void *BstRightChild(bstADT bst, void *np);

#endif // !_bst_h
