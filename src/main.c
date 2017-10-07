#include <string.h>
#include <stdio.h>
#include<stdlib.h>
#include "My_head.h"
int x_now=0,y_now=0;
int judge;
int k=1;
int ban;
//����ʹ��Unicode���ģ�һ������ռ����char������Ҫ*2��+1��Ϊ��ĩβ��'\0'
char aInitDisplayBoardArray[SIZE+1][SIZE*2+1] = 
{
	"���өөөөөөөөөөөөө�",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"���۩۩۩۩۩۩۩۩۩۩۩۩۩�",
	"A B C D E F G H I J K L M N O" 
};
//������������ʾ
char aDisplayBoardArray[SIZE+1][SIZE*2+1];		
		
//�����������㷨����ʹ��		
int aRecordBoard[SIZE][SIZE];		
char play1Pic[]="��";		
char play2Pic[]="��";		
char _play1Pic[]="��";		
char _play2Pic[]="��";		
		
//�������һ������ʱ������		
int current_x;     //�к�		
int current_y;     //�к�		
		
		
void initRecordBorard(void);                             //��ʼ������		
void recordtoDisplayArray(int x_now,int y_now);          //ת������λ��		
void displayBoard(void);                                 //��ʾ����		
void set_piece(int x,int y, int player);                 //����		
int win_judge(int x_now,int y_now,int player);           //�Ƿ�ﵽʤ�������жϺ���		
int Ban_Judge(int n_now,int y_now,int player);           //�Ƿ�����жϺ���		
void getinput(int *x,int *y);                            //��ȡ������		
void GetInput(int *x,int *y,int p);                      //AI ����		
void GetFirst(int *x,int *y);                            //AI ����ʱ�ĵ�һ������		
void Trans(int *x);                                      //��������ʾ��Ҫת��������
		
void main(){		
	int mode_choose;              //ѡ��ģʽ		
	printf("Welcme Five-Point-Game! Please choose the Game mode:\n");		
	printf("(1) Man against Man: Press 1\n");		
	printf("(2) Man against Machine: Press 2\n");		
    scanf("%d",&mode_choose);		
    //����ģʽ		
	switch(mode_choose){		
      case 1:{		
				 initRecordBorard();    //��ʼ������		
				 recordtoDisplayArray(x_now,y_now);		
				 displayBoard();		
	     		
				 for(;;){		
		
					 if (k%2==1){		
						 printf("Player 1 input:");         //��ң�����		
						 getinput(&x_now,&y_now);		
						 Trans(&x_now);
						 		
						 if(x_now<0||x_now>SIZE-1||y_now<0||y_now>SIZE-1){      //�ж��Ƿ񳬳��߽�		
							 printf("\nInput error:out of range! Please enter again!\n");		
							 continue;		
						 }		
						 		
						 if(aRecordBoard[x_now][y_now]!=0){            //�ж��Ƿ��Ѿ�������		
							 printf("\nInput error:the position has been occupied! Please enter again!\n");		
							 continue;		
						 }		
						 		
						 set_piece(x_now,y_now,PLAYER1);                //����		
						 recordtoDisplayArray(x_now,y_now);		
						 displayBoard();		
						 		
						 judge=win_judge(x_now,y_now,PLAYER1);        //�ж��Ƿ�ﵽʤ������		
						 		
						 if(judge==1){                                //ʤ��		
							 printf("Player 1 has won the game!\n");		
							 return;		
						 }		
						 if(judge==-1){                             //ƽ��		
							 printf("The game has ended in a draw!\n");		
							 return;		
						 }		
					 }		
					 		
					 else{		
						 printf("Player 2 input:");               //��ң�����		
						 getinput(&x_now,&y_now);		
						 Trans(&x_now);
						 		
						 if(x_now<0||x_now>SIZE-1||y_now<0||y_now>SIZE-1){          //�ж��Ƿ񳬳��߽�		
							 printf("\nInput error:out of range! Please enter again!\n");		
							 continue;		
						 }		
						 if(aRecordBoard[x_now][y_now]!=0){                       //�ж��Ƿ��Ѿ�������		
							 printf("\nInput error:the position has been occupied! Please enter again!\n");		
							 continue;		
						 }		
						 		
						 set_piece(x_now,y_now,PLAYER2);                 //����		
						 recordtoDisplayArray(x_now,y_now);		
						 displayBoard();		
		
						 judge=win_judge(x_now,y_now,PLAYER2);         //�ж��Ƿ�ﵽʤ������		
						 		
						 if(judge==1){                               //ʤ��		
							 printf("Player 2 has won the game!\n");   		
							 return ;		
						 }		
						 if(judge==-1){                        //ƽ��		
							 printf("The game has ended in a draw!\n");		
							 return ;		
						 }		
					 }		
					 k++;		
				 }		
				 break;		
			 }		
	  case 2:{		
				 //�˻�ģʽ		
				 int first_choose;		
				 //ѡ�������ֻ��߻�������		
				 printf("Please choose Offensive hand or Defensive hand\n");		
				 printf("(1) Human first: Press 1\n");		
				 printf("(2) AI first: Press 2\n");		
				 scanf("%d",&first_choose);		
				 		
				 switch(first_choose){		
					 //������		
					 case 1:{		
								initRecordBorard();          //��ʼ������		
								recordtoDisplayArray(x_now,y_now);		
								displayBoard();		
										
								for(;;){		
									if(k%2==1){		
										printf("Human input:");      //���������		
										getinput(&x_now,&y_now);		
										Trans(&x_now);
		
										if(x_now<0||x_now>SIZE-1||y_now<0||y_now>SIZE-1){     //�Ƿ񳬳��߽�		
											printf("\nInput error:out of range! Please enter again!\n");		
											continue;		
										}		
										if(aRecordBoard[x_now][y_now]!=0){              //�Ƿ��Ѿ�������		
											printf("\nInput error:the position has been occupied! Please enter again!\n");		
											continue;		
										}		
		
										set_piece(x_now,y_now,FIRST_PLAYER);		
										recordtoDisplayArray(x_now,y_now);		
										displayBoard();		
		
										ban=Ban_Judge(x_now,y_now,FIRST_PLAYER);      //�ж��Ƿ����		
										if(ban==1){		
											printf("Prohibitive mathod! AI has won the game!\n");		
											return ;		
										}		
		
										judge=win_judge(x_now,y_now,FIRST_PLAYER);          //�ж��Ƿ�ʤ��		
												
										if(judge==1){           //ʤ��		
											printf("Congratulation! Human has won the game!\n");		
											return ;		
										}		
										if(judge==-1){           //ƽ��		
											printf("The game has ended in a draw!\n");		
											return ;		
										}		
									}		
									else{		
										GetInput(&x_now,&y_now,SECOND_PLAYER);         //AI ����		
										set_piece(x_now,y_now,SECOND_PLAYER);		
										recordtoDisplayArray(x_now,y_now);		
										displayBoard();		
		
										printf("AI Input:%d%c\n",SIZE - x_now,y_now+'A');		
		
										judge=win_judge(x_now,y_now,SECOND_PLAYER);    //�ж��Ƿ�ﵽʤ��		
												
										if(judge==1){           //ʤ��		
											printf("AI has won the game!\n");		
											return ;		
										}		
										if(judge==-1){                //ƽ��		
											printf("The game ended in a draw!\n");		
											return ;		
										}		
									}		
									k++;		
								}		
								break;		
							}		
					 case 2:{		
								//AI ���֣���ʼ������		
								initRecordBorard();		
								recordtoDisplayArray(x_now,y_now);		
								displayBoard();		
		
								GetFirst(&x_now,&y_now);   //�״����ӣ��������м�Ÿ������ѡ��һ������		
										
								set_piece(x_now,y_now,FIRST_PLAYER);		
								recordtoDisplayArray(x_now,y_now);		
								displayBoard();		
		
								printf("AI Input:%d%c\n",SIZE - x_now,y_now+'A');		
										
								for(;;){		
									if(k%2==0){		
										GetInput(&x_now,&y_now,FIRST_PLAYER);    //AI���� 		
												
										set_piece(x_now,y_now,FIRST_PLAYER);		
										recordtoDisplayArray(x_now,y_now);		
										displayBoard();		
										printf("AI Input:%d%c\n",SIZE - x_now,y_now+'A');		
		
										judge=win_judge(x_now,y_now,FIRST_PLAYER);    //�ж�ʤ��		
												
										if(judge==1){        //ʤ��		
											printf("AI has won the game!\n");		
											return;		
										}		
										if(judge==-1){        //ƽ��		
											printf("The game ended in a draw!\n");		
											return ;		
										}		
									}		
											
									else{		
										printf("Human Input:");         //���������		
										getinput(&x_now,&y_now);		
										Trans(&x_now);
		
										if(x_now<0||x_now>SIZE-1||y_now<0||y_now>SIZE-1){         //�Ƿ񳬳��߽�		
											printf("\nInput error:out of range! Please enter again!\n");		
											continue;		
										}		
										if(aRecordBoard[x_now][y_now]!=0){                //�Ƿ��Ѿ�������		
											printf("\nInput error:the position has been occupied! Please enter again!\n");		
											continue;		
										}		
		
										set_piece(x_now,y_now,SECOND_PLAYER);         //������������		
										recordtoDisplayArray(x_now,y_now);		
										displayBoard();		
		
										judge=win_judge(x_now,y_now,SECOND_PLAYER);       // �ж�ʤ��		
												
										if(judge==1){                 //ʤ��		
											printf("Congratulation! Human has won the game!\n");		
											return ;		
										}		
										if(judge==-1){              //ƽ��		
											printf("The game has ended in a draw\n");		
											return ;		
										}		
									}		
									k++;		
								}		
								break;		
							}		
		
					 default:printf("Error: No such mode!\n");        //ģʽѡ��Ƿ�		
				 }		
				 break;		
			 }		
	  		
	  default:printf("Error: No such mode!\n");               //ģʽѡ��Ƿ�		
	}		
}		
		
//������λ�ü�¼��������		
void set_piece(int x,int y, int player){		
	aRecordBoard[x][y]=player;		
	current_x=x;		
	current_y=y;		
}		
		
//��ʼ�����̣����������̳�ʼ��Ϊ��		
void initRecordBorard(void){		
	int i,j;		
	for(i=0;i<SIZE;i++)		
	  for(j=0;j<SIZE;j++)		
		aRecordBoard[i][j]=0;		
}		
		
//��ȡ��Ļ����ĺ���		
void getinput(int *x,int *y){		
	int i,j;		
	scanf("%d",&i);		
	j=getchar()-'A';		
	*x=i-1,*y=j;		
}		
		
//����¼��ֵ������ת����������ʾ��������		
void recordtoDisplayArray(int x_now,int y_now){		
	int i,j;		
	//��aInitDisplayBoardArray�м�¼�Ŀ����̣����Ƶ�aDisplayBoardArray��		
	for(i=0;i<SIZE+1;i++) 		
	  for(j=0;j<2*SIZE+1;j++)		
		aDisplayBoardArray[i][j]=aInitDisplayBoardArray[i][j];		
	//ɨ��aRecordBoard����������0��Ԫ�أ�������ߡ��Ƶ�aDisplayBoardArray����Ӧλ����		
	//ע�⣺aDisplayBoardArray����¼���ַ��������ַ���ÿ���ַ�ռ2���ֽڡ���͡�Ҳ�������ַ���ÿ��Ҳռ2���ֽ�		
	for(i=0;i<SIZE;i++){		
		for(j=0;j<SIZE;j++){		
			//�ж��Ƿ�����ң�������ӣ����ǣ�����ʾ����		
			if(aRecordBoard[i][j]==1){		
				//�ж��Ƿ��Ǳ���������ӣ����ǣ������������ӣ�������Բ����		
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
				//���ڣ���˵������ң�������ӣ���ʾ����		
				if(i==x_now&&j==y_now){		
					//�ж��Ƿ��Ǳ���������ӣ����ǣ���ʾ�������ӣ�������ʾԲ����		
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
		
//����Ļ����ʾ����		
void displayBoard(void){		
	int i;		
	system("clear");   //���� 		
	//�ڶ�������aDisplayBoardArray�������Ļ��		
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
