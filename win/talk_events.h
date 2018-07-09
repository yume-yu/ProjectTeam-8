/**
 * @file talk_event.h
 * @brief �e��b�C�x���g���ƂɌĂяo����鏈�����܂Ƃ߂��w�b�_
 * @author yume_yu
 * @date 
 */


#ifdef STORYTEXT_H
#define TALK_EVENT_H	//�d���ǂݍ��݉���̂��߂̒�`

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
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(event_text)/sizeof(extendstr));
	if(get_potion()){
	}else{
		exstrcpy(now_text,error_text,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3,sizeof(error_text)/sizeof(extendstr));
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
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(event_text)/sizeof(extendstr));
	if(get_potion()){
	}else{
		exstrcpy(now_text,error_text,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3,sizeof(error_text)/sizeof(extendstr));
	}
}

int instory_yesno(int y){
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
	exstrcpy(now_text,lirel_said,sizeof(lirel_said)/sizeof(extendstr));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(lirel_said)/sizeof(extendstr));
}

/* �X�e�[�W1 �N���֎~ */
void noentry_st1(){
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,lirel_stop,sizeof(lirel_stop)/sizeof(extendstr));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(lirel_said)/sizeof(extendstr));
}

/* �X�e�[�W1 �^�񒆂̕��� */
void talk_event_st1_1(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	extendstr error_text[] = {
		{"���ʂ��̊k����  ",0,0},
	};
	exstrcpy(now_text,error_text,1);
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(error_text)/sizeof(extendstr));
}

/* �X�e�[�W1 ���̕��� */
int talk_event_st1_0_arrived = 0;
void talk_event_st1_0(){
	if(talk_event_st1_0_arrived){
		talk_event_st1_1();
	}else{
		flame_flush();
		lirel_find_potion();
		talk_event_st1_0_arrived = 1;
	}
}

/* �X�e�[�W1 �{�X��O */
void before_battle_st1(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,beforebattle_stage1, lengthof(beforebattle_stage1,extendstr));
	string_march(now_text,BATTLE_MODE_COMMAND_POS - 2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,lengthof(beforebattle_stage1,extendstr));
}

/* �X�e�[�W1 �{�X��� */
void after_battle_st1(){
	flame_flush();
	//make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,afterbattle_stage1, sizeof(afterbattle_stage1)/sizeof(extendstr));
	string_march(now_text,2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(afterbattle_stage1)/sizeof(extendstr));
	flame_clean();
}

/* �X�e�[�W2 �E�̕��� */
int talk_event_st2_0_arrived = 0;
int talk_event_st2_0(){
	flame_flush();
	if(!talk_event_st2_0_arrived){
		exstrcpy(now_text,talk_st2_0_1,sizeof(talk_st2_0_1)/sizeof(extendstr));
		string_march(now_text,2,2,sizeof(talk_st2_0_1)/sizeof(extendstr));
		flame_clean();
		exstrcpy(now_text,talk_st2_0_2,sizeof(talk_st2_0_2)/sizeof(extendstr));
		string_march(now_text,2,2,sizeof(talk_st2_0_2)/sizeof(extendstr));
		talk_event_st2_0_arrived = 1;
	}else{
		extendstr error_text[] = {
			{"�����ɂ͂Ȃɂ��Ȃ���  ",0,0},
		};
		exstrcpy(now_text,error_text,1);
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(error_text)/sizeof(extendstr));
	}
}

int talk_event_st2_1_arrived = 0;
int talk_event_st2_1(){
	flame_flush();
	extendstr error_text[] = {
		{"�����ɂ͂Ȃɂ��Ȃ���  ",0,0},
	};
	exstrcpy(now_text,error_text,1);
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(error_text)/sizeof(extendstr));
}

/* �X�e�[�W2 �{�X��O */
void before_battle_st2(){
	flame_flush();
	exstrcpy(now_text,beforebattle_stage2, lengthof(beforebattle_stage2,extendstr));
	string_march(now_text,2,2,lengthof(beforebattle_stage2,extendstr));
}

/* �X�e�[�W2 �{�X��� */
void after_battle_st2(){
	flame_flush();
	//make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,afterbattle_stage2, sizeof(afterbattle_stage2)/sizeof(extendstr));
	string_march(now_text,2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT - 1,sizeof(afterbattle_stage2)/sizeof(extendstr));
	flame_clean();
}

/* �X�e�[�W3 �E�}�b�v����̕��� */
int talk_event_st3_0(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,talk_st3_0,sizeof(talk_st3_0)/sizeof(extendstr));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(talk_st3_0)/sizeof(extendstr));
}

/* �X�e�[�W3 �E�}�b�v���̕��� */
int talk_event_st3_1_arrived = 0;
int talk_event_st3_1(){
	flame_flush();
	if(!talk_event_st3_1_arrived){ //���߂ė����Ƃ����ǂ���
		exstrcpy(now_text,talk_st3_1,sizeof(talk_st3_1)/sizeof(extendstr));
		string_march(now_text,2,2,sizeof(talk_st3_1)/sizeof(extendstr));
		if(instory_yesno(2 + sizeof(talk_st3_1)/sizeof(extendstr) + 1)){
			using_weapon = &all_weapons[1];
			exstrcpy(now_text,talk_st3_1_2,sizeof(talk_st3_1_2)/sizeof(extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_1)/sizeof(extendstr) + 3,sizeof(talk_st3_1_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st3_1_3,sizeof(talk_st3_1_3)/sizeof(extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_1)/sizeof(extendstr) + 3,sizeof(talk_st3_1_3)/sizeof(extendstr));
		}
		talk_event_st3_1_arrived = 1;
	}else if(using_weapon != &all_weapons[1]){ //���߂Ăł͂Ȃ��A�������e�ł͂Ȃ���
		exstrcpy(now_text,talk_st3_1_1,sizeof(talk_st3_1_1)/sizeof(extendstr));
		string_march(now_text,2,2,sizeof(talk_st3_1_1)/sizeof(extendstr));
		if(instory_yesno(2 + sizeof(talk_st3_1_1)/sizeof(extendstr) + 1)){
			using_weapon = &all_weapons[1];
			exstrcpy(now_text,talk_st3_1_2,sizeof(talk_st3_1_2)/sizeof(extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_1)/sizeof(extendstr) + 3,sizeof(talk_st3_1_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st3_1_3,sizeof(talk_st3_1_3)/sizeof(extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_1)/sizeof(extendstr) + 3,sizeof(talk_st3_1_3)/sizeof(extendstr));
		}
	}else{
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		exstrcpy(now_text, talk_st3_1_2,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(talk_st3_1_2)/sizeof(extendstr));
	}
}

/* �X�e�[�W3 �E�}�b�v�E��̕��� */
int talk_event_st3_2_arrived = 0;
void talk_event_st3_2(){
	flame_flush();
	if(!talk_event_st3_2_arrived){ //���߂ė����Ƃ����ǂ���
		exstrcpy(now_text,talk_st3_2,sizeof(talk_st3_2)/sizeof(extendstr));
		string_march(now_text,2,2,sizeof(talk_st3_2)/sizeof(extendstr));
		if(instory_yesno(2 + sizeof(talk_st3_2)/sizeof(extendstr) + 1)){
			using_protector = &all_protectors[2];
			exstrcpy(now_text,talk_st3_2_2,sizeof(talk_st3_2_2)/sizeof(extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_2)/sizeof(extendstr) + 3,sizeof(talk_st3_2_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st3_2_3,sizeof(talk_st3_2_3)/sizeof(extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_2)/sizeof(extendstr) + 3,sizeof(talk_st3_2_3)/sizeof(extendstr));
		}
		talk_event_st3_2_arrived = 1;
	}else if(using_protector != &all_protectors[2]){ //���߂Ăł͂Ȃ��A�������h�앞�ł͂Ȃ���
		exstrcpy(now_text,talk_st3_2_1,sizeof(talk_st3_2_1)/sizeof(extendstr));
		string_march(now_text,2,2,sizeof(talk_st3_2_1)/sizeof(extendstr));
		if(instory_yesno(2 + sizeof(talk_st3_2_1)/sizeof(extendstr) + 1)){
			using_protector = &all_protectors[2];
			exstrcpy(now_text,talk_st3_2_2,sizeof(talk_st3_2_2)/sizeof(extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_2)/sizeof(extendstr) + 3,sizeof(talk_st3_2_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st3_2_3,sizeof(talk_st3_2_3)/sizeof(extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_2)/sizeof(extendstr) + 3,sizeof(talk_st3_2_3)/sizeof(extendstr));
		}
	}else{
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		exstrcpy(now_text, talk_st3_2_2,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(talk_st3_2_2)/sizeof(extendstr));
	}
}

/* �X�e�[�W3 �����}�b�v���̕��� */
int talk_event_st3_3_arrived = 0;
int talk_event_st3_3(){
	flame_flush();
	if(!talk_event_st3_3_arrived){ //���߂ė����Ƃ����ǂ���
		exstrcpy(now_text,talk_st3_3,sizeof(talk_st3_3)/sizeof(extendstr));
		string_march(now_text,2,2,sizeof(talk_st3_3)/sizeof(extendstr));
		if(instory_yesno(2 + sizeof(talk_st3_3)/sizeof(extendstr) + 1)){
			using_weapon = &all_weapons[2];
			exstrcpy(now_text,talk_st3_3_2,sizeof(talk_st3_3_2)/sizeof(extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_3)/sizeof(extendstr) + 3,sizeof(talk_st3_3_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st3_3_3,sizeof(talk_st3_3_3)/sizeof(extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_3)/sizeof(extendstr) + 3,sizeof(talk_st3_3_3)/sizeof(extendstr));
		}
		exstrcpy(now_text,talk_st3_3_0,sizeof(talk_st3_3_0)/sizeof(extendstr));
		string_march(now_text,2,2 + sizeof(talk_st3_3)/sizeof(extendstr) + 4,sizeof(talk_st3_3_0)/sizeof(extendstr));
		extendstr error_text[] = {
			{"�|�[�V�����͂���ȏ㎝�ĂȂ��̂ŕԂ�����  ",0,0},
		};
		if(get_potion()){
		}else{
			exstrcpy(now_text,error_text,1);
			string_march(now_text,2,2 + sizeof(talk_st3_3)/sizeof(extendstr) + 7,sizeof(error_text)/sizeof(extendstr));
		}
		talk_event_st3_3_arrived = 1;
	}else if(using_weapon != &all_weapons[2]){ //���߂Ăł͂Ȃ��A�������e�ł͂Ȃ���
		exstrcpy(now_text,talk_st3_3_1,sizeof(talk_st3_3_1)/sizeof(extendstr));
		string_march(now_text,2,2,sizeof(talk_st3_3_1)/sizeof(extendstr));
		if(instory_yesno(2 + sizeof(talk_st3_3_1)/sizeof(extendstr) + 1)){
			using_weapon = &all_weapons[2];
			exstrcpy(now_text,talk_st3_3_2,sizeof(talk_st3_3_2)/sizeof(extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_3)/sizeof(extendstr) + 3,sizeof(talk_st3_3_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st3_3_3,sizeof(talk_st3_3_3)/sizeof(extendstr));
			string_march(now_text,2,2 + sizeof(talk_st3_3)/sizeof(extendstr) + 3,sizeof(talk_st3_3_3)/sizeof(extendstr));
		}
	}else{
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		exstrcpy(now_text, talk_st3_3_2,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(talk_st3_3_2)/sizeof(extendstr));
	}
}

/* �X�e�[�W3 �����}�b�v���̕��� */
int talk_event_st3_5(){
	flame_flush();
	exstrcpy(now_text,talk_st3_5_1,sizeof(talk_st3_5_1)/sizeof(extendstr));
	string_march(now_text,2,2,sizeof(talk_st3_5_1)/sizeof(extendstr));
	flame_clean();
	exstrcpy(now_text,talk_st3_5_2,sizeof(talk_st3_5_2)/sizeof(extendstr));
	string_march(now_text,2,2,sizeof(talk_st3_5_2)/sizeof(extendstr));
	flame_clean();
	exstrcpy(now_text,talk_st3_5_3,sizeof(talk_st3_5_3)/sizeof(extendstr));
	string_march(now_text,2,2,sizeof(talk_st3_5_3)/sizeof(extendstr));
	have_nasu = 1;
}

/* �X�e�[�W3 �E�}�b�v���̕��� */
int talk_event_st3_6(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,talk_st3_6,sizeof(talk_st3_6)/sizeof(extendstr));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(talk_st3_6)/sizeof(extendstr));
}

/* �X�e�[�W3 �E�}�b�v�E�̕��� */
int battle_event_st3_7_arrived = 0;

/* �X�e�[�W3 �{�X��O */
void before_battle_st3(){
	flame_flush();
	exstrcpy(now_text,beforebattle_stage3, lengthof(beforebattle_stage3,extendstr));
	string_march(now_text,2,2,lengthof(beforebattle_stage3,extendstr));
}

/* �X�e�[�W3 �{�X��� */
void after_battle_st3(){
	flame_flush();
	exstrcpy(now_text,afterbattle_stage3, sizeof(afterbattle_stage3)/sizeof(extendstr));
	string_march(now_text,2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(afterbattle_stage3)/sizeof(extendstr));
	flame_clean();
}

/* �X�e�[�W4 �E�}�b�v�����̕��� */
int talk_event_st4_0_arrived = 0;
int talk_event_st4_0(){
	flame_flush();
	if(!talk_event_st4_0_arrived){ //���߂ė����Ƃ����ǂ���
		exstrcpy(now_text,talk_st4_0,sizeof(talk_st4_0)/sizeof(extendstr));
		string_march(now_text,2,2,sizeof(talk_st4_0)/sizeof(extendstr));
		if(instory_yesno(2 + sizeof(talk_st4_0)/sizeof(extendstr) + 1)){
			arist_using_weapon = &all_weapons4back[1];
			exstrcpy(now_text,talk_st4_0_2,sizeof(talk_st4_0_2)/sizeof(extendstr));
			string_march(now_text,2,2 + sizeof(talk_st4_0)/sizeof(extendstr) + 3,sizeof(talk_st4_0_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st4_0_3,sizeof(talk_st4_0_3)/sizeof(extendstr));
			string_march(now_text,2,2 + sizeof(talk_st4_0)/sizeof(extendstr) + 3,sizeof(talk_st4_0_3)/sizeof(extendstr));
		}
		talk_event_st4_0_arrived = 1;
	}else if(arist_using_weapon != &all_weapons4back[1]){ //���߂Ăł͂Ȃ��A�������e�ł͂Ȃ���
		exstrcpy(now_text,talk_st4_0_1,sizeof(talk_st4_0_1)/sizeof(extendstr));
		string_march(now_text,2,2,sizeof(talk_st4_0_1)/sizeof(extendstr));
		if(instory_yesno(2 + sizeof(talk_st4_0_1)/sizeof(extendstr) + 1)){
			arist_using_weapon = &all_weapons4back[1];
			exstrcpy(now_text,talk_st4_0_2,sizeof(talk_st4_0_2)/sizeof(extendstr));
			string_march(now_text,2,2 + sizeof(talk_st4_0)/sizeof(extendstr) + 3,sizeof(talk_st4_0_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st4_0_3,sizeof(talk_st4_0_3)/sizeof(extendstr));
			string_march(now_text,2,2 + sizeof(talk_st4_0)/sizeof(extendstr) + 3,sizeof(talk_st4_0_3)/sizeof(extendstr));
		}
	}else{
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		exstrcpy(now_text, talk_st4_0_2,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(talk_st4_0_2)/sizeof(extendstr));
	}
}

/* �X�e�[�W4 �E�}�b�v���̕��� */
int talk_event_st4_1_arrived = 0;
int talk_event_st4_1(){
	flame_flush();
	if(!talk_event_st4_1_arrived){ //���߂ė����Ƃ����ǂ���
		exstrcpy(now_text,talk_st4_1,sizeof(talk_st4_1)/sizeof(extendstr));
		string_march(now_text,2,2,sizeof(talk_st4_1)/sizeof(extendstr));
		if(instory_yesno(2 + sizeof(talk_st4_1)/sizeof(extendstr) + 1)){
			arist_using_protector = &all_protectors[1];
			exstrcpy(now_text,talk_st4_1_2,sizeof(talk_st4_1_2)/sizeof(extendstr));
			string_march(now_text,2,2 + sizeof(talk_st4_1)/sizeof(extendstr) + 3,sizeof(talk_st4_1_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st4_1_3,sizeof(talk_st4_1_3)/sizeof(extendstr));
			string_march(now_text,2,2 + sizeof(talk_st4_1)/sizeof(extendstr) + 3,sizeof(talk_st4_1_3)/sizeof(extendstr));
		}
		talk_event_st4_1_arrived = 1;
	}else if(arist_using_protector != &all_protectors[1]){ //���߂Ăł͂Ȃ��A�������e�ł͂Ȃ���
		exstrcpy(now_text,talk_st4_1_1,sizeof(talk_st4_1_1)/sizeof(extendstr));
		string_march(now_text,2,2,sizeof(talk_st4_1_1)/sizeof(extendstr));
		if(instory_yesno(2 + sizeof(talk_st4_1_1)/sizeof(extendstr) + 1)){
			arist_using_protector = &all_protectors[1];
			exstrcpy(now_text,talk_st4_1_2,sizeof(talk_st4_1_2)/sizeof(extendstr));
			string_march(now_text,2,2 + sizeof(talk_st4_1)/sizeof(extendstr) + 3,sizeof(talk_st4_1_2)/sizeof(extendstr));
		}else{
			exstrcpy(now_text,talk_st4_1_3,sizeof(talk_st4_1_3)/sizeof(extendstr));
			string_march(now_text,2,2 + sizeof(talk_st4_1)/sizeof(extendstr) + 3,sizeof(talk_st4_1_3)/sizeof(extendstr));
		}
	}else{
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		exstrcpy(now_text, talk_st4_1_2,1);
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(talk_st4_1_2)/sizeof(extendstr));
	}
}


/* �X�e�[�W4 ���}�b�v�E�̕��� */
int talk_event_st4_2_arrived = 0;
void talk_event_st4_2(){
	if(talk_event_st4_2_arrived){
		talk_event_st1_1();
	}else{
		flame_flush();
		naoki_find_potion();
		talk_event_st4_2_arrived = 1;
	}
}

/* �X�e�[�W4 �����}�b�v���̕��� */
int battle_event_st4_3_arrived = 0;
int talk_event_st4_3(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,talk_st4_3,sizeof(talk_st4_3)/sizeof(extendstr));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(talk_st4_3)/sizeof(extendstr));
}

/* �X�e�[�W4 �E�}�b�v���̕��� */
int battle_event_st4_5_arrived = 0;
int talk_event_st4_5(){
	flame_flush();
	make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
	exstrcpy(now_text,talk_st4_5,sizeof(talk_st4_5)/sizeof(extendstr));
	string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(talk_st4_5)/sizeof(extendstr));
}

/* �X�e�[�W2 �E�̕��� */
int talk_event_st4_6(){
	flame_flush();
	exstrcpy(now_text,talk_st4_6,sizeof(talk_st4_6)/sizeof(extendstr));
	string_march(now_text,2,2,sizeof(talk_st4_6)/sizeof(extendstr));
}

/* �X�e�[�W4 �{�X��O */
void before_battle_st4(){
	flame_flush();
	exstrcpy(now_text,beforebattle_stage4, lengthof(beforebattle_stage4,extendstr));
	string_march(now_text,2,2,lengthof(beforebattle_stage4,extendstr));
}

/* �X�e�[�W4 �{�X��� */
void after_battle_st4(){
	flame_flush();
	exstrcpy(now_text,afterbattle_stage4_1, sizeof(afterbattle_stage4_1)/sizeof(extendstr));
	string_march(now_text,2,2,sizeof(afterbattle_stage4_1)/sizeof(extendstr));
	flame_clean();
	exstrcpy(now_text,afterbattle_stage4_2, sizeof(afterbattle_stage4_2)/sizeof(extendstr));
	string_march(now_text,2,2,sizeof(afterbattle_stage4_2)/sizeof(extendstr));
	flame_clean();
	exstrcpy(now_text,afterbattle_stage4_3, sizeof(afterbattle_stage4_3)/sizeof(extendstr));
	string_march(now_text,2,2,sizeof(afterbattle_stage4_3)/sizeof(extendstr));
	flame_clean();
}

/* �X�e�[�W5 �{�X��� */
void after_battle_st5(){
	flame_flush();
	exstrcpy(now_text,afterbattle_stage5, sizeof(afterbattle_stage5)/sizeof(extendstr));
	string_march(now_text,2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(afterbattle_stage5)/sizeof(extendstr));
	flame_clean();
}

#endif

