#include "QuickSort.h"

static void
swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int
Get_Pivot(int A[], int Left, int Right)  //保证PIVOT是中间值
{
	int Mid = (Left + Right) / 2;
	if (A[Left] > A[Mid])
		swap(&A[Left], &A[Mid]);
	if (A[Left] > A[Right])
		swap(&A[Left], &A[Right]);
	if(A[Mid]>A[Right])
		swap(&A[Mid], &A[Right]);

	swap(&A[Mid], &A[Right - 1]);  //把pivot值放入Right-1的位置
	return A[Right-1];
}

void QuickSort(int A[], int n)
{
	return(QuickSort1(A,0,n-1));
}

void InsertSort(int A[], int n)  //插入排序
{
	int i, j;
	int tmp;
	for (i = 1;i < n;i++)
	{
		for (tmp=A[i],j = i;j >= 0;j--)   //小的在前
		{
			if (A[j - 1] > tmp) A[j] = A[j - 1];
			else break;
		}
		A[j] = tmp;
	}
}

int QuickSelete(int A[], int k, int n)
{
	return (QuickSelete1(A,k,0,n-1));
}

int QuickSelete1(int A[], int k,int Left,int Right)
{
	int i, j;
	int pivot;
	if ((Right - Left) >= CutOff)
	{
		pivot = Get_Pivot(A, Left, Right);
		i = Left, j = Right - 1;
		for (;;)
		{
			while (A[++i] < pivot) {};
			while (A[--j] > pivot) {};//经历这两步后A[i]>A[j]
			if (i < j)//防止越界
			{
				swap(&A[i], &A[j]);
			}
			else
				break;
		}
		swap(&A[i], &A[Right - 1]);//千万别漏了！！！中枢值需要放到i位置
		if (i < k - 1)
		{
			QuickSelete1(A,k,i+1,Right);
		}
		else if (i > k - 1)
		{
			QuickSelete1(A, k, Left, i - 1);
		}
	}
	else
		InsertSort(A + Left, Right - Left + 1);

	return A[k - 1];
}

void QuickSort1(int A[], int Left, int Right)
{
	int i, j;
	int pivot;
	if ((Right - Left) >= CutOff)
	{
		pivot = Get_Pivot(A, Left, Right);
		i = Left, j = Right - 1;
		for (;;)
		{
			while (A[++i] < pivot) {};
			while (A[--j] > pivot) {};//经历这两步后A[i]>A[j]
			if (i < j)//防止越界
			{
				swap(&A[i], &A[j]);
			}
			else
				break;
		}
		swap(&A[i], &A[Right - 1]);//千万别漏了！！！中枢值需要放到i位置

		QuickSort1(A, Left, i - 1);
		QuickSort1(A, i + 1, Right);
	}
	else
		InsertSort(A + Left, Right - Left + 1);
}