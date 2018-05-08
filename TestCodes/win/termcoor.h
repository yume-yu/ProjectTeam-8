/**
  * Writtenby yume_yu
  * windowsのapiを使ってカーソルの位置を指定箇所へ移動する関数を定義したヘッダ
  */
 
#include <windows.h>

/** 
  * 左上を(1,1)としてカーソルを指定位置へ移動させる関数
  * x カーソルのx座標
  * y カーソルのy座標
  */
int mvcur(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}
