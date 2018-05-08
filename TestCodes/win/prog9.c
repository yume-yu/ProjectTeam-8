#include <stdio.h>
#include <conio.h>

#define WIDTH 60
#define HEIGHT 25
#define MAIN_FLAME_X_OFFSET 1
#define MAIN_FLAME_Y_OFFSET 1

#include "test.h"
#include "flame.h"
#include "pstring.h"

int main(){
	//ターミナルの文字を流してカーソル位置を(1,1)にする
	init_term();
	//大枠ウィンドウフレームの作成
 	make_flame(WIDTH,HEIGHT,MAIN_FLAME_X_OFFSET,MAIN_FLAME_Y_OFFSET);

	//テスト呼び出し
	/**
	  * フレームを作成する
	  * make_flame(幅,高さ,開始x座標,開始y座標)
	  */
	make_flame(3,8,5,7);
	
	/**
	  * 2分割フレームを作成する
	  * make_vsflame(幅,高さ,開始x座標,開始y座標,分割する位置のx座標)
	  */
	make_vsflame(40,5,3,20,5);
	
	
	/**
	  * 文字を1行出力する
	  * print_line(文字列,開始x座標,開始y座標)
	  */
	print_line("ほげほげげ",18,21);
	
	/**
	  * 文字を複数行出力する
	  * print_lines(文字列の配列,開始x座標,開始y座標,行数)
	  */
	char string[][100] = {"ほげ","ふが"};
	print_lines(string,5,21,2);
	while(!kbhit()){
	}
}
