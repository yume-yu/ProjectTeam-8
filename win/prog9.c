#include <stdio.h>
#include <conio.h>

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
	/**
	  * �t���[�����쐬����
	  * make_flame(��,����,�J�nx���W,�J�ny���W)
	  */
	make_flame(3,8,5,7);
	
	/**
	  * 2�����t���[�����쐬����
	  * make_vsflame(��,����,�J�nx���W,�J�ny���W,��������ʒu��x���W)
	  */
	make_vsflame(23,5,3,20,5);
	
	
	/**
	  * ������1�s�o�͂���
	  * print_line(������,�J�nx���W,�J�ny���W)
	  */
	print_line("�ق��ق���",18,21);
	
	/**
	  * �����𕡐��s�o�͂���
	  * print_lines(������̔z��,�J�nx���W,�J�ny���W,�s��)
	  */
	char string[][100] = {"�ق�","�ӂ�"};
	print_lines(string,5,21,2);
	
	while(!kbhit()){
	}
}
