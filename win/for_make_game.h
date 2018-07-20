/**
 * Written by yume_yu
 * printf()のみを使用したゲームを作るためのヘッダ
 */

#include "thebeautifulsky.h"





//現在のステージ
stage now_stage = stage1;
char *(now_map)[WIDTH - 2];
arrow_pos *(now_map_coor)[WIDTH - 2][HEIGHT - 2];
int room_id = 0;
arrow_pos start_pos = {0,15,0,0};
extendstr *now_text[HEIGHT];

//マップと座標系一覧の宣言
char *(maps)[9][HEIGHT - 2];
arrow_pos *(map_coors)[10][WIDTH - 2][HEIGHT - 2];


//ストーリーの読み込み








/**
 * @fn
 * ゲーム開始時の座標とステージを初期化する関数
 * @brief start_posとnow_stageの初期化
 * @detail ループ復帰時やチュートリアル終了時などにゲームを始めるときに初期化すべき部分を初期化する
 */
void reset_state(){
	room_id = 0;
	potion_amount = 0;
	have_nasu = 0;
	start_pos.x = 0;
	start_pos.y = 15;
	now_stage = stage1;
}

/*
 *	マップ配列の初期化
 */
void initmaps(){
	mapcpy(maps[stage1],map_st1);
	mapcpy(maps[stage2],map_st2);
	mapcpy(maps[stage3_1],map_st3_1);
	mapcpy(maps[stage3_2],map_st3_2);
	mapcpy(maps[stage3_3],map_st3_3);
	mapcpy(maps[stage4_1],map_st4_1);
	mapcpy(maps[stage4_2],map_st4_2);
	mapcpy(maps[stage4_3],map_st4_3);
	mapcpy(maps[ope_exp],map_exp);
	coor_cnv_adr(map_coors[stage1],st1_pos);
	coor_cnv_adr(map_coors[stage2],st2_pos);
	coor_cnv_adr(map_coors[stage3_1],st3_1_pos);
	coor_cnv_adr(map_coors[stage3_2],st3_2_pos);
	coor_cnv_adr(map_coors[stage3_3],st3_3_pos);
	coor_cnv_adr(map_coors[stage4_1],st4_1_pos);
	coor_cnv_adr(map_coors[stage4_2],st4_2_pos);
	coor_cnv_adr(map_coors[stage4_3],st4_3_pos);
	coor_cnv_adr(map_coors[ope_exp],exp_pos);
	mapcpy(now_map,maps[now_stage]);
	coorcpy(now_map_coor,map_coors[now_stage]);
	reset_state();
}


//各キャラクターのステータス初期化
void initchara(){
	set_ch_stat(FRONT2_NAME,&naoki,FRONT2_HP_ST2,FRONT2_HP_ST2,FRONT2_MINATK_ST2,FRONT2_MAXATK_ST2);
	set_ch_stat(FRONT1_NAME,&lirel,FRONT1_HP,FRONT1_HP,FRONT1_MINATK,FRONT1_MAXATK);
	set_ch_stat(BACK_NAME,&arist,BACK_HP_ST1,BACK_HP_ST1,0,BACK_HEAL_ST1);
	set_ch_stat(FRONT3_NAME,&robo,FRONT3_HP,FRONT3_HP,FRONT3_MINATK,FRONT3_MAXATK);
	set_ch_stat("boss1",&boss1,100,100,10,20);
	set_ch_stat("boss2",&boss2,100,100,10,20);
	set_ch_stat("dummy",&dummy,0,0,0,0);
	//装備を素手に初期化
	using_weapon = &all_weapons[0];
	using_protector = &all_protectors[0];
	arist_using_weapon = &all_weapons4back[0];
	arist_using_protector = &all_protectors[0];
}











/**
 *  タイトルロゴの出方が微妙に違うのでヘッダで定義
 */
//タイトルロゴ宣言
char *(title)[9] = {
	"┌┬┐┬ ┬┌─┐                       ",
	" │ ├─┤├┤                        ",
	" ┴ ┴ ┴└─┘                       ",
	"   ┌┐ ┌─┐┌─┐┬ ┬┌┬┐┬┌─┐┬ ┬┬      ",
	"   ├┴┐├┤ ├─┤│ │ │ │├┤ │ ││      ",
	"   └─┘└─┘┴ ┴└─┘ ┴ ┴└  └─┘┴─┘    ",
	"                      ┌─┐┬┌─┬ ┬ ",
	"	                     └─┐├┴┐└┬┘ ",
	"                      └─┘┴ ┴ ┴  "
};
//ロゴ移動中の片付け宣言
char *(title_space)[9] = {
	"                                ",
	"                                ",
	"                                ",
	"                                ",
	"                                ",
	"                                ",
	"                                ",
	"                                ",
	"                                "
};

char *(gameover)[] = {
	"┌─┐┌─┐┌┬┐┌─┐  ┌─┐┬  ┬┌─┐┬─┐",
	"│ ┬├─┤│││├┤   │ │└┐┌┘├┤ ├┬┘",
	"└─┘┴ ┴┴ ┴└─┘  └─┘ └┘ └─┘┴└─",
};

/**
 *	タイトル画面の星のアニメーションが書かれた関数
 */
void stars(int x[],int y[],int amount){
	//for(int i = 0; i < 10; i++){
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
}

/**
 *	タイトル画面を表示する関数
 */
int maintitle(){
	/**
	 * ここからロゴのスクロール開始
	 * 全部見えてないスクロール→ 全部見えた状態のスクロール
	 */
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < i; j++){
			print_line(title[8 - j],15,i - j + 1);
		}
		fflush(stdout);
		usleep(0.2 * 1000000);
		print_lines(title_space,15,2,9);
		mykbhit();
	}

	print_lines(title,15,2,9);
	fflush(stdout);
	usleep(0.2 * 1000000);
	mykbhit();

	print_lines(title_space,15,2,9);
	print_lines(title,15,3,9);
	fflush(stdout);
	usleep(0.2 * 1000000);
	mykbhit();

	print_lines(title_space,15,3,9);
	print_lines(title,15,4,9);
	fflush(stdout);
	usleep(0.2 * 1000000);
	mykbhit();

	print_lines(title_space,15,4,9);
	print_lines(title,15,5,9);
	print_line("Press Enter",25,HEIGHT - 4);
	fflush(stdout);
	mykbhit();
	/* ここまでロゴスクロール部分
	 * この段階でロゴとPressEnterが見える
	 */

	//ここから星の描画
	//星の座標変数を宣言
	int star_x[STAR_AMOUNT];// ={10,15,20};
	int star_y[STAR_AMOUNT];// ={20,15,10};
	//乱数の初期化
	srand(time(NULL));
	//文字とかぶらないように座標を設定する
	for(int i = 0; i< STAR_AMOUNT;i++){
		//まず乱数を振る
		star_x[i] = rand() % (WIDTH - 2) + 2;
		star_y[i] = rand() % (HEIGHT - 2) + 2;
		//もし座標がタイトルロゴのある範囲とかぶっていたら
		if(star_y[i] >= 5 && star_y[i] < 15){
			if(star_x[i] >= 15 && star_x[i] <= 46){
				i--;	//今の変数に乱数を振り直すため、ラベルを減算
			}
			//PressEnterとかぶっていた時も同じ処理をする
		}else if(star_y[i] >= HEIGHT - 5 && star_y[i] <= HEIGHT - 3){
			if(star_x[i] >= 24 && star_x[i] <= 37){
				i--;
			}
		}
	}
	//星の点滅開始 Enter入力を待機し、押されたらループ脱出
	do{
		stars(star_x,star_y,STAR_AMOUNT);
	}while((mykbhit().input_char) != ENTERKEY);
	char *(select_start)[] =	{										//ゲーム開始の選択肢の文字列
		"     操作説明をみる",
		"     ゲームを始める",
		"",
		"W/S 選択      Enter 決定"
	};
	arrow_pos title_command_pos[] = {
		{TITLE_MENU_BASE_X + 4,TITLE_MENU_BASE_Y,0,0},
		{TITLE_MENU_BASE_X + 4,TITLE_MENU_BASE_Y + 1,0,0}
	};
	make_flame(24 + 5,7,TITLE_MENU_BASE_X - 3,TITLE_MENU_BASE_Y - 2);
	print_lines(select_start,TITLE_MENU_BASE_X,TITLE_MENU_BASE_Y,lengthof(select_start,char *));
	return !select_from_list(title_command_pos,2);
}

/*
 * 戦闘系関数ここから
 */

void gameover_lose(){

}

void gameover_win(){
	print_lines(gameover,(WIDTH - 27) / 2,(HEIGHT - 3) / 2,3);
	wait_anyinput();
}
