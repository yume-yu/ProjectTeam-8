#include <stdio.h>
//randのためにインクルード
#include <stdlib.h>
#include <time.h>

//unixでkbhitを使うためのヘッダ
#include "mconio.h"
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
#define STAR_AMOUNT 50

long get_rand(){
	return rand();
}

void stars(int x[],int y[],int amount){
	for(int i = 0; i < 10; i++){
		for(int j = 0;j < amount; j++){
			print_line("+",x[j],y[j]);
		}
		fflush(stdout);
		usleep(1 * 100000);
		for(int j = 0;j < amount; j++){
			print_line("*",x[j],y[j]);
		}
		fflush(stdout);
		usleep(1 * 100000);
		for(int j = 0;j < amount; j++){
			print_line(" ",x[j],y[j]);
		}
		fflush(stdout);
		usleep(1);
	}
}

int main(){
	//ターミナルの文字を流してカーソル位置を(1,1)にする
	init_term();
	//大枠ウィンドウフレームの作成
	make_flame(WIDTH,HEIGHT,MAIN_FLAME_X_OFFSET,MAIN_FLAME_Y_OFFSET);

	char title[][100] = {
		{"╔╦╗┬ ┬┌─┐                       "},                
		{" ║ ├─┤├┤                        "},                 
		{" ╩ ┴ ┴└─┘                       "},                
		{"   ╔╗ ┌─┐┌─┐┬ ┬┌┬┐┬┌─┐┬ ┬┬      "},
		{"   ╠╩╗├┤ ├─┤│ │ │ │├┤ │ ││      "},  
		{"   ╚═╝└─┘┴ ┴└─┘ ┴ ┴└  └─┘┴─┘    "},
		{"                 ┬ ┬┌─┐┬─┐┬  ┌┬┐"},
		{"                 ││││ │├┬┘│   ││"},
		{"                 └┴┘└─┘┴└─┴─┘─┴┘"}
	};
	char title_space[][100] = {
		{"                         "},
		{"                         "},
		{"                         "},
		{"                         "},
		{"                         "},
		{"                         "},
		{"                         "},
		{"                         "},
		{"                         "},
	};

	for(int i = 0; i < 9; i++){
		for(int j = 0; j < i; j++){
			print_line(title[8 - j],15,i - j + 1);
		}
		fflush(stdout);
		usleep(0.2 * 1000000);
		print_lines(title_space,15,2,9);
	}
	print_lines(title,15,2,9);
	fflush(stdout);
	usleep(0.2 * 1000000);

	print_lines(title_space,15,2,9);
	print_lines(title,15,3,9);
	fflush(stdout);
	usleep(0.2 * 1000000);

	print_lines(title_space,15,3,9);
	print_lines(title,15,4,9);
	fflush(stdout);
	usleep(0.2 * 1000000);

	print_lines(title_space,15,4,9);
	print_lines(title,15,5,9);
	print_line("Press Enter",25,HEIGHT - 4);
	fflush(stdout);
	//星の描画
	int star_x[STAR_AMOUNT];// ={10,15,20};
	int star_y[STAR_AMOUNT];// ={20,15,10}; 
	srand(time(NULL));
	int numtmp;
	for(int i = 0; i< STAR_AMOUNT;i++){
		star_x[i] = get_rand() % (WIDTH - 2) + 2;
		star_y[i] = get_rand() % (HEIGHT - 2) + 2;
		if(star_y[i] >= 5 && star_y[i] < 14){
			if(star_x[i] >= 15 && star_x[i] <= 46){
				mvcur(1,HEIGHT+1);
				//printf("false:(%d,%d)",star_x[i],star_y[i]);
				i--;
			}
		}else if(star_y[i] >= HEIGHT - 5 && star_y[i] <= HEIGHT - 3){
			if(star_x[i] >= 24 && star_x[i] <= 37){
				i--;
			}
		}
	}
	while(1){
		stars(star_x,star_y,STAR_AMOUNT);
	}
}
