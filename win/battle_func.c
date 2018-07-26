/**
 * @file battle_func.c
 * @brief 謌ｦ髣倥↓髢｢騾｣縺吶ｋ髢｢謨ｰ繧貞ｮ夂ｾｩ縺吶ｋ繝輔ぃ繧､繝ｫ
 * @author yume_yu
 * @date 2018/07/14
 */
#include "thebeautifulsky.h"

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
				}else if(!strcmp(enemies[i]->name,ST5_BOSS_NAME) && turn_count != 0 && turn_count % 4 == 0){
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
						"ファールは ",
						"       テトラグラマトンを唱えた!▼ "
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

