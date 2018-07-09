/**
 *	@def
 *	マップ上のメニューに関する定数
 */
#define MAP_WIN_WIDTH		(WIDTH - 2) / 3
#define MAP_WIN_HEIGHT	6
#define MAP_WIN_X				WIDTH - 1 - MAP_WIN_WIDTH
#define MAP_WIN_Y				5

/**
 *	@def
 *	マップ上のステータスメニューに関する定数
 */
#define STAT_WIN_WIDTH		MAP_WIN_WIDTH  + 10
#define STAT_WIN_HEIGHT		8
#define STAT_WIN_X				MAP_WIN_X - (MAP_WIN_WIDTH + 10)

void view_status(){
	character *front;
	switch(now_stage){
		case stage1:
			front = &lirel;
			break;
		default:
			front = &naoki;
	}
	make_flame(STAT_WIN_WIDTH,STAT_WIN_HEIGHT,STAT_WIN_X,MAP_WIN_Y);	
	mvcur(STAT_WIN_X + STAT_WIN_WIDTH - 11, MAP_WIN_Y + 1);
	printf("%3d / %3d",front->hp,front->max_hp);
	mvcur(STAT_WIN_X + 2, MAP_WIN_Y + 1);
	printf("前衛: %s",front->name);
	mvcur(STAT_WIN_X + 6, MAP_WIN_Y + 2);
	printf("武器: %s",using_weapon->name);	
	mvcur(STAT_WIN_X + 6, MAP_WIN_Y + 3);
	printf("防具: %s",using_protector->name);	
	mvcur(STAT_WIN_X + STAT_WIN_WIDTH - 11, MAP_WIN_Y + 4);
	printf("%3d / %3d",arist.hp,arist.max_hp);
	mvcur(STAT_WIN_X + 2, MAP_WIN_Y + 4);
	printf("後衛: %s",arist.name);
	mvcur(STAT_WIN_X + 6, MAP_WIN_Y + 5);
	printf("武器: %s",arist_using_weapon->name);	
	mvcur(STAT_WIN_X + 6, MAP_WIN_Y + 6);
	printf("防具: %s",arist_using_protector->name);	
	wait_input_without_arrow();
	print_lines(now_map,2,2,HEIGHT - 2);
}

/* アイテム欄 */
void item_list_on_map(){
	/* 座標の定義 */
	arrow_pos item_pos[] = {
		{MAP_WIN_X - MAP_WIN_WIDTH + 2,MAP_WIN_Y + 1,0,0},
		{MAP_WIN_X - MAP_WIN_WIDTH + 2,MAP_WIN_Y + 2,0,0},
		{MAP_WIN_X - MAP_WIN_WIDTH + 2,MAP_WIN_Y + 3,0,0},
		{MAP_WIN_X - MAP_WIN_WIDTH + 2,MAP_WIN_Y + 4,0,0},
		{MAP_WIN_X - MAP_WIN_WIDTH + 2,MAP_WIN_Y + 5,0,0}
	};
	extendstr use_potion_message[] = {
		{"ポーションを使った！▼ ",0,0}
	};
	extendstr use_nasu_message[] = {
		{"ここで食べるのはもったいない▼ ",0,0},
		{"戦闘中の補給によさそうだ▼ ",0,0}
	};
	make_flame(MAP_WIN_WIDTH,MAP_WIN_HEIGHT + 1,MAP_WIN_X - MAP_WIN_WIDTH,MAP_WIN_Y);	
	for(int i = 0; i <= potion_amount + have_nasu; i++){
		if(i == potion_amount + have_nasu){
			print_line("戻る",MAP_WIN_X - MAP_WIN_WIDTH + 4,MAP_WIN_Y + 1 + i);
		}else if(i == potion_amount && have_nasu){	//ここで茄子所持のときの分岐
			print_line("ｿﾗﾅﾑ･ﾒﾛﾝｹﾞﾅ",MAP_WIN_X - MAP_WIN_WIDTH + 4,MAP_WIN_Y + 1 + i);
		}else{
			print_line("ポーション",MAP_WIN_X - MAP_WIN_WIDTH + 4,MAP_WIN_Y + 1 + i);
			//print_line("ｿﾗﾅﾑ･ﾒﾛﾝｹﾞﾅ",MAP_WIN_X - MAP_WIN_WIDTH + 4,MAP_WIN_Y + 1 + i);
		}
	}
	int selected_item = select_from_list(item_pos,potion_amount + have_nasu +1);
	if(selected_item < potion_amount){
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		exstrcpy(now_text,use_potion_message,sizeof(use_potion_message)/sizeof(extendstr));
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(use_potion_message)/sizeof(extendstr));
		change_hp(&naoki,-1 * naoki.max_hp);
		change_hp(&arist,-1 * arist.max_hp);
		change_hp(&lirel,-1 * lirel.max_hp);
		potion_amount--;
	}else if(have_nasu && selected_item == potion_amount + have_nasu -1){
		make_flame(BATTLE_MODE_STATUS_FLAME_WIDTH,BATTLE_MODE_STATUS_FLAME_HEIGHT,BATTLE_MODE_STATUS_FLAME_X,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT);
		exstrcpy(now_text,use_nasu_message,sizeof(use_nasu_message)/sizeof(extendstr));
		string_march(now_text,BATTLE_MODE_STATUS_FLAME_X + 1,HEIGHT - BATTLE_MODE_STATUS_FLAME_HEIGHT + 1,sizeof(use_nasu_message)/sizeof(extendstr));
	}
	print_lines(now_map,2,2,HEIGHT - 2);
}

/* マップ上で開くメニュー */
int onmap_manu(){
	/* メニューの終了フラグ */
	int close_menu_flag = 0;
	/* 項目の定義  */
	char *(menu_items)[] = {
		"ステータス",
		"アイテム",
		"タイトルに戻る",
		"閉じる"
	};
	enum menu_id {
		status,
		items,
		back_title,
		close
	};
	/* 座標の定義 */
	arrow_pos menu_pos[] = {
		{MAP_WIN_X + 2,MAP_WIN_Y + 1,0,0},
		{MAP_WIN_X + 2,MAP_WIN_Y + 2,0,0},
		{MAP_WIN_X + 2,MAP_WIN_Y + 3,0,0},
		{MAP_WIN_X + 2,MAP_WIN_Y + 4,0,0}
	};
	while(!close_menu_flag){
		make_flame(MAP_WIN_WIDTH,MAP_WIN_HEIGHT,MAP_WIN_X,MAP_WIN_Y);	
		print_lines(menu_items,MAP_WIN_X + 3,MAP_WIN_Y + 1,4);

		switch(select_from_list(menu_pos,4)){
			case status:
				view_status();
				break;
			case items:
				item_list_on_map();
				break;
			case back_title:
				return 1;
				break;
			case close:
				close_menu_flag = 1;
				continue;
				break;
		}
	}
	sub_flame_clean(MAP_WIN_WIDTH,MAP_WIN_HEIGHT,MAP_WIN_X,MAP_WIN_Y);
	return 0;
}
