#include<stdio.h>
#include<easyx.h>
#include<math.h>
#include<graphics.h>

#define pi 3.1415926535

static void DrawPolarLine(double r, double theta) {
	double radians;

	radians = theta / 180 * pi;
	linerel(r*cos(radians), r*sin(radians));
}

static void DrawFractalLine(double len, double theta, int order) {
	if (order == 0) {
		DrawPolarLine(len, theta);
	}
	else {
		DrawFractalLine(len / 3, theta, order - 1);
		DrawFractalLine(len / 3, theta - 60, order - 1);
		DrawFractalLine(len / 3, theta + 60, order - 1);
		DrawFractalLine(len / 3, theta, order - 1);
	}
}

void KochFractal(double size, int order) {
	double xo, yo;
	xo = getwidth() / 2 - size / 2;
	yo = getheight() / 2 - sqrt(3)*size / 6;
	moveto(xo, yo);
	DrawFractalLine(size, 0, order);
	DrawFractalLine(size, 120, order);
	DrawFractalLine(size, 240, order);
}

int main() {
	double size;
	int order;

	printf("请输入雪花边长度:");
	scanf_s("%lf", &size);
	printf("请输入雪花级数:");
	scanf_s("%d", &order);
	initgraph(1000, 680);
	setlinecolor(LIGHTMAGENTA);
	KochFractal(size, order);
	while (1);

}