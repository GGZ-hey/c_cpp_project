#include "graphics.h"
#include <conio.h>
void main() //»­Ô²
{
	int driver, mode;
	driver = VGA; mode = VGAHI;
	initgraph(&driver, &mode, "");
	rectangle(12, 100, 100, 13);
	circle(100, 100, 50);
	line(100, 50, 1000, 1000);
	_getch();
	closegraph();
}