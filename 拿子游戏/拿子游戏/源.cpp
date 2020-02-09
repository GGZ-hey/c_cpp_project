#include<stdio.h>
#include<stdlib.h>

#define MaxTake 3
#define Nogoodmove -1

int InitialCoins;

typedef enum { Human, Computer }PlayerT;

//����ԭ��
static int Getcomputermove(int nCoins);
static int Findgoodmove(int nCoins);
static int IsBadposition(int nCoins);
static void Judegewinner(int nCoins,PlayerT whoseturn);
static int gethumantake(int nCoins);
int legal(int nTaken, int ncoins);

int main() {
	int nCoins, nTaken;
	PlayerT whoseturn;
	printf("��ӭ����������Ϸ\n");
	printf("�������Ϸ�У�����һ����1����2����3��Ӳ��\n");
	printf("�õ����һ��Ӳ�ҵ�������\n");
	printf("������������ϣ������Խ�����Ϸ�ĳ�ʼ������");
	scanf_s("%d", &InitialCoins);
	nCoins = InitialCoins;
	printf("����ȡ:(����1,2��3)");
	whoseturn = Human;
	while (nCoins > 1) {
		printf("����%d��Ӳ��\n", nCoins);
		switch (whoseturn) {
		case Human:
		{
			printf("���㣬��Ҫ�ö��ٸ�\n");
		nTaken = gethumantake(nCoins);
		whoseturn = Computer;
		break;
		}
		case Computer: {
			nTaken = Getcomputermove(nCoins);
			printf("�һ���%d��Ӳ��\n", nTaken);
			whoseturn = Human;
			break;
		}
		}
		nCoins -= nTaken;
	}
	Judegewinner(nCoins, whoseturn);
}

int gethumantake(int nCoins) {
	int nTaken=0, limit;
	while (1) {
		scanf_s("%d", &nTaken);
		if (legal(nTaken, nCoins))  break;
		limit = (nCoins < MaxTake) ? nCoins : MaxTake;
		printf("��ѡ�������Ƿ�����ѡ���1��%d��Ӳ����\n", limit);
		printf("������%d��Ӳ��\n", nCoins);
	}
	return(nTaken);
}

int legal(int nTaken, int ncoins) {
	if (nTaken <= 0 || nTaken > 3 || nTaken > ncoins) return(0);
	return(1);
}

void Judegewinner(int nCoins, PlayerT whoseturn) {
	if (nCoins == 0) {
		switch (whoseturn) {
		case Human:printf("��������󼸸�Ӳ�ң�������\n"); break;
		case Computer:printf("��������󼸸�Ӳ�ң�������\n"); break;
		}
		
	}
	if (nCoins == 1) {
		switch (whoseturn) {
		case Human:printf("ֻʣһ��Ӳ���ˣ�������\n"); break;
		case Computer:printf("���������һ��Ӳ�ң�������\n"); break;
		}
	}
}

int Getcomputermove(int nCoins) {
	int nTaken;
	nTaken = Findgoodmove(nCoins);
	if (nTaken == Nogoodmove) {
		while (1) {
			nTaken = 1 + rand() % 3;
			if (legal(nTaken, nCoins))  break;
		}
	}
	return(nTaken);
}

int Findgoodmove(int nCoins) {
	int nTaken;
	for (nTaken = 1; nTaken <= MaxTake; nTaken++) {
		if (IsBadposition(nCoins - nTaken)) return(nTaken);
	}
	return (Nogoodmove);
}

int IsBadposition(int nCoins) {
	if (nCoins == 1) return(1);
	else {
		return(Findgoodmove(nCoins) == Nogoodmove)
			;
	}
}