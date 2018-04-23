#include <stdio.h>
#include "termcoor.h"

#define WIDTH 50
#define HEIGHT 25
#define MAIN_FLAME_WIDTH_OFFSET 1
#define MAIN_FLAME_HEIGHT_OFFSET 1

/** 
	* 標準出力の初期化
 	*/
void init_term(){
	//標準出力を流す
	printf("\033[2J");
	//カーソル位置を(1,1)に移動
	mvcur(1,1);
}

/**
	* フレームの作成関数
	* width    作成するフレームの幅
	* height   作成するフレームの高さ
	* offset_x 作成するフレームの開始位置のx座標
	* offset_y 作成するフレームの開始位置のy座標
	*/
void make_flame(int width, int height, int offset_x, int offset_y){
	int print_width = width - 2;
	int print_height = height - 2;
	//1行目の描画
	mvcur(offset_x,offset_y);
	printf("┌");
	for(int i = 0; i < print_width; i++){
		printf("─");
	}
	printf("┐");
	//中間部分の描画
	for(int i = 0; i < print_height; i++){
		mvcur(offset_x,offset_y + 1 + i);
		printf("│");
		for(int j = 0; j < print_width; j++){
			printf(" ");
		}
		printf("│\n");
	}

	//最終行部分の描画
	mvcur(offset_x,offset_y + height - 1);
	printf("└");
	for(int i = 0; i < print_width; i++){
		printf("─");
	}
	printf("┘\n");

	//カーソル位置の初期化
	mvcur(1,HEIGHT+1);
}

int main(){
	//ターミナルの文字を流してカーソル位置を(0,0)にする
	init_term();
	//大枠ウィンドウフレームの作成
 	make_flame(WIDTH,HEIGHT,MAIN_FLAME_WIDTH_OFFSET,MAIN_FLAME_HEIGHT_OFFSET);

	//テスト呼び出し
	make_flame(20,5,15,7);
}
