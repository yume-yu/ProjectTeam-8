#include <stdio.h>

#define WIDTH 50
#define HEIGHT 25
#define MAIN_FLAME_WIDTH_OFFSET 1
#define MAIN_FLAME_HEIGHT_OFFSET 1

#include "termcoor.h"
#include "flame.h"

int main(){
	//ターミナルの文字を流してカーソル位置を(0,0)にする
	init_term();
	//大枠ウィンドウフレームの作成
 	make_flame(WIDTH,HEIGHT,MAIN_FLAME_WIDTH_OFFSET,MAIN_FLAME_HEIGHT_OFFSET);

	//テスト呼び出し
	make_flame(20,5,15,7);
}
