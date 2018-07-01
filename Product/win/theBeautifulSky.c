#include "for_make_game.h"
#include "talk_events.h"
#include "decide_event.h"

void update_map(enum stage now_stage){
	mapcpy(now_map,maps[now_stage]);
	coorcpy(now_map_coor,map_coors[now_stage]);
}

void subtitle(enum stage now_stage){
	int length = 0;
	struct extendstr *nowsubtitle[HEIGHT];
	switch(now_stage){
		case stage1:
			exstrcpy(nowsubtitle,subtitle1,2);
			break;
		case stage2:
			exstrcpy(nowsubtitle,subtitle2,2);
			break;
		case stage3_1:
			exstrcpy(nowsubtitle,subtitle3,2);
			break;
		case stage4_1:
			exstrcpy(nowsubtitle,subtitle4,2);
			break;
		case stage5:
			exstrcpy(nowsubtitle,subtitle5,2);
			break;
	}

	for(int i = 0;i < 100; i++){
		if(nowsubtitle[0]->string[i] == '\0'){
			length = i;
			break;
		}
	}
	string_march(nowsubtitle,(WIDTH - length)/2 ,(HEIGHT - 2)/2,2);
	flame_clean();
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
	subtitle(now_stage);
	story(now_stage);
	flame_flush();
	update_map(now_stage);
	print_lines(now_map,2,2,HEIGHT - 2);
	guide_st1();

	while(1){
		if(now_stage == stage5){ //ステージ5はマップ移動がないので例外処理
			set_ch_stat(ST5_BOSS_NAME,&boss1,ST5_BOSS_HP,ST5_BOSS_HP,ST5_BOSS_MINATK,ST5_BOSS_MAXATK);
			if(battle(front,back,enemies,enemy_amount)){
				after_battle_st5();
				gameover_win();
				return 0;
			}else{
				gameover_win();
				return 0;
			}
		}else{
			print_lines(now_map,2,2,HEIGHT - 2);
			fflush(stdout);
			switch(decide_event(move_on_map(WIDTH - 2, HEIGHT - 2, now_map_coor,start_pos))){
				case battle_event:
					if(battle(front,back,enemies,enemy_amount)){
						switch(now_stage){
							case stage1:
								after_battle_st1();
								now_stage = stage2;
								start_pos.x = 28 - 2;
								start_pos.y = 24 - 2;
								//ステージ移動に伴うステータス更新
								set_ch_stat(BACK_NAME,&arist,arist.hp + (BACK_HP_ST2 - BACK_HP_ST1),BACK_HP_ST2,0,BACK_HEAL_ST2);
								break;
							case stage2:
								if(room_id == 2){//ボス戦だったら
									after_battle_st2();
									now_stage = stage3_1;
									start_pos.x = (WIDTH - 2)/2 - 3;
									start_pos.y = (HEIGHT - 2)-1;
									//ステージ移動に伴うステータス更新
									set_ch_stat(BACK_NAME,&arist,arist.hp + (BACK_HP_ST3 - BACK_HP_ST2),BACK_HP_ST3,0,BACK_HEAL_ST3);
									set_ch_stat(FRONT2_NAME,&naoki,naoki.hp + (FRONT2_HP_ST3 - FRONT2_HP_ST2) ,FRONT2_HP_ST2,FRONT2_MINATK_ST2,FRONT2_MAXATK_ST2);
								}else{
									sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
									naoki_find_potion();
									flame_clean();
									continue;
								}
								break;
							case stage3_1:
							case stage3_2:
							case stage3_3:
								if(room_id == 4){
									after_battle_st3();
									now_stage = stage4_1;
									start_pos.x= 27 - 2;
									start_pos.y = 17 -  2;
									//ステージ移動に伴うステータス更新
									set_ch_stat(BACK_NAME,&arist,arist.hp + (BACK_HP_ST4 - BACK_HP_ST3),BACK_HP_ST4,0,BACK_HEAL_ST4);
									set_ch_stat(FRONT2_NAME,&naoki,naoki.hp + (FRONT2_HP_ST4 - FRONT2_HP_ST3) ,FRONT2_HP_ST4,FRONT2_MINATK_ST4,FRONT2_MAXATK_ST4);
								}else{
									sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
									naoki_find_potion();
									flame_clean();
									continue;
								}
								break;
							case stage4_1:
							case stage4_2:
							case stage4_3:
								if(room_id == 4){
									after_battle_st4();
									now_stage = stage5;
									//ステージ移動に伴うステータス更新
									set_ch_stat(FRONT4_NAME,&robo,FRONT4_HP,FRONT4_HP,FRONT4_MINATK,FRONT4_MAXATK);
								}else{
									sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
									naoki_find_potion();
									flame_clean();
									continue;
								}
								break;
						}
					}else{
						gameover_lose();
						return 0;
					}
					update_map(now_stage);	//マップの更新
					subtitle(now_stage);		//サブタイトル表示
					story(now_stage);				//シナリオ表示
					break;
				case talk_event:
					switch(now_stage){
						case stage1:
							switch(room_id){
								case 0:
									talk_event_st1_0();//左の部屋
									break;
								case 1:
									talk_event_st1_1();//真ん中の部屋
									break;
							}
							break;
						case stage2:
							if(room_id == 0){
								talk_event_st2_0(); //右の部屋
							}else if(room_id == 1){
								talk_event_st2_1();
							}
							break;
						case stage3_1:
						case stage3_2:
						case stage3_3:
							switch(room_id){
								case 0:
									talk_event_st3_0(); //左マップ 左上
									break;
								case 1:
									talk_event_st3_1(); //左マップ 下
									break;
								case 2:
									talk_event_st3_2(); //左マップ 右上
									break;
								case 3:
									talk_event_st3_3(); //中央マップ 左
									break;
								case 5:
									talk_event_st3_5(); //中央マップ 右
									break;
								case 6:
									talk_event_st3_6(); //右マップ 左
									break;
							}
							break;
						case stage4_1:
						case stage4_2:
						case stage4_3:
							switch(room_id){
								case 0:
									talk_event_st4_0(); //左マップ 左上
									break;
								case 1:
									talk_event_st4_1(); //左マップ 下
									break;
								case 2:
									talk_event_st4_2(); //左マップ 右上
									break;
								case 3:
									talk_event_st4_3(); //中央マップ 左
									break;
								case 5:
									talk_event_st4_5(); //中央マップ 右
									break;
								case 6:
									talk_event_st4_6(); //右マップ 左
									break;
							}
							break;
					}
					break;
				case move_map:
					mapcpy(now_map,maps[now_stage]);
					coorcpy(now_map_coor,map_coors[now_stage]);
					break;
				default:
					break;
			}
			flame_flush();
		}
	}
}
