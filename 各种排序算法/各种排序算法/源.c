#include<stdio.h>
#include<stdlib.h>

//1、希尔排序
void xi_er_paiXu(int array[], int n) {
	int flag;
	int temp;
	int i, j, k;
	for (flag = n / 2; flag != 0; flag /= 2) {
		for (i = 0; i < flag; i++) {
			//对每一组运用插入排序算法
			for (j = i; j < n; j += flag)
			{
				temp = array[j];
				for (k = j - flag;k >= 0 && array[k] > temp; k-=flag) {
					array[k + flag] = array[k];
				}
				array[k +flag] = temp;
			}
		}
	}
}

//2、合并排序
int * copySubArray(int array[], int n1, int number) {
	int *result;
	result = (int *)malloc(sizeof(int)*number);
	for (int i = 0; i < number; i++) {
		result[i]=array[n1 + i];
	}
	return(result);
}

void 	Merge(int *array, int * array1, int n1, int * array2, int n2) {
	int p1, p2,p;
	p = p1 = p2 = 0;
	while (p1 < n1&&p2 < n2) {
		if (array1[p1] < array2[p2]) {
			array[p] = array1[p1];
			p++; p1++;
		}
		else {
			array[p] = array2[p2];
			p++; p2++;
		}
	}
	while (p1 < n1) {
		array[p] = array1[p1];
		p++; p1++;
	}
	while (p2 < n2) {
		array[p] = array2[p2];
		p++; p2++;
	}
}


void He_bing_Paixu(int array[], int n) {
	if (n <= 1) return;
	int n1, n2;
	int *array1, *array2;
	n1 = n / 2;
	n2 = n - n1;
	array1 = copySubArray(array,0,n1);   //数组复制次数过多，可优化
	array2 = copySubArray(array, n1, n2);
	He_bing_Paixu(array1, n1);
	He_bing_Paixu(array2, n2);
	Merge(array, array1, n1, array2, n2);
	free(array1);
	free(array2);
}

//2-2  归并排序（优化版）

void Mergeeeee(int A[], int tmp[], int Lpos, int Rpos, int Rend)
{
	int i;
	int Lend = Rpos - 1;
	int Tmp_po = Lpos;
	int Num = Rend - Lpos + 1;
	while (Lpos <= Lend &&
		Rpos <= Rend)
	{
		if (A[Lpos] < A[Rpos])
			tmp[Tmp_po++] = A[Lpos++];
		else tmp[Tmp_po++] = A[Rpos++];
	}
	while (Lpos <= Lend)
		tmp[Tmp_po++] = A[Lpos++];
	while (Rpos <= Rend)
		tmp[Tmp_po++] = A[Rpos++];
	for (i = 0;i < Num;i++,Rend--)
	{
		A[Rend] = tmp[Rend];
	}
}

void MSort(int A[], int tmp[], int Left, int Right)
{
	int Mid;
	Mid = (Right+Left) / 2;
	if (Left == Right)
		return;
	else
	{
		MSort(A, tmp, Left, Mid);
		MSort(A, tmp, Mid + 1, Right);
		Mergeeeee(A, tmp, Left, Mid + 1, Right);
	}
}

void Merge_Sort(int A[], int n)
{
	int *tmp;
	tmp = malloc(sizeof(int)*n);
	if (tmp == NULL)
	{
		printf("Error:malloc Error!!!\n");
		exit(0);
	}
	else {
		MSort(A, tmp, 0, n - 1);
		free(tmp);
	}
}

//3、快速排序（运用最多）
static int Partion(int array[], int n) {
	int lh, rh;
	int temp;
	rh = n-1, lh = 1;
	int jian_kong=array[0];//定义监控值
	while(1) {
		while (lh < rh&&array[rh] >= jian_kong) rh--;
		while (lh < rh&&array[lh] < jian_kong) lh++;
		if (lh == rh) break;
		temp = array[lh];
		array[lh] = array[rh];
		array[rh] = temp;
		
	}
	if (jian_kong < array[lh]) return(0);
	array[0] = array[lh];
	array[lh] = jian_kong;
	if (lh == rh) return(lh);
	
}

void Quick_soft(int array[], int n) {
	if (n <= 1) return;
	int boundary;
	boundary = Partion(array,n);
	Quick_soft(array, boundary);
	Quick_soft(array + boundary + 1, n - boundary - 1);
}

//插入排序
void Insert_sort(int array[], int n) {
	int i, j;
	int temp;
	for (i = 0; i < n; i++) {
		temp = array[i];
		for (j = i - 1; j >= 0 && array[j] > temp; j--) {
			array[j + 1] = array[j];
		}
		array[j + 1] = temp;
	}
}
//测试
int main() {
	int a[] = {111,33,448,7,5426,2,43243,1434,3 };
	int n;
	n = sizeof(a) / sizeof(int);
	Merge_Sort(a, n);
	for (int i = 0; i < n; i++) {
		printf("%d\t", a[i]);
	}
	while (1);
}