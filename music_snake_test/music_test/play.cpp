#include "play.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

//const int pitch[] = { 262, 294, 330, 349, 392, 440, 494 };//中度音
const int pitch[] = { 523, 587, 659, 698, 784, 880, 988 };//高度音

void play_s(char ch)
{
	Beep(pitch[ch - '1'], LEN);
	putch(ch);
}

void play(void)
{
	char ch;
	cout << "1-7代别各个音符,0-退出"<<endl;
	while (1)
	{
		ch = getch();
		if (ch >= '1' && ch <= '7')
		{
			play_s(ch);
		}
		else if (ch == '0')
			return;
	}
}