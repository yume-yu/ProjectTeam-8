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

