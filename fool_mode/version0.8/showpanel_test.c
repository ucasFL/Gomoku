#include <string.h>
#include <stdio.h>
#include<stdlib.h>
#include "my_header.h"
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
int aRecordBoard[SIZE][SIZE];//
char play1Pic[]="��";
char play2Pic[]="��";
char _play1Pic[]="��";
char _play2Pic[]="��";
//�������һ������ʱ������
int current_x;//�к�
int current_y;//�к�


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
//////////////////////////////////////////////����ģʽ
      case 1:{
	//���㲢��ʾ������
    initRecordBorard();
	recordtoDisplayArray(x_now,y_now);
    displayBoard();
	for(;;){
		//��ң�����
		if (k%2==1){
    printf("Player 1 input:\n");
	//�ȴ�����
	getinput(&x_now,&y_now);
	//�ж������Ƿ�Ϸ�
   if(x_now<0||x_now>SIZE-1||y_now<0||y_now>SIZE-1){
	   printf("\nInput error:out of range!\nPlease enter again:\n\n");
	   continue;
   }
    if(aRecordBoard[x_now][y_now]!=0){
             printf("\nInput error:the position has been occupied!\nPlease enter again:\n\n");
             continue;
    }
    //������������
	set_piece(x_now,y_now,PLAYER1);
        recordtoDisplayArray(x_now,y_now);
	displayBoard();
	//�ж���ң������Ժ��Ƿ�ﵽʤ�����������ﵽ������Ϸ����
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
	//��ң�����
	  printf("Player 2 input:\n");
	  //�ȴ�����
          getinput(&x_now,&y_now);
	  //�ж������Ƿ�Ϸ�
	if(x_now<0||x_now>SIZE-1||y_now<0||y_now>SIZE-1){
		printf("\nInput error:out of range!\nPlease enter again:\n\n");
		continue;
	}
        if(aRecordBoard[x_now][y_now]!=0){
             printf("\nInput error:the position has been occupied!\nPlease enter again:\n\n");
             continue;
    }
   
	//������������
	set_piece(x_now,y_now,PLAYER2);
	recordtoDisplayArray(x_now,y_now);
	displayBoard();
	//�ж���ң������Ժ��Ƿ�ﵽʤ�����������ﵽ������Ϸ����
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
///////////////////////////////////////////////////////////////////�˻�ģʽ
		int first_choose;
	//////////////////////////////////
	//ѡ�������ֻ��߻�������
	printf("Please choose Offensive hand or Defensive hand\n");
	printf("(1) Man first: Press 1\n");
    printf("(2) Machine first: Press 2\n");
	scanf("%d",&first_choose);
	switch(first_choose){
/////////////////////////////////////////////////////////
////////////������
		case 1:{
////////////////////////////////////////////////////////
///////��ʼ������
				   initRecordBorard();
                   recordtoDisplayArray(x_now,y_now);
				   displayBoard();
				   for(;;){
					   if(k%2==1){
/////////////////////////////��ȡ����
						   printf("Man input:\n");
						   getinput(&x_now,&y_now);
/////////////////////////////�ж������Ƿ�Ϸ�
						   if(x_now<0||x_now>SIZE-1||y_now<0||y_now>SIZE-1){
							   printf("\nInput error:out of range!\nPlease enter again\n\n");
							   continue;
						   }
						   if(aRecordBoard[x_now][y_now]!=0){
							   printf("\nInput error:the position has been occupied!\nPlease enter again\n\n");
							   continue;
						   }
						   //������������
						   set_piece(x_now,y_now,FIRST_PLAYER);
						   recordtoDisplayArray(x_now,y_now);
						   displayBoard();
						   //�ж��Ƿ����
						   ban=Ban_Judge(x_now,y_now,FIRST_PLAYER);
						   if(ban==1){
							   printf("Prohibitive mathod! Machine player has won the game!\n");
							   return ;
						   }
						   //�ж�����������Ժ��Ƿ�ﵽʤ���������ߴﵽƽ��
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
						   ///��������
						   machine_input(&x_now,&y_now);
						   set_piece(x_now,y_now,SECOND_PLAYER);
						   recordtoDisplayArray(x_now,y_now);
						   displayBoard();
 printf("Machine Input:%d%c\n",x_now+1,y_now+'A');
						   //�ж��Ƿ�ﵽʤ��
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
		//��������
		// ���̳�ʼ��
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
						//��������
						machine_input_mcf(&x_now,&y_now);
						set_piece(x_now,y_now,FIRST_PLAYER);
						recordtoDisplayArray(x_now,y_now);
						displayBoard();
 printf("Machine Input:%d%c\n",x_now+1,y_now+'A');
						//�ж��Ƿ�ﵽʤ����ƽ��
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
/////////////////////////////�ж������Ƿ�Ϸ�
						   if(x_now<0||x_now>SIZE-1||y_now<0||y_now>SIZE-1){
							   printf("\nInput error:out of range!\nPlease enter again\n\n");
							   continue;
						   }
						   if(aRecordBoard[x_now][y_now]!=0){
							   printf("\nInput error:the position has been occupied!\nPlease enter again\n\n");
							   continue;
						   }
						   //������������
						   set_piece(x_now,y_now,SECOND_PLAYER);
						   recordtoDisplayArray(x_now,y_now);
						   displayBoard();
						   //�ж�����������Ժ��Ƿ�ﵽʤ���������ߴﵽƽ��
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
		///ģʽѡ��Ƿ�
		default:printf("Error: No such mode!\n");
                     }
	break;
	}
			 ///ģʽѡ��Ƿ�
				 default:printf("Error: No such mode!\n");
			 }
}
///////////////////////////////////////////////////////////// 
// �������ƣ� set_piece 
// ���ã�������player����������x��y��
//  �������� 
// ����ֵ���� 
/////////////////////////////////////////////////////////////

void set_piece(int x,int y, int player){
	aRecordBoard[x][y]=player;
	current_x=x;
	current_y=y;
}



/////////////////////////////////////////////////////////////
// �������ƣ�initRecordBorard
// ���ã���ʼ����ά����aRecordBoard
//  ��������
// ����ֵ����
/////////////////////////////////////////////////////////////
void initRecordBorard(void){
	//ͨ��˫��ѭ������aRecordBoard��0
	int i,j;
	for(i=0;i<SIZE;i++)
	  for(j=0;j<SIZE;j++)
		aRecordBoard[i][j]=0;
}

/////////////////////////////////////
///��ȡ����ĺ���
void getinput(int *x,int *y){
        int i,j;
	scanf("%d",&i);
	j=getchar()-'A';
	*x=i-1,*y=j;
}

/////////////////////////////////////////////////////////////
// �������ƣ�recordtoDisplayArray
// ���ã���aRecordBoard�м�¼������λ�ã�ת����aDisplayBoardArray��
//  ��������
// ����ֵ����
/////////////////////////////////////////////////////////////
void recordtoDisplayArray(int x_now,int y_now){
	int i,j;
	//��һ������aInitDisplayBoardArray�м�¼�Ŀ����̣����Ƶ�aDisplayBoardArray��
    for(i=0;i<SIZE+1;i++)
	  for(j=0;j<2*SIZE+1;j++)
		aDisplayBoardArray[i][j]=aInitDisplayBoardArray[i][j];
	//�ڶ�����ɨ��aRecordBoard����������0��Ԫ�أ�������ߡ��Ƶ�aDisplayBoardArray����Ӧλ����
	//ע�⣺aDisplayBoardArray����¼���ַ��������ַ���ÿ���ַ�ռ2���ֽڡ���͡�Ҳ�������ַ���ÿ��Ҳռ2���ֽڡ�
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
/////////////////////////////////////////////////////////////
// �������ƣ�displayBoard
// ���ã���aDisplayBoardArray�м�¼�����̣���ʽ����Ļ��
//  ��������
// ����ֵ����
/////////////////////////////////////////////////////////////
void displayBoard(void){
	int i;
	//��һ��������
	system("clear");   //����  
	//�ڶ�������aDisplayBoardArray�������Ļ��
	for(i=0;i<SIZE;i++){
		if(i<9)
		printf("%d ",i+1);
		else 
		  printf("%d",i+1);
		printf("%s\n",aDisplayBoardArray[i]);
	}
	printf("  %s\n",aDisplayBoardArray[SIZE]);
} 
