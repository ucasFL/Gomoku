#include <string.h>
#include <stdio.h>
#include<stdlib.h>
#include "my_header.h"
int x_now=0,y_now=0;
int judge;
int k=1;
int ban;
//棋盘使用Unicode画的，一个符号占两个char，所以要*2，+1是为了末尾的'\0'
char aInitDisplayBoardArray[SIZE+1][SIZE*2+1] = 
{
	"┏┯┯┯┯┯┯┯┯┯┯┯┯┯┓",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┗┷┷┷┷┷┷┷┷┷┷┷┷┷┛",
	"A B C D E F G H I J K L M N O" 
};
//此数组用于显示
char aDisplayBoardArray[SIZE+1][SIZE*2+1];
//此数组用于算法计算使用
int aRecordBoard[SIZE][SIZE];//
char play1Pic[]="●";
char play2Pic[]="◎";
char _play1Pic[]="▲";
char _play2Pic[]="△";
//棋手最近一次落子时的坐标
int current_x;//行号
int current_y;//列号


void initRecordBorard(void);
void recordtoDisplayArray(int x_now,int y_now);
void displayBoard(void);
void set_piece(int x,int y, int player);
int win_judge(int x_now,int y_now,int player);
int Ban_Judge(int n_now,int y_now,int player);
void getinput(int *x,int *y);
void machine_input(int *x,int *y);
void machine_input_mcf(int *x,int *y);
void GetFirst(int *x,int *y);

void main()
{
	int mode_choose;
	printf("Welcme Five-Point-Game! Please choose the Game mode:\n");
	printf("(1) Man against Man: Press 1\n");
	printf("(2) Man against Machine: Press 2\n");
    scanf("%d",&mode_choose);
	switch(mode_choose){
//////////////////////////////////////////////人人模式
      case 1:{
	//清零并显示出棋盘
    initRecordBorard();
	recordtoDisplayArray(x_now,y_now);
    displayBoard();
	for(;;){
		//玩家１落子
		if (k%2==1){
    printf("Player 1 input:\n");
	//等待输入
	getinput(&x_now,&y_now);
	//判断输入是否合法
   if(x_now<0||x_now>SIZE-1||y_now<0||y_now>SIZE-1){
	   printf("\nInput error:out of range!\nPlease enter again:\n\n");
	   continue;
   }
    if(aRecordBoard[x_now][y_now]!=0){
             printf("\nInput error:the position has been occupied!\nPlease enter again:\n\n");
             continue;
    }
    //在棋盘上落子
	set_piece(x_now,y_now,PLAYER1);
        recordtoDisplayArray(x_now,y_now);
	displayBoard();
	//判断玩家１落子以后是否达到胜利条件，若达到，则游戏结束
	judge=win_judge(x_now,y_now,PLAYER1);
	if(judge==1){
		printf("Player 1 has won the game!\n");
		return;
	}
	if(judge==-1){
		printf("The game has ended in a draw\n");
		return;
	}
   }

	  else{
	//玩家２落子
	  printf("Player 2 input:\n");
	  //等待输入
          getinput(&x_now,&y_now);
	  //判断输入是否合法
	if(x_now<0||x_now>SIZE-1||y_now<0||y_now>SIZE-1){
		printf("\nInput error:out of range!\nPlease enter again:\n\n");
		continue;
	}
        if(aRecordBoard[x_now][y_now]!=0){
             printf("\nInput error:the position has been occupied!\nPlease enter again:\n\n");
             continue;
    }
   
	//在棋盘上落子
	set_piece(x_now,y_now,PLAYER2);
	recordtoDisplayArray(x_now,y_now);
	displayBoard();
	//判断玩家２落子以后是否达到胜利条件，若达到，则游戏结束
	judge=win_judge(x_now,y_now,PLAYER2);
	if(judge==1){
		printf("Player 2 has won the game!\n");
		return ;
	}
	if(judge==-1){
		printf("The game has ended in a draw\n");
	    return ;
	}
 }
	k++;
     }
	break;
			 }
	  case 2:{
///////////////////////////////////////////////////////////////////人机模式
		int first_choose;
	//////////////////////////////////
	//选择人先手或者机器先手
	printf("Please choose Offensive hand or Defensive hand\n");
	printf("(1) Man first: Press 1\n");
    printf("(2) Machine first: Press 2\n");
	scanf("%d",&first_choose);
	switch(first_choose){
/////////////////////////////////////////////////////////
////////////人先手
		case 1:{
////////////////////////////////////////////////////////
///////初始化棋盘
				   initRecordBorard();
                   recordtoDisplayArray(x_now,y_now);
				   displayBoard();
				   for(;;){
					   if(k%2==1){
/////////////////////////////获取输入
						   printf("Man input:\n");
						   getinput(&x_now,&y_now);
/////////////////////////////判断输入是否合法
						   if(x_now<0||x_now>SIZE-1||y_now<0||y_now>SIZE-1){
							   printf("\nInput error:out of range!\nPlease enter again\n\n");
							   continue;
						   }
						   if(aRecordBoard[x_now][y_now]!=0){
							   printf("\nInput error:the position has been occupied!\nPlease enter again\n\n");
							   continue;
						   }
						   //在棋盘上落子
						   set_piece(x_now,y_now,FIRST_PLAYER);
						   recordtoDisplayArray(x_now,y_now);
						   displayBoard();
						   //判断是否禁手
						   ban=Ban_Judge(x_now,y_now,FIRST_PLAYER);
						   if(ban==1){
							   printf("Prohibitive mathod! Machine player has won the game!\n");
							   return ;
						   }
						   //判断人玩家落子以后是否达到胜利条件或者达到平局
						   judge=win_judge(x_now,y_now,FIRST_PLAYER);
						   if(judge==1){
							   printf("Man player has won the game!\n");
							   return ;
						   }
						   if(judge==-1){
							   printf("The game has ended in a draw\n");
							   return ;
						   }
					   }
					   else{
						   ///机器落子
						   machine_input(&x_now,&y_now);
						   set_piece(x_now,y_now,SECOND_PLAYER);
						   recordtoDisplayArray(x_now,y_now);
						   displayBoard();
 printf("Machine Input:%d%c\n",x_now+1,y_now+'A');
						   //判断是否达到胜负
						   judge=win_judge(x_now,y_now,SECOND_PLAYER);
						   if(judge==1){
							   printf("Machine player has won the game!\n");
							   return ;
						   }
						   if(judge==-1){
							   printf("The game ended in a draw!\n");
							   return ;
						   }
					   }
					   k++;
				   }
				   break;
			   }
		case 2:{
		//机器先手
		// 棋盘初始化
				initRecordBorard();
				recordtoDisplayArray(x_now,y_now);
				displayBoard();
				GetFirst(&x_now,&y_now);
				set_piece(x_now,y_now,FIRST_PLAYER);
				recordtoDisplayArray(x_now,y_now);
				displayBoard();
 printf("Machine Input:8H\n");
				for(;;){
					if(k%2==0){
						//机器输入
						machine_input_mcf(&x_now,&y_now);
						set_piece(x_now,y_now,FIRST_PLAYER);
						recordtoDisplayArray(x_now,y_now);
						displayBoard();
 printf("Machine Input:%d%c\n",x_now+1,y_now+'A');
						//判断是否达到胜利或平局
						judge=win_judge(x_now,y_now,FIRST_PLAYER);
						if(judge==1){
							printf("Machine player has won the game!\n");
							return;
						}
						if(judge==-1){
							printf("The game ended in a draw!\n");
							return ;
						}
					}
					else{
						  printf("Man input:\n");
						   getinput(&x_now,&y_now);
/////////////////////////////判断输入是否合法
						   if(x_now<0||x_now>SIZE-1||y_now<0||y_now>SIZE-1){
							   printf("\nInput error:out of range!\nPlease enter again\n\n");
							   continue;
						   }
						   if(aRecordBoard[x_now][y_now]!=0){
							   printf("\nInput error:the position has been occupied!\nPlease enter again\n\n");
							   continue;
						   }
						   //在棋盘上落子
						   set_piece(x_now,y_now,SECOND_PLAYER);
						   recordtoDisplayArray(x_now,y_now);
						   displayBoard();
						   //判断人玩家落子以后是否达到胜利条件或者达到平局
						   judge=win_judge(x_now,y_now,SECOND_PLAYER);
						   if(judge==1){
							   printf("Man player has won the game!\n");
							   return ;
						   }
						   if(judge==-1){
							   printf("The game has ended in a draw\n");
							   return ;
						   }
					   }
					k++;
				}
				break;
			   }
		///模式选择非法
		default:printf("Error: No such mode!\n");
                     }
	break;
	}
			 ///模式选择非法
				 default:printf("Error: No such mode!\n");
			 }
}
///////////////////////////////////////////////////////////// 
// 函数名称： set_piece 
// 作用：将棋手player的棋子落在x行y列
//  参数：无 
// 返回值：无 
/////////////////////////////////////////////////////////////

void set_piece(int x,int y, int player){
	aRecordBoard[x][y]=player;
	current_x=x;
	current_y=y;
}



/////////////////////////////////////////////////////////////
// 函数名称：initRecordBorard
// 作用：初始化二维数组aRecordBoard
//  参数：无
// 返回值：无
/////////////////////////////////////////////////////////////
void initRecordBorard(void){
	//通过双重循环，将aRecordBoard清0
	int i,j;
	for(i=0;i<SIZE;i++)
	  for(j=0;j<SIZE;j++)
		aRecordBoard[i][j]=0;
}

/////////////////////////////////////
///获取输入的函数
void getinput(int *x,int *y){
        int i,j;
	scanf("%d",&i);
	j=getchar()-'A';
	*x=i-1,*y=j;
}

/////////////////////////////////////////////////////////////
// 函数名称：recordtoDisplayArray
// 作用：将aRecordBoard中记录的棋子位置，转化到aDisplayBoardArray中
//  参数：无
// 返回值：无
/////////////////////////////////////////////////////////////
void recordtoDisplayArray(int x_now,int y_now){
	int i,j;
	//第一步：将aInitDisplayBoardArray中记录的空棋盘，复制到aDisplayBoardArray中
    for(i=0;i<SIZE+1;i++)
	  for(j=0;j<2*SIZE+1;j++)
		aDisplayBoardArray[i][j]=aInitDisplayBoardArray[i][j];
	//第二步：扫描aRecordBoard，当遇到非0的元素，将●或者◎复制到aDisplayBoardArray的相应位置上
	//注意：aDisplayBoardArray所记录的字符是中文字符，每个字符占2个字节。●和◎也是中文字符，每个也占2个字节。
    for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			//判断是否是玩家１所落的子，若是，则显示黑子
			if(aRecordBoard[i][j]==1){
				//判断是否是本次所落的子，若是，则落三角形子，否则，落圆形子
				if(i==x_now&&j==y_now){
					aDisplayBoardArray[i][2*j]=_play1Pic[0];
					aDisplayBoardArray[i][2*j+1]=_play1Pic[1];
				}
				else{
             	aDisplayBoardArray[i][2*j]=play1Pic[0];
				aDisplayBoardArray[i][2*j+1]=play1Pic[1];
				}
			}
			else if(aRecordBoard[i][j]==2){
				//等于２，说明是玩家２所落的子，显示白子
				if(i==x_now&&j==y_now){
					//判断是否是本次所落的子，若是，显示三角形子，否则，显示圆形子
					aDisplayBoardArray[i][2*j]=_play2Pic[0];
					aDisplayBoardArray[i][2*j+1]=_play2Pic[1];
				}
				else{
				aDisplayBoardArray[i][2*j]=play2Pic[0];
				aDisplayBoardArray[i][2*j+1]=play2Pic[1];
		       }
			}
	}
}
}
/////////////////////////////////////////////////////////////
// 函数名称：displayBoard
// 作用：将aDisplayBoardArray中记录的棋盘，显式到屏幕上
//  参数：无
// 返回值：无
/////////////////////////////////////////////////////////////
void displayBoard(void){
	int i;
	//第一步：清屏
	system("clear");   //清屏  
	//第二步：将aDisplayBoardArray输出到屏幕上
	for(i=0;i<SIZE;i++){
		if(i<9)
		printf("%d ",i+1);
		else 
		  printf("%d",i+1);
		printf("%s\n",aDisplayBoardArray[i]);
	}
	printf("  %s\n",aDisplayBoardArray[SIZE]);
} 
