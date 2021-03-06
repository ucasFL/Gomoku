//人玩家禁手判断函数
#include<stdio.h>
#include "My_head.h"
//计算落子后各个方向的情况
int bcount_x(int x,int y,int p);
int bcount_y(int x,int y,int p);
int bcount_LtoR(int x,int y,int p);
int bcount_RtoL(int x,int y,int p);
extern int aRecordBoard[SIZE][SIZE];

int Ban_Judge(int x_now,int y_now,int player){
	//p代表玩家
	int ban_value=0;
	int x,y;
	int p=player;
	x=x_now,y=y_now;

	int x_number,y_number,LtoR_number,RtoL_number;

	//记录各个方向的棋子数目
	x_number=bcount_x(x,y,p);
	y_number=bcount_y(x,y,p);
	LtoR_number=bcount_LtoR(x,y,p);
	RtoL_number=bcount_RtoL(x,y,p);

	if(x_number>5||y_number>5||LtoR_number>5||RtoL_number>5){   //长连禁手
		ban_value=1;
		return ban_value;
	}

	if((x_number==3&&y_number==3)||(x_number==3&&LtoR_number==3)||(x_number==3&&RtoL_number==3)||(y_number==3&&LtoR_number==3)||(y_number==3&&RtoL_number==3)||(LtoR_number==3&&RtoL_number==3)){
		ban_value=1;              //33禁手
		return ban_value;
	}

	if((x_number==4&&y_number==4)||(x_number==4&&LtoR_number==4)||(x_number==4&&RtoL_number==4)||(y_number==4&&LtoR_number==4)||(y_number==4&&RtoL_number==4)||(LtoR_number==4&&RtoL_number==4)){
		ban_value=1;           //44禁手
		return ban_value;
	}
	return ban_value;
}
//计算落子后水平方向情况
int bcount_x(int x,int y,int p){
	
	int Left_y,Right_y;
	int Left_Info,Right_Info;
	int x_count=1;
                                                                   
	for(Left_y=y-1;aRecordBoard[x][Left_y]==p&&Left_y>=0;Left_y--)       //数子
	  x_count++;
	for(Right_y=y+1;aRecordBoard[x][Right_y]==p&&Right_y<SIZE;Right_y++)
	  x_count++;
	
	if(Left_y>=0)    //名称太长，所以在不超出边界时用新的变量代替边缘值
	  Left_Info=aRecordBoard[x][Left_y];
	if(Right_y<SIZE)
	  Right_Info=aRecordBoard[x][Right_y];
	
	//活子情况
	if(Left_y>=0&&Right_y<SIZE&&Left_Info==0&&Right_Info==0){
	
		//隔空
		if(x_count==1&&((Left_y>=3&&aRecordBoard[x][Left_y-1]==p&&aRecordBoard[x][Left_y-2]==p&&aRecordBoard[x][Left_y-3]==0)||(Right_y<=12&&aRecordBoard[x][Right_y+1]==p&&aRecordBoard[x][Right_y+2]==p&&aRecordBoard[x][Right_y+3]==0)))
		  x_count+=2;
		
		//隔空
		if(x_count==2&&((Left_y>=2&&aRecordBoard[x][Left_y-1]==p&&aRecordBoard[x][Left_y-2]==0)||(Right_y<=13&&aRecordBoard[x][Right_y+1]==p&&aRecordBoard[x][Right_y+2]==0)))
		  x_count++;
		
		if(x_count==3)          //活3
		  return 3;
		if(x_count==4)          //活4
		  return 4;
	}
	
	//半活
	else if(((Left_y<0||(Left_y>=0&&Left_Info!=0))&&Right_y<SIZE&&Right_Info==0)||(Left_y>=0&&Left_Info==0&&(Right_y==SIZE||(Right_y<SIZE&&Right_Info!=0)))){
		if(x_count==4)
		  return 4;        //半活４
	}
	
	else
	  return 0;
}

//计算落子后竖直方向情况
int bcount_y(int x,int y,int p){

	int Up_x,Down_x;
	int Up_Info,Down_Info;
	int y_count=1;
	
	for(Up_x=x-1;aRecordBoard[Up_x][y]==p&&Up_x>=0;Up_x--)        //数子
	  y_count++;
	for(Down_x=x+1;aRecordBoard[Down_x][y]==p&&Down_x<SIZE;Down_x++)
	  y_count++;
	
	if(Up_x>=0)
	  Up_Info=aRecordBoard[Up_x][y];
	if(Down_x<SIZE)
	  Down_Info=aRecordBoard[Down_x][y];
	
	//活子
	if(Up_x>=0&&Down_x<SIZE&&Up_Info==0&&Down_Info==0){
	
		if(y_count==1&&((Up_x>=3&&aRecordBoard[Up_x-1][y]==p&&aRecordBoard[Up_x-2][y]==p&&aRecordBoard[Up_x-3][y]==0)||(Down_x<=12&&aRecordBoard[Down_x+1][y]==p&&aRecordBoard[Down_x+2][y]==p&&aRecordBoard[Down_x+3][y]==0)))
			  y_count+=2;      //隔空
		
		if(y_count==2&&((Up_x>=2&&aRecordBoard[Up_x-1][y]==p&&aRecordBoard[Up_x-2][y]==0)||(Down_x<=13&&aRecordBoard[Down_x+1][y]==p&&aRecordBoard[Down_x+2][y]==0)))
			  y_count++;       //隔空
		
		if(y_count==3)
		  return 3;          //活3
		if(y_count==4)
		  return 4;         //活4
		}
	
	//半活
	else if(((Up_x<0||(Up_x>=0&&Up_Info!=0))&&Down_x<SIZE&&Down_Info==0)||(Up_x>=0&&Up_Info==0&&(Down_x==SIZE||(Down_x<SIZE&&Down_Info!=0)))){
		if(y_count==4)
		  return 4;     //半活4
		}
	
	else
	  return 0;
}

//计算落子后左上到右下方向的情
int bcount_LtoR(int x,int y,int p){
	
	int Left_x,Left_y;
	int Right_x,Right_y;
	int LtoR_count=1;
	int LeftUp_Info,RightDown_Info;
	
	for(Left_x=x-1,Left_y=y-1;Left_x>=0&&Left_y>=0&&aRecordBoard[Left_x][Left_y]==p;Left_x--,Left_y--)    //数子
	  LtoR_count++;
	for(Right_x=x+1,Right_y=y+1;Right_x<SIZE&&Right_y<SIZE&&aRecordBoard[Right_x][Right_y]==p;Right_x++,Right_y++)
	  LtoR_count++;
	
	if(Left_x>=0&&Left_y>=0)
	  LeftUp_Info=aRecordBoard[Left_x][Left_y];
	if(Right_x<SIZE&&Right_y<SIZE)
	  RightDown_Info=aRecordBoard[Right_x][Right_y];
	
	if(Left_x>=0&&Left_y>=0&&Right_x<SIZE&&Right_y<SIZE&&LeftUp_Info==0&&RightDown_Info==0){     //活子
			
		if(LtoR_count==1&&((Left_x>=3&&Left_y>=3&&aRecordBoard[Left_x-1][Left_y-1]==p&&aRecordBoard[Left_x-2][Left_y-2]==p&&aRecordBoard[Left_x-3][Left_y-3]==0)||(Right_x<=12&&Right_y<=12&&aRecordBoard[Right_x+1][Right_y+1]==p&&aRecordBoard[Right_x+2][Right_y+2]==p&&aRecordBoard[Right_x+3][Right_y+3]==0)))
		  LtoR_count+=2;       //隔空
		
		if(LtoR_count==2&&((Left_x>=2&&Left_y>=2&&aRecordBoard[Left_x-1][Left_y-1]==p&&aRecordBoard[Left_x-2][Left_y-2]==0)||(Right_x<=13&&Right_y<=13&&aRecordBoard[Right_x+1][Right_y+1]==p&&aRecordBoard[Right_x+2][Right_y+2]==0)))
		  LtoR_count++;         //隔空
		
		if(LtoR_count==3)
		  return 3;           //活3
		if(LtoR_count==4)
		  return 4;            //活4
		}

	else if(((Left_x<0||Left_y<0||(Left_x>=0&&Left_y>=0&&LeftUp_Info!=0))&&(Right_x<SIZE&&Right_y<SIZE&&RightDown_Info==0))||((Left_x>=0&&Left_y>=0&&LeftUp_Info==0)&&(Right_x==SIZE||Right_y==SIZE||(Right_x<SIZE&&Right_y<SIZE&&RightDown_Info!=0)))){
			if(LtoR_count==4)                        //半活
			  return 4;     //半活4
		}
	
	else
	  return 0;
}
	
//计算从落子后左下到右上方向的情况
int bcount_RtoL(int x,int y,int p){
	
	int Left_x,Left_y;
	int Right_x,Right_y;
	int RtoL_count=1;
	int LeftDown_Info,RightUp_Info;
	
	for(Left_x=x+1,Left_y=y-1;Left_x<SIZE&&Left_y>=0&&aRecordBoard[Left_x][Left_y]==p;Left_x++,Left_y--)     //数子
	  RtoL_count++;
	for(Right_x=x-1,Right_y=y+1;Right_x>=0&&Right_y<SIZE&&aRecordBoard[Right_x][Right_y]==p;Right_x--,Right_y++)
	  RtoL_count++;
		
	if(Left_x<SIZE&&Left_y>=0)
	  LeftDown_Info=aRecordBoard[Left_x][Left_y];
	if(Right_x>=0&&Right_y<SIZE)
	  RightUp_Info=aRecordBoard[Right_x][Right_y];
	
	if(Left_x<SIZE&&Left_y>=0&&Right_x>=0&&Right_y<SIZE&&LeftDown_Info==0&&RightUp_Info==0){        //活子
			
		if(RtoL_count==1&&((Left_x<=12&&Left_y>=3&&aRecordBoard[Left_x+1][Left_y-1]==p&&aRecordBoard[Left_x+2][Left_y-2]==p&&aRecordBoard[Left_x+3][Left_y-3]==0)||(Right_x>=3&&Right_y<=12&&aRecordBoard[Right_x-1][Right_y+1]==p&&aRecordBoard[Right_x-2][Right_y+2]==p&&aRecordBoard[Right_x-3][Right_y+3]==0)))
		  RtoL_count+=2;                 //隔空
			
		if(RtoL_count==2&&((Left_x<=13&&Left_y>=2&&aRecordBoard[Left_x+1][Left_y-1]==p&&aRecordBoard[Left_x+2][Left_y-2]==0)||(Right_x>=2&&Right_y<=13&&aRecordBoard[Right_x-1][Right_y+1]==p&&aRecordBoard[Right_x-2][Right_y+2]==0)))
		  RtoL_count++;             //隔空
		
		if(RtoL_count==3)
		  return 3;               //活3
		if(RtoL_count==4)
		  return 4;         //活4
		}

	else if(((Left_x==SIZE||Left_y<0||(Left_x<SIZE&&Left_y>=0&&LeftDown_Info!=0))&&(Right_x>=0&&Right_y<SIZE&&RightUp_Info==0))||((Left_x<SIZE&&Left_y>=0&&LeftDown_Info==0)&&(Right_x<0||Right_y==SIZE||(Right_x>=0&&Right_y<SIZE&&RightUp_Info!=0)))){
			if(RtoL_count==4)                //半活4
			  return 4;
		}
	
	else
	  return 0;
}
