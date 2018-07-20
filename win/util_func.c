/**
 * @file util_func.c
 * @brief �ėp�I�Ȋ֐����`����t�@�C��
 * @author yume_yu
 * @date 2018/07/08
 */
#include "thebeautifulsky.h"
#ifdef WINDOWS

/**
 * Windows�ɂ̓}�C�N���b��sleep����usleep(int)���Ȃ��̂�
 * time �������~���鎞��[ms]
 */
void usleep(int time){
	Sleep(time/1000);
}

/**
 * �����(1,1)�Ƃ��ăJ�[�\�����w��ʒu�ֈړ�������֐�
 * x �J�[�\����x���W
 * y �J�[�\����y���W
 */
void mvcur(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(
			GetStdHandle(STD_OUTPUT_HANDLE),
			coord
			);
}

/*
 * �L�[�{�[�h��������Ă��邩�Ƃ��̓��̓L�[���Ƃ�֐�
 * �߂�l
 * input_assort temp	2�̃t���O�̍\����
 */
input_assort mykbhit(){
	input_assort temp;
	if(_kbhit()){
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

#endif

/**
 *  �Ȃɂ��̓��͂̑ҋ@������֐�
 */
void wait_anyinput(){
	mvcur(0,HEIGHT + 1);
	fflush(stdout);
	while(!mykbhit().kbhit_flag);
	while(mykbhit().kbhit_flag);
}

/**
 *  �����L�[�ȊO�̓��͂̑ҋ@������֐�
 */
void wait_input_without_arrow(){
	int flag = 1;
	input_assort tmp;
	mvcur(0,HEIGHT + 1);
	fflush(stdout);
	while(flag){
		tmp = mykbhit();
		switch(tmp.input_char){
			case 'a':
			case 's':
			case 'w':
			case 'd':
				break;
			default:
				if(tmp.kbhit_flag){
					flag = 0;
				}
				break;
		}
	}
	while(mykbhit().kbhit_flag);
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
void print_lines(char *string[], int x, int y, int num_lines){
	for(int i = 0; i < num_lines; i++){
		print_line(string[i],x,y+i);
	}
	mvcur(0,HEIGHT + 1);
}

/**
 * �w��ӏ��ւ̕����s�̃A�j���[�V�����������o�͂��s���֐�
 * string    �o�͂��镶����2�����z��
 * x         �o�͂��J�n����x���W
 * y         �o�͂��J�n����y���W
 * num_lines �o�͂���s��
 */
void string_march(extendstr *(tmp)[],int x,int y,int lines){
	char substring[100];
	for(int i = 0; i < lines; i++){
		for(int j = MULTIBYTE_CHAR_SIZE ; j < strlen(tmp[i]->string); j += MULTIBYTE_CHAR_SIZE ){
			mvcur(x + tmp[i]->offset,y + i);
			strncpy(substring,tmp[i]->string,j);
			substring[j] = '\0';
			printf("%s",substring);
			mvcur(0,HEIGHT + 1);
			fflush(stdout);
			input_assort now = mykbhit();
			if(now.kbhit_flag && now.input_char == ENTERKEY){
			}else{
				usleep(30 * 1000);
			}
		}
		if(!tmp[i]->not_need_return){
			wait_input_without_arrow();
			//wait_anyinput();
		}
	}
}

int eslengthof(extendstr sxstr[HEIGHT - 2]){
	int counter = 0;
	while(true){
		if(!strcmp(sxstr[counter].string,"")){
			break;
		}
		counter++;
	}
	return counter;
}


/**
 *	�\�����͂𕶏͂̃A�h���X�z��ɕϊ�����֐�
 */
void exstrcpy(extendstr *(to)[],extendstr from[],int lines){
	for(int i = 0; i < lines; i++){
		to[i] = &from[i];
	}
}

/**
 * ���X�g��\�������ۂɃJ�[�\���̏c�ړ��ƌ��肵�����ڂ��Ǘ�����֐�
 * tmp_pos[10] �J�[�\����\������ʒu���`����arrow_pos�^�̔z��
 * length      ���X�g���ڂ̐�
 * �߂�l length/Enter�������ꂽ�Ƃ��̍��ڂ̃��x��(���ڂ̃��j���[��������)
 */
int select_from_list(arrow_pos tmp_pos[10], int length){
	int arrow_pos_label = 0;
	input_assort tmp_input_list;
	print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
	while(1){
		while(!(tmp_input_list = mykbhit()).kbhit_flag);
		switch(tmp_input_list.input_char){
			case 'w':
				print_line(" ",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				if(arrow_pos_label <= 0){
					arrow_pos_label = length - 1;
				}else{
					arrow_pos_label--;
				}
				print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				continue;
				break;
			case 's':
				print_line(" ",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				if(arrow_pos_label >= length - 1){
					arrow_pos_label = 0;
				}else{
					arrow_pos_label++;
				}
				print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				continue;
				break;
			case ENTERKEY:
				break;
			default:
				continue;
				break;
		}
		break;
	}
	return arrow_pos_label;
}

/**
 * ���X�g��\�������ۂɃJ�[�\���̉��ړ��ƌ��肵�����ڂ��Ǘ�����֐�
 * tmp_pos[10] �J�[�\����\������ʒu���`����arrow_pos�^�̔z��
 * length      ���X�g���ڂ̐�
 * �߂�l length/Enter�������ꂽ�Ƃ��̍��ڂ̃��x��(���ڂ̃��j���[��������)
 */
int select_from_hlist(arrow_pos tmp_pos[10], int length){
	int arrow_pos_label = 0;
	input_assort tmp_input_list;
	print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
	while(1){
		while(!(tmp_input_list = mykbhit()).kbhit_flag);
		switch(tmp_input_list.input_char){
			case 'a':
				print_line(" ",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				if(arrow_pos_label <= 0){
					arrow_pos_label = length - 1;
				}else{
					arrow_pos_label--;
				}
				print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				continue;
				break;
			case 'd':
				print_line(" ",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				if(arrow_pos_label >= length - 1){
					arrow_pos_label = 0;
				}else{
					arrow_pos_label++;
				}
				print_line(">",tmp_pos[arrow_pos_label].x,tmp_pos[arrow_pos_label].y);
				continue;
				break;
			case ENTERKEY:
				break;
			default:
				continue;
				break;
		}
		break;
	}
	return arrow_pos_label;
}

/*
 * ���X�g��\�������ۂɃJ�[�\���̓񎟌��ړ��ƌ��肵�����ڂ��Ǘ�����֐�
 * tmp_pos[10][10]	�J�[�\����\������ʒu���`����arrow_pos�^�̔z��
 * length			���X�g���ڂ̐�
 * �߂�l
 * int length		Enter�������ꂽ�Ƃ��̍��ڂ̃��x��(���ڂ̃��j���[��������)
 */
int select_from_2dlist(int width, int height,arrow_pos tmp_pos[width][height]){
	arrow_pos arrow_pos_label = {0,0};
	input_assort tmp_input_list;
	print_line(">",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
	while(1){
		while(!(tmp_input_list = mykbhit()).kbhit_flag);

		print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
		switch(tmp_input_list.input_char){
			case 'w':
				do{
					if(arrow_pos_label.y <= 0){
						arrow_pos_label.y = height - 1;
					}else{
						arrow_pos_label.y--;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y].not_active);
				print_line(">",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
				continue;
				break;
			case 's':
				do{
					if(arrow_pos_label.y >= height - 1){
						arrow_pos_label.y= 0;
					}else{
						arrow_pos_label.y++;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y].not_active);
				print_line(">",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
				continue;
				break;
			case 'a':
				do{
					if(arrow_pos_label.x <= 0){
						arrow_pos_label.x = width - 1;
					}else{
						arrow_pos_label.x--;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y].not_active);
				print_line(">",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
				continue;
				break;
			case 'd':
				do{
					if(arrow_pos_label.x >= width - 1){
						arrow_pos_label.x= 0;
					}else{
						arrow_pos_label.x++;
					}
				}while(tmp_pos[arrow_pos_label.x][arrow_pos_label.y].not_active);
				print_line(">",tmp_pos[arrow_pos_label.x][arrow_pos_label.y].x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y].y);
				continue;
				break;
			case ENTERKEY:
				break;
			default:
				continue;
				break;
		}
		break;
	}
	return arrow_pos_label.x + width * arrow_pos_label.y;
}

