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
Get_Pivot(int A[], int Left, int Right)  //��֤PIVOT���м�ֵ
{
	int Mid = (Left + Right) / 2;
	if (A[Left] > A[Mid])
		swap(&A[Left], &A[Mid]);
	if (A[Left] > A[Right])
		swap(&A[Left], &A[Right]);
	if(A[Mid]>A[Right])
		swap(&A[Mid], &A[Right]);

	swap(&A[Mid], &A[Right - 1]);  //��pivotֵ����Right-1��λ��
	return A[Right-1];
}

void QuickSort(int A[], int n)
{
	return(QuickSort1(A,0,n-1));
}

void InsertSort(int A[], int n)  //��������
{
	int i, j;
	int tmp;
	for (i = 1;i < n;i++)
	{
		for (tmp=A[i],j = i;j >= 0;j--)   //С����ǰ
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
			while (A[--j] > pivot) {};//������������A[i]>A[j]
			if (i < j)//��ֹԽ��
			{
				swap(&A[i], &A[j]);
			}
			else
				break;
		}
		swap(&A[i], &A[Right - 1]);//ǧ���©�ˣ���������ֵ��Ҫ�ŵ�iλ��
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
			while (A[--j] > pivot) {};//������������A[i]>A[j]
			if (i < j)//��ֹԽ��
			{
				swap(&A[i], &A[j]);
			}
			else
				break;
		}
		swap(&A[i], &A[Right - 1]);//ǧ���©�ˣ���������ֵ��Ҫ�ŵ�iλ��

		QuickSort1(A, Left, i - 1);
		QuickSort1(A, i + 1, Right);
	}
	else
		InsertSort(A + Left, Right - Left + 1);
}