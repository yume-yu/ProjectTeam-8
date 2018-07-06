/**
 * Written by yume_yu
 * printf()�݂̂��g�p�����Q�[������邽�߂̃w�b�_
 */

//�K�v�ȃ��C�u�������C���N���[�h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//�萔��`��
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
 * �X�e�[�W�Z���N�g�t���[���֘A�萔
 * SELECT_STAGE_FLAME_WIDTH  �t���[���̕�
 * SELECT_STAGE_FLAME_HEIGHT �t���[���̍���
 * SELECT_STAGE_FLAME_X      �t���[���̊J�n�ʒu��X���W
 * SELECT_STAGE_FLAME_Y      �t���[���̊J�n�ʒu��Y���W
 */
#define SELECT_STAGE_FLAME_WIDTH  				25
#define SELECT_STAGE_FLAME_HEIGHT 				11
#define SELECT_STAGE_FLAME_X      				(WIDTH  - SELECT_STAGE_FLAME_WIDTH) / 2
#define SELECT_STAGE_FLAME_Y      				(HEIGHT - SELECT_STAGE_FLAME_HEIGHT) / 2

/**
 * �퓬��ʂł̃E�B���h�E�T�C�Y/�z�u�֘A�萔
 * BATTLE_MODE_STATUS_FLAME_WIDTH   �������t���[���̕�
 * BATTLE_MODE_STATUS_FLAME_HEIGHT  �������t���[���̍���
 * BATTLE_MODE_STATUS_FLAME_X       �������t���[���̊J�n�ʒu��X���W
 * BATTLE_MODE_STATUS_FLAME_SPLIT_X �������t���[���̕����ʒu
 * BATTLE_MODE_COMMAND_POS          �퓬�R�}���h�u���[��(����)��1�s�ڂ�X���W
 * BATTLE_MODE_STATUS_HP_POS        �X�e�[�^�X�t���[��(���E)��1�s�ڂ�X���W
 */
#define BATTLE_MODE_STATUS_FLAME_WIDTH		WIDTH-2
#define BATTLE_MODE_STATUS_FLAME_HEIGHT		6
#define BATTLE_MODE_STATUS_FLAME_X				2
#define BATTLE_MODE_STATUS_FLAME_SPLIT_X 	2*(WIDTH-2)/3-1 -2
#define BATTLE_MODE_COMMAND_POS 					7
#define BATTLE_MODE_STATUS_HP_POS 				BATTLE_MODE_STATUS_FLAME_SPLIT_X+5 

/*
 * �L�����N�^�[�X�e�[�^�X�ݒ胂�[�h�֘A�萔
 * EDIT_MODE_SELECT_FLAME_WIDTH
 * EDIT_MODE_SELECT_FLAME_HEIGHT
 * EDIT_MODE_SELECT_FLAME_X
 * EDIT_MODE_SELECT_FLAME_Y
 * EDIT_MODE_EDIT_FLAME_CHAR_X
 * EDIT_MODE_EDIT_FLAME_CHAR_Y
 */
#define EDIT_MODE_SELECT_FLAME_WIDTH			WIDTH - 4
#define EDIT_MODE_SELECT_FLAME_HEIGHT			10
#define EDIT_MODE_SELECT_FLAME_X					3
#define EDIT_MODE_SELECT_FLAME_Y					2
#define EDIT_MODE_EDIT_FLAME_WIDTH				WIDTH - 4
#define EDIT_MODE_EDIT_FLAME_HEIGHT				HEIGHT - 12
#define EDIT_MODE_EDIT_FLAME_X						3
#define EDIT_MODE_EDIT_FLAME_Y						12
#define EDIT_MODE_EDIT_FLAME_CHAR_X				6
#define EDIT_MODE_EDIT_FLAME_CHAR_Y 			14
#define ECHECK_SELECT_FLAME_WIDTH  				WIDTH / 4 + 3
#define ECHECK_SELECT_FLAME_HEIGHT 				HEIGHT / 4
#define ECHECK_SELECT_FLAME_X							WIDTH / 4 + 8
#define ECHECK_SELECT_FLAME_Y      				3 * HEIGHT / 4
#define ECHECK_TEMPLATE_FLAME_WIDTH  			WIDTH / 4 + 10
#define ECHECK_TEMPLATE_FLAME_HEIGHT 			HEIGHT / 4
#define ECHECK_TEMPLATE_FLAME_X      			WIDTH / 4 + 3
#define ECHECK_TEMPLATE_FLAME_Y      			HEIGHT / 2 + 3

#define SELECT_MODE_FLAME_HEIGHT_OFFSET 	2
#define SCHECK_SELECT_FLAME_WIDTH  				WIDTH / 4
#define SCHECK_SELECT_FLAME_HEIGHT 				HEIGHT / 4
#define SCHECK_SELECT_FLAME_X      				WIDTH / 4 + 8
#define SCHECK_SELECT_FLAME_Y      				HEIGHT / 2 - 6
#define SELECT_MODE_EQIP_FLAME_WIDTH			WIDTH / 2 - 6
#define SELECT_MODE_POTION_FLAME_HEIGHT		3
#define SELECT_MODE_EQIP_FLAME_HEIGHT			6
#define SELECT_MODE_EQIP_FLAME_X					3 + WIDTH / 2 + 2
#define SELECT_MODE_EQIP_FLAME_Y					SELECT_MODE_FLAME_HEIGHT_OFFSET
#define SELECT_MODE_EQIP_CHARASET_X				SELECT_MODE_EQIP_FLAME_X + SELECT_MODE_EQIP_FLAME_WIDTH - 2

#define CHARACTER_STATUS_ATK_DIFF 				10
#define CHARACTER_STATUS_HP_DIFF 					20

#define SET_WEAPON_MODE_FLAME_WIDTH 			18
#define SET_WEAPON_MODE_FLAME_HEIGHT 			7
#define SET_WEAPON_MODE_FLAME_X 					(WIDTH - SET_WEAPON_MODE_FLAME_WIDTH) / 2
#define SET_WEAPON_MODE_FLAME_Y 					(HEIGHT - SET_WEAPON_MODE_FLAME_HEIGHT) / 2
#define SET_WEAPON_EDIT_FLAME_CHAR_X 			5
#define SET_WEAPON_EDIT_FLAME_CHAR_Y 			13

#define EDIT_EQIP_SELECT_FLAME_X					2
#define EDIT_EQIP_SELECT_FLAME_Y					2
#define EDIT_EQIP_SELECT_FLAME_WIDTH			(WIDTH - 2)
#define EDIT_EQIP_SELECT_FLAME_HEIGHT			(HEIGHT - 2) / 3
#define EDIT_EQIP_EDIT_FLAME_X						2
#define EDIT_EQIP_EDIT_FLAME_Y						EDIT_EQIP_SELECT_FLAME_HEIGHT + 1
#define EDIT_EQIP_EDIT_FLAME_WIDTH				(WIDTH - 2)
#define EDIT_EQIP_EDIT_FLAME_HEIGHT				2* (HEIGHT - 2) / 3

//�^�C�g����ʂ̐��̐�
#define STAR_AMOUNT 											50
#define TITLE_MENU_BASE_X									(WIDTH - 24)/2
#define TITLE_MENU_BASE_Y									HEIGHT - 5

//�L�����N�^�[�X�e�[�^�X�ݒ�萔
#define FRONT1_NAME				"���[����"
#define FRONT1_HP					110
#define FRONT1_MINATK			15
#define FRONT1_MAXATK			20
#define FRONT2_NAME				"�i�I�L"
#define FRONT2_HP_ST2			90
#define FRONT2_MINATK_ST2	20
#define FRONT2_MAXATK_ST2	35
#define FRONT2_HP_ST3			110
#define FRONT2_MINATK_ST3	30
#define FRONT2_MAXATK_ST3	45
#define FRONT2_HP_ST4			130
#define FRONT2_MINATK_ST4	40
#define FRONT2_MAXATK_ST4	55
#define FRONT3_NAME				"Robo1"
#define FRONT3_HP					2000
#define FRONT3_MINATK			140
#define FRONT3_MAXATK			150
#define FRONT3_SP_DAMAGE	1500
#define FRONT4_NAME				"Robo2"
#define FRONT4_HP					5000
#define FRONT4_MINATK			400
#define FRONT4_MAXATK			450
#define BACK_NAME					"�A���X�g"
#define BACK_HP_ST1				70
#define BACK_HEAL_ST1 		20
#define BACK_HP_ST2				90
#define BACK_HEAL_ST2 		30
#define BACK_HP_ST3				110
#define BACK_HEAL_ST3 		40
#define BACK_HP_ST4				130
#define BACK_HEAL_ST4 		50
#define BACK_ATTACK				35
#define ST1_BOSS_NAME			"St1Bs"
#define ST1_BOSS_HP				100
#define ST1_BOSS_MINATK		10
#define ST1_BOSS_MAXATK		20
#define ST2_BOSS_NAME			"�^�N�g"
#define ST2_BOSS_HP				150
#define ST2_BOSS_MINATK		30
#define ST2_BOSS_MAXATK		40
#define ST3_BOSS_NAME			"St3Bs"
#define ST3_BOSS_HP				250
#define ST3_BOSS_MINATK		50
#define ST3_BOSS_MAXATK		60
#define ST4_BOSS_NAME			"St4Bs"
#define ST4_BOSS_HP				1000
#define ST4_BOSS_MINATK		100
#define ST4_BOSS_MAXATK		130
#define ST5_BOSS_NAME			"St5Bs"
#define ST5_BOSS_HP				3000
#define ST5_BOSS_MINATK		300
#define ST5_BOSS_MAXATK		400


#define lengthof(var,type) (sizeof(var)/sizeof(type))

/*
 * ���̈ʒu���`���邽�߂̍\���́B���X�g�\���̍ۂɍ��W�z��Ƃ��Ďg��
 * int x			x���W
 * int y			y���W
 * int not_active	�Ώۂ̍��W���ړ��\���̃t���O(1�Ȃ�ړ��s��)
 */
struct arrow_pos{
	int x;
	int y;
	int not_active;
	int at_event;
};

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

/**
 * �h��̊�{�X�e�[�^�X�\����
 */
struct protector{
	char *name;
	int def;
};

/**
 *	�X�g�[���[���\��������̍\����
 */
struct extendstr{
	char string[100];
	int offset;
	int not_need_return;
};

//�K�v�L�����N�^-�̒�`
struct character naoki;
struct character lirel;
struct character arist;
struct character robo;
struct character boss1;
struct character boss2;
struct character dummy;
struct character *front;
struct character *back;
struct character *(enemies)[3];
int enemy_amount = 0;

//�O�q�����̐錾
struct weapon all_weapons[7] = {
	{"No weapon",0,0},
	{"HandGun",15,1},
	{"Knife",5,0},
	//{"Bow",30,1}
};

//��q�����̐錾
struct weapon all_weapons4back[7] = {
	{"No weapon",0,0},
	{"Bow",10,1}
};

//�h��̐錾
struct protector all_protectors[7] = {
	{"No protector",0},
	{"Shield",40},
	{"Protective Suit",55}
};

//�����g�̐錾
struct weapon *using_weapon;
struct protector *using_protector;
struct weapon *arist_using_weapon;
struct protector *arist_using_protector;
int potion_amount = 0;
int have_nasu = 0;

/**
 * @enum event
 * �X�e�[�W�̃}�b�v�ꗗ
 */
enum stage {
	stage1,
	stage2,
	stage3_1,
	stage3_2,
	stage3_3,
	stage4_1,
	stage4_2,
	stage4_3,
	stage5,
	ope_exp
};

/**
 * @enum event
 * �N����C�x���g�̈ꗗ
 */
enum event {
	battle_event,
	talk_event,
	move_map,
	open_menu
};

//���݂̃X�e�[�W
enum stage now_stage = stage1;
char *(now_map)[23];
struct arrow_pos *(now_map_coor)[WIDTH - 2][HEIGHT - 2];
int room_id = 0;
struct arrow_pos start_pos = {0,15,0,0};
struct extendstr *now_text[HEIGHT];

//�}�b�v�ƍ��W�n�ꗗ�̐錾
char *(maps)[9][HEIGHT - 2];
struct arrow_pos *(map_coors)[10][WIDTH - 2][HEIGHT - 2];

//�}�b�v�̓ǂݍ���
#include "map_exp.h"
#include "map_st1.h"
#include "map_st2.h"
#include "map_st3.h"
#include "map_st4.h"

//�X�g�[���[�̓ǂݍ���
#include "storytexts.h"

#include <windows.h>
#include <conio.h>

//Windows��UNIX��Enter�L�[�̓��͂��قȂ�̂Ńv���O������̕\�L�𓝈�
#define ENTERKEY 0x0d
//�}���`�o�C�g�����̑傫����OS�Ŏ኱�Ⴄ(�����R�[�h?)
#define MULTIBYTE_CHAR_SIZE 2

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
	struct input_assort tmp;
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
void string_march(struct extendstr *(tmp)[],int x,int y,int lines){
	char substring[100];
	for(int i = 0; i < lines; i++){
		for(int j = MULTIBYTE_CHAR_SIZE ; j < strlen(tmp[i]->string); j += MULTIBYTE_CHAR_SIZE ){
			mvcur(x + tmp[i]->offset,y + i);
			strncpy(substring,tmp[i]->string,j);
			substring[j] = '\0';
			printf("%s",substring);
			mvcur(0,HEIGHT + 1);
			fflush(stdout);
			struct input_assort now = mykbhit();
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

/**
 *	�}�b�v���R�s�[����֐�
 */
void mapcpy(char *(to)[HEIGHT - 2],char *(from)[HEIGHT - 2]){
	for(int i = 0; i <  HEIGHT -2; i++){
		//strcpy(to[i],from[i]);
		to[i] = from[i];
	}
}

/**
 *	���W�z������W�̃A�h���X�z��ɕϊ�����֐�
 */
void coor_cnv_adr(struct arrow_pos *(to)[WIDTH - 2][HEIGHT - 2],struct arrow_pos from[WIDTH - 2][HEIGHT - 2]){
	for(int i = 0; i < WIDTH - 2; i++){
		for(int j = 0; j < HEIGHT - 2; j++){
			to[i][j] = &from[i][j];
		}
	}
}

/**
 *	���W�̃A�h���X�z����R�s�[����֐�
 */
void coorcpy(struct arrow_pos *(to)[WIDTH - 2][HEIGHT - 2],struct arrow_pos *(from)[WIDTH - 2][HEIGHT - 2]){
	for(int i = 0; i < WIDTH - 2; i++){
		for(int j = 0; j < HEIGHT - 2; j++){
			to[i][j] = from[i][j];
		}
	}
}

/**
 *	�\�����͂𕶏͂̃A�h���X�z��ɕϊ�����֐�
 */
void exstrcpy(struct extendstr *(to)[],struct extendstr from[],int lines){
	for(int i = 0; i < lines; i++){
		to[i] = &from[i];
	}
}

/**
 * �L�����N�^�[�̃X�e�[�^�X�ݒ������֐�
 * name[10] �L�����N�^�[�̖��O
 * tmpch    �X�e�[�^�X��ݒ肷��L�����N�^�[�\���̂̃A�h���X
 * hp       �ݒ肷��hp
 * min_atk  �^�_���[�W�̉���
 * max_atk  �^�_���[�W�̏��
 */
void set_ch_stat(char name[10], struct character *tmpch, int hp, int max_hp,int min_atk, int max_atk){
	tmpch->name = name;
	tmpch->hp = hp;
	tmpch->max_hp = max_hp;
	tmpch->max_atk = max_atk;
	tmpch->min_atk = min_atk;
}

/**
 * @fn
 * �Q�[���J�n���̍��W�ƃX�e�[�W������������֐�
 * @brief start_pos��now_stage�̏�����
 * @detail ���[�v���A����`���[�g���A���I�����ȂǂɃQ�[�����n�߂�Ƃ��ɏ��������ׂ�����������������
 */
void reset_state(){
	room_id = 0;
	potion_amount = 0;
	start_pos.x = 0;
	start_pos.y = 15;
	now_stage = stage1;
}

/*
 *	�}�b�v�z��̏�����
 */
void initmaps(){
	mapcpy(maps[stage1],map_st1);
	mapcpy(maps[stage2],map_st2);
	mapcpy(maps[stage3_1],map_st3_1);
	mapcpy(maps[stage3_2],map_st3_2);
	mapcpy(maps[stage3_3],map_st3_3);
	mapcpy(maps[stage4_1],map_st4_1);
	mapcpy(maps[stage4_2],map_st4_2);
	mapcpy(maps[stage4_3],map_st4_3);
	mapcpy(maps[ope_exp],map_exp);
	coor_cnv_adr(map_coors[stage1],st1_pos);
	coor_cnv_adr(map_coors[stage2],st2_pos);
	coor_cnv_adr(map_coors[stage3_1],st3_1_pos);
	coor_cnv_adr(map_coors[stage3_2],st3_2_pos);
	coor_cnv_adr(map_coors[stage3_3],st3_3_pos);
	coor_cnv_adr(map_coors[stage4_1],st4_1_pos);
	coor_cnv_adr(map_coors[stage4_2],st4_2_pos);
	coor_cnv_adr(map_coors[stage4_3],st4_3_pos);
	coor_cnv_adr(map_coors[ope_exp],exp_pos);
	mapcpy(now_map,maps[now_stage]);
	coorcpy(now_map_coor,map_coors[now_stage]);
	reset_state();
}


//�e�L�����N�^�[�̃X�e�[�^�X������
void initchara(){
	set_ch_stat(FRONT2_NAME,&naoki,FRONT2_HP_ST2,FRONT2_HP_ST2,FRONT2_MINATK_ST2,FRONT2_MAXATK_ST2);
	set_ch_stat(FRONT1_NAME,&lirel,FRONT1_HP,FRONT1_HP,FRONT1_MINATK,FRONT1_MAXATK);
	set_ch_stat(BACK_NAME,&arist,BACK_HP_ST1,BACK_HP_ST1,0,BACK_HEAL_ST1);
	set_ch_stat(FRONT3_NAME,&robo,FRONT3_HP,FRONT3_HP,FRONT3_MINATK,FRONT3_MAXATK);
	set_ch_stat("boss1",&boss1,100,100,10,20);
	set_ch_stat("boss2",&boss2,100,100,10,20);
	set_ch_stat("dummy",&dummy,0,0,0,0);
	//������f��ɏ�����
	using_weapon = &all_weapons[0];
	using_protector = &all_protectors[0];
	arist_using_weapon = &all_weapons4back[0];
	arist_using_protector = &all_protectors[0];
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
 * @fn
 * �|�[�V�����̎擾
 * @brief �|�[�V�����̎擾�����s������ꂽ����Ԃ�
 * @return �|�[�V����������ꂽ��
 * @detail �|�[�V�����̏��������m�F���A3�����Ȃ�|�[�V�������擾����1��Ԃ��B��������3�𒴂��Ă�����0��Ԃ�
 */
int get_potion(){
	if(potion_amount < 3){
		potion_amount++;
		return 1;
	}else{
		return 0;
	}
}


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

/*
 * ���X�g��\�������ۂɃJ�[�\���̓񎟌��ړ��ƌ��肵�����ڂ��Ǘ�����֐�
 * tmp_pos[10][10]	�J�[�\����\������ʒu���`����arrow_pos�^�̔z��
 * length			���X�g���ڂ̐�
 * �߂�l
 * int length		Enter�������ꂽ�Ƃ��̍��ڂ̃��x��(���ڂ̃��j���[��������)
 */
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

/*
 * �}�b�v����ړ�����֐�
 * width						�}�b�v�̕�
 * hright 					�}�b�v�̍���
 * tmp_pos[10][10]	�}�b�v���W�̔z��
 * offset						����󂯕t���J�n���̍��W
 * �߂�l
 * int tmp_pos			���[�v�𔲂����ۂ̍��W
 */
struct arrow_pos move_on_map(int width, int height,struct arrow_pos *(tmp_pos)[WIDTH -2 ][HEIGHT - 2], struct arrow_pos offset){
	struct arrow_pos arrow_pos_label = offset;
	struct arrow_pos return_value;
	struct input_assort tmp_input_list;
	print_line("��",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
	while(1){
		while(!(tmp_input_list = mykbhit()).kbhit_flag);
		switch(tmp_input_list.input_char){
			case 'w':
				print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				if(arrow_pos_label.y <= 0 || tmp_pos[arrow_pos_label.x][arrow_pos_label.y - 1]->not_active){
				}else{
					arrow_pos_label.y--;
				}
				print_line("��",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				break;

			case 's':
				print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				if(arrow_pos_label.y > height - 2 || tmp_pos[arrow_pos_label.x][arrow_pos_label.y + 1]->not_active){
				}else{
					arrow_pos_label.y++;
				}
				print_line("��",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				break;

			case 'a':
				print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				if(arrow_pos_label.x <= 0 || tmp_pos[arrow_pos_label.x - 1][arrow_pos_label.y]->not_active){
				}else{
					arrow_pos_label.x--;
				}
				print_line("��",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				break;

			case 'd':
				print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				if(arrow_pos_label.x > width - 2 || tmp_pos[arrow_pos_label.x + 1][arrow_pos_label.y]->not_active){
				}else{
					arrow_pos_label.x++;
				}
				print_line("��",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				break;
			case ENTERKEY:
				break;
			case ' ':
				start_pos =*tmp_pos[arrow_pos_label.x][arrow_pos_label.y];
				start_pos.x -= 2;
				start_pos.y -= 2;
				arrow_pos_label.x = width - 2;
				arrow_pos_label.y = height - 1;
				return *tmp_pos[arrow_pos_label.x][arrow_pos_label.y];
				break;
			default:
				//print_line("��",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				continue;
				//break;
		}
		//�f�o�b�O�p���W�\��
		//printf("%2d,%2d",arrow_pos_label.x,arrow_pos_label.y);
		//printf("%2d,%2d %2d,%2d %d",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y,arrow_pos_label.x,arrow_pos_label.y,tmp_pos[arrow_pos_label.x][arrow_pos_label.y + 1]->not_active);
		if(tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->at_event){
			break;
		}
	}
	return *tmp_pos[arrow_pos_label.x][arrow_pos_label.y];
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
 *  ��������̏o�����Ⴄ�̂Ńw�b�_�Œ�`
 */
char control_explain[][100] = {
	"  w            ��   ",
	"a s d   as  �� �� ��"
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
	print_line("Beta Ver",(WIDTH - 8)/2,14);
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
	struct arrow_pos title_command_pos[] = {
		{TITLE_MENU_BASE_X + 4,TITLE_MENU_BASE_Y,0,0},
		{TITLE_MENU_BASE_X + 4,TITLE_MENU_BASE_Y + 1,0,0}
	};
	make_flame(24 + 5,7,TITLE_MENU_BASE_X - 3,TITLE_MENU_BASE_Y - 2);
	print_lines(select_start,TITLE_MENU_BASE_X,TITLE_MENU_BASE_Y,lengthof(select_start,char *));
	return !select_from_list(title_command_pos,2);
}

/*
 * �퓬�n�֐���������
 */

//�퓬���[�h�̎��ɃR�}���h�����\������֐�
void print_bt_commands(){
	print_line("��������",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
	print_line("�Ƃ�����",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
	print_line("���΂�",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3);
	print_line("�ǂ���",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 4);
	fflush(stdout);
}

//�G��HP�Q�[�W��`�悷��֐�
void print_health_bar(struct character *target[],int amount){
	double health_par = 0;
	for(int i = 0; i < amount; i++){
		make_flame(20,3,2,2 + 3 * i);
		print_line("                    ",2,2+3*i);
		mvcur(2,2 + 3 * i);
		printf("[");
		mvcur(WIDTH - 1,2 + 3 * i);
		printf("]");
		mvcur(3,3 + 3 * i);
		printf("%s",target[i]->name);
		health_par = ( (double)target[i]->hp / target[i]->max_hp) * ( WIDTH - 4 );
		for(int j = 0; j < WIDTH - 4;j++){
			mvcur(3+j,2 + 3 * i);
			if(j < health_par){
				printf("=");
			}else{
				printf(" ");
			}
		}
		//printf("%f�_n%d�_n%d",health_par,target[i]->hp,target[i]->max_hp);
		fflush(stdout);
	}
}

//�퓬���[�h�̎���HP������`�悷��֐�
void print_bt_status(struct character *front,struct character *back){
	//�X�e�[�^�X�����\��
	char *(spaces)[] = {
		"               ",
		"               "
	};
	print_lines(spaces,BATTLE_MODE_STATUS_HP_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,2);
	print_line("HP",BATTLE_MODE_STATUS_HP_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
	mvcur(BATTLE_MODE_STATUS_HP_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
	printf("%-8s:%4d/%4d",front->name,front->hp,front->max_hp);
	if(strcmp(back->name,"dummy")){
		mvcur(BATTLE_MODE_STATUS_HP_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3);
		printf("%-8s:%4d/%4d",back->name,back->hp,back->max_hp);
	}
	mvcur(0,HEIGHT + 1);
	fflush(stdout);
}

//�퓬���[�h
int battle(struct character *front,struct character *back,struct character *enemies[3], int enemy_amount){
	int finish_flag = 0;												//�퓬�I���̃t���O
	int protect_flag = 0;												//���΂��s���̃t���O
	int damage = 0;															//�v�Z��̃_���[�W���L������ϐ�
	int target_label = 0;												//�U���Ώۂ𔻒f���邽�߂̕ϐ�
	int turn_count = 1;													//����s���̂��ߐ퓬�J�n����̃^�[���𐔂���ϐ�
	int sp_count = 0;														//����s���̍s���s�\�^�[���𐔂���ϐ�
	int enemies_dead_check = 0;									//�G���S�ł������ǂ����`�F�b�N���鎞�Ɏg���ϐ�
	int player_can_act = 1;											//�v���C���[���s���\���̃t���O
	int used_flare = 0;													//�X�e�[�W5�ł̖�������s���̎g�p��t���O
	int enemy_amount_for_bar = enemy_amount;		//HP�Q�[�W�`��̂��߁A�{���̓G�̐����L������ϐ�
	struct character *for_bar[enemy_amount];		//HP�Q�[�W�`��̂��߁A�{���̓G�̃A�h���X���L������ϐ�
	for(int i = 0;i < enemy_amount;i++){
		for_bar[i] = enemies[i];
	}
	struct arrow_pos battle_menu_arrow[] = {
		{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1},
		{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2},
		{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3},
		{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 4}
	};

	//�G��HP��������
	for(int i = 0; i < enemy_amount; i++){
		change_hp(enemies[i],-1 * enemies[i]->max_hp);
	}
	flame_flush();
	make_vsflame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_SPLIT_X);

	print_bt_status(front,back);
	print_health_bar(for_bar,enemy_amount_for_bar);

	while(!finish_flag){
		mvcur(BATTLE_MODE_STATUS_FLAME_X + 2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT - 1);
		printf("Turn %2d",turn_count);

		/*�v���C���[�̍s�� ��������*/
		if(player_can_act){
			print_bt_commands();																			//�v���C���[�̃R�}���h��\������
			int command = select_from_list(battle_menu_arrow,4);			//�R�}���h���͂��󂯕t����	
			sub_flame_clean(																					//�R�}���h�����t���[���N���[��	
					BATTLE_MODE_STATUS_FLAME_SPLIT_X,
					BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,
					BATTLE_MODE_STATUS_FLAME_X + 1,
					HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1
					);
			switch(command){
				case 0:																																		//attack(�U��)��������
					/*�G�̈ꗗ�\�� ��������*/
					for(int i = 0; i <= enemy_amount; i++){
						mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1 + i);
						if(i < enemy_amount){
							printf("%s",enemies[i]->name);
						}else{
							printf("�߂�");
						}
					}
					fflush(stdout);
					/*�G�̈ꗗ�\�� �����܂�*/
					target_label = select_from_list(battle_menu_arrow,enemy_amount + 1);
					sub_flame_clean(																												//�R�}���h�����t���[���N���[��
							BATTLE_MODE_STATUS_FLAME_SPLIT_X,
							BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,
							BATTLE_MODE_STATUS_FLAME_X + 1,
							HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1
							);
					if(target_label == enemy_amount){
						continue;
					}
					if(!strcmp(front->name,FRONT1_NAME) || !strcmp(front->name,FRONT2_NAME)){
						damage = front->min_atk + rand() % (front->max_atk - front->min_atk - 1) + using_weapon->atk;
					}else{
						damage = front->min_atk + rand() % (front->max_atk - front->min_atk - 1);
					}
					mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					printf("%s �� %3d �_���[�W!��",enemies[target_label]->name,damage);
					change_hp(enemies[target_label],damage);
					if(using_weapon->is_gun && !strcmp(front->name,FRONT2_NAME)){
						damage = front->min_atk + rand() % (front->max_atk - front->min_atk - 1) + using_weapon->atk;
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
						printf("%s �� %3d �_���[�W!��",enemies[target_label]->name,damage);
						change_hp(enemies[target_label],damage);
					}
					print_health_bar(for_bar,enemy_amount_for_bar);
					wait_anyinput();
					if(enemies[target_label]->hp <= 0){
						sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						printf("%s �͓|�ꂽ!��",enemies[target_label]->name);
						for(int i = target_label; i + 1 < enemy_amount;i++){
							enemies[i] = enemies[i + 1];
						}
						enemy_amount--;
						wait_anyinput();
					}
					break;
				case 1:
					mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					if(strstr(front->name,"Robo") == NULL){
						printf("�߂�");
						fflush(stdout);
						target_label = select_from_list(battle_menu_arrow,1);
					}else{
						if(!strcmp(front->name,FRONT3_NAME)){
							printf("�J���h�{���O");
						}else if(!strcmp(front->name,FRONT4_NAME)){
							printf("�t���A");
						}
						mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
						printf("�߂�");
						fflush(stdout);
						target_label = select_from_list(battle_menu_arrow,2);
					}
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					if((strstr(front->name,"Robo") == NULL && target_label == 0) || target_label == 1){
						continue;
					}else if(target_label == 0){
						if(!strcmp(front->name,FRONT3_NAME)){
							if(turn_count < 5){
								print_line("�J���h�{���O��5�^�[���ڂ܂Ŏg���܂��� ",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								wait_anyinput();
								sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								continue;
							}else{
								mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								printf("%s �̓J���h�{���O���g����!��",front->name);
								wait_anyinput();
								mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
								wait_anyinput();
								/*�G�_���[�W������������*/
								for(int i = 0; i < enemy_amount; i++){
									sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
									change_hp(enemies[i],FRONT3_SP_DAMAGE);
									mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
									printf("%s �� %4d �_���[�W!��",enemies[i]->name,FRONT3_SP_DAMAGE);
									print_health_bar(for_bar,enemy_amount_for_bar);
									wait_anyinput();
									/*�G�_���[�W���������܂�*/
									/*�G���S���肱������*/
									if(enemies[i]->hp <= 0){
										sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
										mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
										printf("%s �͓|�ꂽ!��",enemies[target_label]->name);
										for(int i = target_label; i + 1 < enemy_amount;i++){
											enemies[i] = enemies[i + 1];
										}
										enemy_amount--;
										wait_anyinput();
									}
								}
								/*�G���S���肱���܂�*/
							}
						}else if(!strcmp(front->name,FRONT4_NAME)){
							if(turn_count < 3){
								print_line("�t���A��3�^�[���ڂ܂Ŏg���܂��� ",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								wait_anyinput();
								sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								continue;
							}else if(!used_flare){
								mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								printf("%s �̓t���A���g����!��",front->name);
								used_flare = 1;
								wait_anyinput();
								/*�G�_���[�W������������*/
								for(int i = 0; i < enemy_amount; i++){
									sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
									mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
									printf("%s �� %4d �_���[�W!��",enemies[i]->name,enemies[i]->hp / 2);
									change_hp(enemies[i],enemies[i]->hp / 2);
									print_health_bar(for_bar,enemy_amount_for_bar);
									wait_anyinput();
									/*�G�_���[�W���������܂�*/
									/*�G���S���肱������*/
									if(enemies[i]->hp <= 0){
										sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
										mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
										printf("%s �͓|�ꂽ!��",enemies[target_label]->name);
										for(int i = target_label; i + 1 < enemy_amount;i++){
											enemies[i] = enemies[i + 1];
										}
										enemy_amount--;
										wait_anyinput();
									}
								}
								/*�G���S���肱���܂�*/
							}else{
								print_line("�t���A��1�x�����g���܂��� ",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								wait_anyinput();
								sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								continue;
							}
						}
					}
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					break;
				case 2:
					protect_flag = 1;
					mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					printf("%s �͂��΂��̐��ɓ�������",front->name);
					wait_anyinput();
					break;
				case 3:
					for(int i = 0; i <= potion_amount; i++){
						mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1 + i);
						if(i < potion_amount){
							printf("�|�[�V����");
						}else{
							printf("�߂�");
						}
						fflush(stdout);
					}
					target_label = select_from_list(battle_menu_arrow,potion_amount + 1);
					if(target_label < potion_amount){
						sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						change_hp(front,-1 * front->max_hp);
						change_hp(&arist,-1 * arist.max_hp);
						print_bt_status(front,back);
						print_line("�|�[�V�������g����!�� ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						potion_amount--;
						wait_anyinput();
					}else{
						sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						continue;
					}
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					break;
				default:
					break;
			}
			sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			/*�v���C���[�̍s�� ��������*/

			print_health_bar(for_bar,enemy_amount_for_bar);

			//��������
			enemies_dead_check = 0;
			for(int i = 0; i <  enemy_amount_for_bar; i++){
				enemies_dead_check += for_bar[i]->hp;
			}
			if(enemies_dead_check <= 0){
				print_line("�퓬�ɏ�������!��",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				finish_flag = 1;
				wait_anyinput();
				//flame_flush();
				return 1;
				continue;
			}
			//����I���

			//��q�̍s��
			if(strcmp(back->name,"dummy")){
				switch(rand() % 4){
					case 0:
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						printf("%s �͋����Ă���...��",back->name);
						wait_anyinput();
						break;
					case 1:
						if(!strcmp(arist_using_weapon->name,"Bow")){
							print_line("�A���X�g�̃��C���{�[�A���[!��",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
							wait_anyinput();
							damage = (BACK_ATTACK);
							target_label = rand() % enemy_amount;
							change_hp(enemies[target_label],damage);
							mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
							printf("%s �� %3d �_���[�W!�� ",enemies[target_label]->name,damage);
							print_health_bar(for_bar,enemy_amount_for_bar);
							wait_anyinput();
							break;
						}
					default:
						change_hp(front,-1 * arist.max_atk);
						change_hp(back,-1 * arist.max_atk);
						print_bt_status(front,back);
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						printf("%s�̓q�[����������!�� ",back->name);
						wait_anyinput();
						break;
				}
			}
			sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			//��q�̍s���I���
		}else{
			print_line("�����Ȃ�...�� ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			wait_anyinput();
			sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			for(int i = 0; i < enemy_amount; i++){
				if(!strcmp(enemies[i]->name,ST3_BOSS_NAME)){
					player_can_act = 1;
				}else if(!strcmp(enemies[i]->name,ST5_BOSS_NAME)){
					sp_count++;
					if(sp_count >= 3){
						player_can_act = 1;
						sp_count = 0;
					}
				}
			}
		}
		print_health_bar(for_bar,enemy_amount_for_bar);

		//��������
		enemies_dead_check = 0;
		for(int i = 0; i <  enemy_amount_for_bar; i++){
			enemies_dead_check += for_bar[i]->hp;
		}
		if(enemies_dead_check <= 0){
			print_line("�퓬�ɏ�������!��",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			wait_anyinput();
			finish_flag = 1;
			return 1;
			continue;
		}
		//����I���

		//�G�̍s��
		for(int i = 0; i < enemy_amount; i++){
			if(enemies[i]->hp > 0){
				if(!strcmp(enemies[i]->name,ST3_BOSS_NAME) && turn_count == 6){
					print_line("�Ñ�̋@�B���l�̓���U��!�� ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					wait_anyinput();
					print_line("�A���e�B���b�g�o�E���h!�� ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
					wait_anyinput();
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					mvcur(BATTLE_MODE_COMMAND_POS - 2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					printf("���̃^�[���̍s���𕕂���ꂽ...�� ");
					fflush(stdout);
					wait_anyinput();
					player_can_act = !player_can_act;
				}else if(!strcmp(enemies[i]->name,ST4_BOSS_NAME) && rand() % 10 == 5){
					change_hp(enemies[i],-500);
					print_line("Boss �̓P�A������������!�� ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					wait_anyinput();
				}else if(!strcmp(enemies[i]->name,"St5Bs") && turn_count != 0 && turn_count % 4 == 0){
					print_line("Stage5 Boss's action!�� ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					wait_anyinput();
					print_line("The Gaia!�� ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
					wait_anyinput();
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					char *(string)[] = {
						"3�^�[���̊�,",
						"        �s���𕕂���ꂽ...�� "
					};
					print_lines(string,BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,2);
					fflush(stdout);
					wait_anyinput();
					player_can_act = !player_can_act;
				} else if(!strcmp(enemies[i]->name,ST5_BOSS_NAME) && rand() % 10 == 5 && enemies[i]->hp < enemies[i]->max_hp * 0.4){
					char *(string)[] = {
						"Stage5 Boss cast ",
						"              'Tetragrammaton'!�� "
					};
					change_hp(enemies[i],-1500);
					print_lines(string,BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,2);
					wait_anyinput();
				} else {
					damage = enemies[i]->min_atk + rand() % (enemies[i]->max_atk - enemies[i]->min_atk - 1);
					if(protect_flag || !strcmp(back->name,"dummy")){
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						printf("%s �� %3d �̃_���[�W!��",front->name,damage);
						change_hp(front,damage);
					}else{
						switch((int)(rand() % 2)){
							case 0:
								mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								printf("%s �� %3d �̃_���[�W!��",back->name,damage);
								change_hp(back,damage);
								break;
							default:
								mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								printf("%s �� %3d �̃_���[�W!��",front->name,damage);
								change_hp(front,damage);
								break;
						}
					}
					protect_flag = 0;
					wait_anyinput();
				}
			}
			print_health_bar(for_bar,enemy_amount_for_bar);
			print_bt_status(front,back);
			if(front->hp <= 0 || (back->hp <= 0 && strcmp(back->name,"dummy"))){
				sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				print_line("Lose...��",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				finish_flag = 1;
				return 0;
				wait_anyinput();
				continue;
			}
		}
		//�G�̍s���I���
		sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
		turn_count++;
	}
	return 0;
}

void gameover_lose(){

}

void gameover_win(){
	print_lines(gameover,(WIDTH - 27) / 2,(HEIGHT - 3) / 2,3);
}
