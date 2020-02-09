#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main()
{
	int a[10]; // 存储结果。
	int i, j;

	srand(time(NULL));//通过获取时间值来设定随机数种子，以保证每次运行结果不同。
	for (i = 0; i < 10; )//注意，第三项留空，因为需要判断每次得到的数值是否重复，如重复则不进行i的自加
	{
		a[i] = rand() % 100; //得到一个0-99中的随机数。
		for (j = 0; j < i; j++)
			if (a[j] == a[i])break;//发现重复，结束内循环

		if (j == i) i++;//如果i和j相等，代表内循环是达到条件退出的，即不是通过break,也就是没有重复项。
	}

	for (i = 0; i < 10; i++) //输出得到的数值。
		printf("%d,", a[i]);
	printf("\n");

	return 0;
}