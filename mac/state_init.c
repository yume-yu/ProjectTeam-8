/**
 * @file		state_init.c
 * @brief		ゲームの設定を初期化する関数を書いたファイル
 * @author	yume_yu
 * @date		2018/08/12
 */

#include "theBeautifulSky.h"


char *(maps)[10][HEIGHT - 2];												//全ステージのマップ図
arrow_pos *(map_coors)[10][WIDTH - 2][HEIGHT - 2];	//全ステージのマップ座標
stage now_stage;																		//現在のステージ
char *(now_map)[WIDTH - 2];												//現在のマップ図
arrow_pos *(now_map_coor)[WIDTH - 2][HEIGHT - 2];	//現在のマップ座標
int room_id;																				//侵入した部屋のid
arrow_pos start_pos;																//マップ描画時のキャラクターの初期位置
extendstr *now_text[HEIGHT];												//アニメーションで表示する文字列

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
