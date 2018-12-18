/**
 * @file talk_event.c
 * @brief 各会話イベントごとに呼び出される処理をまとめたファイル
 * @author yume_yu
 * @date
 */

#include "theBeautifulSky.h"

/* リーレルがポーションを見つけた時の挙動  */
void lirel_find_potion(){
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	extendstr event_text[HEIGHT - 2] = {
		{"リーレル：「む、これは」▼  ",0,0},
		{"ポーションを見つけた▼  ",0,0}
	};
	extendstr error_text[HEIGHT - 2] = {
		{"ポーションはこれ以上持てないので諦めた▼  ",0,0},
	};
	exstrcpy(now_text,event_text,2);
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,lengthof(event_text,extendstr));
	if(get_potion()){
	}else{
		exstrcpy(now_text,error_text,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3,lengthof(error_text,extendstr));
	}
}

/* ナオキがポーションを見つけた時の挙動  */
void naoki_find_potion(){
	//make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	extendstr event_text[HEIGHT - 2] = {
		{"ナオキ：「いいもの、発見！」▼  ",0,0},
		{"ポーションを見つけた▼  ",0,0}
	};
	extendstr error_text[HEIGHT - 2] = {
		{"ポーションはこれ以上持てない…▼  ",0,0},
	};
	exstrcpy(now_text,event_text,2);
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(event_text));
	if(get_potion()){
	}else{
		exstrcpy(now_text,error_text,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3,eslengthof(error_text));
	}
}

bool instory_yesno(int y){
	arrow_pos yn[10] = {
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
	exstrcpy(now_text,lirel_said,eslengthof(lirel_said));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(lirel_said));
}

/* ステージ1 侵入禁止 */
void noentry_st1(){
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,lirel_stop,eslengthof(lirel_stop));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(lirel_said));
}

/* ステージ1 真ん中の部屋 */
void talk_event_st1_1(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	extendstr error_text[HEIGHT - 2] = {
		{"もぬけの殻だ▼  ",0,0},
	};
	exstrcpy(now_text,error_text,1);
	//string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(error_text));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,lengthof(error_text,extendstr));
}

/* ステージ1 左の部屋 */
bool talk_event_st1_0_arrived = false;
void talk_event_st1_0(){
	if(talk_event_st1_0_arrived){
		talk_event_st1_1();
	}else{
		flame_flush();
		lirel_find_potion();
		talk_event_st1_0_arrived = true;
	}
}

/* ステージ1 ボス戦前 */
void before_battle_st1(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,beforebattle_stage1, eslengthof(beforebattle_stage1));
	string_march(now_text,BATTLE_MODE_COMMAND_POS - 2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(beforebattle_stage1));
}

/* ステージ1 ボス戦後 */
void after_battle_st1(){
	flame_flush();
	//make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,afterbattle_stage1, eslengthof(afterbattle_stage1));
	string_march(now_text,2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(afterbattle_stage1));
	flame_clean();
}

/* ステージ2 右の部屋 */
bool talk_event_st2_0_arrived = false;
void talk_event_st2_0(){
	flame_flush();
	if(!talk_event_st2_0_arrived){
		exstrcpy(now_text,talk_st2_0_1,eslengthof(talk_st2_0_1));
		string_march(now_text,2,2,eslengthof(talk_st2_0_1));
		flame_clean();
		exstrcpy(now_text,talk_st2_0_2,eslengthof(talk_st2_0_2));
		string_march(now_text,2,2,eslengthof(talk_st2_0_2));
		talk_event_st2_0_arrived = true;
	}else{
		exstrcpy(now_text,talk_st2_null,eslengthof(talk_st2_null));
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(talk_st2_null));
	}
}

bool talk_event_st2_1_arrived = false;
void talk_event_st2_1(){
	flame_flush();
	exstrcpy(now_text,talk_st2_null,eslengthof(talk_st2_null));
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(talk_st2_null));
}

/* ステージ2 ボス戦前 */
void before_battle_st2(){
	flame_flush();
	exstrcpy(now_text,beforebattle_stage2, eslengthof(beforebattle_stage2));
	string_march(now_text,2,2,eslengthof(beforebattle_stage2));
}

/* ステージ2 ボス戦後 */
void after_battle_st2(){
	flame_flush();
	//make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,afterbattle_stage2, eslengthof(afterbattle_stage2));
	string_march(now_text,2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT - 1,eslengthof(afterbattle_stage2));
	flame_clean();
}

/* ステージ3 右マップ左上の部屋 */
void talk_event_st3_0(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,talk_st3_0,eslengthof(talk_st3_0));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(talk_st3_0));
}

/* ステージ3 右マップ下の部屋 */
bool talk_event_st3_1_arrived = false;
void talk_event_st3_1(){
	flame_flush();
	if(!talk_event_st3_1_arrived){ //初めて来たときかどうか
		exstrcpy(now_text,talk_st3_1,eslengthof(talk_st3_1));
		string_march(now_text,2,2,eslengthof(talk_st3_1));
		if(instory_yesno(2 + eslengthof(talk_st3_1) + 1)){
			using_weapon = &all_weapons[1];
			exstrcpy(now_text,talk_st3_1_2,eslengthof(talk_st3_1_2));
			string_march(now_text,2,2 + eslengthof(talk_st3_1) + 3,sizeof(talk_st3_1_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st3_1_3,eslengthof(talk_st3_1_3));
			string_march(now_text,2,2 + eslengthof(talk_st3_1) + 3,sizeof(talk_st3_1_3)/sizeof(extendstr));
		}
		talk_event_st3_1_arrived = true;
	}else if(using_weapon != &all_weapons[1]){ //初めてではなく、装備が銃ではない時
		exstrcpy(now_text,talk_st3_1_1,eslengthof(talk_st3_1_1));
		string_march(now_text,2,2,eslengthof(talk_st3_1_1));
		if(instory_yesno(2 + eslengthof(talk_st3_1_1) + 1)){
			using_weapon = &all_weapons[1];
			exstrcpy(now_text,talk_st3_1_2,eslengthof(talk_st3_1_2));
			string_march(now_text,2,2 + eslengthof(talk_st3_1) + 3,sizeof(talk_st3_1_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st3_1_3,eslengthof(talk_st3_1_3));
			string_march(now_text,2,2 + eslengthof(talk_st3_1) + 3,sizeof(talk_st3_1_3)/sizeof(extendstr));
		}
	}else{
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		exstrcpy(now_text, talk_st3_1_2,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(talk_st3_1_2));
	}
}

/* ステージ3 右マップ右上の部屋 */
bool talk_event_st3_2_arrived = false;
void talk_event_st3_2(){
	flame_flush();
	if(!talk_event_st3_2_arrived){ //初めて来たときかどうか
		exstrcpy(now_text,talk_st3_2,eslengthof(talk_st3_2));
		string_march(now_text,2,2,eslengthof(talk_st3_2));
		if(instory_yesno(2 + eslengthof(talk_st3_2) + 1)){
			using_protector = &all_protectors[2];
			exstrcpy(now_text,talk_st3_2_2,eslengthof(talk_st3_2_2));
			string_march(now_text,2,2 + eslengthof(talk_st3_2) + 3,sizeof(talk_st3_2_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st3_2_3,eslengthof(talk_st3_2_3));
			string_march(now_text,2,2 + eslengthof(talk_st3_2) + 3,sizeof(talk_st3_2_3)/sizeof(extendstr));
		}
		talk_event_st3_2_arrived = true;
	}else if(using_protector != &all_protectors[2]){ //初めてではなく、装備が防護服ではない時
		exstrcpy(now_text,talk_st3_2_1,eslengthof(talk_st3_2_1));
		string_march(now_text,2,2,eslengthof(talk_st3_2_1));
		if(instory_yesno(2 + eslengthof(talk_st3_2_1) + 1)){
			using_protector = &all_protectors[2];
			exstrcpy(now_text,talk_st3_2_2,eslengthof(talk_st3_2_2));
			string_march(now_text,2,2 + eslengthof(talk_st3_2) + 3,sizeof(talk_st3_2_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st3_2_3,eslengthof(talk_st3_2_3));
			string_march(now_text,2,2 + eslengthof(talk_st3_2) + 3,sizeof(talk_st3_2_3)/sizeof(extendstr));
		}
	}else{
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		exstrcpy(now_text, talk_st3_2_2,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(talk_st3_2_2));
	}
}

/* ステージ3 中央マップ左の部屋 */
bool talk_event_st3_3_arrived = false;
void talk_event_st3_3(){
	flame_flush();
	if(!talk_event_st3_3_arrived){ //初めて来たときかどうか
		exstrcpy(now_text,talk_st3_3,eslengthof(talk_st3_3));
		string_march(now_text,2,2,eslengthof(talk_st3_3));
		if(instory_yesno(2 + eslengthof(talk_st3_3) + 1)){
			using_weapon = &all_weapons[2];
			exstrcpy(now_text,talk_st3_3_2,eslengthof(talk_st3_3_2));
			string_march(now_text,2,2 + eslengthof(talk_st3_3) + 3,eslengthof(talk_st3_3_2));
		}else{
			exstrcpy(now_text,talk_st3_3_3,eslengthof(talk_st3_3_3));
			string_march(now_text,2,2 + eslengthof(talk_st3_3) + 3,eslengthof(talk_st3_3_3));
		}
		exstrcpy(now_text,talk_st3_3_0,eslengthof(talk_st3_3_0));
		string_march(now_text,2,2 + eslengthof(talk_st3_3) + 4,eslengthof(talk_st3_3_0));
		extendstr error_text[] = {
			{"ポーションはこれ以上持てないので返した▼  ",0,0},
		};
		if(get_potion()){
		}else{
			exstrcpy(now_text,error_text,1);
			string_march(now_text,2,2 + eslengthof(talk_st3_3) + 7,lengthof(error_text,extendstr));
		}
		talk_event_st3_3_arrived = true;
	}else if(using_weapon != &all_weapons[2]){ //初めてではなく、装備が銃ではない時
		exstrcpy(now_text,talk_st3_3_1,eslengthof(talk_st3_3_1));
		string_march(now_text,2,2,eslengthof(talk_st3_3_1));
		if(instory_yesno(2 + eslengthof(talk_st3_3_1) + 1)){
			using_weapon = &all_weapons[2];
			exstrcpy(now_text,talk_st3_3_2,eslengthof(talk_st3_3_2));
			string_march(now_text,2,2 + eslengthof(talk_st3_3) + 3,eslengthof(talk_st3_3_2));
		}else{
			exstrcpy(now_text,talk_st3_3_3,eslengthof(talk_st3_3_3));
			string_march(now_text,2,2 + eslengthof(talk_st3_3) + 3,eslengthof(talk_st3_3_3));
		}
	}else{
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		exstrcpy(now_text, talk_st3_3_2,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(talk_st3_3_2));
	}
}

/* ステージ3 中央マップ左の部屋 */
void talk_event_st3_5(){
	flame_flush();
	exstrcpy(now_text,talk_st3_5_1,eslengthof(talk_st3_5_1));
	string_march(now_text,2,2,eslengthof(talk_st3_5_1));
	flame_clean();
	exstrcpy(now_text,talk_st3_5_2,eslengthof(talk_st3_5_2));
	string_march(now_text,2,2,eslengthof(talk_st3_5_2));
	flame_clean();
	exstrcpy(now_text,talk_st3_5_3,eslengthof(talk_st3_5_3));
	string_march(now_text,2,2,eslengthof(talk_st3_5_3));
	have_nasu = 1;
}

/* ステージ3 右マップ左の部屋 */
void talk_event_st3_6(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,talk_st3_6,eslengthof(talk_st3_6));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(talk_st3_6));
}

/* ステージ3 右マップ右の部屋 */
bool battle_event_st3_7_arrived = false;

/* ステージ3 ボス戦前 */
void before_battle_st3(){
	flame_flush();
	exstrcpy(now_text,beforebattle_stage3, eslengthof(beforebattle_stage3));
	string_march(now_text,2,2,eslengthof(beforebattle_stage3));
}

/* ステージ3 ボス戦後 */
void after_battle_st3(){
	flame_flush();
	exstrcpy(now_text,afterbattle_stage3, eslengthof(afterbattle_stage3));
	string_march(now_text,2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(afterbattle_stage3));
	flame_clean();
}

/* ステージ4 右マップ左下の部屋 */
bool talk_event_st4_0_arrived = false;
void talk_event_st4_0(){
	flame_flush();
	if(!talk_event_st4_0_arrived){ //初めて来たときかどうか
		exstrcpy(now_text,talk_st4_0,eslengthof(talk_st4_0));
		string_march(now_text,2,2,eslengthof(talk_st4_0));
		if(instory_yesno(2 + eslengthof(talk_st4_0) + 1)){
			arist_using_weapon = &all_weapons4back[1];
			exstrcpy(now_text,talk_st4_0_2,eslengthof(talk_st4_0_2));
			string_march(now_text,2,2 + eslengthof(talk_st4_0) + 3,eslengthof(talk_st4_0_2));
		}else{
			exstrcpy(now_text,talk_st4_0_3,eslengthof(talk_st4_0_3));
			string_march(now_text,2,2 + eslengthof(talk_st4_0) + 3,eslengthof(talk_st4_0_3));
		}
		talk_event_st4_0_arrived = true;
	}else if(arist_using_weapon != &all_weapons4back[1]){ //初めてではなく、装備が銃ではない時
		exstrcpy(now_text,talk_st4_0_1,eslengthof(talk_st4_0_1));
		string_march(now_text,2,2,eslengthof(talk_st4_0_1));
		if(instory_yesno(2 + eslengthof(talk_st4_0_1) + 1)){
			arist_using_weapon = &all_weapons4back[1];
			exstrcpy(now_text,talk_st4_0_2,eslengthof(talk_st4_0_2));
			string_march(now_text,2,2 + eslengthof(talk_st4_0) + 3,eslengthof(talk_st4_0_2));
		}else{
			exstrcpy(now_text,talk_st4_0_3,eslengthof(talk_st4_0_3));
			string_march(now_text,2,2 + eslengthof(talk_st4_0) + 3,eslengthof(talk_st4_0_3));
		}
	}else{
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		exstrcpy(now_text, talk_st4_0_2,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(talk_st4_0_2));
	}
}

/* ステージ4 右マップ下の部屋 */
bool talk_event_st4_1_arrived = false;
void talk_event_st4_1(){
	flame_flush();
	if(!talk_event_st4_1_arrived){ //初めて来たときかどうか
		exstrcpy(now_text,talk_st4_1,eslengthof(talk_st4_1));
		string_march(now_text,2,2,eslengthof(talk_st4_1));
		if(instory_yesno(2 + eslengthof(talk_st4_1) + 1)){
			arist_using_protector = &all_protectors[1];
			exstrcpy(now_text,talk_st4_1_2,eslengthof(talk_st4_1_2));
			string_march(now_text,2,2 + eslengthof(talk_st4_1) + 3,eslengthof(talk_st4_1_2));
		}else{
			exstrcpy(now_text,talk_st4_1_3,eslengthof(talk_st4_1_3));
			string_march(now_text,2,2 + eslengthof(talk_st4_1) + 3,eslengthof(talk_st4_1_3));
		}
		talk_event_st4_1_arrived = true;
	}else if(arist_using_protector != &all_protectors[1]){ //初めてではなく、装備が銃ではない時
		exstrcpy(now_text,talk_st4_1_1,eslengthof(talk_st4_1_1));
		string_march(now_text,2,2,eslengthof(talk_st4_1_1));
		if(instory_yesno(2 + eslengthof(talk_st4_1_1) + 1)){
			arist_using_protector = &all_protectors[1];
			exstrcpy(now_text,talk_st4_1_2,eslengthof(talk_st4_1_2));
			string_march(now_text,2,2 + eslengthof(talk_st4_1) + 3,eslengthof(talk_st4_1_2));
		}else{
			exstrcpy(now_text,talk_st4_1_3,eslengthof(talk_st4_1_3));
			string_march(now_text,2,2 + eslengthof(talk_st4_1) + 3,eslengthof(talk_st4_1_3));
		}
	}else{
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		exstrcpy(now_text, talk_st4_1_2,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(talk_st4_1_2));
	}
}


/* ステージ4 左マップ右の部屋 */
bool talk_event_st4_2_arrived = false;
void talk_event_st4_2(){
	if(talk_event_st4_2_arrived){
		talk_event_st1_1();
	}else{
		flame_flush();
		naoki_find_potion();
		talk_event_st4_2_arrived = true;
	}
}

/* ステージ4 中央マップ左の部屋 */
bool battle_event_st4_3_arrived = false;
void talk_event_st4_3(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,talk_st4_3,eslengthof(talk_st4_3));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(talk_st4_3));
}

/* ステージ4 右マップ左の部屋 */
bool battle_event_st4_5_arrived = false;
void talk_event_st4_5(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,talk_st4_5,eslengthof(talk_st4_5));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(talk_st4_5));
}

/* ステージ2 右の部屋 */
void talk_event_st4_6(){
	flame_flush();
	exstrcpy(now_text,talk_st4_6,eslengthof(talk_st4_6));
	string_march(now_text,2,2,eslengthof(talk_st4_6));
}

/* ステージ4 ボス戦前 */
void before_battle_st4(){
	flame_flush();
	exstrcpy(now_text,beforebattle_stage4, eslengthof(beforebattle_stage4));
	string_march(now_text,2,2,eslengthof(beforebattle_stage4));
}

/* ステージ4 ボス戦後 */
void after_battle_st4(){
	flame_flush();
	exstrcpy(now_text,afterbattle_stage4_1, eslengthof(afterbattle_stage4_1));
	string_march(now_text,2,2,eslengthof(afterbattle_stage4_1));
	flame_clean();
	exstrcpy(now_text,afterbattle_stage4_2, eslengthof(afterbattle_stage4_2));
	string_march(now_text,2,2,eslengthof(afterbattle_stage4_2));
	flame_clean();
	exstrcpy(now_text,afterbattle_stage4_3, eslengthof(afterbattle_stage4_3));
	string_march(now_text,2,2,eslengthof(afterbattle_stage4_3));
	flame_clean();
}

/* ステージ5 ボス戦後 */
void after_battle_st5(){
	flame_flush();
	exstrcpy(now_text,afterbattle_stage5, eslengthof(afterbattle_stage5));
	string_march(now_text,2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(afterbattle_stage5));
	flame_clean();
}

