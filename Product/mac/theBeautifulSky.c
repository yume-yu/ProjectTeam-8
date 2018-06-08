#include "for_make_game.h"
#include "map_st2.h"

struct arrow_pos *(now_map_coor)[WIDTH - 2][HEIGHT - 2];
struct arrow_pos start_pos = {(WIDTH - 2)/2 - 2,(HEIGHT - 2)-1,0,0};
char *(now_map)[23];

int main(){
	//now_map = string;
	coorcpy(now_map_coor,st2_pos);
	mapcpy(now_map,map_st2);
	//キャラクターの初期化
	//initchara();
	//コンソールの初期化
	init_term();
	//メインフレーム描画
	make_flame(WIDTH,HEIGHT,MAIN_FLAME_X,MAIN_FLAME_Y);
	//タイトル画面表示
	maintitle();
	//アニメーション付きフレームクリーン
	flame_flush();
	//シナリオ表示？
	//scenario();
	while(1){
		print_lines(now_map,2,2,23);
		fflush(stdout);
		move_on_map(WIDTH - 2, HEIGHT - 2, now_map_coor,start_pos);
		flame_flush();
	}
	/*
	while(flag){
		//マップ上を歩いて、イベントマスを通ったら分岐
		switch(decide_event(move_on_map(座標とか))){
			//戦闘だったら
			case battle_event:
				//勝ったか
				if(buttle(敵)){
					if(ステージボスか){
						if(ラスボスか){
							クリアフラグを立てる
						}else{
							マップの更新
						}
					}else{
						なにもしない
					}
				}else{
					負け
				}
				break;
			//会話イベントだったら
			case talk_event:
				talk_event();
				break;
			default:
				break;
		}
	}
	*/
}
