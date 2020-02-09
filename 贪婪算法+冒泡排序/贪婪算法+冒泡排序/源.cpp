#include<stdio.h>

int weight[3] = { 10,20,30 };
int value[3] = { 50,90,120 };
double average[3] = { 0 };

int main() {
	int i;
	int m, n,temp;
	int bag = 30;
	int p=0;
	int bagvalue = 0;
	for (i = 0; i < 3; i++) { average[i] = (double)value[i] / (double)weight[i]; }
	for (m = 0; m < 2; m++)//冒泡算法，把最小的冒泡到最后
	{
		for (n = 0; n < 2 - m; n++) {
			if (average[n] < average[n + 1]) {
				temp = average[n];
				average[n] = average[n + 1];
				average[n + 1] = temp;
				temp = weight[n];
				weight[n] = weight[n + 1];
				weight[n + 1] = temp;
				temp = value[n];
				value[n] = value[n + 1];
				value[n + 1] = temp;
			}
		}
	}

	while (p <= 2) //寻找局部最优解
	{
		if (bag >= weight[p]) {
			bagvalue += weight[p] * average[p];
			bag -= weight[p];
			printf("%f 元/kg\n", average[p]);
			printf("剩余%d kg\n", bag);
			printf("%d 元\n", bagvalue);
		}
		else {
			bagvalue += average[p] * bag;
			printf("%d 元\n", bagvalue);

			break;
		}
		p++;
	}
	while (1);
}