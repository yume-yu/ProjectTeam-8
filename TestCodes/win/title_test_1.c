#include <stdio.h>
//rand�̂��߂ɃC���N���[�h
#include <stdlib.h>
#include <time.h>

#include <conio.h>
#define WIDTH 60
#define HEIGHT 25
#define MAIN_FLAME_X_OFFSET 1
#define MAIN_FLAME_Y_OFFSET 1

//#include "for_make_game.h"
#include "termcoor.h"
#include "pstring.h"
#include "flame.h"

//�����p���b�g�g�̑傫��/�I�t�Z�b�g�̒�`
#define CHAR_FLAME_W 33
#define CHAR_FLAME_H 7
#define CHAR_FLAME_X_OFFSET 4 
#define CHAR_FLAME_Y_OFFSET 15

//���̐�
#define STAR_AMOUNT 50

long get_rand(){
	return rand();
}

//�����u���֐�
void stars(int x[],int y[],int amount){
	//for(int i = 0; i < 10; i++){
		for(int j = 0;j < amount; j++){
			print_line("+",x[j],y[j]);
		}
		fflush(stdout);
		usleep(1 * 100000);
		for(int j = 0;j < amount; j++){
			print_line("*",x[j],y[j]);
		}
		fflush(stdout);
		usleep(1 * 100000);
		/*
		for(int j = 0;j < amount; j++){
			print_line(" ",x[j],y[j]);
		}
		fflush(stdout);
		*/
		//usleep(1);
	//}
}

int main(){
	//�^�[�~�i���̕����𗬂��ăJ�[�\���ʒu��(1,1)�ɂ���
	init_term();
	//��g�E�B���h�E�t���[���̍쐬
	make_flame(WIDTH,HEIGHT,MAIN_FLAME_X_OFFSET,MAIN_FLAME_Y_OFFSET);

	//�^�C�g�����S�錾
	char title[][100] = {
		{"�������� ��������                       "},                
		{" �� ����������                        "},                 
		{" �� �� ��������                       "},                
		{"   ���� �������������� ������������������ ����      "},
		{"   ���������� �������� �� �� ������ �� ����      "},  
		{"   �������������� �������� �� ����  ������������    "},
		{"                      �������������� �� "},
		{"	                    ������������������ "},
		{"                      �������� �� ��  "}
	};
	//���S�ړ����̕Еt���錾
	char title_space[][100] = {
		{"                         "},
		{"                         "},
		{"                         "},
		{"                         "},
		{"                         "},
		{"                         "},
		{"                         "},
		{"                         "},
		{"                         "},
	};
	
	/**
		* �������烍�S�̃X�N���[���J�n
		* �S�������ĂȂ��X�N���[���� �S����������Ԃ̃X�N���[��
		*/
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < i; j++){
			print_line(title[8 - j],15,i - j + 1);
		}
		fflush(stdout);
		usleep(0.2 * 1000000);
		print_lines(title_space,15,2,9);
	}

	print_lines(title,15,2,9);
	fflush(stdout);
	usleep(0.2 * 1000000);

	print_lines(title_space,15,2,9);
	print_lines(title,15,3,9);
	fflush(stdout);
	usleep(0.2 * 1000000);
	
	print_lines(title_space,15,3,9);
	print_lines(title,15,4,9);
	fflush(stdout);
	usleep(0.2 * 1000000);

	print_lines(title_space,15,4,9);
	print_lines(title,15,5,9);
	print_line("Press Enter",25,HEIGHT - 4);
	fflush(stdout);
	/* �����܂Ń��S�X�N���[������
	 * ���̒i�K�Ń��S��PressEnter��������
	 */

	//�������琯�̕`��
	//���̍��W�ϐ���錾
	int star_x[STAR_AMOUNT];// ={10,15,20};
	int star_y[STAR_AMOUNT];// ={20,15,10}; 
	//�����̏�����
	srand(time(NULL));
	//�����Ƃ��Ԃ�Ȃ��悤�ɍ��W��ݒ肷��
	for(int i = 0; i< STAR_AMOUNT;i++){
		//�܂�������U��
		star_x[i] = get_rand() % (WIDTH - 2) + 2;
		star_y[i] = get_rand() % (HEIGHT - 2) + 2;
		//�������W���^�C�g�����S�̂���͈͂Ƃ��Ԃ��Ă�����
		if(star_y[i] >= 5 && star_y[i] < 14){
			if(star_x[i] >= 15 && star_x[i] <= 46){
				mvcur(1,HEIGHT+1);
				//���̕ϐ��ɗ�����U�蒼�����߁A���x�������Z
				i--;
			}
		//PressEnter�Ƃ��Ԃ��Ă���������������������
		}else if(star_y[i] >= HEIGHT - 5 && star_y[i] <= HEIGHT - 3){
			if(star_x[i] >= 24 && star_x[i] <= 37){
				i--;
			}
		}
	}
	//���̓_�ŊJ�n Enter���͂�ҋ@���A�����ꂽ�烋�[�v�E�o
	do{
		stars(star_x,star_y,STAR_AMOUNT);
	}while((kbhit().input_char) == '�_0');
	
	//�t���[�����X�y�[�X���ߊJ�n
	flame_flush();
	/*for(int i = 2; i < HEIGHT; i++){
		for(int j = 2; j < WIDTH; j++){
			print_line(" ",j,i);
		}
		fflush(stdout);
		usleep(2 * 10000);
	}*/
	//�����܂�
	string_march("��34",10,10,10,10);
}
