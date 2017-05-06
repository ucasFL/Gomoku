//计算棋盘信息，根据得分选择最佳落子位置
#include "my_header.h"
//计算落子后各个方向的情况
int count_x(int x,int y,int p);
int count_y(int x,int y,int p);
int count_LtoR(int x,int y,int p);
int count_RtoL(int x,int y,int p);
//将落子后的情形转化为得分
int num_to_Score_Live(int num);
int num_to_Score_HalfLive(int num);
int num_to_Score_Death(int num);
int other_score(int num);
//查找最高综合得分位置
void GreatScore(int *Info_x,int *Info_y);
//用于记录器棋盘信息的数组
int MyInfo[SIZE][SIZE][DIREC];
int OppInfo[SIZE][SIZE][DIREC];
int MyScore[SIZE][SIZE];
int OppScore[SIZE][SIZE];
int SingleScore[SIZE][SIZE];
int Info_x,Info_y;
int My_Win_x,My_Win_y;
int Opp_Win_x,Opp_Win_y;
int My_LiveFour_x,My_LiveFour_y;
int Opp_LiveFour_x1,Opp_LiveFour_x2,Opp_LiveFour_y1,Opp_LiveFour_y2;
int My_4and4_x,My_4and4_y;
int My_h4and4_x,My_h4and4_y;
int My_o4and3_x,My_o4and3_y;
int My_o4ando4_x,My_o4ando4_y;
int My_o4and4_x,My_o4and4_y;
int Opp_o4and3_x,Opp_o4and3_y;
int Opp_o4ando4_x,Opp_o4ando4_y;
int Opp_o4and4_x,Opp_o4and4_y;
int MyDouble_LiveThree_x,MyDouble_LiveThree_y;
int My_LiveThree_HalfDeathFour_x,My_LiveThree_HalfDeathFour_y;
int OppDouble_LiveThree_x,OppDouble_LiveThree_y;
int Opp_LiveThree_HalfDeathFour_x,Opp_LiveThree_HalfDeathFour_y;
//machine_input 函数:获取电脑输入，电脑后手
void machine_input(int *x,int *y,int p){
        int My_Judge_Win=0,Opp_Judge_Win=0,Opp_Judge_LiveFour=0,My_Judge_LiveFour=0;
		int My_Judge_2Three=0,My_Judge_3and4=0,Opp_Judge_3and4=0;
        int My_Judge_4and4=0,My_hJudge_4and4=0,My_Judge_o4and3=0,My_Judge_o4and4=0,My_Judge_o4ando4=0;
        int Opp_Judge_o4and4=0,Opp_Judge_o4ando4=0,Opp_Judge_o4and3=0;
	extern int aRecordBoard[SIZE][SIZE];
	int i,j,k;
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			if(aRecordBoard[i][j]!=0){
				for(k=0;k<DIREC;k++){
					MyInfo[i][j][k]=0;
					OppInfo[i][j][k]=0;
				}
				MyScore[i][j]=0;
				OppScore[i][j]=0;
				SingleScore[i][j]=0;
			}
			else{
				//计算棋盘信息：自己及对方
			    MyInfo[i][j][0]=count_x(i,j,SECOND_PLAYER);
			    MyInfo[i][j][1]=count_y(i,j,SECOND_PLAYER);
			    MyInfo[i][j][2]=count_LtoR(i,j,SECOND_PLAYER);
			    MyInfo[i][j][3]=count_RtoL(i,j,SECOND_PLAYER);
			    MyScore[i][j]=MyInfo[i][j][0]+MyInfo[i][j][1]+MyInfo[i][j][2]+MyInfo[i][j][3];
			    OppInfo[i][j][0]=count_x(i,j,FIRST_PLAYER);
			    OppInfo[i][j][1]=count_y(i,j,FIRST_PLAYER);
		        OppInfo[i][j][2]=count_LtoR(i,j,FIRST_PLAYER);
			    OppInfo[i][j][3]=count_RtoL(i,j,FIRST_PLAYER);
			    OppScore[i][j]=OppInfo[i][j][0]+OppInfo[i][j][1]+OppInfo[i][j][2]+OppInfo[i][j][3];
			    SingleScore[i][j]=MyScore[i][j]+OppScore[i][j];
			}
		}
	}
  int t=0;
	//根据棋盘信息选择落子
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			for(k=0;k<DIREC;k++){
				//活五
				if(MyInfo[i][j][k]==WIN){
					My_Win_x=i;
					My_Win_y=j;
					My_Judge_Win=1;
				}
				//对方活五
				if(OppInfo[i][j][k]==WIN){
					Opp_Win_x=i;
					Opp_Win_y=j;
					Opp_Judge_Win=1;
				}
				//活四
				if(MyInfo[i][j][k]==LIVE_FOUR){
					My_LiveFour_x=i;
					My_LiveFour_y=j;
					My_Judge_LiveFour=1;
				}
				//对方活四
				if(OppInfo[i][j][k]==LIVE_FOUR){
          if(t%2==0){
            Opp_LiveFour_x1=i;
  					Opp_LiveFour_y1=j;
            t++;
          }
          else{
            Opp_LiveFour_x2=i;
            Opp_LiveFour_y2=j;
          }
					Opp_Judge_LiveFour=1;
				}
          //活四加半活四
			    if((MyInfo[i][j][0]==LIVE_FOUR&&MyInfo[i][j][1]==HALF_LIVE_FOUR)||(MyInfo[i][j][0]==HALF_LIVE_FOUR&&MyInfo[i][j][1]==LIVE_FOUR)||(MyInfo[i][j][0]==LIVE_FOUR&&MyInfo[i][j][2]==HALF_LIVE_FOUR)||(MyInfo[i][j][0]==HALF_LIVE_FOUR&&MyInfo[i][j][2]==LIVE_FOUR)||(MyInfo[i][j][0]==LIVE_FOUR&&MyInfo[i][j][3]==HALF_LIVE_FOUR)||(MyInfo[i][j][0]==HALF_LIVE_FOUR&&MyInfo[i][j][3]==LIVE_FOUR)||(MyInfo[i][j][1]==LIVE_FOUR&&MyInfo[i][j][2]==HALF_LIVE_FOUR)||(MyInfo[i][j][1]==HALF_LIVE_FOUR&&MyInfo[i][j][2]==LIVE_FOUR)||(MyInfo[i][j][1]==LIVE_FOUR&&MyInfo[i][j][3]==HALF_LIVE_FOUR)||(MyInfo[i][j][1]==HALF_LIVE_FOUR&&MyInfo[i][j][3]==LIVE_FOUR)||(MyInfo[i][j][2]==LIVE_FOUR&&MyInfo[i][j][3]==HALF_LIVE_FOUR)||(MyInfo[i][j][2]==HALF_LIVE_FOUR&&MyInfo[i][j][3]==LIVE_FOUR)){
				My_4and4_x=i;
				My_4and4_y=j;
			    My_Judge_4and4=1;
				}
        //半活四加半活四
        if((MyInfo[i][j][0]==HALF_LIVE_FOUR&&MyInfo[i][j][1]==HALF_LIVE_FOUR)||(MyInfo[i][j][0]==HALF_LIVE_FOUR&&MyInfo[i][j][1]==HALF_LIVE_FOUR)||(MyInfo[i][j][0]==HALF_LIVE_FOUR&&MyInfo[i][j][2]==HALF_LIVE_FOUR)||(MyInfo[i][j][0]==HALF_LIVE_FOUR&&MyInfo[i][j][2]==HALF_LIVE_FOUR)||(MyInfo[i][j][0]==HALF_LIVE_FOUR&&MyInfo[i][j][3]==HALF_LIVE_FOUR)||(MyInfo[i][j][0]==HALF_LIVE_FOUR&&MyInfo[i][j][3]==HALF_LIVE_FOUR)||(MyInfo[i][j][1]==HALF_LIVE_FOUR&&MyInfo[i][j][2]==HALF_LIVE_FOUR)||(MyInfo[i][j][1]==HALF_LIVE_FOUR&&MyInfo[i][j][2]==HALF_LIVE_FOUR)||(MyInfo[i][j][1]==HALF_LIVE_FOUR&&MyInfo[i][j][3]==HALF_LIVE_FOUR)||(MyInfo[i][j][1]==HALF_LIVE_FOUR&&MyInfo[i][j][3]==HALF_LIVE_FOUR)||(MyInfo[i][j][2]==HALF_LIVE_FOUR&&MyInfo[i][j][3]==HALF_LIVE_FOUR)||(MyInfo[i][j][2]==HALF_LIVE_FOUR&&MyInfo[i][j][3]==HALF_LIVE_FOUR)){
      My_h4and4_x=i;
      My_h4and4_y=j;
        My_hJudge_4and4=1;
      }
        //另一种半活四+半活四
        if((MyInfo[i][j][0]==HALF_LIVE_FOUR&&MyInfo[i][j][1]==O_HLIVE_F)||(MyInfo[i][j][0]==O_HLIVE_F&&MyInfo[i][j][1]==HALF_LIVE_FOUR)||(MyInfo[i][j][0]==O_HLIVE_F&&MyInfo[i][j][2]==HALF_LIVE_FOUR)||(MyInfo[i][j][0]==HALF_LIVE_FOUR&&MyInfo[i][j][2]==O_HLIVE_F)||(MyInfo[i][j][0]==HALF_LIVE_FOUR&&MyInfo[i][j][3]==O_HLIVE_F)||(MyInfo[i][j][0]==O_HLIVE_F&&MyInfo[i][j][3]==HALF_LIVE_FOUR)||(MyInfo[i][j][1]==HALF_LIVE_FOUR&&MyInfo[i][j][2]==O_HLIVE_F)||(MyInfo[i][j][1]==O_HLIVE_F&&MyInfo[i][j][2]==HALF_LIVE_FOUR)||(MyInfo[i][j][1]==HALF_LIVE_FOUR&&MyInfo[i][j][3]==O_HLIVE_F)||(MyInfo[i][j][1]==O_HLIVE_F&&MyInfo[i][j][3]==HALF_LIVE_FOUR)||(MyInfo[i][j][2]==HALF_LIVE_FOUR&&MyInfo[i][j][3]==O_HLIVE_F)||(MyInfo[i][j][2]==O_HLIVE_F&&MyInfo[i][j][3]==HALF_LIVE_FOUR)){
          My_o4and4_x=i;
          My_o4and4_y=j;
            My_Judge_o4and4=1;
        }
        //另一种双半活四
        if((MyInfo[i][j][0]==O_HLIVE_F&&MyInfo[i][j][1]==O_HLIVE_F)||(MyInfo[i][j][0]==O_HLIVE_F&&MyInfo[i][j][1]==O_HLIVE_F)||(MyInfo[i][j][0]==O_HLIVE_F&&MyInfo[i][j][2]==O_HLIVE_F)||(MyInfo[i][j][0]==O_HLIVE_F&&MyInfo[i][j][2]==O_HLIVE_F)||(MyInfo[i][j][0]==O_HLIVE_F&&MyInfo[i][j][3]==O_HLIVE_F)||(MyInfo[i][j][0]==O_HLIVE_F&&MyInfo[i][j][3]==O_HLIVE_F)||(MyInfo[i][j][1]==O_HLIVE_F&&MyInfo[i][j][2]==O_HLIVE_F)||(MyInfo[i][j][1]==O_HLIVE_F&&MyInfo[i][j][2]==O_HLIVE_F)||(MyInfo[i][j][1]==O_HLIVE_F&&MyInfo[i][j][3]==O_HLIVE_F)||(MyInfo[i][j][1]==O_HLIVE_F&&MyInfo[i][j][3]==O_HLIVE_F)||(MyInfo[i][j][2]==O_HLIVE_F&&MyInfo[i][j][3]==O_HLIVE_F)||(MyInfo[i][j][2]==O_HLIVE_F&&MyInfo[i][j][3]==O_HLIVE_F)){
          My_o4ando4_x=i;
          My_o4ando4_y=j;
            My_Judge_o4ando4=1;
        }
			//双活三
			if((MyInfo[i][j][0]==LIVE_THREE&&MyInfo[i][j][1]==LIVE_THREE)||(MyInfo[i][j][0]==LIVE_THREE&&MyInfo[i][j][2]==LIVE_THREE)||(MyInfo[i][j][0]==LIVE_THREE&&MyInfo[i][j][3]==LIVE_THREE)||(MyInfo[i][j][1]==LIVE_THREE&&MyInfo[i][j][2]==LIVE_THREE)||(MyInfo[i][j][1]==LIVE_THREE&&MyInfo[i][j][3]==LIVE_THREE)||(MyInfo[i][j][2]==LIVE_THREE&&MyInfo[i][j][3]==LIVE_THREE)){
				MyDouble_LiveThree_x=i;
				MyDouble_LiveThree_y=j;
			    My_Judge_2Three=1;
			}
      //对方双活三
			if((OppInfo[i][j][0]==LIVE_THREE&&OppInfo[i][j][1]==LIVE_THREE)||(OppInfo[i][j][0]==LIVE_THREE&&OppInfo[i][j][2]==LIVE_THREE)||(OppInfo[i][j][0]==LIVE_THREE&&OppInfo[i][j][3]==LIVE_THREE)||(OppInfo[i][j][1]==LIVE_THREE&&OppInfo[i][j][2]==LIVE_THREE)||(OppInfo[i][j][1]==LIVE_THREE&&OppInfo[i][j][3]==LIVE_THREE)||(OppInfo[i][j][2]==LIVE_THREE&&OppInfo[i][j][3]==LIVE_THREE)){
				SingleScore[i][j]=0;
			}
			//活三加半活四
			if((MyInfo[i][j][0]==LIVE_THREE&&MyInfo[i][j][1]==HALF_LIVE_FOUR)||(MyInfo[i][j][0]==HALF_LIVE_FOUR&&MyInfo[i][j][1]==LIVE_THREE)||(MyInfo[i][j][0]==LIVE_THREE&&MyInfo[i][j][2]==HALF_LIVE_FOUR)||(MyInfo[i][j][0]==HALF_LIVE_FOUR&&MyInfo[i][j][2]==LIVE_THREE)||(MyInfo[i][j][0]==LIVE_THREE&&MyInfo[i][j][3]==HALF_LIVE_FOUR)||(MyInfo[i][j][0]==HALF_LIVE_FOUR&&MyInfo[i][j][3]==LIVE_THREE)||(MyInfo[i][j][1]==LIVE_THREE&&MyInfo[i][j][2]==HALF_LIVE_FOUR)||(MyInfo[i][j][1]==HALF_LIVE_FOUR&&MyInfo[i][j][2]==LIVE_THREE)||(MyInfo[i][j][1]==LIVE_THREE&&MyInfo[i][j][3]==HALF_LIVE_FOUR)||(MyInfo[i][j][1]==HALF_LIVE_FOUR&&MyInfo[i][j][3]==LIVE_THREE)||(MyInfo[i][j][2]==LIVE_THREE&&MyInfo[i][j][3]==HALF_LIVE_FOUR)||(MyInfo[i][j][2]==HALF_LIVE_FOUR&&MyInfo[i][j][3]==LIVE_THREE)){
				My_LiveThree_HalfDeathFour_x=i;
				My_LiveThree_HalfDeathFour_y=j;
			    My_Judge_3and4=1;
			}
                        //另一种半活四加活三
			if((MyInfo[i][j][0]==LIVE_THREE&&MyInfo[i][j][1]==O_HLIVE_F)||(MyInfo[i][j][0]==O_HLIVE_F&&MyInfo[i][j][1]==LIVE_THREE)||(MyInfo[i][j][0]==O_HLIVE_F&&MyInfo[i][j][2]==LIVE_THREE)||(MyInfo[i][j][0]==LIVE_THREE&&MyInfo[i][j][2]==O_HLIVE_F)||(MyInfo[i][j][0]==LIVE_THREE&&MyInfo[i][j][3]==O_HLIVE_F)||(MyInfo[i][j][0]==O_HLIVE_F&&MyInfo[i][j][3]==LIVE_THREE)||(MyInfo[i][j][1]==LIVE_THREE&&MyInfo[i][j][2]==O_HLIVE_F)||(MyInfo[i][j][1]==O_HLIVE_F&&MyInfo[i][j][2]==LIVE_THREE)||(MyInfo[i][j][1]==LIVE_THREE&&MyInfo[i][j][3]==O_HLIVE_F)||(MyInfo[i][j][1]==O_HLIVE_F&&MyInfo[i][j][3]==LIVE_THREE)||(MyInfo[i][j][2]==LIVE_THREE&&MyInfo[i][j][3]==O_HLIVE_F)||(MyInfo[i][j][2]==O_HLIVE_F&&MyInfo[i][j][3]==LIVE_THREE)){
				My_o4and3_x=i;
				My_o4and3_y=j;
			    My_Judge_o4and3=1;
			}
      //对方另一种活四＋半活四
      if((OppInfo[i][j][0]==O_HLIVE_F&&OppInfo[i][j][1]==HALF_LIVE_FOUR)||(OppInfo[i][j][0]==HALF_LIVE_FOUR&&OppInfo[i][j][1]==O_HLIVE_F)||(OppInfo[i][j][0]==O_HLIVE_F&&OppInfo[i][j][2]==HALF_LIVE_FOUR)||(OppInfo[i][j][0]==HALF_LIVE_FOUR&&OppInfo[i][j][2]==O_HLIVE_F)||(OppInfo[i][j][0]==O_HLIVE_F&&OppInfo[i][j][3]==HALF_LIVE_FOUR)||(OppInfo[i][j][0]==HALF_LIVE_FOUR&&OppInfo[i][j][3]==O_HLIVE_F)||(OppInfo[i][j][1]==O_HLIVE_F&&OppInfo[i][j][2]==HALF_LIVE_FOUR)||(OppInfo[i][j][1]==HALF_LIVE_FOUR&&OppInfo[i][j][2]==O_HLIVE_F)||(OppInfo[i][j][1]==O_HLIVE_F&&OppInfo[i][j][3]==HALF_LIVE_FOUR)||(OppInfo[i][j][1]==HALF_LIVE_FOUR&&OppInfo[i][j][3]==O_HLIVE_F)||(OppInfo[i][j][2]==O_HLIVE_F&&OppInfo[i][j][3]==HALF_LIVE_FOUR)||(OppInfo[i][j][2]==HALF_LIVE_FOUR&&OppInfo[i][j][3]==O_HLIVE_F)){
        Opp_o4and4_x=i;
        Opp_o4and4_y=j;
          Opp_Judge_o4and4=1;
      }
      //对方另一种双半活四
      if((OppInfo[i][j][0]==O_HLIVE_F&&OppInfo[i][j][1]==O_HLIVE_F)||(OppInfo[i][j][0]==O_HLIVE_F&&OppInfo[i][j][1]==O_HLIVE_F)||(OppInfo[i][j][0]==O_HLIVE_F&&OppInfo[i][j][2]==O_HLIVE_F)||(OppInfo[i][j][0]==O_HLIVE_F&&OppInfo[i][j][2]==O_HLIVE_F)||(OppInfo[i][j][0]==O_HLIVE_F&&OppInfo[i][j][3]==O_HLIVE_F)||(OppInfo[i][j][0]==O_HLIVE_F&&OppInfo[i][j][3]==O_HLIVE_F)||(OppInfo[i][j][1]==O_HLIVE_F&&OppInfo[i][j][2]==O_HLIVE_F)||(OppInfo[i][j][1]==O_HLIVE_F&&OppInfo[i][j][2]==O_HLIVE_F)||(OppInfo[i][j][1]==O_HLIVE_F&&OppInfo[i][j][3]==O_HLIVE_F)||(OppInfo[i][j][1]==O_HLIVE_F&&OppInfo[i][j][3]==O_HLIVE_F)||(OppInfo[i][j][2]==O_HLIVE_F&&OppInfo[i][j][3]==O_HLIVE_F)||(OppInfo[i][j][2]==O_HLIVE_F&&OppInfo[i][j][3]==O_HLIVE_F)){
        Opp_o4ando4_x=i;
        Opp_o4ando4_y=j;
          Opp_Judge_o4ando4=1;
      }
			//对方活三加半活四
			if((OppInfo[i][j][0]==LIVE_THREE&&OppInfo[i][j][1]==HALF_LIVE_FOUR)||(OppInfo[i][j][0]==HALF_LIVE_FOUR&&OppInfo[i][j][1]==LIVE_THREE)||(OppInfo[i][j][0]==LIVE_THREE&&OppInfo[i][j][2]==HALF_LIVE_FOUR)||(OppInfo[i][j][0]==HALF_LIVE_FOUR&&OppInfo[i][j][2]==LIVE_THREE)||(OppInfo[i][j][0]==LIVE_THREE&&OppInfo[i][j][3]==HALF_LIVE_FOUR)||(OppInfo[i][j][0]==HALF_LIVE_FOUR&&OppInfo[i][j][3]==LIVE_THREE)||(OppInfo[i][j][1]==LIVE_THREE&&OppInfo[i][j][2]==HALF_LIVE_FOUR)||(OppInfo[i][j][1]==HALF_LIVE_FOUR&&OppInfo[i][j][2]==LIVE_THREE)||(OppInfo[i][j][1]==LIVE_THREE&&OppInfo[i][j][3]==HALF_LIVE_FOUR)||(OppInfo[i][j][1]==HALF_LIVE_FOUR&&OppInfo[i][j][3]==LIVE_THREE)||(OppInfo[i][j][2]==LIVE_THREE&&OppInfo[i][j][3]==HALF_LIVE_FOUR)||(OppInfo[i][j][2]==HALF_LIVE_FOUR&&OppInfo[i][j][3]==LIVE_THREE)){
				Opp_LiveThree_HalfDeathFour_x=i;
				Opp_LiveThree_HalfDeathFour_y=j;
			    Opp_Judge_3and4=1;
        }
        //对方另一种半活四加活三
      if((OppInfo[i][j][0]==LIVE_THREE&&OppInfo[i][j][1]==O_HLIVE_F)||(OppInfo[i][j][0]==O_HLIVE_F&&OppInfo[i][j][1]==LIVE_THREE)||(OppInfo[i][j][0]==O_HLIVE_F&&OppInfo[i][j][2]==LIVE_THREE)||(OppInfo[i][j][0]==LIVE_THREE&&OppInfo[i][j][2]==O_HLIVE_F)||(OppInfo[i][j][0]==LIVE_THREE&&OppInfo[i][j][3]==O_HLIVE_F)||(OppInfo[i][j][0]==O_HLIVE_F&&OppInfo[i][j][3]==LIVE_THREE)||(OppInfo[i][j][1]==LIVE_THREE&&OppInfo[i][j][2]==O_HLIVE_F)||(OppInfo[i][j][1]==O_HLIVE_F&&OppInfo[i][j][2]==LIVE_THREE)||(OppInfo[i][j][1]==LIVE_THREE&&OppInfo[i][j][3]==O_HLIVE_F)||(OppInfo[i][j][1]==O_HLIVE_F&&OppInfo[i][j][3]==LIVE_THREE)||(OppInfo[i][j][2]==LIVE_THREE&&OppInfo[i][j][3]==O_HLIVE_F)||(OppInfo[i][j][2]==O_HLIVE_F&&OppInfo[i][j][3]==LIVE_THREE)){
          Opp_o4and3_x=i;
          Opp_o4and3_y=j;
            Opp_Judge_o4and3=1;
        }
      }
		}
	}
	//在该点落子后获胜
	if(My_Judge_Win==1){
		*x=My_Win_x;
		*y=My_Win_y;
		return;
	}
	//对方在该点落子后获胜
	if(Opp_Judge_Win==1){
		*x=Opp_Win_x;
		*y=Opp_Win_y;
		return;
	}
  //在该点落子后活四
  if(My_Judge_LiveFour==1){
    *x=My_LiveFour_x;
    *y=My_LiveFour_y;
    return;
  }
	//在该点落子后活四加半活四
	if(My_Judge_4and4==1){
		*x=My_4and4_x;
		*y=My_4and4_y;
		return;
	}
  //双半活四
  if(My_hJudge_4and4==1){
		*x=My_h4and4_x;
		*y=My_h4and4_y;
		return;
	}
  //另一种半活四加半活四
  if(My_Judge_o4and4==1){
    *x=My_o4and4_x;
    *y=My_o4and4_y;
    return;
  }
  //另一种双半活四
  if(My_Judge_o4ando4==1){
    *x=My_o4ando4_x;
    *y=My_o4ando4_y;
    return;
  }

  //对方另一种半活四加半活四
    if(Opp_Judge_o4and4==1){
      *x=Opp_o4and4_x;
      *y=Opp_o4and4_y;
      return;
    }
    //对方另一种双半活四
    if(Opp_Judge_o4ando4==1){
      *x=Opp_o4ando4_x;
      *y=Opp_o4ando4_y;
      return;
    }
	//对方在该点落子后活四
	if(Opp_Judge_LiveFour==1){
    if(SingleScore[Opp_LiveFour_x1][Opp_LiveFour_y1]>SingleScore[Opp_LiveFour_x2][Opp_LiveFour_y2]){
      *x=Opp_LiveFour_x1;
      *y=Opp_LiveFour_y1;
      return;
    }
    else{
      *x=Opp_LiveFour_x2;
      *y=Opp_LiveFour_y2;
      return;
    }
	}

	//在该点落子后双活三
	if(My_Judge_2Three==1){
		*x=MyDouble_LiveThree_x;
		*y=MyDouble_LiveThree_y;
		return;
	}
	//在该点落子后活三加半活四
	if(My_Judge_3and4==1){
		*x=My_LiveThree_HalfDeathFour_x;
		*y=My_LiveThree_HalfDeathFour_y;
		return;
	}
  //另一种半活四加活三
  if(My_Judge_o4and3==1){
    *x=My_o4and3_x;
    *y=My_o4and3_y;
    return ;
  }

	//对方在该点落子后活三加半活四
	if(Opp_Judge_3and4==1){
		*x=Opp_LiveThree_HalfDeathFour_x;
		*y=Opp_LiveThree_HalfDeathFour_y;
		return;
	}
  //对方另一种半活四加活三
  if(Opp_Judge_o4and3==1){
    *x=Opp_o4and3_x;
    *y=Opp_o4and3_y;
    return ;
  }
	//其他情况选择综合得分最高的点落子
	GreatScore(&Info_x,&Info_y);
	*x=Info_x;
	*y=Info_y;
}
//计算落子后水平方向得分
int count_x(int x,int y,int p){
	extern int aRecordBoard[SIZE][SIZE];
	int Left_y,Right_y;
	int Left_Info,Right_Info;
	int x_count=1;
	for(Left_y=y-1;aRecordBoard[x][Left_y]==p&&Left_y>=0;Left_y--)
	  x_count++;
	for(Right_y=y+1;aRecordBoard[x][Right_y]==p&&Right_y<SIZE;Right_y++)
	  x_count++;
	if(Left_y>=0)
	  Left_Info=aRecordBoard[x][Left_y];
	if(Right_y<SIZE)
	  Right_Info=aRecordBoard[x][Right_y];
    //活
	if(Left_y>=0&&Right_y<SIZE&&Left_Info==0&&Right_Info==0){
    if(x_count==1&&((Left_y>=4&&aRecordBoard[x][Left_y-1]==p&&aRecordBoard[x][Left_y-2]==p&&aRecordBoard[x][Left_y-3]==p&&aRecordBoard[x][Left_y-4]!=p&&aRecordBoard[x][Left_y-4]!=0)||(Right_y<=11&&aRecordBoard[x][Right_y+1]==p&&aRecordBoard[x][Right_y+2]==p&&aRecordBoard[x][Right_y+3]==p&&aRecordBoard[x][Right_y+4]!=p&&aRecordBoard[x][Right_y+4]!=0))){
      return other_score(4);
    }
    if(x_count==2&&((Left_y>=3&&aRecordBoard[x][Left_y-1]==p&&aRecordBoard[x][Left_y-2]==p&&aRecordBoard[x][Left_y-3]!=p&&aRecordBoard[x][Left_y-3]!=0)||(Right_y<=12&&aRecordBoard[x][Right_y+1]==p&&aRecordBoard[x][Right_y+2]==p&&aRecordBoard[x][Right_y+3]!=p&&aRecordBoard[x][Right_y+3]!=0))){
      return other_score(4);
    }
    if(x_count==1&&((Left_y>=3&&aRecordBoard[x][Left_y-1]==p&&aRecordBoard[x][Left_y-2]==p&&aRecordBoard[x][Left_y-3]!=0&&aRecordBoard[x][Left_y-3]!=p)||(Right_y<=12&&aRecordBoard[x][Right_y+1]==p&&aRecordBoard[x][Right_y+2]==p&&aRecordBoard[x][Right_y+3]!=0&&aRecordBoard[x][Right_y+3]!=p))){
      return other_score(3);
    }
    if(x_count==1&&((Left_y>=2&&aRecordBoard[x][Left_y-1]==p&&aRecordBoard[x][Left_y-2]!=p&&aRecordBoard[x][Left_y-2]!=0)||(Right_y<=13&&aRecordBoard[x][Right_y+1]==p&&aRecordBoard[x][Right_y+2]!=p&&aRecordBoard[x][Right_y+2]!=0))){
      return other_score(2);
    }
		if(x_count==1&&((Left_y>=3&&aRecordBoard[x][Left_y-1]==p&&aRecordBoard[x][Left_y-2]==p&&aRecordBoard[x][Left_y-3]==0)||(Right_y<=12&&aRecordBoard[x][Right_y+1]==p&&aRecordBoard[x][Right_y+2]==p&&aRecordBoard[x][Right_y+3]==0)))
		  x_count+=2;
		if(x_count==2&&((Left_y>=2&&aRecordBoard[x][Left_y-1]==p&&aRecordBoard[x][Left_y-2]==0)||(Right_y<=13&&aRecordBoard[x][Right_y+1]==p&&aRecordBoard[x][Right_y+2]==0)))
		  x_count++;
	    return num_to_Score_Live(x_count);
	}
  //半活
	else if(((Left_y<0||(Left_y>=0&&Left_Info!=0))&&Right_y<SIZE&&Right_Info==0)||(Left_y>=0&&Left_Info==0&&(Right_y==SIZE||(Right_y<SIZE&&Right_Info!=0)))){
    if(x_count==3&&((Left_y>=2&&aRecordBoard[x][Left_y-1]==p&&aRecordBoard[x][Left_y-2]==0)||(Right_y<=13&&aRecordBoard[x][Right_y+1]==p&&aRecordBoard[x][Right_y+2]==0))){
      return other_score(4);
    }
    if(x_count==2&&((Left_y>=3&&aRecordBoard[x][Left_y-1]==p&&aRecordBoard[x][Left_y-2]==p&&aRecordBoard[x][Left_y-3]==0)||(Right_y<=12&&aRecordBoard[x][Right_y+1]==p&&aRecordBoard[x][Right_y+2]==p&&aRecordBoard[x][Right_y+3]==0))){
      return other_score(4);
    }
    if(x_count==2&&((Left_y>=2&&aRecordBoard[x][Left_y-1]==p&&aRecordBoard[x][Left_y-2]==0)||(Right_y<=13&&aRecordBoard[x][Right_y+1]==p&&aRecordBoard[x][Right_y+2]==0))){
      return other_score(3);
    }
    if(x_count==1&&((Left_y>=2&&aRecordBoard[x][Left_y-1]==p&&aRecordBoard[x][Left_y-2]==0)||(Right_y<=13&&aRecordBoard[x][Right_y+1]==p&&aRecordBoard[x][Right_y+2]==0))){
      return other_score(2);
    }
    return num_to_Score_HalfLive(x_count);
  }
  //死
	else
	  return num_to_Score_Death(x_count);
}
//计算落子后竖直方向得分
int count_y(int x,int y,int p){
	extern int aRecordBoard[SIZE][SIZE];
	int Up_x,Down_x;
	int Up_Info,Down_Info;
	int y_count=1;
	for(Up_x=x-1;aRecordBoard[Up_x][y]==p&&Up_x>=0;Up_x--)
	  y_count++;
	for(Down_x=x+1;aRecordBoard[Down_x][y]==p&&Down_x<SIZE;Down_x++)
	  y_count++;
	if(Up_x>=0)
	  Up_Info=aRecordBoard[Up_x][y];
	if(Down_x<SIZE)
	  Down_Info=aRecordBoard[Down_x][y];
    //活
	if(Up_x>=0&&Down_x<SIZE&&Up_Info==0&&Down_Info==0){
    if(y_count==1&&((Up_x>=4&&aRecordBoard[Up_x-1][y]==p&&aRecordBoard[Up_x-2][y]==p&&aRecordBoard[Up_x-3][y]==p&&aRecordBoard[Up_x-4][y]!=p&&aRecordBoard[Up_x-4][y]!=0)||(Down_x<=11&&aRecordBoard[Down_x+1][y]==p&&aRecordBoard[Down_x+2][y]==p&&aRecordBoard[Down_x+3][y]==p&&aRecordBoard[Down_x+4][y]!=p&&aRecordBoard[Down_x+4][y]!=0))){
      return other_score(4);
    }
    if(y_count==2&&((Up_x>=3&&aRecordBoard[Up_x-1][y]==p&&aRecordBoard[Up_x-2][y]==p&&aRecordBoard[Up_x-3][y]!=p&&aRecordBoard[Up_x-3][y]!=0)||(Down_x<=12&&aRecordBoard[Down_x+1][y]==p&&aRecordBoard[Down_x+2][y]==p&&aRecordBoard[Down_x+3][y]!=p&&aRecordBoard[Down_x+3][y]!=0))){
      return other_score(4);
    }
    if(y_count==1&&((Up_x>=3&&aRecordBoard[Up_x-1][y]==p&&aRecordBoard[Up_x-2][y]==p&&aRecordBoard[Up_x-3][y]!=0&&aRecordBoard[Up_x-3][y]!=p)||(Down_x<=12&&aRecordBoard[Down_x+1][y]==p&&aRecordBoard[Down_x+2][y]==p&&aRecordBoard[Down_x+3][y]!=0&&aRecordBoard[Down_x+3][y]!=p))){
      return other_score(3);
    }
    if(y_count==1&&((Up_x>=2&&aRecordBoard[Up_x-1][y]==p&&aRecordBoard[Up_x-2][y]!=p&&aRecordBoard[Up_x-2][y]!=0)||(Down_x<=13&&aRecordBoard[Down_x+1][y]==p&&aRecordBoard[Down_x+2][y]!=p&&aRecordBoard[Down_x+2][y]!=0))){
      return other_score(2);
    }
		if(y_count==1&&((Up_x>=3&&aRecordBoard[Up_x-1][y]==p&&aRecordBoard[Up_x-2][y]==p&&aRecordBoard[Up_x-3][y]==0)||(Down_x<=12&&aRecordBoard[Down_x+1][y]==p&&aRecordBoard[Down_x+2][y]==p&&aRecordBoard[Down_x+3][y]==0)))
		  y_count+=2;
		if(y_count==2&&((Up_x>=2&&aRecordBoard[Up_x-1][y]==p&&aRecordBoard[Up_x-2][y]==0)||(Down_x<=13&&aRecordBoard[Down_x+1][y]==p&&aRecordBoard[Down_x+2][y]==0)))
		  y_count++;
	  return num_to_Score_Live(y_count);
	}
  //半活
	else if(((Up_x<0||(Up_x>=0&&Up_Info!=0))&&Down_x<SIZE&&Down_Info==0)||(Up_x>=0&&Up_Info==0&&(Down_x==SIZE||(Down_x<SIZE&&Down_Info!=0)))){
    if(y_count==3&&((Up_x>=2&&aRecordBoard[Up_x-1][y]==p&&aRecordBoard[Up_x-2][y]==0)||(Down_x<=13&&aRecordBoard[Down_x+1][y]==p&&aRecordBoard[Down_x+2][y]==0))){
      return other_score(4);
    }
    if(y_count==2&&((Up_x>=3&&aRecordBoard[Up_x-1][y]==p&&aRecordBoard[Up_x-2][y]==p&&aRecordBoard[Up_x-3][y]==0)||(Down_x<=12&&aRecordBoard[Down_x+1][y]==p&&aRecordBoard[Down_x+2][y]==p&&aRecordBoard[Down_x+3][y]==0))){
      return other_score(4);
    }
    if(y_count==2&&((Up_x>=2&&aRecordBoard[Up_x-1][y]==p&&aRecordBoard[Up_x-2][y]==0)||(Down_x<=13&&aRecordBoard[Down_x+1][y]==p&&aRecordBoard[Down_x+2][y]==0))){
      return other_score(3);
    }
    if(y_count==1&&((Up_x>=2&&aRecordBoard[Up_x-1][y]==p&&aRecordBoard[Up_x-2][y]==0)||(Down_x<=13&&aRecordBoard[Down_x+1][y]==p&&aRecordBoard[Down_x+2][y]==0))){
      return other_score(2);
    }
    return num_to_Score_HalfLive(y_count);
  }
	  //死
	else
	  return num_to_Score_Death(y_count);
}
//计算落子后左上到右下方向的得分
int count_LtoR(int x,int y,int p){
	extern int aRecordBoard[SIZE][SIZE];
	int Left_x,Left_y;
	int Right_x,Right_y;
	int LtoR_count=1;
	int LeftUp_Info,RightDown_Info;
	for(Left_x=x-1,Left_y=y-1;Left_x>=0&&Left_y>=0&&aRecordBoard[Left_x][Left_y]==p;Left_x--,Left_y--)
	  LtoR_count++;
	for(Right_x=x+1,Right_y=y+1;Right_x<SIZE&&Right_y<SIZE&&aRecordBoard[Right_x][Right_y]==p;Right_x++,Right_y++)
	  LtoR_count++;
	if(Left_x>=0&&Left_y>=0)
	  LeftUp_Info=aRecordBoard[Left_x][Left_y];
	if(Right_x<SIZE&&Right_y<SIZE)
	  RightDown_Info=aRecordBoard[Right_x][Right_y];
    //活
	if(Left_x>=0&&Left_y>=0&&Right_x<SIZE&&Right_y<SIZE&&LeftUp_Info==0&&RightDown_Info==0){
    if(LtoR_count==1&&((Left_y>=4&&Left_x>=4&&aRecordBoard[Left_x-1][Left_y-1]==p&&aRecordBoard[Left_x-2][Left_y-2]==p&&aRecordBoard[Left_x-3][Left_y-3]==p&&aRecordBoard[Left_x-4][Left_x-4]!=p&&aRecordBoard[Left_x-4][Left_y-4]!=0)||(Right_x<=11&&Right_y<=11&&aRecordBoard[Right_x+1][Right_y+1]==p&&aRecordBoard[Right_x+2][Right_y+2]==p&&aRecordBoard[Right_x+3][Right_y+3]==p&&aRecordBoard[Right_x+4][Right_y+4]!=p&&aRecordBoard[Right_x+4][Right_y+4]!=0))){
      return other_score(4);
    }
    if(LtoR_count==2&&((Left_y>=3&&Left_x>=3&&aRecordBoard[Left_x-1][Left_y-1]==p&&aRecordBoard[Left_x-2][Left_y-2]==p&&aRecordBoard[Left_x-3][Left_y-3]!=p&&aRecordBoard[Left_x-3][Left_x-3]!=0)||(Right_x<=12&&Right_y<=12&&aRecordBoard[Right_x+1][Right_y+1]==p&&aRecordBoard[Right_x+2][Right_y+2]==p&&aRecordBoard[Right_x+3][Right_y+3]!=p&&aRecordBoard[Right_x+3][Right_y+3]!=0))){
      return other_score(4);
    }
    if(LtoR_count==1&&((Left_x>=3&&Left_y>=3&&aRecordBoard[Left_x-1][Left_y-1]==p&&aRecordBoard[Left_x-2][Left_y-2]==p&&aRecordBoard[Left_x-3][Left_y-3]!=0&&aRecordBoard[Left_x-3][Left_y-3]!=p)||(Right_y<=12&&Right_x<=12&&aRecordBoard[Right_x+1][Right_y+1]==p&&aRecordBoard[Right_x+2][Right_y+2]==p&&aRecordBoard[Right_x+3][Right_y+3]!=0&&aRecordBoard[Right_x+3][Right_y+3]!=p))){
      return other_score(3);
    }
    if(LtoR_count==1&&((Left_x>=2&&Left_y>=2&&aRecordBoard[Left_x-1][Left_y-1]==p&&aRecordBoard[Left_x-2][Left_y-2]!=p&&aRecordBoard[Left_x-2][Left_y-2]!=0)||(Right_y<=13&&Right_x<=13&&aRecordBoard[Right_x+1][Right_y+1]==p&&aRecordBoard[Right_x+2][Right_y+2]!=p&&aRecordBoard[Right_x+2][Right_y+2]!=0))){
      return other_score(2);
    }
		if(LtoR_count==1&&((Left_x>=3&&Left_y>=3&&aRecordBoard[Left_x-1][Left_y-1]==p&&aRecordBoard[Left_x-2][Left_y-2]==p&&aRecordBoard[Left_x-3][Left_y-3]==0)||(Right_x<=12&&Right_y<=12&&aRecordBoard[Right_x+1][Right_y+1]==p&&aRecordBoard[Right_x+2][Right_y+2]==p&&aRecordBoard[Right_x+3][Right_y+3]==0)))
		  LtoR_count+=2;
		if(LtoR_count==2&&((Left_x>=2&&Left_y>=2&&aRecordBoard[Left_x-1][Left_y-1]==p&&aRecordBoard[Left_x-2][Left_y-2]==0)||(Right_x<=13&&Right_y<=13&&aRecordBoard[Right_x+1][Right_y+1]==p&&aRecordBoard[Right_x+2][Right_y+2]==0)))
		  LtoR_count++;
	  return num_to_Score_Live(LtoR_count);
	}
  //半活
	else if(((Left_x<0||Left_y<0||(Left_x>=0&&Left_y>=0&&LeftUp_Info!=0))&&(Right_x<SIZE&&Right_y<SIZE&&RightDown_Info==0))||((Left_x>=0&&Left_y>=0&&LeftUp_Info==0)&&(Right_x==SIZE||Right_y==SIZE||(Right_x<SIZE&&Right_y<SIZE&&RightDown_Info!=0)))){
    if(LtoR_count==3&&((Left_x>=2&&Left_y>=2&&aRecordBoard[Left_x-1][Left_y-1]==p&&aRecordBoard[Left_x-2][Left_y-2]==0)||(Right_x<=13&&Right_y<=13&&aRecordBoard[Right_x+1][Right_y+1]==p&&aRecordBoard[Right_x+2][Right_y+2]==0))){
      return other_score(4);
    }
    if(LtoR_count==2&&((Left_x>=3&&Left_y>=3&&aRecordBoard[Left_x-1][Left_y-1]==p&&aRecordBoard[Left_x-2][Left_y-2]==p&&aRecordBoard[Left_x-3][Left_y-3]==0)||(Right_x<=12&&Right_y<=12&&aRecordBoard[Right_x+1][Right_y+1]==p&&aRecordBoard[Right_x+2][Right_y+2]==p&&aRecordBoard[Right_x+3][Right_y+3]==0))){
      return other_score(4);
    }
    if(LtoR_count==2&&((Left_y>=2&&Left_x>=2&&aRecordBoard[Left_x-1][Left_y-1]==p&&aRecordBoard[Left_x-2][Left_y-2]==0)||(Right_y<=13&&Right_x<=13&&aRecordBoard[Right_x+1][Right_y+1]==p&&aRecordBoard[Right_x+2][Right_y+2]==0))){
      return other_score(3);
    }
    if(LtoR_count==1&&((Left_x>=2&&Left_y>=2&&aRecordBoard[Left_x-1][Left_y-1]==p&&aRecordBoard[Left_x-2][Left_y-2]==0)||(Right_y<=13&&Right_x<=13&&aRecordBoard[Right_x+1][Right_y+1]==p&&aRecordBoard[Right_x+2][Right_y+2]==0))){
      return other_score(2);
    }
    return num_to_Score_HalfLive(LtoR_count);
  }
  //死
  else
	  return num_to_Score_Death(LtoR_count);
}
//计算从落子后左下到右上方向的得分
int count_RtoL(int x,int y,int p){
	extern int aRecordBoard[SIZE][SIZE];
	int Left_x,Left_y;
	int Right_x,Right_y;
	int RtoL_count=1;
	int LeftDown_Info,RightUp_Info;
	for(Left_x=x+1,Left_y=y-1;Left_x<SIZE&&Left_y>=0&&aRecordBoard[Left_x][Left_y]==p;Left_x++,Left_y--)
	  RtoL_count++;
	for(Right_x=x-1,Right_y=y+1;Right_x>=0&&Right_y<SIZE&&aRecordBoard[Right_x][Right_y]==p;Right_x--,Right_y++)
	  RtoL_count++;
	if(Left_x<SIZE&&Left_y>=0)
	  LeftDown_Info=aRecordBoard[Left_x][Left_y];
	if(Right_x>=0&&Right_y<SIZE)
	  RightUp_Info=aRecordBoard[Right_x][Right_y];
    //活
	if(Left_x<SIZE&&Left_y>=0&&Right_x>=0&&Right_y<SIZE&&LeftDown_Info==0&&RightUp_Info==0){
    if(RtoL_count==1&&((Left_y>=4&&Left_x<=11&&aRecordBoard[Left_x+1][Left_y-1]==p&&aRecordBoard[Left_x+2][Left_y-2]==p&&aRecordBoard[Left_x+3][Left_y-3]==p&&aRecordBoard[Left_x+4][Left_x-4]!=p&&aRecordBoard[Left_x+4][Left_y-4]!=0)||(Right_x>=4&&Right_y<=11&&aRecordBoard[Right_x-1][Right_y+1]==p&&aRecordBoard[Right_x-2][Right_y+2]==p&&aRecordBoard[Right_x-3][Right_y+3]==p&&aRecordBoard[Right_x-4][Right_y+4]!=p&&aRecordBoard[Right_x-4][Right_y+4]!=0))){
      return other_score(4);
    }
    if(RtoL_count==2&&((Left_y>=3&&Left_x<=12&&aRecordBoard[Left_x+1][Left_y-1]==p&&aRecordBoard[Left_x+2][Left_y-2]==p&&aRecordBoard[Left_x+3][Left_y-3]!=p&&aRecordBoard[Left_x+3][Left_x-3]!=0)||(Right_x>=3&&Right_y<=12&&aRecordBoard[Right_x-1][Right_y+1]==p&&aRecordBoard[Right_x-2][Right_y+2]==p&&aRecordBoard[Right_x-3][Right_y+3]!=p&&aRecordBoard[Right_x-3][Right_y+3]!=0))){
      return other_score(4);
    }
    if(RtoL_count==1&&((Left_x<=12&&Left_y>=3&&aRecordBoard[Left_x+1][Left_y-1]==p&&aRecordBoard[Left_x+2][Left_y-2]==p&&aRecordBoard[Left_x+3][Left_y-3]!=0&&aRecordBoard[Left_x+3][Left_y-3]!=p)||(Right_y<=12&&Right_x>=3&&aRecordBoard[Right_x-1][Right_y+1]==p&&aRecordBoard[Right_x-2][Right_y+2]==p&&aRecordBoard[Right_x-3][Right_y+3]!=0&&aRecordBoard[Right_x-3][Right_y+3]!=p))){
      return other_score(3);
    }
    if(RtoL_count==1&&((Left_x<=13&&Left_y>=2&&aRecordBoard[Left_x+1][Left_y-1]==p&&aRecordBoard[Left_x+2][Left_y-2]!=p&&aRecordBoard[Left_x+2][Left_y-2]!=0)||(Right_y<=13&&Right_x>=2&&aRecordBoard[Right_x-1][Right_y+1]==p&&aRecordBoard[Right_x-2][Right_y+2]!=p&&aRecordBoard[Right_x-2][Right_y+2]!=0))){
      return other_score(2);
    }
		if(RtoL_count==1&&((Left_x<=12&&Left_y>=3&&aRecordBoard[Left_x+1][Left_y-1]==p&&aRecordBoard[Left_x+2][Left_y-2]==p&&aRecordBoard[Left_x+3][Left_y-3]==0)||(Right_x>=3&&Right_y<=12&&aRecordBoard[Right_x-1][Right_y+1]==p&&aRecordBoard[Right_x-2][Right_y+2]==p&&aRecordBoard[Right_x-3][Right_y+3]==0)))
		  RtoL_count+=2;
		if(RtoL_count==2&&((Left_x<=13&&Left_y>=2&&aRecordBoard[Left_x+1][Left_y-1]==p&&aRecordBoard[Left_x+2][Left_y-2]==0)||(Right_x>=2&&Right_y<=13&&aRecordBoard[Right_x-1][Right_y+1]==p&&aRecordBoard[Right_x-2][Right_y+2]==0)))
		  RtoL_count++;
	  return num_to_Score_Live(RtoL_count);
	}
  //半活
	else if(((Left_x==SIZE||Left_y<0||(Left_x<SIZE&&Left_y>=0&&LeftDown_Info!=0))&&(Right_x>=0&&Right_y<SIZE&&RightUp_Info==0))||((Left_x<SIZE&&Left_y>=0&&LeftDown_Info==0)&&(Right_x<0||Right_y==SIZE||(Right_x>=0&&Right_y<SIZE&&RightUp_Info!=0)))){
    if(RtoL_count==3&&((Left_x<=13&&Left_y>=2&&aRecordBoard[Left_x+1][Left_y-1]==p&&aRecordBoard[Left_x+2][Left_y-2]==0)||(Right_x>=2&&Right_y<=13&&aRecordBoard[Right_x-1][Right_y+1]==p&&aRecordBoard[Right_x-2][Right_y+2]==0))){
      return other_score(4);
    }
    if(RtoL_count==2&&((Left_x<=12&&Left_y>=3&&aRecordBoard[Left_x+1][Left_y-1]==p&&aRecordBoard[Left_x+2][Left_y-2]==p&&aRecordBoard[Left_x+3][Left_y-3]==0)||(Right_x>=3&&Right_y<=12&&aRecordBoard[Right_x-1][Right_y+1]==p&&aRecordBoard[Right_x-2][Right_y+2]==p&&aRecordBoard[Right_x-2][Right_y+2]))){
      return other_score(4);
    }
    if(RtoL_count==2&&((Left_x<=13&&Left_y>=2&&aRecordBoard[Left_x+1][Left_y-1]==p&&aRecordBoard[Left_x+2][Left_y-2]==0)||(Right_x>=2&&Right_y<=13&&aRecordBoard[Right_x-1][Right_y+1]==p&&aRecordBoard[Right_x-2][Right_y+2]==0))){
      return other_score(3);
    }
    if(RtoL_count==1&&((Left_x<=13&&Left_y>=2&&aRecordBoard[Left_x+1][Left_y-1]==p&&aRecordBoard[Left_x+2][Left_y-2]==0)||(Right_x>=2&&Right_y<=13&&aRecordBoard[Right_x-1][Right_y+1]==p&&aRecordBoard[Right_x-2][Right_y+2]==0))){
      return other_score(2);
    }
    return num_to_Score_HalfLive(RtoL_count);
  }
  //死
  else
	  return num_to_Score_Death(RtoL_count);
}
//查询综合得分最高的落子位置
void GreatScore(int *Info_x,int *Info_y){
        extern int SingleScore[SIZE][SIZE];
	int Great_x=0,Great_y=0;
	int Great_Score=SingleScore[0][0];
	int i,j;
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			if(SingleScore[i][j]>Great_Score){
				Great_Score=SingleScore[i][j];
				Great_x=i;
				Great_y=j;
			}
		}
	}
	*Info_x=Great_x;
	*Info_y=Great_y;
}
//将活子转化为得分
int num_to_Score_Live(int num){
	if(num>=5)
	  return WIN;
	else{
		switch(num){
			case 4:return LIVE_FOUR;
			       break;
			case 3:return LIVE_THREE;
			       break;
			case 2:return LIVE_TWO;
			       break;
			case 1:return LIVE_ONE;
			       break;
			default:return 0;
		}
	}
}
//将半活子转化为得分
int num_to_Score_HalfLive(int num){
	if(num>=5)
	  return WIN;
	else{
		switch(num){
			case 4:return HALF_LIVE_FOUR;
			      break;
			case 3:return HALF_LIVE_THREE;
			       break;
			case 2:return HALF_LIVE_TWO;
			       break;
			case 1:return HALF_LIVE_ONE;
		    	   break;
			default:return 0;
		}
	}
}
//将死子转化为得分
int num_to_Score_Death(int num){
	if(num>=5)
	  return WIN;
	else{
		switch(num){
			case 4:return DEATH_FOUR;
			       break;
			case 3:return DEATH_THREE;
		    	   break;
			case 2:return DEATH_TWO;
	     		   break;
			case 1:return DEATH_ONE;
			       break;
			default:return 0;
		}
	}
}
//另一种半活，隔空半活
int other_score(int num){
  switch (num) {
    case 2:return O_HLIVE_TW;
           break;
    case 3:return O_HLIVE_TH;
           break;
    case 4:return O_HLIVE_F;
           break;
    default:return 0;
  }
}
