#include "thebeautifulsky.h"

event decide_event(arrow_pos exit_point){
	event selected_event;
	/* ���j���[�\�����ǂ����𔻒� */
	if(exit_point.x == 58 && exit_point.y == 24){
		selected_event = open_menu;
	}else{
		switch(now_stage){
			case stage1:
				if(exit_point.x == 31 && exit_point.y == 7){
					/* �{�X���B */
					selected_event = battle_event;
					front = &lirel;
					back = &arist;
					set_ch_stat(ST1_BOSS_NAME,&boss1,ST1_BOSS_HP,ST1_BOSS_HP,ST1_BOSS_MINATK,ST1_BOSS_MAXATK);
					enemies[0] = &boss1;
					enemies[1] = &dummy;
					enemy_amount = 1;
					/* �}�b�v���A���̍��W���w�� */
					start_pos.x = exit_point.x - 2;
					start_pos.y = (exit_point.y + 1 ) - 2;
					before_battle_st1();
				}else if((exit_point.x == 4 || exit_point.x == 5) && exit_point.y == 15){
					/* ��ԍ��̕������B */
					selected_event = talk_event;
					room_id = 0;
					/* �}�b�v���A���̍��W���w�� */
					start_pos.x = exit_point.x - 2;
					start_pos.y = (exit_point.y + 1 ) - 2;
				}else if(exit_point.x == 25 && exit_point.y == 14){
					/* �^�񒆂̕������B */
					selected_event = talk_event;
					room_id = 1;
					/* �}�b�v���A���̍��W���w�� */
					start_pos.x = exit_point.x - 2;
					start_pos.y = (exit_point.y + 1 ) - 2;
				}
				/* �E���̐N���֎~ */
				if(exit_point.x == 35 && exit_point.y == 17){
					room_id = 2;
					selected_event = talk_event;
					/* �}�b�v���A���̍��W���w�� */
					start_pos.x = exit_point.x - 1 - 2;
					start_pos.y = exit_point.y - 2;
					/* �E���̐N���֎~ */
					if(exit_point.x == 35 && exit_point.y == 17){
						selected_event = talk_event;
					}
				}
				break;
			case stage2:
				if(exit_point.x == 28 && exit_point.y == 9){
					/* �{�X���B */
					room_id = 2;
					selected_event = battle_event;
					front = &naoki;
					back = &arist;
					set_ch_stat(ST2_BOSS_NAME,&boss1,ST2_BOSS_HP,ST2_BOSS_HP,ST2_BOSS_MINATK,ST2_BOSS_MAXATK);
					enemies[0] = &boss1;
					enemies[1] = &dummy;
					enemy_amount = 1;
					before_battle_st2();
				}else if(exit_point.x == 15 && exit_point.y == 15){
					/* ���̕��� */
					room_id = 1;
					if(!talk_event_st2_1_arrived){
						room_id = 1;
						selected_event = battle_event;
						front = &naoki;
						back = &arist;
						set_ch_stat(ST2_WEAK_NAME,&boss1,ST1_BOSS_HP,ST1_BOSS_HP,ST1_BOSS_MINATK,ST1_BOSS_MAXATK);
						enemies[0] = &boss1;
						enemies[1] = &dummy;
						enemy_amount = 1;
						talk_event_st2_1_arrived = 1;
					}else{
						selected_event = talk_event;
					}
				}else if(exit_point.x == 41 && exit_point.y == 15){
					/* �E�̕��� */
					room_id = 0;
					selected_event = talk_event;
				}else{
				}
				/* �}�b�v���A���̍��W���w�� */
				start_pos.x = exit_point.x - 2;
				start_pos.y = (exit_point.y + 1 ) - 2;
				break;
			case stage3_1:	//�����}�b�v
				if(exit_point.x == 58 && exit_point.y == 18){
					/* �E�}�b�v�ւ̈ړ� */
					selected_event = move_map;
					now_stage = stage3_2;
					start_pos.x= 1;
					start_pos.y = 17 -  2;
				}else if(exit_point.x == 2 && exit_point.y == 18){
					/* ���}�b�v�ւ̈ړ� */
					selected_event = move_map;
					now_stage = stage3_3;
					start_pos.x= 56 - 2;
					start_pos.y = 17 -  2;
				}else if(exit_point.x == 15 && exit_point.y == 15){
					/* ���̉� */
					room_id = 3;
					selected_event = talk_event;
					/* �}�b�v���A���̍��W���w�� */
					start_pos.x= 15 - 2;
					start_pos.y = 15 + 1 - 2;
				}else if(exit_point.x == 28 && exit_point.y == 9){
					/* �{�X���B */
					room_id = 4;
					selected_event = battle_event;
					front = &naoki;
					back = &arist;
					set_ch_stat(ST3_BOSS_NAME,&boss1,ST3_BOSS_HP,ST3_BOSS_HP,ST3_BOSS_MINATK,ST3_BOSS_MAXATK);
					enemies[0] = &boss1;
					enemies[1] = &dummy;
					enemy_amount = 1;
					before_battle_st3();
				}else if(exit_point.x == 41 && exit_point.y == 15){
					/* �E�̉� */
					room_id = 5;
					selected_event = talk_event;
					/* �}�b�v���A���̍��W���w�� */
					start_pos.x= 41 - 2;
					start_pos.y = 15 + 1 - 2;
				}
				break;
			case stage3_2:	//�E�}�b�v
				if(exit_point.x == 3 && exit_point.y == 17){
					/* �����}�b�v�ւ̈ړ� */
					selected_event = move_map;
					now_stage = stage3_1;
					start_pos.x = 57 - 2;
					start_pos.y = 18 - 2;
				}else if(exit_point.x == 43 && exit_point.y == 14){
					/* ���̉� */
					room_id = 7;
					if(!battle_event_st3_7_arrived){ //�n�߂Ă̖K��̎�
						selected_event = battle_event;
						/* �L�����N�^�[�Z�b�g */
						front = &naoki;
						back = &arist;
						set_ch_stat(ST31_WEAK_NAME,&boss1,ST1_BOSS_HP,ST1_BOSS_HP,ST1_BOSS_MINATK,ST1_BOSS_MAXATK);
						set_ch_stat(ST32_WEAK_NAME,&boss2,ST1_BOSS_HP,ST1_BOSS_HP,ST1_BOSS_MINATK,ST1_BOSS_MAXATK);
						enemies[0] = &boss1;
						enemies[1] = &boss2;
						enemy_amount = 2;
						battle_event_st3_7_arrived = 1;
					}else{ //2��߈ȍ~�̎�
						room_id = 6; //�߂�ǂ����������̂ŁA�ׂ̕����ɋU�����ē����C�x���g���N����
						selected_event = talk_event;
					}
					/* �}�b�v���A���̍��W���w�� */
					start_pos.x= 43 - 2;
					start_pos.y = 14 + 1 - 2;
				}else if(exit_point.x == 15 && exit_point.y == 14){
					/* �E�̉� */
					room_id = 6;
					selected_event = talk_event;
					/* �}�b�v���A���̍��W���w�� */
					start_pos.x= 15 - 2;
					start_pos.y = 14 + 1 - 2;
				}
				break;
			case stage3_3:	//���}�b�v
				if(exit_point.x == 57 && exit_point.y == 17){
					/* �����}�b�v�ւ̈ړ� */
					selected_event = move_map;
					now_stage = stage3_1;
					start_pos.x = 2;
					start_pos.y = 18 - 2;
				}else if(exit_point.x == 43 && exit_point.y == 14){
					/* ����̉� */
					room_id = 2;
					selected_event = talk_event;
					/* �}�b�v���A���̍��W���w�� */
					start_pos.x= 43 - 2;
					start_pos.y = 14 + 1 - 2;
				}else if(exit_point.x == 27 && exit_point.y == 20){
					/* ���̉� */
					room_id = 1;
					selected_event = talk_event;
					/* �}�b�v���A���̍��W���w�� */
					start_pos.x= 27 - 2;
					start_pos.y = 20 - 1 - 2;
				}else if(exit_point.x == 15 && exit_point.y == 14){
					/* �E��̉� */
					room_id = 0;
					selected_event = talk_event;
					/* �}�b�v���A���̍��W���w�� */
					start_pos.x= 15 - 2;
					start_pos.y = 14 + 1 - 2;
				}
				break;
			case stage4_1: //���}�b�v
				if(exit_point.x == 55 && (exit_point.y == 13 || exit_point.y == 14)){
					/* �����}�b�v�ւ̈ړ� */
					selected_event = move_map;
					now_stage = stage4_2;
					mapcpy(now_map,maps[now_stage]);
					coorcpy(now_map_coor,map_coors[now_stage]);
					start_pos.x = 4 - 2;
					start_pos.y = 14 - 2;
				}else if((exit_point.x == 14 || exit_point.x == 15) && exit_point.y == 11){
					/* �����̉� */
					selected_event = talk_event;
					room_id = 0;
					/* �}�b�v���A���̍��W���w�� */
					start_pos.x = exit_point.x - 2;;
					start_pos.y = 12 - 2;
				}else if(exit_point.x == 40 && exit_point.y == 6){
					/* ��̉� */
					room_id = 1;
					selected_event = talk_event;
					/* �}�b�v���A���̍��W���w�� */
					start_pos.x= 40 - 1 - 2;
					start_pos.y = 6 - 2;
				}else if(exit_point.x == 38 && exit_point.y == 11){
					/* �E���̉� */
					room_id = 2;
					selected_event = talk_event;
					/* �}�b�v���A���̍��W���w�� */
					start_pos.x= exit_point.x - 2;
					start_pos.y = 11 + 1 - 2;
				}
				break;
			case stage4_2: //�����}�b�v
				if(exit_point.x == 55 && (exit_point.y == 14 || exit_point.y == 15)){
					/* �E�}�b�v�ւ̈ړ� */
					selected_event = move_map;
					now_stage = stage4_3;
					mapcpy(now_map,maps[now_stage]);
					coorcpy(now_map_coor,map_coors[now_stage]);
					start_pos.x = 2;
					start_pos.y = 14 - 2;
				}else if(exit_point.x == 3 && (exit_point.y == 14 || exit_point.y == 13)){
					/* ���}�b�v�ւ̈ړ� */
					selected_event = move_map;
					now_stage = stage4_1;
					mapcpy(now_map,maps[now_stage]);
					coorcpy(now_map_coor,map_coors[now_stage]);
					start_pos.x = 54 - 2;
					start_pos.y = 14 - 2;
				}else if(exit_point.x == 20 && exit_point.y == 6){
					/* ��̉� */
					room_id = 3;
					selected_event = talk_event;
					/* �}�b�v���A���̍��W���w�� */
					start_pos.x= 20 - 1 - 2;
					start_pos.y = 6 - 2;
				}else if((exit_point.x == 36 || exit_point.x == 37 || exit_point.x == 38) && exit_point.y == 12){
					/* �{�X���B */
					room_id = 4;
					selected_event = battle_event;
					/* �L�����N�^�[�Z�b�g */
					front = &robo;
					back = &dummy;
					set_ch_stat(ST4_BOSS_NAME,&boss1,ST4_BOSS_HP,ST4_BOSS_HP,ST4_BOSS_MINATK,ST4_BOSS_MAXATK);
					enemies[0] = &boss1;
					enemies[1] = &dummy;
					enemy_amount = 1;
					before_battle_st4();
				}
				break;
			case stage4_3://�E�}�b�v
				/* �����}�b�v�ւ̈ړ� */
				if(exit_point.x == 2 && (exit_point.y == 14 || exit_point.y == 15)){
					selected_event = move_map;
					now_stage = stage4_2;
					mapcpy(now_map,maps[now_stage]);
					coorcpy(now_map_coor,map_coors[now_stage]);
					start_pos.x = 54 - 2;
					start_pos.y = 14 - 2;
				}else if((exit_point.x == 14 || exit_point.x == 15) && exit_point.y == 11){
					/* ���̉� */
					room_id = 5;
					if(!battle_event_st4_5_arrived){ //�n�߂Ă̖K��̎�
						selected_event = battle_event;
						/* �L�����N�^�[�Z�b�g */
						front = &naoki;
						back = &arist;
						set_ch_stat(ST41_WEAK_NAME,&boss1,ST1_BOSS_HP,ST1_BOSS_HP,ST1_BOSS_MINATK,ST1_BOSS_MAXATK);
						set_ch_stat(ST42_WEAK_NAME,&boss2,ST1_BOSS_HP,ST1_BOSS_HP,ST1_BOSS_MINATK,ST1_BOSS_MAXATK);
						enemies[0] = &boss1;
						enemies[1] = &boss2;
						enemy_amount = 2;
						battle_event_st4_5_arrived = 1;
					}else{ //2��߈ȍ~�̎�
						selected_event = talk_event;
					}
					start_pos.x = exit_point.x - 2;
					start_pos.y = 12 - 2;
				}else if(exit_point.x == 40 && exit_point.y == 6){
					/* ��̉� */
					room_id = 6;
					selected_event = talk_event;
					/* �}�b�v���A���̍��W���w�� */
					start_pos.x=  40 - 1 - 2;
					start_pos.y = 6 - 2;
				}
				break;
			default:
				break;
		}
	}
	return selected_event;
}
