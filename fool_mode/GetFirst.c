#include<stdlib.h>
void GetFirst(int *x,int *y){
	int i,j;
	for(;;){
		i=rand()%15;
		j=rand()%15;
		if(i>5&&i<9&&j>5&&j<9){
			*x=i;
			*y=j;
			return ;
		}
	}
}
