#include <stdio.h>
#include "mconio.h"
#include "termcoor.h"

#define TRUE 1;
#define FALSE 0;

int* p_ch;
int* p_flag;
/**
 * 各キャラクター構造体
 */
struct status{
	int hitpoint;
	int weapon;
};

int wait_keyhit(){
	struct input_assort in;
	//struct input_assort* p_in;
	//p_in = &in;
	while(1){
		in = kbhit();
		if(!in.kbhit_flag){
			break;
		}
	}
	return in.input_char;
}

int wait_input(){
	struct input_assort in;
	//struct input_assort* p_in;
	//p_in = &in;
	while(1){
		in = kbhit();
		if(!in.kbhit_flag){
			break;
		}
	}
	return in.kbhit_flag;
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
		mvcur(5,6);
		printf("┌───────────────────┐\n");
		mvcur(5,7);
		//printf("\033[7;5H");
		printf("│ > back            │\n");
		mvcur(5,8);
		//printf("\033[8;5H");
		printf("└───────────────────┘\n");
		//printf("\033[9B");
		mvcur(0,18);
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
		mvcur(5,6);
		printf("┌───────────────────┐\n");
		mvcur(5,7);
		//printf("\033[7;5H");
		printf("│ > back            │\n");
		mvcur(5,8);
		//printf("\033[8;5H");
		printf("└───────────────────┘\n");
		//printf("\033[9B");
		mvcur(0,18);
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
	int is_item = FALSE;
	int c;
	struct input_assort tmp;
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
	while(!kbhit().kbhit_flag){
	}
	printf("\033[2J\n"); 
	while(!(tmp = kbhit()).kbhit_flag && tmp.input_char != 'i'){
		flush_view_before(is_item,height);
		switch(tmp.input_char){
			case 'i':
				is_item = !is_item;
				break;
			case EOF:
				break;
			default:
				break;
		}	
		usleep(5 * 100000);
		flush_view_after(is_item,height);
		switch(tmp.input_char){
			case 'i':
				is_item = !is_item;
				break;
			case EOF:
				break;
			default:
				break;
		}	
		usleep(5 * 100000);
	}
	//wait_keyhit();
	/*while(!wait_keyhit()){
		}
		c = getchar();
		printf("%c\n",c);*/
	return 0;
}

