#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stddef.h>
#include <conio.h>

int random_number_2_4();//随机出2和4
int* random_number_16(int* p);//确定随机的格子，返回指针。

int main()
{
	int end = 0;
	long long mark = 0;//总分
	int i, j;
	int c = 0;//判误参数
	char key;//键盘输入
	int line, colum;
	int temp1;//临时数组下标
	int temp[4] = { 0 };
	int* blank = NULL;//指向空格子的指针
	int interface[4][4] = { 0 };//界面二维数组。

	blank = random_number_16(&interface[0][0]);//开始出现的两个。
	*blank = random_number_2_4();
	blank = random_number_16(&interface[0][0]);
	*blank = random_number_2_4();



	while (1)   //循环现实界面
	{

		system("cls");//清屏
		for (i = 0; i<4; i++)
		{
			for (j = 0; j<4; j++)
			{
				if (interface[i][j] == 0)
					printf("%c\t", '-');
				else
					printf("%d\t", interface[i][j]);
			}
			printf("\n\n");
		}printf("\n");


		printf("\tMark=%lld\t", mark);//显示参数
		printf("\n\n|*   上是w，下是s，左是a，右是d  *|\n\n\n|*    阿杜亲编，欢迎扩散~   *|\n\n");


		/*输入是否合法*/
	cannot://错误则返回的地方。
		c = 0;
		do//错误就循环输入
		{
			key = _getch();
		} while (key != 'w' && key != 's' && key != 'a' && key != 'd');

		/*上下左右都是一个原理，所以这里只介绍“上”——“w”*/

		switch (key)
		{
		case 'w':
		{
			/*判断是否符合移动条件*/
			for (colum = 0; colum<4; colum++)
				for (line = 3; line>0; line--)
				{
					if ((interface[line][colum] != 0 && interface[line - 1][colum] == 0) || (interface[line][colum] == interface[line - 1][colum]))
					{
						c++; break;
					}
				}


			if (c == 0)
			{
				goto cannot;//不能移动就回去再输入
			}


			/*判断是否有空位置，有则补上。*/
			//基本思想是通过把一行或者一列非零的赋值给临时全为0的一维数组，再把一维数组赋值回去。

			for (temp1 = 0; temp1<4; temp1++)//清空临时数组
				temp[temp1] = 0;
			for (colum = 0; colum<4; colum++)//先把一列赋值给一个一维数组
			{
				for (line = 0, temp1 = 0; line<4; line++)
				{
					if (interface[line][colum])
					{
						temp[temp1] = interface[line][colum];
						temp1++;
					}
				}

				for (line = 0, temp1 = 0; line<4; line++, temp1++)//再把数组赋值回去
					interface[line][colum] = temp[temp1];

				for (temp1 = 0; temp1<4; temp1++)//清空临时数组
					temp[temp1] = 0;
			}

			/*先判断相邻的是否相等，然后相加。*/
			for (colum = 0; colum<4; colum++)
				for (line = 0; line<3; line++)
				{
					if (interface[line][colum] == interface[line + 1][colum])
					{
						interface[line][colum] += interface[line + 1][colum];
						mark += interface[line][colum];
						interface[line + 1][colum] = 0;
					}
				}
			/*再判断是否有空位置，有则补上。*/
			//基本思想是通过把一行或者一列非零的赋值给临时全为0的一维数组，再把一维数组赋值回去。

			for (temp1 = 0; temp1<4; temp1++)//清空临时数组
				temp[temp1] = 0;

			for (colum = 0; colum<4; colum++)//先把一列赋值给一个一维数组
			{
				for (line = 0, temp1 = 0; line<4; line++)
				{
					if (interface[line][colum])
					{
						temp[temp1] = interface[line][colum];
						temp1++;
					}
				}

				for (line = 0, temp1 = 0; line<4; line++, temp1++)//再把数组赋值回去
					interface[line][colum] = temp[temp1];

				for (temp1 = 0; temp1<4; temp1++)//清空临时数组
					temp[temp1] = 0;
			}


		}break;
		case 's':
		{
			for (colum = 0; colum<4; colum++)
				for (line = 0; line<3; line++)
				{
					if ((interface[line][colum] != 0 && interface[line + 1][colum] == 0) || (interface[line][colum] == interface[line + 1][colum]))
					{
						c++; break;
					}
				}
			if (c == 0)
			{
				goto cannot;
			}



			for (temp1 = 0; temp1<4; temp1++)
				temp[temp1] = 0;
			for (colum = 0; colum<4; colum++)
			{
				for (line = 3, temp1 = 3; line >= 0; line--)
				{
					if (interface[line][colum])
					{
						temp[temp1] = interface[line][colum];
						temp1--;
					}
				}

				for (line = 0, temp1 = 0; line<4; line++, temp1++)
					interface[line][colum] = temp[temp1];

				for (temp1 = 0; temp1<4; temp1++)
					temp[temp1] = 0;
			}


			for (colum = 0; colum<4; colum++)
				for (line = 3; line>0; line--)
				{
					if (interface[line][colum] == interface[line - 1][colum])
					{
						interface[line][colum] += interface[line - 1][colum];
						mark += interface[line][colum];
						interface[line - 1][colum] = 0;
					}
				}


			for (temp1 = 0; temp1<4; temp1++)
				temp[temp1] = 0;
			for (colum = 0; colum<4; colum++)
			{
				for (line = 3, temp1 = 3; line >= 0; line--)
				{
					if (interface[line][colum])
					{
						temp[temp1] = interface[line][colum];
						temp1--;
					}
				}

				for (line = 0, temp1 = 0; line<4; line++, temp1++)
					interface[line][colum] = temp[temp1];

				for (temp1 = 0; temp1<4; temp1++)
					temp[temp1] = 0;
			}


		}break;
		case 'a':
		{

			for (line = 0; line<4; line++)
				for (colum = 3; colum>0; colum--)
				{
					if ((interface[line][colum] != 0 && interface[line][colum - 1] == 0) || (interface[line][colum] == interface[line][colum - 1]))
					{
						c++; break;
					}
				}
			if (c == 0)
			{
				goto cannot;
			}



			for (temp1 = 0; temp1<4; temp1++)
				temp[temp1] = 0;
			for (line = 0; line<4; line++)
			{
				for (colum = 0, temp1 = 0; colum<4; colum++)
				{
					if (interface[line][colum])
					{
						temp[temp1] = interface[line][colum];
						temp1++;
					}
				}

				for (colum = 0, temp1 = 0; colum<4; colum++, temp1++)
					interface[line][colum] = temp[temp1];

				for (temp1 = 0; temp1<4; temp1++)
					temp[temp1] = 0;
			}


			for (line = 0; line<4; line++)
				for (colum = 0; colum<3; colum++)
				{
					if (interface[line][colum] == interface[line][colum + 1])
					{
						interface[line][colum] += interface[line][colum + 1];
						mark += interface[line][colum];
						interface[line][colum + 1] = 0;
					}
				}

			for (temp1 = 0; temp1<4; temp1++)
				temp[temp1] = 0;

			for (line = 0; line<4; line++)
			{
				for (colum = 0, temp1 = 0; colum<4; colum++)
				{
					if (interface[line][colum])
					{
						temp[temp1] = interface[line][colum];
						temp1++;
					}
				}

				for (colum = 0, temp1 = 0; colum<4; colum++, temp1++)
					interface[line][colum] = temp[temp1];

				for (temp1 = 0; temp1<4; temp1++)
					temp[temp1] = 0;
			}


		}break;
		case 'd':
		{

			for (line = 0; line<4; line++)
				for (colum = 0; colum<3; colum++)
				{
					if ((interface[line][colum] != 0 && interface[line][colum + 1] == 0) || (interface[line][colum] == interface[line][colum + 1]))
					{
						c++; break;
					}
				}
			if (c == 0)
			{
				goto cannot;
			}




			for (temp1 = 0; temp1<4; temp1++)
				temp[temp1] = 0;
			for (line = 0; line<4; line++)
			{
				for (colum = 3, temp1 = 3; colum >= 0; colum--)
				{
					if (interface[line][colum])
					{
						temp[temp1] = interface[line][colum];
						temp1--;
					}
				}

				for (colum = 0, temp1 = 0; colum<4; colum++, temp1++)
					interface[line][colum] = temp[temp1];

				for (temp1 = 0; temp1<4; temp1++)
					temp[temp1] = 0;
			}


			for (line = 0; line<4; line++)
				for (colum = 3; colum>0; colum--)
				{
					if (interface[line][colum] == interface[line][colum - 1])
					{
						interface[line][colum] += interface[line][colum - 1];
						mark += interface[line][colum];
						interface[line][colum - 1] = 0;
					}
				}

			for (temp1 = 0; temp1<4; temp1++)
				temp[temp1] = 0;
			for (line = 0; line<4; line++)
			{
				for (colum = 3, temp1 = 3; colum >= 0; colum--)
				{
					if (interface[line][colum])
					{
						temp[temp1] = interface[line][colum];
						temp1--;
					}
				}

				for (colum = 0, temp1 = 0; colum<4; colum++, temp1++)
					interface[line][colum] = temp[temp1];

				for (temp1 = 0; temp1<4; temp1++)
					temp[temp1] = 0;
			}


		}break;
		}


		blank = random_number_16(&interface[0][0]);//随机给出一个数
		*blank = random_number_2_4();

		/*判断是不是已经挂了= =*/

		for (colum = 0; colum<4; colum++)
			for (line = 3; line>0; line--)
			{
				if (((interface[line][colum] != 0 && interface[line - 1][colum] == 0) || (interface[line][colum] == interface[line - 1][colum])))
					end++;
			}

		for (colum = 0; colum<4; colum++)
			for (line = 0; line<3; line++)
			{
				if (((interface[line][colum] != 0 && interface[line + 1][colum] == 0) || (interface[line][colum] == interface[line + 1][colum])))
					end++;
			}
		for (line = 0; line<4; line++)
			for (colum = 3; colum>0; colum--)
			{
				if (((interface[line][colum] != 0 && interface[line][colum - 1] == 0) || (interface[line][colum] == interface[line][colum - 1])))
					end++;
			}
		for (line = 0; line<4; line++)
			for (colum = 0; colum<3; colum++)
			{
				if (((interface[line][colum] != 0 && interface[line][colum + 1] == 0) || (interface[line][colum] == interface[line][colum + 1])))
					end++;
			}


		if (end == 0)
			break;

		end = 0;//重置end

				/*显示最后结果*/
	}


	system("cls");//清屏
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			if (interface[i][j] == 0)
				printf("%c\t", '=');
			else
				printf("%d\t", interface[i][j]);
		}
		printf("\n\n");
	}printf("\n");


	printf("\tMark=%lld\t", mark);//显示参数
	printf("\n\n|*   上是w，下是s，左是a，右是d  *|\n\n\n|*    阿杜亲编，欢迎扩散~   *|\n\n");
	printf("\tGame Over！T_T");
	while (1);
	return 0;

}







/*以下为子函数*/

int random_number_2_4()//随机出2和4
{
	int a, b;
	srand(time(0));
	a = rand() % 2;
	b = 2 * (a + 1);
	return b;
}


int* random_number_16(int* p)//确定随机的格子，返回指针。
{
	int k;
	int *judge[16];
	for (k = 0; k<16; k++)
	{
		judge[k] = NULL;//存放界面指针的函数。初始化数组
	}
	int i, j;
	for (i = 0, j = 0; i<16; i++)//存放指针
	{
		if (*(p + i) == 0)
		{
			judge[j] = p + i;
			j++;
		}
	}
	srand(time(0));//确定位置
	int L;
	L = rand() % j;

	return (judge[L]);
}