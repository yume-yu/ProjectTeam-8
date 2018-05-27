/**
  * Writtenby yume_yu
  * windowsのapiを使ってカーソルの位置を指定箇所へ移動する関数を定義したヘッダ
  */
 
#include <windows.h>
#include <conio.h>

//WindowsとUNIXでEnterキーの入力が異なるのでプログラム上の表記を統一
#define ENTERKEY 0x0d

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

/*
 * 入力周りを扱う構造体
 * kbhit_flag	キーが押されているかを返すint
 * input_char	押されているキー
 */
struct input_assort{
	int kbhit_flag;
	int input_char;
};

/*
 * キーボードが押されているかとその入力キーをとる関数
 * 戻り値
 * struct input_assort temp	2つのフラグの構造体
 */
struct input_assort mykbhit(){
	struct input_assort temp;
	if(kbhit()){
		temp.input_char =  _getch();
		temp.kbhit_flag = 1;
	}else{
		temp.input_char = 0;
		temp.kbhit_flag = 0;
	}
	return temp;
}

/** 
 * 標準出力の初期化
 */
void init_term(){
	//カーソル位置を(1,1)に移動
	mvcur(1,1);
}

/**
 * 指定箇所への1行の文字出力を行う関数
 * string 出力する文字列
 * x      出力するx座標
 * y      出力するy座標
 */
void print_line(char string[], int x, int y){
	mvcur(x,y);
	printf("%s",string);
	mvcur(0,HEIGHT + 1);
}

/*
 * 指定箇所への複数行行の文字出力を行う関数
 * string    出力する文字列配列
 * x         出力を開始するx座標
 * y         出力を開始するy座標
 * num_lines 出力する行数
 */
void print_lines(char string[][100], int x, int y, int num_lines){
	for(int i = 0; i < num_lines; i++){
		mvcur(x,y+i);
		printf("%s",string[i]);
	}
	mvcur(0,HEIGHT + 1);
}

/*
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
		printf("│");
	}

	//最終行部分の描画
	mvcur(offset_x,offset_y + height - 1);
	printf("└");
	for(int i = 0; i < print_width; i++){
		printf("─");
	}
	printf("┘");

	//カーソル位置の初期化
	mvcur(1,HEIGHT+1);
}

/**
 * 横分割フレームの作成関数
 * width    作成するフレームの幅
 * height   作成するフレームの高さ
 * offset_x 作成するフレームの開始位置のx座標
 * offset_y 作成するフレームの開始位置のy座標
 * split_x  フレームの区切り線を入れるx座標
 */
void make_vsflame(int width, int height, int offset_x, int offset_y, int split_x){
	int print_width = width - 2;
	int print_height = height - 2;
	//1行目の描画
	mvcur(offset_x,offset_y);
	printf("┌");
	for(int i = 0; i < print_width; i++){
		if(i == split_x){
			printf("┬");
		}else{
			printf("─");
		}
	}
	printf("┐");
	//中間部分の描画
	for(int i = 0; i < print_height; i++){
		mvcur(offset_x,offset_y + 1 + i);
		printf("│");
		for(int j = 0; j < print_width; j++){
			if(j == split_x){
				printf("│");
			}else{
				printf(" ");
			}
		}
		printf("│");
	}
	//最終行部分の描画
	mvcur(offset_x,offset_y + height - 1);
	printf("└");
	for(int i = 0; i < print_width; i++){
		if(i == split_x){
			printf("┴");
		}else{
			printf("─");
		}
	}


	printf("┘\n");

	//カーソル位置の初期化
	mvcur(1,HEIGHT+1);

}

/**
 * フレーム内をアニメーションでスペース埋めにする関数
 */
void flame_flush(){	
	for(int i = 2; i < HEIGHT; i++){
		for(int j = 2; j < WIDTH; j++){
			print_line(" ",j,i);
		}
		fflush(stdout);
		usleep(2 * 10000);
	}
}

/**
 * フレーム内をスペース埋めにする関数
 */
void flame_clean(){	
	for(int i = 2; i < HEIGHT; i++){
		for(int j = 2; j < WIDTH; j++){
			mvcur(j,i);
			printf(" ");
		}
		//usleep(2 * 10000);
	}
		fflush(stdout);
}

/**
 * 指定フレーム内をスペース埋めにする関数
 */
void sub_flame_clean(int width, int height, int x, int y){	
	for(int i = y; i < y + height; i++){
		for(int j = x; j <x+  width;j++){
			print_line(" ",j,i);
		}
	}	
	fflush(stdout);
}

/**
  *  Enter入力の待機をする関数
  */
void wait_anyinput(){
	mvcur(0,HEIGHT + 1);
	fflush(stdout);
	while(!mykbhit().kbhit_flag);
	while(mykbhit().kbhit_flag);
}
