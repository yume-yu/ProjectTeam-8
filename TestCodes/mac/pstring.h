/**
  * Writtenby yume_yu
  * 標準出力の任意の場所に文字列を出力する自作関数を扱うためのヘッダ
  */


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

/**
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

void string_march(char string[4], int x, int y, int width, int height){
	int line_num = 0;
	int chara_count = 0;
	char *p_str = string;
	printf("%s",string);
	/*while(line_num < height){
		while((chara_count % width) != 0){
			
		}
		printf("\n");
	}*/
}
