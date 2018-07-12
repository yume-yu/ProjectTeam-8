/**
 * @file thebeautifulsky.h
 * @brief ゲーム｢thebeautifulsky｣のヘッダ
 * @author yume_yu
 * @date 2018/07/08
 */

//多重インクルード防止
#pragma once

/**
 * コンパイルするOSの宣言
 * Windows系	WINDOWS
 * mac/Linux	MAC
 */
#define WINDOWS

/* 使用するヘッダのインクルード */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

//OSに依存するライブラリをここに書く
#if defined WINDOWS

#include <windows.h>						//カーソル移動SetConsoleCursorPosition等
#include <conio.h>							//kbhit(),getch()など

#define ENTERKEY 0x0d						//Enterキーの入力の統一表記
#define MULTIBYTE_CHAR_SIZE 2		//マルチバイト文字の大きさの統一表記(文字コード?)

#elif defined MAC

#include "mconio.h"

#define ENTERKEY '＼n'						//Enterキーの入力の統一表記
#define MULTIBYTE_CHAR_SIZE 3		//マルチバイト文字の大きさの統一表記(文字コード?)

#endif


/* 定数の定義(define) */

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
#define BATTLE_MODE_STATUS_FLAME_SPLIT_X 	2*(WIDTH-2)/3-1 -2
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

//タイトル画面の星の数
#define STAR_AMOUNT 											50
#define TITLE_MENU_BASE_X									(WIDTH - 24)/2
#define TITLE_MENU_BASE_Y									HEIGHT - 5

/**
 *	@def
 *	マップ上のメニューに関する定数
 */
#define MAP_WIN_WIDTH		(WIDTH - 2) / 3
#define MAP_WIN_HEIGHT	6
#define MAP_WIN_X				WIDTH - 1 - MAP_WIN_WIDTH
#define MAP_WIN_Y				5

/**
 *	@def
 *	マップ上のステータスメニューに関する定数
 */
#define STAT_WIN_WIDTH		MAP_WIN_WIDTH  + 10
#define STAT_WIN_HEIGHT		8
#define STAT_WIN_X				MAP_WIN_X - (MAP_WIN_WIDTH + 10)

//キャラクターステータス設定定数
#define FRONT1_NAME				"リーレル"
#define FRONT1_HP					110
#define FRONT1_MINATK			15
#define FRONT1_MAXATK			20
#define FRONT2_NAME				"ナオキ"
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
#define BACK_NAME					"アリスト"
#define BACK_HP_ST1				70
#define BACK_HEAL_ST1 		20
#define BACK_HP_ST2				90
#define BACK_HEAL_ST2 		30
#define BACK_HP_ST3				110
#define BACK_HEAL_ST3 		40
#define BACK_HP_ST4				130
#define BACK_HEAL_ST4 		50
#define BACK_ATTACK				35
#define ST1_BOSS_NAME			"追手の操機兵"
#define ST1_BOSS_HP				100
#define ST1_BOSS_MINATK		10
#define ST1_BOSS_MAXATK		20
#define ST2_BOSS_NAME			"タクト"
#define ST2_BOSS_HP				150
#define ST2_BOSS_MINATK		30
#define ST2_BOSS_MAXATK		40
#define ST3_BOSS_NAME			"デジレ = シニジェ"
#define ST3_BOSS_HP				250
#define ST3_BOSS_MINATK		50
#define ST3_BOSS_MAXATK		60
#define ST4_BOSS_NAME			"古代の機械巨人"
#define ST4_BOSS_HP				1000
#define ST4_BOSS_MINATK		100
#define ST4_BOSS_MAXATK		130
#define ST5_BOSS_NAME			"ファール"
#define ST5_BOSS_HP				3000
#define ST5_BOSS_MINATK		300
#define ST5_BOSS_MAXATK		400
#define ST2_WEAK_NAME			"リトルワイバーン"
#define ST31_WEAK_NAME		"クレイジードッグ"
#define ST32_WEAK_NAME		"マッドドッグ"
#define ST41_WEAK_NAME		"羽を失いしもの A"
#define ST42_WEAK_NAME		"羽を失いしもの B"


/* 構造体の宣言 */

// arrow_pos	座標を管理するための構造体。リスト表示やマップ上で、配列にして使う
typedef struct {
	int x;							//x座標
	int y;							//y座標
	bool not_active;		//移動可能な座標かどうか
	bool at_event;			//イベントが有るマスかどうか
} arrow_pos;

// character	キャラクターの基本ステータス構造体
typedef struct {
	char *name;					//名前
	int hp;							//現在の体力
	int max_hp;					//体力の最大値
	int max_atk;				//与ダメージの上限
	int min_atk;				//与ダメージの下限
} character;

// weapon 武器の基本ステータス構造体
typedef struct {
	char *name;					//名前
	int atk;						//与ダメージ増加分
	bool is_gun;				//銃であるかどうか
} weapon;

// protector 防具の基本ステータス構造体
typedef struct {
	char *name;					//名前
	int def;						//防御力の増加分
} protector;

// extendstr ストーリー等表示文字列の構造体
typedef struct {
	char string[100];		//表示する文字列
	int offset;					//表示位置の右ずらしオフセット
	int not_need_return;//入力を待つ行であるかのフラグ
} extendstr;

// input_assort 入力を扱う構造体
typedef struct {
	bool kbhit_flag;		//キーが押されているかを返すフラグ
	int input_char;			//入力されたキー
} input_assort;

// stage マップを表す列挙
typedef enum {
	stage1,
	stage2,
	stage3_1,
	stage3_2,
	stage3_3,
	stage4_1,
	stage4_2,
	stage4_3,
	stage5,
	ope_exp
} stage;

// event マップで起こるイベントを表す列挙
typedef enum {
	battle_event, //戦闘イベント
	talk_event,		//会話イベント
	move_map,			//マップ間の移動
	open_menu			//メニューを開く
} event;

/* 定数の定義(const) */


/* グローバル関数宣言 */

//必要キャラクタ-の定義
extern character naoki;
extern character lirel;
extern character arist;
extern character robo;
extern character boss1;
extern character boss2;
extern character dummy;
extern character *front;
extern character *back;
extern character *(enemies)[3];

//戦闘時の敵の数
extern int enemy_amount;

//装備と装備枠
extern weapon all_weapons[7];							//全前衛武器の宣言
extern weapon all_weapons4back[7];				//全後衛武器の宣言
extern protector all_protectors[7];				//全防具の宣言
extern weapon *using_weapon;							//前衛の武器
extern protector *using_protector;				//前衛の防具
extern weapon *arist_using_weapon;				//後衛の武器
extern protector *arist_using_protector;	//後衛の防具
extern int potion_amount;									//所持しているポーションの数
extern int have_nasu;											//所持しているナスの数

//ステージ管理/マップ管理
extern char *(maps)[9][HEIGHT - 2];												//全ステージのマップ図
extern arrow_pos *(map_coors)[10][WIDTH - 2][HEIGHT - 2];	//全ステージのマップ座標
extern stage now_stage;																		//現在のステージ
extern char *(now_map)[WIDTH - 2];												//現在のマップ図
extern arrow_pos *(now_map_coor)[WIDTH - 2][HEIGHT - 2];	//現在のマップ座標
extern int room_id;																				//侵入した部屋のid
extern arrow_pos start_pos;																//マップ描画時のキャラクターの初期位置
extern extendstr *now_text[HEIGHT];												//アニメーションで表示する文字列

/* ここからmap_stX.cで定義する変数 */

//マップ変数
extern char *(map_st1)[WIDTH - 2];
extern char *(map_st2)[WIDTH - 2];
extern char *(map_st3_1)[WIDTH - 2];
extern char *(map_st3_2)[WIDTH - 2];
extern char *(map_st3_3)[WIDTH - 2];
extern char *(map_st4_1)[WIDTH - 2];
extern char *(map_st4_2)[WIDTH - 2];
extern char *(map_st4_3)[WIDTH - 2];
extern char *(map_exp)[WIDTH - 2];

//マップ座標変数
extern arrow_pos st1_pos[WIDTH - 2][HEIGHT - 2] ;
extern arrow_pos st2_pos[WIDTH - 2][HEIGHT - 2] ;
extern arrow_pos st3_1_pos[WIDTH - 2][HEIGHT - 2];
extern arrow_pos st3_2_pos[WIDTH - 2][HEIGHT - 2];
extern arrow_pos st3_3_pos[WIDTH - 2][HEIGHT - 2];
extern arrow_pos st4_1_pos[WIDTH - 2][HEIGHT - 2];
extern arrow_pos st4_2_pos[WIDTH - 2][HEIGHT - 2];
extern arrow_pos st4_3_pos[WIDTH - 2][HEIGHT - 2];
extern arrow_pos exp_pos[WIDTH - 2][HEIGHT - 2] ;

/* ここまでmap_stX.cで定義する変数 */

/* ここからstorytext.cで定義する*/
extern extendstr subtitle1[];
extern extendstr subtitle2[];
extern extendstr subtitle3[];
extern extendstr subtitle4[];
extern extendstr subtitle5[];
extern extendstr cenario_stage1[];
extern extendstr lirel_said[];
extern extendstr lirel_stop[];
extern extendstr beforebattle_stage1[];
extern extendstr afterbattle_stage1[];
extern extendstr cenario_stage2[];
extern extendstr talk_st2_0_1[];
extern extendstr talk_st2_0_2[];
extern extendstr beforebattle_stage2[];
extern extendstr afterbattle_stage2[];
extern extendstr cenario_stage3[];
extern extendstr talk_st3_0[];
extern extendstr talk_st3_1[];
extern extendstr talk_st3_1_1[];
extern extendstr talk_st3_1_3[];
extern extendstr talk_st3_1_2[];
extern extendstr talk_st3_2[];
extern extendstr talk_st3_2_1[];
extern extendstr talk_st3_2_2[];
extern extendstr talk_st3_2_3[];
extern extendstr talk_st3_3[];
extern extendstr talk_st3_3_0[];
extern extendstr talk_st3_3_1[];
extern extendstr talk_st3_3_2[];
extern extendstr talk_st3_3_3[];
extern extendstr talk_st3_5_1[];
extern extendstr talk_st3_5_2[];
extern extendstr talk_st3_5_3[];
extern extendstr talk_st3_6[];
extern extendstr beforebattle_stage3[];
extern extendstr afterbattle_stage3[];
extern extendstr cenario_stage4[];
extern extendstr talk_st4_0[];
extern extendstr talk_st4_0_1[];
extern extendstr talk_st4_0_2[];
extern extendstr talk_st4_0_3[];
extern extendstr talk_st4_1[];
extern extendstr talk_st4_1_1[];
extern extendstr talk_st4_1_2[];
extern extendstr talk_st4_1_3[];
extern extendstr talk_st4_3[];
extern extendstr talk_st4_5[];
extern extendstr talk_st4_6[];
extern extendstr beforebattle_stage4[];
extern extendstr afterbattle_stage4_1[];
extern extendstr afterbattle_stage4_2[];
extern extendstr afterbattle_stage4_3[];
extern extendstr cenario_stage5[];
extern extendstr afterbattle_stage5[];
/* ここまでstorytext.cで定義する*/

/* 関数マクロ定義 */
//char配列やextendstr配列の文字数/行数を返すマクロ
#define lengthof(var,type) (sizeof(var)/sizeof(type))

/* プロトタイプ宣言 */

/* ここからutil_func.cで定義する関数 */
#ifdef WINDOWS									//Windowsのときだけ必要な記述をこのifの中に入れる
void usleep(int time);					//usleepの表記統一のため
#endif

void mvcur(int x, int y);																												//カーソル移動を行う関数
input_assort mykbhit();																													//キー入力を取る関数
void wait_anyinput();																														//なにかキー入力を待つ関数
void wait_input_without_arrow();																								//AWSD以外のキー入力を待つ関数
void init_term();																																//ターミナルの初期化を行う関数
void print_line(char string[], int x, int y);																		//指定した座標を行頭にに1行出力する関数
void print_lines(char *string[], int x, int y, int num_lines);									//指定した座標を行頭に複数行出力する関数
void string_march(extendstr *(tmp)[],int x,int y,int lines);										//指定した座標を行頭に複数行アニメーション出力する関数
void exstrcpy(extendstr *(to)[],extendstr from[],int lines);										//アニメーション表示用構造体配列をアドレスの配列に変換する関数
int select_from_list(arrow_pos tmp_pos[10], int length);												//縦方向のリストから選択させる関数
int select_from_hlist(arrow_pos tmp_pos[10], int length);												//横方向のリストから選択させる関数
int select_from_2dlist(int width, int height,arrow_pos tmp_pos[width][height]);	//平面リストから選択させる関数
/* ここまでutil_func.cで定義する関数 */

/* ここからflame_func.cで定義する関数 */
void make_flame(int width, int height, int offset_x, int offset_y);								//指定位置を左上に高さと幅を指定したフレームを作成する関数
void make_vsflame(int width, int height, int offset_x, int offset_y, int split_x);//指定位置を左上に高さと幅と分割位置を指定した横2分割のフレームを作成する関数
void flame_flush();																																//メインフレーム内をアニメーション付きでスペース埋めする関数
void flame_clean();																																//メインフレーム内をアニメーションなしでスペース埋めする関数
void sub_flame_clean(int width, int height, int x, int y);												//指定範囲内をアニメーションなしでスペース埋めする関数
int check_window(int width, int height, int x, int y, char *string);							//確認文とy/nの確認フレームを出す関数
/* ここまでflame_func.cで定義する関数 */

/* ここからweapons_items.cで定義する関数 */
void set_weapon_stat(weapon *tmpwp, int atk, bool is_gun);												//武器のステータスを更新する関数
void set_protector_stat(protector *tmppr, int def);																//防具のステータスを更新する関数
bool get_potion();																																//ポーションを入手したときの関数
/* ここまでweapons_items.cで定義する関数 */

/* ここからcharacter.cで定義する関数 */
void set_ch_stat(char name[10], character *tmpch, int hp, int max_hp,int min_atk, int max_atk);	//キャラクターのステータスを更新する関数
void change_hp(character *tmpch, int damage);																										//キャラクターのダメージ/回復処理を行う関数
/* ここまでcharacter.cで定義する関数 */

/* ここからmap_func.cで定義する関数 */
void mapcpy(char *(to)[HEIGHT - 2],char *(from)[HEIGHT - 2]);																								//マップを別関数にコピーする関数
void coor_cnv_adr(arrow_pos *(to)[WIDTH - 2][HEIGHT - 2],arrow_pos from[WIDTH - 2][HEIGHT - 2]);						//マップ座標をアドレス配列にしてコピーする関数
void coorcpy(arrow_pos *(to)[WIDTH - 2][HEIGHT - 2],arrow_pos *(from)[WIDTH - 2][HEIGHT - 2]);							//マップ座標のアドレス配列をコピーする関数
arrow_pos move_on_map(int width, int height,arrow_pos *(tmp_pos)[WIDTH -2 ][HEIGHT - 2], arrow_pos offset);	//マップ上を移動する関数
/* ここまでmap_func.cで定義する関数 */

/* ここからmap_menu.cで定義する関数 */
void view_status();																																//マップメニューでステータスを表示する関数
void item_list_on_map();																													//マップメニューでアイテム一覧を表示する関数
int onmap_manu();																																	//マップメニューを開く関数
void update_map(stage now_stage);																									//表示するマップをステージに合わせて更新する関数
/* ここまでmap_menu.cで定義する関数 */

