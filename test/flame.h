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

