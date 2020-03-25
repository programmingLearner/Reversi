#include<iostream>
using namespace std;

extern short now[][9];
extern short record[][9][9];
extern int turns;

bool my_reverse(int i,int j)//翻转棋子
{
	bool judge=0;//1表示有翻转，0表示无翻转
	short color=now[i][j];
	int i_search=i,j_search=j;
	int m=0,n=0;
	//翻转下面
	i_search++;
	while((i_search<9)&&(now[i_search][j]==3-color))
		i_search++;
	if((i_search<9)&&(now[i_search][j]==color))
	{
		for(m=i+1;m<i_search;m++)
		{
			judge=1;
			now[m][j]=3-now[m][j];
		}
	}
	//翻转上面
	i_search=i;
	i_search--;
	while((i_search>0)&&(now[i_search][j]==3-color))
		i_search--;
	if((i_search>0)&&(now[i_search][j]==color))
	{
		for(m=i-1;m>i_search;m--)
		{
			judge=1;
			now[m][j]=3-now[m][j];
		}
	}
	//翻转右面
	j_search++;
	while((j_search<9)&&(now[i][j_search]==3-color))
		j_search++;
	if((j_search<9)&&(now[i][j_search]==color))
	{
		for(n=j+1;n<j_search;n++)
		{
			judge=1;
			now[i][n]=3-now[i][n];
		}
	}
	//翻转左面
	j_search=j-1;
	while((j_search>0)&&(now[i][j_search]==3-color))
		j_search--;
	if((j_search>0)&&(now[i][j_search]==color))
	{
		for(n=j-1;n>j_search;n--)
		{
			judge=1;
			now[i][n]=3-now[i][n];
		}
	}
	//翻转左上
	i_search=i-1;
	j_search=j-1;
	while((j_search>0)&&(i_search>0)&&(now[i_search][j_search]==3-color))
		{i_search--;j_search--;}
	if((j_search>0)&&(i_search>0)&&(now[i_search][j_search]==color))
	{
		for(m=i-1,n=j-1;m>i_search,n>j_search;m--,n--)
		{
			judge=1;
			now[m][n]=3-now[m][n];
		}
	}
	//翻转右上
	i_search=i-1;
	j_search=j+1;
	while((j_search<9)&&(i_search>0)&&(now[i_search][j_search]==3-color))
		{i_search--;j_search++;}
	if((j_search<9)&&(i_search>0)&&(now[i_search][j_search]==color))
	{
		for(m=i-1,n=j+1;m>i_search,n<j_search;m--,n++)
		{
			judge=1;
			now[m][n]=3-now[m][n];
		}
	}
	//翻转右下
	i_search=i+1;
	j_search=j+1;
	while((j_search<9)&&(i_search<9)&&(now[i_search][j_search]==3-color))
		{i_search++;j_search++;}
	if((j_search<9)&&(i_search<9)&&(now[i_search][j_search]==color))
	{
		for(m=i+1,n=j+1;m<i_search,n<j_search;m++,n++)
		{
			judge=1;
			now[m][n]=3-now[m][n];
		}
	}
	//翻转左下
	i_search=i+1;
	j_search=j-1;
	while((j_search>0)&&(i_search<9)&&(now[i_search][j_search]==3-color))
		{i_search++;j_search--;}
	if((j_search>0)&&(i_search<9)&&(now[i_search][j_search]==color))
	{
		for(m=i+1,n=j-1;m<i_search,n>j_search;m++,n--)
		{
			judge=1;
			now[m][n]=3-now[m][n];
		}
	}
	return judge;
}