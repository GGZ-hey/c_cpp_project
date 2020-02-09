#include<iostream>
#include<cmath>
using namespace std;

typedef double fn(double);

const double Pi = 3.1415926535898;
const int MAX_devide = 60000;

double jifen(fn *fn, double down, double up);
fn fn1 ,fn2,fn3;


int main() {
	double sum1, sum2, sum3;
	sum1 = jifen(fn1, 0, 1);
	sum2 = jifen(fn2, 1, 2);
	sum3 = jifen(fn3, 0, (Pi / 2.0));
	cout << "本程序可计算某一元函数的积分" << endl;
	cout << "目前有三个函数,将计算他们的积分" << endl;
	cout << "fn1(x)=4/(1+x^2)在0到1上的积分" << endl;
	cout << "fn2(x)=√1+x^2在1到2上的积分" << endl;
	cout << "fn3(x)=sinx在0到PI/2上的积分" << endl;
	cout << "他们的结果分别为 ";
	cout << sum1 << "  " << "  " << sum2 << "  " << sum3<<endl;

}

double jifen(fn *fn, double down, double up) {
	double h;
	int n=MAX_devide;
	double T;
	double add=0;
	h = (double)(up - down) /(double) n;
	T = h*(fn(up) + fn(down)) / 2.0;
	for (n = 1; n < MAX_devide; n++) {
		add += fn(down + n*h);
	}
	T = T + h*add;
	return(T);
}

double fn1(double x) {
	return(4 / (1 + x*x));
}

double fn2(double x) {
	return(sqrt(1.0+x*x));
}

double fn3(double x) {
	return(sin(x));
}