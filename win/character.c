/**
 * @file character.c
 * @brief �L�����N�^�[�֘A�̕ϐ���֐����`����t�@�C��
 * @author yume_yu
 * @date 2018/07/12
 */

#include "thebeautifulsky.h"

//�K�v�L�����N�^-�̒�`
character naoki;
character lirel;
character arist;
character robo;
character boss1;
character boss2;
character dummy;
character *front;
character *back;
character *(enemies)[3];
int enemy_amount = 0;

/**
 * �L�����N�^�[�̃X�e�[�^�X�ݒ������֐�
 * name[10] �L�����N�^�[�̖��O
 * tmpch    �X�e�[�^�X��ݒ肷��L�����N�^�[�\���̂̃A�h���X
 * hp       �ݒ肷��hp
 * min_atk  �^�_���[�W�̉���
 * max_atk  �^�_���[�W�̏��
 */
void set_ch_stat(char name[10], character *tmpch, int hp, int max_hp,int min_atk, int max_atk){
	tmpch->name = name;
	tmpch->hp = hp;
	tmpch->max_hp = max_hp;
	tmpch->max_atk = max_atk;
	tmpch->min_atk = min_atk;
}

/**
 * �L�����N�^�[��HP��ϓ�������֐�
 * tmpch    hp���ϓ�����L�����N�^�[�\���̂̃A�h���X
 * damage   �_���[�W�� ���Ȃ猸�Z/���Ȃ���Z����� ex.damage��-20 �� 20��
 */
void change_hp(character *tmpch, int damage){
	tmpch->hp -= damage;
	if(tmpch->hp < 0){
		tmpch->hp = 0;
	}else if(tmpch->hp > tmpch->max_hp){
		tmpch->hp = tmpch->max_hp;
	}
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


