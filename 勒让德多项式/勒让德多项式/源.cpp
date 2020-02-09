#include<iostream>
using namespace std;

double lerangP(double n, double x);

int main() {
	double n, x;
	int result;
	cout << "本程序计算勒让德多项式，请输入相应的n,x"<<endl;
	cout << "n=";
	cin >> n;
	cout << "x=";
	cin >> x;
	result = lerangP(n, x);
	cout << "结果为:" << result;
}

double lerangP(double n, double x) {
	if (n == 0) {
		return(1);
	}
	else if (n == 1) return(x);
	else return((2 * n - 1)*lerangP(n - 1, x) - (n - 1)*lerangP(n - 2, x)) / n;
}