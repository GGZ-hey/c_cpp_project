#include<stdio.h>
#include<stdlib.h>

#define winningPosition 1000
#define NeutralPosition 0
#define Losingposition (-winningPosition)


typedef enum{human,computer} PlayerT;

#define FirstPlayer computer

typedef int moveT;

typedef struct {
	char board[(3 * 3) + 1];
	PlayerT whoseturn;
	int Turnnum;
}STATE, *stateT;

#define Max_move 9

#define Max_depth 10000

static int Winning[][3] = {
	{1,2,3},
	{4,5,6},
	{7,8,9},
	{1,4,7},
	{2,5,8},
	{3,6,9},
	{1,5,9},
	{3,5,7}
};
static int nWinningposition = sizeof(Winning) / sizeof(Winning[0]);
void Init(stateT state);
int Game_over(stateT state);
moveT Gethumanmove(stateT state);
moveT GetConputermove(stateT state);
moveT FindGoodMove(stateT state,int depth,int *pRating);
int Evaluation(stateT state, int depth);
PlayerT Whoseturn(stateT state);
void DisplayMove(moveT move);
void JudgeWinner(stateT state);
void MakeMove(stateT state, moveT move);
int GenerateMoveList(stateT state, moveT moveArray[]);
void RetractMove(stateT state, moveT move);
int Evaluationstatic(stateT state);
int CheckforWin(stateT state, PlayerT player);
PlayerT Opponent(PlayerT player);
char Playermark(PlayerT player);
void Displaygame(stateT state);

int main() {
	stateT state;
	moveT move;
	state = (stateT)malloc(sizeof(STATE));

	Init(state);
	while (!Game_over(state)) {
		Displaygame(state);
			switch (Whoseturn (state)) {
		case human: {
			printf("你要走哪里\n");
			move = Gethumanmove(state);
			break;
		}
		case computer: {
			move = GetConputermove(state);
			DisplayMove(move);
			break;
		}
		}
		MakeMove(state, move);
	}
	JudgeWinner(state);
	while (1);
}

void Init(stateT state) {
	int i;
	for (i = 1; i <= 9; i++) {
		state->board[i] = ' ';
	}
	state->whoseturn = FirstPlayer;
	state->Turnnum = 0;
}

moveT GetConputermove(stateT state) {
	int pRating;
	printf("我的移动.\n");
	return(FindGoodMove(state, 0, &pRating));
}

moveT FindGoodMove(stateT state, int depth, int *pRating) {
	moveT nMoves, moveArray[Max_move],move,Bestmove;
	int i, rating, minRating;
	nMoves = GenerateMoveList(state, moveArray);
	if (nMoves == 0) { printf("没有可移动的了\n"); 
	exit(0);
	}
	minRating = winningPosition + 1;
	for (i = 0; i < nMoves && minRating!=Losingposition; i++) {
		move = moveArray[i];
		MakeMove(state, move);
		rating = Evaluation(state, depth + 1);
		if (rating < minRating) {
			Bestmove = move;
			minRating = rating;
		}
		RetractMove(state, move);
	}
	*pRating = -minRating;
	return(Bestmove);
}

int Evaluation(stateT state, int depth) {
	int rating;
	if (Game_over(state) || depth >= Max_depth) {
		return(Evaluationstatic(state));
	}
		(void)FindGoodMove(state, depth, &rating);
	
	return(rating);
}

int Evaluationstatic(stateT state) {
	if (CheckforWin(state, state->whoseturn)) {
		return (winningPosition);
	}
	if (CheckforWin(state, Opponent(state->whoseturn))) {
		return(Losingposition);
	}
	return(NeutralPosition);
}

PlayerT Opponent(PlayerT player) {
	switch (player) {
	case human:return(computer); break;
	case computer:return(human); break;
	}
}

PlayerT Whoseturn(stateT state) {
	return(state->whoseturn);
}

void MakeMove(stateT state, moveT move) {
	switch (Whoseturn(state)) {
	case human: {
		state->board[move] = 'x'; break;
	}
	case computer: {
		state->board[move] = 'o'; break;
	}
	}
	state->whoseturn = Opponent(state->whoseturn);
	state->Turnnum++;
}

void RetractMove(stateT state, moveT move) {
	state->board[move] = ' ';
	state->whoseturn = Opponent(state->whoseturn);
	state->Turnnum--;
}

int GenerateMoveList(stateT state, moveT moveArray[]) {
	int i;
	int nMoves = 0;
	for (i = 1; i <= 9; i++) {
		if (state->board[i] == ' ') {
			moveArray[nMoves] = (moveT)i;
			nMoves++;
			
		}
	}
	return(nMoves);
}

int CheckforWin(stateT state, PlayerT player) {
	int i;
	char mark;
	if (state->Turnnum < 5) { return(0); }
	mark = Playermark(player);
	for (i = 0; i <= nWinningposition; i++) {
		if (mark == state->board[Winning[i][0]] && mark == state->board[Winning[i][1]] && mark == state->board[Winning[i][2]]) {
			return(1);
		}
	}
	return(0);
}

char Playermark(PlayerT player) {
	switch (player) {
	case human:return('x'); break;
	case computer:return('o'); break;
	}
}

int Game_over(stateT state) {
	return(state->Turnnum == 9 || CheckforWin(state, state->whoseturn) || CheckforWin(state, Opponent(state->whoseturn)));
}

void DisplayMove(moveT move) {
	printf("我会走%d\n", move);
}

void Displaygame(stateT state) {
	int row, col;
	for (row = 0; row < 3; row++) {
		if (row != 0) printf("--+--+--\n");
		for (col = 0; col < 3; col++) {
			if (col != 0) printf(" |");
			printf("%c", state->board[row*3+col+1]);
		}
		printf("\n");
	}
	printf("\n");
}

moveT Gethumanmove(stateT state) {
	int row, col;
	int move;
	printf("你要走第几行\n");
	scanf_s("%d", &row);
	printf("你要走第几列\n");
	scanf_s("%d", &col);
	move = (row-1) * 3 + col ;
	if (state->board[move] != ' '||move>9||move<0) {
		while (1) {
			printf("你选的位置不行，请重新选择\n");
			printf("格式 行+回车+列");
			scanf_s("%d", &row);
			scanf_s("%d", &col);
			move = (row - 1) * 3 + col;
			if (state->board[move] == ' ' && move > 0 && move <= 9) break;
		}
	}
	return(move);
}

void JudgeWinner(stateT state) {
	if (state->Turnnum == 9) printf("平局\n");
	else if (CheckforWin(state, state->whoseturn) && state->whoseturn == human)  printf("You win!\n");
	else printf("I win!HAha");
		
	
}