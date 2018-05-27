/**
  * Writtenby yume_yu
  * windows��api���g���ăJ�[�\���̈ʒu���w��ӏ��ֈړ�����֐����`�����w�b�_
  */
 
#include <windows.h>
#include <conio.h>

//Windows��UNIX��Enter�L�[�̓��͂��قȂ�̂Ńv���O������̕\�L�𓝈�
#define ENTERKEY 0x0d

/** 
  * �����(1,1)�Ƃ��ăJ�[�\�����w��ʒu�ֈړ�������֐�
  * x �J�[�\����x���W
  * y �J�[�\����y���W
  */
int mvcur(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}

/*
 * ���͎���������\����
 * kbhit_flag	�L�[��������Ă��邩��Ԃ�int
 * input_char	������Ă���L�[
 */
struct input_assort{
	int kbhit_flag;
	int input_char;
};

/*
 * �L�[�{�[�h��������Ă��邩�Ƃ��̓��̓L�[���Ƃ�֐�
 * �߂�l
 * struct input_assort temp	2�̃t���O�̍\����
 */
struct input_assort mykbhit(){
	struct input_assort temp;
	if(kbhit()){
		temp.input_char =  _getch();
		temp.kbhit_flag = 1;
	}else{
		temp.input_char = 0;
		temp.kbhit_flag = 0;
	}
	return temp;
}

/** 
 * �W���o�͂̏�����
 */
void init_term(){
	//�J�[�\���ʒu��(1,1)�Ɉړ�
	mvcur(1,1);
}

/**
 * �w��ӏ��ւ�1�s�̕����o�͂��s���֐�
 * string �o�͂��镶����
 * x      �o�͂���x���W
 * y      �o�͂���y���W
 */
void print_line(char string[], int x, int y){
	mvcur(x,y);
	printf("%s",string);
	mvcur(0,HEIGHT + 1);
}

/*
 * �w��ӏ��ւ̕����s�s�̕����o�͂��s���֐�
 * string    �o�͂��镶����z��
 * x         �o�͂��J�n����x���W
 * y         �o�͂��J�n����y���W
 * num_lines �o�͂���s��
 */
void print_lines(char string[][100], int x, int y, int num_lines){
	for(int i = 0; i < num_lines; i++){
		mvcur(x,y+i);
		printf("%s",string[i]);
	}
	mvcur(0,HEIGHT + 1);
}

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


	printf("��\n");

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
  *  Enter���͂̑ҋ@������֐�
  */
void wait_anyinput(){
	mvcur(0,HEIGHT + 1);
	fflush(stdout);
	while(!mykbhit().kbhit_flag);
	while(mykbhit().kbhit_flag);
}
