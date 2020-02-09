#include<stdio.h>
#include<stdlib.h>
#include"bst.h"
#include"genlib.h"


typedef void *treeT;//指针的指针（为了按指针传递）

struct bstCDT
{
	treeT root;
	int userSize, totalSize;
	cmpFnT cmpFn;
	nodeInitFnT nodeInitfnT;

};

typedef struct {
	treeT left, right;

}bstDataT;

//某些接口函数原型

static treeT *RecFindNode(bstADT bst, treeT t, void *kp);
static void *RecInsertNode(bstADT bst, treeT *tptr, void *kp, void *clientData);
static void *RecDeleteNode(bstADT bst, treeT *tptr, void *kp);
static void *DeleteTargetNode(bstADT bst, treeT *tptr);
static void RecMapBST(nodeFnT fn, bstADT bst, treeT t, traversalOrderT Order, void *clientData);
static bstDataT *BstData(bstADT bst, treeT t);

//实现
//构造器函数
bstADT NewBst(int size, cmpFnT cmpfn, nodeInitFnT nodeInitfnT) {
	bstADT bst;
	bst = (bstADT)malloc(sizeof(struct bstCDT));
	bst->root = NULL;
	bst->cmpFn = cmpfn;
	bst->nodeInitfnT = nodeInitfnT;
	bst->userSize = size;
	bst->totalSize = bst->userSize + sizeof(bstDataT);
	return(bst);
}

void FreeBst(bstADT bst, nodeFnT freeNodeFn) {
	MapBst(freeNodeFn, bst, PostOrder, NULL);
	free(bst);
}

//功能函数
void *FindBSTNode(bstADT bst, void *kp) {
	return(RecFindNode(bst, bst->root, kp));
}//包装器函数，其实要传入树根root参数

static treeT *RecFindNode(bstADT bst, treeT t, void *kp) {
	bstDataT *dp;
	int sign;

	if (t == NULL) return(NULL);
	sign = bst->cmpFn(kp, t);
	if (sign == 0) return(t);
	dp = BstData(bst, t);
	if (sign < 0) {
		return(RecFindNode(bst, dp->left, kp));
	}
	else {
		return(RecFindNode(bst, dp->right, kp));
	}
}



void *InsertBSTNode(bstADT bst, void *kp, void *clientData) {
	return(RecInsertNode(bst, &(bst->root), kp, clientData));
}

static void *RecInsertNode(bstADT bst, treeT *tptr, void *kp, void *clientData) {
	bstDataT *dp;
	treeT t;
	int sign;

	t = *tptr;
	if (t == NULL) {
		t =malloc(bst->totalSize+1);
		bst->nodeInitfnT(t, kp, clientData);
		dp = BstData(bst, t);
		dp->left = dp->right = NULL;
		*tptr = t;
		return(t);
	}
	sign = bst->cmpFn(kp, t);
	if (sign == 0) return(t);
	dp = BstData(bst, t);
	if (sign < 0) {
		return(RecInsertNode(bst, &dp->left, kp, clientData));
	}
	else {
		return(RecInsertNode(bst, &dp->right, kp, clientData));
	}
}


void *DeleteBSTNode(bstADT bst, void *kp) {
	return(RecDeleteNode(bst, &bst->root, kp));
}

static void *RecDeleteNode(bstADT bst, treeT *tptr, void *kp) {
	bstDataT *dp;
	treeT t;
	int sign;
	
	t = *tptr;
	if (t == NULL) return(NULL);
	sign = bst->cmpFn(kp, t);
	if (sign == 0) {
		DeleteTargetNode(bst, tptr);
	}
	dp = BstData(bst, t);
	if (sign < 0) {
		return(RecDeleteNode(bst, &dp->left, kp));
		 }
	else {
		return(RecDeleteNode(bst, &dp->right, kp));
	}
}

static void *DeleteTargetNode(bstADT bst, treeT *tptr) {
	bstDataT *dp1,*dp2;
	treeT *lt,target;

	target = *tptr;

	dp1 = BstData(bst, target);
	if (dp1->left == NULL) {
		*tptr = dp1->right;
	}
	else if (dp1->right == NULL) {
		*tptr = dp1->left;
	}
	else {
		lt = &dp1->left;//用左子树最右的子树代替删除节点，再把删除节点左右子树修改下
		dp2 = BstData(bst, *lt);
		while (dp2->right != NULL) {
			lt = &dp2->right;
			dp2 = BstData(bst, *lt);
		}
		*tptr = *lt;
		*lt = dp2->left;
		dp2->left = dp1->left;//修改删除节点的左右子树
		dp2->right = dp1->right;

	}
	return(target);
}



void MapBst(nodeFnT fn, bstADT bst, traversalOrderT order, void *clientData) {
	RecMapBST(fn, bst, bst->root, order, clientData);
}

static void RecMapBST(nodeFnT fn, bstADT bst, treeT t, traversalOrderT Order, void *clientData) {
	bstDataT *dp;
	if (t != NULL) {
		dp = BstData(bst, t);
		if (Order == InOrder) {
			fn(t, clientData);
			RecMapBST(fn, bst, dp->right,Order, clientData);
		}
		else if (Order == PreOrder) {
			fn(t, clientData);
			RecMapBST(fn, bst, dp->left,Order, clientData);
		}
		else if (Order == PostOrder) fn(t, clientData);
	}
}

//选择器函数

void *BstRoot(bstADT bst) {
	return(bst->root);
}

void *BstLeftChild(bstADT bst, void *np) {
	bstDataT *dp;

	if (np == NULL) {
		printf("BSTLeftChild:Argument is NULL");
		exit(0);
	}
	dp = BstData(bst, np);
	return(dp->left);
}

void *BstRightChild(bstADT bst, void *np) {
	bstDataT *dp;

	if (np == NULL) {
		printf("BSTRightChild:Argument is NULL");
		exit(0);
	}
	dp = BstData(bst, np);
	return(dp->right);
}

static bstDataT *BstData(bstADT bst, treeT t) {
	return((bstDataT *)(((char *)t) + (bst->userSize)));
}