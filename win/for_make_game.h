/**
 * Written by yume_yu
 * printf()�݂̂��g�p�����Q�[������邽�߂̃w�b�_
 */

#include "thebeautifulsky.h"
//���݂̃X�e�[�W
stage now_stage = stage1;
char *(now_map)[WIDTH - 2];
arrow_pos *(now_map_coor)[WIDTH - 2][HEIGHT - 2];
int room_id = 0;
arrow_pos start_pos = {0,15,0,0};
extendstr *now_text[HEIGHT];

//�}�b�v�ƍ��W�n�ꗗ�̐錾
char *(maps)[9][HEIGHT - 2];
arrow_pos *(map_coors)[10][WIDTH - 2][HEIGHT - 2];


/**
 *  �^�C�g�����S�̏o���������ɈႤ�̂Ńw�b�_�Œ�`
 */
//�^�C�g�����S�錾
char *(title)[9] = {
	"�������� ��������                       ",
	" �� ����������                        ",
	" �� �� ��������                       ",
	"   ���� �������������� ������������������ ����      ",
	"   ���������� �������� �� �� ������ �� ����      ",
	"   �������������� �������� �� ����  ������������    ",
	"                      �������������� �� ",
	"	                     ������������������ ",
	"                      �������� �� ��  "
};
//���S�ړ����̕Еt���錾
char *(title_space)[9] = {
	"                                ",
	"                                ",
	"                                ",
	"                                ",
	"                                ",
	"                                ",
	"                                ",
	"                                ",
	"                                "
};

char *(gameover)[] = {
	"������������������������  ��������  ��������������",
	"�� ������������������   �� �������������� ������",
	"�������� ���� ��������  ������ ���� ������������",
};

/**
 *	�^�C�g����ʂ̐��̃A�j���[�V�����������ꂽ�֐�
 */
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
}

/**
 *	�^�C�g����ʂ�\������֐�
 */
int maintitle(){
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
		mykbhit();
	}

	print_lines(title,15,2,9);
	fflush(stdout);
	usleep(0.2 * 1000000);
	mykbhit();

	print_lines(title_space,15,2,9);
	print_lines(title,15,3,9);
	fflush(stdout);
	usleep(0.2 * 1000000);
	mykbhit();

	print_lines(title_space,15,3,9);
	print_lines(title,15,4,9);
	fflush(stdout);
	usleep(0.2 * 1000000);
	mykbhit();

	print_lines(title_space,15,4,9);
	print_lines(title,15,5,9);
	print_line("Press Enter",25,HEIGHT - 4);
	fflush(stdout);
	mykbhit();
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
		star_x[i] = rand() % (WIDTH - 2) + 2;
		star_y[i] = rand() % (HEIGHT - 2) + 2;
		//�������W���^�C�g�����S�̂���͈͂Ƃ��Ԃ��Ă�����
		if(star_y[i] >= 5 && star_y[i] < 15){
			if(star_x[i] >= 15 && star_x[i] <= 46){
				i--;	//���̕ϐ��ɗ�����U�蒼�����߁A���x�������Z
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
	}while((mykbhit().input_char) != ENTERKEY);
	char *(select_start)[] =	{										//�Q�[���J�n�̑I�����̕�����
		"     ����������݂�",
		"     �Q�[�����n�߂�",
		"",
		"W/S �I��      Enter ����"
	};
	arrow_pos title_command_pos[] = {
		{TITLE_MENU_BASE_X + 4,TITLE_MENU_BASE_Y,0,0},
		{TITLE_MENU_BASE_X + 4,TITLE_MENU_BASE_Y + 1,0,0}
	};
	make_flame(24 + 5,7,TITLE_MENU_BASE_X - 3,TITLE_MENU_BASE_Y - 2);
	print_lines(select_start,TITLE_MENU_BASE_X,TITLE_MENU_BASE_Y,lengthof(select_start,char *));
	return !select_from_list(title_command_pos,2);
}

void gameover_lose(){

}

void gameover_win(){
	print_lines(gameover,(WIDTH - 27) / 2,(HEIGHT - 3) / 2,3);
	wait_anyinput();
}
