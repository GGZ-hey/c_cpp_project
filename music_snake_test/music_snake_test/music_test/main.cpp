#include <iostream>
#include "play.h"
#include "music.h"

using namespace std;
int main()
{
	int sel;

	while (1)
	{
		cout << "��ѡ���ܣ�1-���� 2-���� 0-�˳�" << endl;
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
			cout << "�������" << endl;
			break;
		}
		cout << endl<<endl;
	}
}