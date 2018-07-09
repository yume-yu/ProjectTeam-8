#include "thebeautifulsky.h"
#ifdef WINDOWS

/**
 * Windowsにはマイクロ秒でsleepするusleep(int)がないので
 * time 処理を停止する時間[ms]
 */
void usleep(int time){
	Sleep(time/1000);
}

/**
 * 左上を(1,1)としてカーソルを指定位置へ移動させる関数
 * x カーソルのx座標
 * y カーソルのy座標
 */
void mvcur(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(
			GetStdHandle(STD_OUTPUT_HANDLE),
			coord
			);
}

#endif
