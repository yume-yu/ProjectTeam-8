#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "termcoor.h"

int* p_ch;
int* p_flag;
/**
 * 各キャラクター構造体
 *
 */
struct status{
	int hitpoint;
	int weapon;
};

/**
 * なんかわからんがunixでkbhit()を実装するおまじない
 *
 */
int kbhit(void){
	struct termios oldt, newt;
	int ch;
	int oldf;
	int flag;
	p_ch = &ch;
	p_flag = &flag;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if (ch != EOF) {
		if(ch == 'i'){
			flag = 0;
		}else{
			flag = 1;
			ungetc(ch, stdin);
		}

		return 1;
	}

	return 0;
}

int wait_keyhit(){
	while(!(kbhit())){
	}
	return getchar();
}


void flush_view_before(int item_flag,int height){
	//printf("\033[2J"); 
	printf("\033[0;0H");
	printf("┌──────────────────────────────────────┐\n");
	printf("│                     @outside of Olden│\n");
	printf("│      /\\                              │\n");
	printf("│     /  \\        ^     ^    ^         │\n");
	printf("│    /┌──┐\\            ^        ^      │\n");
	printf("│     │  │      ^          ^           │\n");
	printf("│   1 └──┘          ^         ^   ^    │\n");
	printf("│                      ^               │\n");
	printf("│             ^               /\\       │\n");
	printf("│     ^   ^        ^         /  \\      │\n");
	printf("│           ^               /┌──┐\\     │\n");
	printf("│       ^          ^         │  │      │\n");
	printf("│         ^                2 └──┘      │\n");
	printf("│┌────────────────────────────────────┐│\n");
	printf("││ Select destination               ▼ ││\n");
	printf("│└────────────────────────────────────┘│\n");
	printf("└──────────────────────────────────────┘\n");
	//アイテムがある時の表示
	if(!item_flag){
		mvcur(6,5);
		printf("┌───────────────────┐\n");
		mvcur(7,5);
		//printf("\033[7;5H");
		printf("│ > back            │\n");
		mvcur(8,5);
		//printf("\033[8;5H");
		printf("└───────────────────┘\n");
		//printf("\033[9B");
		mvcur(18,0);
	}
}
void flush_view_after(int item_flag,int height){
	//printf("\033[2J"); 
	printf("\033[0;0H");
	printf("┌──────────────────────────────────────┐\n");
	printf("│                     @outside of Olden│\n");
	printf("│      /\\                              │\n");
	printf("│     /  \\        ^     ^    ^         │\n");
	printf("│    /┌──┐\\            ^        ^      │\n");
	printf("│     │  │      ^          ^           │\n");
	printf("│   1 └──┘          ^         ^   ^    │\n");
	printf("│                      ^               │\n");
	printf("│             ^               /\\       │\n");
	printf("│     ^   ^        ^         /  \\      │\n");
	printf("│           ^               /┌──┐\\     │\n");
	printf("│       ^          ^         │  │      │\n");
	printf("│         ^                2 └──┘      │\n");
	printf("│┌────────────────────────────────────┐│\n");
	printf("││ Select destination                 ││\n");
	printf("│└────────────────────────────────────┘│\n");
	printf("└──────────────────────────────────────┘\n");
	//アイテムがある時の表示
	if(!item_flag){
		printf("\033[6;5H");
		printf("┌───────────────────┐\n");
		printf("\033[7;5H");
		printf("│ > back            │\n");
		printf("\033[8;5H");
		printf("└───────────────────┘\n");
		printf("\033[9B");
	}
}

int check_is_item(){
	if(*p_flag == 0){
		return 1;
	}else{
		return 0;
	}

}

int main(){
	/**
	 * 行数のマジックナンバー
	 */
	int height = 17;
	int is_item = 1;
	struct status naoki = {300,0};
	printf("↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑  →\n");
	for(int i = 0; i < height - 2; i++){
		if(i == (height - 2) / 2){
			printf("  ウィンドウを矢印にあわせてください   →\n");
		}else{
			printf("                                       →\n");
		}
	}
	printf("                ここに合わせてください↓→");
	wait_keyhit();
	printf("\033[2J\n"); 
	while(1){
		flush_view_before(is_item,height);	
		if(kbhit()){
			if(check_is_item()){
				is_item = !is_item;
			}else{
				break;
			}
		}
		usleep(5 * 100000);
		flush_view_after(is_item,height);
		if(kbhit()){
			if(check_is_item()){
				is_item = !is_item;
			}else{
				break;
			}
		}
		usleep(5 * 100000);
	}
	//wait_keyhit();
	return 0;
}

