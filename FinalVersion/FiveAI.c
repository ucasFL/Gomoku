//AI落子，具体算法是扫描棋盘上所有点，计算每个点的分值，单点分值计算为包含该点的所有五元组的分之和，然后在分值最高的点落子
#include "My_head.h"

//记录每个点的得分
long Score[SIZE][SIZE];

//计算总得分
long Sum(int x,int y,int p);

//分别计算四个方向得分
long count_x(int x,int y,int p);
long count_y(int x,int y,int p);
long count_UtoD(int x,int y,int p);
long count_DtoU(int x,int y,int p);

//计算相邻五个点情况
long mark_x(int x,int y,int p);
long mark_y(int x,int y,int p);
long mark_UtoD(int x,int y,int p);
long mark_DtoU(int x,int y,int p);

//将子数转化为分数
long toScore(int my,int opp);

//找最大分位置
void GreatScore(int *x,int *y,int p);

//判断若在该点落子是否禁手
int MyBan(int x,int y,int p);

int Info_x,Info_y;
extern int aRecordBoard[SIZE][SIZE];

void GetInput(int *x,int *y,int p){
	int i,j,k;
	//扫描整个棋盘计算出每个点的分
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){

			if(aRecordBoard[i][j]!=0)
			  Score[i][j]=-1;              //已经被落子的点分为-1
			
			else
			  Score[i][j]=Sum(i,j,p);       //空着的点调用函数计算分值
		}
	}

	GreatScore(&Info_x,&Info_y,p);         //找出最高分
	*x=Info_x;
	*y=Info_y;
	return;
}

//计算单点得分
long Sum(int x,int y,int p){
	long direc[4];

	direc[0]=count_x(x,y,p);        //计算4个方向的分
	direc[1]=count_y(x,y,p);
	direc[2]=count_UtoD(x,y,p);
	direc[3]=count_DtoU(x,y,p);
	
	return direc[0]+direc[1]+direc[2]+direc[3];           //将4个方向的分之和返回
}

//计算水平方向所有五元组得分之和
long count_x(int x,int y,int p){

	long grade[5];
	int i,j=0;

	for(i=y-4;i<=y;i++)          //每个点包含在五个五元组中，计算每个五元组的得分，然后加和返回
		grade[j++]=mark_x(x,i,p);
	
	return grade[0]+grade[1]+grade[2]+grade[3]+grade[4];
}

//计算竖直方向所有五元组得分之和
long count_y(int x,int y,int p){
	
	long grade[5];
	int i,j=0;
	
	for(i=x-4;i<=x;i++)
	  grade[j++]=mark_y(i,y,p);
	
	return grade[0]+grade[1]+grade[2]+grade[3]+grade[4];
}

//计算从左上到右下方向所有五元组的得分之和
long count_UtoD(int x,int y,int p){

	long grade[5];
	int i,j,k=0;
	
	for(i=x-4,j=y-4;i<=x,j<=y;i++,j++)
	  grade[k++]=mark_UtoD(i,j,p);
	
	return grade[0]+grade[1]+grade[2]+grade[3]+grade[4];
}

//计算从左下到右上方向所有五元组的得分之和
long count_DtoU(int x,int y,int p){

	long grade[5];
	int i,j,k=0;
	
	for(i=x+4,j=y-4;i>=x,j<=y;i--,j++)
	  grade[k++]=mark_DtoU(i,j,p);
	
	return grade[0]+grade[1]+grade[2]+grade[3]+grade[4];
}

//计算水平五元组得分
long mark_x(int x,int y,int p){
	
	if(y<0||(y+4)>=SIZE)
	  return NO;            //超出边界，说明不是五元组
	
	else{                    //统计五元组中自己的子数和对方的字数，不用去管具体是什么格局
		
		int i,my=0,opp=0;
		for(i=y;i<=(y+4);i++){
		
			if(aRecordBoard[x][i]==p)
			  my++;
			if(aRecordBoard[x][i]!=p&&aRecordBoard[x][i]!=0)
			  opp++;
		}
		  
		return toScore(my,opp);
	}
}
//计算竖直方向五元组得分
long mark_y(int x,int y,int p){
	
	if(x<0||(x+4)>=SIZE)
	  return NO;    //同上
	else{
	
		int i,my=0,opp=0;
		for(i=x;i<=(x+4);i++){
		
			if(aRecordBoard[i][y]==p)
			  my++;
			
			if(aRecordBoard[i][y]!=0&&aRecordBoard[i][y]!=p)
			  opp++;
		}
		  
		return toScore(my,opp);
	}
}
//计算左上到右下方向五元组得分
long mark_UtoD(int x,int y,int p){
	
	if(x<0||y<0||(x+4)>=SIZE||(y+4)>=SIZE)
	  return NO;          //同上
	else{
		
		int i,j,my=0,opp=0;
		for(i=x,j=y;i<=(x+4),j<=(y+4);i++,j++){
		
			if(aRecordBoard[i][j]==p)
			  my++;
		
			if(aRecordBoard[i][j]!=p&&aRecordBoard[i][j]!=0)
			  opp++;
		}
		
		return toScore(my,opp);
	}
}
//计算从左下到右上方向五元组得分
long mark_DtoU(int x,int y,int p){
	
	if(x>=SIZE||(x-4)<0||y<0||(y+4)>=SIZE)
	  return NO;             //同上
	else{

		int i,j,my=0,opp=0;
		for(i=x,j=y;i>=(x-4),j<=(y+4);i--,j++){
		
			if(aRecordBoard[i][j]==p)
			  my++;
			if(aRecordBoard[i][j]!=p&&aRecordBoard[i][j]!=0)
			  opp++;
		}
		
		return toScore(my,opp);
	}
}
//将子数转化为得分
long toScore(int my,int opp){
	
	if(my!=0&&opp!=0)
	  return PU;     //既有自己的子又有对方的子，五元组被"污染"，返回0
	
	else if(opp==0){                  //对方子为0,只有自己的子，根据子数返回相应分值
		switch(my){
			case 1:return M1;
				   break;
			case 2:return M2;
				   break;
			case 3:return M3;
				   break;
			case 4:return M4;
				   break;
			default:return VO;
		}
	}
	
	else{                            //自己子数为0
		switch(opp){
			case 1:return O1;
				   break;
			case 2:return O2;
				   break;
			case 3:return O3;
				   break;
			case 4:return O4;
				   break;
			default:return VO;
		}
	}
}
//计算最高分
void GreatScore(int *x,int *y,int p){

	int Great_x,Great_y;
	int i,j;
	
	for(;;){
		int Great_Score=-1;      //初始时将最高分赋值为-1　
		for(i=0;i<SIZE;i++){
			for(j=0;j<SIZE;j++){        //双层循环找最高分

				if(Score[i][j]>Great_Score){
					Great_Score=Score[i][j];
					Great_x=i;
					Great_y=j;
				}
			}
		}
		//判断是否是先手
		if(p==FIRST_PLAYER){
			int Judge;
			Judge=MyBan(Great_x,Great_y,p);     //判断是否是禁手
			if(Judge==1){
				Score[Great_x][Great_y]=-2;      //若是禁手，把该点的分赋值为-2，然后再去找第二高的分
				continue;
			}

			else{
				*x=Great_x;
				*y=Great_y;
				return;
			}
		}
		//后手
		else{
			*x=Great_x;
			*y=Great_y;
			return;
		}
	}
}
