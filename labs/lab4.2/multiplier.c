#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NROWS 2000
#define NCOLS 2000
#define NUM_THREADS 20
#define NUM_CYCLES NROWS/NUM_THREADS
#define PATH_MA "matA.dat"
#define PATH_MB "matB.dat"
#define TOTALN NCOLS*NROWS
#define NCHAR 255

int NUM_BUFFERS; 
long **buffers; 
long *result; 
long *mat4m; 
long *mat_2k; 
pthread_mutex_t *mutexes; 
long *mat1; 
long *mat2; 

long* readMatrix(char*); 
long* getColumn(int, long*); 
long* getRow(int, long*); 
int getLock(void); 
int releaseLock(int); 
long dotProduct(long *vec1, long *vec2); 
long *multiply(long *matA, long *matB); 
int saveResultMatrix(long  * result); 
void *helper(void* row); 

int main(int argc, char **argv){
    initLogger("stdout"); 
    if(argc !=3){
        errorf("Invalid format.\nIt must be ./multipler -n NUMBUFFERS\n"); 
        return -1; 
    } else if(strcmp(argv[1],"-n")!=0){
        errorf("Invalid format.\nIt must be ./multipler -n NUMBUFFERS\n"); 
        return -1; 
    }
	NUM_BUFFERS=atoi(argv[2]); 
    if(NUM_BUFFERS<1){
        errorf("Invalid format.\nNUMBUFFERS must be a valid number\n"); 
        return -1; 
    }
	long *matA,*matB; 
	matA=malloc(TOTALN*sizeof(long)); 
	mat4m=malloc(TOTALN*sizeof(long)); 
	matB=malloc(TOTALN*sizeof(long)); 
	mat1=malloc(TOTALN*sizeof(long)); 
	mat2=malloc(TOTALN*sizeof(long)); 
	result=malloc(TOTALN*sizeof(long)); 
	mat_2k=malloc(NROWS*sizeof(long)); 
	buffers=malloc(NUM_BUFFERS*sizeof(long*)); 
	mutexes=malloc(NUM_BUFFERS*sizeof(pthread_mutex_t)); 
    int i; 
	for(i=0; i<NUM_BUFFERS; i++){
		buffers[i]=malloc(NROWS*sizeof(long)); 
	}
	memcpy(matA,readMatrix(PATH_MA),TOTALN*sizeof(long)); 
	memcpy(matB,readMatrix(PATH_MB),TOTALN*sizeof(long)); 
	multiply(matA,matB); 
	memcpy(mat4m,result,TOTALN*sizeof(long)); 
	saveResultMatrix(mat4m); 
	pthread_mutex_destroy(mutexes); 
	pthread_mutex_destroy(mutexes); 
}

long * readMatrix(char *filename){
	int j; 
	FILE *fp; 
	char buff[NCHAR]; 
	fp=fopen(filename, "r"); 
	for(j=0; j<TOTALN; j++){
		fgets(buff,NCHAR,(FILE*)fp); 
		mat4m[j]=(long)atoi(buff); 
	}
	fclose(fp); 
	return mat4m; 
}

long * getColumn(int col, long * mat){	
	int j; 
	for(j=0; j<NCOLS; j++)mat_2k[j]=mat[j*NCOLS+col]; 
	return(mat_2k); 
}

long * getRow(int row, long * mat){
	int j; 
	for(j=0; j<NROWS; j++)mat_2k[j]=mat[j+row*NROWS]; 
	return(mat_2k); 
}

int getLock(){
	int jl; 
	for(jl=0; jl<NUM_BUFFERS; jl++){
		if((pthread_mutex_trylock(&mutexes[jl]))==0){
			return jl; 
		}
	}
	return -1; 
}

int releaseLock(int a){
	if((pthread_mutex_unlock(&mutexes[a]))==0)
		return 0; 
	return -1; 	
}

long dotProduct(long * vec1, long * vec2){
	int i; 
	long prod; 
	prod=0; 
	for(i=0; i<NROWS; i++)prod+=vec1[i]*vec2[i]; 
	return prod; 
}

long * multiply(long * matA, long * matB){
	int j,lim,k; 
	pthread_t tid [NROWS]; 
	pthread_attr_t attr;  		
	pthread_attr_init(&attr); 
	memcpy(mat1,matA,TOTALN*sizeof(long)); 
	memcpy(mat2,matB,TOTALN*sizeof(long)); 
	lim=0; 
	k=0; 
	do{
		for (j=0;  j<NUM_THREADS;  j++){ 
			pthread_create(&tid[j],&attr,helper,(void*)k); 
			k++; 
		}
		for (j=0;  j <NUM_THREADS;  j++){ 
			pthread_join(tid[j], NULL); 
		}
	}while(lim++<(NROWS/NUM_THREADS)-1); 
	free(mat1); 
	free(mat2); 
	return 0; 
}

int saveResultMatrix(long *result){
	int i; 
	FILE *fp=fopen("result.dat","w"); 
	for(i=0; i<TOTALN; i++){
		fprintf(fp,"%ld\n",result[i]); 
	}
	fclose(fp); 
	return 0; 
}

void * helper(void *param){	
	int mutex_id,par; 
    int i,j,k; 
	while((mutex_id=getLock())==-1); 
	long *row,*col; 
	par=(int) param; 
	row=malloc(NROWS*sizeof(long)); 
	col=malloc(NROWS*sizeof(long)); 
	memcpy(row,getRow(par,mat1),NROWS*sizeof(long)); 
	for(i=0; i<NROWS; i++){
		memcpy(col,getColumn(i,mat2),NROWS*sizeof(long)); 
		buffers[mutex_id][i]=dotProduct(row,col); 
	}
	for(j=0; j<NROWS; j++){
		result[NROWS*par+j]=buffers[mutex_id][j]; 
	}
	free(row); 
	free(col); 
	releaseLock(mutex_id); 
	pthread_exit(0); 
}
