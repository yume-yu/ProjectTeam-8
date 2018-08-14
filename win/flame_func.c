/**
 * @file flame_func.c
 * @brief �t���[������Ɋւ���֐����`����t�@�C��
 * @author yume_yu
 * @date 2018/07/09
 */
#include "thebeautifulsky.h"

/*
 * �t���[���̍쐬�֐�
 * width    �쐬����t���[���̕�
 * height   �쐬����t���[���̍���
 * offset_x �쐬����t���[���̊J�n�ʒu��x���W
 * offset_y �쐬����t���[���̊J�n�ʒu��y���W
 */
void make_flame(int width, int height, int offset_x, int offset_y){
	int print_width = width - 2;
	int print_height = height - 2;
	//1�s�ڂ̕`��
	mvcur(offset_x,offset_y);
	printf("��");
	for(int i = 0; i < print_width; i++){
		printf("��");
	}
	printf("��");
	//���ԕ����̕`��
	for(int i = 0; i < print_height; i++){
		mvcur(offset_x,offset_y + 1 + i);
		printf("��");
		for(int j = 0; j < print_width; j++){
			printf(" ");
		}
		printf("��");
	}

	//�ŏI�s�����̕`��
	mvcur(offset_x,offset_y + height - 1);
	printf("��");
	for(int i = 0; i < print_width; i++){
		printf("��");
	}
	printf("��");

	//�J�[�\���ʒu�̏�����
	mvcur(1,HEIGHT+1);
}

/**
 * �������t���[���̍쐬�֐�
 * width    �쐬����t���[���̕�
 * height   �쐬����t���[���̍���
 * offset_x �쐬����t���[���̊J�n�ʒu��x���W
 * offset_y �쐬����t���[���̊J�n�ʒu��y���W
 * split_x  �t���[���̋�؂��������x���W
 */
void make_vsflame(int width, int height, int offset_x, int offset_y, int split_x){
	int print_width = width - 2;
	int print_height = height - 2;
	//1�s�ڂ̕`��
	mvcur(offset_x,offset_y);
	printf("��");
	for(int i = 0; i < print_width; i++){
		if(i == split_x){
			printf("��");
		}else{
			printf("��");
		}
	}
	printf("��");
	//���ԕ����̕`��
	for(int i = 0; i < print_height; i++){
		mvcur(offset_x,offset_y + 1 + i);
		printf("��");
		for(int j = 0; j < print_width; j++){
			if(j == split_x){
				printf("��");
			}else{
				printf(" ");
			}
		}
		printf("��");
	}
	//�ŏI�s�����̕`��
	mvcur(offset_x,offset_y + height - 1);
	printf("��");
	for(int i = 0; i < print_width; i++){
		if(i == split_x){
			printf("��");
		}else{
			printf("��");
		}
	}
	printf("��");
#if defined WINDOWS
	printf("\n");
#elif defined MAC
	printf("%c",ENTERKEY);
#endif
	//�J�[�\���ʒu�̏�����
	mvcur(1,HEIGHT+1);
}

/**
 * �t���[�������A�j���[�V�����ŃX�y�[�X���߂ɂ���֐�
 */
void flame_flush(){
	for(int i = 2; i < HEIGHT; i++){
		for(int j = 2; j < WIDTH; j++){
			print_line(" ",j,i);
		}
		fflush(stdout);
		usleep(2 * 10000);
	}
}

/**
 * �t���[�������X�y�[�X���߂ɂ���֐�
 */
void flame_clean(){
	for(int i = 2; i < HEIGHT; i++){
		for(int j = 2; j < WIDTH; j++){
			mvcur(j,i);
			printf(" ");
		}
		//usleep(2 * 10000);
	}
	fflush(stdout);
}

/**
 * �w��t���[�������X�y�[�X���߂ɂ���֐�
 */
void sub_flame_clean(int width, int height, int x, int y){
	for(int i = y; i < y + height; i++){
		for(int j = x; j <x+  width;j++){
			print_line(" ",j,i);
		}
	}
	fflush(stdout);
}

/**
 * �w��ʒu,�T�C�Y�Ŋm�F�����o���֐�
 */
int check_window(int width, int height, int x, int y, char *string){
	arrow_pos yesno_pos[2] = {
		{x + width / 2 + 2,y+3},
		{x + width / 2 - 3,y+3}
	};
	make_flame(width,height,x,y);
	mvcur(x+2,y+1);
	printf("%s",string);
	print_line("y /  n",x + width / 2 - 2,y+3);
	return select_from_hlist(yesno_pos,2);
}

