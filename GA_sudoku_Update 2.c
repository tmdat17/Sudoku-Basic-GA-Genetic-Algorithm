/*
	Name: Sudoku Giai Thuat Di Truyen
	Copyright: Bai Hoan Chinh
	Author: 
		Tran Minh Dat B1913221
		Nguyen Thanh Duy B1913291
		Le Huynh Khai Dang B1913293
	Date: 13/12/21 13:23
	Description: 
*/

#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#define NB 9
#define NB_ROWS 9
#define NB_COLS 9
#define EMPTY 0
#define MAX_GEN 9
#define MAX_VALUE 10
#define ARS 3
#define INF 999999
#define MAX_CHRO 1000

int random(int minN, int maxN){ 
	return minN + rand() % (maxN + 1 - minN);
}

typedef struct{
	int allele[ARS * ARS];   //gia tri (1->9) cua 9 o vuong nho trong 1 o vuong 3x3
	int encode[ARS * ARS];   //gia tri ma hoa (0 o chua co gia tri, 1 o co gia tri) cua 9 o vuong nho trong 1 o vuong 3x3
}Gen;

typedef struct{
	Gen	gen[MAX_GEN];
	float fitness;
}Chromosome;


typedef struct{
	Chromosome chromosome[MAX_CHRO];
	int popsize;
}Population;


typedef struct{
	int cells[NB_ROWS][NB_COLS];
}Sudoku;


void initSudoku(Sudoku* sudoku){
	int i,j;
	for(i = 0; i < NB_ROWS; i++){
		for(j = 0; j < NB_COLS; j++){
			sudoku->cells[i][j] = EMPTY;
		}
	}
}

//ham chuyen 1 ca the thanh 1 bang sudoku
void transform(Chromosome C, Sudoku *S){
	initSudoku(S);
	int i,j,t,k;
	for(i = 0; i < NB_ROWS; i++){
		if(i==0 || i==3 || i==6){
			k=0;
		}
			
		if(i==1 || i==4 || i==7){
			k=3;
		}
			
		if(i==2 || i==5 || i==8){
			k=6;
		}
			
		for(j = 0; j < NB_COLS; j++){
			//hang 0
			t = 0;
			
			if(i == 0 && j <= 2){
				S->cells[i][j] = C.gen[t].allele[k];
				k++;
				if(j==2)
					k=0;
			}
				
			if(i == 0 && j > 2 && j <= 5 ){
				S->cells[i][j] = C.gen[t+1].allele[k];
				k++;
				if(j==5)
					k=0;
			}
				
			if(i == 0 && j > 5 && j <= 8){
				S->cells[i][j] = C.gen[t+2].allele[k];
				k++;
				if(j==8)
					continue;
			}
				
			//hang 1
			if(i == 1 && j <= 2){
				S->cells[i][j] = C.gen[t].allele[k];
				k++;
				if(j==2)
					k=3;
			}
				
			if(i == 1 && j > 2 && j <= 5 ){
				S->cells[i][j] = C.gen[t+1].allele[k];
				k++;
				if(j==5)
					k=3;
			}
				
			if(i == 1 && j > 5 && j <= 8 ){
				S->cells[i][j] = C.gen[t+2].allele[k];
				k++;
				if(j==8)
					continue;
			}
				
			//hang 2
			if(i == 2 && j <= 2 ){
				S->cells[i][j] = C.gen[t].allele[k];
				k++;
				if(j==2)
					k=6;
			}
				
			if(i == 2 && j > 2 && j <= 5 ){
				S->cells[i][j] = C.gen[t+1].allele[k];
				k++;
				if(j==5)
					k=6;
			}
				
			if(i == 2 && j > 5 && j <= 8 ){
				S->cells[i][j] = C.gen[t+2].allele[k];
				k++;
				if(j==8)
					continue;
			}
				
			//hang 3
			if(i == 3 && j <= 2 ){
				S->cells[i][j] = C.gen[t+3].allele[k];
				k++;
				if(j==2)
					k=0;
			}
				
			if(i == 3 && j > 2 && j <= 5 ){
				S->cells[i][j] = C.gen[t+4].allele[k];
				k++;
				if(j==5)
					k=0;
			}
				
			if(i == 3 && j > 5 && j <= 8 ){
				S->cells[i][j] = C.gen[t+5].allele[k];
				k++;
				if(j==8)
					continue;
			}
				
			//hang 4
			if(i == 4 && j <= 2 ){
				S->cells[i][j] = C.gen[t+3].allele[k];
				k++;
				if(j==2)
					k=3;
			}
				
			if(i == 4 && j > 2 && j <= 5 ){
				S->cells[i][j] = C.gen[t+4].allele[k];
				k++;
				if(j==5)
					k=3;
			}
				
			if(i == 4 && j > 5 && j <= 8 ){
				S->cells[i][j] = C.gen[t+5].allele[k];
				k++;
				if(j==8)
					continue;
			}
				
			//hang 5
			if(i == 5 && j <= 2 ){
				S->cells[i][j] = C.gen[t+3].allele[k];
				k++;
				if(j==2)
					k=6;
			}
				
			if(i == 5 && j > 2 && j <= 5){
				S->cells[i][j] = C.gen[t+4].allele[k];
				k++;
				if(j==5)
					k=6;
			}
				
			if(i == 5 && j > 5 && j <= 8 ){
				S->cells[i][j] = C.gen[t+5].allele[k];
				k++;
				if(j==8)
					continue;
			}
				
			//hang 6
			if(i == 6 && j <= 2){
				S->cells[i][j] = C.gen[t+6].allele[k];
				k++;
				if(j==2)
					k=0;
			}
				
			if(i == 6 && j > 2 && j <= 5 ){
				S->cells[i][j] = C.gen[t+7].allele[k];
				k++;
				if(j==5)
					k=0;
			}
				
			if(i == 6 && j > 5 && j <= 8 ){
				S->cells[i][j] = C.gen[t+8].allele[k];
				k++;
				if(j==8)
					continue;
			}
				
			//hang 7
			if(i == 7 && j <= 2 ){
				S->cells[i][j] = C.gen[t+6].allele[k];
				k++;
				if(j==2)
					k=3;
			}
				
			if(i == 7 && j > 2 && j <= 5 ){
				S->cells[i][j] = C.gen[t+7].allele[k];
				k++;
				if(j==5)
					k=3;
			}
				
			if(i == 7 && j > 5 && j <= 8 ){
				S->cells[i][j] = C.gen[t+8].allele[k];
				k++;
				if(j==8)
					continue;
			}
				
			//hang 8
			if(i == 8 && j <= 2 ){
				S->cells[i][j] = C.gen[t+6].allele[k];
				k++;
				if(j==2)
					k=6;
			}
				
			if(i == 8 && j > 2 && j <= 5){
				S->cells[i][j] = C.gen[t+7].allele[k];
				k++;
				if(j==5)
					k=6;
			}
				
			if(i == 8 && j > 5 && j <= 8 ){
				S->cells[i][j] = C.gen[t+8].allele[k];
				k++;
				if(j==8)
					continue;
			}
		}
	}
}

//tinh fitness cho 9 hang cua 1 ca the
float f_row(Sudoku s){
	float count = 0.0;
	int flag;
	int k,i,j;
	for(i = 0; i < NB_ROWS; i++){
		for(j = 0; j < NB_COLS; j++){
			flag = 0;
			for(k = j; k < NB_COLS; k++){
				if(s.cells[i][k] == s.cells[i][j] && k != j)				
					flag = 1;
			}
			if(flag)
				count++;
		}
	}
	return count;
}

//tinh fitness cho 9 cot cua 1 ca the
float f_col(Sudoku s){
	float count = 0.0;
	int flag;
	int k,i,j;
	for(j = 0; j < NB_COLS; j++){
		for(i = 0; i < NB_ROWS; i++){
			flag = 0;
			for(k = i; k < NB_ROWS; k++){
				if(s.cells[i][j] == s.cells[k][j] && k != i)					
					flag = 1;		
			}
			if(flag)
				count++;
		}
	}
	return count;
}


//tinh tong fitness cho 1 ca the (bao gom hang va cot)
void fitness(Chromosome *C){
	Sudoku S;
	transform(*C,&S);
	C->fitness = f_row(S)+f_col(S);
}


//input map de
void inputSu1(Sudoku *S){
	FILE *f;
	freopen("inputSu1.txt","r",stdin);
	initSudoku(S);
	int i,j,a;
	for(i = 0; i < NB_ROWS; i++){
		for(j = 0; j < NB_COLS; j++){
			scanf("%d", &a);
			S->cells[i][j] = a;
		}
	}
}

//input map tieu chuan
void inputSu2(Sudoku *S){
	FILE *f;
	freopen("inputSu2.txt","r",stdin);
	initSudoku(S);
	int i,j,a;
	for(i = 0; i < NB_ROWS; i++){
		for(j = 0; j < NB_COLS; j++){
			scanf("%d", &a);
			S->cells[i][j] = a;
		}
	}
}


//input map kho
void inputSu3(Sudoku *S){
	FILE *f;
	freopen("inputSu3.txt","r",stdin);
	initSudoku(S);
	int i,j,a;
	for(i = 0; i < NB_ROWS; i++){
		for(j = 0; j < NB_COLS; j++){
			scanf("%d", &a);
			S->cells[i][j] = a;
		}
	}
}

//transform tu Sudoku sang Ca the
Chromosome RootChromosome(Sudoku S){
	Chromosome C;
	int i, j;
	int g;
	int counti = 0;
	int countj = 0;
	int k;
	for(i = 0; i < NB_ROWS; i++){
		if(counti == ARS){
			counti = 0;
		}
		for(j = 0; j < NB_COLS; j++){
			g = (i/ARS)*ARS + j/ARS;
			if(countj == ARS){
				k = counti * ARS;
				countj = 0;
			}
			C.gen[g].allele[k] = S.cells[i][j];
			if(C.gen[g].allele[k] != 0)
				C.gen[g].encode[k] = 1;
			else C.gen[g].encode[k] = 0;
			k++;
			countj++;
		}
		counti++;
	}
	return C;
}


//tao 1 ca the ngau nhien (co tinh fitness)
Chromosome randomC(Chromosome root){
	Chromosome C = root;
	int value[MAX_GEN];
	int i,j,k,t;
	for(i = 0; i < MAX_GEN; i++){
		//gan cac gia tri tu 1-9 chua duoc dien = 1
		for(t=1;t<=MAX_GEN;t++){
			value[t] = 1;
		}
		//kiem tra o vuong 3x3 xem gia tri (1->9) 
		//da duoc dien vo chua
		//neu roi thi gan value tai gia tri do bang 0 de khong dien lai trong o vuong 3x3
		for(j=0; j<MAX_GEN; j++){
			if(C.gen[i].allele[j] != 0){
				value[C.gen[i].allele[j]] = 0;
			}
		}
		//dien random vô ô vuông 3x3
		//chi dien vo ô co value = 1 va khi o vuong 3x3 chua duoc random het
		for(j=0; j<MAX_GEN; j++){
			while(C.gen[i].allele[j] == 0){  //kiem tra xem cac o vuong da duoc dien du chua
				k = random(1,9);
				if(value[k] == 1){
					C.gen[i].allele[j] = k;
					value[k] = 0;  //sau khi dien xong gia tri k thi gan value = 0 (xem nhu da su dung gia tri do roi)
				}
			}
		}
	}
	//va cuoi cung tinh do fitness cho ca the vua random ra
	fitness(&C);
	return C;
}

//kiem tra 2 ca the co giong nhau khong
int checkC(Chromosome C,Chromosome C1){
	int i,j;
	for(i=0;i< MAX_GEN;i++){
		for(j= 0;j< MAX_GEN;j++){
			if(C.gen[i].allele[j] != C1.gen[i].allele[j])
				return 1;  //neu 2 ca the khac nhau thi return ngay lap tuc
		}
	}
	return 0;
}

//them ca the vao quan the (dieu kien: ca the moi khong ton tai trong quan the thi moi duoc them)
int add_pop(Population *pop, Chromosome C){
	int i;
	int flag;
	for(i = 0; i < pop->popsize; i++){
		//kiem tra xem ca the moi C da ton tai trong quan the chua
		//neu flag=1 nghia la chua thi duoc phep them vao quan the
		flag = checkC(C, pop->chromosome[i]); 
		if(flag == 0){	
			break;	
		}	
	}
	if(flag){
		pop->chromosome[pop->popsize++] = C;
		return 1;		
	}
	return 0;
}

//hoan vi
void swap(Chromosome *a, Chromosome *b){
	Chromosome temp;
	temp = *a;
	*a = *b;
	*b = temp;
}


//sap xep tang dan
void sort(Population *P){
    int i,j;
    for(i=0; i < P->popsize-1; i++){
        for(j=i+1; j < P->popsize; j++){
            if(P->chromosome[i].fitness >= P->chromosome[j].fitness) 
				swap(&P->chromosome[i], &P->chromosome[j]);
        }
    }
}



//Khoi tao quan the  (voi so luong ca the duoc chi dinh)
void init_Population(Population *pop, int size, Chromosome root){ 
	pop->popsize = 0;
	Chromosome C;
	int i;
	//lap cho den khi so luong ca the trong quan the = voi so luong ca the chi dinh
	while(pop->popsize < size){
		//tao ca the ranom 
		C = randomC(root);
//		fitness(&C);
		
		//chi ca the nao co suc khoe (fitness) <= 40 thi moi them vao quan the
		if(C.fitness <= 40){
			add_pop(pop, C);			
		} 
	}
// Kich thuoc quan the: pop_size
}

//in ra ca the
void testPrint(Chromosome C){
	int i,j;
	printf("Chromosome \n");
	for(i=0;i<MAX_GEN;i++){
		for(j=0;j<MAX_GEN;j++){
			printf("%d  ", C.gen[i].allele[j]);
		}
		printf("\n");
	}
//	printf("\n Encode \n");
//	for(i=0;i<MAX_GEN;i++){
//		for(j=0;j<MAX_GEN;j++){
//			printf("%d  ", C.gen[i].encode[j]);
//		}
//		printf("\n");
//	}
}

//xoa ca the trong quan the (tai vi tri chi dinh pos)
void DeleteChromosome(Population *p, int pos){
	int i, j;
	for(i=pos-1; i<p->popsize-1; i++)
		p->chromosome[i] = p->chromosome[i+1];
	p->popsize--;	
}


//chon so luong(resize) ca the theo chi dinh (vd: quan the co 50 ca the, minh co the chon lai voi resize = 30) 
Chromosome Slection_chromosomes(Population *P, int resize){ // Chon loc ca the
	P->chromosome[0].fitness += 0.91;
	while(P->popsize > resize){
		DeleteChromosome(P, P->popsize);	  //xoa ca the cuoi cung(fitness lon nhat)
	}
	//cuoi cung tra ve ca the manh nhat (fitness nho nhat)
	return P->chromosome[0]; 	
//	P->popsize = resize;
}

//chia lam 3 phan (a = 0, 1, 2)
float rulerow(Chromosome C, int a){
	Sudoku s;
	transform(C, &s);
	float count = 0.0;
	int flag;
	int k,i,j;
	//tuong tu f_row()
	
	if(a == 0){  
		for(i = 0; i < 3; i++){  // a = 0 tinh fitness cho 3 hang dau (hang` 0 -> 2)
			for(j = 0; j < NB_COLS; j++){
				flag = 0;
				for(k = j; k < NB_COLS; k++){
					if(s.cells[i][k] == s.cells[i][j] && k != j)				
						flag = 1;
				}
				if(flag)
					count++;
			}
		
		}	
	}
	else if(a == 1){
		for(i = 3; i < 6; i++){		// a = 1 tinh fitness cho 3 hang dau (hang` 3 -> 5)
			for(j = 0; j < NB_COLS; j++){
				flag = 0;
				for(k = j; k < NB_COLS; k++){
					if(s.cells[i][k] == s.cells[i][j] && k != j)				
						flag = 1;
				}
				if(flag)
					count++;
			}
		}
	}	
	else if( a== 2){
		for(i = 6; i < 9; i++){ 	// a = 2 tinh fitness cho 3 hang dau (hang` 6 -> 8)
			for(j = 0; j < NB_COLS; j++){
				flag = 0;
				for(k = j; k < NB_COLS; k++){
					if(s.cells[i][k] == s.cells[i][j] && k != j)				
						flag = 1;
				}
				if(flag)
					count++;
			}
		}
	}
	//tra ve do fitness cua phan a truyen vo
	return count;
}


//ham lai tra ve ca the con
Chromosome Crossover_row(Chromosome Cx, Chromosome Cy){
	Chromosome C; //ca the con
	int i;
	for(i = 0; i < 3; i++){
		if(i == 0){
			if(rulerow(Cx, i) > rulerow(Cy, i) ){
				C.gen[0] = Cy.gen[0];
				C.gen[1] = Cy.gen[1];
				C.gen[2] = Cy.gen[2];			
			}
			else{
				C.gen[0] = Cx.gen[0];
				C.gen[1] = Cx.gen[1];
				C.gen[2] = Cx.gen[2];					
			}			
		}
		else if(i == 1){
			if(rulerow(Cx, i) > rulerow(Cy, i) ){
				C.gen[3] = Cy.gen[3];
				C.gen[4] = Cy.gen[4];
				C.gen[5] = Cy.gen[5];			
			}
			else{
				C.gen[3] = Cx.gen[3];
				C.gen[4] = Cx.gen[4];
				C.gen[5] = Cx.gen[5];					
			}			
		}
		else if(i == 2){
			if(rulerow(Cx, i) > rulerow(Cy, i) ){
				C.gen[6] = Cy.gen[6];
				C.gen[7] = Cy.gen[7];
				C.gen[8] = Cy.gen[8];			
			}
			else{
				C.gen[6] = Cx.gen[6];
				C.gen[7] = Cx.gen[7];
				C.gen[8] = Cx.gen[8];					
			}			
		}			
	}
	fitness(&C);
	return C;
}

//giong rulerow 
//a chia lam 3 phan(a = 0,1,2)
float rulecol(Chromosome C, int a){
	Sudoku s;
	transform(C, &s);
	float count = 0.0;
	int flag;
	int k,i,j;
	if(a == 0){
		for(j = 0; j < 3; j++){
			for(i = 0; i < NB_ROWS; i++){
				flag = 0;
				for(k = i; k < NB_ROWS; k++){
					if(s.cells[i][j] == s.cells[k][j] && k != i)					
					flag = 1;		
				}
				if(flag)
					count++;
			}
		}
	}
	else if(a == 1){
		for(j = 3; j < 6; j++){
			for(i = 0; i < NB_ROWS; i++){
				flag = 0;
				for(k = i; k < NB_ROWS; k++){
					if(s.cells[i][j] == s.cells[k][j] && k != i)					
					flag = 1;		
				}
				if(flag)
					count++;
			}
		}
	}
	else if(a == 2){
		for(j = 6; j < 9; j++){
			for(i = 0; i < NB_ROWS; i++){
				flag = 0;
				for(k = i; k < NB_ROWS; k++){
					if(s.cells[i][j] == s.cells[k][j] && k != i)					
					flag = 1;		
				}
				if(flag)
					count++;
			}
		}
	}	
	//tra ve do fitness cua phan a truyen vo
	return count;
}


//giong Crossover_row
Chromosome Crossover_col(Chromosome Cx, Chromosome Cy){
	Chromosome C;
	int i;
	for(i = 0; i < 3; i++){
		if(i == 0){
			if(rulecol(Cx, i) > rulecol(Cy, i) ){
				C.gen[0] = Cy.gen[0];
				C.gen[1] = Cy.gen[1];
				C.gen[2] = Cy.gen[2];			
			}
			else{
				C.gen[0] = Cx.gen[0];
				C.gen[1] = Cx.gen[1];
				C.gen[2] = Cx.gen[2];					
			}			
		}
		else if(i == 1){
			if(rulecol(Cx, i) > rulecol(Cy, i) ){
				C.gen[3] = Cy.gen[3];
				C.gen[4] = Cy.gen[4];
				C.gen[5] = Cy.gen[5];			
			}
			else{
				C.gen[3] = Cx.gen[3];
				C.gen[4] = Cx.gen[4];
				C.gen[5] = Cx.gen[5];					
			}			
		}
		else if(i == 2){
			if(rulecol(Cx, i) > rulecol(Cy, i) ){
				C.gen[6] = Cy.gen[6];
				C.gen[7] = Cy.gen[7];
				C.gen[8] = Cy.gen[8];			
			}
			else{
				C.gen[6] = Cx.gen[6];
				C.gen[7] = Cx.gen[7];
				C.gen[8] = Cx.gen[8];					
			}			
		}			
	}
	fitness(&C);
	return C;	
}

//


void confirm_pos(Chromosome C, int t, int *x, int *y){               //không can su dung
	switch (t) {
		case 0: {
			*x = 0;
			*y = 0;
			break;
		}
		case 1: {
			*x = 0;
			*y = 3;
			break;
		}
		case 2: {
			*x = 0;
			*y = 6;
			break;
		}
		
		case 3: {
			*x = 3;
			*y = 0;
			break;
		}
		case 4: {
			*x = 3;
			*y = 3;
			break;
		}
		case 5: {
			*x = 3;
			*y = 6;
			break;
		}
		
		case 6: {
			*x = 6;
			*y = 0;
			break;
		}
		case 7: {
			*x = 6;
			*y = 3;
			break;
		}
		case 8: {
			*x = 6;
			*y = 6;
			break;
		}
		default:{
			break;
		}
	}
}

float fitness_gen(Chromosome C, int t){								//không can su dung
	int i,j,X,Y, key_X, key_Y, areaX, areaY;
	Sudoku S;
	transform(C,&S);
	confirm_pos(C,t,&areaX,&areaY);
	int e;
	float sum[9];
	for(e=0;e<9;e++){
		sum[e] = 0.0;
	}

	
	key_X = areaX;
	key_Y = areaY;
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			X = areaX + i;
			Y = areaY + j;
			
			
			areaX = areaX + i;
			areaY = areaY + j;
			//di len
			while(areaX > 0){
				if((S.cells[X][Y] == S.cells[areaX - 1][areaY])  && ((X != areaX - 1) || (Y != areaY)) ){
					sum[S.cells[X][Y]] += 1;
					areaX -= 1;
				}
				else areaX -= 1;
			}
			
			
			areaX = key_X;
			areaY = key_Y;
			areaX = areaX + i;
			areaY = areaY + j;
			//di xuong
			while(areaX < 8){
				if((S.cells[X][Y] == S.cells[areaX + 1][areaY])  && ((X != areaX + 1) || (Y != areaY)) ){
					sum[S.cells[X][Y]] += 1;
					areaX += 1;
				}
				else areaX += 1;
			}
			
			areaX = key_X;
			areaY = key_Y;
			areaX = areaX + i;
			areaY = areaY + j;
			//sang phai
			while(areaY < 8){
				if((S.cells[X][Y] == S.cells[areaX][areaY + 1])  && ((X != areaX) || (Y != areaY + 1)) ){
					sum[S.cells[X][Y]] += 1;
					areaY += 1;
				}
				else areaY += 1;
			}
			
			areaX = key_X;
			areaY = key_Y;
			areaX = areaX + i;
			areaY = areaY + j;
			//sai trai
			while(areaY > 0){
				if((S.cells[X][Y] == S.cells[areaX][areaY - 1])  && ((X != areaX) || (Y != areaY - 1)) ){
					sum[S.cells[X][Y]] += 1;
					areaY -= 1;
				}
				else areaY -= 1;
			}
			areaX = key_X;
			areaY = key_Y;
		}
	}
	float res=0;
	for(e=0; e<9; e++){
		res = res + sum[e];
	}
	return res;
}



//hoan vi 2 allele trong 1 gen voi nhau 
void swap_in_Gen(Gen *G){
	int a, b; //2 allele ngau nhien
	do {
		a = random(0,8);		
		b = random(0,8);
	}
	while (a==b || G->encode[a]==1 || G->encode[b]==1);	//lap voi dk(a == b thi lap lai), cac gia tri cung tu input khong the bi hoan vi
	int t;
	//hoan vi 2 allele
	t = G->allele[a];
	G->allele[a] = G->allele[b];
	G->allele[b] = t;
}

void Mutation(Chromosome *C, int a){
	swap_in_Gen(&C->gen[a]);
}

float powergen(Chromosome C, int i){
	int x = i / ARS ;
	int y = i % ARS ;
	return rulerow(C, x) + rulecol(C, y);
}

//phuong phap lai 2 ca the theo powergen
Chromosome Crossover_G(Chromosome Cx, Chromosome Cy){
	Chromosome C;
	int i;
	for(i = 0; i < MAX_GEN; i++){
		if(powergen(Cx, i) > powergen(Cy, i))
			C.gen[i] = Cy.gen[i];
		else 
			C.gen[i] = Cx.gen[i];
	}
	fitness(&C);
	return C;
}

int Crossover_chromosomes(Population *P, Chromosome Cx, Chromosome Cy){ //Lai 2 hay nhieu cap ca the	
	Chromosome tmp1, tmp2, tmp3;  //3 ca the con tuong ung voi 3 lan dot bien khac nhau
	Chromosome child1 = Crossover_row(Cx, Cy);
	if(child1.fitness == 0){  //neu child.fitness = 0 (GOAL) thi sort lai dua no len dau quan the roi return 1
		add_pop(P, child1);
		sort(P);
		printf("\nCrossover_row\n");
		return 1;
	}
	Chromosome child2 = Crossover_col(Cx, Cy);
	if(child2.fitness == 0){  //neu child.fitness = 0 (GOAL) thi sort lai dua no len dau quan the roi return 1
		add_pop(P, child2);
		sort(P);
		printf("\nCrossover_col\n");
		return 1;
	}
	Chromosome child3 = Crossover_G(Cx, Cy);
	if(child3.fitness == 0){  //neu child.fitness = 0 (GOAL) thi sort lai dua no len dau quan the roi return 1
		add_pop(P, child3);
		sort(P);
		printf("\nCrossover_G\n");
		return 1;
	}
	//neu child.fitness != 0 thi khong can sort lai
	add_pop(P, child1);
	add_pop(P, child2);
	add_pop(P, child3);
	int k;
	
	//lap k-max = 9  va i-max = 9  nghia la lap (9 x 9 = 81 lan)
	for(k = 0; k < 9; k++){
		int i = 0;				
		do{
			//gan lai cac ca the con vua lai cho cac tmp de dem di dot bien
			tmp1 = child1;
			tmp2 = child2;	
			tmp3 = child3;
			Mutation(&tmp1, i);		
			fitness(&tmp1);
			if(tmp1.fitness == 0){ //neu tmp.fitness = 0 (GOAL) thi sort lai dua no len dau quan the roi return 1
				add_pop(P, tmp1);
				sort(P);
				printf("\nmutation child1\n");
				return 1;
			}
			Mutation(&tmp2, i);	
			fitness(&tmp2);
			if(tmp2.fitness == 0){ //neu child.fitness = 0 (GOAL) thi sort lai dua no len dau quan the roi return 1
				add_pop(P, tmp2);
				sort(P);
				printf("\nmutation child2\n");
				return 1;
			}
			Mutation(&tmp3, i);	
			fitness(&tmp3);
			if(tmp3.fitness == 0){ //neu child.fitness = 0 (GOAL) thi sort lai dua no len dau quan the roi return 1
				add_pop(P, tmp3);
				sort(P);
				printf("\nmutation child3\n");
				return 1;
			}
			add_pop(P, tmp1);
			add_pop(P, tmp2);
			add_pop(P, tmp3);	
			i++;
		}while(i < 9);		
	}
	return 0;
}

//in ban do Sudoku
void printSudoku(Sudoku S){
	int i,j;
	printf("\nSudoku");
	printf("\n-------------------------------\n");
	for(i=0;i<NB_ROWS;i++){
		for(j=0;j<NB_COLS;j++){
			if(j==2)
				printf("%d | ",S.cells[i][j]);
			else if(j==0)
				printf("| %d  ",S.cells[i][j]);
			else if (j==5)
				printf("%d | ",S.cells[i][j]);
			else if (j==8) 
				printf("%d |",S.cells[i][j]);
			else printf("%d  ",S.cells[i][j]);
		}
		if(i==2)
			printf("\n-------------------------------\n");
		else if(i==5)
			printf("\n-------------------------------\n");
		else printf("\n");
	}
	printf("-------------------------------\n");
}

//tinh ti le giong nhau giua 2 ca the
float same(Chromosome Cx, Chromosome Cy){
	int i, j;
	float same = 0.0;
	int count = 0;
	for(i = 0; i < MAX_GEN; i++){
		for(j = 0; j < MAX_GEN; j++){
			//neu 2 allele cung vi tri bang nhau  THI` count++
			if(Cx.gen[i].allele[j] == Cy.gen[i].allele[j]){
				count++;
			}
		}
	}
	return count/81.0;  // lay count / cho tông? so ô trên map sudoku  => ti le giong nhau giua 2 ca the
}


Chromosome G_A(Population P, Chromosome root){
	srand((int)time(0));
	Chromosome C;
	Sudoku S;
	int i,k=0;
	Chromosome pivot;
	pivot.fitness = 999999.99;    //su dung de cho tam chap nhan ket qua
	while(1){
		k++;
		printf("\nlan thu k: %d\n",k);
		if(k==3){ // sau 3 the he k=3 khong tim thay ca the GOAL thi tra ve ca the tot nhat (tam chap nhan GOAL)
			if(pivot.fitness < P.chromosome[0].fitness)
				return pivot;
			else return P.chromosome[0];
		}
		
		if(pivot.fitness > P.chromosome[0].fitness){
			pivot.fitness = P.chromosome[0].fitness;
		}
		pivot = P.chromosome[0];
		init_Population(&P, 100, root); //khoi tao
		sort(&P);
		
		//neu khoi tao MAY MAN NHAT se ra duoc ca the 0 la GOAL  (Rat rat rat rat... HIEM)
		if(P.chromosome[0].fitness < 1){
			return P.chromosome[0];
		}	
		i  = 0;
		
		while(i <= 100){   //i la the he
			printf("%d %.2f %d\n", i, P.chromosome[0].fitness, P.popsize);		
	
			int j = 1;    //j = 1 boi vi sau khi Slection_chromosomes() xong se tra ve ca the dau tien trong quan the
			int parent = 0;
			float s = 0.98;	
			//chon ra resize=61 trong 100 ca the cua 1 quan the		
			C = Slection_chromosomes(&P, 61);		//tra ve ca the dau tien cua quan the (tot nhat)		
			while(j < P.popsize){
				if(same(C, P.chromosome[j]) <= s){ //neu ti le giong nhau giua 2 ca the (C va P.[j]) trong muc do cho phep cua s
	//				printf("same 0, %d: %.3f\n",j, same(C, P.chromosome[j]));
					
					//Crossover_chromosomes = Crossover_row + Crossover_col + Crossover_G 
					if(Crossover_chromosomes(&P,C, P.chromosome[j]) == 1){  //tra ve 1 nghia la da tim dc GOAL
						printf("the he cross : %d \n",i+1);
						return P.chromosome[0];
					}
					parent++;
					s-= 0.007;			//moi lan lai xong phai giam s di
				}
				
				if(parent == 11){	//chi lay 11 cap cha me (nghia la lai 11 lan) 
					break;
				}
				j++;					
			}
			sort(&P);			

			i++;
		}	
	}
}

void loading(){
	int i,j;
	char a = 177, b = 219;
	printf("\t\t\t\tLoading...\n");
	printf("\t\t\t");
	for(i=1;i<=25;i++){
		printf("%c",a);
	}
	printf("\r");
	printf("\t\t\t");
	for(i=1;i<=25;i++){
		printf("%c",b);
		Sleep(70);
	}
}

int main(){
	Population P;
	Chromosome root;
	Sudoku S;
	
	inputSu1(&S);	   //map de
//	inputSu2(&S);	  //map tieu chuan
//	inputSu3(&S);    //map kho

	
	
	root = RootChromosome(S);
	
	Chromosome C;
	printSudoku(S);
	C = G_A(P, root);
	transform(C, &S);
	loading();
	printSudoku(S);
	fitness(&C);
	printf("%.2f ", C.fitness);
	
	
	
//	inputSu1(&S);
//	root = RootChromosome(S);
//	init_Population(&P,3,root);
//	
//	int i;
////	root = RootChromosome(S);
//	for(i=0;i<P.popsize;i++){
//		transform(P.chromosome[i], &S);
//		printSudoku(S);
//		fitness(&P.chromosome[i]);
//		printf("fitness: %.2f\n\n",P.chromosome[i].fitness);
//	}
	
	
	return 0;
}
