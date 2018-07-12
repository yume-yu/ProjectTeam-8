/**
 * Written by yume_yu
 * printf()のみを使用したゲームを作るためのヘッダ
 */

#include "thebeautifulsky.h"

//必要キャラクタ-の定義
character naoki;
character lirel;
character arist;
character robo;
character boss1;
character boss2;
character dummy;
character *front;
character *back;
character *(enemies)[3];
int enemy_amount = 0;

//前衛装備の宣言
weapon all_weapons[7] = {
	{"No weapon",0,0},
	{"HandGun",15,1},
	{"Knife",5,0},
};

//後衛装備の宣言
weapon all_weapons4back[7] = {
	{"No weapon",0,0},
	{"Bow",10,1}
};

//防具の宣言
protector all_protectors[7] = {
	{"No protector",0},
	{"Shield",40},
	{"Protective Suit",55}
};

//装備枠の宣言
weapon *using_weapon;
protector *using_protector;
weapon *arist_using_weapon;
protector *arist_using_protector;
int potion_amount = 0;
int have_nasu = 0;



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
#include "storytexts.h"





/**
 *	マップをコピーする関数
 */
void mapcpy(char *(to)[HEIGHT - 2],char *(from)[HEIGHT - 2]){
	for(int i = 0; i <  HEIGHT -2; i++){
		//strcpy(to[i],from[i]);
		to[i] = from[i];
	}
}

/**
 *	座標配列を座標のアドレス配列に変換する関数
 */
void coor_cnv_adr(arrow_pos *(to)[WIDTH - 2][HEIGHT - 2],arrow_pos from[WIDTH - 2][HEIGHT - 2]){
	for(int i = 0; i < WIDTH - 2; i++){
		for(int j = 0; j < HEIGHT - 2; j++){
			to[i][j] = &from[i][j];
		}
	}
}

/**
 *	座標のアドレス配列をコピーする関数
 */
void coorcpy(arrow_pos *(to)[WIDTH - 2][HEIGHT - 2],arrow_pos *(from)[WIDTH - 2][HEIGHT - 2]){
	for(int i = 0; i < WIDTH - 2; i++){
		for(int j = 0; j < HEIGHT - 2; j++){
			to[i][j] = from[i][j];
		}
	}
}

/**
 *	表示文章を文章のアドレス配列に変換する関数
 */
void exstrcpy(extendstr *(to)[],extendstr from[],int lines){
	for(int i = 0; i < lines; i++){
		to[i] = &from[i];
	}
}

/**
 * キャラクターのステータス設定をする関数
 * name[10] キャラクターの名前
 * tmpch    ステータスを設定するキャラクター構造体のアドレス
 * hp       設定するhp
 * min_atk  与ダメージの下限
 * max_atk  与ダメージの上限
 */
void set_ch_stat(char name[10], character *tmpch, int hp, int max_hp,int min_atk, int max_atk){
	tmpch->name = name;
	tmpch->hp = hp;
	tmpch->max_hp = max_hp;
	tmpch->max_atk = max_atk;
	tmpch->min_atk = min_atk;
}

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
 * 武器のステータス設定をする関数
 * tmpwp    ステータスを設定する武器構造体のアドレス
 * atk      武器の攻撃力
 * is_gun  	銃かどうかのフラグ
 */
void set_weapon_stat(weapon *tmpwp, int atk, bool is_gun){
	tmpwp->atk = atk;
	tmpwp->is_gun = is_gun;
}

/**
 * 防具のステータス設定をする関数
 * tmppr    ステータスを設定する武器構造体のアドレス
 * def      武器の攻撃力
 */
void set_protector_stat(protector *tmppr, int def){
	tmppr->def = def;
}

/**
 * キャラクターのHPを変動させる関数
 * tmpch    hpが変動するキャラクター構造体のアドレス
 * damage   ダメージ量 正なら減算/負なら加算される ex.damageが-20 → 20回復
 */
void change_hp(character *tmpch, int damage){
	tmpch->hp -= damage;
	if(tmpch->hp < 0){
		tmpch->hp = 0;
	}else if(tmpch->hp > tmpch->max_hp){
		tmpch->hp = tmpch->max_hp;
	}
}

/**
 * @fn
 * ポーションの取得
 * @brief ポーションの取得を実行し得られたかを返す
 * @return ポーションが得られたか
 * @detail ポーションの所持数を確認し、3未満ならポーションを取得して1を返す。所持数が3を超えていたら0を返す
 */
int get_potion(){
	if(potion_amount < 3){
		potion_amount++;
		return 1;
	}else{
		return 0;
	}
}



/*
 * マップ上を移動する関数
 * width						マップの幅
 * hright 					マップの高さ
 * tmp_pos[10][10]	マップ座標の配列
 * offset						操作受け付け開始時の座標
 * 戻り値
 * int tmp_pos			ループを抜けた際の座標
 */
arrow_pos move_on_map(int width, int height,arrow_pos *(tmp_pos)[WIDTH -2 ][HEIGHT - 2], arrow_pos offset){
	arrow_pos arrow_pos_label = offset;
	arrow_pos return_value;
	input_assort tmp_input_list;
	print_line("●",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
	while(1){
		while(!(tmp_input_list = mykbhit()).kbhit_flag);
		switch(tmp_input_list.input_char){
			case 'w':
				print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				if(arrow_pos_label.y <= 0 || tmp_pos[arrow_pos_label.x][arrow_pos_label.y - 1]->not_active){
				}else{
					arrow_pos_label.y--;
				}
				print_line("●",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				break;

			case 's':
				print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				if(arrow_pos_label.y > height - 2 || tmp_pos[arrow_pos_label.x][arrow_pos_label.y + 1]->not_active){
				}else{
					arrow_pos_label.y++;
				}
				print_line("●",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				break;

			case 'a':
				print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				if(arrow_pos_label.x <= 0 || tmp_pos[arrow_pos_label.x - 1][arrow_pos_label.y]->not_active){
				}else{
					arrow_pos_label.x--;
				}
				print_line("●",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				break;

			case 'd':
				print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				if(arrow_pos_label.x > width - 2 || tmp_pos[arrow_pos_label.x + 1][arrow_pos_label.y]->not_active){
				}else{
					arrow_pos_label.x++;
				}
				print_line("●",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				break;
			case ENTERKEY:
				break;
			case ' ':
				start_pos =*tmp_pos[arrow_pos_label.x][arrow_pos_label.y];
				start_pos.x -= 2;
				start_pos.y -= 2;
				arrow_pos_label.x = width - 2;
				arrow_pos_label.y = height - 1;
				return *tmp_pos[arrow_pos_label.x][arrow_pos_label.y];
				break;
			default:
				//print_line("●",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				continue;
				//break;
		}
		//デバッグ用座標表示
		//printf("%2d,%2d",arrow_pos_label.x,arrow_pos_label.y);
		//printf("%2d,%2d %2d,%2d %d",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y,arrow_pos_label.x,arrow_pos_label.y,tmp_pos[arrow_pos_label.x][arrow_pos_label.y + 1]->not_active);
		if(tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->at_event){
			break;
		}
	}
	return *tmp_pos[arrow_pos_label.x][arrow_pos_label.y];
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
	print_line("Beta Ver",(WIDTH - 8)/2,14);
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

//戦闘モードの時にコマンド部分表示する関数
void print_bt_commands(){
	print_line("こうげき",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
	print_line("とくしゅ",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
	print_line("かばう",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3);
	print_line("どうぐ",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 4);
	fflush(stdout);
}

//敵のHPゲージを描画する関数
void print_health_bar(character *target[],int amount){
	double health_par = 0;
	for(int i = 0; i < amount; i++){
		make_flame(25,3,2,2 + 3 * i);
		print_line("                    ",2,2+3*i);
		mvcur(2,2 + 3 * i);
		printf("[");
		mvcur(WIDTH - 1,2 + 3 * i);
		printf("]");
		mvcur(3,3 + 3 * i);
		printf("%s",target[i]->name);
		health_par = ( (double)target[i]->hp / target[i]->max_hp) * ( WIDTH - 4 );
		for(int j = 0; j < WIDTH - 4;j++){
			mvcur(3+j,2 + 3 * i);
			if(j < health_par){
				printf("=");
			}else{
				printf(" ");
			}
		}
		//printf("%f＼n%d＼n%d",health_par,target[i]->hp,target[i]->max_hp);
		fflush(stdout);
	}
}

//戦闘モードの時にHP部分を描画する関数
void print_bt_status(character *front,character *back){
	//ステータス部分表示
	char *(spaces)[] = {
		"               ",
		"               "
	};
	print_lines(spaces,BATTLE_MODE_STATUS_HP_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,2);
	print_line("HP",BATTLE_MODE_STATUS_HP_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
	mvcur(BATTLE_MODE_STATUS_HP_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
	printf("%-8s:%4d/%4d",front->name,front->hp,front->max_hp);
	if(strcmp(back->name,"dummy")){
		mvcur(BATTLE_MODE_STATUS_HP_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3);
		printf("%-8s:%4d/%4d",back->name,back->hp,back->max_hp);
	}
	mvcur(0,HEIGHT + 1);
	fflush(stdout);
}

//戦闘モード
int battle(character *front,character *back,character *enemies[3], int enemy_amount){
	mykbhit();																	//過剰入力クッション
	int finish_flag = 0;												//戦闘終了のフラグ
	int protect_flag = 0;												//かばう行動のフラグ
	int use_nasu = 0;														//ナス使用フラグ
	int damage = 0;															//計算後のダメージを記憶する変数
	int target_label = 0;												//攻撃対象を判断するための変数
	int turn_count = 1;													//特殊行動のため戦闘開始からのターンを数える変数
	int sp_count = 0;														//特殊行動の行動不能ターンを数える変数
	int enemies_dead_check = 0;									//敵が全滅したかどうかチェックする時に使う変数
	int player_can_act = 1;											//プレイヤーが行動可能かのフラグ
	int used_flare = 0;													//ステージ5での味方特殊行動の使用後フラグ
	int enemy_amount_for_bar = enemy_amount;		//HPゲージ描画のため、本来の敵の数を記憶する変数
	char battle_text[100] = "\0";
	character *for_bar[enemy_amount];		//HPゲージ描画のため、本来の敵のアドレスを記憶する変数
	for(int i = 0;i < enemy_amount;i++){
		for_bar[i] = enemies[i];
	}
	arrow_pos battle_menu_arrow[] = {
		{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1},
		{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2},
		{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3},
		{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 4}
	};
	arrow_pos battle_item_menu_arrow[2][4] = {
		{
			{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1},
			{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2},
			{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3},
			{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 4},
		},
		{
			{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,1},
			{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2,1},
			{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3,1},
			{2 * BATTLE_MODE_COMMAND_POS + 10 - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 4},
		}
	};

	//敵のHPを初期化
	for(int i = 0; i < enemy_amount; i++){
		change_hp(enemies[i],-1 * enemies[i]->max_hp);
	}
	flame_flush();
	make_vsflame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_SPLIT_X);

	print_bt_status(front,back);
	print_health_bar(for_bar,enemy_amount_for_bar);

	while(!finish_flag){
		mvcur(BATTLE_MODE_STATUS_FLAME_X + 2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT - 1);
		printf("Turn %2d",turn_count);

		/*プレイヤーの行動 ここから*/
		if(player_can_act){
			print_bt_commands();																			//プレイヤーのコマンドを表示する
			int command = select_from_list(battle_menu_arrow,4);			//コマンド入力を受け付ける	
			sub_flame_clean(																					//コマンド部分フレームクリーン	
					BATTLE_MODE_STATUS_FLAME_SPLIT_X,
					BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,
					BATTLE_MODE_STATUS_FLAME_X + 1,
					HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1
					);
			switch(command){
				case 0:																																		//attack(攻撃)だった時
					/*敵の一覧表示 ここから*/
					for(int i = 0; i <= enemy_amount; i++){
						mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1 + i);
						if(i < enemy_amount){
							printf("%s",enemies[i]->name);
						}else{
							printf("戻る");
						}
					}
					fflush(stdout);
					/*敵の一覧表示 ここまで*/
					target_label = select_from_list(battle_menu_arrow,enemy_amount + 1);
					sub_flame_clean(																												//コマンド部分フレームクリーン
							BATTLE_MODE_STATUS_FLAME_SPLIT_X,
							BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,
							BATTLE_MODE_STATUS_FLAME_X + 1,
							HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1
							);
					if(target_label == enemy_amount){
						continue;
					}
					if(!strcmp(front->name,FRONT1_NAME) || !strcmp(front->name,FRONT2_NAME)){
						damage = front->min_atk + rand() % (front->max_atk - front->min_atk - 1) + using_weapon->atk;
					}else{
						damage = front->min_atk + rand() % (front->max_atk - front->min_atk - 1);
					}
					if(use_nasu){
						damage *= 2;
						use_nasu = 0;
					}
					mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					printf("%s に",enemies[target_label]->name);
					mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
					printf("                %3d ダメージ!▼",damage);
					change_hp(enemies[target_label],damage);
					if(using_weapon->is_gun && !strcmp(front->name,FRONT2_NAME)){
						damage = front->min_atk + rand() % (front->max_atk - front->min_atk - 1) + using_weapon->atk;
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3);
						printf("%s に",enemies[target_label]->name);
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 4);
						printf("                %3d ダメージ!▼",damage);
						change_hp(enemies[target_label],damage);
					}
					print_health_bar(for_bar,enemy_amount_for_bar);
					wait_anyinput();
					if(enemies[target_label]->hp <= 0){
						sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						printf("%s は",enemies[target_label]->name);
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
						printf("                      倒れた!▼");
						for(int i = target_label; i + 1 < enemy_amount;i++){
							enemies[i] = enemies[i + 1];
						}
						enemy_amount--;
						wait_anyinput();
					}
					break;
				case 1:
					mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					if(strstr(front->name,"Robo") == NULL){
						printf("戻る");
						fflush(stdout);
						target_label = select_from_list(battle_menu_arrow,1);
					}else{
						if(!strcmp(front->name,FRONT3_NAME)){
							printf("カラドボルグ");
						}else if(!strcmp(front->name,FRONT4_NAME)){
							printf("フレア");
						}
						mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
						printf("戻る");
						fflush(stdout);
						target_label = select_from_list(battle_menu_arrow,2);
					}
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					if((strstr(front->name,"Robo") == NULL && target_label == 0) || target_label == 1){
						continue;
					}else if(target_label == 0){
						if(!strcmp(front->name,FRONT3_NAME)){
							if(turn_count < 5){
								print_line("カラドボルグは5ターン目まで使えません▼ ",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								wait_anyinput();
								sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								continue;
							}else{
								mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								printf("%s はカラドボルグを使った!▼",front->name);
								wait_anyinput();
								mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
								wait_anyinput();
								/*敵ダメージ処理ここから*/
								for(int i = 0; i < enemy_amount; i++){
									sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
									change_hp(enemies[i],FRONT3_SP_DAMAGE);
									mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
									printf("%s に %3d ダメージ!▼",enemies[target_label]->name,damage);
									print_health_bar(for_bar,enemy_amount_for_bar);
									wait_anyinput();
									/*敵ダメージ処理ここまで*/
									/*敵死亡判定ここから*/
									if(enemies[i]->hp <= 0){
										sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
										mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
										printf("%s は",enemies[target_label]->name);
										mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
										printf("                      倒れた!▼");
										for(int i = target_label; i + 1 < enemy_amount;i++){
											enemies[i] = enemies[i + 1];
										}
										enemy_amount--;
										wait_anyinput();
									}
								}
								/*敵死亡判定ここまで*/
							}
						}else if(!strcmp(front->name,FRONT4_NAME)){
							if(turn_count < 3){
								print_line("フレアは3ターン目まで使えません▼ ",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								wait_anyinput();
								sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								continue;
							}else if(!used_flare){
								mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								printf("%s はフレアを使った!▼",front->name);
								used_flare = 1;
								wait_anyinput();
								/*敵ダメージ処理ここから*/
								for(int i = 0; i < enemy_amount; i++){
									sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
									mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
									printf("%s に %4d ダメージ!▼",enemies[i]->name,enemies[i]->hp / 2);
									change_hp(enemies[i],enemies[i]->hp / 2);
									print_health_bar(for_bar,enemy_amount_for_bar);
									wait_anyinput();
									/*敵ダメージ処理ここまで*/
									/*敵死亡判定ここから*/
									if(enemies[i]->hp <= 0){
										sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
										mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
										printf("%s は倒れた!▼",enemies[target_label]->name);
										for(int i = target_label; i + 1 < enemy_amount;i++){
											enemies[i] = enemies[i + 1];
										}
										enemy_amount--;
										wait_anyinput();
									}
								}
								/*敵死亡判定ここまで*/
							}else{
								print_line("フレアは1度しか使えません▼ ",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								wait_anyinput();
								sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								continue;
							}
						}
					}
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					break;
				case 2:
					protect_flag = 1;
					mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					printf("%s はかばう体勢に入った▼",front->name);
					wait_anyinput();
					break;
				case 3:
					if(potion_amount + have_nasu <= 3){
						for(int i = 0; i <= potion_amount + have_nasu; i++){
							mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1 + i);
							if(i < potion_amount){
								printf("ポーション");
							}else if(i < potion_amount + have_nasu){
								printf("ｿﾗﾅﾑ･ﾒﾛﾝｹﾞﾅ");
							}else{
								printf("戻る");
							}
							fflush(stdout);
						}
						target_label = select_from_list(battle_menu_arrow,potion_amount + have_nasu + 1);
						if(target_label < potion_amount){
							sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
							change_hp(front,-1 * front->max_hp);
							change_hp(&arist,-1 * arist.max_hp);
							print_bt_status(front,back);
							print_line("ポーションを使った!▼ ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
							potion_amount--;
							wait_anyinput();
						}else if(target_label < potion_amount + have_nasu){
							sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
							print_line("力がみなぎる!▼ ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
							have_nasu = 0;
							use_nasu = 1;
							wait_anyinput();
						}else{
							sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
							continue;
						}
					}else if(potion_amount + have_nasu >= 4){
						for(int i = 0; i <= potion_amount + have_nasu; i++){
							mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1 + i);
							if(i < potion_amount){
								printf("ポーション");
							}else if(i < potion_amount + have_nasu){
								printf("ｿﾗﾅﾑ･ﾒﾛﾝｹﾞﾅ");
							}
							fflush(stdout);
						}
						print_line("戻る",2 * BATTLE_MODE_COMMAND_POS + 10,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + potion_amount + have_nasu);

						target_label = select_from_2dlist(2,4,battle_item_menu_arrow);
						switch(target_label){
							case 0:	//ポーション
							case 2:
							case 4:
								sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								change_hp(front,-1 * front->max_hp);
								change_hp(&arist,-1 * arist.max_hp);
								print_bt_status(front,back);
								print_line("ポーションを使った!▼ ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								potion_amount--;
								wait_anyinput();
								break;
							case 6:	//Nasu
								sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								print_line("力がみなぎる!▼ ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								have_nasu = 0;
								use_nasu = 1;
								wait_anyinput();
								break;
							case 7:	//戻る
								sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								continue;
								break;
							default:
								break;
								
						}
					}
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					break;
				default:
					break;
			}
			sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			/*プレイヤーの行動 ここから*/

			print_health_bar(for_bar,enemy_amount_for_bar);

			//勝利判定
			enemies_dead_check = 0;
			for(int i = 0; i <  enemy_amount_for_bar; i++){
				enemies_dead_check += for_bar[i]->hp;
			}
			if(enemies_dead_check <= 0){
				print_line("戦闘に勝利した!▼",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				finish_flag = 1;
				wait_anyinput();
				//flame_flush();
				return 1;
				continue;
			}
			//判定終わり

			//後衛の行動
			if(strcmp(back->name,"dummy")){
				switch(rand() % 4){
					case 0:
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						printf("%s は怯えている...▼",back->name);
						wait_anyinput();
						break;
					case 1:
						if(!strcmp(arist_using_weapon->name,"Bow")){
							print_line("アリストのレインボーアロー!▼",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
							wait_anyinput();
							damage = (BACK_ATTACK);
							target_label = rand() % enemy_amount;
							change_hp(enemies[target_label],damage);
							mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
							printf("%s に %3d ダメージ!▼ ",enemies[target_label]->name,damage);
							print_health_bar(for_bar,enemy_amount_for_bar);
							wait_anyinput();
							break;
						}
					default:
						change_hp(front,-1 * arist.max_atk);
						change_hp(back,-1 * arist.max_atk);
						print_bt_status(front,back);
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						printf("%sはヒールを唱えた!▼ ",back->name);
						wait_anyinput();
						break;
				}
			}
			sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			//後衛の行動終わり
		}else{
			print_line("動けない...▼ ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			wait_anyinput();
			sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			for(int i = 0; i < enemy_amount; i++){
				if(!strcmp(enemies[i]->name,ST3_BOSS_NAME)){
					player_can_act = 1;
				}else if(!strcmp(enemies[i]->name,ST5_BOSS_NAME)){
					sp_count++;
					if(sp_count >= 3){
						player_can_act = 1;
						sp_count = 0;
					}
				}
			}
		}
		print_health_bar(for_bar,enemy_amount_for_bar);

		//勝利判定
		enemies_dead_check = 0;
		for(int i = 0; i <  enemy_amount_for_bar; i++){
			enemies_dead_check += for_bar[i]->hp;
		}
		if(enemies_dead_check <= 0){
			print_line("戦闘に勝利した!▼",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			wait_anyinput();
			finish_flag = 1;
			return 1;
			continue;
		}
		//判定終わり

		//敵の行動
		for(int i = 0; i < enemy_amount; i++){
			if(enemies[i]->hp > 0){
				if(!strcmp(enemies[i]->name,ST3_BOSS_NAME) && turn_count == 6){
					print_line("古代の機械巨人の特殊攻撃!▼ ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					wait_anyinput();
					print_line("アルティメットバウンド!▼ ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
					wait_anyinput();
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					mvcur(BATTLE_MODE_COMMAND_POS - 2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					printf("次のターンの行動を封じられた...▼ ");
					fflush(stdout);
					wait_anyinput();
					player_can_act = !player_can_act;
				}else if(!strcmp(enemies[i]->name,ST4_BOSS_NAME) && rand() % 10 == 5){
					change_hp(enemies[i],-500);
					print_line("Boss はケアルラを唱えた!▼ ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					wait_anyinput();
				}else if(!strcmp(enemies[i]->name,"St5Bs") && turn_count != 0 && turn_count % 4 == 0){
					print_line("Stage5 Boss's action!▼ ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					wait_anyinput();
					print_line("The Gaia!▼ ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
					wait_anyinput();
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					char *(string)[] = {
						"3ターンの間,",
						"        行動を封じられた...▼ "
					};
					print_lines(string,BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,2);
					fflush(stdout);
					wait_anyinput();
					player_can_act = !player_can_act;
				} else if(!strcmp(enemies[i]->name,ST5_BOSS_NAME) && rand() % 10 == 5 && enemies[i]->hp < enemies[i]->max_hp * 0.4){
					char *(string)[] = {
						"Stage5 Boss cast ",
						"              'Tetragrammaton'!▼ "
					};
					change_hp(enemies[i],-1500);
					print_lines(string,BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,2);
					wait_anyinput();
				} else {
					damage = enemies[i]->min_atk + rand() % (enemies[i]->max_atk - enemies[i]->min_atk - 1);
					if(protect_flag || !strcmp(back->name,"dummy")){
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						printf("%s に %3d のダメージ!▼",front->name,damage);
						change_hp(front,damage);
					}else{
						switch((int)(rand() % 2)){
							case 0:
								mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								printf("%s に %3d のダメージ!▼",back->name,damage);
								change_hp(back,damage);
								break;
							default:
								mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								printf("%s に %3d のダメージ!▼",front->name,damage);
								change_hp(front,damage);
								break;
						}
					}
					protect_flag = 0;
					wait_anyinput();
				}
			}
			print_health_bar(for_bar,enemy_amount_for_bar);
			print_bt_status(front,back);
			if(front->hp <= 0 || (back->hp <= 0 && strcmp(back->name,"dummy"))){
				sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				print_line("Lose...▼",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				finish_flag = 1;
				return 0;
				wait_anyinput();
				continue;
			}
		}
		//敵の行動終わり
		sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
		turn_count++;
	}
	return 0;
}

void gameover_lose(){

}

void gameover_win(){
	print_lines(gameover,(WIDTH - 27) / 2,(HEIGHT - 3) / 2,3);
	wait_anyinput();
}
