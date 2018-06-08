/**
 * Written by yume_yu
 * printf()のみを使用したゲームを作るためのヘッダ
 */

 //必要なライブラリをインクルード
 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <string.h>

 //定数定義部
 /**
  * メインフレーム(大枠)関連定数
  * WIDTH          メインフレームの幅
  * HEIGHT         メインフレームの高さ
  * MAIN_FLAME_X   メインフレームの開始位置のX座標
  * MAIN_FLAME_Y   メインフレームの開始位置のY座標
  */
 #define WIDTH					60
 #define HEIGHT 				25
 #define MAIN_FLAME_X	1
 #define MAIN_FLAME_Y 	1

 /*
  * ステージセレクトフレーム関連定数
  * SELECT_STAGE_FLAME_WIDTH  フレームの幅
  * SELECT_STAGE_FLAME_HEIGHT フレームの高さ
  * SELECT_STAGE_FLAME_X      フレームの開始位置のX座標
  * SELECT_STAGE_FLAME_Y      フレームの開始位置のY座標
  */
 #define SELECT_STAGE_FLAME_WIDTH  				25
 #define SELECT_STAGE_FLAME_HEIGHT 				11
 #define SELECT_STAGE_FLAME_X      				(WIDTH  - SELECT_STAGE_FLAME_WIDTH) / 2
 #define SELECT_STAGE_FLAME_Y      				(HEIGHT - SELECT_STAGE_FLAME_HEIGHT) / 2

 /**
  * 戦闘画面でのウィンドウサイズ/配置関連定数
  * BATTLE_MODE_STATUS_FLAME_WIDTH   下分割フレームの幅
  * BATTLE_MODE_STATUS_FLAME_HEIGHT  下分割フレームの高さ
  * BATTLE_MODE_STATUS_FLAME_X       下分割フレームの開始位置のX座標
  * BATTLE_MODE_STATUS_FLAME_SPLIT_X 下分割フレームの分割位置
  * BATTLE_MODE_COMMAND_POS          戦闘コマンドブレーム(下左)の1行目のX座標
  * BATTLE_MODE_STATUS_HP_POS        ステータスフレーム(下右)の1行目のX座標
  */
 #define BATTLE_MODE_STATUS_FLAME_WIDTH		WIDTH-2
 #define BATTLE_MODE_STATUS_FLAME_HEIGHT		6
 #define BATTLE_MODE_STATUS_FLAME_X				2
 #define BATTLE_MODE_STATUS_FLAME_SPLIT_X 	2*(WIDTH-2)/3-1
 #define BATTLE_MODE_COMMAND_POS 					7
 #define BATTLE_MODE_STATUS_HP_POS 				BATTLE_MODE_STATUS_FLAME_SPLIT_X+5

 /*
  * キャラクターステータス設定モード関連定数
  * EDIT_MODE_SELECT_FLAME_WIDTH
  * EDIT_MODE_SELECT_FLAME_HEIGHT
  * EDIT_MODE_SELECT_FLAME_X
  * EDIT_MODE_SELECT_FLAME_Y
  * EDIT_MODE_EDIT_FLAME_CHAR_X
  * EDIT_MODE_EDIT_FLAME_CHAR_Y
  */
 #define EDIT_MODE_SELECT_FLAME_WIDTH			WIDTH - 4
 #define EDIT_MODE_SELECT_FLAME_HEIGHT			10
 #define EDIT_MODE_SELECT_FLAME_X					3
 #define EDIT_MODE_SELECT_FLAME_Y					2
 #define EDIT_MODE_EDIT_FLAME_WIDTH				WIDTH - 4
 #define EDIT_MODE_EDIT_FLAME_HEIGHT				HEIGHT - 12
 #define EDIT_MODE_EDIT_FLAME_X						3
 #define EDIT_MODE_EDIT_FLAME_Y						12
 #define EDIT_MODE_EDIT_FLAME_CHAR_X				6
 #define EDIT_MODE_EDIT_FLAME_CHAR_Y 			14
 #define ECHECK_SELECT_FLAME_WIDTH  				WIDTH / 4 + 3
 #define ECHECK_SELECT_FLAME_HEIGHT 				HEIGHT / 4
 #define ECHECK_SELECT_FLAME_X							WIDTH / 4 + 8
 #define ECHECK_SELECT_FLAME_Y      				3 * HEIGHT / 4
 #define ECHECK_TEMPLATE_FLAME_WIDTH  			WIDTH / 4 + 10
 #define ECHECK_TEMPLATE_FLAME_HEIGHT 			HEIGHT / 4
 #define ECHECK_TEMPLATE_FLAME_X      			WIDTH / 4 + 3
 #define ECHECK_TEMPLATE_FLAME_Y      			HEIGHT / 2 + 3

 #define SELECT_MODE_FLAME_HEIGHT_OFFSET 	2
 #define SCHECK_SELECT_FLAME_WIDTH  				WIDTH / 4
 #define SCHECK_SELECT_FLAME_HEIGHT 				HEIGHT / 4
 #define SCHECK_SELECT_FLAME_X      				WIDTH / 4 + 8
 #define SCHECK_SELECT_FLAME_Y      				HEIGHT / 2 - 6
 #define SELECT_MODE_EQIP_FLAME_WIDTH			WIDTH / 2 - 6
 #define SELECT_MODE_POTION_FLAME_HEIGHT		3
 #define SELECT_MODE_EQIP_FLAME_HEIGHT			6
 #define SELECT_MODE_EQIP_FLAME_X					3 + WIDTH / 2 + 2
 #define SELECT_MODE_EQIP_FLAME_Y					SELECT_MODE_FLAME_HEIGHT_OFFSET
 #define SELECT_MODE_EQIP_CHARASET_X				SELECT_MODE_EQIP_FLAME_X + SELECT_MODE_EQIP_FLAME_WIDTH - 2

 #define CHARACTER_STATUS_ATK_DIFF 				10
 #define CHARACTER_STATUS_HP_DIFF 					20

 #define SET_WEAPON_MODE_FLAME_WIDTH 			18
 #define SET_WEAPON_MODE_FLAME_HEIGHT 			7
 #define SET_WEAPON_MODE_FLAME_X 					(WIDTH - SET_WEAPON_MODE_FLAME_WIDTH) / 2
 #define SET_WEAPON_MODE_FLAME_Y 					(HEIGHT - SET_WEAPON_MODE_FLAME_HEIGHT) / 2
 #define SET_WEAPON_EDIT_FLAME_CHAR_X 			5
 #define SET_WEAPON_EDIT_FLAME_CHAR_Y 			13

 #define EDIT_EQIP_SELECT_FLAME_X					2
 #define EDIT_EQIP_SELECT_FLAME_Y					2
 #define EDIT_EQIP_SELECT_FLAME_WIDTH			(WIDTH - 2)
 #define EDIT_EQIP_SELECT_FLAME_HEIGHT			(HEIGHT - 2) / 3
 #define EDIT_EQIP_EDIT_FLAME_X						2
 #define EDIT_EQIP_EDIT_FLAME_Y						EDIT_EQIP_SELECT_FLAME_HEIGHT + 1
 #define EDIT_EQIP_EDIT_FLAME_WIDTH				(WIDTH - 2)
 #define EDIT_EQIP_EDIT_FLAME_HEIGHT				2* (HEIGHT - 2) / 3

 #define ARIST_ATTACK		35
 //タイトル画面の星の数
 #define STAR_AMOUNT 		50

 //キャラクターステータス設定定数
 #define FRONT1_NAME				"Lirel"
 #define FRONT1_HP					110
 #define FRONT1_MINATK			15
 #define FRONT1_MAXATK			20
 #define FRONT2_NAME				"Naoki"
 #define FRONT2_HP_ST2			90
 #define FRONT2_MINATK_ST2	20
 #define FRONT2_MAXATK_ST2	35
 #define FRONT2_HP_ST3			110
 #define FRONT2_MINATK_ST3	30
 #define FRONT2_MAXATK_ST3	45
 #define FRONT2_HP_ST4			130
 #define FRONT2_MINATK_ST4	40
 #define FRONT2_MAXATK_ST4	55
 #define FRONT3_NAME				"Robo1"
 #define FRONT3_HP					2000
 #define FRONT3_MINATK			140
 #define FRONT3_MAXATK			150
 #define FRONT3_SP_DAMAGE	1500
 #define FRONT4_NAME				"Robo2"
 #define FRONT4_HP					5000
 #define FRONT4_MINATK			400
 #define FRONT4_MAXATK			450
 #define BACK_NAME					"Arist"
 #define BACK_HP_ST1				70
 #define BACK_HEAL_ST1 		20
 #define BACK_HP_ST2				90
 #define BACK_HEAL_ST2 		30
 #define BACK_HP_ST3				110
 #define BACK_HEAL_ST3 		40
 #define BACK_HP_ST4				130
 #define BACK_HEAL_ST4 		50
 #define ST1_BOSS_NAME			"St1Bs"
 #define ST1_BOSS_HP				100
 #define ST1_BOSS_MINATK		10
 #define ST1_BOSS_MAXATK		20
 #define ST2_BOSS_NAME			"St2Bs"
 #define ST2_BOSS_HP				150
 #define ST2_BOSS_MINATK		30
 #define ST2_BOSS_MAXATK		40
 #define ST3_BOSS_NAME			"St3Bs"
 #define ST3_BOSS_HP				250
 #define ST3_BOSS_MINATK		50
 #define ST3_BOSS_MAXATK		60
 #define ST4_BOSS_NAME			"St4Bs"
 #define ST4_BOSS_HP				1000
 #define ST4_BOSS_MINATK		100
 #define ST4_BOSS_MAXATK		130
 #define ST5_BOSS_NAME			"St5Bs"
 #define ST5_BOSS_HP				3000
 #define ST5_BOSS_MINATK		300
 #define ST5_BOSS_MAXATK		400

//必要キャラクタ-の定義
struct character naoki;
struct character lirel;
struct character arist;
struct character robo;
struct character boss1;
struct character boss2;
struct character dummy;

//装備枠の宣言
struct weapon *using_weapon;
struct protector *using_protector;
struct weapon *arist_using_weapon;
struct protector *arist_using_protector;
int potion_amount = 0;

#include <windows.h>
#include <conio.h>

//WindowsとUNIXでEnterキーの入力が異なるのでプログラム上の表記を統一
#define ENTERKEY 0x0d

/**
  * Windowsにはマイクロ秒でsleepするusleep(int)がないので
  * time 処理を停止する時間[ms]
  */
void usleep(int time){
	Sleep(time/1000);
}

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
 void print_lines(char *string[], int x, int y, int num_lines){
 	for(int i = 0; i < num_lines; i++){
 		print_line(string[i],x,y+i);
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
  *  ステータス関連関数
  */

/**
  * キャラクターの基本ステータス構造体
  */
struct character{
	char *name;
	int hp;
	int max_hp;
	int max_atk;
	int min_atk;
};

/**
  * 武器の基本ステータス構造体
  */
struct weapon{
	char *name;
	int atk;
	int is_gun;
};

#define WEPONS_AMOUNT		3
#define WEPONS_AMOUNT_BACK	2

struct weapon all_weapons[7] = {
	{"No weapon",0,0},
	{"HandGun",15,1},
	{"Knife",5,0},
	//{"Bow",15,1}
};

struct weapon all_weapons4back[7] = {
	{"No weapon",0,0},
	{"Bow",10,1}
};
/**
  * 防具の基本ステータス構造体
  */
struct protector{
	char *name;
	int def;
};

#define PROTECTORS_AMOUNT 3

struct protector all_protectors[7] = {
	{"No protector",0},
	{"Shield",10},
	{"Protective Suit",30}
};

/**
 * 武器のステータス設定をする関数
 * tmpwp    ステータスを設定する武器構造体のアドレス
 * atk      武器の攻撃力
 * is_gun  	銃かどうかのフラグ
 */
void set_weapon_stat(struct weapon *tmpwp, int atk, int is_gun){
	tmpwp->atk = atk;
	tmpwp->is_gun = is_gun;
}

/**
 * 防具のステータス設定をする関数
 * tmppr    ステータスを設定する武器構造体のアドレス
 * def      武器の攻撃力
 */
void set_protector_stat(struct protector *tmppr, int def){
	tmppr->def = def;
}

/**
  * キャラクターのステータス設定をする関数
  * name[10] キャラクターの名前
  * tmpch    ステータスを設定するキャラクター構造体のアドレス
  * hp       設定するhp
  * min_atk  与ダメージの下限
  * max_atk  与ダメージの上限
  */
void set_ch_stat(char name[10], struct character *tmpch, int hp, int min_atk, int max_atk){
	tmpch->name = name;
	tmpch->hp = hp;
	tmpch->max_hp = hp;
	tmpch->max_atk = max_atk;
	tmpch->min_atk = min_atk;
}

/**
  * キャラクターのHPを変動させる関数
  * tmpch    hpが変動するキャラクター構造体のアドレス
  * damage   ダメージ量 正なら減算/負なら加算される ex.damageが-20 → 20回復
  */
void change_hp(struct character *tmpch, int damage){
	tmpch->hp -= damage;
	if(tmpch->hp < 0){
		tmpch->hp = 0;
	}else if(tmpch->hp > tmpch->max_hp){
		tmpch->hp = tmpch->max_hp;
	}
}

/*
 * 矢印の位置を定義するための構造体。リスト表示の際に座標配列として使う
 * int x			x座標
 * int y			y座標
 * int not_active	対象の座標が移動可能かのフラグ(1なら移動不可)
 */
struct arrow_pos{
	int x;
	int y;
	int not_active;
  int at_event;
};

/**
  * リストを表示した際にカーソルの縦移動と決定した項目を管理する関数
  * tmp_pos[10] カーソルを表示する位置を定義したarrow_pos型の配列
  * length      リスト項目の数
  * 戻り値 length/Enterが押されたときの項目のラベル(何個目のメニューだったか)
  */
int select_from_list(struct arrow_pos tmp_pos[10], int length){
	int arrow_pos_label = 0;
	struct input_assort tmp_input_list;
	print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
	while(1){
		while(!(tmp_input_list = mykbhit()).kbhit_flag);
		switch(tmp_input_list.input_char){
			case 'w':
				print_line(" ",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				if(arrow_pos_label <= 0){
					arrow_pos_label = length - 1;
				}else{
					arrow_pos_label--;
				}
				print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				continue;
				break;
			case 's':
				print_line(" ",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				if(arrow_pos_label >= length - 1){
					arrow_pos_label = 0;
				}else{
					arrow_pos_label++;
				}
				print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				continue;
				break;
			case ENTERKEY:
				break;
			default:
				continue;
				break;
		}
		break;
	}
	return arrow_pos_label;
}

/**
  * リストを表示した際にカーソルの横移動と決定した項目を管理する関数
  * tmp_pos[10] カーソルを表示する位置を定義したarrow_pos型の配列
  * length      リスト項目の数
  * 戻り値 length/Enterが押されたときの項目のラベル(何個目のメニューだったか)
  */
int select_from_hlist(struct arrow_pos tmp_pos[10], int length){
	int arrow_pos_label = 0;
	struct input_assort tmp_input_list;
	print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
	while(1){
		while(!(tmp_input_list = mykbhit()).kbhit_flag);
		switch(tmp_input_list.input_char){
			case 'a':
				print_line(" ",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				if(arrow_pos_label <= 0){
					arrow_pos_label = length - 1;
				}else{
					arrow_pos_label--;
				}
				print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				continue;
				break;
			case 'd':
				print_line(" ",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				if(arrow_pos_label >= length - 1){
					arrow_pos_label = 0;
				}else{
					arrow_pos_label++;
				}
				print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				continue;
				break;
			case ENTERKEY:
				break;
			default:
				continue;
				break;
		}
		break;
	}
	return arrow_pos_label;
}

/*
 * リストを表示した際にカーソルの二次元移動と決定した項目を管理する関数
 * tmp_pos[10][10]	カーソルを表示する位置を定義したarrow_pos型の配列
 * length			リスト項目の数
 * 戻り値
 * int length		Enterが押されたときの項目のラベル(何個目のメニューだったか)
 */
int select_from_2dlist(int width, int height,struct arrow_pos tmp_pos[width][height]){
	struct arrow_pos arrow_pos_label = {0,0};
	struct input_assort tmp_input_list;
	print_line(">",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
	while(1){
		while(!(tmp_input_list = mykbhit()).kbhit_flag);

		print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
		switch(tmp_input_list.input_char){
			case 'w':
				do{
					if(arrow_pos_label.y <= 0){
						arrow_pos_label.y = height - 1;
					}else{
						arrow_pos_label.y--;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y].not_active);
				print_line(">",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
				continue;
				break;
			case 's':
				do{
					if(arrow_pos_label.y >= height - 1){
						arrow_pos_label.y= 0;
					}else{
						arrow_pos_label.y++;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y].not_active);
				print_line(">",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
				continue;
				break;
			case 'a':
				do{
					if(arrow_pos_label.x <= 0){
						arrow_pos_label.x = width - 1;
					}else{
						arrow_pos_label.x--;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y].not_active);
				print_line(">",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
				continue;
				break;
			case 'd':
				do{
					if(arrow_pos_label.x >= width - 1){
						arrow_pos_label.x= 0;
					}else{
						arrow_pos_label.x++;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y].not_active);
				print_line(">",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
				continue;
				break;
			case ENTERKEY:
				break;
			default:
				continue;
				break;
		}
		break;
	}
	return arrow_pos_label.x + width * arrow_pos_label.y;
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
struct arrow_pos move_on_map(int width, int height,struct arrow_pos *(tmp_pos)[WIDTH -2 ][HEIGHT - 2], struct arrow_pos offset){
	struct arrow_pos arrow_pos_label = offset;
	struct input_assort tmp_input_list;
	print_line("◯",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
	while(1){
		while(!(tmp_input_list = mykbhit()).kbhit_flag);

		print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
		switch(tmp_input_list.input_char){
			case 'w':
				do{
					if(arrow_pos_label.y <= 0 || tmp_pos[arrow_pos_label.x][arrow_pos_label.y - 1]->not_active){
						//arrow_pos_label.y = height - 1;
					}else{
						arrow_pos_label.y--;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->not_active);
				print_line("◯",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				if(tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->at_event){
					break;
				}
				continue;
				break;
			case 's':
				do{
					if(arrow_pos_label.y > height - 2 || tmp_pos[arrow_pos_label.x][arrow_pos_label.y + 1]->not_active){
						//arrow_pos_label.y= 0;
					}else{
						arrow_pos_label.y++;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->not_active);
				print_line("◯",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);

				if(tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->at_event){
					break;
				}
				continue;
				break;
			case 'a':
				do{
					if(arrow_pos_label.x <= 0 || tmp_pos[arrow_pos_label.x - 1][arrow_pos_label.y]->not_active){
						//arrow_pos_label.x = width - 1;
					}else{
						arrow_pos_label.x--;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->not_active);
				print_line("◯",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				if(tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->at_event){
					break;
				}
				continue;
				break;
			case 'd':
				do{
					if(arrow_pos_label.x > width - 2 || tmp_pos[arrow_pos_label.x + 1][arrow_pos_label.y]->not_active){
						//arrow_pos_label.x= 0;
					}else{
						arrow_pos_label.x++;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->not_active);
				print_line("◯",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				if(tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->at_event){
					break;
				}
				continue;
				break;
			case ENTERKEY:
				break;
			default:
        print_line("◯",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				continue;
				break;
		}
		break;
	}
	return arrow_pos_label;
}


int check_window(int width, int height, int x, int y, char *string){
	struct arrow_pos yesno_pos[2] = {
		{x + width / 2 + 2,y+3},
		{x + width / 2 - 3,y+3}
		};
	make_flame(width,height,x,y);
	mvcur(x+2,y+1);
	printf("%s",string);
	print_line("y /  n",x + width / 2 - 2,y+3);
	return select_from_hlist(yesno_pos,2);
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

/**
  *  操作説明の出方が違うのでヘッダで定義
  */
char control_explain[][100] = {
	"  w            ↑   ",
	"a s d   as  ← ↓ →"
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
void maintitle(){
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
	print_line("for PaperTest Ver",(WIDTH - 17)/2,14);
	print_line("Press Enter",25,HEIGHT - 4);
	fflush(stdout);
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
				mvcur(1,HEIGHT+1);
				//今の変数に乱数を振り直すため、ラベルを減算
				i--;
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
}

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
	*	座標情報をコピーする関数
	*/
void coorcpy(struct arrow_pos *(to)[WIDTH - 2][HEIGHT - 2],struct arrow_pos from[WIDTH - 2][HEIGHT - 2]){
	for(int i = 0; i < WIDTH - 2; i++){
		for(int j = 0; j < HEIGHT - 2; j++){
			to[i][j] = &from[i][j];
		}
	}
}

/*
 * 戦闘系関数ここから
 */

//戦闘モードの時にコマンド部分表示する関数
void print_bt_commands(){
	print_line("Attack",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
	print_line("Special",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
	print_line("Protect",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3);
	print_line("Item",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 4);
	fflush(stdout);
}

//敵のHPゲージを描画する関数
void print_health_bar(struct character *target[],int amount){
	double health_par = 0;
	for(int i = 0; i < amount; i++){
		make_flame(20,3,2,2 + 3 * i);
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
void print_bt_status(struct character *front,struct character *back){
	//ステータス部分表示
	char *(spaces)[] = {
		"               ",
		"               "
	};
	print_lines(spaces,BATTLE_MODE_STATUS_HP_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,2);
	print_line("HP",BATTLE_MODE_STATUS_HP_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
	mvcur(BATTLE_MODE_STATUS_HP_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
	printf("%s:%4d/%4d",front->name,front->hp,front->max_hp);
	if(strcmp(back->name,"dummy")){
		mvcur(BATTLE_MODE_STATUS_HP_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3);
		printf("%s:%4d/%4d",back->name,back->hp,back->max_hp);
	}
	mvcur(0,HEIGHT + 1);
	fflush(stdout);
}

//戦闘モード
int battle(struct character *front,struct character *back,struct character *enemies[3], int enemy_amount){
	int finish_flag = 0;												//戦闘終了のフラグ
	int protect_flag = 0;												//かばう行動のフラグ
	int damage = 0;															//計算後のダメージを記憶する変数
	int target_label = 0;												//攻撃対象を判断するための変数
	int turn_count = 1;													//特殊行動のため戦闘開始からのターンを数える変数
	int sp_count = 0;														//特殊行動の行動不能ターンを数える変数
	int enemies_dead_check = 0;									//敵が全滅したかどうかチェックする時に使う変数
	int player_can_act = 1;											//プレイヤーが行動可能かのフラグ
	int used_flare = 0;													//ステージ5での味方特殊行動の使用後フラグ
	int enemy_amount_for_bar = enemy_amount;		//HPゲージ描画のため、本来の敵の数を記憶する変数
	struct character *for_bar[enemy_amount];		//HPゲージ描画のため、本来の敵のアドレスを記憶する変数
	for(int i = 0;i < enemy_amount;i++){
		for_bar[i] = enemies[i];
	}
	struct arrow_pos battle_menu_arrow[] = {
		{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1},
		{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2},
		{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3},
		{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 4}
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
		if(player_can_act){
			print_bt_commands();
			int command = select_from_list(battle_menu_arrow,4);
			//コマンド部分フレームクリーン
			sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			switch(command){
				case 0:
					for(int i = 0; i <= enemy_amount; i++){
						mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1 + i);
						if(i < enemy_amount){
							printf("%s",enemies[i]->name);
						}else{
							printf("back");
						}
					}
					fflush(stdout);
					target_label = select_from_list(battle_menu_arrow,enemy_amount + 1);
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					if(target_label == enemy_amount){
						continue;
					}
					if(!strcmp(front->name,"Naoki") || !strcmp(front->name,"Lirel")){
						damage = front->min_atk + rand() % (front->max_atk - front->min_atk - 1) + using_weapon->atk;
					}else{
						damage = front->min_atk + rand() % (front->max_atk - front->min_atk - 1);
					}
					mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					printf("%s got %3d damaged!▼",enemies[target_label]->name,damage);
					change_hp(enemies[target_label],damage);
					if(using_weapon->is_gun && !strcmp(front->name,"Naoki")){
						damage = front->min_atk + rand() % (front->max_atk - front->min_atk - 1) + using_weapon->atk;
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
						printf("%s got %3d damaged!▼",enemies[target_label]->name,damage);
						change_hp(enemies[target_label],damage);
					}
					print_health_bar(for_bar,enemy_amount_for_bar);
					wait_anyinput();
					if(enemies[target_label]->hp <= 0){
						sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						printf("%s was down!▼",enemies[target_label]->name);
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
						printf("back");
						fflush(stdout);
						target_label = select_from_list(battle_menu_arrow,1);
					}else{
						if(!strcmp(front->name,FRONT3_NAME)){
							printf("Caladbolg");
						}else if(!strcmp(front->name,FRONT4_NAME)){
							printf("Flare");
						}
						mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);	
						printf("back");
						fflush(stdout);
						target_label = select_from_list(battle_menu_arrow,2);
					}
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					if((strstr(front->name,"Robo") == NULL && target_label == 0) || target_label == 1){
						continue;
					}else if(target_label == 0){
						if(!strcmp(front->name,FRONT3_NAME)){
							if(turn_count < 5){
								print_line("Caladbolg can use since turn 5▼ ",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								wait_anyinput();
								sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								continue;
							}else{
								mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								printf("%s use Caladbolg!▼",front->name);
								wait_anyinput();
								mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
								wait_anyinput();
								/*敵ダメージ処理ここから*/
								for(int i = 0; i < enemy_amount; i++){
									sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
									change_hp(enemies[i],FRONT3_SP_DAMAGE);
									mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
									printf("%s got %4d damaged!▼",enemies[i]->name,FRONT3_SP_DAMAGE);
									print_health_bar(for_bar,enemy_amount_for_bar);
									wait_anyinput();
									/*敵ダメージ処理ここまで*/
									/*敵死亡判定ここから*/
									if(enemies[i]->hp <= 0){
										sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
										mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
										printf("%s was down!▼",enemies[target_label]->name);
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
								print_line("Flare can use since turn 3▼ ",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								wait_anyinput();
								sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								continue;
							}else if(!used_flare){
								mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								printf("%s use Flare!▼",front->name);
								used_flare = 1;
								wait_anyinput();
								/*敵ダメージ処理ここから*/
								for(int i = 0; i < enemy_amount; i++){
									sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
									mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
									printf("%s got %4d damaged!▼",enemies[i]->name,enemies[i]->hp / 2);
									change_hp(enemies[i],enemies[i]->hp / 2);
									print_health_bar(for_bar,enemy_amount_for_bar);
									wait_anyinput();
									/*敵ダメージ処理ここまで*/
									/*敵死亡判定ここから*/
									if(enemies[i]->hp <= 0){
										sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
										mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
										printf("%s was down!▼",enemies[target_label]->name);
										for(int i = target_label; i + 1 < enemy_amount;i++){
											enemies[i] = enemies[i + 1];
										}
										enemy_amount--;
										wait_anyinput();
									}
								}
								/*敵死亡判定ここまで*/
							}else{
								print_line("Flare can use only once▼ ",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
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
					printf("%s is ready to protect!▼",front->name);
					wait_anyinput();
					break;
				case 3:
					for(int i = 0; i <= potion_amount; i++){
						mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1 + i);
						if(i < potion_amount){
							printf("potion");
						}else{
							printf("back");
						}
						fflush(stdout);
					}
					target_label = select_from_list(battle_menu_arrow,potion_amount + 1);
					if(target_label < potion_amount){
						sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						change_hp(front,-1 * front->max_hp);
						change_hp(&arist,-1 * arist.max_hp);
						print_bt_status(front,back);
						print_line("use potion!▼ ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						potion_amount--;
						wait_anyinput();
					}else{
						sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						continue;
					}
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					break;
				default:
					break;
			}
			sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			//プレイヤーの行動終わり
			print_health_bar(for_bar,enemy_amount_for_bar);

			//勝利判定
			enemies_dead_check = 0;
			for(int i = 0; i <  enemy_amount_for_bar; i++){
				enemies_dead_check += for_bar[i]->hp;
			}
			if(enemies_dead_check <= 0){
				print_line("Win!▼",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				finish_flag = 1;
				return 1;
				wait_anyinput();
				continue;
			}
			//判定終わり

			//後衛の行動
			if(strcmp(back->name,"dummy")){
				switch(rand() % 4){
					case 0:
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						printf("%s was terrified...▼",back->name);
						wait_anyinput();
						break;
					case 1:
						if(!strcmp(arist_using_weapon->name,"Bow")){
							print_line("Arist's Rainbow Arrow!▼",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
							wait_anyinput();
							damage = (ARIST_ATTACK);
							target_label = rand() % enemy_amount;
							change_hp(enemies[target_label],damage);
							mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
							printf("%s got %3d damaged!▼ ",enemies[target_label]->name,damage);
							print_health_bar(for_bar,enemy_amount_for_bar);
							wait_anyinput();
							break;
						}
					default:
						change_hp(front,-1 * arist.max_atk);
						change_hp(back,-1 * arist.max_atk);
						print_bt_status(front,back);
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						printf("Arist cast 'heal'!▼ ");
						wait_anyinput();
						break;
				}
			}
			sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			//後衛の行動終わり
		}else{
			print_line("Can't Action...▼ ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			wait_anyinput();
			sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			for(int i = 0; i < enemy_amount; i++){
				if(!strcmp(enemies[i]->name,"St3Bs")){
					player_can_act = 1;
				}else if(!strcmp(enemies[i]->name,"St5Bs")){
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
			print_line("Win!▼",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			finish_flag = 1;
			return 1;
			wait_anyinput();
			continue;
		}
		//判定終わり

		//敵の行動
		for(int i = 0; i < enemy_amount; i++){
			if(enemies[i]->hp > 0){
				if(!strcmp(enemies[i]->name,ST3_BOSS_NAME) && turn_count == 6){
					print_line("Ancient Gear Golem's action!▼ ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);		
					wait_anyinput();
					print_line("Ultimate bound!▼ ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);		
					wait_anyinput();
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					mvcur(BATTLE_MODE_COMMAND_POS - 2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);		
					printf("Next turn,Players can't action...▼ ");	
					fflush(stdout);
					wait_anyinput();
					player_can_act = !player_can_act;
				}else if(!strcmp(enemies[i]->name,ST4_BOSS_NAME) && rand() % 10 == 5){
					change_hp(enemies[i],-500);
					print_line("Stage4 Boss cast 'Curala'!▼ ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);		
					wait_anyinput();
				}else if(!strcmp(enemies[i]->name,"St5Bs") && turn_count != 0 && turn_count % 4 == 0){
					print_line("Stage5 Boss's action!▼ ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);		
					wait_anyinput();
					print_line("The Gaia!▼ ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
					wait_anyinput();
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					char *(string)[] = {
						"in 3 turn,",
						"        Players can't action...▼ "
					};
					print_lines(string,BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,2);
					fflush(stdout);
					wait_anyinput();
					player_can_act = !player_can_act;
				} else if(!strcmp(enemies[i]->name,ST5_BOSS_NAME) && rand() % 10 == 5 && enemies[i]->hp < enemies[i]->max_hp * 0.25){
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
						printf("%s get %3d damaged by %s!▼",front->name,damage,enemies[i]->name);
						change_hp(front,damage);
					}else{
						switch((int)(rand() % 2)){
							case 0:
								mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								printf("%s get %3d damaged by %s!▼",back->name,damage,enemies[i]->name);
								change_hp(back,damage);
								break;
							default:
								mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								printf("%s get %3d damaged by %s!▼",front->name,damage,enemies[i]->name);
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

int deside_event(struct arrow_pos){
	
	return 0;
}
