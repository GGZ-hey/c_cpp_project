#include <stdio.h>
#include <stdlib.h>
int m[8][8] = {0};  //表示棋盘，初始为0，表示未放置皇后 
int num = 0;  //解数目

//对于棋盘前row-1行已放置好皇后
//检查在第row行、第column列放置一枚皇后是否可行
//因为在c 语言中并没有办法直接调用 bool 函数 所以我们用 0 和 1 代替 false 和 true
int check(int row,int column)
{ 
    if(row==1){
		return 1;
    } 
    int i,j; 
    
	//纵向只能有一枚"皇后"
	for(i=0;i<=row-2;i++){ 
        if(m[i][column-1]==1){
			return 0; 
        }
	}
	
	
    //左上至右下只能有一枚"皇后" 
	i = row-2; 
	j = i-(row-column);
	while(i>=0&&j>=0){
        if(m[i][j]==1){ 
			return 0;
        }
		i--;
		j--;
	}

	//右上至左下只能有一枚"皇后"
	i = row-2;
	j = row+column-i-2;
	while(i>=0&&j<=7){ 
        if(m[i][j]==1){ 
			return 0;
        }
		i--; 
		j++;
	}
	return 1;
}

//当已放置8枚皇后，为可行解时，输出棋盘
void output()
{ 
    int i,j; 
    num++;
	printf("answer %d:\n",num); 
	for(i=0;i<8;i++){ 
        for(j=0;j<8;j++){ 
			printf("%d ",m[i][j]);
        }
		printf("\n"); 
	}
} 

//采用递归函数实现八皇后回溯算法
//该函数求解当棋盘前row-1行已放置好皇后，在第row行放置皇后
//注意，此处row的取值为1~8
void solve(int row)
{ 
    
    //请在此填写你的递归算法
    
}

//主函数
int main()
{
	//求解八皇后问题
    solve(1);
    system("pause");
	return 0; 
}
