#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/** 
 * ���C���t���[��(��g)�֘A�萔
 * WIDTH          ���C���t���[���̕�
 * HEIGHT         ���C���t���[���̍���
 * MAIN_FLAME_X   ���C���t���[���̊J�n�ʒu��X���W
 * MAIN_FLAME_Y   ���C���t���[���̊J�n�ʒu��Y���W
 */
#define WIDTH					60
#define HEIGHT 				25
#define MAIN_FLAME_X	1
#define MAIN_FLAME_Y 	1

/*
 * �ėp�֐����`�����w�b�_
 * �K�����C���t���[���T�C�Y��`�̌���include���邱��
 */
#include "for_make_game_simple.h"

int main(){
	//�^�[�~�i���̕����𗬂��ăJ�[�\���ʒu��(1,1)�ɂ���
	init_term();
	//��g�E�B���h�E�t���[���̍쐬
	make_flame(WIDTH,HEIGHT,MAIN_FLAME_X,MAIN_FLAME_Y);
	//�o�͂�����
	char strings[][100] = {
		"������",
		"����������",
		"�����傭���܂�",
		" ",
		" ",
		" ",
		" ",
		"qwertyuiop"
	};

	/*
	�������o�͂���Ƃ���
	print_lines(strings,MAIN_FLAME_X,MAIN_FLAME_Y,��̔z��̍s��);
	*/
	print_lines(strings,MAIN_FLAME_X + 1,MAIN_FLAME_Y + 1,8);

	//�Ȃɂ����͂�҂�
	wait_anyinput();
}
