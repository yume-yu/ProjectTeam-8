#include <stdio.h>
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


int main(){
	//ターミナルの文字を流してカーソル位置を(1,1)にする
	init_term();
	//大枠ウィンドウフレームの作成
 	make_flame(WIDTH,HEIGHT,MAIN_FLAME_X_OFFSET,MAIN_FLAME_Y_OFFSET);
	
	//入力フレームの描写
	make_flame(CHAR_FLAME_W,3,CHAR_FLAME_X_OFFSET,CHAR_FLAME_Y_OFFSET - 3);	
	char input_string[] = "_";
	print_line(input_string,CHAR_FLAME_X_OFFSET + 2,CHAR_FLAME_Y_OFFSET - 2);

	//文字パレット描写	
	make_flame(CHAR_FLAME_W,CHAR_FLAME_H,CHAR_FLAME_X_OFFSET,CHAR_FLAME_Y_OFFSET);
	print_line(" あ か さ た な は ま や ら わ ",CHAR_FLAME_X_OFFSET + 1,CHAR_FLAME_Y_OFFSET + 1);
	print_line(" い き し ち に ひ み    り    ",CHAR_FLAME_X_OFFSET + 1,CHAR_FLAME_Y_OFFSET + 2);
	print_line(" う く す つ ぬ ふ む ゆ る を ",CHAR_FLAME_X_OFFSET + 1,CHAR_FLAME_Y_OFFSET + 3);
	print_line(" え け せ て ね へ め    れ    ",CHAR_FLAME_X_OFFSET + 1,CHAR_FLAME_Y_OFFSET + 4);
	print_line(" お こ そ と の ほ も よ ろ ん ",CHAR_FLAME_X_OFFSET + 1,CHAR_FLAME_Y_OFFSET + 5);
	mvcur(CHAR_FLAME_X_OFFSET + 2,CHAR_FLAME_Y_OFFSET + 1);
	
	int flag = 1;
	int char_pos;
	struct input_assort tmp;
	while(flag){
		while(!((tmp = kbhit()).kbhit_flag)){
		}
		if(tmp.input_char == '\n'){
			continue;
		}else if(tmp.input_char == 'a'){
			printf("左");
		}
		char_pos = 0;
		while(input_string[char_pos] != '_'){
			char_pos++;
		}
		input_string[char_pos] = tmp.input_char;
		input_string[char_pos + 1] = '_';
		input_string[char_pos + 2] = '\0';
		print_line(input_string,CHAR_FLAME_X_OFFSET + 2,CHAR_FLAME_Y_OFFSET - 2);
	}

}
