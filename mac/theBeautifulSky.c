/*
#include "for_make_game.h"

struct extendstr *now_text[HEIGHT];

int main(){
//マップ/座標一覧の初期化
initmaps();
//キャラクターの初期化
initchara();
//コンソールの初期化
init_term();
//メインフレーム描画
make_flame(WIDTH,HEIGHT,MAIN_FLAME_X,MAIN_FLAME_Y);
//タイトル画面表示
//maintitle();
//アニメーション付きフレームクリーン
//flame_flush();
//シナリオ表示？
//scenario();

//準備してないので、ステージを1に
now_stage = stage1;
exstrcpy(now_text,cenario_stage1,story_lines[now_stage]);
//string_march(now_text,2,2,story_lines[now_stage]);
//flame_clean();
now_stage = stage2;
//暫定的にマップをセット
mapcpy(now_map,maps[now_stage]);
mapcpy(now_map,maps[now_stage]);
coorcpy(now_map_coor,map_coors[stage2]);
//coorcpy(now_map_coor,st2_pos);
printf("%lu\n",sizeof(struct extendstr));

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
#include "for_make_game.h"

void update_map(enum stage now_stage){
	mapcpy(now_map,maps[now_stage]);
	coorcpy(now_map_coor,map_coors[now_stage]);
}

void subtitle(struct extendstr nowsubtitle[]){
	int length = 0;
	for(int i = 0;i < 100; i++){
		if(nowsubtitle[0].string[i] == '\0'){
			length = i;
			break;
		}
	}
	exstrcpy(now_text,nowsubtitle,1);
	string_march(now_text,(WIDTH - length)/2 ,(HEIGHT - 2)/2,1);
}

void story(enum stage now_stage){
	switch(now_stage){
		case stage1:
			exstrcpy(now_text,cenario_stage1,sizeof(cenario_stage1) / sizeof(struct extendstr));
			string_march(now_text,2,2,sizeof(cenario_stage1) / sizeof(struct extendstr));
			break;
		case stage2:
			exstrcpy(now_text,cenario_stage2,sizeof(cenario_stage2) / sizeof(struct extendstr));
			string_march(now_text,2,2,sizeof(cenario_stage2) / sizeof(struct extendstr));
			break;
		case stage3_1:
			exstrcpy(now_text,cenario_stage3,sizeof(cenario_stage3) / sizeof(struct extendstr));
			string_march(now_text,2,2,sizeof(cenario_stage3) / sizeof(struct extendstr));
			break;
		case stage4_1:
			exstrcpy(now_text,cenario_stage4,sizeof(cenario_stage4) / sizeof(struct extendstr));
			string_march(now_text,2,2,sizeof(cenario_stage4) / sizeof(struct extendstr));
			break;
		case stage5:
			exstrcpy(now_text,cenario_stage5,sizeof(cenario_stage5) / sizeof(struct extendstr));
			string_march(now_text,2,2,sizeof(cenario_stage5) / sizeof(struct extendstr));
			break;
		default:
			break;
	}
}
int main(){
	//マップ/座標一覧の初期化
	initmaps();
	//キャラクターの初期化
	initchara();
	//コンソールの初期化
	init_term();
	//メインフレーム描画
	make_flame(WIDTH,HEIGHT,MAIN_FLAME_X,MAIN_FLAME_Y);
	//タイトル画面表示
	maintitle();
	//アニメーション付きフレームクリーン
	flame_flush();
	//シナリオ表示
	subtitle(subtitle5);
	flame_clean();
	story(now_stage);
	flame_flush();
	update_map(now_stage);

	while(1){
		print_lines(now_map,2,2,HEIGHT - 2);
		fflush(stdout);
		switch(decide_event(move_on_map(WIDTH - 2, HEIGHT - 2, now_map_coor,start_pos))){
			case battle_event:
				if(battle(front,back,enemies,enemy_amount)){
					switch(now_stage){
						case stage1:
							flame_clean();
							now_stage = stage2;
							update_map(now_stage);
							start_pos.x = 28 - 2;
							start_pos.y = 24 - 2;
							//subtitle(now_stage);
							story(now_stage);
							wait_anyinput();
							break;
						case stage5:
							gameover_win();
							return 0;
							break;
					}
				}else{
					gameover_lose();
					return 0;
				}
				break;
			case talk_event:
				break;
			default:
				break;
		}
		flame_flush();
	}
}