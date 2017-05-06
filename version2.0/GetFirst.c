#include<time.h>
#include<stdio.h>
#include<stdlib.h>
void GetFirst(int *x,int *y){
	int i,j;
	srand((unsigned)time(NULL));
	*x=6+rand()%3;
	*y=6+rand()%3;
	return;
}
