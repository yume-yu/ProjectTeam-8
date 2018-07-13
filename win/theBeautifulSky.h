/**
 * @file thebeautifulsky.h
 * @brief �Q�[���thebeautifulsky��̃w�b�_
 * @author yume_yu
 * @date 2018/07/08
 */

//���d�C���N���[�h�h�~
#pragma once

/**
 * �R���p�C������OS�̐錾
 * Windows�n	WINDOWS
 * mac/Linux	MAC
 */
#define WINDOWS

/* �g�p����w�b�_�̃C���N���[�h */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

//OS�Ɉˑ����郉�C�u�����������ɏ���
#if defined WINDOWS

#include <windows.h>						//�J�[�\���ړ�SetConsoleCursorPosition��
#include <conio.h>							//kbhit(),getch()�Ȃ�

#define ENTERKEY 0x0d						//Enter�L�[�̓��͂̓���\�L
#define MULTIBYTE_CHAR_SIZE 2		//�}���`�o�C�g�����̑傫���̓���\�L(�����R�[�h?)

#elif defined MAC

#include "mconio.h"

#define ENTERKEY '�_n'						//Enter�L�[�̓��͂̓���\�L
#define MULTIBYTE_CHAR_SIZE 3		//�}���`�o�C�g�����̑傫���̓���\�L(�����R�[�h?)

#endif


/* �萔�̒�`(define) */

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

/**
 *	@def
 *	�}�b�v��̃��j���[�Ɋւ���萔
 */
#define MAP_WIN_WIDTH		(WIDTH - 2) / 3
#define MAP_WIN_HEIGHT	6
#define MAP_WIN_X				WIDTH - 1 - MAP_WIN_WIDTH
#define MAP_WIN_Y				5

/**
 *	@def
 *	�}�b�v��̃X�e�[�^�X���j���[�Ɋւ���萔
 */
#define STAT_WIN_WIDTH		MAP_WIN_WIDTH  + 10
#define STAT_WIN_HEIGHT		8
#define STAT_WIN_X				MAP_WIN_X - (MAP_WIN_WIDTH + 10)

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
#define ST1_BOSS_NAME			"�ǎ�̑��@��"
#define ST1_BOSS_HP				100
#define ST1_BOSS_MINATK		10
#define ST1_BOSS_MAXATK		20
#define ST2_BOSS_NAME			"�^�N�g"
#define ST2_BOSS_HP				150
#define ST2_BOSS_MINATK		30
#define ST2_BOSS_MAXATK		40
#define ST3_BOSS_NAME			"�f�W�� = �V�j�W�F"
#define ST3_BOSS_HP				250
#define ST3_BOSS_MINATK		50
#define ST3_BOSS_MAXATK		60
#define ST4_BOSS_NAME			"�Ñ�̋@�B���l"
#define ST4_BOSS_HP				1000
#define ST4_BOSS_MINATK		100
#define ST4_BOSS_MAXATK		130
#define ST5_BOSS_NAME			"�t�@�[��"
#define ST5_BOSS_HP				3000
#define ST5_BOSS_MINATK		300
#define ST5_BOSS_MAXATK		400
#define ST2_WEAK_NAME			"���g�����C�o�[��"
#define ST31_WEAK_NAME		"�N���C�W�[�h�b�O"
#define ST32_WEAK_NAME		"�}�b�h�h�b�O"
#define ST41_WEAK_NAME		"�H������������ A"
#define ST42_WEAK_NAME		"�H������������ B"


/* �\���̂̐錾 */

// arrow_pos	���W���Ǘ����邽�߂̍\���́B���X�g�\����}�b�v��ŁA�z��ɂ��Ďg��
typedef struct {
	int x;							//x���W
	int y;							//y���W
	bool not_active;		//�ړ��\�ȍ��W���ǂ���
	bool at_event;			//�C�x���g���L��}�X���ǂ���
} arrow_pos;

// character	�L�����N�^�[�̊�{�X�e�[�^�X�\����
typedef struct {
	char *name;					//���O
	int hp;							//���݂̗̑�
	int max_hp;					//�̗͂̍ő�l
	int max_atk;				//�^�_���[�W�̏��
	int min_atk;				//�^�_���[�W�̉���
} character;

// weapon ����̊�{�X�e�[�^�X�\����
typedef struct {
	char *name;					//���O
	int atk;						//�^�_���[�W������
	bool is_gun;				//�e�ł��邩�ǂ���
} weapon;

// protector �h��̊�{�X�e�[�^�X�\����
typedef struct {
	char *name;					//���O
	int def;						//�h��͂̑�����
} protector;

// extendstr �X�g�[���[���\��������̍\����
typedef struct {
	char string[100];		//�\�����镶����
	int offset;					//�\���ʒu�̉E���炵�I�t�Z�b�g
	int not_need_return;//���͂�҂s�ł��邩�̃t���O
} extendstr;

// input_assort ���͂������\����
typedef struct {
	bool kbhit_flag;		//�L�[��������Ă��邩��Ԃ��t���O
	int input_char;			//���͂��ꂽ�L�[
} input_assort;

// stage �}�b�v��\����
typedef enum {
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
} stage;

// event �}�b�v�ŋN����C�x���g��\����
typedef enum {
	battle_event, //�퓬�C�x���g
	talk_event,		//��b�C�x���g
	move_map,			//�}�b�v�Ԃ̈ړ�
	open_menu			//���j���[���J��
} event;

/* �萔�̒�`(const) */


/* �O���[�o���֐��錾 */

//�K�v�L�����N�^-�̒�`
extern character naoki;
extern character lirel;
extern character arist;
extern character robo;
extern character boss1;
extern character boss2;
extern character dummy;
extern character *front;
extern character *back;
extern character *(enemies)[3];

//�퓬���̓G�̐�
extern int enemy_amount;

//�����Ƒ����g
extern weapon all_weapons[7];							//�S�O�q����̐錾
extern weapon all_weapons4back[7];				//�S��q����̐錾
extern protector all_protectors[7];				//�S�h��̐錾
extern weapon *using_weapon;							//�O�q�̕���
extern protector *using_protector;				//�O�q�̖h��
extern weapon *arist_using_weapon;				//��q�̕���
extern protector *arist_using_protector;	//��q�̖h��
extern int potion_amount;									//�������Ă���|�[�V�����̐�
extern int have_nasu;											//�������Ă���i�X�̐�

//�X�e�[�W�Ǘ�/�}�b�v�Ǘ�
extern char *(maps)[9][HEIGHT - 2];												//�S�X�e�[�W�̃}�b�v�}
extern arrow_pos *(map_coors)[10][WIDTH - 2][HEIGHT - 2];	//�S�X�e�[�W�̃}�b�v���W
extern stage now_stage;																		//���݂̃X�e�[�W
extern char *(now_map)[WIDTH - 2];												//���݂̃}�b�v�}
extern arrow_pos *(now_map_coor)[WIDTH - 2][HEIGHT - 2];	//���݂̃}�b�v���W
extern int room_id;																				//�N������������id
extern arrow_pos start_pos;																//�}�b�v�`�掞�̃L�����N�^�[�̏����ʒu
extern extendstr *now_text[HEIGHT];												//�A�j���[�V�����ŕ\�����镶����

/* ��������map_stX.c�Œ�`����ϐ� */

//�}�b�v�ϐ�
extern char *(map_st1)[WIDTH - 2];
extern char *(map_st2)[WIDTH - 2];
extern char *(map_st3_1)[WIDTH - 2];
extern char *(map_st3_2)[WIDTH - 2];
extern char *(map_st3_3)[WIDTH - 2];
extern char *(map_st4_1)[WIDTH - 2];
extern char *(map_st4_2)[WIDTH - 2];
extern char *(map_st4_3)[WIDTH - 2];
extern char *(map_exp)[WIDTH - 2];

//�}�b�v���W�ϐ�
extern arrow_pos st1_pos[WIDTH - 2][HEIGHT - 2] ;
extern arrow_pos st2_pos[WIDTH - 2][HEIGHT - 2] ;
extern arrow_pos st3_1_pos[WIDTH - 2][HEIGHT - 2];
extern arrow_pos st3_2_pos[WIDTH - 2][HEIGHT - 2];
extern arrow_pos st3_3_pos[WIDTH - 2][HEIGHT - 2];
extern arrow_pos st4_1_pos[WIDTH - 2][HEIGHT - 2];
extern arrow_pos st4_2_pos[WIDTH - 2][HEIGHT - 2];
extern arrow_pos st4_3_pos[WIDTH - 2][HEIGHT - 2];
extern arrow_pos exp_pos[WIDTH - 2][HEIGHT - 2] ;

/* �����܂�map_stX.c�Œ�`����ϐ� */

/* ��������storytext.c�Œ�`����*/
extern extendstr subtitle1[];
extern extendstr subtitle2[];
extern extendstr subtitle3[];
extern extendstr subtitle4[];
extern extendstr subtitle5[];
extern extendstr cenario_stage1[];
extern extendstr lirel_said[];
extern extendstr lirel_stop[];
extern extendstr beforebattle_stage1[];
extern extendstr afterbattle_stage1[];
extern extendstr cenario_stage2[];
extern extendstr talk_st2_0_1[];
extern extendstr talk_st2_0_2[];
extern extendstr beforebattle_stage2[];
extern extendstr afterbattle_stage2[];
extern extendstr cenario_stage3[];
extern extendstr talk_st3_0[];
extern extendstr talk_st3_1[];
extern extendstr talk_st3_1_1[];
extern extendstr talk_st3_1_3[];
extern extendstr talk_st3_1_2[];
extern extendstr talk_st3_2[];
extern extendstr talk_st3_2_1[];
extern extendstr talk_st3_2_2[];
extern extendstr talk_st3_2_3[];
extern extendstr talk_st3_3[];
extern extendstr talk_st3_3_0[];
extern extendstr talk_st3_3_1[];
extern extendstr talk_st3_3_2[];
extern extendstr talk_st3_3_3[];
extern extendstr talk_st3_5_1[];
extern extendstr talk_st3_5_2[];
extern extendstr talk_st3_5_3[];
extern extendstr talk_st3_6[];
extern extendstr beforebattle_stage3[];
extern extendstr afterbattle_stage3[];
extern extendstr cenario_stage4[];
extern extendstr talk_st4_0[];
extern extendstr talk_st4_0_1[];
extern extendstr talk_st4_0_2[];
extern extendstr talk_st4_0_3[];
extern extendstr talk_st4_1[];
extern extendstr talk_st4_1_1[];
extern extendstr talk_st4_1_2[];
extern extendstr talk_st4_1_3[];
extern extendstr talk_st4_3[];
extern extendstr talk_st4_5[];
extern extendstr talk_st4_6[];
extern extendstr beforebattle_stage4[];
extern extendstr afterbattle_stage4_1[];
extern extendstr afterbattle_stage4_2[];
extern extendstr afterbattle_stage4_3[];
extern extendstr cenario_stage5[];
extern extendstr afterbattle_stage5[];
/* �����܂�storytext.c�Œ�`����*/

/* �֐��}�N����` */
//char�z���extendstr�z��̕�����/�s����Ԃ��}�N��
#define lengthof(var,type) (sizeof(var)/sizeof(type))

/* �v���g�^�C�v�錾 */

/* ��������util_func.c�Œ�`����֐� */
#ifdef WINDOWS									//Windows�̂Ƃ������K�v�ȋL�q������if�̒��ɓ����
void usleep(int time);					//usleep�̕\�L����̂���
#endif

void mvcur(int x, int y);																												//�J�[�\���ړ����s���֐�
input_assort mykbhit();																													//�L�[���͂����֐�
void wait_anyinput();																														//�Ȃɂ��L�[���͂�҂֐�
void wait_input_without_arrow();																								//AWSD�ȊO�̃L�[���͂�҂֐�
void init_term();																																//�^�[�~�i���̏��������s���֐�
void print_line(char string[], int x, int y);																		//�w�肵�����W���s���ɂ�1�s�o�͂���֐�
void print_lines(char *string[], int x, int y, int num_lines);									//�w�肵�����W���s���ɕ����s�o�͂���֐�
void string_march(extendstr *(tmp)[],int x,int y,int lines);										//�w�肵�����W���s���ɕ����s�A�j���[�V�����o�͂���֐�
void exstrcpy(extendstr *(to)[],extendstr from[],int lines);										//�A�j���[�V�����\���p�\���̔z����A�h���X�̔z��ɕϊ�����֐�
int select_from_list(arrow_pos tmp_pos[10], int length);												//�c�����̃��X�g����I��������֐�
int select_from_hlist(arrow_pos tmp_pos[10], int length);												//�������̃��X�g����I��������֐�
int select_from_2dlist(int width, int height,arrow_pos tmp_pos[width][height]);	//���ʃ��X�g����I��������֐�
/* �����܂�util_func.c�Œ�`����֐� */

/* ��������flame_func.c�Œ�`����֐� */
void make_flame(int width, int height, int offset_x, int offset_y);								//�w��ʒu������ɍ����ƕ����w�肵���t���[�����쐬����֐�
void make_vsflame(int width, int height, int offset_x, int offset_y, int split_x);//�w��ʒu������ɍ����ƕ��ƕ����ʒu���w�肵����2�����̃t���[�����쐬����֐�
void flame_flush();																																//���C���t���[�������A�j���[�V�����t���ŃX�y�[�X���߂���֐�
void flame_clean();																																//���C���t���[�������A�j���[�V�����Ȃ��ŃX�y�[�X���߂���֐�
void sub_flame_clean(int width, int height, int x, int y);												//�w��͈͓����A�j���[�V�����Ȃ��ŃX�y�[�X���߂���֐�
int check_window(int width, int height, int x, int y, char *string);							//�m�F����y/n�̊m�F�t���[�����o���֐�
/* �����܂�flame_func.c�Œ�`����֐� */

/* ��������weapons_items.c�Œ�`����֐� */
void set_weapon_stat(weapon *tmpwp, int atk, bool is_gun);												//����̃X�e�[�^�X���X�V����֐�
void set_protector_stat(protector *tmppr, int def);																//�h��̃X�e�[�^�X���X�V����֐�
bool get_potion();																																//�|�[�V��������肵���Ƃ��̊֐�
/* �����܂�weapons_items.c�Œ�`����֐� */

/* ��������character.c�Œ�`����֐� */
void set_ch_stat(char name[10], character *tmpch, int hp, int max_hp,int min_atk, int max_atk);	//�L�����N�^�[�̃X�e�[�^�X���X�V����֐�
void change_hp(character *tmpch, int damage);																										//�L�����N�^�[�̃_���[�W/�񕜏������s���֐�
/* �����܂�character.c�Œ�`����֐� */

/* ��������map_func.c�Œ�`����֐� */
void mapcpy(char *(to)[HEIGHT - 2],char *(from)[HEIGHT - 2]);																								//�}�b�v��ʊ֐��ɃR�s�[����֐�
void coor_cnv_adr(arrow_pos *(to)[WIDTH - 2][HEIGHT - 2],arrow_pos from[WIDTH - 2][HEIGHT - 2]);						//�}�b�v���W���A�h���X�z��ɂ��ăR�s�[����֐�
void coorcpy(arrow_pos *(to)[WIDTH - 2][HEIGHT - 2],arrow_pos *(from)[WIDTH - 2][HEIGHT - 2]);							//�}�b�v���W�̃A�h���X�z����R�s�[����֐�
arrow_pos move_on_map(int width, int height,arrow_pos *(tmp_pos)[WIDTH -2 ][HEIGHT - 2], arrow_pos offset);	//�}�b�v����ړ�����֐�
/* �����܂�map_func.c�Œ�`����֐� */

/* ��������map_menu.c�Œ�`����֐� */
void view_status();																																//�}�b�v���j���[�ŃX�e�[�^�X��\������֐�
void item_list_on_map();																													//�}�b�v���j���[�ŃA�C�e���ꗗ��\������֐�
int onmap_manu();																																	//�}�b�v���j���[���J���֐�
void update_map(stage now_stage);																									//�\������}�b�v���X�e�[�W�ɍ��킹�čX�V����֐�
/* �����܂�map_menu.c�Œ�`����֐� */

/* ��������decide_event.c�Œ�`����֐� */
event decide_event(arrow_pos exit_point);
/* �����܂�decide_event.c�Œ�`����֐� */

/* ��������talk_event.c�Œ�`����֐� */
void lirel_find_potion();
void naoki_find_potion();
bool instory_yesno(int y);
void guide_st1();
void noentry_st1();
void talk_event_st1_1();
void talk_event_st1_0();
void before_battle_st1();
void after_battle_st1();
void talk_event_st2_0();
void talk_event_st2_1();
void before_battle_st2();
void after_battle_st2();
void talk_event_st3_0();
void talk_event_st3_1();
void talk_event_st3_2();
void talk_event_st3_3();
void talk_event_st3_5();
void talk_event_st3_6();
void before_battle_st3();
void after_battle_st3();
void talk_event_st4_0();
void talk_event_st4_1();
void talk_event_st4_2();
void talk_event_st4_3();
void talk_event_st4_5();
void talk_event_st4_6();
void before_battle_st4();
void after_battle_st4();
void after_battle_st5();
/* �����܂�talk_event.c�Œ�`����֐� */


