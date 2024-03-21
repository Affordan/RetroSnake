#include "snkae.h"

int main()
{
	Snake mysnake;

	initgraph(width, height,EX_SHOWCONSOLE);	//SHOWCONSOLE显示控制台干什么？
	setbkcolor(Champagne);
	cleardevice();

	mysnake.creatSnake();

	//双缓冲->画面流畅
	BeginBatchDraw();
	while (1)
	{
		cleardevice();
		mysnake.DrawBK();
		mysnake.DrawSnak();
		
		
		mysnake.autoMove();
		//mysnake.disPlaySnakeCorrdinate();
	
		Sleep(200);
		FlushBatchDraw();
	}
	EndBatchDraw();


	_getch();
	closegraph();

	return 0;
}


