/**
  * Writtenby yume_yu
  * windows��api���g���ăJ�[�\���̈ʒu���w��ӏ��ֈړ�����֐����`�����w�b�_
  */
 
#include <windows.h>
#include <conio.h>

//Windows��UNIX��Enter�L�[�̓��͂��قȂ�̂Ńv���O������̕\�L�𓝈�
#define ENTERKEY 0x0d

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
int mvcur(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}

struct input_assort{
	int kbhit_flag;
	int input_char;
};

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

/**
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

/**
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
  *  �X�e�[�^�X�֘A�֐�
  */

/**
  * �L�����N�^�[�̊�{�X�e�[�^�X�\����
  */
struct character{
	char *name;
	int hp;
	int max_hp;
	int max_atk;
	int min_atk;
};

/**
  * ����̊�{�X�e�[�^�X�\����
  */
struct weapon{
	char *name;
	int atk;
	int is_gun;
};

#define WEPONS_AMOUNT				3
#define WEPONS_AMOUNT_BACK	2

struct weapon all_weapons[7] = {
	{"No weapon",0,0},
	{"HandGun",15,1},
	{"Knife",5,0},
	//{"Bow",15,1}
};

struct weapon all_weapons4back[7] = {
	{"No weapon",0,0},
	{"Bow",10,1}
};
/**
  * �h��̊�{�X�e�[�^�X�\����
  */
struct protector{
	char *name;
	int def;
};

#define PROTECTORS_AMOUNT 3

struct protector all_protectors[7] = {
	{"No protector",0},
	{"Shield",10},
	{"Protective Suit",30}
};

/**
 * ����̃X�e�[�^�X�ݒ������֐�
 * tmpwp    �X�e�[�^�X��ݒ肷�镐��\���̂̃A�h���X
 * atk      ����̍U����
 * is_gun  	�e���ǂ����̃t���O
 */
void set_weapon_stat(struct weapon *tmpwp, int atk, int is_gun){
	tmpwp->atk = atk;
	tmpwp->is_gun = is_gun;
}

/**
 * �h��̃X�e�[�^�X�ݒ������֐�
 * tmppr    �X�e�[�^�X��ݒ肷�镐��\���̂̃A�h���X
 * def      ����̍U����
 */
void set_protector_stat(struct protector *tmppr, int def){
	tmppr->def = def;
}

/**
  * �L�����N�^�[�̃X�e�[�^�X�ݒ������֐�
  * name[10] �L�����N�^�[�̖��O
  * tmpch    �X�e�[�^�X��ݒ肷��L�����N�^�[�\���̂̃A�h���X
  * hp       �ݒ肷��hp
  * min_atk  �^�_���[�W�̉���
  * max_atk  �^�_���[�W�̏��
  */
void set_ch_stat(char name[10], struct character *tmpch, int hp, int min_atk, int max_atk){
	tmpch->name = name;
	tmpch->hp = hp;
	tmpch->max_hp = hp;
	tmpch->max_atk = max_atk;
	tmpch->min_atk = min_atk;
}

/**
  * �L�����N�^�[��HP��ϓ�������֐�
  * tmpch    hp���ϓ�����L�����N�^�[�\���̂̃A�h���X
  * damage   �_���[�W�� ���Ȃ猸�Z/���Ȃ���Z����� ex.damage��-20 �� 20��
  */
void change_hp(struct character *tmpch, int damage){
	tmpch->hp -= damage;
	if(tmpch->hp < 0){
		tmpch->hp = 0;
	}else if(tmpch->hp > tmpch->max_hp){
		tmpch->hp = tmpch->max_hp;
	}
}

/**
  *  UI�֘A�֐�
  */
  
//���̈ʒu���`���邽�߂̍\���́B���X�g�\���̍ۂɍ��W�z��Ƃ��Ďg��
struct arrow_pos{
	int x;
	int y;
	int not_active;
};

/**
  * ���X�g��\�������ۂɃJ�[�\���̏c�ړ��ƌ��肵�����ڂ��Ǘ�����֐�
  * tmp_pos[10] �J�[�\����\������ʒu���`����arrow_pos�^�̔z��
  * length      ���X�g���ڂ̐�
  * �߂�l length/Enter�������ꂽ�Ƃ��̍��ڂ̃��x��(���ڂ̃��j���[��������)
  */
int select_from_list(struct arrow_pos tmp_pos[10], int length){
	int arrow_pos_label = 0;
	struct input_assort tmp_input_list;
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
int select_from_hlist(struct arrow_pos tmp_pos[10], int length){
	int arrow_pos_label = 0;
	struct input_assort tmp_input_list;
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

int select_from_2dlist(int width, int height,struct arrow_pos tmp_pos[width][height]){
	struct arrow_pos arrow_pos_label = {0,0};
	struct input_assort tmp_input_list;
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

int check_window(int width, int height, int x, int y, char *string){
	struct arrow_pos yesno_pos[2] = {
		{x + width / 2 + 2,y+3},
		{x + width / 2 - 3,y+3}
		};
	make_flame(width,height,x,y);
	mvcur(x+2,y+1);
	printf("%s",string);
	print_line("y /  n",x + width / 2 - 2,y+3);
	return select_from_hlist(yesno_pos,2);
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

/**
  *  �^�C�g�����S�̏o���������ɈႤ�̂Ńw�b�_�Œ�`
  */
//�^�C�g�����S�錾
char title[][100] = {
	{"�������� ��������                       "},                
	{" �� ����������                        "},                 
	{" �� �� ��������                       "},                
	{"   ���� �������������� ������������������ ����      "},
	{"   ���������� �������� �� �� ������ �� ����      "},  
	{"   �������������� �������� �� ����  ������������    "},
	{"                      �������������� �� "},
	{"	                     ������������������ "},
	{"                      �������� �� ��  "}
};
//���S�ړ����̕Еt���錾
char title_space[][100] = {
	{"                                "},
	{"                                "},
	{"                                "},
	{"                                "},
	{"                                "},
	{"                                "},
	{"                                "},
	{"                                "},
	{"                                "}
};

/**
  *  ��������̏o�����Ⴄ�̂Ńw�b�_�Œ�`
  */
char control_explain[][100] = {
	"  w            ��   ",
	"a s d   as  �� �� ��"	
};