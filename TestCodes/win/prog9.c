#include <stdio.h>
#include <conio.h>

#define WIDTH 60
#define HEIGHT 25
#define MAIN_FLAME_X_OFFSET 1
#define MAIN_FLAME_Y_OFFSET 1

#include "test.h"
#include "flame.h"
#include "pstring.h"

int main(){
	//�^�[�~�i���̕����𗬂��ăJ�[�\���ʒu��(1,1)�ɂ���
	init_term();
	//��g�E�B���h�E�t���[���̍쐬
 	make_flame(WIDTH,HEIGHT,MAIN_FLAME_X_OFFSET,MAIN_FLAME_Y_OFFSET);

	//�e�X�g�Ăяo��
	make_flame(3,8,5,7);
	make_vsflame(40,5,3,20,5);
	char string[][100] = {"�ق�","�ӂ�"};
	print_line("�ق��ق���",18,21);
	print_lines(string,5,21,2);
	while(!kbhit()){
	}
}
