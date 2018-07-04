/*
 * 汎用関数を定義したヘッダをインクルード
 */
#include "for_make_game.h"

//必要キャラクタの定義
struct character naoki;
struct character lirel;
struct character arist;
struct character robo;
struct character boss1;
struct character boss2;
struct character dummy;

//装備枠の宣言
struct weapon *using_weapon;
struct protector *using_protector;
struct weapon *arist_using_weapon;
struct protector *arist_using_protector;
int potion_amount = 0;



//各キャラクターのステータス設定を表示
void print_ch_stat(int x,int y){
	make_flame(34,8,x,y);
	print_line("Now status list",x+5,y+1);
	mvcur(x+2,y+2);
	printf("naoki - HP:%4d  ATK:%3d 〜%3d",naoki.max_hp,naoki.min_atk,naoki.max_atk);
	mvcur(x+2,y+3);
	printf("arist - HP:%4d  HEAL:%d",arist.max_hp,arist.max_atk);
	mvcur(x+2,y+4);
	printf("lirel - HP:%4d  ATK:%3d 〜%3d",lirel.max_hp,lirel.min_atk,lirel.max_atk);
	mvcur(x+2,y+5);
	printf("boss1 - HP:%4d  ATK:%3d 〜%3d",boss1.max_hp,boss1.min_atk,boss1.max_atk);
	mvcur(x+2,y+6);
	printf("boss2 - HP:%4d  ATK:%3d 〜%3d",boss2.max_hp,boss2.min_atk,boss2.max_atk);
	mvcur(0,HEIGHT + 1);
	fflush(stdout);
}

//メインウィンドウの描画とモード選択
int main_window_init(){
	flame_clean();
	//モード選択フレームのカーゾル座標変数
	struct arrow_pos main_menu_arrow[] = {
		//{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+1}
		{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+ 2},
		{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+ 3},
		{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+ 4},
		//{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+ 5},
		{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+ 6},
		{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+ 7},
		{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+ 8},
		//{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+ 9},
		{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+10}
		//{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+11}
	};
	//モード選択フレームの表示
	//sel_mode_window(SELECT_MODE_FLAME_HEIGHT_OFFSET);
	make_flame(WIDTH / 2 + 1,HEIGHT / 2 ,3,SELECT_MODE_FLAME_HEIGHT_OFFSET);
	char menu_items[][100] = {
		"For PaperTest",
		"   battle",
		"   change equipment",
		"   edit item",
		"For Coordinate/Debug",
		"   edit character status",
		"   edit equip/sp values ",
		"   test battle",
		" ",
		"   exit"
	};
	print_lines(menu_items,6,SELECT_MODE_FLAME_HEIGHT_OFFSET+1,10);
	/*前衛装備表示*/
	make_flame(SELECT_MODE_EQIP_FLAME_WIDTH,SELECT_MODE_EQIP_FLAME_HEIGHT,SELECT_MODE_EQIP_FLAME_X,SELECT_MODE_EQIP_FLAME_Y);
	print_line("Front",SELECT_MODE_EQIP_FLAME_X + 2,SELECT_MODE_EQIP_FLAME_Y);
	print_line("Weapon",SELECT_MODE_EQIP_FLAME_X + 2,SELECT_MODE_EQIP_FLAME_Y + 1);
	mvcur(WIDTH - 3 - strlen(using_weapon->name),SELECT_MODE_EQIP_FLAME_Y + 2);
	printf("%s",using_weapon->name);
	print_line("Protector",SELECT_MODE_EQIP_FLAME_X + 2,SELECT_MODE_EQIP_FLAME_Y + 3);
	mvcur(WIDTH - 3 - strlen(using_protector->name),SELECT_MODE_EQIP_FLAME_Y + 4);
	printf("%s",using_protector->name);
	/*後衛装備表示*/
	make_flame(SELECT_MODE_EQIP_FLAME_WIDTH,SELECT_MODE_EQIP_FLAME_HEIGHT,SELECT_MODE_EQIP_FLAME_X,SELECT_MODE_EQIP_FLAME_Y + SELECT_MODE_EQIP_FLAME_HEIGHT);
	print_line("Back",SELECT_MODE_EQIP_FLAME_X + 2,SELECT_MODE_EQIP_FLAME_Y + SELECT_MODE_EQIP_FLAME_HEIGHT);
	print_line("Weapon",SELECT_MODE_EQIP_FLAME_X + 2,SELECT_MODE_EQIP_FLAME_Y + SELECT_MODE_EQIP_FLAME_HEIGHT + 1);
	mvcur(WIDTH - 3 - strlen(arist_using_weapon->name),SELECT_MODE_EQIP_FLAME_Y + SELECT_MODE_EQIP_FLAME_HEIGHT + 2);
	printf("%s",arist_using_weapon->name);
	print_line("Protector",SELECT_MODE_EQIP_FLAME_X + 2,SELECT_MODE_EQIP_FLAME_Y + SELECT_MODE_EQIP_FLAME_HEIGHT + 3);
	mvcur(WIDTH - 3 - strlen(arist_using_protector->name),SELECT_MODE_EQIP_FLAME_Y + SELECT_MODE_EQIP_FLAME_HEIGHT + 4);
	printf("%s",arist_using_protector->name);
	/*ポーション所持数表示*/
	make_flame(SELECT_MODE_EQIP_FLAME_WIDTH,SELECT_MODE_POTION_FLAME_HEIGHT,SELECT_MODE_EQIP_FLAME_X,SELECT_MODE_EQIP_FLAME_Y + 2 * SELECT_MODE_EQIP_FLAME_HEIGHT);
	print_line("Potion amount",SELECT_MODE_EQIP_FLAME_X + 1,SELECT_MODE_EQIP_FLAME_Y + 2 * SELECT_MODE_EQIP_FLAME_HEIGHT);
	mvcur(SELECT_MODE_EQIP_CHARASET_X - 1,SELECT_MODE_EQIP_FLAME_Y + 2 * SELECT_MODE_EQIP_FLAME_HEIGHT + 1);
	printf("%d",potion_amount);
	print_lines(control_explain,WIDTH - 20,HEIGHT - 2,2);
	print_line("The Beautiful Sky",4,HEIGHT - 1);
	fflush(stdout);
	//モード選択
	return select_from_list(main_menu_arrow,7);
}

//戦闘モードの時にコマンド部分表示する関数
void print_bt_commands(){
	print_line("Attack",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
	print_line("Special",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
	print_line("Protect",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3);
	print_line("Item",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 4);
	fflush(stdout);
}

//戦闘モードの時にHP部分を描画する関数
void print_bt_status(struct character *front,struct character *back){
	//ステータス部分表示
	char spaces[][100] = {
		{"               "},
		{"               "}
	};
	print_lines(spaces,BATTLE_MODE_STATUS_HP_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,2);
	print_line("HP",BATTLE_MODE_STATUS_HP_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
	mvcur(BATTLE_MODE_STATUS_HP_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
	printf("%s:%4d/%4d",front->name,front->hp,front->max_hp);
	if(strcmp(back->name,"dummy")){
		mvcur(BATTLE_MODE_STATUS_HP_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3);
		printf("%s:%4d/%4d",back->name,back->hp,back->max_hp);
	}
	mvcur(0,HEIGHT + 1);
	fflush(stdout);
}

//戦闘モード前のステージ選択をする関数
int select_stage(){
	make_flame(SELECT_STAGE_FLAME_WIDTH,SELECT_STAGE_FLAME_HEIGHT,SELECT_STAGE_FLAME_X,SELECT_STAGE_FLAME_Y);
	char stage_list[][100] = {
		"Select Battle",
		"  Stage1 vs Boss",
		"  Stage2 vs Boss",
		"  Stage3 vs WeakEnemy",
		"  Stage3 vs Boss",
		"  Stage4 vs WeakEnemy",
		"  Stage4 vs Boss",
		"  Stage5 vs Boss"
	};
	struct arrow_pos stage_select_arrow[] = {
		{SELECT_STAGE_FLAME_X + 2,SELECT_STAGE_FLAME_Y + 2},
		{SELECT_STAGE_FLAME_X + 2,SELECT_STAGE_FLAME_Y + 3},
		{SELECT_STAGE_FLAME_X + 2,SELECT_STAGE_FLAME_Y + 4},
		{SELECT_STAGE_FLAME_X + 2,SELECT_STAGE_FLAME_Y + 5},
		{SELECT_STAGE_FLAME_X + 2,SELECT_STAGE_FLAME_Y + 6},
		{SELECT_STAGE_FLAME_X + 2,SELECT_STAGE_FLAME_Y + 7},
		{SELECT_STAGE_FLAME_X + 2,SELECT_STAGE_FLAME_Y + 8},
		{SELECT_STAGE_FLAME_X + 2,SELECT_STAGE_FLAME_Y + 9}
	};
	print_lines(stage_list,SELECT_STAGE_FLAME_X + 2,SELECT_STAGE_FLAME_Y + 1,8);
	print_line("back",SELECT_STAGE_FLAME_X + 4,SELECT_STAGE_FLAME_Y + 9);
	return select_from_list(stage_select_arrow,sizeof(stage_select_arrow)/sizeof(struct arrow_pos));
}

//敵のHPゲージを描画する関数
void print_health_bar(struct character *target[],int amount){
	double health_par = 0;
	for(int i = 0; i < amount; i++){
		make_flame(20,3,2,2 + 3 * i);
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
		//printf("%f\n%d\n%d",health_par,target[i]->hp,target[i]->max_hp);
		fflush(stdout);
	}
}


void set_stat_from_template_mamber(struct character *now_edit,int target){
	int selected = 0; //選択されたテンプレートを記憶する変数
	struct arrow_pos arrow[] = {
		{EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 1},
		{EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 2},
		{EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 3},
		{EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 4},
	};
	print_line("Stage",EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y);
	if(target == 1){
		print_line("Stage2",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 1);
		print_line("Stage3",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 2);
		print_line("Stage4",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 3);
		selected = select_from_list(arrow,3);
	}else if(target == 2){
		print_line("Stage1",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 1);
		print_line("Stage2",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 2);
		print_line("Stage3",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 3);
		print_line("Stage4",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 4);
		selected = select_from_list(arrow,4);
	}else if(target == 3){
		print_line("Stage4",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 1);
		print_line("Stage5",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 2);
		selected = select_from_list(arrow,2);
	}
	switch(target){
		case 1:
			switch(selected){
				case 0:
					set_ch_stat(FRONT2_NAME,&naoki,FRONT2_HP_ST2,FRONT2_MINATK_ST2,FRONT2_MAXATK_ST2);
					break;
				case 1:
					set_ch_stat(FRONT2_NAME,&naoki,FRONT2_HP_ST3,FRONT2_MINATK_ST3,FRONT2_MAXATK_ST3);
					break;
				case 2:
					set_ch_stat(FRONT2_NAME,&naoki,FRONT2_HP_ST4,FRONT2_MINATK_ST4,FRONT2_MAXATK_ST4);
					break;
			}
			break;
		case 2:
			switch(selected){
				case 0:
					set_ch_stat(BACK_NAME,&arist,BACK_HP_ST1,0,BACK_HEAL_ST1);
					break;
				case 1:
					set_ch_stat(BACK_NAME,&arist,BACK_HP_ST2,0,BACK_HEAL_ST2);
					break;
				case 2:
					set_ch_stat(BACK_NAME,&arist,BACK_HP_ST3,0,BACK_HEAL_ST3);
					break;
				case 3:
					set_ch_stat(BACK_NAME,&arist,BACK_HP_ST4,0,BACK_HEAL_ST4);
					break;
			}
			break;
		case 3:
			switch(selected){
				case 0:
					set_ch_stat(FRONT3_NAME,&robo,FRONT3_HP,FRONT3_MINATK,FRONT3_MAXATK);
					break;
				case 1:
					set_ch_stat(FRONT4_NAME,&robo,FRONT4_HP,FRONT4_MINATK,FRONT4_MAXATK);
					break;
			}
			break;
	}
}

//敵ステータステンプレート選択
void set_stat_from_template_enemy(struct character *now_edit){
	int target = 0;
	struct arrow_pos arrow[] = {
		{EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 1},
		{EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 2},
		{EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 3},
		{EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 4},
		{EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 5},
		{EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 8}
	};
	print_line("Boss",EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y);
	print_line("St1Boss",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 1);
	print_line("St2Boss",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 2);
	print_line("St3Boss",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 3);
	print_line("St4Boss",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 4);
	print_line("St5Boss",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 5);
	print_line("NotBoss",EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 7);
	print_line("enemy",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 8);
	target = select_from_list(arrow,6);
	switch(target){
		case 0:
			set_ch_stat(ST1_BOSS_NAME,now_edit,ST1_BOSS_HP,ST1_BOSS_MINATK,ST1_BOSS_MAXATK);
			break;
		case 1:
			set_ch_stat(ST2_BOSS_NAME,now_edit,ST2_BOSS_HP,ST2_BOSS_MINATK,ST2_BOSS_MAXATK);
			break;
		case 2:
			set_ch_stat(ST3_BOSS_NAME,now_edit,ST3_BOSS_HP,ST3_BOSS_MINATK,ST3_BOSS_MAXATK);
			break;
		case 3:
			set_ch_stat(ST4_BOSS_NAME,now_edit,ST4_BOSS_HP,ST4_BOSS_MINATK,ST4_BOSS_MAXATK);
			break;
		case 4:
			set_ch_stat(ST5_BOSS_NAME,now_edit,ST5_BOSS_HP,ST5_BOSS_MINATK,ST5_BOSS_MAXATK);
			break;
		case 5:
			set_ch_stat("enemy",now_edit,ST2_BOSS_HP,ST2_BOSS_MINATK,ST2_BOSS_MAXATK);
			break;
	}
}

//メンバーステータス設定モード
void set_member_stat_mode(){
	struct character *now_edit;
	struct character draft;
	//モード選択フレームのカーゾル座標変数
	struct arrow_pos set_ch_arrow[4][2] = {
		{
			{(EDIT_MODE_EDIT_FLAME_WIDTH - 30) / 2 - 1,EDIT_MODE_SELECT_FLAME_Y+4},
			{(EDIT_MODE_EDIT_FLAME_WIDTH - 30) / 2 - 1,EDIT_MODE_SELECT_FLAME_Y+6},
		},
		{
			{(EDIT_MODE_EDIT_FLAME_WIDTH - 30) / 2 + 7,EDIT_MODE_SELECT_FLAME_Y+4},
			{(EDIT_MODE_EDIT_FLAME_WIDTH - 30) / 2 + 7,EDIT_MODE_SELECT_FLAME_Y+6},
		}	,
		{
			{(EDIT_MODE_EDIT_FLAME_WIDTH - 30) / 2 + 15,EDIT_MODE_SELECT_FLAME_Y+4},
			{(EDIT_MODE_EDIT_FLAME_WIDTH - 30) / 2 + 15,EDIT_MODE_SELECT_FLAME_Y+6},
		},
		{
			{(EDIT_MODE_EDIT_FLAME_WIDTH - 30) / 2 + 23,EDIT_MODE_SELECT_FLAME_Y+4},
			{(EDIT_MODE_EDIT_FLAME_WIDTH - 30) / 2 + 23,EDIT_MODE_SELECT_FLAME_Y+6,1},
		}
	};
	//struct arrow_pos *arrow_p[4] = set_ch_arrow;
	char draft_name[] = "hoge";
	draft.name = draft_name;
	flame_flush();
	make_flame(EDIT_MODE_SELECT_FLAME_WIDTH,EDIT_MODE_SELECT_FLAME_HEIGHT,EDIT_MODE_SELECT_FLAME_X,EDIT_MODE_SELECT_FLAME_Y);
	//print_ch_stat(WIDTH - 36,3);
	print_line("Select Character",EDIT_MODE_SELECT_FLAME_X + 4,EDIT_MODE_SELECT_FLAME_Y+2);
	print_line(" Lirel   Naoki   Arist   Robo",(EDIT_MODE_EDIT_FLAME_WIDTH - 30) / 2 ,EDIT_MODE_SELECT_FLAME_Y+4);
	print_line(" Boss1   Boss2   Back ",(EDIT_MODE_EDIT_FLAME_WIDTH - 30) / 2 ,EDIT_MODE_SELECT_FLAME_Y+6);
	fflush(stdout);
	make_flame(EDIT_MODE_EDIT_FLAME_WIDTH,EDIT_MODE_EDIT_FLAME_HEIGHT,EDIT_MODE_EDIT_FLAME_X,EDIT_MODE_EDIT_FLAME_Y);
	mvcur(0,HEIGHT + 1);
	int flag = 1;
	int target = 0;
	struct input_assort tmp_input_ch;
	struct input_assort continue_check;
	while(flag){
		print_ch_stat(EDIT_MODE_EDIT_FLAME_X + 1,EDIT_MODE_EDIT_FLAME_Y + 1);
		target = select_from_2dlist(4,2,&set_ch_arrow[0]);
		switch(target){
			case 0:
				now_edit = &lirel;
				break;
			case 1:
				now_edit = &naoki;
				break;
			case 2:
				now_edit = &arist;
				break;
			case 3:
				now_edit = &robo;
				break;
			case 4:
				now_edit = &boss1;
				break;
			case 5:
				now_edit = &boss2;
				break;
			case 6:
				flag = 0;
				break;
			default:
				continue;
		}
		//テンプレートから選択するかを確認
		if(target != 6){
			if(check_window(ECHECK_TEMPLATE_FLAME_WIDTH,ECHECK_TEMPLATE_FLAME_HEIGHT,ECHECK_TEMPLATE_FLAME_X,ECHECK_TEMPLATE_FLAME_Y,"Choose from tamplate?")){
				sub_flame_clean(EDIT_MODE_EDIT_FLAME_WIDTH - 2,EDIT_MODE_EDIT_FLAME_HEIGHT - 2,EDIT_MODE_EDIT_FLAME_X + 1,EDIT_MODE_EDIT_FLAME_Y + 1);
				switch(target){
					case 0:
						set_ch_stat(FRONT1_NAME,&lirel,FRONT1_HP,FRONT1_MINATK,FRONT1_MAXATK);
						break;
					case 1:
					case 2:
					case 3:
						set_stat_from_template_mamber(now_edit,target);
						break;
					case 4:
					case 5:
						set_stat_from_template_enemy(now_edit);
						break;
				}
			}else{
				sub_flame_clean(EDIT_MODE_EDIT_FLAME_WIDTH - 2,EDIT_MODE_EDIT_FLAME_HEIGHT - 2,EDIT_MODE_EDIT_FLAME_X + 1,EDIT_MODE_EDIT_FLAME_Y + 1);
				mvcur(EDIT_MODE_EDIT_FLAME_CHAR_X,EDIT_MODE_EDIT_FLAME_CHAR_Y);
				printf("Selected Character: %s",now_edit->name);
				mvcur(EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 1);
				printf("    HP : %3d",now_edit->max_hp);
				mvcur(EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 2);
				if(now_edit == &arist){
					printf("  HEAL : %3d",now_edit->max_atk);
				}else{
					printf("   ATK : %3d 〜 %3d",now_edit->min_atk,now_edit->max_atk);
				}
				mvcur(EDIT_MODE_EDIT_FLAME_CHAR_X,EDIT_MODE_EDIT_FLAME_CHAR_Y + 5);
				printf("New Status:");
				mvcur(EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 6);
				printf("    HP : ");
				mvcur(EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 7);
				if(now_edit != &arist){
					printf("MINATK : ");
				}else{
					printf("  HEAL : ");
				}
				mvcur(EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 8);
				if(now_edit != &arist){
					printf("MAXATK : ");
				}
				mvcur(EDIT_MODE_EDIT_FLAME_CHAR_X + 10,EDIT_MODE_EDIT_FLAME_CHAR_Y + 6);
				scanf("%d",&draft.hp);
				mvcur(EDIT_MODE_EDIT_FLAME_CHAR_X + 10,EDIT_MODE_EDIT_FLAME_CHAR_Y + 7);
				if(now_edit != &arist){
					scanf("%d",&draft.min_atk);
				}else{
					scanf("%d",&draft.max_atk);
					draft.min_atk = 0;
				}
				mvcur(EDIT_MODE_EDIT_FLAME_CHAR_X + 10,EDIT_MODE_EDIT_FLAME_CHAR_Y + 8);
				if(now_edit != &arist){
					scanf("%d",&draft.max_atk);
				}
				//scanfで漏れたEnterを受け流す
				getchar();
				if(check_window(ECHECK_SELECT_FLAME_WIDTH, ECHECK_SELECT_FLAME_HEIGHT, ECHECK_SELECT_FLAME_X, ECHECK_SELECT_FLAME_Y,"Admit Change?")){
					set_ch_stat(now_edit->name,now_edit,draft.hp,draft.min_atk,draft.max_atk);
				}
			}
		}
		sub_flame_clean(EDIT_MODE_EDIT_FLAME_WIDTH - 2,EDIT_MODE_EDIT_FLAME_HEIGHT - 2,EDIT_MODE_EDIT_FLAME_X + 1,EDIT_MODE_EDIT_FLAME_Y + 1);
		mvcur(0,HEIGHT + 1);
		//print_line(" ",set_ch_arrow[target].x,set_ch_arrow[target].y);

	}
}

void set_eqip_values(){
	struct weapon *now_editw;
	struct protector * now_editp;
	flame_flush();
	make_flame(EDIT_EQIP_SELECT_FLAME_WIDTH,EDIT_EQIP_SELECT_FLAME_HEIGHT,EDIT_EQIP_SELECT_FLAME_X,EDIT_EQIP_SELECT_FLAME_Y);
	make_flame(EDIT_EQIP_EDIT_FLAME_WIDTH,EDIT_EQIP_EDIT_FLAME_HEIGHT,EDIT_EQIP_EDIT_FLAME_X,EDIT_EQIP_EDIT_FLAME_Y);
	wait_anyinput();
}

//装備設定モード
void set_weapon_mode(){
	int target_chara	= 0;
	int target_equip = 0;
	struct weapon *weapon_list;
	int weapon_amount = 0;
	int label = 0;
	//対象選択フレームのカーソル座標変数
	struct arrow_pos arrow[] = {
		{SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2 - 2,SET_WEAPON_MODE_FLAME_Y+4},
		{SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2 - 2,SET_WEAPON_MODE_FLAME_Y+5}
	};
	//装備選択のカーソル座標変数
	struct arrow_pos w_arrow[] = {
		{SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2 - 2,SET_WEAPON_MODE_FLAME_Y + 3},
		{SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2 - 2,SET_WEAPON_MODE_FLAME_Y + 4},
		{SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2 - 2,SET_WEAPON_MODE_FLAME_Y + 5},
		{SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2 - 2,SET_WEAPON_MODE_FLAME_Y + 6}
	};
	/* 装備変更キャラ選択 */
	make_flame(SET_WEAPON_MODE_FLAME_WIDTH,SET_WEAPON_MODE_FLAME_HEIGHT,SET_WEAPON_MODE_FLAME_X,SET_WEAPON_MODE_FLAME_Y);
	print_line("Select edit",SET_WEAPON_MODE_FLAME_X + 2,SET_WEAPON_MODE_FLAME_Y + 1);
	print_line("     character",SET_WEAPON_MODE_FLAME_X + 2,SET_WEAPON_MODE_FLAME_Y + 2);
	print_line("  Naoki",SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2,SET_WEAPON_MODE_FLAME_Y + 4);
	print_line("  Arist",SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2,SET_WEAPON_MODE_FLAME_Y + 5);
	target_chara = select_from_list(arrow,2);
	/* 変更対象選択 */
	make_flame(SET_WEAPON_MODE_FLAME_WIDTH,SET_WEAPON_MODE_FLAME_HEIGHT,SET_WEAPON_MODE_FLAME_X,SET_WEAPON_MODE_FLAME_Y);
	print_line("Which edit",SET_WEAPON_MODE_FLAME_X + 2,SET_WEAPON_MODE_FLAME_Y + 1);
	print_line("         equip",SET_WEAPON_MODE_FLAME_X + 2,SET_WEAPON_MODE_FLAME_Y + 2);
	print_line(" Weapon",SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2,SET_WEAPON_MODE_FLAME_Y + 4);
	print_line(" Protector",SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2,SET_WEAPON_MODE_FLAME_Y + 5);
	target_equip = select_from_list(arrow,2);
	switch(target_equip){
		case 0:
			make_flame(SET_WEAPON_MODE_FLAME_WIDTH,SET_WEAPON_MODE_FLAME_HEIGHT,SET_WEAPON_MODE_FLAME_X,SET_WEAPON_MODE_FLAME_Y);
			print_line("Select weapon:",SET_WEAPON_MODE_FLAME_X + 2,SET_WEAPON_MODE_FLAME_Y + 1);
			switch(target_chara){
				case 0:
					weapon_list = all_weapons;
					weapon_amount = WEAPONS_AMOUNT;
					break;
				case 1:
					weapon_list = all_weapons4back;
					weapon_amount = WEAPONS_AMOUNT_BACK;
					break;
			}
			for(int i = 0; i <weapon_amount; i++){
				mvcur(SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2,SET_WEAPON_MODE_FLAME_Y + 3 + i);
				printf("%s",(weapon_list + i)->name);
			}
			label = select_from_list(w_arrow,weapon_amount);
			if(target_chara == 0){
				using_weapon = &all_weapons[label];
			}else if(target_chara == 1){
				arist_using_weapon = &all_weapons4back[label];
			}
			break;
		case 1:
			make_flame(SET_WEAPON_MODE_FLAME_WIDTH + 5,SET_WEAPON_MODE_FLAME_HEIGHT,SET_WEAPON_MODE_FLAME_X,SET_WEAPON_MODE_FLAME_Y);
			print_line("Select protector:",SET_WEAPON_MODE_FLAME_X + 2,SET_WEAPON_MODE_FLAME_Y + 1);
			for(int i = 0; i < PROTECTORS_AMOUNT; i++){
				mvcur(SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2,SET_WEAPON_MODE_FLAME_Y + 3 + i);
				printf("%s",all_protectors[i].name);
			}
			label = select_from_list(w_arrow,PROTECTORS_AMOUNT);
			if(target_chara == 0){
				using_protector = &all_protectors[label];
			}else if(target_chara == 1){
				arist_using_protector = &all_protectors[label];
			}
			break;
	}
}

void set_item_mode(){
	struct arrow_pos arrow[] = {
		{(WIDTH / 2) - 5,(HEIGHT - 3) / 2 + 3},
		{(WIDTH / 2) - 2,(HEIGHT - 3) / 2 + 3},
		{(WIDTH / 2) + 1,(HEIGHT - 3) / 2 + 3},
		{(WIDTH / 2) + 4,(HEIGHT - 3) / 2 + 3}
	};
	make_flame(23,5,(WIDTH - 20) / 2 - 1 ,(HEIGHT - 3) / 2);
	print_line("Potion amaount edit",(WIDTH / 2) - 9,(HEIGHT - 3) / 2 + 1);
	print_line("0  1  2  3",(WIDTH / 2) - 4,(HEIGHT - 3) / 2 + 3);
	potion_amount = select_from_hlist(arrow,4);
}

int main(){
	//Ctrl+Cを無効化
	ignore_cc();
	//ターミナルの文字を流してカーソル位置を(1,1)にする
	init_term();
	//大枠ウィンドウフレームの作成
	make_flame(WIDTH,HEIGHT,MAIN_FLAME_X,MAIN_FLAME_Y);

	maintitle();

	flame_flush();
	initchara();

	int exit_flag = 1;
	int mode = 0;
	//テスト戦闘用変数宣言
	int type[3];
	struct character *front = &dummy;
	struct character *back = &dummy;
	char printed_string[100] = "null";
	char any_types[][100] = {
		"2 vs 1",
		"2 vs 2 ",
		"1 vs 1"
	};
	struct arrow_pos type_pos[3] = {
		{(22 - 6) / 2 +(WIDTH - 22)/2 -	2,(HEIGHT - 7)/2 + 3},
		{(22 - 6) / 2 +(WIDTH - 22)/2 - 2,(HEIGHT - 7)/2 + 4},
		{(22 - 6) / 2 +(WIDTH - 22)/2 - 2,(HEIGHT - 7)/2 + 5}
	};
	//ここまでテスト戦闘用変数宣言

	struct input_assort check_select;
	struct character *enemies[4]= {&dummy,&dummy,&dummy,&dummy};
	while(exit_flag){
		mode = main_window_init();
		//入力がミスでないかを確認
		if(!check_window(SCHECK_SELECT_FLAME_WIDTH, SCHECK_SELECT_FLAME_HEIGHT, SCHECK_SELECT_FLAME_X, SCHECK_SELECT_FLAME_Y,"Continue?")){
			continue;
		}

		switch(mode){
			case 0://battle
				switch(select_stage()){
					case 0://stage1 vs boss
						enemies[0] = &boss1;
						set_ch_stat(ST1_BOSS_NAME,&boss1,ST1_BOSS_HP,ST1_BOSS_MINATK,ST1_BOSS_MAXATK);
						set_ch_stat(FRONT1_NAME,&lirel,FRONT1_HP,FRONT1_MINATK,FRONT1_MAXATK);
						set_ch_stat(BACK_NAME,&arist,BACK_HP_ST1,0,BACK_HEAL_ST1);
						battle(&lirel,&arist,enemies,1);
						flame_flush();
						break;
					case 1://stage2 vs boss
						enemies[0] = &boss1;
						set_ch_stat(ST2_BOSS_NAME,&boss1,ST2_BOSS_HP,ST2_BOSS_MINATK,ST2_BOSS_MAXATK);
						set_ch_stat(FRONT2_NAME,&naoki,FRONT2_HP_ST2,FRONT2_MINATK_ST2,FRONT2_MAXATK_ST2);
						set_ch_stat(BACK_NAME,&arist,BACK_HP_ST2,0,BACK_HEAL_ST2);
						battle(&naoki,&arist,enemies,1);
						flame_flush();
						break;
					case 2://stage3 vs weakenemy
						enemies[0] = &boss1;
						enemies[1] = &boss2;
						set_ch_stat("enemy",&boss1,ST1_BOSS_HP,ST1_BOSS_MINATK,ST1_BOSS_MAXATK);
						set_ch_stat("enemy",&boss2,ST1_BOSS_HP,ST1_BOSS_MINATK,ST1_BOSS_MAXATK);
						set_ch_stat(BACK_NAME,&arist,BACK_HP_ST3,0,BACK_HEAL_ST3);
						set_ch_stat(FRONT2_NAME,&naoki,FRONT2_HP_ST3,FRONT2_MINATK_ST3,FRONT2_MAXATK_ST3);
						battle(&naoki,&arist,enemies,2);
						flame_flush();
						break;
					case 3://stage3 vs boss
						enemies[0] = &boss1;
						set_ch_stat(ST3_BOSS_NAME,&boss1,ST3_BOSS_HP,ST3_BOSS_MINATK,ST3_BOSS_MAXATK);
						set_ch_stat(FRONT2_NAME,&naoki,FRONT2_HP_ST3,FRONT2_MINATK_ST3,FRONT2_MAXATK_ST3);
						set_ch_stat(BACK_NAME,&arist,BACK_HP_ST3,0,BACK_HEAL_ST3);
						battle(&naoki,&arist,enemies,1);
						flame_flush();
						break;
					case 4://stage4 vs weakenemy
						enemies[0] = &boss1;
						enemies[1] = &boss2;
						set_ch_stat("enemy",&boss1,ST2_BOSS_HP,ST2_BOSS_MINATK,ST2_BOSS_MAXATK);
						set_ch_stat("enemy",&boss2,ST2_BOSS_HP,ST2_BOSS_MINATK,ST2_BOSS_MAXATK);
						set_ch_stat(BACK_NAME,&arist,BACK_HP_ST4,0,BACK_HEAL_ST4);
						set_ch_stat(FRONT2_NAME,&naoki,FRONT2_HP_ST4,FRONT2_MINATK_ST4,FRONT2_MAXATK_ST4);
						battle(&naoki,&arist,enemies,2);
						flame_flush();
						break;
					case 5://stage4 vs boss
						enemies[0] = &boss1;
						set_ch_stat(ST4_BOSS_NAME,&boss1,ST4_BOSS_HP,ST4_BOSS_MINATK,ST4_BOSS_MAXATK);
						set_ch_stat(FRONT3_NAME,&robo,FRONT3_HP,FRONT3_MINATK,FRONT3_MAXATK);
						battle(&robo,&dummy,enemies,1);
						flame_flush();
						break;
					case 6://stage5 vs boss
						enemies[0] = &boss1;
						set_ch_stat(ST5_BOSS_NAME,&boss1,ST5_BOSS_HP,ST5_BOSS_MINATK,ST5_BOSS_MAXATK);
						set_ch_stat(FRONT4_NAME,&robo,FRONT4_HP,FRONT4_MINATK,FRONT4_MAXATK);
						battle(&robo,&dummy,enemies,1);
						flame_flush();
						break;
					default:
						flame_clean();
						break;
				}
				break;
			case 1://change equipment
				set_weapon_mode();
				break;
			case 2://edit item
				set_item_mode();
				break;
			case 3://edit character
				set_member_stat_mode();
				flame_flush();
				break;
			case 4:
				set_eqip_values();
				break;
			case 5://test battle
				make_flame(22,7,(WIDTH - 22)/2,(HEIGHT - 7)/2 );
				strcpy(printed_string,"Select Battle Type");
				strcpy(any_types[0], "2 vs 1");
				strcpy(any_types[1], "2 vs 2");
				strcpy(any_types[2], "1 vs 1");
				print_line(printed_string,(22 - strlen(printed_string)) / 2 +(WIDTH - 22)/2 ,(HEIGHT - 7)/2 + 1);
				print_lines(any_types,(22 - 6) / 2 +(WIDTH - 22)/2 ,(HEIGHT - 7)/2 + 3,3);
				type[0] = select_from_list(type_pos,3); //戦闘の種類を選択
				sub_flame_clean(20,5,(WIDTH - 22) / 2 + 1,(HEIGHT - 7 )/ 2 + 1);
				if(type[0] != 2){//1vsでなければ前衛を選択
					strcpy(printed_string,"Select Front Chara");
					print_line(printed_string,(22 - strlen(printed_string)) / 2 +(WIDTH - 22)/2 ,(HEIGHT - 7)/2 + 1);
					strcpy(any_types[0], "Lirel");
					strcpy(any_types[1], "Naoki");
					print_lines(any_types,(22 - 6) / 2 +(WIDTH - 22)/2 ,(HEIGHT - 7)/2 + 3,2);
					type[1] = select_from_list(type_pos,2);	//前衛を選択
				}
				strcpy(any_types[0], "Boss1");
				strcpy(any_types[1], "Boss2");
				sub_flame_clean(20,5,(WIDTH - 22) / 2 + 1,(HEIGHT - 7 )/ 2 + 1);
				strcpy(printed_string,"Select Enemy");
				print_line(printed_string,(22 - strlen(printed_string)) / 2 +(WIDTH - 22)/2 ,(HEIGHT - 7)/2 + 1);
				if(type[0] != 1){ //vs2戦闘でなければ敵を選択
					print_lines(any_types,(22 - 6) / 2 +(WIDTH - 22)/2 ,(HEIGHT - 7)/2 + 3,2);
					type[2] = select_from_list(type_pos,2);	//敵を選択
				}
				switch(type[0]){
					case 0:
						switch(type[1]){
							case 0:
								front = &lirel;
								break;
							case 1:
								front = &naoki;
								break;
						}
						back = &arist;
						switch(type[2]){
							case 0:
								enemies[0] = &boss1;
								break;
							case 1:
								enemies[0] = &boss2;
								break;
						}
						battle(front,back,enemies,1);
						break;
					case 1:
						switch(type[1]){
							case 0:
								front = &lirel;
								break;
							case 1:
								front = &naoki;
								break;
						}
						back = &arist;
						enemies[0] = &boss1;
						enemies[1] = &boss2;
						battle(front,back,enemies,2);
						break;
					case 2:
						front = &robo;
						switch(type[2]){
							case 0:
								enemies[0] = &boss1;
								break;
							case 1:
								enemies[0] = &boss2;
								break;
						}
						back = &dummy;
						battle(front,back,enemies,1);
						break;
					default:
						break;
				}
				flame_flush();
				break;
			case 6://exit
				exit_flag = 0;
				break;
		}
	}
}
