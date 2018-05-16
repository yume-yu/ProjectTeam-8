#include <stdio.h>
//randのためにインクルード
#include <stdlib.h>
#include <time.h>

#include <conio.h>
#define WIDTH 60
#define HEIGHT 25
#define MAIN_FLAME_X_OFFSET 1
#define MAIN_FLAME_Y_OFFSET 1

#include "termcoor.h"
#include "flame.h"
#include "pstring.h"

//文字パレット枠の大きさ/オフセットの定義
#define CHAR_FLAME_W 33
#define CHAR_FLAME_H 7
#define CHAR_FLAME_X_OFFSET 4 
#define CHAR_FLAME_Y_OFFSET 15

//星の数
#define STAR_AMOUNT 20

long get_rand(){
	return rand();
}

void stars(int x[],int y[],int amount){
	for(int i = 0; i < 10; i++){
		for(int j = 0;j < amount; j++){
			print_line("+",x[j],y[j]);
		}
		fflush(stdout);
		Sleep(2 * 100);
		for(int j = 0;j < amount; j++){
			print_line("*",x[j],y[j]);
		}
		fflush(stdout);
		Sleep(2 * 100);
		for(int j = 0;j < amount; j++){
			print_line(" ",x[j],y[j]);
		}
		fflush(stdout);
		Sleep(1);
	}
}

int main(){
	//ターミナルの文字を流してカーソル位置を(1,1)にする
	init_term();
	//大枠ウィンドウフレームの作成
	make_flame(WIDTH,HEIGHT,MAIN_FLAME_X_OFFSET,MAIN_FLAME_Y_OFFSET);

	char title[][100] = {
		{"The"},
		{"Beautiful"},
		{"World"}
	};
	char title_space[][100] = {
		{"                 "},
		{"                 "},
		{"                 "}
	};

	print_lines(title,20,3,3);
	fflush(stdout);
	Sleep(1 * 1000);

	print_lines(title_space,20,3,3);
	print_lines(title,20,4,3);
	fflush(stdout);
	Sleep(1 * 1000);

	print_lines(title_space,20,4,3);
	print_lines(title,20,5,3);
	fflush(stdout);
	Sleep(1 * 1000);

	print_lines(title_space,20,5,3);
	print_lines(title,20,6,3);
	fflush(stdout);
	Sleep(1 * 1000);
	
	int star_x[STAR_AMOUNT];// ={10,15,20};
	int star_y[STAR_AMOUNT];// ={20,15,10}; 
	srand(time(NULL));
	while(1){
		for(int i = 0; i< STAR_AMOUNT;i++){
			star_x[i] = get_rand() % (WIDTH - 2) + 2;
			star_y[i] = get_rand() % (HEIGHT - 2) + 2;
		}
		stars(star_x,star_y,STAR_AMOUNT);
	}
}
