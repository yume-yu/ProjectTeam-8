/**
 * Writtenby yume_yu
 * �W���o�͏�Ƀt���[����`�悷�邽�߂̎���֐����������߂̃w�b�_
 */


/** 
 * �W���o�͂̏�����
 */
void init_term(){
	//�J�[�\���ʒu��(1,1)�Ɉړ�
	mvcur(1,1);
}

/**
 * �t���[���̍쐬�֐�
 * width    �쐬����t���[���̕�
 * height   �쐬����t���[���̍���
 * offset_x �쐬����t���[���̊J�n�ʒu��x���W
 * offset_y �쐬����t���[���̊J�n�ʒu��y���W
 */
void make_flame(int width, int height, int offset_x, int offset_y){
	int print_width = width - 2;
	int print_height = height - 2;
	//1�s�ڂ̕`��
	mvcur(offset_x,offset_y);
	printf("��");
	for(int i = 0; i < print_width; i++){
		printf("��");
	}
	printf("��");
	//���ԕ����̕`��
	for(int i = 0; i < print_height; i++){
		mvcur(offset_x,offset_y + 1 + i);
		printf("��");
		for(int j = 0; j < print_width; j++){
			printf(" ");
		}
		printf("��");
	}

	//�ŏI�s�����̕`��
	mvcur(offset_x,offset_y + height - 1);
	printf("��");
	for(int i = 0; i < print_width; i++){
		printf("��");
	}
	printf("��");

	//�J�[�\���ʒu�̏�����
	mvcur(1,HEIGHT+1);
}

void make_vsflame(int width, int height, int offset_x, int offset_y, int split_x){
	int print_width = width - 2;
	int print_height = height - 2;
	//1�s�ڂ̕`��
	mvcur(offset_x,offset_y);
	printf("��");
	for(int i = 0; i < print_width; i++){
		if(i == split_x){
			printf("��");
		}else{
			printf("��");
		}
	}
	printf("��");
	//���ԕ����̕`��
	for(int i = 0; i < print_height; i++){
		mvcur(offset_x,offset_y + 1 + i);
		printf("��");
		for(int j = 0; j < print_width; j++){
			if(j == split_x){
				printf("��");
			}else{
				printf(" ");
			}
		}
		printf("��");
	}
	//�ŏI�s�����̕`��
	mvcur(offset_x,offset_y + height - 1);
	printf("��");
	for(int i = 0; i < print_width; i++){
		if(i == split_x){
			printf("��");
		}else{
			printf("��");
		}
	}


	printf("��\n");

	//�J�[�\���ʒu�̏�����
	mvcur(1,HEIGHT+1);

}
