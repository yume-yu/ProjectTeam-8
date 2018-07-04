enum event decide_event(struct arrow_pos exit_point){
	enum event selected_event;
	/* メニュー表示かどうかを判定 */
	if(exit_point.x == 58 && exit_point.y == 24){
		selected_event = open_menu;
	}else{
		switch(now_stage){
			case stage1:
				if(exit_point.x == 31 && exit_point.y == 7){
					/* ボス到達 */
					selected_event = battle_event;
					front = &lirel;
					back = &arist;
					set_ch_stat(ST1_BOSS_NAME,&boss1,ST1_BOSS_HP,ST1_BOSS_HP,ST1_BOSS_MINATK,ST1_BOSS_MAXATK);
					enemies[0] = &boss1;
					enemies[1] = &dummy;
					enemy_amount = 1;
					/* マップ復帰時の座標を指定 */
					start_pos.x = exit_point.x - 2;
					start_pos.y = (exit_point.y + 1 ) - 2;
				}else if((exit_point.x == 4 || exit_point.x == 5) && exit_point.y == 15){
					/* 一番左の部屋到達 */
					selected_event = talk_event;
					room_id = 0;
					/* マップ復帰時の座標を指定 */
					start_pos.x = exit_point.x - 2;
					start_pos.y = (exit_point.y + 1 ) - 2;
				}else if(exit_point.x == 25 && exit_point.y == 14){
					/* 真ん中の部屋到達 */
					selected_event = talk_event;
					room_id = 1;
					/* マップ復帰時の座標を指定 */
					start_pos.x = exit_point.x - 2;
					start_pos.y = (exit_point.y + 1 ) - 2;
				}
				/* 右側の侵入禁止 */
				if(exit_point.x == 35 && exit_point.y == 17){
					room_id = 2;
					selected_event = talk_event;
					/* マップ復帰時の座標を指定 */
					start_pos.x = exit_point.x - 1 - 2;
					start_pos.y = exit_point.y - 2;
					/* 右側の侵入禁止 */
					if(exit_point.x == 35 && exit_point.y == 17){
						selected_event = talk_event;
					}
				}
				break;
			case stage2:
				if(exit_point.x == 28 && exit_point.y == 9){
					/* ボス到達 */
					room_id = 2;
					selected_event = battle_event;
					front = &naoki;
					back = &arist;
					set_ch_stat(ST2_BOSS_NAME,&boss1,ST2_BOSS_HP,ST2_BOSS_HP,ST2_BOSS_MINATK,ST2_BOSS_MAXATK);
					enemies[0] = &boss1;
					enemies[1] = &dummy;
					enemy_amount = 1;
				}else if(exit_point.x == 15 && exit_point.y == 15){
					/* 左の部屋 */
					room_id = 1;
					if(!talk_event_st2_1_arrived){
						room_id = 1;
						selected_event = battle_event;
						front = &naoki;
						back = &arist;
						set_ch_stat("Weak",&boss1,ST1_BOSS_HP,ST1_BOSS_HP,ST1_BOSS_MINATK,ST1_BOSS_MAXATK);
						enemies[0] = &boss1;
						enemies[1] = &dummy;
						enemy_amount = 1;
						talk_event_st2_1_arrived = 1;
					}else{
						selected_event = talk_event;
					}
				}else if(exit_point.x == 41 && exit_point.y == 15){
					/* 右の部屋 */
					room_id = 0;
					selected_event = talk_event;
				}else{
				}
				/* マップ復帰時の座標を指定 */
				start_pos.x = exit_point.x - 2;
				start_pos.y = (exit_point.y + 1 ) - 2;
				break;
			case stage3_1:	//中央マップ
				if(exit_point.x == 58 && exit_point.y == 18){
					/* 右マップへの移動 */
					selected_event = move_map;
					now_stage = stage3_2;
					start_pos.x= 1;
					start_pos.y = 17 -  2;
				}else if(exit_point.x == 2 && exit_point.y == 18){
					/* 左マップへの移動 */
					selected_event = move_map;
					now_stage = stage3_3;
					start_pos.x= 56 - 2;
					start_pos.y = 17 -  2;
				}else if(exit_point.x == 15 && exit_point.y == 15){
					/* 左の家 */
					room_id = 3;
					selected_event = talk_event;
					/* マップ復帰時の座標を指定 */
					start_pos.x= 15 - 2;
					start_pos.y = 15 + 1 - 2;
				}else if(exit_point.x == 28 && exit_point.y == 9){
					/* ボス到達 */
					room_id = 4;
					selected_event = battle_event;
					front = &naoki;
					back = &arist;
					set_ch_stat(ST3_BOSS_NAME,&boss1,ST3_BOSS_HP,ST3_BOSS_HP,ST3_BOSS_MINATK,ST3_BOSS_MAXATK);
					enemies[0] = &boss1;
					enemies[1] = &dummy;
					enemy_amount = 1;
				}else if(exit_point.x == 41 && exit_point.y == 15){
					/* 右の家 */
					room_id = 5;
					selected_event = talk_event;
					/* マップ復帰時の座標を指定 */
					start_pos.x= 41 - 2;
					start_pos.y = 15 + 1 - 2;
				}
				break;
			case stage3_2:	//右マップ
				if(exit_point.x == 3 && exit_point.y == 17){
					/* 中央マップへの移動 */
					selected_event = move_map;
					now_stage = stage3_1;
					start_pos.x = 57 - 2;
					start_pos.y = 18 - 2;
				}else if(exit_point.x == 43 && exit_point.y == 14){
					/* 左の家 */
					room_id = 7;
					if(!battle_event_st3_7_arrived){ //始めての訪問の時
						selected_event = battle_event;
						/* キャラクターセット */
						front = &naoki;
						back = &arist;
						set_ch_stat("Weak 1",&boss1,ST1_BOSS_HP,ST1_BOSS_HP,ST1_BOSS_MINATK,ST1_BOSS_MAXATK);
						set_ch_stat("Weak 2",&boss2,ST1_BOSS_HP,ST1_BOSS_HP,ST1_BOSS_MINATK,ST1_BOSS_MAXATK);
						enemies[0] = &boss1;
						enemies[1] = &boss2;
						enemy_amount = 2;
						battle_event_st3_7_arrived = 1;
					}else{ //2回め以降の時
						room_id = 6; //めんどくさかったので、隣の部屋に偽装して同じイベントを起こす
						selected_event = talk_event;
					}
					/* マップ復帰時の座標を指定 */
					start_pos.x= 43 - 2;
					start_pos.y = 14 + 1 - 2;
				}else if(exit_point.x == 15 && exit_point.y == 14){
					/* 右の家 */
					room_id = 6;
					selected_event = talk_event;
					/* マップ復帰時の座標を指定 */
					start_pos.x= 15 - 2;
					start_pos.y = 14 + 1 - 2;
				}
				break;
			case stage3_3:	//左マップ
				if(exit_point.x == 57 && exit_point.y == 17){
					/* 中央マップへの移動 */
					selected_event = move_map;
					now_stage = stage3_1;
					start_pos.x = 2;
					start_pos.y = 18 - 2;
				}else if(exit_point.x == 43 && exit_point.y == 14){
					/* 左上の家 */
					room_id = 2;
					selected_event = talk_event;
					/* マップ復帰時の座標を指定 */
					start_pos.x= 43 - 2;
					start_pos.y = 14 + 1 - 2;
				}else if(exit_point.x == 27 && exit_point.y == 20){
					/* 下の家 */
					room_id = 1;
					selected_event = talk_event;
					/* マップ復帰時の座標を指定 */
					start_pos.x= 27 - 2;
					start_pos.y = 20 - 1 - 2;
				}else if(exit_point.x == 15 && exit_point.y == 14){
					/* 右上の家 */
					room_id = 0;
					selected_event = talk_event;
					/* マップ復帰時の座標を指定 */
					start_pos.x= 15 - 2;
					start_pos.y = 14 + 1 - 2;
				}
				break;
			case stage4_1: //左マップ
				if(exit_point.x == 55 && (exit_point.y == 13 || exit_point.y == 14)){
					/* 中央マップへの移動 */
					selected_event = move_map;
					now_stage = stage4_2;
					mapcpy(now_map,maps[now_stage]);
					coorcpy(now_map_coor,map_coors[now_stage]);
					start_pos.x = 4 - 2;
					start_pos.y = 14 - 2;
				}else if((exit_point.x == 14 || exit_point.x == 15) && exit_point.y == 11){
					/* 左下の家 */
					selected_event = talk_event;
					room_id = 0;
					/* マップ復帰時の座標を指定 */
					start_pos.x = exit_point.x - 2;;
					start_pos.y = 12 - 2;
				}else if(exit_point.x == 40 && exit_point.y == 6){
					/* 上の家 */
					room_id = 1;
					selected_event = talk_event;
					/* マップ復帰時の座標を指定 */
					start_pos.x= 40 - 1 - 2;
					start_pos.y = 6 - 2;
				}else if(exit_point.x == 38 && exit_point.y == 11){
					/* 右下の家 */
					room_id = 2;
					selected_event = talk_event;
					/* マップ復帰時の座標を指定 */
					start_pos.x= exit_point.x - 2;
					start_pos.y = 11 + 1 - 2;
				}
				break;
			case stage4_2: //中央マップ
				if(exit_point.x == 55 && (exit_point.y == 14 || exit_point.y == 15)){
					/* 右マップへの移動 */
					selected_event = move_map;
					now_stage = stage4_3;
					mapcpy(now_map,maps[now_stage]);
					coorcpy(now_map_coor,map_coors[now_stage]);
					start_pos.x = 2;
					start_pos.y = 14 - 2;
				}else if(exit_point.x == 3 && (exit_point.y == 14 || exit_point.y == 13)){
					/* 左マップへの移動 */
					selected_event = move_map;
					now_stage = stage4_1;
					mapcpy(now_map,maps[now_stage]);
					coorcpy(now_map_coor,map_coors[now_stage]);
					start_pos.x = 54 - 2;
					start_pos.y = 14 - 2;
				}else if(exit_point.x == 20 && exit_point.y == 6){
					/* 上の家 */
					room_id = 3;
					selected_event = talk_event;
					/* マップ復帰時の座標を指定 */
					start_pos.x= 20 - 1 - 2;
					start_pos.y = 6 - 2;
				}else if((exit_point.x == 36 || exit_point.x == 37 || exit_point.x == 38) && exit_point.y == 12){
					/* ボス到達 */
					room_id = 4;
					selected_event = battle_event;
					/* キャラクターセット */
					front = &robo;
					back = &dummy;
					set_ch_stat(ST4_BOSS_NAME,&boss1,ST4_BOSS_HP,ST4_BOSS_HP,ST4_BOSS_MINATK,ST4_BOSS_MAXATK);
					enemies[0] = &boss1;
					enemies[1] = &dummy;
					enemy_amount = 1;
				}
				break;
			case stage4_3://右マップ
				/* 中央マップへの移動 */
				if(exit_point.x == 2 && (exit_point.y == 14 || exit_point.y == 15)){
					selected_event = move_map;
					now_stage = stage4_2;
					mapcpy(now_map,maps[now_stage]);
					coorcpy(now_map_coor,map_coors[now_stage]);
					start_pos.x = 54 - 2;
					start_pos.y = 14 - 2;
				}else if((exit_point.x == 14 || exit_point.x == 15) && exit_point.y == 11){
					/* 左の家 */
					room_id = 5;
					if(!battle_event_st4_5_arrived){ //始めての訪問の時
						selected_event = battle_event;
						/* キャラクターセット */
						front = &naoki;
						back = &arist;
						set_ch_stat("Weak 1",&boss1,ST1_BOSS_HP,ST1_BOSS_HP,ST1_BOSS_MINATK,ST1_BOSS_MAXATK);
						set_ch_stat("Weak 2",&boss2,ST1_BOSS_HP,ST1_BOSS_HP,ST1_BOSS_MINATK,ST1_BOSS_MAXATK);
						enemies[0] = &boss1;
						enemies[1] = &boss2;
						enemy_amount = 2;
						battle_event_st4_5_arrived = 1;
					}else{ //2回め以降の時
						selected_event = talk_event;
					}
					start_pos.x = exit_point.x - 2;
					start_pos.y = 12 - 2;
				}else if(exit_point.x == 40 && exit_point.y == 6){
					/* 上の家 */
					room_id = 6;
					selected_event = talk_event;
					/* マップ復帰時の座標を指定 */
					start_pos.x=  40 - 1 - 2;
					start_pos.y = 6 - 2;
				}
				break;
			default:
				break;
		}
	}
	return selected_event;
}
