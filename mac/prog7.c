#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

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
		ungetc(ch, stdin);
		return 1;
	}

	return 0;
}

int wait_keyhit(){
	while(!(kbhit())){
	}
	return getchar();
}


void flush_view_before(){
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
}
void flush_view_after(){
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
}

int main(){
	/**
	 * 行数のマジックナンバー
	 */
	int height = 17;
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
	while(!kbhit()){
		flush_view_before();	
		usleep(5 * 100000);
		flush_view_after();
		usleep(5 * 100000);
			/*if(kbhit()){
				break;
			}*/
	}
	//wait_keyhit();
	return 0;
}

