#include<iostream>
#include"head.h"
using namespace std;

extern short now[][9];
extern short record[][9][9];
extern int turns;

void end_game()//������Ϸ
{
	print_board(1);
	int i=0,j=0,b=0,w=0;
	for(i=1;i<9;i++)
	{
		for(j=1;j<9;j++)
		{
			if(now[i][j]==1)
				b++;
			if(now[i][j]==2)
				w++;
		}
	}
	if(b<w)
		cout<<"��ϲ�׷���ʤ��"<<endl;
	if(b==w)
		cout<<"ƽ�֣�������ս��"<<endl;
	if(b>w)
		cout<<"��ϲ�ڷ���ʤ��"<<endl;
}