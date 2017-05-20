//判断AI选择的最高分点是否是禁手
#include<stdio.h>
#include "My_head.h"
//计算落子后各个方向的情况
int bcount_x(int x,int y,int p);
int bcount_y(int x,int y,int p);
int bcount_LtoR(int x,int y,int p);
int bcount_RtoL(int x,int y,int p);
extern int aRecordBoard[SIZE][SIZE];

int MyBan(int x,int y,int player){
	//p代表玩家
	aRecordBoard[x][y]=player;         //先试探落子
	int ban_value=0;
	int p=player;

	int x_number,y_number,LtoR_number,RtoL_number;

	//记录在该点落子后各个方向的棋子数目
	x_number=bcount_x(x,y,p);
	y_number=bcount_y(x,y,p);
	LtoR_number=bcount_LtoR(x,y,p);
	RtoL_number=bcount_RtoL(x,y,p);

	if(x_number>5||y_number>5||LtoR_number>5||RtoL_number>5){   //长连禁手
		ban_value=1;
		aRecordBoard[x][y]=0;       //恢复之前的棋盘值
		return ban_value;
	}

	if((x_number==3&&y_number==3)||(x_number==3&&LtoR_number==3)||(x_number==3&&RtoL_number==3)||(y_number==3&&LtoR_number==3)||(y_number==3&&RtoL_number==3)||(LtoR_number==3&&RtoL_number==3)){
		ban_value=1;                                      //33禁手
		aRecordBoard[x][y]=0;
		return ban_value;
	}

	if((x_number==4&&y_number==4)||(x_number==4&&LtoR_number==4)||(x_number==4&&RtoL_number==4)||(y_number==4&&LtoR_number==4)||(y_number==4&&RtoL_number==4)||(LtoR_number==4&&RtoL_number==4)){
		ban_value=1;                                 //44禁手
		aRecordBoard[x][y]=0;
		return ban_value;
	}
	//非禁手，返回0
	aRecordBoard[x][y]=0;
	return ban_value;
}
	
