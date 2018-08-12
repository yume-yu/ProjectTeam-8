/**
 * @file		state_init.c
 * @brief		ゲームの設定を初期化する関数を書いたファイル
 * @author	yume_yu
 * @date		2018/08/12
 */

#include "thebeautifulsky.h"

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
