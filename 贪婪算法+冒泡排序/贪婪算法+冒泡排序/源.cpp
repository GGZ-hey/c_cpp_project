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
	for (m = 0; m < 2; m++)//ð���㷨������С��ð�ݵ����
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

	while (p <= 2) //Ѱ�Ҿֲ����Ž�
	{
		if (bag >= weight[p]) {
			bagvalue += weight[p] * average[p];
			bag -= weight[p];
			printf("%f Ԫ/kg\n", average[p]);
			printf("ʣ��%d kg\n", bag);
			printf("%d Ԫ\n", bagvalue);
		}
		else {
			bagvalue += average[p] * bag;
			printf("%d Ԫ\n", bagvalue);

			break;
		}
		p++;
	}
	while (1);
}