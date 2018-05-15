#include <stdio.h>
//randのためにインクルード
#include <stdlib.h>
#include <time.h>

//unixでkbhitを使うためのヘッダ
#include "mconio.h"
#define WIDTH 60
#define HEIGHT 25
#define MAIN_FLAME_X_OFFSET 1
#define MAIN_FLAME_Y_OFFSET 1

#include "for_make_game.h"

//文字パレット枠の大きさ/オフセットの定義
#define CHAR_FLAME_W 33
#define CHAR_FLAME_H 7
#define CHAR_FLAME_X_OFFSET 4 
#define CHAR_FLAME_Y_OFFSET 15

//戦闘画面でのウィンドウサイズ/配置設定
#define BATTLE_MODE_STATUS_FLAME_WIDTH WIDTH-2
#define BATTLE_MODE_STATUS_FLAME_HEIGHT 6
#define BATTLE_MODE_STATUS_FLAME_X 2
#define BATTLE_MODE_STATUS_FLAME_SPLIT_X 2*(WIDTH-2)/3-1
#define BATTLE_MODE_COMMAND_POS 7
#define BATTLE_MODE_STATUS_HP_POS BATTLE_MODE_STATUS_FLAME_SPLIT_X+5

//星の数
#define STAR_AMOUNT 50

//キャラクターの基本ステータス構造体
struct charactor{
	char *name;
	int hp;
	int max_hp;
	int max_atk;
	int min_atk;
};

//矢印の位置関数
struct arrow_pos{
	int x;
	int y;
};

//乱数取得
long get_rand(){
	return rand();
}

//キャラクターの変数設定関数
void set_ch_stat(char name[10], struct charactor *tmpch, int hp, int min_atk, int max_atk){
	tmpch->name = name;
	tmpch->hp = hp;
	tmpch->max_hp = hp;
	tmpch->max_atk = max_atk;
	tmpch->min_atk = min_atk;
}

void change_hp(struct charactor *tmpch, int damage){
	tmpch->hp -= damage;
	if(tmpch->hp < 0){
		tmpch->hp = 0;
	}else if(tmpch->hp > tmpch->max_hp){
		tmpch->hp = tmpch->max_hp;
	}
}
//必要キャラクタの定義
struct charactor naoki;
struct charactor lirel;
struct charactor arist;
struct charactor boss1;
struct charactor boss2;

//各キャラクターのステータス初期化
void initchara(){
	set_ch_stat("naoki",&naoki,90,20,35);
	set_ch_stat("lirel",&lirel,120,15,20);
	set_ch_stat("arist",&arist,70,0,20);
	set_ch_stat("boss1",&boss1,100,10,20);
	set_ch_stat("boss2",&boss2,100,10,20);
}

//各キャラクターのステータス設定を表示
void show_ch_stat(int x,int y){
	make_flame(32,8,x,y);
	print_line("Now status list",x+5,y+1);
	mvcur(x+1,y+2);
	printf("naoki - HP:%4d  ATK:%3d 〜%3d\n",naoki.max_hp,naoki.min_atk,naoki.max_atk);
	mvcur(x+1,y+3);
	printf("lirel - HP:%4d  ATK:%3d 〜%3d\n",lirel.max_hp,lirel.min_atk,lirel.max_atk);
	mvcur(x+1,y+4);
	printf("arist - HP:%4d  HEAL:%d\n",arist.max_hp,arist.max_atk);
	mvcur(x+1,y+5);
	printf("boss1 - HP:%4d  ATK:%3d 〜%3d\n",boss1.max_hp,boss1.min_atk,boss1.max_atk);
	mvcur(x+1,y+6);
	printf("boss2 - HP:%4d  ATK:%3d 〜%3d\n",boss2.max_hp,boss2.min_atk,boss2.max_atk);
	mvcur(0,HEIGHT + 1);
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

	show_ch_stat(WIDTH - 34,HEIGHT - 8);
	sel_mode_window(2);
}

struct arrow_pos battle_menu_arrow[] = {{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1},{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2},{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3},{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 4}};

void print_bt_commands(){
	//コマンド部分表示
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

int select_from_list(struct arrow_pos tmp_pos[10], int length){
	int arrow_pos_label = 0;
	struct input_assort tmp_input_list;
	print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
	while(1){
		while(!(tmp_input_list = kbhit()).kbhit_flag);
		switch(tmp_input_list.input_char){
			case 'w':
				print_line(" ",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				if(arrow_pos_label <= 0){
					arrow_pos_label = length - 1;
				}else{
					arrow_pos_label--;
				}
				print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				continue;
				break;
			case 's':
				print_line(" ",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				if(arrow_pos_label >= length - 1){
					arrow_pos_label = 0;
				}else{
					arrow_pos_label++;
				}
				print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				continue;
				break;
			case '\n':
				break;
			default:
				continue;
				break;
		}
		break;
	}
	return arrow_pos_label;
}

//2対1用戦闘モード
void battle2v1(struct charactor *front,struct charactor *enemy){
	change_hp(front,-10000);
	change_hp(enemy,-10000);
	change_hp(&arist,-10000);
	int finish_flag = 1;
	int protect_flag = 0;
	int damage = 0;
	flame_flush();
	make_vsflame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_SPLIT_X);
	
	print_bt_status(front,&arist);

	while(finish_flag){
		print_bt_commands();
		int command = select_from_list(battle_menu_arrow,4);
		//コマンド部分フレームクリーン
		sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
		switch(command){
			case 0:
				mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				printf("%s\n",enemy->name);
				select_from_list(battle_menu_arrow,1);
				sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				damage = front->min_atk + get_rand() % (front->max_atk - front->min_atk - 1);
				mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				printf("%s got %3d damaged!▼",enemy->name,damage);
				change_hp(enemy,damage);
				mvcur(0,HEIGHT + 1);
				fflush(stdout);
				while(!kbhit().kbhit_flag);
				break;
			case 1:
				break;
			case 2:
				protect_flag = 1;
				mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				printf("%s is ready to protect!▼",front->name);
				mvcur(0,HEIGHT + 1);
				fflush(stdout);
				while(!kbhit().kbhit_flag);
				break;
			case 3:
				break;
			default:
				break;
		}
		sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
		//プレイヤーの行動終わり
		//勝利判定
		if(enemy->hp <= 0){
			print_line("Win!▼",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			finish_flag = 0;
			mvcur(0,HEIGHT + 1);
			fflush(stdout);
			while(!kbhit().kbhit_flag);
			continue;
		}
		//判定終わり
		//後衛の行動
		switch(get_rand() % 3){
			case 0:
				print_line("Arist was terrified...▼",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				mvcur(0,HEIGHT + 1);
				fflush(stdout);
				while(!kbhit().kbhit_flag);
				break;
			default:
				change_hp(front,-1 * arist.max_atk);
				change_hp(&arist,-1 * arist.max_atk);
				print_line("Arist cast \"heal\"!▼",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				print_bt_status(front,&arist);
				mvcur(0,HEIGHT + 1);
				fflush(stdout);
				while(!kbhit().kbhit_flag);
				break;
		}
		sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
		//後衛の行動終わり
		//敵の行動
		damage = enemy->min_atk + get_rand() % (enemy->max_atk - enemy->min_atk - 1);
		if(protect_flag){
			mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			printf("%s get %3d damaged by %s!▼",front->name,damage,enemy->name);
			change_hp(front,damage);
		}else{
			switch((int)(get_rand() % 2)){
				case 0:
					mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					printf("%s get %3d damaged by %s!▼",arist.name,damage,enemy->name);
					change_hp(&arist,damage);
					break;
				default:
					mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					printf("%s get %3d damaged by %s!▼",front->name,damage,enemy->name);
					change_hp(front,damage);
					break;
			}
		}
		protect_flag = 0;
		mvcur(0,HEIGHT + 1);
		fflush(stdout);
					while(!kbhit().kbhit_flag);
		print_bt_status(front,&arist);
		//敵の行動終わり
		sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);

	}
	main_window_init();
}

//2対2用戦闘モード2
void battle2v2(struct charactor *front,struct charactor *enemy1,struct charactor *enemy2){
	int finish_flag = 1;	
	
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
		while(!(tmp_input_ch = kbhit()).kbhit_flag);
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
				printf("   ATK : %3d 〜 %3d",now_edit->min_atk,now_edit->max_atk);
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
			printf("HP:%3d ATK:%3d 〜 %3d\n",draft.hp,draft.min_atk,draft.max_atk);
			print_line("Admit Change? [y/n]",5,22);
			while((c = getchar()) != '\n');
			while(!(continue_check = kbhit()).kbhit_flag);
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
		{"                      ┌─┐┬┌─┬ ┬"},
		{"	                    └─┐├┴┐└┬┘"},
		{"                      └─┘┴ ┴ ┴ "}
	};
	//ロゴ移動中の片付け宣言
	char title_space[][100] = {
		{"                         "},
		{"                         "},
		{"                         "},
		{"                         "},
		{"                         "},
		{"                         "},
		{"                         "},
		{"                         "},
		{"                         "},
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
	}while((kbhit().input_char) != '\n');

	initchara();
	main_window_init();

	int flag = 1;
	struct input_assort tmp_input;
	while(flag){
		while(!(tmp_input = kbhit()).kbhit_flag);
		switch(tmp_input.input_char){
			case '1':
				battle2v1(&naoki,&boss1);
				break;
			case '2':
				break;
			case '3':
				break;
			case '4':
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
