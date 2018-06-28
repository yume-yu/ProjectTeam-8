/* リーレルがポーションを見つけた時の挙動  */
void lirel_find_potion(){		
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	struct extendstr event_text[] = {
		{"リーレル：「む、これは」▼  ",0,0},
		{"ポーションを見つけた▼  ",0,0}
	};
	struct extendstr error_text[] = {
		{"ポーションはこれ以上持てないので諦めた▼  ",0,0},
	};
	exstrcpy(now_text,event_text,2);
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(event_text)/sizeof(struct extendstr));
	if(get_potion()){
	}else{
		exstrcpy(now_text,error_text,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3,sizeof(error_text)/sizeof(struct extendstr));
	}
}

/* ナオキがポーションを見つけた時の挙動  */
void naoki_find_potion(){		
	//make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	struct extendstr event_text[] = {
		{"ナオキ：「いいもの、発見！」▼  ",0,0},
		{"ポーションを見つけた▼  ",0,0}
	};
	struct extendstr error_text[] = {
		{"ポーションはこれ以上持てないので諦めた▼  ",0,0},
	};
	exstrcpy(now_text,event_text,2);
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(event_text)/sizeof(struct extendstr));
	if(get_potion()){
	}else{
		exstrcpy(now_text,error_text,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3,sizeof(error_text)/sizeof(struct extendstr));
	}
}

int instory_yesno(int y){
	struct arrow_pos yn[10] = {
			{11,y,0,0},
			{18,y,0,0}
	};
	char *yesno = "  はい   いいえ";
	print_line(yesno,10,y);
	return !select_from_hlist(yn,2);
}

/* ステージ1 開始直後 */
void guide_st1(){
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,lirel_said,sizeof(lirel_said)/sizeof(struct extendstr));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(lirel_said)/sizeof(struct extendstr));
}

/* ステージ1 真ん中の部屋 */
void talk_event_st1_1(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	struct extendstr error_text[] = {
		{"もぬけの殻だ▼  ",0,0},
	};
	exstrcpy(now_text,error_text,1);
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(error_text)/sizeof(struct extendstr));
}

/* ステージ1 左の部屋 */
int talk_event_st1_0_arrived = 0;
void talk_event_st1_0(){
	if(talk_event_st1_0_arrived){
		talk_event_st1_1();
	}else{
		flame_flush();
		lirel_find_potion();
		talk_event_st1_0_arrived = 1;
	}
}

/* ステージ1 ボス戦後 */
void after_battle_st1(){
	flame_flush();
	//make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,afterbattle_stage1, sizeof(afterbattle_stage1)/sizeof(struct extendstr));
	string_march(now_text,2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(afterbattle_stage1)/sizeof(struct extendstr));
	flame_clean();
}

/* ステージ2 右の部屋 */
int talk_event_st2_0_arrived = 0;
int talk_event_st2_0(){
	flame_flush();
	if(!talk_event_st2_0_arrived){
		exstrcpy(now_text,talk_st2_0_1,sizeof(talk_st2_0_1)/sizeof(struct extendstr));
		string_march(now_text,2,2,sizeof(talk_st2_0_1)/sizeof(struct extendstr));
		flame_clean();
		exstrcpy(now_text,talk_st2_0_2,sizeof(talk_st2_0_2)/sizeof(struct extendstr));
		string_march(now_text,2,2,sizeof(talk_st2_0_2)/sizeof(struct extendstr));
	}else{
	}
}

/* ステージ2 ボス戦後 */
void after_battle_st2(){
	flame_flush();
	//make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,afterbattle_stage2, sizeof(afterbattle_stage2)/sizeof(struct extendstr));
	string_march(now_text,2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(afterbattle_stage2)/sizeof(struct extendstr));
	flame_clean();
}

/* ステージ3 右マップ左上の部屋 */
int talk_event_st3_0(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,talk_st3_0,sizeof(talk_st3_0)/sizeof(struct extendstr));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(talk_st3_0)/sizeof(struct extendstr));
}

/* ステージ3 右マップ下の部屋 */
int talk_event_st3_1_arrived = 0;
int talk_event_st3_1(){
	flame_flush();
	if(!talk_event_st3_1_arrived){ //初めて来たときかどうか
		exstrcpy(now_text,talk_st3_1,sizeof(talk_st3_1)/sizeof(struct extendstr));
		string_march(now_text,2,2,sizeof(talk_st3_1)/sizeof(struct extendstr));
		if(instory_yesno(2 + sizeof(talk_st3_1)/sizeof(struct extendstr) + 1)){
			using_weapon = &all_weapons[1];
			exstrcpy(now_text,talk_st3_1_2,sizeof(talk_st3_1_2)/sizeof(struct extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_1)/sizeof(struct extendstr) + 3,sizeof(talk_st3_1_2)/sizeof(struct extendstr));
		}else{
			exstrcpy(now_text,talk_st3_1_3,sizeof(talk_st3_1_3)/sizeof(struct extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_1)/sizeof(struct extendstr) + 3,sizeof(talk_st3_1_3)/sizeof(struct extendstr));
		}
		talk_event_st3_1_arrived = 1;
	}else if(using_weapon != &all_weapons[1]){ //初めてではなく、装備が銃ではない時
		exstrcpy(now_text,talk_st3_1_1,sizeof(talk_st3_1_1)/sizeof(struct extendstr));
		string_march(now_text,2,2,sizeof(talk_st3_1_1)/sizeof(struct extendstr));
		if(instory_yesno(2 + sizeof(talk_st3_1_1)/sizeof(struct extendstr) + 1)){
			using_weapon = &all_weapons[1];
			exstrcpy(now_text,talk_st3_1_2,sizeof(talk_st3_1_2)/sizeof(struct extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_1)/sizeof(struct extendstr) + 3,sizeof(talk_st3_1_2)/sizeof(struct extendstr));
		}else{
			exstrcpy(now_text,talk_st3_1_3,sizeof(talk_st3_1_3)/sizeof(struct extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_1)/sizeof(struct extendstr) + 3,sizeof(talk_st3_1_3)/sizeof(struct extendstr));
		}
	}else{
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		exstrcpy(now_text, talk_st3_1_2,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(talk_st3_1_2)/sizeof(struct extendstr));
	}
}

/* ステージ3 右マップ右上の部屋 */
int talk_event_st3_2_arrived = 0;
void talk_event_st3_2(){
	flame_flush();
	if(!talk_event_st3_2_arrived){ //初めて来たときかどうか
		exstrcpy(now_text,talk_st3_2,sizeof(talk_st3_2)/sizeof(struct extendstr));
		string_march(now_text,2,2,sizeof(talk_st3_2)/sizeof(struct extendstr));
		if(instory_yesno(2 + sizeof(talk_st3_2)/sizeof(struct extendstr) + 1)){
			using_protector = &all_protectors[2];
			exstrcpy(now_text,talk_st3_2_2,sizeof(talk_st3_2_2)/sizeof(struct extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_2)/sizeof(struct extendstr) + 3,sizeof(talk_st3_2_2)/sizeof(struct extendstr));
		}else{
			exstrcpy(now_text,talk_st3_2_3,sizeof(talk_st3_2_3)/sizeof(struct extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_2)/sizeof(struct extendstr) + 3,sizeof(talk_st3_2_3)/sizeof(struct extendstr));
		}
		talk_event_st3_2_arrived = 1;
	}else if(using_protector != &all_protectors[2]){ //初めてではなく、装備が防護服ではない時
		exstrcpy(now_text,talk_st3_2_1,sizeof(talk_st3_2_1)/sizeof(struct extendstr));
		string_march(now_text,2,2,sizeof(talk_st3_2_1)/sizeof(struct extendstr));
		if(instory_yesno(2 + sizeof(talk_st3_2_1)/sizeof(struct extendstr) + 1)){
			using_protector = &all_protectors[2];
			exstrcpy(now_text,talk_st3_2_2,sizeof(talk_st3_2_2)/sizeof(struct extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_2)/sizeof(struct extendstr) + 3,sizeof(talk_st3_2_2)/sizeof(struct extendstr));
		}else{
			exstrcpy(now_text,talk_st3_2_3,sizeof(talk_st3_2_3)/sizeof(struct extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_2)/sizeof(struct extendstr) + 3,sizeof(talk_st3_2_3)/sizeof(struct extendstr));
		}
	}else{
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		exstrcpy(now_text, talk_st3_2_2,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(talk_st3_2_2)/sizeof(struct extendstr));
	}
}

/* ステージ3 中央マップ左の部屋 */
int talk_event_st3_3_arrived = 0;
int talk_event_st3_3(){
	flame_flush();
	if(!talk_event_st3_3_arrived){ //初めて来たときかどうか
		exstrcpy(now_text,talk_st3_3,sizeof(talk_st3_3)/sizeof(struct extendstr));
		string_march(now_text,2,2,sizeof(talk_st3_3)/sizeof(struct extendstr));
		if(instory_yesno(2 + sizeof(talk_st3_3)/sizeof(struct extendstr) + 1)){
			using_weapon = &all_weapons[2];
			exstrcpy(now_text,talk_st3_3_2,sizeof(talk_st3_3_2)/sizeof(struct extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_3)/sizeof(struct extendstr) + 3,sizeof(talk_st3_3_2)/sizeof(struct extendstr));
		}else{
			exstrcpy(now_text,talk_st3_3_3,sizeof(talk_st3_3_3)/sizeof(struct extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_3)/sizeof(struct extendstr) + 3,sizeof(talk_st3_3_3)/sizeof(struct extendstr));
		}
		exstrcpy(now_text,talk_st3_3_0,sizeof(talk_st3_3_0)/sizeof(struct extendstr));
		string_march(now_text,2,2 + sizeof(talk_st3_3)/sizeof(struct extendstr) + 4,sizeof(talk_st3_3_0)/sizeof(struct extendstr));
		struct extendstr error_text[] = {
			{"ポーションはこれ以上持てないので返した▼  ",0,0},
		};
		if(get_potion()){
		}else{
			exstrcpy(now_text,error_text,1);
			string_march(now_text,2,2 + sizeof(talk_st3_3)/sizeof(struct extendstr) + 5,sizeof(error_text)/sizeof(struct extendstr));
		}
		talk_event_st3_3_arrived = 1;
	}else if(using_weapon != &all_weapons[2]){ //初めてではなく、装備が銃ではない時
		exstrcpy(now_text,talk_st3_3_1,sizeof(talk_st3_3_1)/sizeof(struct extendstr));
		string_march(now_text,2,2,sizeof(talk_st3_3_1)/sizeof(struct extendstr));
		if(instory_yesno(2 + sizeof(talk_st3_3_1)/sizeof(struct extendstr) + 1)){
			using_weapon = &all_weapons[2];
			exstrcpy(now_text,talk_st3_3_2,sizeof(talk_st3_3_2)/sizeof(struct extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_3)/sizeof(struct extendstr) + 3,sizeof(talk_st3_3_2)/sizeof(struct extendstr));
		}else{
			exstrcpy(now_text,talk_st3_3_3,sizeof(talk_st3_3_3)/sizeof(struct extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_3)/sizeof(struct extendstr) + 3,sizeof(talk_st3_3_3)/sizeof(struct extendstr));
		}
	}else{
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		exstrcpy(now_text, talk_st3_3_2,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(talk_st3_3_2)/sizeof(struct extendstr));
	}
}

/* ステージ3 中央マップ左の部屋 */
int talk_event_st3_5(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,talk_st3_5,sizeof(talk_st3_5)/sizeof(struct extendstr));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(talk_st3_5)/sizeof(struct extendstr));
}

/* ステージ3 右マップ左の部屋 */
int talk_event_st3_6(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,talk_st3_6,sizeof(talk_st3_6)/sizeof(struct extendstr));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(talk_st3_6)/sizeof(struct extendstr));
}

/* ステージ3 右マップ右の部屋 */
int battle_event_st3_7_arrived = 0;

/* ステージ3 ボス戦後 */
void after_battle_st3(){
	flame_flush();
	exstrcpy(now_text,afterbattle_stage3, sizeof(afterbattle_stage3)/sizeof(struct extendstr));
	string_march(now_text,2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(afterbattle_stage3)/sizeof(struct extendstr));
	flame_clean();
}


