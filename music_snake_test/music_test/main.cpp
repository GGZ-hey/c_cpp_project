#include <iostream>
#include "play.h"
#include "music.h"

using namespace std;
int main()
{
	int sel;

	while (1)
	{
		cout << "请选择功能：1-弹奏 2-播放 0-退出" << endl;
		cin >> sel;
		switch (sel)
		{
		case 0:
			return 0;
		case 1:
			play();
			break;
		case 2:
			music();
			break;
		default:
			cout << "输入错误" << endl;
			break;
		}
		cout << endl<<endl;
	}
}