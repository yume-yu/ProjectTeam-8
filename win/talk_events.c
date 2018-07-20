/**
 * @file talk_event.c
 * @brief �e��b�C�x���g���ƂɌĂяo����鏈�����܂Ƃ߂��t�@�C��
 * @author yume_yu
 * @date
 */

#include "thebeautifulsky.h"

/* ���[�������|�[�V���������������̋���  */
void lirel_find_potion(){
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	extendstr event_text[] = {
		{"���[�����F�u�ށA����́v��  ",0,0},
		{"�|�[�V��������������  ",0,0}
	};
	extendstr error_text[] = {
		{"�|�[�V�����͂���ȏ㎝�ĂȂ��̂Œ��߂���  ",0,0},
	};
	exstrcpy(now_text,event_text,2);
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(event_text));
	if(get_potion()){
	}else{
		exstrcpy(now_text,error_text,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3,eslengthof(error_text));
	}
}

/* �i�I�L���|�[�V���������������̋���  */
void naoki_find_potion(){
	//make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	extendstr event_text[] = {
		{"�i�I�L�F�u�������́A�����I�v��  ",0,0},
		{"�|�[�V��������������  ",0,0}
	};
	extendstr error_text[] = {
		{"�|�[�V�����͂���ȏ㎝�ĂȂ��c��  ",0,0},
	};
	exstrcpy(now_text,event_text,2);
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(event_text));
	if(get_potion()){
	}else{
		exstrcpy(now_text,error_text,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3,eslengthof(error_text));
	}
}

bool instory_yesno(int y){
	arrow_pos yn[10] = {
		{11,y,0,0},
		{18,y,0,0}
	};
	char *yesno = "  �͂�   ������";
	print_line(yesno,10,y);
	return !select_from_hlist(yn,2);
}

/* �X�e�[�W1 �J�n���� */
void guide_st1(){
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,lirel_said,eslengthof(lirel_said));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(lirel_said));
}

/* �X�e�[�W1 �N���֎~ */
void noentry_st1(){
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,lirel_stop,eslengthof(lirel_stop));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(lirel_said));
}

/* �X�e�[�W1 �^�񒆂̕��� */
void talk_event_st1_1(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	extendstr error_text[] = {
		{"���ʂ��̊k����  ",0,0},
	};
	exstrcpy(now_text,error_text,1);
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(error_text));
}

/* �X�e�[�W1 ���̕��� */
bool talk_event_st1_0_arrived = false;
void talk_event_st1_0(){
	if(talk_event_st1_0_arrived){
		talk_event_st1_1();
	}else{
		flame_flush();
		lirel_find_potion();
		talk_event_st1_0_arrived = true;
	}
}

/* �X�e�[�W1 �{�X��O */
void before_battle_st1(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,beforebattle_stage1, eslengthof(beforebattle_stage1));
	string_march(now_text,BATTLE_MODE_COMMAND_POS - 2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(beforebattle_stage1));
}

/* �X�e�[�W1 �{�X��� */
void after_battle_st1(){
	flame_flush();
	//make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,afterbattle_stage1, eslengthof(afterbattle_stage1));
	string_march(now_text,2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(afterbattle_stage1));
	flame_clean();
}

/* �X�e�[�W2 �E�̕��� */
bool talk_event_st2_0_arrived = false;
void talk_event_st2_0(){
	flame_flush();
	if(!talk_event_st2_0_arrived){
		exstrcpy(now_text,talk_st2_0_1,eslengthof(talk_st2_0_1));
		string_march(now_text,2,2,eslengthof(talk_st2_0_1));
		flame_clean();
		exstrcpy(now_text,talk_st2_0_2,eslengthof(talk_st2_0_2));
		string_march(now_text,2,2,eslengthof(talk_st2_0_2));
		talk_event_st2_0_arrived = true;
	}else{
		extendstr error_text[] = {
			{"�����ɂ͂Ȃɂ��Ȃ���  ",0,0},
		};
		exstrcpy(now_text,error_text,1);
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(error_text));
	}
}

bool talk_event_st2_1_arrived = false;
void talk_event_st2_1(){
	flame_flush();
	extendstr error_text[] = {
		{"�����ɂ͂Ȃɂ��Ȃ���  ",0,0},
	};
	exstrcpy(now_text,error_text,1);
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(error_text));
}

/* �X�e�[�W2 �{�X��O */
void before_battle_st2(){
	flame_flush();
	exstrcpy(now_text,beforebattle_stage2, eslengthof(beforebattle_stage2));
	string_march(now_text,2,2,eslengthof(beforebattle_stage2));
}

/* �X�e�[�W2 �{�X��� */
void after_battle_st2(){
	flame_flush();
	//make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,afterbattle_stage2, eslengthof(afterbattle_stage2));
	string_march(now_text,2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT - 1,eslengthof(afterbattle_stage2));
	flame_clean();
}

/* �X�e�[�W3 �E�}�b�v����̕��� */
void talk_event_st3_0(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,talk_st3_0,eslengthof(talk_st3_0));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(talk_st3_0));
}

/* �X�e�[�W3 �E�}�b�v���̕��� */
bool talk_event_st3_1_arrived = false;
void talk_event_st3_1(){
	flame_flush();
	if(!talk_event_st3_1_arrived){ //���߂ė����Ƃ����ǂ���
		exstrcpy(now_text,talk_st3_1,eslengthof(talk_st3_1));
		string_march(now_text,2,2,eslengthof(talk_st3_1));
		if(instory_yesno(2 + eslengthof(talk_st3_1) + 1)){
			using_weapon = &all_weapons[1];
			exstrcpy(now_text,talk_st3_1_2,eslengthof(talk_st3_1_2));
			string_march(now_text,2,2 + eslengthof(talk_st3_1) + 3,sizeof(talk_st3_1_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st3_1_3,eslengthof(talk_st3_1_3));
			string_march(now_text,2,2 + eslengthof(talk_st3_1) + 3,sizeof(talk_st3_1_3)/sizeof(extendstr));
		}
		talk_event_st3_1_arrived = true;
	}else if(using_weapon != &all_weapons[1]){ //���߂Ăł͂Ȃ��A�������e�ł͂Ȃ���
		exstrcpy(now_text,talk_st3_1_1,eslengthof(talk_st3_1_1));
		string_march(now_text,2,2,eslengthof(talk_st3_1_1));
		if(instory_yesno(2 + eslengthof(talk_st3_1_1) + 1)){
			using_weapon = &all_weapons[1];
			exstrcpy(now_text,talk_st3_1_2,eslengthof(talk_st3_1_2));
			string_march(now_text,2,2 + eslengthof(talk_st3_1) + 3,sizeof(talk_st3_1_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st3_1_3,eslengthof(talk_st3_1_3));
			string_march(now_text,2,2 + eslengthof(talk_st3_1) + 3,sizeof(talk_st3_1_3)/sizeof(extendstr));
		}
	}else{
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		exstrcpy(now_text, talk_st3_1_2,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(talk_st3_1_2));
	}
}

/* �X�e�[�W3 �E�}�b�v�E��̕��� */
bool talk_event_st3_2_arrived = false;
void talk_event_st3_2(){
	flame_flush();
	if(!talk_event_st3_2_arrived){ //���߂ė����Ƃ����ǂ���
		exstrcpy(now_text,talk_st3_2,eslengthof(talk_st3_2));
		string_march(now_text,2,2,eslengthof(talk_st3_2));
		if(instory_yesno(2 + eslengthof(talk_st3_2) + 1)){
			using_protector = &all_protectors[2];
			exstrcpy(now_text,talk_st3_2_2,eslengthof(talk_st3_2_2));
			string_march(now_text,2,2 + eslengthof(talk_st3_2) + 3,sizeof(talk_st3_2_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st3_2_3,eslengthof(talk_st3_2_3));
			string_march(now_text,2,2 + eslengthof(talk_st3_2) + 3,sizeof(talk_st3_2_3)/sizeof(extendstr));
		}
		talk_event_st3_2_arrived = true;
	}else if(using_protector != &all_protectors[2]){ //���߂Ăł͂Ȃ��A�������h�앞�ł͂Ȃ���
		exstrcpy(now_text,talk_st3_2_1,eslengthof(talk_st3_2_1));
		string_march(now_text,2,2,eslengthof(talk_st3_2_1));
		if(instory_yesno(2 + eslengthof(talk_st3_2_1) + 1)){
			using_protector = &all_protectors[2];
			exstrcpy(now_text,talk_st3_2_2,eslengthof(talk_st3_2_2));
			string_march(now_text,2,2 + eslengthof(talk_st3_2) + 3,sizeof(talk_st3_2_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st3_2_3,eslengthof(talk_st3_2_3));
			string_march(now_text,2,2 + eslengthof(talk_st3_2) + 3,sizeof(talk_st3_2_3)/sizeof(extendstr));
		}
	}else{
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		exstrcpy(now_text, talk_st3_2_2,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(talk_st3_2_2));
	}
}

/* �X�e�[�W3 �����}�b�v���̕��� */
bool talk_event_st3_3_arrived = false;
void talk_event_st3_3(){
	flame_flush();
	if(!talk_event_st3_3_arrived){ //���߂ė����Ƃ����ǂ���
		exstrcpy(now_text,talk_st3_3,eslengthof(talk_st3_3));
		string_march(now_text,2,2,eslengthof(talk_st3_3));
		if(instory_yesno(2 + eslengthof(talk_st3_3) + 1)){
			using_weapon = &all_weapons[2];
			exstrcpy(now_text,talk_st3_3_2,eslengthof(talk_st3_3_2));
			string_march(now_text,2,2 + eslengthof(talk_st3_3) + 3,sizeof(talk_st3_3_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st3_3_3,eslengthof(talk_st3_3_3));
			string_march(now_text,2,2 + eslengthof(talk_st3_3) + 3,sizeof(talk_st3_3_3)/sizeof(extendstr));
		}
		exstrcpy(now_text,talk_st3_3_0,eslengthof(talk_st3_3_0));
		string_march(now_text,2,2 + eslengthof(talk_st3_3) + 4,sizeof(talk_st3_3_0)/sizeof(extendstr));
		extendstr error_text[] = {
			{"�|�[�V�����͂���ȏ㎝�ĂȂ��̂ŕԂ�����  ",0,0},
		};
		if(get_potion()){
		}else{
			exstrcpy(now_text,error_text,1);
			string_march(now_text,2,2 + eslengthof(talk_st3_3) + 7,sizeof(error_text)/sizeof(extendstr));
		}
		talk_event_st3_3_arrived = true;
	}else if(using_weapon != &all_weapons[2]){ //���߂Ăł͂Ȃ��A�������e�ł͂Ȃ���
		exstrcpy(now_text,talk_st3_3_1,eslengthof(talk_st3_3_1));
		string_march(now_text,2,2,eslengthof(talk_st3_3_1));
		if(instory_yesno(2 + eslengthof(talk_st3_3_1) + 1)){
			using_weapon = &all_weapons[2];
			exstrcpy(now_text,talk_st3_3_2,eslengthof(talk_st3_3_2));
			string_march(now_text,2,2 + eslengthof(talk_st3_3) + 3,sizeof(talk_st3_3_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st3_3_3,eslengthof(talk_st3_3_3));
			string_march(now_text,2,2 + eslengthof(talk_st3_3) + 3,sizeof(talk_st3_3_3)/sizeof(extendstr));
		}
	}else{
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		exstrcpy(now_text, talk_st3_3_2,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(talk_st3_3_2));
	}
}

/* �X�e�[�W3 �����}�b�v���̕��� */
void talk_event_st3_5(){
	flame_flush();
	exstrcpy(now_text,talk_st3_5_1,eslengthof(talk_st3_5_1));
	string_march(now_text,2,2,eslengthof(talk_st3_5_1));
	flame_clean();
	exstrcpy(now_text,talk_st3_5_2,eslengthof(talk_st3_5_2));
	string_march(now_text,2,2,eslengthof(talk_st3_5_2));
	flame_clean();
	exstrcpy(now_text,talk_st3_5_3,eslengthof(talk_st3_5_3));
	string_march(now_text,2,2,eslengthof(talk_st3_5_3));
	have_nasu = 1;
}

/* �X�e�[�W3 �E�}�b�v���̕��� */
void talk_event_st3_6(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,talk_st3_6,eslengthof(talk_st3_6));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(talk_st3_6));
}

/* �X�e�[�W3 �E�}�b�v�E�̕��� */
bool battle_event_st3_7_arrived = false;

/* �X�e�[�W3 �{�X��O */
void before_battle_st3(){
	flame_flush();
	exstrcpy(now_text,beforebattle_stage3, eslengthof(beforebattle_stage3));
	string_march(now_text,2,2,eslengthof(beforebattle_stage3));
}

/* �X�e�[�W3 �{�X��� */
void after_battle_st3(){
	flame_flush();
	exstrcpy(now_text,afterbattle_stage3, eslengthof(afterbattle_stage3));
	string_march(now_text,2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(afterbattle_stage3));
	flame_clean();
}

/* �X�e�[�W4 �E�}�b�v�����̕��� */
bool talk_event_st4_0_arrived = false;
void talk_event_st4_0(){
	flame_flush();
	if(!talk_event_st4_0_arrived){ //���߂ė����Ƃ����ǂ���
		exstrcpy(now_text,talk_st4_0,eslengthof(talk_st4_0));
		string_march(now_text,2,2,eslengthof(talk_st4_0));
		if(instory_yesno(2 + eslengthof(talk_st4_0) + 1)){
			arist_using_weapon = &all_weapons4back[1];
			exstrcpy(now_text,talk_st4_0_2,eslengthof(talk_st4_0_2));
			string_march(now_text,2,2 + eslengthof(talk_st4_0) + 3,sizeof(talk_st4_0_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st4_0_3,eslengthof(talk_st4_0_3));
			string_march(now_text,2,2 + eslengthof(talk_st4_0) + 3,sizeof(talk_st4_0_3)/sizeof(extendstr));
		}
		talk_event_st4_0_arrived = true;
	}else if(arist_using_weapon != &all_weapons4back[1]){ //���߂Ăł͂Ȃ��A�������e�ł͂Ȃ���
		exstrcpy(now_text,talk_st4_0_1,eslengthof(talk_st4_0_1));
		string_march(now_text,2,2,eslengthof(talk_st4_0_1));
		if(instory_yesno(2 + eslengthof(talk_st4_0_1) + 1)){
			arist_using_weapon = &all_weapons4back[1];
			exstrcpy(now_text,talk_st4_0_2,eslengthof(talk_st4_0_2));
			string_march(now_text,2,2 + eslengthof(talk_st4_0) + 3,sizeof(talk_st4_0_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st4_0_3,eslengthof(talk_st4_0_3));
			string_march(now_text,2,2 + eslengthof(talk_st4_0) + 3,sizeof(talk_st4_0_3)/sizeof(extendstr));
		}
	}else{
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		exstrcpy(now_text, talk_st4_0_2,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(talk_st4_0_2));
	}
}

/* �X�e�[�W4 �E�}�b�v���̕��� */
bool talk_event_st4_1_arrived = false;
void talk_event_st4_1(){
	flame_flush();
	if(!talk_event_st4_1_arrived){ //���߂ė����Ƃ����ǂ���
		exstrcpy(now_text,talk_st4_1,eslengthof(talk_st4_1));
		string_march(now_text,2,2,eslengthof(talk_st4_1));
		if(instory_yesno(2 + eslengthof(talk_st4_1) + 1)){
			arist_using_protector = &all_protectors[1];
			exstrcpy(now_text,talk_st4_1_2,eslengthof(talk_st4_1_2));
			string_march(now_text,2,2 + eslengthof(talk_st4_1) + 3,sizeof(talk_st4_1_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st4_1_3,eslengthof(talk_st4_1_3));
			string_march(now_text,2,2 + eslengthof(talk_st4_1) + 3,sizeof(talk_st4_1_3)/sizeof(extendstr));
		}
		talk_event_st4_1_arrived = true;
	}else if(arist_using_protector != &all_protectors[1]){ //���߂Ăł͂Ȃ��A�������e�ł͂Ȃ���
		exstrcpy(now_text,talk_st4_1_1,eslengthof(talk_st4_1_1));
		string_march(now_text,2,2,eslengthof(talk_st4_1_1));
		if(instory_yesno(2 + eslengthof(talk_st4_1_1) + 1)){
			arist_using_protector = &all_protectors[1];
			exstrcpy(now_text,talk_st4_1_2,eslengthof(talk_st4_1_2));
			string_march(now_text,2,2 + eslengthof(talk_st4_1) + 3,sizeof(talk_st4_1_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st4_1_3,eslengthof(talk_st4_1_3));
			string_march(now_text,2,2 + eslengthof(talk_st4_1) + 3,sizeof(talk_st4_1_3)/sizeof(extendstr));
		}
	}else{
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		exstrcpy(now_text, talk_st4_1_2,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(talk_st4_1_2));
	}
}


/* �X�e�[�W4 ���}�b�v�E�̕��� */
bool talk_event_st4_2_arrived = false;
void talk_event_st4_2(){
	if(talk_event_st4_2_arrived){
		talk_event_st1_1();
	}else{
		flame_flush();
		naoki_find_potion();
		talk_event_st4_2_arrived = true;
	}
}

/* �X�e�[�W4 �����}�b�v���̕��� */
bool battle_event_st4_3_arrived = false;
void talk_event_st4_3(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,talk_st4_3,eslengthof(talk_st4_3));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(talk_st4_3));
}

/* �X�e�[�W4 �E�}�b�v���̕��� */
bool battle_event_st4_5_arrived = false;
void talk_event_st4_5(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,talk_st4_5,eslengthof(talk_st4_5));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(talk_st4_5));
}

/* �X�e�[�W2 �E�̕��� */
void talk_event_st4_6(){
	flame_flush();
	exstrcpy(now_text,talk_st4_6,eslengthof(talk_st4_6));
	string_march(now_text,2,2,eslengthof(talk_st4_6));
}

/* �X�e�[�W4 �{�X��O */
void before_battle_st4(){
	flame_flush();
	exstrcpy(now_text,beforebattle_stage4, eslengthof(beforebattle_stage4));
	string_march(now_text,2,2,eslengthof(beforebattle_stage4));
}

/* �X�e�[�W4 �{�X��� */
void after_battle_st4(){
	flame_flush();
	exstrcpy(now_text,afterbattle_stage4_1, eslengthof(afterbattle_stage4_1));
	string_march(now_text,2,2,eslengthof(afterbattle_stage4_1));
	flame_clean();
	exstrcpy(now_text,afterbattle_stage4_2, eslengthof(afterbattle_stage4_2));
	string_march(now_text,2,2,eslengthof(afterbattle_stage4_2));
	flame_clean();
	exstrcpy(now_text,afterbattle_stage4_3, eslengthof(afterbattle_stage4_3));
	string_march(now_text,2,2,eslengthof(afterbattle_stage4_3));
	flame_clean();
}

/* �X�e�[�W5 �{�X��� */
void after_battle_st5(){
	flame_flush();
	exstrcpy(now_text,afterbattle_stage5, eslengthof(afterbattle_stage5));
	string_march(now_text,2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,eslengthof(afterbattle_stage5));
	flame_clean();
}

