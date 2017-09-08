//胜负判断函数
#include<stdio.h>
#include "my_header.h"
int judge_x(int x,int y,int p);
int judge_y(int x,int y,int p);
int judge_LtoR(int x,int y,int p);
int judge_RtoL(int x,int y,int p);
int win_judge(int x_now,int y_now,int player){
	//参数p代表玩家
	extern int aRecordBoard[SIZE][SIZE];
	int win_value;
	int x,y;
	int p=player;
	x=x_now,y=y_now;

	int x_number,y_number,LtoR_number,RtoL_number;
	
	//记录各个方向的棋子数目
	x_number=judge_x(x,y,p);
	y_number=judge_y(x,y,p);
	LtoR_number=judge_LtoR(x,y,p);
	RtoL_number=judge_RtoL(x,y,p);
	
	//计算各方向棋子数目
	if(x_number>=5||y_number>=5||LtoR_number>=5||RtoL_number>=5){
		win_value=1;
	}                                                  //判断是否达到胜利条件
	else{
               //判断是否平局或其他
		win_value=-1;
		int i,j;
		for(i=0;i<SIZE;i++){
			for(j=0;j<SIZE;j++){
				if(aRecordBoard[i][j]==0){
					win_value=0;
					break;
				}
			}
			if(win_value==0)
			  break;
		}
	}
	return win_value;
}
//////////////////////
//计算水平方向的棋子数目
int judge_x(int x,int y,int p){
	extern int aRecordBoard[SIZE][SIZE];
	int x_count=1;
	int j;
	//往右数子
	for(j=y+1;j<SIZE&&aRecordBoard[x][j]==p;j++)
	  x_count++;
	//往左数子
	for(j=y-1;j>=0&&aRecordBoard[x][j]==p;j--)
	  x_count++;
	return x_count;
}
///////////////////////
//计算竖直方向的棋子数目
int judge_y(int x,int y,int p){
	extern int aRecordBoard[SIZE][SIZE];
	int y_count=1;
	int i;
	//往上数子
	for(i=x-1;i>=0&&aRecordBoard[i][y]==p;i--)
	  y_count++;
	//往下数子
	for(i=x+1;i<SIZE&&aRecordBoard[i][y]==p;i++)
	  y_count++;
	return y_count;
}
////////////////////////////////
//计算从左上到右下方向的棋子数目
int judge_LtoR(int x,int y,int p){
	extern int aRecordBoard[SIZE][SIZE];
	int LtoR_count=1;
	int i,j;
	//往左上数棋子数目
	for(i=x-1,j=y-1;i>=0&&j>=0&&aRecordBoard[i][j]==p;i--,j--)
	  LtoR_count++;
	//往右下数棋子数目
	for(i=x+1,j=y+1;i<SIZE&&j<SIZE&&aRecordBoard[i][j]==p;i++,j++)
	  LtoR_count++;
	return LtoR_count;
}
///////////////////////////////
//计算从左下到右上方向的棋子数目
int judge_RtoL(int x,int y,int p){
	extern int aRecordBoard[SIZE][SIZE];
	int RtoL_count=1;
	int i,j;
	//往右上数棋子
	for(i=x-1,j=y+1;i>=0&&j<SIZE&&aRecordBoard[i][j]==p;i--,j++)
	  RtoL_count++;
	//往左下数棋子数目
	for(i=x+1,j=y-1;i<SIZE&&j>=0&&aRecordBoard[i][j]==p;i++,j--)
	  RtoL_count++;
	return RtoL_count;
}
