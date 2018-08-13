/**
 * @file weapons_items.c
 * @brief �����֘A�̕ϐ���֐����`����t�@�C��
 * @author yume_yu
 * @date 2018/07/12
 */

#include "thebeautifulsky.h"

//�O�q�����̒�`
weapon all_weapons[7] = {
	{"No weapon",0,0},
	{"HandGun",15,1},
	{"Knife",5,0},
};

//��q�����̒�`
weapon all_weapons4back[7] = {
	{"No weapon",0,0},
	{"Bow",10,1}
};

//�h��̒�`
protector all_protectors[7] = {
	{"No protector",0},
	{"Shield",40},
	{"Protective Suit",55}
};

//�����g�̒�`
weapon *using_weapon;
protector *using_protector;
weapon *arist_using_weapon;
protector *arist_using_protector;
int potion_amount = 0;
int have_nasu = 0;

/**
 * ����̃X�e�[�^�X�X�V������֐�
 * tmpwp    �X�e�[�^�X��ݒ肷�镐��\���̂̃A�h���X
 * atk      ����̍U����
 * is_gun  	�e���ǂ����̃t���O
 */
void set_weapon_stat(weapon *tmpwp, int atk, bool is_gun){
	tmpwp->atk = atk;
	tmpwp->is_gun = is_gun;
}

/**
 * �h��̃X�e�[�^�X�X�V������֐�
 * tmppr    �X�e�[�^�X��ݒ肷�镐��\���̂̃A�h���X
 * def      ����̍U����
 */
void set_protector_stat(protector *tmppr, int def){
	tmppr->def = def;
}

/**
 * @fn
 * �|�[�V�����̎擾
 * @brief �|�[�V�����̎擾�����s������ꂽ����Ԃ�
 * @return �|�[�V����������ꂽ��
 * @detail �|�[�V�����̏��������m�F���A3�����Ȃ�|�[�V�������擾����1��Ԃ��B��������3�𒴂��Ă�����0��Ԃ�
 */
bool get_potion(){
	if(potion_amount < 3){
		potion_amount++;
		return true;
	}else{
		return false;
	}
}

