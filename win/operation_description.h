/**
 * 操作説明の関数
 */

/* 枠内への文表示 */
void print_explain_in(struct extendstr explain[],int size){
	exstrcpy(now_text,explain,size);
	string_march(
			now_text,
			BATTLE_MODE_STATUS_FLAME_X + 1,
			HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,
			size
			);
	sub_flame_clean(
			BATTLE_MODE_STATUS_FLAME_SPLIT_X,
			BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,
			BATTLE_MODE_STATUS_FLAME_X + 1,
			HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1
			);
}

/* 枠外への文表示 */
void print_explain_out(struct extendstr explain[],int size){
	exstrcpy(now_text,explain,size);
	string_march(now_text,8,8,size);
	sub_flame_clean(WIDTH - 2,5,2,8);
}

/* 戦闘の説明 */
void explain_battle(){
	struct extendstr first[] = {
		{"チュートリアル戦闘を行います▼ ",0,0}
	};

	struct extendstr second[] = {
		{"戦闘は前衛と後衛の２人 ",0,1},
		{"対エネミーで行います▼ ",12,0}
	};

	struct extendstr third[] = {
		{"プレイヤーが操作するのは ",0,1},
		{"前衛のみです▼ ",20,0}
	};

	struct extendstr fourth[] = {
		{"後衛の行動は ",0,1},
		{"ランダムに決定されます▼ ",10,0}
	};

	struct extendstr fifth[] = {
		{"行動の順番は必ず ",0,1},
		{"前衛→後衛→エネミーです▼ ",9,0}
	};

	struct extendstr sixth[] = {
		{"エネミーのHPは上部に ",0,1},
		{"パーティーのHPは右に表\示されます▼ ",0,0}
	};

	print_explain_in(first,sizeof(first)/sizeof(struct extendstr));
	print_explain_in(second,sizeof(second)/sizeof(struct extendstr));
	print_explain_in(third,sizeof(third)/sizeof(struct extendstr));
	print_explain_in(fourth,sizeof(fourth)/sizeof(struct extendstr));
	print_explain_in(fifth,sizeof(fifth)/sizeof(struct extendstr));
	print_explain_in(sixth,sizeof(sixth)/sizeof(struct extendstr));
}

/* 戦闘コマンドの説明 */
void explain_command(){
	struct extendstr first[] = {
		{"最後に戦闘時のコマンドについて説明します▼ ",0,0}
	};

	struct extendstr second[] = {
		{"こうげき　コマンドを選ぶと攻撃ができます ",0,1},
		{"攻撃の前には攻撃する相手を選択できます▼ ",0,0},
	};

	struct extendstr third[] = {
		{"とくしゅ　コマンドを選ぶと特殊な攻撃ができます ",0,1},
		{"特殊攻撃を持っていないキャラクターもいるので ",0,1},
		{"注意してください▼ ",30,0},
	};

	struct extendstr fourth[] = {
		{"かばう　コマンドを選ぶと後衛をかばうことができます ",0,1},
		{"使用するときには前衛のHPに気を付けましょう▼ ",0,0},
	};

	struct extendstr fifth[] = {
		{"どうぐ　コマンドを選ぶとポーションを使用できます ",0,1},
		{"ポーションの効果はパーティーの全回復です▼ ",0,0},
	};

	struct extendstr sixth[] = {
		{"では実際に戦ってみましょう▼ ",0,0},
	};
	
	print_explain_out(first,sizeof(first)/sizeof(struct extendstr));
	print_explain_out(second,sizeof(second)/sizeof(struct extendstr));
	print_explain_out(third,sizeof(third)/sizeof(struct extendstr));
	print_explain_out(fourth,sizeof(fourth)/sizeof(struct extendstr));
	print_explain_out(fifth,sizeof(fifth)/sizeof(struct extendstr));
	print_explain_out(sixth,sizeof(sixth)/sizeof(struct extendstr));
}
/* チュートリアル戦闘モード */
int demo_battle(struct character *front,struct character *back,struct character *enemies[3], int enemy_amount){
	int finish_flag = 0;																																	//戦闘終了のフラグ
	int protect_flag = 0;																																	//かばう行動のフラグ
	int damage = 0;																																				//計算後のダメージを記憶する変数
	int target_label = 0;																																	//攻撃対象を判断するための変数
	int turn_count = 1;																																		//特殊行動のため戦闘開始からのターンを数える変数
	int sp_count = 0;																																			//特殊行動の行動不能ターンを数える変数
	int enemies_dead_check = 0;																														//敵が全滅したかどうかチェックする時に使う変数
	int player_can_act = 1;																																//プレイヤーが行動可能かのフラグ
	int used_flare = 0;																																		//ステージ5での味方特殊行動の使用後フラグ
	int enemy_amount_for_bar = enemy_amount;																							//HPゲージ描画のため、本来の敵の数を記憶する変数
	struct character *for_bar[enemy_amount];																							//HPゲージ描画のため、本来の敵のアドレスを記憶する変数
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

	print_bt_status(front,back);																													//味方HPの表示
	print_health_bar(for_bar,enemy_amount_for_bar);																				//敵HPゲージの表示
	mvcur(BATTLE_MODE_STATUS_FLAME_X + 2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT - 1);		//ターン数表示用カーソル移動
	printf("Turn %2d",turn_count);																												//ターン数表示
	
	explain_battle();

	print_bt_commands();																			//プレイヤーのコマンドを表示する
	explain_command();
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
					mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					printf("%s に %3d ダメージ!▼",enemies[target_label]->name,damage);
					change_hp(enemies[target_label],damage);
					if(using_weapon->is_gun && !strcmp(front->name,FRONT2_NAME)){
						damage = front->min_atk + rand() % (front->max_atk - front->min_atk - 1) + using_weapon->atk;
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
						printf("%s に %3d ダメージ!▼",enemies[target_label]->name,damage);
						change_hp(enemies[target_label],damage);
					}
					print_health_bar(for_bar,enemy_amount_for_bar);
					wait_anyinput();
					if(enemies[target_label]->hp <= 0){
						sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						printf("%s は倒れた!▼",enemies[target_label]->name);
						for(int i = target_label; i + 1 < enemy_amount;i++){
							enemies[i] = enemies[i + 1];
						}
						enemy_amount--;
						wait_anyinput();
					}
					break;
				case 1:
					mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					printf("戻る");
					fflush(stdout);
					target_label = select_from_list(battle_menu_arrow,1);
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					continue;
					break;
				case 2:
					protect_flag = 1;
					mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					printf("%s はかばう体勢に入った▼",front->name);
					wait_anyinput();
					break;
				case 3:
					for(int i = 0; i <= potion_amount; i++){
						mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1 + i);
						if(i < potion_amount){
							printf("ポーション");
						}else{
							printf("戻る");
						}
						fflush(stdout);
					}
					target_label = select_from_list(battle_menu_arrow,potion_amount + 1);
					if(target_label < potion_amount){
						sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						change_hp(front,-1 * front->max_hp);
						change_hp(&arist,-1 * arist.max_hp);
						print_bt_status(front,back);
						print_line("ポーションを使った!▼ ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
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
			print_health_bar(for_bar,enemy_amount_for_bar);
			print_bt_status(front,back);
			if(front->hp <= 0 || (back->hp <= 0 && strcmp(back->name,"dummy"))){
				sub_flame_clean(
						BATTLE_MODE_STATUS_FLAME_SPLIT_X,
						BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,
						BATTLE_MODE_STATUS_FLAME_X + 1,
						HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1
						);
				print_line("負けてしまった...▼",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				finish_flag = 1;
				return 0;
				wait_anyinput();
				continue;
			}
		}
		//敵の行動終わり
		sub_flame_clean(
				BATTLE_MODE_STATUS_FLAME_SPLIT_X,
				BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,
				BATTLE_MODE_STATUS_FLAME_X + 1,
				HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1
				);
		turn_count++;
	}
	return 0;
}

/* 操作説明の本体 */
int operation_description(){
	now_stage = ope_exp;
	flame_clean();
	struct extendstr first[] = {
		{"このゲームでの操作は以下のキーで行います。 ",0,1},
		{"　 ",0,1},
		{"Enter:決定　文字送り ",1,1},
		{"（文字送りは他のキーでも可 ",3,1},
		{" Enterの長押しor連打は想定外の選択の可能\性あり） ",10,1},
		{"　 ",0,1},
		{"AWSD: マップ上の移動　カーソ\ル移動 ",1,1},
		{"Ａ＝←　Ｗ＝↑　Ｓ＝↓　Ｄ＝→  ",5,1},
		{"　 ",0,1},
		{"Space:マップ上でメニューを開く ",1,1},
	};
	struct arrow_pos yesno[] = {
		{(WIDTH - 16)/2 + 8,16,0,0},
		{(WIDTH - 16)/2 + 1,16,0,0},
	};

	struct extendstr second[] = {
		{"マップ上でのキャラクターの位置は●で表\されます ",0,1},
		{"次に進む場合はキャラクターを出口へ移動させてください▼  ",0,0},
	};

	struct extendstr after[] = {
		{"操作説明／チュートリアルは以上です。 ",0,1},
		{"ゲームを始めますか？ ",7,1},
		{" ",0,1},
		{"ゲームを始める ",7,1},
		{"タイトルにもどる ",7,1},
	};

	struct arrow_pos tobe[] = {
		{(WIDTH - 36)/2 + 6,11,0,0},
		{(WIDTH - 36)/2 + 6,12,0,0},
	};
	print_line("How to play game",(WIDTH - 16)/2,2);															//タイトルテキストを出す
	exstrcpy(now_text,first,sizeof(first)/sizeof(struct extendstr));
	string_march(now_text,2,4,sizeof(first)/sizeof(struct extendstr));
	print_line("次に進む場合は「はい」を選んでください",(WIDTH - 38)/2,15);				//確認の文章を表示
	print_line("はい   いいえ",(WIDTH - 16)/2 + 2,16);
	while(!select_from_hlist(yesno,2));																						//｢はい｣の入力をまつ
	sub_flame_clean(WIDTH - 2,2,2,15);																						//次に進む場合は～の文章を消す
	exstrcpy(now_text,second,sizeof(second)/sizeof(struct extendstr));						//次に表示する文章をnow_textに用意
	string_march(now_text,2,15,sizeof(second)/sizeof(struct extendstr));					//now_textを表示
	coorcpy(now_map_coor,map_coors[now_stage]);																		//説明用マップ座標をnow_map_coorに用意
	start_pos.x = 1;																															//マップ移動開始時のX座標をセット
	start_pos.y = 0;																															//マップ移動開始時のY座標をセット	
	print_lines(map_exp,10,17,8);																									//説明用マップを表示
	while(move_on_map(39, 6, now_map_coor,start_pos).x != 48){										//マップ移動開始
		start_pos.x -= 8;
		start_pos.y -= 16;
	}
	set_ch_stat("前衛",&lirel,FRONT1_HP,FRONT1_HP,FRONT1_MINATK,FRONT1_MAXATK);		//前衛ステータスセット
	set_ch_stat("後衛",&arist,BACK_HP_ST1,BACK_HP_ST1,0,BACK_HEAL_ST1);						//後衛ステータスセット		
	front = &lirel;																																//前衛アドレスセット
	back = &arist;																																//後衛アドレスセット
	set_ch_stat("デモエネミー",&boss1,30,35,30,35);																//敵ステータスセット
	enemies[0] = &boss1;																													//敵アドレスセット	
	enemies[1] = &dummy;
	potion_amount = 1;
	enemy_amount = 1;																															//敵の数を設定
	demo_battle(front,back,enemies,enemy_amount);
	make_flame(39,7,(WIDTH - 36) / 2 - 2,7);
	exstrcpy(now_text,after,sizeof(after)/sizeof(struct extendstr));
	string_march(now_text,(WIDTH - 36) / 2,8,sizeof(after)/sizeof(struct extendstr));
	now_stage = stage1;
	return select_from_list(tobe,2);
}
