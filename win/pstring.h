/**
  * Writtenby yume_yu
  * �W���o�͂̔C�ӂ̏ꏊ�ɕ�������o�͂��鎩��֐����������߂̃w�b�_
  */


/**
	* �w��ӏ��ւ�1�s�̕����o�͂��s���֐�
	* string �o�͂��镶����
	* x      �o�͂���x���W
	* y      �o�͂���y���W
	*/
void print_line(char string[], int x, int y){
	mvcur(x,y);
	printf("%s",string);
	mvcur(0,HEIGHT + 1);
}

/**
	* �w��ӏ��ւ̕����s�s�̕����o�͂��s���֐�
	* string    �o�͂��镶����z��
	* x         �o�͂��J�n����x���W
	* y         �o�͂��J�n����y���W
	* num_lines �o�͂���s��
	*/
void print_lines(char string[][100], int x, int y, int num_lines){
	for(int i = 0; i < num_lines; i++){
		mvcur(x,y+i);
		printf("%s",string[i]);
	}
	mvcur(0,HEIGHT + 1);
}
