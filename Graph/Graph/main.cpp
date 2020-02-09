#include"Graph.h"
#include<iostream>
using namespace std;
int main()
{
	GraphMatrix<char, int> G;
	Stack<char>* St;
	G.insert('a');
	G.insert('s');
	G.insert('d');
	G.insert('z');
	G.insert(1, 2, 0, 1);
	G.insert(1, 3, 1, 2);
	G.insert(1, 5, 1, 3);
	G.insert(1, 11, 3, 2);
	St=G.tSort(0);
	for (int i = 4 ; i > 0;i--)
	{
		cout << St->pop() <<"\n" ;
	}
	while (1);
}