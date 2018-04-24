#include <stdio.h>
#include <curses.h>
int main( int argc, char *argv[] )
{
	int i;
	WINDOW *newwin(int nlines, int ncols, int begin_y, int begin_x);
	initscr();
	clear();
	for( i = 0; i < LINES; i++ ) {
		move(i,i+1);
		if( i%2 == 1 )
			standout();
		addstr("Hello, world");
		if( i%2 == 1 )
			standend();
	}
	refresh();
	SCREEN *set_term(&newwin);
	getch();
	endwin();
	return 0;
}

void new_window(){
}

