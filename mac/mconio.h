#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

struct input_assort{
	int kbhit_flag;
	int input_char;
};

/**
 * なんかわからんがunixでkbhit()を実装するおまじない
 *
 */
//int kbhit(void){
struct input_assort mykbhit(){
	struct termios oldt, newt;
	struct input_assort reply;
	int ch;
	int oldf;
	int flag;

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
			//ungetc(ch, stdin);
			reply.input_char = ch;
			reply.kbhit_flag = 1;
		return reply;
	}
	//reply.input_char = '\0';
	reply.kbhit_flag = 0;
	return reply;
}

