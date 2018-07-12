/**
 * @file weapons_items.c
 * @brief 装備関連の変数や関数を定義するファイル
 * @author yume_yu
 * @date 2018/07/12
 */

#include "thebeautifulsky.h"

//前衛装備の定義
weapon all_weapons[7] = {
	{"No weapon",0,0},
	{"HandGun",15,1},
	{"Knife",5,0},
};

//後衛装備の定義
weapon all_weapons4back[7] = {
	{"No weapon",0,0},
	{"Bow",10,1}
};

//防具の定義
protector all_protectors[7] = {
	{"No protector",0},
	{"Shield",40},
	{"Protective Suit",55}
};

//装備枠の定義
weapon *using_weapon;
protector *using_protector;
weapon *arist_using_weapon;
protector *arist_using_protector;
int potion_amount = 0;
int have_nasu = 0;

/**
 * 武器のステータス更新をする関数
 * tmpwp    ステータスを設定する武器構造体のアドレス
 * atk      武器の攻撃力
 * is_gun  	銃かどうかのフラグ
 */
void set_weapon_stat(weapon *tmpwp, int atk, bool is_gun){
	tmpwp->atk = atk;
	tmpwp->is_gun = is_gun;
}

/**
 * 防具のステータス更新をする関数
 * tmppr    ステータスを設定する武器構造体のアドレス
 * def      武器の攻撃力
 */
void set_protector_stat(protector *tmppr, int def){
	tmppr->def = def;
}

/**
 * @fn
 * ポーションの取得
 * @brief ポーションの取得を実行し得られたかを返す
 * @return ポーションが得られたか
 * @detail ポーションの所持数を確認し、3未満ならポーションを取得して1を返す。所持数が3を超えていたら0を返す
 */
bool get_potion(){
	if(potion_amount < 3){
		potion_amount++;
		return true;
	}else{
		return false;
	}
}

