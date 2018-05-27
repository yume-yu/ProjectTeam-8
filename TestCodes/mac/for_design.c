#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/** 
 * メインフレーム(大枠)関連定数
 * WIDTH          メインフレームの幅
 * HEIGHT         メインフレームの高さ
 * MAIN_FLAME_X   メインフレームの開始位置のX座標
 * MAIN_FLAME_Y   メインフレームの開始位置のY座標
 */
#define WIDTH					60
#define HEIGHT 				25
#define MAIN_FLAME_X	1
#define MAIN_FLAME_Y 	1

/*
 * 汎用関数を定義したヘッダ
 * 必ずメインフレームサイズ定義の後ろでincludeすること
 */
#include "for_make_game.h"

int main(){
	//ターミナルの文字を流してカーソル位置を(1,1)にする
	init_term();
	//大枠ウィンドウフレームの作成
	make_flame(WIDTH,HEIGHT,MAIN_FLAME_X,MAIN_FLAME_Y);
	//出力する問題
	char strings[][100] = {
		"ここに",
		"もじをうつと",
		"しゅつりょくします",
		" ",
		" ",
		" ",
		" ",
		"qwertyuiop"
	};

	/*
	文字を出力するところ
	print_lines(strings,MAIN_FLAME_X,MAIN_FLAME_Y,上の配列の行数);
	*/
	print_lines(strings,MAIN_FLAME_X + 1,MAIN_FLAME_Y + 1,8);

	//なにか入力を待つ
	wait_anyinput();
}
