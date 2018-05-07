#include <stdio.h>
#include "mconio.h"
#define WIDTH 60
#define HEIGHT 25
#define MAIN_FLAME_X_OFFSET 1
#define MAIN_FLAME_Y_OFFSET 1

#include "termcoor.h"
#include "flame.h"
#include "pstring.h"
int main(){
	//ターミナルの文字を流してカーソル位置を(1,1)にする
	init_term();
	//大枠ウィンドウフレームの作成
 	make_flame(WIDTH,HEIGHT,MAIN_FLAME_X_OFFSET,MAIN_FLAME_Y_OFFSET);

	//テスト呼び出し
	make_flame(2,2,2,2);
	make_flame(5,5,7,7);
	make_vsflame(20,5,5,5,5);
	print_line("aasdasdas",16,8);
	char string[][100] = {"","*決意を抱いた"};
	print_lines(string,16,8,2);
	struct input_assort tmp;
	while(!(tmp = kbhit()).kbhit_flag){
	}
	printf("%X\n",tmp.input_char);
}

