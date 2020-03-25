#include<iostream>
#include<stdio.h>
#include<stdlib.h>

#include"head.h"

using namespace std;

short now[9][9]={0};//用于存放现在的局面
short available[9][9]={0};//用于寻找合法走子方法
short whose_turn=1;//1表示是黑棋的回合，2表示是白棋的回合

short record_start[9][9]={0};//用于记录开局时的棋盘状态
short record_whose_turn[100]={0};//用于记录turns回合中黑白回合，1黑2白
short record_i[100]={0};//用于记录turns回合中落子所在行数，-1表示pass
short record_j[100]={0};//用于记录turns回合中落子所在列数，-1表示pass

int turns=0;//回合数
int deep_limit=8;//AI最大最小（非剪枝）算法搜索深度
int search_to_end_turns=48;//当局面上的棋子总数大于这个数后，搜索到底
int mode=1;//1为开发者模式
int win_mode=0;//1为只求胜，不求赢尽可能多的子

int main()
{
	//以下声明函数
	bool read_from_file();
	void replay();
	void clear();
	void pause_time();
	void free_initiate();
	//以下定义变量
	char pause='a',position='a';
	int i=0,j=0,k=0,choose=0,temp=0;
	short end=0;
	bool quit=1,skip=0,read=0;
	//进入游戏主菜单
	while(true)
	{
		//初始化
		i=0;j=0;k=0;choose=0;temp=0;end=0;quit=1;skip=0;read=0;
		clear();
		system("cls");
		//菜单选择
		cout<<"*********欢迎来到黑白棋游戏*********"<<endl<<endl<<endl;
		cout<<"*************1 双人对战*************"<<endl<<endl;
		cout<<"*************2 人机先手*************"<<endl<<endl;
		cout<<"*************3 人机后手*************"<<endl<<endl;
		cout<<"*************4 双机对比*************"<<endl<<endl;
		cout<<"**********5 复盘并继续游戏**********"<<endl<<endl;
		cout<<"**********6 自定义开局游戏**********"<<endl<<endl;
		cout<<"***************7 复盘***************"<<endl<<endl;
		cout<<"*************8 退出游戏*************"<<endl<<endl;
		cin>>choose;
		//cout<<"请选择计算机计算模式：1为只求胜，不求赢尽可能多的子；反之输入0"<<endl;
		//cin>>win_mode;
		//以下初始化棋盘
		initiate_board();
		//以下完成5-8的功能
		if(choose==5)
		{
			read_from_file();
			replay();
			cout<<"*************1 双人对战*************"<<endl<<endl;
			cout<<"*************2 人机执黑*************"<<endl<<endl;
			cout<<"*************3 人机执白*************"<<endl<<endl;
			cout<<"*************4 双机对比*************"<<endl<<endl;
			cin>>choose;
			cout<<"黑先请输入1，白先请输入2"<<endl;
			cin>>whose_turn;
		}
		if(choose==6)
		{
			free_initiate();
			cout<<"*************1 双人对战*************"<<endl<<endl;
			cout<<"*************2 人机执黑*************"<<endl<<endl;
			cout<<"*************3 人机执白*************"<<endl<<endl;
			cout<<"*************4 双机对比*************"<<endl<<endl;
			cin>>choose;
		}
		if(choose==7)
		{
			read_from_file();
			replay();
			continue;
		}
		if(choose==8)
			break;
		//以下一些模式选择
		system("cls");
		if(choose!=1)
		{
			cout<<"是否开启开发者模式？如是输入1；否则输入0。"<<endl;
			cin>>mode;
			cout<<endl<<"请输入AI难度：输入一个正整数，"<<endl;
			cout<<"8以下难度，计算机走一步一般会在3秒内完成"<<endl;
			cout<<"难度为8，计算机走一步一般会在10秒内完成"<<endl;
			cout<<"难度为9，计算机走一步一般会在1分钟内完成"<<endl;
			cout<<"难度大于9，计算机走一步可能将会超过五分钟"<<endl<<endl;
			cin>>deep_limit;
			cout<<endl<<"请输入一个正整数，当局面上棋子数大于该数后，计算机将会做完美搜索"<<endl;
			cout<<"48以上，搜索一般会在3秒内完成"<<endl;
			cout<<"输入48，搜索一般会在10秒内完成"<<endl;
			cout<<"输入47，搜索一般会在1分钟内完成"<<endl;
			cout<<"输入小于47，计算机走一步可能将会超过五分钟"<<endl<<endl;
			cin>>search_to_end_turns;
		}
		if(choose!=4)
		{
			cout<<endl<<"在您的回合中，您可以键入“undo”以悔棋；"<<endl;
			cout<<"可以键入“save”以存盘并退出游戏；"<<endl;
			cout<<"可以键入“quit”以直接退出游戏（不存盘）。"<<endl;
			cout<<"输入“c（+回车）”以继续。  "<<endl;
			cin>>pause;
		}
		system("cls");
		//以下进入游戏主体
		end=0;skip=0;
		while(temp<64)
		{
			turns++;
			record_whose_turn[turns]=whose_turn;
			print_board(1);
			position='a'-1+record_j[turns-1];
			cout<<"您的对手刚才在"<<record_i[turns-1]<<position<<"处落子"<<endl;
			skip=judge_end(whose_turn);
			if(end==2)
				break;
			if(skip==0)
			{
				if(whose_turn==1)
					cout<<"黑方无子可下，需要跳过回合"<<endl;
				else
					cout<<"白方无子可下，需要跳过回合"<<endl;
				pause_time();
				record_i[turns]=-1;
				record_j[turns]=-1;
				end++;
			}
			else
			{			
				if((whose_turn==1)&&(choose==2))
					cout<<"请您（黑方）走子（例如输入：“A（+回车）”与棋盘上该字母的位置对应）  ";
				else if((whose_turn==2)&&(choose==3))
					cout<<"请您（白方）走子（例如输入：“A（+回车）”与棋盘上该字母的位置对应）  ";
				else if(((whose_turn==2)&&(choose==2))||((whose_turn==1)&&(choose==3)))
					cout<<"请稍等，复杂的运算进行中...  ";
				else if((whose_turn==1)&&(choose==1))
					cout<<"请黑方走子（例如输入：“4a（+回车）”）  ";
				else if((whose_turn==2)&&(choose==1))
					cout<<"请白方走子（例如输入：“4a（+回车）”）  ";
				else if((whose_turn==1)&&(choose==4))
					cout<<"请黑方走子  ";
				else if((whose_turn==2)&&(choose==4))
					cout<<"请白方走子  ";
				if((choose==1)||((choose==2)&&(whose_turn==1))||((choose==3)&&(whose_turn==2)))
					quit=players_turn(whose_turn);
				else if((choose==4)||((choose==2)&&(whose_turn==2))||((choose==3)&&(whose_turn==1)))
					AI(whose_turn);
				if(quit==0)
					break;
				end=0;
				//cin>>pause;
			}
			whose_turn=3-whose_turn;
			temp=count();
			temp=temp/100+temp%100;
			system("cls");
		}
		//以下一盘棋结束
		record_whose_turn[turns+1]=-1;//表示终局
		if(quit==1)//如果玩家没有选择退出
		{
			end_game();
			cout<<endl<<"您是否愿意存盘？如果是请键入1，否则输入0"<<endl;
			cin>>temp;
			if(temp==1)
				save_to_file();
			cout<<endl<<"您是否愿意复盘？如果是请键入1，否则输入0"<<endl;
			cin>>temp;
			if(temp==1)
				replay();
		}
		else//如果玩家退出游戏	
			continue;
		cout<<"输入“c（+回车）”以继续。  "<<endl;
		cin>>pause;
		system("cls");
	}
	//结束游戏
	cout<<"欢迎下次再来！"<<endl;
	pause_time();
	return 0;
}

void clear()
{
	whose_turn=1;turns=0;deep_limit=5;search_to_end_turns=51;mode=0;
	int i=0,j=0;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			now[i][j]=0;
			available[i][j]=0;
			record_start[i][j]=0;
		}
	}
	return;
}

void pause_time()
{
	int i=0,j=0,k=0;
	int l=750;
	for(i=0;i<l;i++)
	{
		for(j=0;j<l;j++)
		{
			for(k=0;k<l;k++)
				true;
		}
	}
	return;
}

void replay()
{
	turns=0;
	int i=0,j=0;
	char pause='a';
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
			now[i][j]=record_start[i][j];
	}
	system("cls");
	print_board(1);
	while(record_whose_turn[turns+1]!=-1)
	{
		turns++;
		if(record_i[turns]!=-1)
		{
			now[record_i[turns]][record_j[turns]]=record_whose_turn[turns];
			my_reverse(record_i[turns],record_j[turns]);
		}
		system("cls");
		print_board(1);
		cout<<endl<<"输入“c”以继续"<<endl;
		cin>>pause;
	}
	cout<<"复盘到此结束"<<endl;
	cout<<endl<<"输入“c”以继续"<<endl;
	cin>>pause;
	return;
}

void free_initiate()//自定义开局
{
	cout<<"欢迎来到自定义开局模式"<<endl<<endl;
	clear();
	int color=0,i=1,j=1;
	char pause;
	while(true)
	{
		system("cls");
		cout<<"欢迎来到自定义开局模式"<<endl<<endl;
		now[i][j]=4;
		print_board(2);
		cout<<"输入“-1”以结束"<<endl;
		cout<<"输入“0”将“＃”位置设置为无落子点"<<endl;
		cout<<"输入“1”将“＃”位置设置为黑棋子"<<endl;
		cout<<"输入“2”将“＃”位置设置为白棋子"<<endl;
		cin>>color;
		if(color==-1)
		{
			now[i][j]=0;
			break;
		}
		record_start[i][j]=color;
		now[i][j]=color;
		j++;
		if((j==9)&&(i!=8))
		{
			i++;
			j=1;
		}
		else if((j==9)&&(i==8))
			break;
	}
	cout<<"黑先请输入1，白先请输入2"<<endl;
	cin>>whose_turn;
	cout<<endl<<"初始化完毕，输入“c”以继续"<<endl;
	cin>>pause;
	return;
}