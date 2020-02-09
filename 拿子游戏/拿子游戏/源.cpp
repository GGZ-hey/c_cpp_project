#include<stdio.h>
#include<stdlib.h>

#define MaxTake 3
#define Nogoodmove -1

int InitialCoins;

typedef enum { Human, Computer }PlayerT;

//函数原型
static int Getcomputermove(int nCoins);
static int Findgoodmove(int nCoins);
static int IsBadposition(int nCoins);
static void Judegewinner(int nCoins,PlayerT whoseturn);
static int gethumantake(int nCoins);
int legal(int nTaken, int ncoins);

int main() {
	int nCoins, nTaken;
	PlayerT whoseturn;
	printf("欢迎来到拿子游戏\n");
	printf("在这个游戏中，你能一次拿1个，2个或3个硬币\n");
	printf("拿到最后一个硬币的人算输\n");
	printf("现在请输入你希望与电脑进行游戏的初始子数：");
	scanf_s("%d", &InitialCoins);
	nCoins = InitialCoins;
	printf("你先取:(输入1,2或3)");
	whoseturn = Human;
	while (nCoins > 1) {
		printf("还有%d个硬币\n", nCoins);
		switch (whoseturn) {
		case Human:
		{
			printf("到你，你要拿多少个\n");
		nTaken = gethumantake(nCoins);
		whoseturn = Computer;
		break;
		}
		case Computer: {
			nTaken = Getcomputermove(nCoins);
			printf("我会拿%d个硬币\n", nTaken);
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
		printf("你选的数量非法，请选择从1到%d的硬币数\n", limit);
		printf("现在有%d个硬币\n", nCoins);
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
		case Human:printf("我拿了最后几个硬币，我输了\n"); break;
		case Computer:printf("你拿了最后几个硬币，你输了\n"); break;
		}
		
	}
	if (nCoins == 1) {
		switch (whoseturn) {
		case Human:printf("只剩一个硬币了，你输了\n"); break;
		case Computer:printf("我拿了最后一个硬币，我输了\n"); break;
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