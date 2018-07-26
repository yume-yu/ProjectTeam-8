/**
 * @file battle_func.c
 * @brief 戦闘に関連する関数を定義するファイル
 * @author yume_yu
 * @date 2018/07/14
 */
#include "thebeautifulsky.h"

//�퓬���[�h�̎��ɃR�}���h�����\������֐�
void print_bt_commands(){
	print_line("��������",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
	print_line("�Ƃ�����",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
	print_line("���΂�",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3);
	print_line("�ǂ���",BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 4);
	fflush(stdout);
}

//�G��HP�Q�[�W��`�悷��֐�
void print_health_bar(character *target[],int amount){
	double health_par = 0;
	for(int i = 0; i < amount; i++){
		make_flame(25,3,2,2 + 3 * i);
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
void print_bt_status(character *front,character *back){
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
int battle(character *front,character *back,character *enemies[3], int enemy_amount){
	mykbhit();																	//�ߏ���̓N�b�V����
	int finish_flag = 0;												//�퓬�I���̃t���O
	int protect_flag = 0;												//���΂��s���̃t���O
	int use_nasu = 0;														//�i�X�g�p�t���O
	int damage = 0;															//�v�Z��̃_���[�W���L������ϐ�
	int target_label = 0;												//�U���Ώۂ𔻒f���邽�߂̕ϐ�
	int turn_count = 1;													//����s���̂��ߐ퓬�J�n����̃^�[���𐔂���ϐ�
	int sp_count = 0;														//����s���̍s���s�\�^�[���𐔂���ϐ�
	int enemies_dead_check = 0;									//�G���S�ł������ǂ����`�F�b�N���鎞�Ɏg���ϐ�
	int player_can_act = 1;											//�v���C���[���s���\���̃t���O
	int used_flare = 0;													//�X�e�[�W5�ł̖�������s���̎g�p��t���O
	int enemy_amount_for_bar = enemy_amount;		//HP�Q�[�W�`��̂��߁A�{���̓G�̐����L������ϐ�
	char battle_text[100] = "\0";
	character *for_bar[enemy_amount];		//HP�Q�[�W�`��̂��߁A�{���̓G�̃A�h���X���L������ϐ�
	for(int i = 0;i < enemy_amount;i++){
		for_bar[i] = enemies[i];
	}
	arrow_pos battle_menu_arrow[] = {
		{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1},
		{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2},
		{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3},
		{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 4}
	};
	arrow_pos battle_item_menu_arrow[2][4] = {
		{
			{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1},
			{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2},
			{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3},
			{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 4},
		},
		{
			{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,1},
			{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2,1},
			{BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3,1},
			{2 * BATTLE_MODE_COMMAND_POS + 10 - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 4},
		}
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
					if(use_nasu){
						damage *= 2;
						use_nasu = 0;
					}
					mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
					printf("%s ��",enemies[target_label]->name);
					mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
					printf("                %3d �_���[�W!��",damage);
					change_hp(enemies[target_label],damage);
					if(using_weapon->is_gun && !strcmp(front->name,FRONT2_NAME)){
						damage = front->min_atk + rand() % (front->max_atk - front->min_atk - 1) + using_weapon->atk;
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 3);
						printf("%s ��",enemies[target_label]->name);
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 4);
						printf("                %3d �_���[�W!��",damage);
						change_hp(enemies[target_label],damage);
					}
					print_health_bar(for_bar,enemy_amount_for_bar);
					wait_anyinput();
					if(enemies[target_label]->hp <= 0){
						sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
						printf("%s ��",enemies[target_label]->name);
						mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
						printf("                      �|�ꂽ!��");
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
									mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
									printf("%s �� %3d �_���[�W!��",enemies[target_label]->name,damage);
									print_health_bar(for_bar,enemy_amount_for_bar);
									wait_anyinput();
									/*�G�_���[�W���������܂�*/
									/*�G���S���肱������*/
									if(enemies[i]->hp <= 0){
										sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
										mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
										printf("%s ��",enemies[target_label]->name);
										mvcur(BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 2);
										printf("                      �|�ꂽ!��");
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
					if(potion_amount + have_nasu <= 3){
						for(int i = 0; i <= potion_amount + have_nasu; i++){
							mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1 + i);
							if(i < potion_amount){
								printf("�|�[�V����");
							}else if(i < potion_amount + have_nasu){
								printf("���ѥ��ݹ��");
							}else{
								printf("�߂�");
							}
							fflush(stdout);
						}
						target_label = select_from_list(battle_menu_arrow,potion_amount + have_nasu + 1);
						if(target_label < potion_amount){
							sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
							change_hp(front,-1 * front->max_hp);
							change_hp(&arist,-1 * arist.max_hp);
							print_bt_status(front,back);
							print_line("�|�[�V�������g����!�� ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
							potion_amount--;
							wait_anyinput();
						}else if(target_label < potion_amount + have_nasu){
							sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
							print_line("�͂��݂Ȃ���!�� ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
							have_nasu = 0;
							use_nasu = 1;
							wait_anyinput();
						}else{
							sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
							continue;
						}
					}else if(potion_amount + have_nasu >= 4){
						for(int i = 0; i <= potion_amount + have_nasu; i++){
							mvcur(BATTLE_MODE_COMMAND_POS,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1 + i);
							if(i < potion_amount){
								printf("�|�[�V����");
							}else if(i < potion_amount + have_nasu){
								printf("���ѥ��ݹ��");
							}
							fflush(stdout);
						}
						print_line("�߂�",2 * BATTLE_MODE_COMMAND_POS + 10,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + potion_amount + have_nasu);

						target_label = select_from_2dlist(2,4,battle_item_menu_arrow);
						switch(target_label){
							case 0:	//�|�[�V����
							case 2:
							case 4:
								sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								change_hp(front,-1 * front->max_hp);
								change_hp(&arist,-1 * arist.max_hp);
								print_bt_status(front,back);
								print_line("�|�[�V�������g����!�� ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								potion_amount--;
								wait_anyinput();
								break;
							case 6:	//Nasu
								sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								print_line("�͂��݂Ȃ���!�� ",BATTLE_MODE_COMMAND_POS - 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								have_nasu = 0;
								use_nasu = 1;
								wait_anyinput();
								break;
							case 7:	//�߂�
								sub_flame_clean(BATTLE_MODE_STATUS_FLAME_SPLIT_X,BATTLE_MODE_STATUS_FLAME_HEIGHT - 2,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1);
								continue;
								break;
							default:
								break;

						}
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
				}else if(!strcmp(enemies[i]->name,ST5_BOSS_NAME) && turn_count != 0 && turn_count % 4 == 0){
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
						"�t�@�[���� ",
						"       �e�g���O���}�g����������!�� "
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

