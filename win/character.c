/**
 * @file character.c
 * @brief キャラクター関連の変数や関数を定義するファイル
 * @author yume_yu
 * @date 2018/07/12
 */

#include "thebeautifulsky.h"

//必要キャラクタ-の定義
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
 * キャラクターのステータス設定をする関数
 * name[10] キャラクターの名前
 * tmpch    ステータスを設定するキャラクター構造体のアドレス
 * hp       設定するhp
 * min_atk  与ダメージの下限
 * max_atk  与ダメージの上限
 */
void set_ch_stat(char name[10], character *tmpch, int hp, int max_hp,int min_atk, int max_atk){
	tmpch->name = name;
	tmpch->hp = hp;
	tmpch->max_hp = max_hp;
	tmpch->max_atk = max_atk;
	tmpch->min_atk = min_atk;
}

/**
 * キャラクターのHPを変動させる関数
 * tmpch    hpが変動するキャラクター構造体のアドレス
 * damage   ダメージ量 正なら減算/負なら加算される ex.damageが-20 → 20回復
 */
void change_hp(character *tmpch, int damage){
	tmpch->hp -= damage;
	if(tmpch->hp < 0){
		tmpch->hp = 0;
	}else if(tmpch->hp > tmpch->max_hp){
		tmpch->hp = tmpch->max_hp;
	}
}

