/**
 * @file map_func.c
 * @brief マップ関連の変数や関数を定義するファイル
 * @author yume_yu
 * @date 2018/07/12
 */

#include "thebeautifulsky.h"

/**
 *	マップをコピーする関数
 */
void mapcpy(char *(to)[HEIGHT - 2],char *(from)[HEIGHT - 2]){
	for(int i = 0; i <  HEIGHT -2; i++){
		//strcpy(to[i],from[i]);
		to[i] = from[i];
	}
}

/**
 *	座標配列を座標のアドレス配列に変換する関数
 */
void coor_cnv_adr(arrow_pos *(to)[WIDTH - 2][HEIGHT - 2],arrow_pos from[WIDTH - 2][HEIGHT - 2]){
	for(int i = 0; i < WIDTH - 2; i++){
		for(int j = 0; j < HEIGHT - 2; j++){
			to[i][j] = &from[i][j];
		}
	}
}

/**
 *	座標のアドレス配列をコピーする関数
 */
void coorcpy(arrow_pos *(to)[WIDTH - 2][HEIGHT - 2],arrow_pos *(from)[WIDTH - 2][HEIGHT - 2]){
	for(int i = 0; i < WIDTH - 2; i++){
		for(int j = 0; j < HEIGHT - 2; j++){
			to[i][j] = from[i][j];
		}
	}
}

/*
 * マップ上を移動する関数
 * width						マップの幅
 * hright 					マップの高さ
 * tmp_pos[10][10]	マップ座標の配列
 * offset						操作受け付け開始時の座標
 * 戻り値
 * int tmp_pos			ループを抜けた際の座標
 */
arrow_pos move_on_map(int width, int height,arrow_pos *(tmp_pos)[WIDTH -2 ][HEIGHT - 2], arrow_pos offset){
	arrow_pos arrow_pos_label = offset;
	arrow_pos return_value;
	input_assort tmp_input_list;
	print_line("●",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
	while(1){
		while(!(tmp_input_list = mykbhit()).kbhit_flag);
		switch(tmp_input_list.input_char){
			case 'w':
				print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				if(arrow_pos_label.y <= 0 || tmp_pos[arrow_pos_label.x][arrow_pos_label.y - 1]->not_active){
				}else{
					arrow_pos_label.y--;
				}
				print_line("●",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				break;

			case 's':
				print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				if(arrow_pos_label.y > height - 2 || tmp_pos[arrow_pos_label.x][arrow_pos_label.y + 1]->not_active){
				}else{
					arrow_pos_label.y++;
				}
				print_line("●",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				break;

			case 'a':
				print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				if(arrow_pos_label.x <= 0 || tmp_pos[arrow_pos_label.x - 1][arrow_pos_label.y]->not_active){
				}else{
					arrow_pos_label.x--;
				}
				print_line("●",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				break;

			case 'd':
				print_line(" ",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				if(arrow_pos_label.x > width - 2 || tmp_pos[arrow_pos_label.x + 1][arrow_pos_label.y]->not_active){
				}else{
					arrow_pos_label.x++;
				}
				print_line("●",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				break;
			case ENTERKEY:
				break;
			case ' ':
				start_pos =*tmp_pos[arrow_pos_label.x][arrow_pos_label.y];
				start_pos.x -= 2;
				start_pos.y -= 2;
				arrow_pos_label.x = width - 2;
				arrow_pos_label.y = height - 1;
				return *tmp_pos[arrow_pos_label.x][arrow_pos_label.y];
				break;
			default:
				//print_line("●",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y);
				continue;
				//break;
		}
		//デバッグ用座標表示
		//printf("%2d,%2d",arrow_pos_label.x,arrow_pos_label.y);
		//printf("%2d,%2d %2d,%2d %d",tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->x,tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->y,arrow_pos_label.x,arrow_pos_label.y,tmp_pos[arrow_pos_label.x][arrow_pos_label.y + 1]->not_active);
		if(tmp_pos[arrow_pos_label.x][arrow_pos_label.y]->at_event){
			break;
		}
	}
	return *tmp_pos[arrow_pos_label.x][arrow_pos_label.y];
}

void update_map(stage now_stage){
	mapcpy(now_map,maps[now_stage]);
	coorcpy(now_map_coor,map_coors[now_stage]);
}

/*
 *	マップ配列の初期化
 */
void initmaps(){
	mapcpy(maps[stage1],map_st1);
	mapcpy(maps[stage2],map_st2);
	mapcpy(maps[stage3_1],map_st3_1);
	mapcpy(maps[stage3_2],map_st3_2);
	mapcpy(maps[stage3_3],map_st3_3);
	mapcpy(maps[stage4_1],map_st4_1);
	mapcpy(maps[stage4_2],map_st4_2);
	mapcpy(maps[stage4_3],map_st4_3);
	mapcpy(maps[ope_exp],map_exp);
	coor_cnv_adr(map_coors[stage1],st1_pos);
	coor_cnv_adr(map_coors[stage2],st2_pos);
	coor_cnv_adr(map_coors[stage3_1],st3_1_pos);
	coor_cnv_adr(map_coors[stage3_2],st3_2_pos);
	coor_cnv_adr(map_coors[stage3_3],st3_3_pos);
	coor_cnv_adr(map_coors[stage4_1],st4_1_pos);
	coor_cnv_adr(map_coors[stage4_2],st4_2_pos);
	coor_cnv_adr(map_coors[stage4_3],st4_3_pos);
	coor_cnv_adr(map_coors[ope_exp],exp_pos);
	mapcpy(now_map,maps[now_stage]);
	coorcpy(now_map_coor,map_coors[now_stage]);
	reset_state();
}
