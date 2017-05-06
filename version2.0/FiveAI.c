//AI落子
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

void GetInput(int *x,int *y,int p){
	extern int aRecordBoard[SIZE][SIZE];
	int i,j,k;
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			if(aRecordBoard[i][j]!=0)
			  Score[i][j]=-1;
			else
			  Score[i][j]=Sum(i,j,p);
		}
	}
	GreatScore(&Info_x,&Info_y,p);
	*x=Info_x;
	*y=Info_y;
	return;
}

//计算单点得分
long Sum(int x,int y,int p){
	long direc[4];
	direc[0]=count_x(x,y,p);
	direc[1]=count_y(x,y,p);
	direc[2]=count_UtoD(x,y,p);
	direc[3]=count_DtoU(x,y,p);
	return direc[0]+direc[1]+direc[2]+direc[3];
}
//计算水平方向所有五元组得分之和
long count_x(int x,int y,int p){
	long grade[5];
	int i,j=0;
	for(i=y-4;i<=y;i++)
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
	extern int aRecordBoard[SIZE][SIZE];
	if(y<0||(y+4)>=SIZE)
	  return NO;
	else{
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
	extern int aRecordBoard[SIZE][SIZE];
	if(x<0||(x+4)>=SIZE)
	  return NO;
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
	extern int aRecordBoard[SIZE][SIZE];
	if(x<0||y<0||(x+4)>=SIZE||(y+4)>=SIZE)
	  return NO;
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
	extern int aRecordBoard[SIZE][SIZE];
	if(x>=SIZE||(x-4)<0||y<0||(y+4)>=SIZE)
	  return NO;
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
	  return PU;
	else if(opp==0){
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
	else{
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
	extern long Score[SIZE][SIZE];
	int Great_x=0,Great_y=0;
	int i,j;
	for(;;){
		int Great_Score=-1;
		for(i=0;i<SIZE;i++){
			for(j=0;j<SIZE;j++){
				if(Score[i][j]>Great_Score){
					Great_Score=Score[i][j];
					Great_x=i;
					Great_y=j;
				}
			}
		}
		if(p==FIRST_PLAYER){
			int Judge;
			Judge=MyBan(Great_x,Great_y,p);
			if(Judge==1){
				Score[Great_x][Great_y]=-2;
				continue;
			}
			else{
				*x=Great_x;
				*y=Great_y;
				return;
			}
		}
		else{
			*x=Great_x;
			*y=Great_y;
			return;
		}
	}
}
