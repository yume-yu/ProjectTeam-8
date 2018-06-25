/**
  * Writtenby yume_yu
  * windowsのapiを使ってカーソルの位置を指定箇所へ移動する関数を定義したヘッダ
  */

#include <windows.h>
#include <conio.h>

//WindowsとUNIXでEnterキーの入力が異なるのでプログラム上の表記を統一
#define ENTERKEY 0x0d

//Ctrl+Cによる終了を防ぐ
#include <signal.h>
void ignore_cc(){
	struct sigaction sa;
    // 初期化
    memset( &sa, 0, sizeof(struct sigaction) );

    /*
     * シグナルを単純に無視する場合
     */
    sa.sa_handler = SIG_IGN;
		// シグナルハンドラの設定
    if( sigaction( SIGINT, &sa, NULL ) < 0 ) {
        perror("sigaction");
    }
}

/**
  * Windowsにはマイクロ秒でsleepするusleep(int)がないので
  * time 処理を停止する時間[ms]
  */
void usleep(int time){
	Sleep(time/1000);
}
/**
  * 左上を(1,1)としてカーソルを指定位置へ移動させる関数
  * x カーソルのx座標
  * y カーソルのy座標
  */
int mvcur(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}

/*
 * 入力周りを扱う構造体
 * kbhit_flag	キーが押されているかを返すint
 * input_char	押されているキー
 */
struct input_assort{
	int kbhit_flag;
	int input_char;
};

/*
 * キーボードが押されているかとその入力キーをとる関数
 * 戻り値
 * struct input_assort temp	2つのフラグの構造体
 */
struct input_assort mykbhit(){
	struct input_assort temp;
	if(kbhit()){
		temp.input_char =  _getch();
		temp.kbhit_flag = 1;
	}else{
		temp.input_char = 0;
		temp.kbhit_flag = 0;
	}
	return temp;
}

/**
 * 標準出力の初期化
 */
void init_term(){
	//カーソル位置を(1,1)に移動
	mvcur(1,1);
}

/**
 * 指定箇所への1行の文字出力を行う関数
 * string 出力する文字列
 * x      出力するx座標
 * y      出力するy座標
 */
void print_line(char string[], int x, int y){
	mvcur(x,y);
	printf("%s",string);
	mvcur(0,HEIGHT + 1);
}

/*
 * 指定箇所への複数行行の文字出力を行う関数
 * string    出力する文字列配列
 * x         出力を開始するx座標
 * y         出力を開始するy座標
 * num_lines 出力する行数
 */
void print_lines(char string[][100], int x, int y, int num_lines){
	for(int i = 0; i < num_lines; i++){
		mvcur(x,y+i);
		printf("%s",string[i]);
	}
	mvcur(0,HEIGHT + 1);
}

/*
 * フレームの作成関数
 * width    作成するフレームの幅
 * height   作成するフレームの高さ
 * offset_x 作成するフレームの開始位置のx座標
 * offset_y 作成するフレームの開始位置のy座標
 */
void make_flame(int width, int height, int offset_x, int offset_y){
	int print_width = width - 2;
	int print_height = height - 2;
	//1行目の描画
	mvcur(offset_x,offset_y);
	printf("┌");
	for(int i = 0; i < print_width; i++){
		printf("─");
	}
	printf("┐");
	//中間部分の描画
	for(int i = 0; i < print_height; i++){
		mvcur(offset_x,offset_y + 1 + i);
		printf("│");
		for(int j = 0; j < print_width; j++){
			printf(" ");
		}
		printf("│");
	}

	//最終行部分の描画
	mvcur(offset_x,offset_y + height - 1);
	printf("└");
	for(int i = 0; i < print_width; i++){
		printf("─");
	}
	printf("┘");

	//カーソル位置の初期化
	mvcur(1,HEIGHT+1);
}

/**
 * 横分割フレームの作成関数
 * width    作成するフレームの幅
 * height   作成するフレームの高さ
 * offset_x 作成するフレームの開始位置のx座標
 * offset_y 作成するフレームの開始位置のy座標
 * split_x  フレームの区切り線を入れるx座標
 */
void make_vsflame(int width, int height, int offset_x, int offset_y, int split_x){
	int print_width = width - 2;
	int print_height = height - 2;
	//1行目の描画
	mvcur(offset_x,offset_y);
	printf("┌");
	for(int i = 0; i < print_width; i++){
		if(i == split_x){
			printf("┬");
		}else{
			printf("─");
		}
	}
	printf("┐");
	//中間部分の描画
	for(int i = 0; i < print_height; i++){
		mvcur(offset_x,offset_y + 1 + i);
		printf("│");
		for(int j = 0; j < print_width; j++){
			if(j == split_x){
				printf("│");
			}else{
				printf(" ");
			}
		}
		printf("│");
	}
	//最終行部分の描画
	mvcur(offset_x,offset_y + height - 1);
	printf("└");
	for(int i = 0; i < print_width; i++){
		if(i == split_x){
			printf("┴");
		}else{
			printf("─");
		}
	}


	printf("┘\n");

	//カーソル位置の初期化
	mvcur(1,HEIGHT+1);

}

/**
 * フレーム内をアニメーションでスペース埋めにする関数
 */
void flame_flush(){
	for(int i = 2; i < HEIGHT; i++){
		for(int j = 2; j < WIDTH; j++){
			print_line(" ",j,i);
		}
		fflush(stdout);
		usleep(2 * 10000);
	}
}

/**
 * フレーム内をスペース埋めにする関数
 */
void flame_clean(){
	for(int i = 2; i < HEIGHT; i++){
		for(int j = 2; j < WIDTH; j++){
			mvcur(j,i);
			printf(" ");
		}
		//usleep(2 * 10000);
	}
		fflush(stdout);
}

/**
 * 指定フレーム内をスペース埋めにする関数
 */
void sub_flame_clean(int width, int height, int x, int y){
	for(int i = y; i < y + height; i++){
		for(int j = x; j <x+  width;j++){
			print_line(" ",j,i);
		}
	}
	fflush(stdout);
}

/**
  *  ステータス関連関数
  */

/**
  * キャラクターの基本ステータス構造体
  */
struct character{
	char *name;
	int hp;
	int max_hp;
	int max_atk;
	int min_atk;
};

/**
  * 武器の基本ステータス構造体
  */
struct weapon{
	char *name;
	int atk;
	int is_gun;
};

#define WEPONS_AMOUNT		3
#define WEPONS_AMOUNT_BACK	2

struct weapon all_weapons[7] = {
	{"No weapon",0,0},
	{"HandGun",15,1},
	{"Knife",5,0},
	//{"Bow",15,1}
};

struct weapon all_weapons4back[7] = {
	{"No weapon",0,0},
	{"Bow",10,1}
};
/**
  * 防具の基本ステータス構造体
  */
struct protector{
	char *name;
	int def;
};

#define PROTECTORS_AMOUNT 3

struct protector all_protectors[7] = {
	{"No protector",0},
	{"Shield",10},
	{"Protective Suit",30}
};

/**
 * 武器のステータス設定をする関数
 * tmpwp    ステータスを設定する武器構造体のアドレス
 * atk      武器の攻撃力
 * is_gun  	銃かどうかのフラグ
 */
void set_weapon_stat(struct weapon *tmpwp, int atk, int is_gun){
	tmpwp->atk = atk;
	tmpwp->is_gun = is_gun;
}

/**
 * 防具のステータス設定をする関数
 * tmppr    ステータスを設定する武器構造体のアドレス
 * def      武器の攻撃力
 */
void set_protector_stat(struct protector *tmppr, int def){
	tmppr->def = def;
}

/**
  * キャラクターのステータス設定をする関数
  * name[10] キャラクターの名前
  * tmpch    ステータスを設定するキャラクター構造体のアドレス
  * hp       設定するhp
  * min_atk  与ダメージの下限
  * max_atk  与ダメージの上限
  */
void set_ch_stat(char name[10], struct character *tmpch, int hp, int min_atk, int max_atk){
	tmpch->name = name;
	tmpch->hp = hp;
	tmpch->max_hp = hp;
	tmpch->max_atk = max_atk;
	tmpch->min_atk = min_atk;
}

/**
  * キャラクターのHPを変動させる関数
  * tmpch    hpが変動するキャラクター構造体のアドレス
  * damage   ダメージ量 正なら減算/負なら加算される ex.damageが-20 → 20回復
  */
void change_hp(struct character *tmpch, int damage){
	tmpch->hp -= damage;
	if(tmpch->hp < 0){
		tmpch->hp = 0;
	}else if(tmpch->hp > tmpch->max_hp){
		tmpch->hp = tmpch->max_hp;
	}
}

/*
 * 矢印の位置を定義するための構造体。リスト表示の際に座標配列として使う
 * int x			x座標
 * int y			y座標
 * int not_active	対象の座標が移動可能かのフラグ(1なら移動不可)
 */
struct arrow_pos{
	int x;
	int y;
	int not_active;
};

/**
  * リストを表示した際にカーソルの縦移動と決定した項目を管理する関数
  * tmp_pos[10] カーソルを表示する位置を定義したarrow_pos型の配列
  * length      リスト項目の数
  * 戻り値 length/Enterが押されたときの項目のラベル(何個目のメニューだったか)
  */
int select_from_list(struct arrow_pos tmp_pos[10], int length){
	int arrow_pos_label = 0;
	struct input_assort tmp_input_list;
	print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
	while(1){
		while(!(tmp_input_list = mykbhit()).kbhit_flag);
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
			case ENTERKEY:
				break;
			default:
				continue;
				break;
		}
		break;
	}
	return arrow_pos_label;
}

/**
  * リストを表示した際にカーソルの横移動と決定した項目を管理する関数
  * tmp_pos[10] カーソルを表示する位置を定義したarrow_pos型の配列
  * length      リスト項目の数
  * 戻り値 length/Enterが押されたときの項目のラベル(何個目のメニューだったか)
  */
int select_from_hlist(struct arrow_pos tmp_pos[10], int length){
	int arrow_pos_label = 0;
	struct input_assort tmp_input_list;
	print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
	while(1){
		while(!(tmp_input_list = mykbhit()).kbhit_flag);
		switch(tmp_input_list.input_char){
			case 'a':
				print_line(" ",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				if(arrow_pos_label <= 0){
					arrow_pos_label = length - 1;
				}else{
					arrow_pos_label--;
				}
				print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				continue;
				break;
			case 'd':
				print_line(" ",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				if(arrow_pos_label >= length - 1){
					arrow_pos_label = 0;
				}else{
					arrow_pos_label++;
				}
				print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				continue;
				break;
			case ENTERKEY:
				break;
			default:
				continue;
				break;
		}
		break;
	}
	return arrow_pos_label;
}

/*
 * リストを表示した際にカーソルの二次元移動と決定した項目を管理する関数
 * tmp_pos[10][10]	カーソルを表示する位置を定義したarrow_pos型の配列
 * length			リスト項目の数
 * 戻り値
 * int length		Enterが押されたときの項目のラベル(何個目のメニューだったか)
 */
int select_from_2dlist(int width, int height,struct arrow_pos tmp_pos[width][height]){
	struct arrow_pos arrow_pos_label = {0,0};
	struct input_assort tmp_input_list;
	print_line(">",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
	while(1){
		while(!(tmp_input_list = mykbhit()).kbhit_flag);

		print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
		switch(tmp_input_list.input_char){
			case 'w':
				do{
					if(arrow_pos_label.y <= 0){
						arrow_pos_label.y = height - 1;
					}else{
						arrow_pos_label.y--;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y].not_active);
				print_line(">",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
				continue;
				break;
			case 's':
				do{
					if(arrow_pos_label.y >= height - 1){
						arrow_pos_label.y= 0;
					}else{
						arrow_pos_label.y++;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y].not_active);
				print_line(">",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
				continue;
				break;
			case 'a':
				do{
					if(arrow_pos_label.x <= 0){
						arrow_pos_label.x = width - 1;
					}else{
						arrow_pos_label.x--;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y].not_active);
				print_line(">",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
				continue;
				break;
			case 'd':
				do{
					if(arrow_pos_label.x >= width - 1){
						arrow_pos_label.x= 0;
					}else{
						arrow_pos_label.x++;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y].not_active);
				print_line(">",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
				continue;
				break;
			case ENTERKEY:
				break;
			default:
				continue;
				break;
		}
		break;
	}
	return arrow_pos_label.x + width * arrow_pos_label.y;
}

/*
 * リストを表示した際にカーソルの二次元移動と決定した項目を管理する関数
 * tmp_pos[10][10]	カーソルを表示する位置を定義したarrow_pos型の配列
 * length			リスト項目の数
 * 戻り値
 * int length		Enterが押されたときの項目のラベル(何個目のメニューだったか)
 */
struct arrow_pos move_on_map(int width, int height,struct arrow_pos tmp_pos[width][height], struct arrow_pos offset){
	struct arrow_pos arrow_pos_label = offset;
	struct input_assort tmp_input_list;
	print_line("◯",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
	while(1){
		while(!(tmp_input_list = mykbhit()).kbhit_flag);

		print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
		switch(tmp_input_list.input_char){
			case 'w':
				do{
					if(arrow_pos_label.y <= 0 || tmp_pos[arrow_pos_label.x][arrow_pos_label.y - 1].not_active){
						//arrow_pos_label.y = height - 1;
					}else{
						arrow_pos_label.y--;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y].not_active);
				print_line("◯",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
				continue;
				break;
			case 's':
				do{
					if(arrow_pos_label.y > height - 2 || tmp_pos[arrow_pos_label.x][arrow_pos_label.y + 1].not_active){
						//arrow_pos_label.y= 0;
					}else{
						arrow_pos_label.y++;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y].not_active);
				print_line("◯",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
				continue;
				break;
			case 'a':
				do{
					if(arrow_pos_label.x <= 0 || tmp_pos[arrow_pos_label.x - 1][arrow_pos_label.y].not_active){
						//arrow_pos_label.x = width - 1;
					}else{
						arrow_pos_label.x--;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y].not_active);
				print_line("◯",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
				continue;
				break;
			case 'd':
				do{
					if(arrow_pos_label.x > width - 2 || tmp_pos[arrow_pos_label.x + 1][arrow_pos_label.y].not_active){
						//arrow_pos_label.x= 0;
					}else{
						arrow_pos_label.x++;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y].not_active);
				print_line("◯",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
				continue;
				break;
			case ENTERKEY:
				break;
			default:
				continue;
				break;
		}
		break;
	}
	return arrow_pos_label;
}

int check_window(int width, int height, int x, int y, char *string){
	struct arrow_pos yesno_pos[2] = {
		{x + width / 2 + 2,y+3},
		{x + width / 2 - 3,y+3}
		};
	make_flame(width,height,x,y);
	mvcur(x+2,y+1);
	printf("%s",string);
	print_line("y /  n",x + width / 2 - 2,y+3);
	return select_from_hlist(yesno_pos,2);
}

/**
  *  Enter入力の待機をする関数
  */
void wait_anyinput(){
	mvcur(0,HEIGHT + 1);
	fflush(stdout);
	while(!mykbhit().kbhit_flag);
	while(mykbhit().kbhit_flag);
}

/**
  *  タイトルロゴの出方が微妙に違うのでヘッダで定義
  */
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
  *  操作説明の出方が違うのでヘッダで定義
  */
char control_explain[][100] = {
	"  w            ↑   ",
	"a s d   as  ← ↓ →"
};
