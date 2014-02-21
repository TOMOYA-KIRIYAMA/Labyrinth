#include stdio.h
#include stdlib.h
#include time.h

#define WIDTH 5
#define HIGHT 5
#define MAX_WALL_NUM ((HIGHT-1)  (WIDTH-1))   壁を配置していい上限数
#define CAND_WALL_NUM (HIGHT(WIDTH-1)+WIDTH(HIGHT-1))  壁を配置できる候補数

typedef struct Panel{
	int upper;  壁のあるなし
	int under;
	int left;
	int right;
	struct Panel upper_pa;
	struct Panel under_pa;
	struct Panel left_pa;
	struct Panel right_pa;
} panel_t;


 debug用 
 wall配列の中身を表示する 
 10個ごとに改行 
void prt_wall(int wall[])
{
	int j;
	for (j=0; jCAND_WALL_NUM; j++)
		printf(%d%s, wall[j], ((j+1)%(WIDTH-1) == 0)  n   );
	printf(n);
}


 各種初期化 
void init(panel_t panel[HIGHT][WIDTH])
{
	int i, j;
	
	 乱数系列の設定 
	srand((unsigned) time(NULL));
	
	 panel間の対応付け 
	for (i=0; iHIGHT; i++){
		for (j=0; jWIDTH; j++){
			 上パネル 
			if (i=0){
				panel[i][j].upper_pa = NULL;
				panel[i][j].upper = 1;
			}else{
				panel[i][j].upper_pa = &panel[i-1][j];
				panel[i][j].upper = 0;
			}
			
			 下パネル 
			if (i=HIGHT-1){
				panel[i][j].under_pa = NULL;
				panel[i][j].under = 1;
			}else{
				panel[i][j].under_pa = &panel[i+1][j];
				panel[i][j].under = 0;
			}
			
			 左パネル 
			if (j=0){
				panel[i][j].left_pa = NULL;
				panel[i][j].left = 1;
			}else{
				panel[i][j].left_pa = &panel[i][j-1];
				panel[i][j].left = 0;
			}
			
			 右パネル 
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


 aとbの値を入れ替える 
void swap(int a, int b){
	int tmp = a;
	a = b;
	b = tmp;
}


 0～ｎまでの数から重複なしでmax個とりだす 
 返り値はg 
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


 tmp配列に入っている数字を参考に、wall配列内の適切なところを1にする 
void validate_wall_array(int wall[], int create[MAX_WALL_NUM])
{
	int i;
	
	for (i=0; iMAX_WALL_NUM; i++){
		wall[ create[i] ] = 1;
	}
}


 壁の配置 
void set_wall(int wall[])
{
	int create[MAX_WALL_NUM];
	
	myRand(create);
	validate_wall_array(wall, create);
}


 壁で11の正方形が存在するかどうか 
int isExistSquare(int wall[])
{
	int i, j;
	int wall_co[HIGHT][WIDTH];
	int hi, col;
	
	 初期化 
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
			if (i CAND_WALL_NUM2){  縦壁を順に登録 
				hi  = i(WIDTH-1);
				col = i%(WIDTH-1);
				++wall_co[hi][col];
				++wall_co[hi][col+1];
			}else{  横壁を順に登録 
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


 wall配列で1になっているところに壁を作成する 
void create_wall(int wall[], panel_t panel[HIGHT][WIDTH])
{
	int i, j;
	int hi, col;
	
	
	for (i=0; iCAND_WALL_NUM; i++){
		if (wall[i] == 1){
			if (i CAND_WALL_NUM2){  縦壁を順に登録 
				hi  = i(WIDTH-1);
				col = i%(WIDTH-1);
				panel[hi][col].right = 1;
				panel[hi][col+1].left = 1;
			}else{  横壁を順に登録 
				hi  =  i%(HIGHT-1);
				col =  i(HIGHT-1)-WIDTH;
				panel[hi][col].under = 1;
				panel[hi+1][col].upper = 1;
			}
		}
	}
}


 左上がスタート、右下がゴール 
void create_labyrinth(panel_t panel[HIGHT][WIDTH])
{
	int wall[CAND_WALL_NUM];  壁の置かれる場所には1が入る
	int i;
	
	 ランダムで壁の配置場所の決定 
	do{
		 壁配列の初期化 
		for (i=0; iCAND_WALL_NUM; i++){
			wall[i] = 0;
		}
		set_wall(wall);
	}while(isExistSquare(wall));  作成した迷路が有効かどうか(いけない場所は存在しないか) 
	printf(%sn, (isExistSquare(wall)) MISS OK);  for debug
	prt_wall(wall);  for debug
	
	 壁作成の関数(左パネルの右壁と右パネルの左壁を同時に有効化 
	create_wall(wall, panel);
	
	isValidLaby(wall);
}


void play_game(void)
{
	 ゴールまですすめ！ 
	
	
	
}


int main(void)
{
	panel_t panel[HIGHT][WIDTH];  fix me
	init(panel);  各種初期化
	create_labyrinth(panel);
	play_game();  作った迷路で遊ぶ
	
	return 0;
}