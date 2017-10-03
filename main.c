#include <string.h>
#include <stdio.h>
#include<stdlib.h>
#include "My_head.h"
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
int aRecordBoard[SIZE][SIZE];		
char play1Pic[]="●";		
char play2Pic[]="◎";		
char _play1Pic[]="▲";		
char _play2Pic[]="△";		
		
//棋手最近一次落子时的坐标		
int current_x;     //行号		
int current_y;     //列号		
		
		
void initRecordBorard(void);                             //初始化棋盘		
void recordtoDisplayArray(int x_now,int y_now);          //转换落子位置		
void displayBoard(void);                                 //显示棋盘		
void set_piece(int x,int y, int player);                 //落子		
int win_judge(int x_now,int y_now,int player);           //是否达到胜利条件判断函数		
int Ban_Judge(int n_now,int y_now,int player);           //是否禁手判断函数		
void getinput(int *x,int *y);                            //获取人输入		
void GetInput(int *x,int *y,int p);                      //AI 输入		
void GetFirst(int *x,int *y);                            //AI 先手时的第一次落子		
void Trans(int *x);                                      //因棋盘显示需要转化横坐标
		
void main(){		
	int mode_choose;              //选择模式		
	printf("Welcme Five-Point-Game! Please choose the Game mode:\n");		
	printf("(1) Man against Man: Press 1\n");		
	printf("(2) Man against Machine: Press 2\n");		
    scanf("%d",&mode_choose);		
    //人人模式		
	switch(mode_choose){		
      case 1:{		
				 initRecordBorard();    //初始化棋盘		
				 recordtoDisplayArray(x_now,y_now);		
				 displayBoard();		
	     		
				 for(;;){		
		
					 if (k%2==1){		
						 printf("Player 1 input:");         //玩家１落子		
						 getinput(&x_now,&y_now);		
						 Trans(&x_now);
						 		
						 if(x_now<0||x_now>SIZE-1||y_now<0||y_now>SIZE-1){      //判断是否超出边界		
							 printf("\nInput error:out of range! Please enter again!\n");		
							 continue;		
						 }		
						 		
						 if(aRecordBoard[x_now][y_now]!=0){            //判断是否已经被落子		
							 printf("\nInput error:the position has been occupied! Please enter again!\n");		
							 continue;		
						 }		
						 		
						 set_piece(x_now,y_now,PLAYER1);                //落子		
						 recordtoDisplayArray(x_now,y_now);		
						 displayBoard();		
						 		
						 judge=win_judge(x_now,y_now,PLAYER1);        //判断是否达到胜利条件		
						 		
						 if(judge==1){                                //胜利		
							 printf("Player 1 has won the game!\n");		
							 return;		
						 }		
						 if(judge==-1){                             //平局		
							 printf("The game has ended in a draw!\n");		
							 return;		
						 }		
					 }		
					 		
					 else{		
						 printf("Player 2 input:");               //玩家２落子		
						 getinput(&x_now,&y_now);		
						 Trans(&x_now);
						 		
						 if(x_now<0||x_now>SIZE-1||y_now<0||y_now>SIZE-1){          //判断是否超出边界		
							 printf("\nInput error:out of range! Please enter again!\n");		
							 continue;		
						 }		
						 if(aRecordBoard[x_now][y_now]!=0){                       //判断是否已经被落子		
							 printf("\nInput error:the position has been occupied! Please enter again!\n");		
							 continue;		
						 }		
						 		
						 set_piece(x_now,y_now,PLAYER2);                 //落子		
						 recordtoDisplayArray(x_now,y_now);		
						 displayBoard();		
		
						 judge=win_judge(x_now,y_now,PLAYER2);         //判断是否达到胜利条件		
						 		
						 if(judge==1){                               //胜利		
							 printf("Player 2 has won the game!\n");   		
							 return ;		
						 }		
						 if(judge==-1){                        //平局		
							 printf("The game has ended in a draw!\n");		
							 return ;		
						 }		
					 }		
					 k++;		
				 }		
				 break;		
			 }		
	  case 2:{		
				 //人机模式		
				 int first_choose;		
				 //选择人先手或者机器先手		
				 printf("Please choose Offensive hand or Defensive hand\n");		
				 printf("(1) Human first: Press 1\n");		
				 printf("(2) AI first: Press 2\n");		
				 scanf("%d",&first_choose);		
				 		
				 switch(first_choose){		
					 //人先手		
					 case 1:{		
								initRecordBorard();          //初始化棋盘		
								recordtoDisplayArray(x_now,y_now);		
								displayBoard();		
										
								for(;;){		
									if(k%2==1){		
										printf("Human input:");      //人玩家落子		
										getinput(&x_now,&y_now);		
										Trans(&x_now);
		
										if(x_now<0||x_now>SIZE-1||y_now<0||y_now>SIZE-1){     //是否超出边界		
											printf("\nInput error:out of range! Please enter again!\n");		
											continue;		
										}		
										if(aRecordBoard[x_now][y_now]!=0){              //是否已经被落子		
											printf("\nInput error:the position has been occupied! Please enter again!\n");		
											continue;		
										}		
		
										set_piece(x_now,y_now,FIRST_PLAYER);		
										recordtoDisplayArray(x_now,y_now);		
										displayBoard();		
		
										ban=Ban_Judge(x_now,y_now,FIRST_PLAYER);      //判断是否禁手		
										if(ban==1){		
											printf("Prohibitive mathod! AI has won the game!\n");		
											return ;		
										}		
		
										judge=win_judge(x_now,y_now,FIRST_PLAYER);          //判断是否胜利		
												
										if(judge==1){           //胜利		
											printf("Congratulation! Human has won the game!\n");		
											return ;		
										}		
										if(judge==-1){           //平局		
											printf("The game has ended in a draw!\n");		
											return ;		
										}		
									}		
									else{		
										GetInput(&x_now,&y_now,SECOND_PLAYER);         //AI 落子		
										set_piece(x_now,y_now,SECOND_PLAYER);		
										recordtoDisplayArray(x_now,y_now);		
										displayBoard();		
		
										printf("AI Input:%d%c\n",SIZE - x_now,y_now+'A');		
		
										judge=win_judge(x_now,y_now,SECOND_PLAYER);    //判断是否达到胜利		
												
										if(judge==1){           //胜利		
											printf("AI has won the game!\n");		
											return ;		
										}		
										if(judge==-1){                //平局		
											printf("The game ended in a draw!\n");		
											return ;		
										}		
									}		
									k++;		
								}		
								break;		
							}		
					 case 2:{		
								//AI 先手，初始化棋盘		
								initRecordBorard();		
								recordtoDisplayArray(x_now,y_now);		
								displayBoard();		
		
								GetFirst(&x_now,&y_now);   //首次落子，在棋盘中间九个点随机选择一个落子		
										
								set_piece(x_now,y_now,FIRST_PLAYER);		
								recordtoDisplayArray(x_now,y_now);		
								displayBoard();		
		
								printf("AI Input:%d%c\n",SIZE - x_now,y_now+'A');		
										
								for(;;){		
									if(k%2==0){		
										GetInput(&x_now,&y_now,FIRST_PLAYER);    //AI落子 		
												
										set_piece(x_now,y_now,FIRST_PLAYER);		
										recordtoDisplayArray(x_now,y_now);		
										displayBoard();		
										printf("AI Input:%d%c\n",SIZE - x_now,y_now+'A');		
		
										judge=win_judge(x_now,y_now,FIRST_PLAYER);    //判断胜利		
												
										if(judge==1){        //胜利		
											printf("AI has won the game!\n");		
											return;		
										}		
										if(judge==-1){        //平局		
											printf("The game ended in a draw!\n");		
											return ;		
										}		
									}		
											
									else{		
										printf("Human Input:");         //人玩家落子		
										getinput(&x_now,&y_now);		
										Trans(&x_now);
		
										if(x_now<0||x_now>SIZE-1||y_now<0||y_now>SIZE-1){         //是否超出边界		
											printf("\nInput error:out of range! Please enter again!\n");		
											continue;		
										}		
										if(aRecordBoard[x_now][y_now]!=0){                //是否已经被落子		
											printf("\nInput error:the position has been occupied! Please enter again!\n");		
											continue;		
										}		
		
										set_piece(x_now,y_now,SECOND_PLAYER);         //在棋盘上落子		
										recordtoDisplayArray(x_now,y_now);		
										displayBoard();		
		
										judge=win_judge(x_now,y_now,SECOND_PLAYER);       // 判断胜利		
												
										if(judge==1){                 //胜利		
											printf("Congratulation! Human has won the game!\n");		
											return ;		
										}		
										if(judge==-1){              //平局		
											printf("The game has ended in a draw\n");		
											return ;		
										}		
									}		
									k++;		
								}		
								break;		
							}		
		
					 default:printf("Error: No such mode!\n");        //模式选择非法		
				 }		
				 break;		
			 }		
	  		
	  default:printf("Error: No such mode!\n");               //模式选择非法		
	}		
}		
		
//将落子位置记录到数组中		
void set_piece(int x,int y, int player){		
	aRecordBoard[x][y]=player;		
	current_x=x;		
	current_y=y;		
}		
		
//初始化棋盘，将整个棋盘初始化为０		
void initRecordBorard(void){		
	int i,j;		
	for(i=0;i<SIZE;i++)		
	  for(j=0;j<SIZE;j++)		
		aRecordBoard[i][j]=0;		
}		
		
//获取屏幕输入的函数		
void getinput(int *x,int *y){		
	int i,j;		
	scanf("%d",&i);		
	j=getchar()-'A';		
	*x=i-1,*y=j;		
}		
		
//将记录数值的数组转换到棋盘显示的数组中		
void recordtoDisplayArray(int x_now,int y_now){		
	int i,j;		
	//将aInitDisplayBoardArray中记录的空棋盘，复制到aDisplayBoardArray中		
	for(i=0;i<SIZE+1;i++) 		
	  for(j=0;j<2*SIZE+1;j++)		
		aDisplayBoardArray[i][j]=aInitDisplayBoardArray[i][j];		
	//扫描aRecordBoard，当遇到非0的元素，将●或者◎复制到aDisplayBoardArray的相应位置上		
	//注意：aDisplayBoardArray所记录的字符是中文字符，每个字符占2个字节。●和◎也是中文字符，每个也占2个字节		
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
		
//在屏幕上显示棋盘		
void displayBoard(void){		
	int i;		
	system("clear");   //清屏 		
	//第二步：将aDisplayBoardArray输出到屏幕上		
	for(i=0;i<SIZE;i++){		
		if(i<6)		
		  printf("%d",SIZE - i);		
		else 		
		  printf("%d ",SIZE - i);		
		printf("%s\n",aDisplayBoardArray[i]);		
	}		
	printf("  %s\n",aDisplayBoardArray[SIZE]);		
} 

void Trans(int *x){
	*x = SIZE - 1 - *x;
}
