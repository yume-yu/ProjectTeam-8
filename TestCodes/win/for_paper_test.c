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
#include "for_make_game.h"

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
#define BATTLE_MODE_STATUS_FLAME_SPLIT_X 	2*(WIDTH-2)/3-1
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

#define ARIST_ATTACK		35
//�^�C�g����ʂ̐��̐�
#define STAR_AMOUNT 		50

//�L�����N�^�[�X�e�[�^�X�ݒ�萔
#define FRONT1_NAME				"Lirel"
#define FRONT1_HP					110
#define FRONT1_MINATK			15
#define FRONT1_MAXATK			20
#define FRONT2_NAME				"Naoki"
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
#define BACK_NAME					"Arist"
#define BACK_HP_ST1				70
#define BACK_HEAL_ST1 		20
#define BACK_HP_ST2				90
#define BACK_HEAL_ST2 		30
#define BACK_HP_ST3				110
#define BACK_HEAL_ST3 		40
#define BACK_HP_ST4				130
#define BACK_HEAL_ST4 		50
#define ST1_BOSS_NAME			"St1Bs"
#define ST1_BOSS_HP				100
#define ST1_BOSS_MINATK		10
#define ST1_BOSS_MAXATK		20
#define ST2_BOSS_NAME			"St2Bs"	
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

//�K�v�L�����N�^�̒�`
struct character naoki;
struct character lirel;
struct character arist;
struct character robo;
struct character boss1;
struct character boss2;
struct character dummy;

//�����g�̐錾
struct weapon *using_weapon;
struct protector *using_protector;
struct weapon *arist_using_weapon;
struct protector *arist_using_protector;
int potion_amount = 0;

//�e�L�����N�^�[�̃X�e�[�^�X������
void initchara(){
	set_ch_stat("naoki",&naoki,90,20,35);
	set_ch_stat("lirel",&lirel,120,15,20);
	set_ch_stat("arist",&arist,70,0,20);
	set_ch_stat("Robo1",&robo,2000,140,150);
	set_ch_stat("boss1",&boss1,100,10,20);
	set_ch_stat("boss2",&boss2,100,10,20);
	set_ch_stat("dummy",&dummy,0,0,0);
	//������f��ɏ�����
	using_weapon = &all_weapons[0];
	using_protector = &all_protectors[0];
	arist_using_weapon = &all_weapons4back[0];
	arist_using_protector = &all_protectors[0];
}

//�e�L�����N�^�[�̃X�e�[�^�X�ݒ��\��
void show_ch_stat(int x,int y){
	make_flame(34,8,x,y);
	print_line("Now status list",x+5,y+1);
	mvcur(x+2,y+2);
	printf("naoki - HP:%4d  ATK:%3d �`%3d",naoki.max_hp,naoki.min_atk,naoki.max_atk);
	mvcur(x+2,y+3);
	printf("arist - HP:%4d  HEAL:%d",arist.max_hp,arist.max_atk);
	mvcur(x+2,y+4);
	printf("lirel - HP:%4d  ATK:%3d �`%3d",lirel.max_hp,lirel.min_atk,lirel.max_atk);
	mvcur(x+2,y+5);
	printf("boss1 - HP:%4d  ATK:%3d �`%3d",boss1.max_hp,boss1.min_atk,boss1.max_atk);
	mvcur(x+2,y+6);
	printf("boss2 - HP:%4d  ATK:%3d �`%3d",boss2.max_hp,boss2.min_atk,boss2.max_atk);
	mvcur(0,HEIGHT + 1);
	fflush(stdout);
}

int sel_mode_window(int y){
	return 0;
}

int main_window_init(){
	flame_clean();
	//���[�h�I���t���[���̃J�[�]�����W�ϐ�
	struct arrow_pos main_menu_arrow[] = {
		//{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+1}
		{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+ 2},
		{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+ 3},
		{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+ 4},
		//{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+ 5},
		//{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+ 6},
		{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+ 7},
		{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+ 8},
		//{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+ 9},
		{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+10}
		//{6,SELECT_MODE_FLAME_HEIGHT_OFFSET+11}
	};
	//���[�h�I���t���[���̕\��
	//sel_mode_window(SELECT_MODE_FLAME_HEIGHT_OFFSET);
	make_flame(WIDTH / 2 + 1,HEIGHT / 2 ,3,SELECT_MODE_FLAME_HEIGHT_OFFSET);
	char menu_items[][100] = {
		"For PaperTest",
		"   battle",
		"   change equipment",
		"   edit item",
		" ",
		"For Coordinate/Debug",
		"   edit character status",
		"   test battle",
		" ",
		"   exit"
	};
	print_lines(menu_items,6,SELECT_MODE_FLAME_HEIGHT_OFFSET+1,10);
	/*�O�q�����\��*/
	make_flame(SELECT_MODE_EQIP_FLAME_WIDTH,SELECT_MODE_EQIP_FLAME_HEIGHT,SELECT_MODE_EQIP_FLAME_X,SELECT_MODE_EQIP_FLAME_Y);
	print_line("Front",SELECT_MODE_EQIP_FLAME_X + 2,SELECT_MODE_EQIP_FLAME_Y);
	print_line("Weapon",SELECT_MODE_EQIP_FLAME_X + 2,SELECT_MODE_EQIP_FLAME_Y + 1);
	mvcur(WIDTH - 3 - strlen(using_weapon->name),SELECT_MODE_EQIP_FLAME_Y + 2);
	printf("%s",using_weapon->name);
	print_line("Protector",SELECT_MODE_EQIP_FLAME_X + 2,SELECT_MODE_EQIP_FLAME_Y + 3);
	mvcur(WIDTH - 3 - strlen(using_protector->name),SELECT_MODE_EQIP_FLAME_Y + 4);
	printf("%s",using_protector->name);
	/*��q�����\��*/
	make_flame(SELECT_MODE_EQIP_FLAME_WIDTH,SELECT_MODE_EQIP_FLAME_HEIGHT,SELECT_MODE_EQIP_FLAME_X,SELECT_MODE_EQIP_FLAME_Y + SELECT_MODE_EQIP_FLAME_HEIGHT);
	print_line("Back",SELECT_MODE_EQIP_FLAME_X + 2,SELECT_MODE_EQIP_FLAME_Y + SELECT_MODE_EQIP_FLAME_HEIGHT);
	print_line("Weapon",SELECT_MODE_EQIP_FLAME_X + 2,SELECT_MODE_EQIP_FLAME_Y + SELECT_MODE_EQIP_FLAME_HEIGHT + 1);
	mvcur(WIDTH - 3 - strlen(arist_using_weapon->name),SELECT_MODE_EQIP_FLAME_Y + SELECT_MODE_EQIP_FLAME_HEIGHT + 2);
	printf("%s",arist_using_weapon->name);
	print_line("Protector",SELECT_MODE_EQIP_FLAME_X + 2,SELECT_MODE_EQIP_FLAME_Y + SELECT_MODE_EQIP_FLAME_HEIGHT + 3);
	mvcur(WIDTH - 3 - strlen(arist_using_protector->name),SELECT_MODE_EQIP_FLAME_Y + SELECT_MODE_EQIP_FLAME_HEIGHT + 4);
	printf("%s",arist_using_protector->name);
	/*�|�[�V�����������\��*/
	make_flame(SELECT_MODE_EQIP_FLAME_WIDTH,SELECT_MODE_POTION_FLAME_HEIGHT,SELECT_MODE_EQIP_FLAME_X,SELECT_MODE_EQIP_FLAME_Y + 2 * SELECT_MODE_EQIP_FLAME_HEIGHT);
	print_line("Potion amount",SELECT_MODE_EQIP_FLAME_X + 2,SELECT_MODE_EQIP_FLAME_Y + 2 * SELECT_MODE_EQIP_FLAME_HEIGHT);
	mvcur(SELECT_MODE_EQIP_CHARASET_X - 1,SELECT_MODE_EQIP_FLAME_Y + 2 * SELECT_MODE_EQIP_FLAME_HEIGHT + 1);
	printf("%d",potion_amount);
	char control_explain[][100] = {
		"  w            ��   ",
		"a s d   as  �� �� ��"	
	};
	print_lines(control_explain,WIDTH - 20,HEIGHT - 2,2);
	print_line("The Beautiful Sky",4,HEIGHT - 1);
	fflush(stdout);
	//���[�h�I��
	return select_from_list(main_menu_arrow,6);
}

//�퓬���[�h�̎��ɃR�}���h�����\������֐�
void print_bt_commands(){
	print_line("Attack",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
	print_line("Special",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
	print_line("Protect",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3);
	print_line("Item",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 4);
	fflush(stdout);
}

void print_bt_status(struct character *front,struct character *back){
	//�X�e�[�^�X�����\��
	char spaces[][100] = {
		{"               "},
		{"               "}
	};
	print_lines(spaces,BATTLE_MODE_STATUS_HP_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,2);
	print_line("HP",BATTLE_MODE_STATUS_HP_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
	mvcur(BATTLE_MODE_STATUS_HP_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
	printf("%s:%4d/%4d",front->name,front->hp,front->max_hp);
	if(strcmp(back->name,"dummy")){
		mvcur(BATTLE_MODE_STATUS_HP_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3);
		printf("%s:%4d/%4d",back->name,back->hp,back->max_hp);
	}
	mvcur(0,HEIGHT + 1);
	fflush(stdout);
}

int select_stage(){
	make_flame(SELECT_STAGE_FLAME_WIDTH,SELECT_STAGE_FLAME_HEIGHT,SELECT_STAGE_FLAME_X,SELECT_STAGE_FLAME_Y);
	char stage_list[][100] = {
		"Select Battle",
		"  Stage1 vs Boss",
		"  Stage2 vs Boss",
		"  Stage3 vs WeakEnemy",
		"  Stage3 vs Boss",
		"  Stage4 vs WeakEnemy",
		"  Stage4 vs Boss",
		"  Stage5 vs Boss"
	};
	struct arrow_pos stage_select_arrow[] = {
		{SELECT_STAGE_FLAME_X + 2,SELECT_STAGE_FLAME_Y + 2},
		{SELECT_STAGE_FLAME_X + 2,SELECT_STAGE_FLAME_Y + 3},
		{SELECT_STAGE_FLAME_X + 2,SELECT_STAGE_FLAME_Y + 4},
		{SELECT_STAGE_FLAME_X + 2,SELECT_STAGE_FLAME_Y + 5},
		{SELECT_STAGE_FLAME_X + 2,SELECT_STAGE_FLAME_Y + 6},
		{SELECT_STAGE_FLAME_X + 2,SELECT_STAGE_FLAME_Y + 7},
		{SELECT_STAGE_FLAME_X + 2,SELECT_STAGE_FLAME_Y + 8},
		{SELECT_STAGE_FLAME_X + 2,SELECT_STAGE_FLAME_Y + 9}
	};
	print_lines(stage_list,SELECT_STAGE_FLAME_X + 2,SELECT_STAGE_FLAME_Y + 1,8);
	print_line("back",SELECT_STAGE_FLAME_X + 4,SELECT_STAGE_FLAME_Y + 9);
	return select_from_list(stage_select_arrow,sizeof(stage_select_arrow)/sizeof(struct arrow_pos));
}

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

//�퓬���[�h
void battle(struct character *front,struct character *back,struct character *enemies[3], int enemy_amount){
	int finish_flag = 0;
	int protect_flag = 0;
	int damage = 0;
	int target_label = 0;
	int turn_count = 1;
	int sp_count = 0;
	int enemies_dead_flag[enemy_amount];
	int enemies_dead_check = 0;
	int player_can_act = 1;
	int used_flare = 0;
	int enemy_amount_for_bar = enemy_amount;
	struct character *for_bar[enemy_amount];
	for(int i = 0;i < enemy_amount;i++){
		for_bar[i] = enemies[i];
	}
	struct arrow_pos battle_menu_arrow[] = {{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1},{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2},{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3},{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 4}};

	//�G��HP�Ɛ����t���O��������
	for(int i = 0; i < enemy_amount; i++){
		change_hp(enemies[i],-1 * enemies[i]->max_hp);
		enemies_dead_flag[i] = 1;
	}
	flame_flush();
	make_vsflame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_SPLIT_X);

	print_bt_status(front,back);
	print_health_bar(for_bar,enemy_amount_for_bar);

	while(!finish_flag){
		if(player_can_act){
			print_bt_commands();
			int command = select_from_list(battle_menu_arrow,4);
			//�R�}���h�����t���[���N���[��
			sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			switch(command){
				case 0:
					for(int i = 0; i <= enemy_amount; i++){
						mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1 + i);
						if(i < enemy_amount){
							printf("%s",enemies[i]->name);
						}else{
							printf("back");
						}
					}
					fflush(stdout);
					target_label = select_from_list(battle_menu_arrow,enemy_amount + 1);
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					if(target_label == enemy_amount){
						continue;
					}
					if(!strcmp(front->name,"Naoki") || !strcmp(front->name,"Lirel")){
						damage = front->min_atk + rand() % (front->max_atk - front->min_atk - 1) + using_weapon->atk;
					}else{
						damage = front->min_atk + rand() % (front->max_atk - front->min_atk - 1);
					}
					mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					printf("%s got %3d damaged!��",enemies[target_label]->name,damage);
					change_hp(enemies[target_label],damage);
					if(using_weapon->is_gun && !strcmp(front->name,"Naoki")){
						damage = front->min_atk + rand() % (front->max_atk - front->min_atk - 1) + using_weapon->atk;
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
						printf("%s got %3d damaged!��",enemies[target_label]->name,damage);
						change_hp(enemies[target_label],damage);
					}
					print_health_bar(for_bar,enemy_amount_for_bar);
					wait_anyinput();
					if(enemies[target_label]->hp <= 0){
						sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						printf("%s was down!��",enemies[target_label]->name);
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
						printf("back");
						fflush(stdout);
						target_label = select_from_list(battle_menu_arrow,1);
					}else{
						if(!strcmp(front->name,FRONT3_NAME)){
							printf("Caladbolg");
						}else if(!strcmp(front->name,FRONT4_NAME)){
							printf("Flare");
						}
						mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);	
						printf("back");
						fflush(stdout);
						target_label = select_from_list(battle_menu_arrow,2);
					}
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					if((strstr(front->name,"Robo") == NULL && target_label == 0) || target_label == 1){
						continue;
					}else if(target_label == 0){
						if(!strcmp(front->name,FRONT3_NAME)){
							if(turn_count < 5){
								print_line("Caladbolg can use since turn 5�� ",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								wait_anyinput();
								sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								continue;
							}else{
								mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								printf("%s use Caladbolg!��",front->name);
								wait_anyinput();
								mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
								wait_anyinput();
								/*�G�_���[�W������������*/
								for(int i = 0; i < enemy_amount; i++){
									sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
									change_hp(enemies[i],FRONT3_SP_DAMAGE);
									mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
									printf("%s got %4d damaged!��",enemies[i]->name,FRONT3_SP_DAMAGE);
									print_health_bar(for_bar,enemy_amount_for_bar);
									wait_anyinput();
									/*�G�_���[�W���������܂�*/
									/*�G���S���肱������*/
									if(enemies[i]->hp <= 0){
										sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
										mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
										printf("%s was down!��",enemies[target_label]->name);
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
								print_line("Flare can use since turn 3�� ",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								wait_anyinput();
								sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								continue;
							}else if(!used_flare){
								mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								printf("%s use Flare!��",front->name);
								used_flare = 1;
								wait_anyinput();
								/*�G�_���[�W������������*/
								for(int i = 0; i < enemy_amount; i++){
									sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
									mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
									printf("%s got %4d damaged!��",enemies[i]->name,enemies[i]->hp / 2);
									change_hp(enemies[i],enemies[i]->hp / 2);
									print_health_bar(for_bar,enemy_amount_for_bar);
									wait_anyinput();
									/*�G�_���[�W���������܂�*/
									/*�G���S���肱������*/
									if(enemies[i]->hp <= 0){
										sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
										mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
										printf("%s was down!��",enemies[target_label]->name);
										for(int i = target_label; i + 1 < enemy_amount;i++){
											enemies[i] = enemies[i + 1];
										}
										enemy_amount--;
										wait_anyinput();
									}
								}
								/*�G���S���肱���܂�*/
							}else{
								print_line("Flare can use only once�� ",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
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
					printf("%s is ready to protect!��",front->name);
					wait_anyinput();
					break;
				case 3:
					for(int i = 0; i <= potion_amount; i++){
						mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1 + i);
						if(i < potion_amount){
							printf("potion");
						}else{
							printf("back");
						}
						fflush(stdout);
					}
					target_label = select_from_list(battle_menu_arrow,potion_amount + 1);
					if(target_label < potion_amount){
						sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						change_hp(front,-1 * front->max_hp);
						change_hp(&arist,-1 * arist.max_hp);
						print_bt_status(front,back);
						print_line("use potion!�� ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
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
			//�v���C���[�̍s���I���
			print_health_bar(for_bar,enemy_amount_for_bar);

			//��������
			enemies_dead_check = 0;
			for(int i = 0; i <  enemy_amount_for_bar; i++){
				enemies_dead_check += for_bar[i]->hp;
			}
			if(enemies_dead_check <= 0){
				print_line("Win!��",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				finish_flag = 1;
				wait_anyinput();
				continue;
			}
			//����I���

			//��q�̍s��
			if(strcmp(back->name,"dummy")){
				switch(rand() % 4){
					case 0:
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						printf("%s was terrified...��",back->name);
						wait_anyinput();
						break;
					case 1:
						if(!strcmp(arist_using_weapon->name,"Bow")){
							print_line("Arist's Rainbow Arrow!��",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
							wait_anyinput();
							damage = (ARIST_ATTACK);
							target_label = rand() % enemy_amount;
							change_hp(enemies[target_label],damage);
							mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
							printf("%s got %3d damaged!�� ",enemies[target_label]->name,damage);
							print_health_bar(for_bar,enemy_amount_for_bar);
							wait_anyinput();
							break;
						}
					default:
						change_hp(front,-1 * arist.max_atk);
						change_hp(back,-1 * arist.max_atk);
						print_bt_status(front,back);
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						printf("Arist cast 'heal'!�� ");
						wait_anyinput();
						break;
				}
			}
			sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			//��q�̍s���I���
		}else{
			print_line("Can't Action...�� ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			wait_anyinput();
			sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			for(int i = 0; i < enemy_amount; i++){
				if(!strcmp(enemies[i]->name,"St3Bs")){
					player_can_act = 1;
				}else if(!strcmp(enemies[i]->name,"St5Bs")){
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
		for(int i = 0; i <  enemy_amount; i++){
			enemies_dead_check += enemies_dead_flag[i];
		}
		if(enemies_dead_check <= 0){
			print_line("Win!��",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
			finish_flag = 1;
			wait_anyinput();
			continue;
		}
		//����I���

		//�G�̍s��
		for(int i = 0; i < enemy_amount; i++){
			if(enemies[i]->hp > 0){
				if(!strcmp(enemies[i]->name,"St3Bs") && turn_count == 6){
					print_line("Ancient Gear Golem's action!�� ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);		
					wait_anyinput();
					print_line("Ultimate bound!�� ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);		
					wait_anyinput();
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					mvcur(BATTLE_MODE_COMMAND_POS - 2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);		
					printf("Next turn,Players can't action...�� ");	
					fflush(stdout);
					wait_anyinput();
					player_can_act = !player_can_act;
				}else if(!strcmp(enemies[i]->name,"St4Bs") && rand() % 10 == 5){
					change_hp(enemies[i],-500);
					print_line("Stage4 Boss cast 'Curala'!�� ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);		
					wait_anyinput();
				}else if(!strcmp(enemies[i]->name,"St5Bs") && turn_count != 0 && turn_count % 4 == 0){
					print_line("Stage5 Boss's action!�� ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);		
					wait_anyinput();
					print_line("The Gaia!�� ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
					wait_anyinput();
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					char string[][100] = {
						"in 3 turn,",
						"        Players can't action...�� "
					};
					print_lines(string,BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,2);
					fflush(stdout);
					wait_anyinput();
					player_can_act = !player_can_act;
				} else if(!strcmp(enemies[i]->name,"St5Bs") && rand() % 10 == 5){
					char string[][100] = {
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
						printf("%s get %3d damaged by %s!��",front->name,damage,enemies[i]->name);
						change_hp(front,damage);
					}else{
						switch((int)(rand() % 2)){
							case 0:
								mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								printf("%s get %3d damaged by %s!��",back->name,damage,enemies[i]->name);
								change_hp(back,damage);
								break;
							default:
								mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								printf("%s get %3d damaged by %s!��",front->name,damage,enemies[i]->name);
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
				wait_anyinput();
				continue;
			}
		}
		//�G�̍s���I���
		sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
		turn_count++;
	}
}

void set_stat_from_template_mamber(struct character *now_edit,int target){
	struct arrow_pos arrow[] = {
		{EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 1},
		{EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 2},
		{EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 3},
		{EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 4},
		{EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 5}
	};
	print_line("Stage",EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y);
	print_line("Stage1",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 1);
	print_line("Stage2",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 2);
	print_line("Stage3",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 3);
	print_line("Stage4",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 4);
	print_line("Stage5",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 5);
	int selected = select_from_list(arrow,5);
	switch(selected){
		case 0:
		case 1:
		case 2:
			switch(target){
				case 0:
					set_ch_stat("naoki",&naoki,90 + (CHARACTER_STATUS_HP_DIFF * selected),20 + (CHARACTER_STATUS_ATK_DIFF * selected),35 + (CHARACTER_STATUS_ATK_DIFF * selected));
					break;
				case 1:
					set_ch_stat("arist",&arist,70 + (CHARACTER_STATUS_HP_DIFF * selected),0,20 + (CHARACTER_STATUS_ATK_DIFF * selected));
					break;
				case 2:
					set_ch_stat("lirel",&lirel,120 + (CHARACTER_STATUS_HP_DIFF * selected),15 + (CHARACTER_STATUS_ATK_DIFF * selected),20 + (CHARACTER_STATUS_ATK_DIFF * selected));
					break;
			}
			break;
		case 3:
			switch(target){
				case 0:
				case 1:
				case 2:
					break;
			}
			break;
		case 4:
			switch(target){
				case 0:
				case 1:
				case 2:
					break;
			}
			break;
	}
}

//�G�X�e�[�^�X�e���v���[�g�I��
void set_stat_from_template_enemy(struct character *now_edit){
	int target = 0;
	struct arrow_pos arrow[] = {
		{EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 1},
		{EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 2},
		{EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 3},
		{EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 4},
		{EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 5},
		{EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 8}
	};
	print_line("Boss",EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y);
	print_line("St1Boss",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 1);
	print_line("St2Boss",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 2);
	print_line("St3Boss",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 3);
	print_line("St4Boss",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 4);
	print_line("St5Boss",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 5);
	print_line("NotBoss",EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 7);
	print_line("default",EDIT_MODE_EDIT_FLAME_CHAR_X + 3,EDIT_MODE_EDIT_FLAME_CHAR_Y + 8);
	target = select_from_list(arrow,6);
	switch(target){
		case 0:
			set_ch_stat(ST1_BOSS_NAME,now_edit,ST1_BOSS_HP,ST1_BOSS_MINATK,ST1_BOSS_MAXATK);
			break;
		case 1:
			set_ch_stat(ST2_BOSS_NAME,now_edit,ST2_BOSS_HP,ST2_BOSS_MINATK,ST2_BOSS_MAXATK);
			break;
		case 2:
			set_ch_stat(ST3_BOSS_NAME,now_edit,ST3_BOSS_HP,ST3_BOSS_MINATK,ST3_BOSS_MAXATK);
			break;
		case 3:
			set_ch_stat(ST4_BOSS_NAME,now_edit,ST4_BOSS_HP,ST4_BOSS_MINATK,ST4_BOSS_MAXATK);
			break;
		case 4:
			set_ch_stat(ST5_BOSS_NAME,now_edit,ST5_BOSS_HP,ST5_BOSS_MINATK,ST5_BOSS_MAXATK);
			break;
		case 5:
			set_ch_stat("enemy",now_edit,100,10,20);
			break;
	}
}

//�����o�[�X�e�[�^�X�ݒ胂�[�h
void set_member_stat_mode(){
	struct character *now_edit;
	struct character draft;
	//���[�h�I���t���[���̃J�[�]�����W�ϐ�
	struct arrow_pos set_ch_arrow[] = {
		{EDIT_MODE_SELECT_FLAME_X + 3,EDIT_MODE_SELECT_FLAME_Y+3},
		{EDIT_MODE_SELECT_FLAME_X + 3,EDIT_MODE_SELECT_FLAME_Y+4},
		{EDIT_MODE_SELECT_FLAME_X + 3,EDIT_MODE_SELECT_FLAME_Y+5},
		{EDIT_MODE_SELECT_FLAME_X + 3,EDIT_MODE_SELECT_FLAME_Y+6},
		{EDIT_MODE_SELECT_FLAME_X + 3,EDIT_MODE_SELECT_FLAME_Y+7},
		{EDIT_MODE_SELECT_FLAME_X + 3,EDIT_MODE_SELECT_FLAME_Y+8}
	};
	char draft_name[] = "hoge";
	draft.name = draft_name;
	flame_flush();
	make_flame(EDIT_MODE_SELECT_FLAME_WIDTH,EDIT_MODE_SELECT_FLAME_HEIGHT,EDIT_MODE_SELECT_FLAME_X,EDIT_MODE_SELECT_FLAME_Y);
	show_ch_stat(WIDTH - 36,3);
	print_line("Select Character",EDIT_MODE_SELECT_FLAME_X + 2,EDIT_MODE_SELECT_FLAME_Y+1);
	print_line("naoki",EDIT_MODE_SELECT_FLAME_X + 5,EDIT_MODE_SELECT_FLAME_Y+3);
	print_line("arist",EDIT_MODE_SELECT_FLAME_X + 5,EDIT_MODE_SELECT_FLAME_Y+4);
	print_line("lirel",EDIT_MODE_SELECT_FLAME_X + 5,EDIT_MODE_SELECT_FLAME_Y+5);
	print_line("boss1",EDIT_MODE_SELECT_FLAME_X + 5,EDIT_MODE_SELECT_FLAME_Y+6);
	print_line("boss2",EDIT_MODE_SELECT_FLAME_X + 5,EDIT_MODE_SELECT_FLAME_Y+7);
	print_line("exit",EDIT_MODE_SELECT_FLAME_X + 5,EDIT_MODE_SELECT_FLAME_Y+8);
	fflush(stdout);
	make_flame(EDIT_MODE_EDIT_FLAME_WIDTH,EDIT_MODE_EDIT_FLAME_HEIGHT,EDIT_MODE_EDIT_FLAME_X,EDIT_MODE_EDIT_FLAME_Y);
	mvcur(0,HEIGHT + 1);
	int flag = 1;
	int target = 0;
	struct input_assort tmp_input_ch;
	struct input_assort continue_check;
	while(flag){
		target = select_from_list(set_ch_arrow,6);
		switch(target){
			case '1':
			case 0:
				now_edit = &naoki;
				break;
			case '2':
			case 1:
				now_edit = &arist;
				break;
			case '3':
			case 2:
				now_edit = &lirel;
				break;
			case '4':
			case 3:
				now_edit = &boss1;
				break;
			case '5':
			case 4:
				now_edit = &boss2;
				break;
			case '9':
			case 5:
				flag = 0;
				break;
			default:
				continue;
		}
		//�e���v���[�g����I�����邩���m�F
		if(target != 5){
			if(check_window(ECHECK_TEMPLATE_FLAME_WIDTH,ECHECK_TEMPLATE_FLAME_HEIGHT,ECHECK_TEMPLATE_FLAME_X,ECHECK_TEMPLATE_FLAME_Y,"Choose from tamplate?")){
				sub_flame_clean(EDIT_MODE_EDIT_FLAME_WIDTH - 2,EDIT_MODE_EDIT_FLAME_HEIGHT - 2,EDIT_MODE_EDIT_FLAME_X + 1,EDIT_MODE_EDIT_FLAME_Y + 1);
				switch(target){
					case 0:
					case 1:
					case 2:
						set_stat_from_template_mamber(now_edit,target);
						break;
					case 3:
					case 4:
						set_stat_from_template_enemy(now_edit);
						break;
				}
			}else{
				sub_flame_clean(EDIT_MODE_EDIT_FLAME_WIDTH - 2,EDIT_MODE_EDIT_FLAME_HEIGHT - 2,EDIT_MODE_EDIT_FLAME_X + 1,EDIT_MODE_EDIT_FLAME_Y + 1);
				mvcur(EDIT_MODE_EDIT_FLAME_CHAR_X,EDIT_MODE_EDIT_FLAME_CHAR_Y);
				printf("Selected Character: %s",now_edit->name);
				mvcur(EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 1);
				printf("    HP : %3d",now_edit->max_hp);
				mvcur(EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 2);
				if(now_edit == &arist){
					printf("  HEAL : %3d",now_edit->max_atk);
				}else{
					printf("   ATK : %3d �` %3d",now_edit->min_atk,now_edit->max_atk);
				}
				mvcur(EDIT_MODE_EDIT_FLAME_CHAR_X,EDIT_MODE_EDIT_FLAME_CHAR_Y + 5);
				printf("New Status:");
				mvcur(EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 6);
				printf("    HP : ");
				mvcur(EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 7);
				if(now_edit != &arist){
					printf("MINATK : ");
				}else{
					printf("  HEAL : ");
				}
				mvcur(EDIT_MODE_EDIT_FLAME_CHAR_X + 1,EDIT_MODE_EDIT_FLAME_CHAR_Y + 8);
				if(now_edit != &arist){
					printf("MAXATK : ");
				}
				mvcur(EDIT_MODE_EDIT_FLAME_CHAR_X + 10,EDIT_MODE_EDIT_FLAME_CHAR_Y + 6);
				scanf("%d",&draft.hp);	
				mvcur(EDIT_MODE_EDIT_FLAME_CHAR_X + 10,EDIT_MODE_EDIT_FLAME_CHAR_Y + 7);
				if(now_edit != &arist){
					scanf("%d",&draft.min_atk);	
				}else{
					scanf("%d",&draft.max_atk);
					draft.min_atk = 0;
				}
				mvcur(EDIT_MODE_EDIT_FLAME_CHAR_X + 10,EDIT_MODE_EDIT_FLAME_CHAR_Y + 8);
				if(now_edit != &arist){
					scanf("%d",&draft.max_atk);
				}
				//scanf�ŘR�ꂽEnter���󂯗���
				getchar();
				if(check_window(ECHECK_SELECT_FLAME_WIDTH, ECHECK_SELECT_FLAME_HEIGHT, ECHECK_SELECT_FLAME_X, ECHECK_SELECT_FLAME_Y,"Admit Change?")){
					set_ch_stat(now_edit->name,now_edit,draft.hp,draft.min_atk,draft.max_atk);
				}
			}
		}
		sub_flame_clean(EDIT_MODE_EDIT_FLAME_WIDTH - 2,EDIT_MODE_EDIT_FLAME_HEIGHT - 2,EDIT_MODE_EDIT_FLAME_X + 1,EDIT_MODE_EDIT_FLAME_Y + 1);
		show_ch_stat(WIDTH - 36,3);
		mvcur(0,HEIGHT + 1);
		print_line(" ",set_ch_arrow[target].x,set_ch_arrow[target].y);
	}
}

//�����ݒ胂�[�h
void set_weapon_mode(){
	int target_chara	= 0;
	int target_equip = 0;
	struct weapon *weapon_list;
	int weapon_amount = 0;
	int label = 0;
	//�ΏۑI���t���[���̃J�[�\�����W�ϐ�
	struct arrow_pos arrow[] = {
		{SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2 - 2,SET_WEAPON_MODE_FLAME_Y+4},
		{SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2 - 2,SET_WEAPON_MODE_FLAME_Y+5}
	};
	//�����I���̃J�[�\�����W�ϐ�
	struct arrow_pos w_arrow[] = {
		{SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2 - 2,SET_WEAPON_MODE_FLAME_Y + 3},
		{SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2 - 2,SET_WEAPON_MODE_FLAME_Y + 4},
		{SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2 - 2,SET_WEAPON_MODE_FLAME_Y + 5},
		{SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2 - 2,SET_WEAPON_MODE_FLAME_Y + 6}
	};
	/* �����ύX�L�����I�� */
	make_flame(SET_WEAPON_MODE_FLAME_WIDTH,SET_WEAPON_MODE_FLAME_HEIGHT,SET_WEAPON_MODE_FLAME_X,SET_WEAPON_MODE_FLAME_Y);
	print_line("Select edit",SET_WEAPON_MODE_FLAME_X + 2,SET_WEAPON_MODE_FLAME_Y + 1);
	print_line("     character",SET_WEAPON_MODE_FLAME_X + 2,SET_WEAPON_MODE_FLAME_Y + 2);
	print_line("  Naoki",SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2,SET_WEAPON_MODE_FLAME_Y + 4);
	print_line("  Arist",SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2,SET_WEAPON_MODE_FLAME_Y + 5);
	target_chara = select_from_list(arrow,2);
	/* �ύX�ΏۑI�� */
	make_flame(SET_WEAPON_MODE_FLAME_WIDTH,SET_WEAPON_MODE_FLAME_HEIGHT,SET_WEAPON_MODE_FLAME_X,SET_WEAPON_MODE_FLAME_Y);
	print_line("Which edit",SET_WEAPON_MODE_FLAME_X + 2,SET_WEAPON_MODE_FLAME_Y + 1);
	print_line("         equip",SET_WEAPON_MODE_FLAME_X + 2,SET_WEAPON_MODE_FLAME_Y + 2);
	print_line(" Weapon",SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2,SET_WEAPON_MODE_FLAME_Y + 4);
	print_line(" Protector",SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2,SET_WEAPON_MODE_FLAME_Y + 5);
	target_equip = select_from_list(arrow,2);
	switch(target_equip){
		case 0:
			make_flame(SET_WEAPON_MODE_FLAME_WIDTH,SET_WEAPON_MODE_FLAME_HEIGHT,SET_WEAPON_MODE_FLAME_X,SET_WEAPON_MODE_FLAME_Y);
			print_line("Select weapon:",SET_WEAPON_MODE_FLAME_X + 2,SET_WEAPON_MODE_FLAME_Y + 1);
			switch(target_chara){
				case 0:
					weapon_list = all_weapons;
					weapon_amount = WEPONS_AMOUNT;
					break;
				case 1:
					weapon_list = all_weapons4back;
					weapon_amount = WEPONS_AMOUNT_BACK;
					break;
			}
			for(int i = 0; i <weapon_amount; i++){
				mvcur(SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2,SET_WEAPON_MODE_FLAME_Y + 3 + i);
				printf("%s",(weapon_list + i)->name);
			}
			label = select_from_list(w_arrow,weapon_amount);
			if(target_chara == 0){
				using_weapon = &all_weapons[label];
			}else if(target_chara == 1){
				arist_using_weapon = &all_weapons4back[label];
			}
			break;
		case 1:
			make_flame(SET_WEAPON_MODE_FLAME_WIDTH + 5,SET_WEAPON_MODE_FLAME_HEIGHT,SET_WEAPON_MODE_FLAME_X,SET_WEAPON_MODE_FLAME_Y);
			print_line("Select protector:",SET_WEAPON_MODE_FLAME_X + 2,SET_WEAPON_MODE_FLAME_Y + 1);
			for(int i = 0; i < PROTECTORS_AMOUNT; i++){
				mvcur(SET_WEAPON_MODE_FLAME_X + (SET_WEAPON_MODE_FLAME_WIDTH - 7) / 2,SET_WEAPON_MODE_FLAME_Y + 3 + i);
				printf("%s",all_protectors[i].name);
			}
			label = select_from_list(w_arrow,PROTECTORS_AMOUNT);
			if(target_chara == 0){
				using_protector = &all_protectors[label];
			}else if(target_chara == 1){
				arist_using_protector = &all_protectors[label];
			}
			break;
	}
}

void set_item_mode(){
	struct arrow_pos arrow[] = {
		{(WIDTH / 2) - 5,(HEIGHT - 3) / 2 + 3},
		{(WIDTH / 2) - 2,(HEIGHT - 3) / 2 + 3},
		{(WIDTH / 2) + 1,(HEIGHT - 3) / 2 + 3},
		{(WIDTH / 2) + 4,(HEIGHT - 3) / 2 + 3}
	};
	make_flame(23,5,(WIDTH - 20) / 2 - 1 ,(HEIGHT - 3) / 2);
	print_line("Potion amaount edit",(WIDTH / 2) - 9,(HEIGHT - 3) / 2 + 1);
	print_line("0  1  2  3",(WIDTH / 2) - 4,(HEIGHT - 3) / 2 + 3);
	potion_amount = select_from_hlist(arrow,4);
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
}

int main(){
	//�^�[�~�i���̕����𗬂��ăJ�[�\���ʒu��(1,1)�ɂ���
	init_term();
	//��g�E�B���h�E�t���[���̍쐬
	make_flame(WIDTH,HEIGHT,MAIN_FLAME_X,MAIN_FLAME_Y);

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
	print_line("for PaperTest Ver",(WIDTH - 17)/2,14);
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
		star_x[i] = rand() % (WIDTH - 2) + 2;
		star_y[i] = rand() % (HEIGHT - 2) + 2;
		//�������W���^�C�g�����S�̂���͈͂Ƃ��Ԃ��Ă�����
		if(star_y[i] >= 5 && star_y[i] < 15){
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
	}while((mykbhit().input_char) != ENTERKEY);

	flame_flush();
	initchara();

	int exit_flag = 1;
	int mode = 0;
	struct input_assort check_select;
	struct character *enemies[4]= {&dummy,&dummy,&dummy,&dummy};
	while(exit_flag){
		mode = main_window_init();
		//���͂��~�X�łȂ������m�F
		if(!check_window(SCHECK_SELECT_FLAME_WIDTH, SCHECK_SELECT_FLAME_HEIGHT, SCHECK_SELECT_FLAME_X, SCHECK_SELECT_FLAME_Y,"Continue?")){
			continue;
		}

		switch(mode){
			case 0:
				switch(select_stage()){
					case 0://stage1 vs boss
						enemies[0] = &boss1;
						set_ch_stat(ST1_BOSS_NAME,&boss1,ST1_BOSS_HP,ST1_BOSS_MINATK,ST1_BOSS_MAXATK);
						set_ch_stat(FRONT1_NAME,&lirel,FRONT1_HP,FRONT1_MINATK,FRONT1_MAXATK);
						set_ch_stat(BACK_NAME,&arist,BACK_HP_ST1,0,BACK_HEAL_ST1);
						battle(&lirel,&arist,enemies,1);
						flame_flush();
						break;
					case 1://stage2 vs boss
						enemies[0] = &boss1;
						set_ch_stat(ST2_BOSS_NAME,&boss1,ST2_BOSS_HP,ST2_BOSS_MINATK,ST2_BOSS_MAXATK);
						set_ch_stat(FRONT2_NAME,&naoki,FRONT2_HP_ST2,FRONT2_MINATK_ST2,FRONT2_MAXATK_ST2);
						set_ch_stat(BACK_NAME,&arist,BACK_HP_ST2,0,BACK_HEAL_ST2);
						battle(&naoki,&arist,enemies,1);
						flame_flush();
						break;
					case 2://stage3 vs weakenemy
						enemies[0] = &boss1;
						enemies[1] = &boss2;
						set_ch_stat("enemy",&boss1,ST2_BOSS_HP,ST2_BOSS_MINATK,ST2_BOSS_MAXATK);
						set_ch_stat("enemy",&boss2,ST2_BOSS_HP,ST2_BOSS_MINATK,ST2_BOSS_MAXATK);
						set_ch_stat(BACK_NAME,&arist,BACK_HP_ST3,0,BACK_HEAL_ST3);
						set_ch_stat(FRONT2_NAME,&naoki,FRONT2_HP_ST3,FRONT2_MINATK_ST3,FRONT2_MAXATK_ST3);
						battle(&naoki,&arist,enemies,2);
						flame_flush();
						break;
					case 3://stage3 vs boss
						enemies[0] = &boss1;
						set_ch_stat(ST3_BOSS_NAME,&boss1,ST3_BOSS_HP,ST3_BOSS_MINATK,ST3_BOSS_MAXATK);
						set_ch_stat(FRONT2_NAME,&naoki,FRONT2_HP_ST3,FRONT2_MINATK_ST3,FRONT2_MAXATK_ST3);
						set_ch_stat(BACK_NAME,&arist,BACK_HP_ST3,0,BACK_HEAL_ST3);
						battle(&naoki,&arist,enemies,1);
						flame_flush();
						break;
					case 4://stage4 vs weakenemy
						enemies[0] = &boss1;
						enemies[1] = &boss2;
						set_ch_stat("enemy",&boss1,ST2_BOSS_HP,ST2_BOSS_MINATK,ST2_BOSS_MAXATK);
						set_ch_stat("enemy",&boss2,ST2_BOSS_HP,ST2_BOSS_MINATK,ST2_BOSS_MAXATK);
						set_ch_stat(BACK_NAME,&arist,BACK_HP_ST4,0,BACK_HEAL_ST4);
						set_ch_stat(FRONT2_NAME,&naoki,FRONT2_HP_ST4,FRONT2_MINATK_ST4,FRONT2_MAXATK_ST4);
						battle(&naoki,&arist,enemies,2);
						flame_flush();
						break;
					case 5://stage4 vs boss
						enemies[0] = &boss1;
						set_ch_stat(ST4_BOSS_NAME,&boss1,ST4_BOSS_HP,ST4_BOSS_MINATK,ST4_BOSS_MAXATK);
						set_ch_stat(FRONT3_NAME,&robo,FRONT3_HP,FRONT3_MINATK,FRONT3_MAXATK);
						battle(&robo,&dummy,enemies,1);
						flame_flush();
						break;
					case 6://stage5 vs boss
						enemies[0] = &boss1;
						set_ch_stat(ST5_BOSS_NAME,&boss1,ST5_BOSS_HP,ST5_BOSS_MINATK,ST5_BOSS_MAXATK);
						set_ch_stat(FRONT4_NAME,&robo,FRONT4_HP,FRONT4_MINATK,FRONT4_MAXATK);
						battle(&robo,&dummy,enemies,1);
						flame_flush();
						break;
					default:
						flame_clean();
						break;
				}
				break;
			case 1:
				set_weapon_mode();
				break;
			case 2:
				set_item_mode();
				break;
			case 3:
				set_member_stat_mode();
				flame_flush();
				break;
			case 5:
				exit_flag = 0;
				break;
		}
	}
}