#pragma once
#ifndef _bst_h
#define _bst_h

typedef int(*cmpFnT)(const void *p1, const void *p2);

typedef struct bstCDT *bstADT;

typedef void(*nodeFnT)(void *np, void *clientData);//��ڵ���صĺ�������ɾ���ڵ㣩

typedef void(*nodeInitFnT)(void *np, void *kp, void *clientData);//�ڵ��ʼ������

//���Ĳ���
//����������
bstADT NewBst(int size, cmpFnT cmpfn, nodeInitFnT nodeInitfnT);//��������
void FreeBst(bstADT bst, nodeFnT freeNodeFn);//�ͷ��ڴ�
void *FindBSTNode(bstADT bst, void *kp);
void *InsertBSTNode(bstADT bst, void *kp, void *clientData);//��ĳ��λ��(kp)����ڵ�
void *DeleteBSTNode(bstADT bst, void *kp);

//������
typedef enum{InOrder,PreOrder,PostOrder} traversalOrderT;
void MapBst(nodeFnT fn, bstADT bst, traversalOrderT order, void *clientData);

//ѡ��������
void *BstRoot(bstADT bst);
void *BstLeftChild(bstADT bst,void *np);
void *BstRightChild(bstADT bst, void *np);

#endif // !_bst_h
