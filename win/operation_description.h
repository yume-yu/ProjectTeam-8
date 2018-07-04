/**
 * ��������̊֐�
 */

/* �g���ւ̕��\�� */
void print_explain_in(struct extendstr explain[],int size){
	exstrcpy(now_text,explain,size);
	string_march(
			now_text,
			BATTLE_MODE_STATUS_FLAME_X + 1,
			HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,
			size
			);
	sub_flame_clean(
			BATTLE_MODE_STATUS_FLAME_SPLIT_X,
			BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,
			BATTLE_MODE_STATUS_FLAME_X + 1,
			HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1
			);
}

/* �g�O�ւ̕��\�� */
void print_explain_out(struct extendstr explain[],int size){
	exstrcpy(now_text,explain,size);
	string_march(now_text,8,8,size);
	sub_flame_clean(WIDTH - 2,5,2,8);
}

/* �퓬�̐��� */
void explain_battle(){
	struct extendstr first[] = {
		{"�`���[�g���A���퓬���s���܂��� ",0,0}
	};

	struct extendstr second[] = {
		{"�퓬�͑O�q�ƌ�q�̂Q�l ",0,1},
		{"�΃G�l�~�[�ōs���܂��� ",12,0}
	};

	struct extendstr third[] = {
		{"�v���C���[�����삷��̂� ",0,1},
		{"�O�q�݂̂ł��� ",20,0}
	};

	struct extendstr fourth[] = {
		{"��q�̍s���� ",0,1},
		{"�����_���Ɍ��肳��܂��� ",10,0}
	};

	struct extendstr fifth[] = {
		{"�s���̏��Ԃ͕K�� ",0,1},
		{"�O�q����q���G�l�~�[�ł��� ",9,0}
	};

	struct extendstr sixth[] = {
		{"�G�l�~�[��HP�͏㕔�� ",0,1},
		{"�p�[�e�B�[��HP�͉E�ɕ\\������܂��� ",0,0}
	};

	print_explain_in(first,sizeof(first)/sizeof(struct extendstr));
	print_explain_in(second,sizeof(second)/sizeof(struct extendstr));
	print_explain_in(third,sizeof(third)/sizeof(struct extendstr));
	print_explain_in(fourth,sizeof(fourth)/sizeof(struct extendstr));
	print_explain_in(fifth,sizeof(fifth)/sizeof(struct extendstr));
	print_explain_in(sixth,sizeof(sixth)/sizeof(struct extendstr));
}

/* �퓬�R�}���h�̐��� */
void explain_command(){
	struct extendstr first[] = {
		{"�Ō�ɐ퓬���̃R�}���h�ɂ��Đ������܂��� ",0,0}
	};

	struct extendstr second[] = {
		{"���������@�R�}���h��I�ԂƍU�����ł��܂� ",0,1},
		{"�U���̑O�ɂ͍U�����鑊���I���ł��܂��� ",0,0},
	};

	struct extendstr third[] = {
		{"�Ƃ�����@�R�}���h��I�ԂƓ���ȍU�����ł��܂� ",0,1},
		{"����U���������Ă��Ȃ��L�����N�^�[������̂� ",0,1},
		{"���ӂ��Ă��������� ",30,0},
	};

	struct extendstr fourth[] = {
		{"���΂��@�R�}���h��I�Ԃƌ�q�����΂����Ƃ��ł��܂� ",0,1},
		{"�g�p����Ƃ��ɂ͑O�q��HP�ɋC��t���܂��傤�� ",0,0},
	};

	struct extendstr fifth[] = {
		{"�ǂ����@�R�}���h��I�Ԃƃ|�[�V�������g�p�ł��܂� ",0,1},
		{"�|�[�V�����̌��ʂ̓p�[�e�B�[�̑S�񕜂ł��� ",0,0},
	};

	struct extendstr sixth[] = {
		{"�ł͎��ۂɐ���Ă݂܂��傤�� ",0,0},
	};
	
	print_explain_out(first,sizeof(first)/sizeof(struct extendstr));
	print_explain_out(second,sizeof(second)/sizeof(struct extendstr));
	print_explain_out(third,sizeof(third)/sizeof(struct extendstr));
	print_explain_out(fourth,sizeof(fourth)/sizeof(struct extendstr));
	print_explain_out(fifth,sizeof(fifth)/sizeof(struct extendstr));
	print_explain_out(sixth,sizeof(sixth)/sizeof(struct extendstr));
}
/* �`���[�g���A���퓬���[�h */
int demo_battle(struct character *front,struct character *back,struct character *enemies[3], int enemy_amount){
	int finish_flag = 0;																																	//�퓬�I���̃t���O
	int protect_flag = 0;																																	//���΂��s���̃t���O
	int damage = 0;																																				//�v�Z��̃_���[�W���L������ϐ�
	int target_label = 0;																																	//�U���Ώۂ𔻒f���邽�߂̕ϐ�
	int turn_count = 1;																																		//����s���̂��ߐ퓬�J�n����̃^�[���𐔂���ϐ�
	int sp_count = 0;																																			//����s���̍s���s�\�^�[���𐔂���ϐ�
	int enemies_dead_check = 0;																														//�G���S�ł������ǂ����`�F�b�N���鎞�Ɏg���ϐ�
	int player_can_act = 1;																																//�v���C���[���s���\���̃t���O
	int used_flare = 0;																																		//�X�e�[�W5�ł̖�������s���̎g�p��t���O
	int enemy_amount_for_bar = enemy_amount;																							//HP�Q�[�W�`��̂��߁A�{���̓G�̐����L������ϐ�
	struct character *for_bar[enemy_amount];																							//HP�Q�[�W�`��̂��߁A�{���̓G�̃A�h���X���L������ϐ�
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

	print_bt_status(front,back);																													//����HP�̕\��
	print_health_bar(for_bar,enemy_amount_for_bar);																				//�GHP�Q�[�W�̕\��
	mvcur(BATTLE_MODE_STATUS_FLAME_X + 2,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT - 1);		//�^�[�����\���p�J�[�\���ړ�
	printf("Turn %2d",turn_count);																												//�^�[�����\��
	
	explain_battle();

	print_bt_commands();																			//�v���C���[�̃R�}���h��\������
	explain_command();
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
					printf("�߂�");
					fflush(stdout);
					target_label = select_from_list(battle_menu_arrow,1);
					sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					continue;
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
			print_health_bar(for_bar,enemy_amount_for_bar);
			print_bt_status(front,back);
			if(front->hp <= 0 || (back->hp <= 0 && strcmp(back->name,"dummy"))){
				sub_flame_clean(
						BATTLE_MODE_STATUS_FLAME_SPLIT_X,
						BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,
						BATTLE_MODE_STATUS_FLAME_X + 1,
						HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1
						);
				print_line("�����Ă��܂���...��",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
				finish_flag = 1;
				return 0;
				wait_anyinput();
				continue;
			}
		}
		//�G�̍s���I���
		sub_flame_clean(
				BATTLE_MODE_STATUS_FLAME_SPLIT_X,
				BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,
				BATTLE_MODE_STATUS_FLAME_X + 1,
				HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1
				);
		turn_count++;
	}
	return 0;
}

/* ��������̖{�� */
int operation_description(){
	now_stage = ope_exp;
	flame_clean();
	struct extendstr first[] = {
		{"���̃Q�[���ł̑���͈ȉ��̃L�[�ōs���܂��B ",0,1},
		{"�@ ",0,1},
		{"Enter:����@�������� ",1,1},
		{"�i��������͑��̃L�[�ł��� ",3,1},
		{" Enter�̒�����or�A�ł͑z��O�̑I���̉\\������j ",10,1},
		{"�@ ",0,1},
		{"AWSD: �}�b�v��̈ړ��@�J�[�\\���ړ� ",1,1},
		{"�`�����@�v�����@�r�����@�c����  ",5,1},
		{"�@ ",0,1},
		{"Space:�}�b�v��Ń��j���[���J�� ",1,1},
	};
	struct arrow_pos yesno[] = {
		{(WIDTH - 16)/2 + 8,16,0,0},
		{(WIDTH - 16)/2 + 1,16,0,0},
	};

	struct extendstr second[] = {
		{"�}�b�v��ł̃L�����N�^�[�̈ʒu�́��ŕ\\����܂� ",0,1},
		{"���ɐi�ޏꍇ�̓L�����N�^�[���o���ֈړ������Ă���������  ",0,0},
	};

	struct extendstr after[] = {
		{"��������^�`���[�g���A���͈ȏ�ł��B ",0,1},
		{"�Q�[�����n�߂܂����H ",7,1},
		{" ",0,1},
		{"�Q�[�����n�߂� ",7,1},
		{"�^�C�g���ɂ��ǂ� ",7,1},
	};

	struct arrow_pos tobe[] = {
		{(WIDTH - 36)/2 + 6,11,0,0},
		{(WIDTH - 36)/2 + 6,12,0,0},
	};
	print_line("How to play game",(WIDTH - 16)/2,2);															//�^�C�g���e�L�X�g���o��
	exstrcpy(now_text,first,sizeof(first)/sizeof(struct extendstr));
	string_march(now_text,2,4,sizeof(first)/sizeof(struct extendstr));
	print_line("���ɐi�ޏꍇ�́u�͂��v��I��ł�������",(WIDTH - 38)/2,15);				//�m�F�̕��͂�\��
	print_line("�͂�   ������",(WIDTH - 16)/2 + 2,16);
	while(!select_from_hlist(yesno,2));																						//��͂���̓��͂��܂�
	sub_flame_clean(WIDTH - 2,2,2,15);																						//���ɐi�ޏꍇ�́`�̕��͂�����
	exstrcpy(now_text,second,sizeof(second)/sizeof(struct extendstr));						//���ɕ\�����镶�͂�now_text�ɗp��
	string_march(now_text,2,15,sizeof(second)/sizeof(struct extendstr));					//now_text��\��
	coorcpy(now_map_coor,map_coors[now_stage]);																		//�����p�}�b�v���W��now_map_coor�ɗp��
	start_pos.x = 1;																															//�}�b�v�ړ��J�n����X���W���Z�b�g
	start_pos.y = 0;																															//�}�b�v�ړ��J�n����Y���W���Z�b�g	
	print_lines(map_exp,10,17,8);																									//�����p�}�b�v��\��
	while(move_on_map(39, 6, now_map_coor,start_pos).x != 48){										//�}�b�v�ړ��J�n
		start_pos.x -= 8;
		start_pos.y -= 16;
	}
	set_ch_stat("�O�q",&lirel,FRONT1_HP,FRONT1_HP,FRONT1_MINATK,FRONT1_MAXATK);		//�O�q�X�e�[�^�X�Z�b�g
	set_ch_stat("��q",&arist,BACK_HP_ST1,BACK_HP_ST1,0,BACK_HEAL_ST1);						//��q�X�e�[�^�X�Z�b�g		
	front = &lirel;																																//�O�q�A�h���X�Z�b�g
	back = &arist;																																//��q�A�h���X�Z�b�g
	set_ch_stat("�f���G�l�~�[",&boss1,30,35,30,35);																//�G�X�e�[�^�X�Z�b�g
	enemies[0] = &boss1;																													//�G�A�h���X�Z�b�g	
	enemies[1] = &dummy;
	potion_amount = 1;
	enemy_amount = 1;																															//�G�̐���ݒ�
	demo_battle(front,back,enemies,enemy_amount);
	make_flame(39,7,(WIDTH - 36) / 2 - 2,7);
	exstrcpy(now_text,after,sizeof(after)/sizeof(struct extendstr));
	string_march(now_text,(WIDTH - 36) / 2,8,sizeof(after)/sizeof(struct extendstr));
	now_stage = stage1;
	return select_from_list(tobe,2);
}
