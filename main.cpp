#include<iostream>
#include<stdio.h>
#include<stdlib.h>

#include"head.h"

using namespace std;

short now[9][9]={0};//���ڴ�����ڵľ���
short available[9][9]={0};//����Ѱ�ҺϷ����ӷ���
short whose_turn=1;//1��ʾ�Ǻ���Ļغϣ�2��ʾ�ǰ���Ļغ�

short record_start[9][9]={0};//���ڼ�¼����ʱ������״̬
short record_whose_turn[100]={0};//���ڼ�¼turns�غ��кڰ׻غϣ�1��2��
short record_i[100]={0};//���ڼ�¼turns�غ�����������������-1��ʾpass
short record_j[100]={0};//���ڼ�¼turns�غ�����������������-1��ʾpass

int turns=0;//�غ���
int deep_limit=8;//AI�����С���Ǽ�֦���㷨�������
int search_to_end_turns=48;//�������ϵ����������������������������
int mode=1;//1Ϊ������ģʽ
int win_mode=0;//1Ϊֻ��ʤ������Ӯ�����ܶ����

int main()
{
	//������������
	bool read_from_file();
	void replay();
	void clear();
	void pause_time();
	void free_initiate();
	//���¶������
	char pause='a',position='a';
	int i=0,j=0,k=0,choose=0,temp=0;
	short end=0;
	bool quit=1,skip=0,read=0;
	//������Ϸ���˵�
	while(true)
	{
		//��ʼ��
		i=0;j=0;k=0;choose=0;temp=0;end=0;quit=1;skip=0;read=0;
		clear();
		system("cls");
		//�˵�ѡ��
		cout<<"*********��ӭ�����ڰ�����Ϸ*********"<<endl<<endl<<endl;
		cout<<"*************1 ˫�˶�ս*************"<<endl<<endl;
		cout<<"*************2 �˻�����*************"<<endl<<endl;
		cout<<"*************3 �˻�����*************"<<endl<<endl;
		cout<<"*************4 ˫���Ա�*************"<<endl<<endl;
		cout<<"**********5 ���̲�������Ϸ**********"<<endl<<endl;
		cout<<"**********6 �Զ��忪����Ϸ**********"<<endl<<endl;
		cout<<"***************7 ����***************"<<endl<<endl;
		cout<<"*************8 �˳���Ϸ*************"<<endl<<endl;
		cin>>choose;
		//cout<<"��ѡ����������ģʽ��1Ϊֻ��ʤ������Ӯ�����ܶ���ӣ���֮����0"<<endl;
		//cin>>win_mode;
		//���³�ʼ������
		initiate_board();
		//�������5-8�Ĺ���
		if(choose==5)
		{
			read_from_file();
			replay();
			cout<<"*************1 ˫�˶�ս*************"<<endl<<endl;
			cout<<"*************2 �˻�ִ��*************"<<endl<<endl;
			cout<<"*************3 �˻�ִ��*************"<<endl<<endl;
			cout<<"*************4 ˫���Ա�*************"<<endl<<endl;
			cin>>choose;
			cout<<"����������1������������2"<<endl;
			cin>>whose_turn;
		}
		if(choose==6)
		{
			free_initiate();
			cout<<"*************1 ˫�˶�ս*************"<<endl<<endl;
			cout<<"*************2 �˻�ִ��*************"<<endl<<endl;
			cout<<"*************3 �˻�ִ��*************"<<endl<<endl;
			cout<<"*************4 ˫���Ա�*************"<<endl<<endl;
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
		//����һЩģʽѡ��
		system("cls");
		if(choose!=1)
		{
			cout<<"�Ƿ���������ģʽ����������1����������0��"<<endl;
			cin>>mode;
			cout<<endl<<"������AI�Ѷȣ�����һ����������"<<endl;
			cout<<"8�����Ѷȣ��������һ��һ�����3�������"<<endl;
			cout<<"�Ѷ�Ϊ8���������һ��һ�����10�������"<<endl;
			cout<<"�Ѷ�Ϊ9���������һ��һ�����1���������"<<endl;
			cout<<"�Ѷȴ���9���������һ�����ܽ��ᳬ�������"<<endl<<endl;
			cin>>deep_limit;
			cout<<endl<<"������һ���������������������������ڸ����󣬼������������������"<<endl;
			cout<<"48���ϣ�����һ�����3�������"<<endl;
			cout<<"����48������һ�����10�������"<<endl;
			cout<<"����47������һ�����1���������"<<endl;
			cout<<"����С��47���������һ�����ܽ��ᳬ�������"<<endl<<endl;
			cin>>search_to_end_turns;
		}
		if(choose!=4)
		{
			cout<<endl<<"�����Ļغ��У������Լ��롰undo���Ի��壻"<<endl;
			cout<<"���Լ��롰save���Դ��̲��˳���Ϸ��"<<endl;
			cout<<"���Լ��롰quit����ֱ���˳���Ϸ�������̣���"<<endl;
			cout<<"���롰c��+�س������Լ�����  "<<endl;
			cin>>pause;
		}
		system("cls");
		//���½�����Ϸ����
		end=0;skip=0;
		while(temp<64)
		{
			turns++;
			record_whose_turn[turns]=whose_turn;
			print_board(1);
			position='a'-1+record_j[turns-1];
			cout<<"���Ķ��ָղ���"<<record_i[turns-1]<<position<<"������"<<endl;
			skip=judge_end(whose_turn);
			if(end==2)
				break;
			if(skip==0)
			{
				if(whose_turn==1)
					cout<<"�ڷ����ӿ��£���Ҫ�����غ�"<<endl;
				else
					cout<<"�׷����ӿ��£���Ҫ�����غ�"<<endl;
				pause_time();
				record_i[turns]=-1;
				record_j[turns]=-1;
				end++;
			}
			else
			{			
				if((whose_turn==1)&&(choose==2))
					cout<<"�������ڷ������ӣ��������룺��A��+�س������������ϸ���ĸ��λ�ö�Ӧ��  ";
				else if((whose_turn==2)&&(choose==3))
					cout<<"�������׷������ӣ��������룺��A��+�س������������ϸ���ĸ��λ�ö�Ӧ��  ";
				else if(((whose_turn==2)&&(choose==2))||((whose_turn==1)&&(choose==3)))
					cout<<"���Եȣ����ӵ����������...  ";
				else if((whose_turn==1)&&(choose==1))
					cout<<"��ڷ����ӣ��������룺��4a��+�س�������  ";
				else if((whose_turn==2)&&(choose==1))
					cout<<"��׷����ӣ��������룺��4a��+�س�������  ";
				else if((whose_turn==1)&&(choose==4))
					cout<<"��ڷ�����  ";
				else if((whose_turn==2)&&(choose==4))
					cout<<"��׷�����  ";
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
		//����һ�������
		record_whose_turn[turns+1]=-1;//��ʾ�վ�
		if(quit==1)//������û��ѡ���˳�
		{
			end_game();
			cout<<endl<<"���Ƿ�Ը����̣�����������1����������0"<<endl;
			cin>>temp;
			if(temp==1)
				save_to_file();
			cout<<endl<<"���Ƿ�Ը�⸴�̣�����������1����������0"<<endl;
			cin>>temp;
			if(temp==1)
				replay();
		}
		else//�������˳���Ϸ	
			continue;
		cout<<"���롰c��+�س������Լ�����  "<<endl;
		cin>>pause;
		system("cls");
	}
	//������Ϸ
	cout<<"��ӭ�´�������"<<endl;
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
		cout<<endl<<"���롰c���Լ���"<<endl;
		cin>>pause;
	}
	cout<<"���̵��˽���"<<endl;
	cout<<endl<<"���롰c���Լ���"<<endl;
	cin>>pause;
	return;
}

void free_initiate()//�Զ��忪��
{
	cout<<"��ӭ�����Զ��忪��ģʽ"<<endl<<endl;
	clear();
	int color=0,i=1,j=1;
	char pause;
	while(true)
	{
		system("cls");
		cout<<"��ӭ�����Զ��忪��ģʽ"<<endl<<endl;
		now[i][j]=4;
		print_board(2);
		cout<<"���롰-1���Խ���"<<endl;
		cout<<"���롰0����������λ������Ϊ�����ӵ�"<<endl;
		cout<<"���롰1����������λ������Ϊ������"<<endl;
		cout<<"���롰2����������λ������Ϊ������"<<endl;
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
	cout<<"����������1������������2"<<endl;
	cin>>whose_turn;
	cout<<endl<<"��ʼ����ϣ����롰c���Լ���"<<endl;
	cin>>pause;
	return;
}