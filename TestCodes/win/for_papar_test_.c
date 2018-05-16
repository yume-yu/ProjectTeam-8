#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/** 
  * メインフレーム(大枠)関連定数
  * WIDTH                 メインフレームの幅
  * HEIGHT                メインフレームの高さ
  * MAIN_FLAME_X_OFFSET   メインフレームの開始位置のX座標
  * MAIN_FLAME_Y_OFFSET   メインフレームの開始位置のY座標
  */
#define WIDTH 60
#define HEIGHT 25
#define MAIN_FLAME_X_OFFSET 1
#define MAIN_FLAME_Y_OFFSET 1

//汎用関数を定義したヘッダ
#include "for_make_game.h"

/** 
  * 戦闘画面でのウィンドウサイズ/配置関連定数
  * BATTLE_MODE_STATUS_FLAME_WIDTH   下分割フレームの幅
  * BATTLE_MODE_STATUS_FLAME_HEIGHT  下分割フレームの高さ
  * BATTLE_MODE_STATUS_FLAME_X       下分割フレームの開始位置のX座標
  * BATTLE_MODE_STATUS_FLAME_SPLIT_X 下分割フレームの分割位置
  * BATTLE_MODE_COMMAND_POS          戦闘コマンドブレームの1行目のX座標
  * BATTLE_MODE_STATUS_HP_POS        ステータスフレームの1行目のX座標
  */
#define BATTLE_MODE_STATUS_FLAME_WIDTH WIDTH-2
#define BATTLE_MODE_STATUS_FLAME_HEIGHT 6
#define BATTLE_MODE_STATUS_FLAME_X 2
#define BATTLE_MODE_STATUS_FLAME_SPLIT_X 2*(WIDTH-2)/3-1
#define BATTLE_MODE_COMMAND_POS 7
#define BATTLE_MODE_STATUS_HP_POS BATTLE_MODE_STATUS_FLAME_SPLIT_X+5

//タイトル画面の星の数
#define STAR_AMOUNT 50

//乱数取得
long get_rand(){
	return rand();
}

//必要キャラクタの定義
struct charactor naoki;
struct charactor lirel;
struct charactor arist;
struct charactor boss1;
struct charactor boss2;
struct charactor dummy;

//各キャラクターのステータス初期化
void initchara(){
	set_ch_stat("naoki",&naoki,90,20,35);
	set_ch_stat("lirel",&lirel,120,15,20);
	set_ch_stat("arist",&arist,70,0,20);
	set_ch_stat("boss1",&boss1,100,10,20);
	set_ch_stat("boss2",&boss2,100,10,20);
	set_ch_stat("dummy",&dummy,0,0,0);
}

//各キャラクターのステータス設定を表示
void show_ch_stat(int x,int y){
	make_flame(32,8,x,y);
	print_line("Now status list",x+5,y+1);
	mvcur(x+1,y+2);
	printf("naoki - HP:%4d  ATK:%3d ～%3d",naoki.max_hp,naoki.min_atk,naoki.max_atk);
	mvcur(x+1,y+3);
	printf("lirel - HP:%4d  ATK:%3d ～%3d",lirel.max_hp,lirel.min_atk,lirel.max_atk);
	mvcur(x+1,y+4);
	printf("arist - HP:%4d  HEAL:%d",arist.max_hp,arist.max_atk);
	mvcur(x+1,y+5);
	printf("boss1 - HP:%4d  ATK:%3d ～%3d",boss1.max_hp,boss1.min_atk,boss1.max_atk);
	mvcur(x+1,y+6);
	printf("boss2 - HP:%4d  ATK:%3d ～%3d",boss2.max_hp,boss2.min_atk,boss2.max_atk);
	mvcur(0,HEIGHT + 1);
	fflush(stdout);
}

int sel_mode_window(int y){
	make_flame(WIDTH - 4,HEIGHT / 2,3,y);
	print_line("Select mode",5,y+1);
	print_line(" 1:battle - naoki&arist vs boss1",5,y+2);
	print_line(" 2:battle - naoki&arist vs boss1&boss2",5,y+3);
	print_line(" 3:battle - lirel&arist vs boss1",5,y+4);
	print_line(" 4:battle - lirel&arist vs boss1&boss2",5,y+5);
	print_line(" 5:edit status",5,y+6);
	print_line(" 9:exit",5,y+7);
	fflush(stdout);
	mvcur(0,HEIGHT + 1);
	return 0;
}

void main_window_init(){
	//フレーム内スペース埋め
	flame_flush();
	//ステータスフレーム表示
	show_ch_stat(WIDTH - 34,HEIGHT - 8);
	//
	sel_mode_window(2);
}

//戦闘モードの時にコマンド部分表示する関数
void print_bt_commands(){
	print_line("Attack",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
	print_line("Magic",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
	print_line("Protect",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3);
	print_line("Item",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 4);
}

void print_bt_status(struct charactor *front,struct charactor *back){
	//ステータス部分表示
	char spaces[][100] = {
		{"               "},
		{"               "}
	};
	print_lines(spaces,BATTLE_MODE_STATUS_HP_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,2);
	print_line("HP",BATTLE_MODE_STATUS_HP_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
	mvcur(BATTLE_MODE_STATUS_HP_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
	printf("%s:%4d/%4d",front->name,front->hp,front->max_hp);
	mvcur(BATTLE_MODE_STATUS_HP_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3);
	printf("%s:%4d/%4d",back->name,back->hp,back->max_hp);
	mvcur(0,HEIGHT + 1);
	fflush(stdout);
}

//戦闘モード
void battle(struct charactor *front,struct charactor *enemies[3], int enemy_amount){
	int finish_flag = 0;
	int protect_flag = 0;
	int damage = 0;
	int target_label = 0;
	int enemies_dead_flag[enemy_amount];
	int enemies_dead_check = 0;
	struct arrow_pos battle_menu_arrow[] = {{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1},{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2},{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3},{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 4}};
	
	//敵のHPと生存フラグを初期化
	for(int i = 0; i < enemy_amount; i++){
		change_hp(enemies[i],-1 * enemies[i]->max_hp);
		enemies_dead_flag[i] = 1;
	}
	flame_flush();
	make_vsflame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_SPLIT_X);
	
	print_bt_status(front,&arist);

	while(!finish_flag){
		print_bt_commands();
		int command = select_from_list(battle_menu_arrow,4);
		//コマンド部分フレームクリーン
		sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
		switch(command){
			case 0:
				for(int i = 0; i <= enemy_amount; i++){
					mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1 + i);
					if(i < enemy_amount){
						printf("%s",enemies[i]->name);
					}else{
						printf("back");
					}
					fflush(stdout);
				}
				target_label = select_from_list(battle_menu_arrow,enemy_amount + 1);
				sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				if(target_label == enemy_amount){
					continue;
				}
				damage = front->min_atk + get_rand() % (front->max_atk - front->min_atk - 1);
				mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				printf("%s got %3d damaged!▼",enemies[target_label]->name,damage);
				change_hp(enemies[target_label],damage);
				wait_anyinput();
				if(enemies[target_label]->hp <= 0){
					enemies_dead_flag[target_label] = 0;
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					printf("%s was down!▼",enemies[target_label]->name);
					wait_anyinput();
				}
				break;
			case 1:
				break;
			case 2:
				protect_flag = 1;
				mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				printf("%s is ready to protect!▼",front->name);
				wait_anyinput();
				break;
			case 3:
				break;
			default:
				break;
		}
		sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
		//プレイヤーの行動終わり
		
		//勝利判定
		enemies_dead_check = 0;
		for(int i = 0; i <  enemy_amount; i++){
			enemies_dead_check += enemies_dead_flag[i];
		}
		if(enemies_dead_check <= 0){
			print_line("Win!▼",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			finish_flag = 1;
			wait_anyinput();
			continue;
		}
		/*
		if(enemies[0]->hp <= 0){
			print_line("Win!▼",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			finish_flag = 1;
			mvcur(0,HEIGHT + 1);
			fflush(stdout);
			while(!mykbhit().kbhit_flag);
			continue;
		}*/
		//判定終わり
		
		//後衛の行動
		switch(get_rand() % 3){
			case 0:
				print_line("Arist was terrified...▼",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				mvcur(0,HEIGHT + 1);
				fflush(stdout);
				while(!mykbhit().kbhit_flag);
				break;
			default:
				change_hp(front,-1 * arist.max_atk);
				change_hp(&arist,-1 * arist.max_atk);
				print_line("Arist cast \"heal\"!▼",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				print_bt_status(front,&arist);
				mvcur(0,HEIGHT + 1);
				fflush(stdout);
				while(!mykbhit().kbhit_flag);
				break;
		}
		sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
		//後衛の行動終わり
		//敵の行動
		for(int i = 0; i < enemy_amount; i++){
			damage = enemies[i]->min_atk + get_rand() % (enemies[i]->max_atk - enemies[i]->min_atk - 1);
			if(protect_flag){
				mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				printf("%s get %3d damaged by %s!▼",front->name,damage,enemies[i]->name);
				change_hp(front,damage);
			}else{
				switch((int)(get_rand() % 2)){
					case 0:
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						printf("%s get %3d damaged by %s!▼",arist.name,damage,enemies[i]->name);
						change_hp(&arist,damage);
						break;
					default:
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						printf("%s get %3d damaged by %s!▼",front->name,damage,enemies[i]->name);
						change_hp(front,damage);
						break;
				}
			}
		
		protect_flag = 0;
		mvcur(0,HEIGHT + 1);
		fflush(stdout);
					while(!mykbhit().kbhit_flag);
		print_bt_status(front,&arist);
		}
		//敵の行動終わり
		sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);

	}
	main_window_init();
}

//ステータス設定モード
void set_ch_stat_mode(){
	int y = 2;
	int c;
	struct charactor *now_edit;
	struct charactor draft;
	char draft_name[] = "hoge";
	draft.name = draft_name;
	flame_flush();
	make_flame(WIDTH - 4,10,3,y);
	show_ch_stat(WIDTH - 35,3);
	print_line("Select Charactor",5,y+1);
	print_line(" 1:naoki",5,y+3);
	print_line(" 2:arist",5,y+4);
	print_line(" 3:lirel",5,y+5);
	print_line(" 4:boss1",5,y+6);
	print_line(" 5:boss2",5,y+7);
	print_line(" 9:exit",5,y+8);
	fflush(stdout);
	make_flame(WIDTH - 4,HEIGHT - 12,3,12);
	mvcur(0,HEIGHT + 1);
	int flag = 1;
	struct input_assort tmp_input_ch;
	struct input_assort continue_check;
	while(flag){
		while(!(tmp_input_ch = mykbhit()).kbhit_flag);
		switch(tmp_input_ch.input_char){
			case '1':
				now_edit = &naoki;
				break;
			case '2':
				now_edit = &arist;
				break;
			case '3':
				now_edit = &lirel;
				break;
			case '4':
				now_edit = &boss1;
				break;
			case '5':
				now_edit = &boss2;
				break;
			case '9':
				flag = 0;
				break;
			default:
				continue;
		}
		
		if(flag){
			mvcur(5,13);
			printf("Selected Charactor: %s",now_edit->name);
			mvcur(6,14);
			printf("    HP : %3d",now_edit->max_hp);
			mvcur(6,15);
			if(now_edit == &arist){
				printf("  HEAL : %3d",now_edit->max_atk);
			}else{
				printf("   ATK : %3d ～ %3d",now_edit->min_atk,now_edit->max_atk);
			}
			mvcur(5,17);
			printf("New Status:");
			mvcur(6,18);
			printf("    HP : ");
			mvcur(6,19);
			printf("MINATK : ");
			mvcur(6,20);
			printf("MAXATK : ");
			mvcur(15,18);
			scanf("%d",&draft.hp);	
			mvcur(15,19);
			scanf("%d",&draft.min_atk);	
			mvcur(15,20);
			scanf("%d",&draft.max_atk);
			mvcur(6,23);
			printf("HP:%3d ATK:%3d ～ %3d",draft.hp,draft.min_atk,draft.max_atk);
			print_line("Admit Change? [y/n]",5,22);
			while((c = getchar()) != ENTERKEY);
			while(!(continue_check = mykbhit()).kbhit_flag);
			switch(continue_check.input_char){
				case 'y':
					set_ch_stat(now_edit->name,now_edit,draft.hp,draft.min_atk,draft.max_atk);
					break;
				case 'n':
					break;
				default:
					continue;
					break;
			}
			sub_flame_clean(WIDTH - 6,HEIGHT - 14,4,13);	
			show_ch_stat(WIDTH - 35,3);
		}
		mvcur(0,HEIGHT + 1);
	}
	main_window_init();
}


//星が瞬く関数
void stars(int x[],int y[],int amount){
	//for(int i = 0; i < 10; i++){
	for(int j = 0;j < amount; j++){
		print_line("+",x[j],y[j]);
	}
	fflush(stdout);
	usleep(1 * 100000);
	for(int j = 0;j < amount; j++){
		print_line("*",x[j],y[j]);
	}
	fflush(stdout);
	usleep(1 * 100000);
}

int main(){
	//ターミナルの文字を流してカーソル位置を(1,1)にする
	init_term();
	//大枠ウィンドウフレームの作成
	make_flame(WIDTH,HEIGHT,MAIN_FLAME_X_OFFSET,MAIN_FLAME_Y_OFFSET);

	//タイトルロゴ宣言
	char title[][100] = {
		{"┌┬┐┬ ┬┌─┐                       "},                
		{" │ ├─┤├┤                        "},                 
		{" ┴ ┴ ┴└─┘                       "},                
		{"   ┌┐ ┌─┐┌─┐┬ ┬┌┬┐┬┌─┐┬ ┬┬      "},
		{"   ├┴┐├┤ ├─┤│ │ │ │├┤ │ ││      "},  
		{"   └─┘└─┘┴ ┴└─┘ ┴ ┴└  └─┘┴─┘    "},
		{"                      ┌─┐┬┌─┬ ┬ "},
		{"	                     └─┐├┴┐└┬┘ "},
		{"                      └─┘┴ ┴ ┴  "}
	};
	//ロゴ移動中の片付け宣言
	char title_space[][100] = {
		{"                                "},
		{"                                "},
		{"                                "},
		{"                                "},
		{"                                "},
		{"                                "},
		{"                                "},
		{"                                "},
		{"                                "}
	};

	/**
	 * ここからロゴのスクロール開始
	 * 全部見えてないスクロール→ 全部見えた状態のスクロール
	 */
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < i; j++){
			print_line(title[8 - j],15,i - j + 1);
		}
		fflush(stdout);
		usleep(0.2 * 1000000);
		print_lines(title_space,15,2,9);
	}

	print_lines(title,15,2,9);
	fflush(stdout);
	usleep(0.2 * 1000000);

	print_lines(title_space,15,2,9);
	print_lines(title,15,3,9);
	fflush(stdout);
	usleep(0.2 * 1000000);

	print_lines(title_space,15,3,9);
	print_lines(title,15,4,9);
	fflush(stdout);
	usleep(0.2 * 1000000);

	print_lines(title_space,15,4,9);
	print_lines(title,15,5,9);
	print_line("for PaperTest Ver",(WIDTH - 17)/2,14);
	print_line("Press Enter",25,HEIGHT - 4);
	fflush(stdout);
	/* ここまでロゴスクロール部分
	 * この段階でロゴとPressEnterが見える
	 */

	//ここから星の描画
	//星の座標変数を宣言
	int star_x[STAR_AMOUNT];// ={10,15,20};
	int star_y[STAR_AMOUNT];// ={20,15,10}; 
	//乱数の初期化
	srand(time(NULL));
	//文字とかぶらないように座標を設定する
	for(int i = 0; i< STAR_AMOUNT;i++){
		//まず乱数を振る
		star_x[i] = get_rand() % (WIDTH - 2) + 2;
		star_y[i] = get_rand() % (HEIGHT - 2) + 2;
		//もし座標がタイトルロゴのある範囲とかぶっていたら
		if(star_y[i] >= 5 && star_y[i] < 15){
			if(star_x[i] >= 15 && star_x[i] <= 46){
				mvcur(1,HEIGHT+1);
				//今の変数に乱数を振り直すため、ラベルを減算
				i--;
			}
			//PressEnterとかぶっていた時も同じ処理をする
		}else if(star_y[i] >= HEIGHT - 5 && star_y[i] <= HEIGHT - 3){
			if(star_x[i] >= 24 && star_x[i] <= 37){
				i--;
			}
		}
	}
	//星の点滅開始 Enter入力を待機し、押されたらループ脱出
	do{
		stars(star_x,star_y,STAR_AMOUNT);
	}while((mykbhit().input_char) != ENTERKEY);

	initchara();
	main_window_init();

	int flag = 1;
	struct input_assort tmp_input;
	struct charactor *enemies[4]= {&dummy,&dummy,&dummy,&dummy};
	while(flag){
		while(!(tmp_input = mykbhit()).kbhit_flag);
		switch(tmp_input.input_char){
			case '1':
				enemies[0] = &boss1;
				battle(&naoki,enemies,1);
				break;
			case '2':
				enemies[0] = &boss1;
				enemies[1] = &boss2;
				battle(&naoki,enemies,2);
				break;
			case '3':
				enemies[0] = &boss1;
				battle(&lirel,enemies,1);
				break;
			case '4':
				enemies[0] = &boss1;
				enemies[1] = &boss2;
				battle(&lirel,enemies,2);
				break;
			case '5':
				set_ch_stat_mode();
				break;
			case '9':
				flag = 0;
				break;
		}
	}
}
