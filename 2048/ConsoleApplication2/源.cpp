#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stddef.h>
#include <conio.h>

int random_number_2_4();//�����2��4
int* random_number_16(int* p);//ȷ������ĸ��ӣ�����ָ�롣

int main()
{
	int end = 0;
	long long mark = 0;//�ܷ�
	int i, j;
	int c = 0;//�������
	char key;//��������
	int line, colum;
	int temp1;//��ʱ�����±�
	int temp[4] = { 0 };
	int* blank = NULL;//ָ��ո��ӵ�ָ��
	int interface[4][4] = { 0 };//�����ά���顣

	blank = random_number_16(&interface[0][0]);//��ʼ���ֵ�������
	*blank = random_number_2_4();
	blank = random_number_16(&interface[0][0]);
	*blank = random_number_2_4();



	while (1)   //ѭ����ʵ����
	{

		system("cls");//����
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


		printf("\tMark=%lld\t", mark);//��ʾ����
		printf("\n\n|*   ����w������s������a������d  *|\n\n\n|*    �����ױ࣬��ӭ��ɢ~   *|\n\n");


		/*�����Ƿ�Ϸ�*/
	cannot://�����򷵻صĵط���
		c = 0;
		do//�����ѭ������
		{
			key = _getch();
		} while (key != 'w' && key != 's' && key != 'a' && key != 'd');

		/*�������Ҷ���һ��ԭ����������ֻ���ܡ��ϡ�������w��*/

		switch (key)
		{
		case 'w':
		{
			/*�ж��Ƿ�����ƶ�����*/
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
				goto cannot;//�����ƶ��ͻ�ȥ������
			}


			/*�ж��Ƿ��п�λ�ã������ϡ�*/
			//����˼����ͨ����һ�л���һ�з���ĸ�ֵ����ʱȫΪ0��һά���飬�ٰ�һά���鸳ֵ��ȥ��

			for (temp1 = 0; temp1<4; temp1++)//�����ʱ����
				temp[temp1] = 0;
			for (colum = 0; colum<4; colum++)//�Ȱ�һ�и�ֵ��һ��һά����
			{
				for (line = 0, temp1 = 0; line<4; line++)
				{
					if (interface[line][colum])
					{
						temp[temp1] = interface[line][colum];
						temp1++;
					}
				}

				for (line = 0, temp1 = 0; line<4; line++, temp1++)//�ٰ����鸳ֵ��ȥ
					interface[line][colum] = temp[temp1];

				for (temp1 = 0; temp1<4; temp1++)//�����ʱ����
					temp[temp1] = 0;
			}

			/*���ж����ڵ��Ƿ���ȣ�Ȼ����ӡ�*/
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
			/*���ж��Ƿ��п�λ�ã������ϡ�*/
			//����˼����ͨ����һ�л���һ�з���ĸ�ֵ����ʱȫΪ0��һά���飬�ٰ�һά���鸳ֵ��ȥ��

			for (temp1 = 0; temp1<4; temp1++)//�����ʱ����
				temp[temp1] = 0;

			for (colum = 0; colum<4; colum++)//�Ȱ�һ�и�ֵ��һ��һά����
			{
				for (line = 0, temp1 = 0; line<4; line++)
				{
					if (interface[line][colum])
					{
						temp[temp1] = interface[line][colum];
						temp1++;
					}
				}

				for (line = 0, temp1 = 0; line<4; line++, temp1++)//�ٰ����鸳ֵ��ȥ
					interface[line][colum] = temp[temp1];

				for (temp1 = 0; temp1<4; temp1++)//�����ʱ����
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


		blank = random_number_16(&interface[0][0]);//�������һ����
		*blank = random_number_2_4();

		/*�ж��ǲ����Ѿ�����= =*/

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

		end = 0;//����end

				/*��ʾ�����*/
	}


	system("cls");//����
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


	printf("\tMark=%lld\t", mark);//��ʾ����
	printf("\n\n|*   ����w������s������a������d  *|\n\n\n|*    �����ױ࣬��ӭ��ɢ~   *|\n\n");
	printf("\tGame Over��T_T");
	while (1);
	return 0;

}







/*����Ϊ�Ӻ���*/

int random_number_2_4()//�����2��4
{
	int a, b;
	srand(time(0));
	a = rand() % 2;
	b = 2 * (a + 1);
	return b;
}


int* random_number_16(int* p)//ȷ������ĸ��ӣ�����ָ�롣
{
	int k;
	int *judge[16];
	for (k = 0; k<16; k++)
	{
		judge[k] = NULL;//��Ž���ָ��ĺ�������ʼ������
	}
	int i, j;
	for (i = 0, j = 0; i<16; i++)//���ָ��
	{
		if (*(p + i) == 0)
		{
			judge[j] = p + i;
			j++;
		}
	}
	srand(time(0));//ȷ��λ��
	int L;
	L = rand() % j;

	return (judge[L]);
}