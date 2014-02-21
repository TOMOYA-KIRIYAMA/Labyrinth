#include stdio.h
#include stdlib.h
#include time.h

#define WIDTH 5
#define HIGHT 5
#define MAX_WALL_NUM ((HIGHT-1)  (WIDTH-1))   �ǂ�z�u���Ă��������
#define CAND_WALL_NUM (HIGHT(WIDTH-1)+WIDTH(HIGHT-1))  �ǂ�z�u�ł����␔

typedef struct Panel{
	int upper;  �ǂ̂���Ȃ�
	int under;
	int left;
	int right;
	struct Panel upper_pa;
	struct Panel under_pa;
	struct Panel left_pa;
	struct Panel right_pa;
} panel_t;


 debug�p 
 wall�z��̒��g��\������ 
 10���Ƃɉ��s 
void prt_wall(int wall[])
{
	int j;
	for (j=0; jCAND_WALL_NUM; j++)
		printf(%d%s, wall[j], ((j+1)%(WIDTH-1) == 0)  n   );
	printf(n);
}


 �e�평���� 
void init(panel_t panel[HIGHT][WIDTH])
{
	int i, j;
	
	 �����n��̐ݒ� 
	srand((unsigned) time(NULL));
	
	 panel�Ԃ̑Ή��t�� 
	for (i=0; iHIGHT; i++){
		for (j=0; jWIDTH; j++){
			 ��p�l�� 
			if (i=0){
				panel[i][j].upper_pa = NULL;
				panel[i][j].upper = 1;
			}else{
				panel[i][j].upper_pa = &panel[i-1][j];
				panel[i][j].upper = 0;
			}
			
			 ���p�l�� 
			if (i=HIGHT-1){
				panel[i][j].under_pa = NULL;
				panel[i][j].under = 1;
			}else{
				panel[i][j].under_pa = &panel[i+1][j];
				panel[i][j].under = 0;
			}
			
			 ���p�l�� 
			if (j=0){
				panel[i][j].left_pa = NULL;
				panel[i][j].left = 1;
			}else{
				panel[i][j].left_pa = &panel[i][j-1];
				panel[i][j].left = 0;
			}
			
			 �E�p�l�� 
			if (j=HIGHT-1){
				panel[i][j].right_pa = NULL;
				panel[i][j].right = 1;
			}else{
				panel[i][j].right_pa = &panel[i][j+1];
				panel[i][j].right = 0;
			}
		}
	}
}


 a��b�̒l�����ւ��� 
void swap(int a, int b){
	int tmp = a;
	a = b;
	b = tmp;
}


 0�`���܂ł̐�����d���Ȃ���max�Ƃ肾�� 
 �Ԃ�l��g 
void myRand(int g[])
{
	int tmp[CAND_WALL_NUM];
	int i;
	int r;
	
	for (i=0; iCAND_WALL_NUM; i++){
		tmp[i] = i;
	}
	
	for (i=0; iMAX_WALL_NUM; i++){
		r = rand()%CAND_WALL_NUM;
		swap(&tmp[i], &tmp[r]);
		printf(%d%s, r, (i%10==0) n   );  for debug
	}
	for (i=0; iMAX_WALL_NUM; i++){
		g[i] = tmp[i];
	}
}


 tmp�z��ɓ����Ă��鐔�����Q�l�ɁAwall�z����̓K�؂ȂƂ����1�ɂ��� 
void validate_wall_array(int wall[], int create[MAX_WALL_NUM])
{
	int i;
	
	for (i=0; iMAX_WALL_NUM; i++){
		wall[ create[i] ] = 1;
	}
}


 �ǂ̔z�u 
void set_wall(int wall[])
{
	int create[MAX_WALL_NUM];
	
	myRand(create);
	validate_wall_array(wall, create);
}


 �ǂ�11�̐����`�����݂��邩�ǂ��� 
int isExistSquare(int wall[])
{
	int i, j;
	int wall_co[HIGHT][WIDTH];
	int hi, col;
	
	 ������ 
	for (i=0; iHIGHT; i++){
		for (j=0; jWIDTH; j++){
			wall_co[i][j] = 0;
			if (i==0  i==HIGHT-1)
				++wall_co[i][j];
			if (j==0  j==WIDTH-1)
				++wall_co[i][j];
		}
	}
	
	
	for (i=0; iCAND_WALL_NUM; i++){
		if (wall[i] == 1){
			if (i CAND_WALL_NUM2){  �c�ǂ����ɓo�^ 
				hi  = i(WIDTH-1);
				col = i%(WIDTH-1);
				++wall_co[hi][col];
				++wall_co[hi][col+1];
			}else{  ���ǂ����ɓo�^ 
				hi  =  i%(HIGHT-1);
				col =  i(HIGHT-1)-WIDTH;
				++wall_co[hi][col];
				++wall_co[hi+1][col];
			}
		}
	}
	
	for (i=0; iHIGHT; i++){
		for (j=0; jWIDTH; j++){
			if (wall_co[i][j] = 4){
				return 1;
			}
		}
	}
	
	return 0;
}


int isSurrounded(int wall[])  making
{
	int i, j;
	int been_panel[HIGHT][WIDTH];
	
	for (i=0; iHIGHT; i++){
		for (j=0; jWIDTH; j++){
			been_panel[i][j] = 0;
		}
	}
	
	
	return 1;
}


int isValidLaby(int wall[])
{
	return !isSurrounded(wall);
}


 wall�z���1�ɂȂ��Ă���Ƃ���ɕǂ��쐬���� 
void create_wall(int wall[], panel_t panel[HIGHT][WIDTH])
{
	int i, j;
	int hi, col;
	
	
	for (i=0; iCAND_WALL_NUM; i++){
		if (wall[i] == 1){
			if (i CAND_WALL_NUM2){  �c�ǂ����ɓo�^ 
				hi  = i(WIDTH-1);
				col = i%(WIDTH-1);
				panel[hi][col].right = 1;
				panel[hi][col+1].left = 1;
			}else{  ���ǂ����ɓo�^ 
				hi  =  i%(HIGHT-1);
				col =  i(HIGHT-1)-WIDTH;
				panel[hi][col].under = 1;
				panel[hi+1][col].upper = 1;
			}
		}
	}
}


 ���オ�X�^�[�g�A�E�����S�[�� 
void create_labyrinth(panel_t panel[HIGHT][WIDTH])
{
	int wall[CAND_WALL_NUM];  �ǂ̒u�����ꏊ�ɂ�1������
	int i;
	
	 �����_���ŕǂ̔z�u�ꏊ�̌��� 
	do{
		 �ǔz��̏����� 
		for (i=0; iCAND_WALL_NUM; i++){
			wall[i] = 0;
		}
		set_wall(wall);
	}while(isExistSquare(wall));  �쐬�������H���L�����ǂ���(�����Ȃ��ꏊ�͑��݂��Ȃ���) 
	printf(%sn, (isExistSquare(wall)) MISS OK);  for debug
	prt_wall(wall);  for debug
	
	 �Ǎ쐬�̊֐�(���p�l���̉E�ǂƉE�p�l���̍��ǂ𓯎��ɗL���� 
	create_wall(wall, panel);
	
	isValidLaby(wall);
}


void play_game(void)
{
	 �S�[���܂ł����߁I 
	
	
	
}


int main(void)
{
	panel_t panel[HIGHT][WIDTH];  fix me
	init(panel);  �e�평����
	create_labyrinth(panel);
	play_game();  ��������H�ŗV��
	
	return 0;
}