#include <stdio.h>

#define WIDTH 25
#define HEIGHT 25
#define MAIN_FLAME_X_OFFSET 1
#define MAIN_FLAME_Y_OFFSET 1

#include "termcoor.h"
#include "flame.h"
#include "pstring.h"

int main(){
	//�^�[�~�i���̕����𗬂��ăJ�[�\���ʒu��(1,1)�ɂ���
	init_term();
	//��g�E�B���h�E�t���[���̍쐬
 	make_flame(WIDTH,HEIGHT,MAIN_FLAME_X_OFFSET,MAIN_FLAME_Y_OFFSET);

	//�e�X�g�Ăяo��
	make_flame(2,2,3,2);
	make_vsflame(23,5,3,20,5);
	//print_line("aasdasdas",16,8);
	char string[][100] = {"","*���ӂ������"};
	print_lines(string,16,8,2); getchar();
}
