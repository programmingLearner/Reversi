#include<iostream>
#include"head.h"
using namespace std;

extern short now[][9];
extern short record[][9][9];
extern short record_i[100];
extern short record_j[100];
extern int turns;
extern int deep_limit;//�������
extern int search_to_end_turns;
extern int mode;
extern int win_mode;

const int large_num=30000;
const int larger_num=60000;
const int depth=60;//Ҫ�����������*2����Ϊ����skip���ĵط�Ҫռ2���ռ䣩

int times_of_skips=0;
int maxmin[depth]={0};//��֦ʱ�����ڴ洢max��min�ڵ��alpha��betaֵ
int deep_now=0;//������ȣ������˼�����Ϊ׼
bool search_all=0;//����0����ʾû�е��о��б��׼�����������ף����򣬵��о��б��׼����������
int number=0;

bool AI(short whose_turn)
{
	int count_board();
	int search_min(short whose_turn);
	int pre_score_board(short whose_turn,int i,int j);
	int score_board(short whose_turn);
	int max=-larger_num;//��������������߷��Ĺ�ֵ
	int max_i=-1,max_j=-1;//������ӵ�����
	short save_board[9][9]={0};//���ڴ洢�µ���û������ʱ�ľ���
	int i=0,j=0,m=0,n=0,temp=0,finish=0;
	//�����ж��Ƿ�������������������������
	temp=count_board();
	if(temp>=search_to_end_turns)
		search_all=1;
	number=temp;
	//���´��
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
			save_board[i][j]=now[i][j];
	}
	//���½���Ԥ���۾��棬���Ż�����˳�򣬴Ӷ�������֦Ч��
	short score_list[50]={0};//��������λ��һ���Ժ�ľ������۷���
	short i_list[50]={0};//��������λ�õ�����
	short j_list[50]={0};//��������λ�õ�����
	short now_num=0;//�������ӵı��
	short total_num=0;//һ�����е���������
	for(i=1;i<9;i++)
	{
		for(j=1;j<9;j++)
		{
			if(now[i][j]==0)//�������ط���û������
			{
				now[i][j]=whose_turn;//��������
				if(my_reverse(i,j)==0)//�Ƿ����ӵ�
					now[i][j]=0;//��ԭ���λ�õ�״̬
				else
				{
					now_num++;
					total_num++;
					score_list[now_num]=pre_score_board(whose_turn,i,j);
					i_list[now_num]=i;
					j_list[now_num]=j;
					for(m=1;m<9;m++)
					{
						for(n=1;n<9;n++)
							now[m][n]=save_board[m][n];//����
					}
				}
			}
		}
	}
	//����ð������
	int rank_temp=0;
	for(i=1;i<total_num;i++)
	{
		for(j=1;j<=total_num-i;j++)
		{
			if(score_list[j]<score_list[j+1])
			{
				rank_temp=score_list[j];
				score_list[j]=score_list[j+1];
				score_list[j+1]=rank_temp;
				rank_temp=i_list[j];
				i_list[j]=i_list[j+1];
				i_list[j+1]=rank_temp;
				rank_temp=j_list[j];
				j_list[j]=j_list[j+1];
				j_list[j+1]=rank_temp;
			}
		}
	}
	//����Ѱ��������ӵ�
	for(i=1;i<=total_num;i++)
	{
		now[i_list[i]][j_list[i]]=whose_turn;
		my_reverse(i_list[i],j_list[i]);
		maxmin[deep_now]=max;//�洢�ڵ����ݣ�׼����֦
		deep_now++;
		temp=search_min(whose_turn);//���ü���к���
		deep_now--;//����
		if(mode==1)
			cout<<temp<<" ";
		if(temp>max)//���ŵ����ӣ����ڵ��ں��ǲ��Եģ���ʹ��֦����
		{
			max=temp;
			max_i=i_list[i];
			max_j=j_list[i];
		}
		for(m=1;m<9;m++)
		{
			for(n=1;n<9;n++)
				now[m][n]=save_board[m][n];//����
		}
		if((search_all==1)&&(win_mode==1))
		{
			if(max>0)
			{
				finish=1;
				break;//��min�ﲻ�ܼ�֦��
			}
		}
	}
	//��������
	now[max_i][max_j]=whose_turn;
	my_reverse(max_i,max_j);
	record_i[turns]=max_i;
	record_j[turns]=max_j;
	return 1;
}

int search_min(short whose_turn)
{
	int count_board();
	int search_max(short whose_turn);
	int pre_score_board(short whose_turn,int i,int j);
	int score_board(short whose_turn);
	//�����ж��Ƿ񴥷�������������
	bool to_end=0;//1Ϊ�������������þ������ۺ�����0Ϊ��������
	if(count_board()==64)//�Ƿ��Ѿ�����ȫ�֣�
		to_end=1;
	else if(times_of_skips==2)//�Ƿ�����pass�����غϣ�˫�������ӿ��£�
	{
		times_of_skips=0;
		to_end=1;
	}
	else if((deep_now>=deep_limit)&&(search_all==0))//�Ƿ��ڲ����������дﵽ��������ȣ�
		to_end=1;
	//�������������������
	if(to_end==1)
		return score_board(whose_turn);
	//���û�д������������������ж��Ƿ���Ϊ�÷����ӿ��¶��������غ�
	int i=0,j=0,m=0,n=0,temp=large_num,step=0;
	if(judge_end(3-whose_turn)==0)
	{
		times_of_skips++;
		maxmin[deep_now]=temp;
		deep_now++;
		temp=search_max(whose_turn);
		deep_now--;
		return temp;
	}
	//����Ȳ���������Ҳ���������غ�
	times_of_skips=0;
	int min=large_num;//��������������߷��Ĺ�ֵ
	short save_board[9][9]={0};//���ڴ洢�µ���û������ʱ�ľ���
	//���´��
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
			save_board[i][j]=now[i][j];
	}
	if(number+deep_now>59)
	{
		//����Ѱ��������ӵ�
		for(i=0;i<8;i++)
		{
			if(i==0)
				i=8;
			for(j=1;j<9;j++)
			{
				if(now[i][j]==0)//�������ط���û������
				{
					now[i][j]=3-whose_turn;//��������
					if(my_reverse(i,j)==0)//�Ƿ����ӵ�
					{
						now[i][j]=0;//��ԭ���λ�õ�״̬
						continue;//������һ��λ��
					}
					else//�Ϸ����ӵ�
					{
						maxmin[deep_now]=min;//�洢�ڵ����ݣ�׼����֦
						deep_now++;
						temp=search_max(whose_turn);//���ü���к���
						deep_now--;//����
						if(temp<min)//���ŵ����ӣ�С�ڵ��ں��ǲ��Եģ���ʹ��֦����
							min=temp;
						for(m=1;m<9;m++)
						{
							for(n=1;n<9;n++)
								now[m][n]=save_board[m][n];//����
						}
						for(step=deep_now-1;step>=0;step=step-2)//��0�Ļ������Ľ��Ǿ�ȷ�ģ�����ÿ��������Ĺ�ֵ��׼ȷ
						{
							if(min<=maxmin[step])//alpha��֦
								return min;
						}
					}
				}
			}
			if(i==8)
				i=0;
		}
		return min;
	}
	//���½���Ԥ���۾��棬���Ż�����˳�򣬴Ӷ�������֦Ч��
	short score_list[50]={0};//��������λ��һ���Ժ�ľ������۷���
	short i_list[50]={0};//��������λ�õ�����
	short j_list[50]={0};//��������λ�õ�����
	short now_num=0;//�������ӵı��
	short total_num=0;//һ�����е���������
	for(i=1;i<9;i++)
	{
		for(j=1;j<9;j++)
		{
			if(now[i][j]==0)//�������ط���û������
			{
				now[i][j]=3-whose_turn;//��������
				if(my_reverse(i,j)==0)//�Ƿ����ӵ�
					now[i][j]=0;//��ԭ���λ�õ�״̬
				else
				{
					now_num++;
					total_num++;
					score_list[now_num]=pre_score_board(3-whose_turn,i,j);
					i_list[now_num]=i;
					j_list[now_num]=j;
					for(m=1;m<9;m++)
					{
						for(n=1;n<9;n++)
							now[m][n]=save_board[m][n];//����
					}
				}
			}
		}
	}
	//����ð������
	int rank_temp=0;
	for(i=1;i<total_num;i++)
	{
		for(j=1;j<=total_num-i;j++)
		{
			if(score_list[j]<score_list[j+1])
			{
				rank_temp=score_list[j];
				score_list[j]=score_list[j+1];
				score_list[j+1]=rank_temp;
				rank_temp=i_list[j];
				i_list[j]=i_list[j+1];
				i_list[j+1]=rank_temp;
				rank_temp=j_list[j];
				j_list[j]=j_list[j+1];
				j_list[j+1]=rank_temp;
			}
		}
	}
	//����Ѱ��������ӵ�
	for(i=1;i<=total_num;i++)
	{
		now[i_list[i]][j_list[i]]=3-whose_turn;
		my_reverse(i_list[i],j_list[i]);
		maxmin[deep_now]=min;//�洢�ڵ����ݣ�׼����֦
		deep_now++;
		temp=search_max(whose_turn);//���ü���к���
		deep_now--;//����
		if(temp<min)//���ŵ����ӣ�С�ڵ��ں��ǲ��Եģ���ʹ��֦����
			min=temp;
		for(m=1;m<9;m++)
		{
			for(n=1;n<9;n++)
				now[m][n]=save_board[m][n];//����
		}
		for(step=deep_now-1;step>=0;step=step-2)//��0�Ļ������Ľ��Ǿ�ȷ�ģ�����ÿ��������Ĺ�ֵ��׼ȷ
		{
			if(min<=maxmin[step])//alpha��֦
				return min;
		}
	}
	return min;
}

int search_max(short whose_turn)
{
	int count_board();
	int search_min(short whose_turn);
	int pre_score_board(short whose_turn,int i,int j);
	int score_board(short whose_turn);
	//�����ж��Ƿ񴥷�������������
	bool to_end=0;//1Ϊ�������������þ������ۺ�����0Ϊ��������
	if(count_board()==64)//�Ƿ��Ѿ�����ȫ�֣�
		to_end=1;
	else if(times_of_skips==2)//�Ƿ�����pass�����غϣ�˫�������ӿ��£�
	{
		times_of_skips=0;
		to_end=1;
	}
	else if((deep_now>=deep_limit)&&(search_all==0))//�Ƿ��ڲ����������дﵽ��������ȣ�
		to_end=1;
	//�������������������
	if(to_end==1)
		return score_board(whose_turn);
	//���û�д������������������ж��Ƿ���Ϊ�÷����ӿ��¶��������غ�
	int i=0,j=0,m=0,n=0,temp=-large_num,step=0;
	if(judge_end(whose_turn)==0)
	{
		times_of_skips++;		
		maxmin[deep_now]=temp;
		deep_now++;
		temp=search_min(whose_turn);
		deep_now--;	
		return temp;
	}
	//����Ȳ���������Ҳ���������غ�
	times_of_skips=0;
	int max=-large_num;//��������������߷��Ĺ�ֵ
	short save_board[9][9]={0};//���ڴ洢�µ���û������ʱ�ľ���
	//���´��
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
			save_board[i][j]=now[i][j];
	}
	if(number+deep_now>59)
	{
		//����Ѱ��������ӵ�
		for(i=0;i<8;i++)
		{
			if(i==0)
				i=8;
			for(j=1;j<9;j++)
			{
				if(now[i][j]==0)//�������ط���û������
				{
					now[i][j]=whose_turn;//��������
					if(my_reverse(i,j)==0)//�Ƿ����ӵ�
					{
						now[i][j]=0;//��ԭ���λ�õ�״̬
						continue;//������һ��λ��
					}
					else//�Ϸ����ӵ�
					{
						maxmin[deep_now]=max;//�洢�ڵ����ݣ�׼����֦
						deep_now++;
						temp=search_min(whose_turn);//���ü���к���
						deep_now--;//����
						if(temp>max)//���ŵ����ӣ����ڵ��ں��ǲ��Եģ���ʹ��֦����
							max=temp;
						for(m=1;m<9;m++)
						{
							for(n=1;n<9;n++)
								now[m][n]=save_board[m][n];//����
						}
						if((search_all==1)&&(win_mode==1))
						{
							if(max>0)
								return max;
						}
						for(step=deep_now-1;step>=0;step=step-2)//��0�Ļ������Ľ��Ǿ�ȷ�ģ�����ÿ��������Ĺ�ֵ��׼ȷ
						{
							if(max>=maxmin[step])//beta��֦
								return max;
						}
					}
				}
			}
			if(i==8)
				i=0;
		}
		return max;
	}
	//���½���Ԥ���۾��棬���Ż�����˳�򣬴Ӷ�������֦Ч��
	short score_list[50]={0};//��������λ��һ���Ժ�ľ������۷���
	short i_list[50]={0};//��������λ�õ�����
	short j_list[50]={0};//��������λ�õ�����
	short now_num=0;//�������ӵı��
	short total_num=0;//һ�����е���������
	for(i=1;i<9;i++)
	{
		for(j=1;j<9;j++)
		{
			if(now[i][j]==0)//�������ط���û������
			{
				now[i][j]=whose_turn;//��������
				if(my_reverse(i,j)==0)//�Ƿ����ӵ�
					now[i][j]=0;//��ԭ���λ�õ�״̬
				else
				{
					now_num++;
					total_num++;
					score_list[now_num]=pre_score_board(whose_turn,i,j);
					i_list[now_num]=i;
					j_list[now_num]=j;
					for(m=1;m<9;m++)
					{
						for(n=1;n<9;n++)
							now[m][n]=save_board[m][n];//����
					}
				}
			}
		}
	}
	//����ð������
	int rank_temp=0;
	for(i=1;i<total_num;i++)
	{
		for(j=1;j<=total_num-i;j++)
		{
			if(score_list[j]<score_list[j+1])
			{
				rank_temp=score_list[j];
				score_list[j]=score_list[j+1];
				score_list[j+1]=rank_temp;
				rank_temp=i_list[j];
				i_list[j]=i_list[j+1];
				i_list[j+1]=rank_temp;
				rank_temp=j_list[j];
				j_list[j]=j_list[j+1];
				j_list[j+1]=rank_temp;
			}
		}
	}
	//����Ѱ��������ӵ�
	for(i=1;i<=total_num;i++)
	{
		now[i_list[i]][j_list[i]]=whose_turn;
		my_reverse(i_list[i],j_list[i]);
		maxmin[deep_now]=max;//�洢�ڵ����ݣ�׼����֦
		deep_now++;
		temp=search_min(whose_turn);//���ü���к���
		deep_now--;//����
		if(temp>max)//���ŵ����ӣ����ڵ��ں��ǲ��Եģ���ʹ��֦����
			max=temp;
		for(m=1;m<9;m++)
		{
			for(n=1;n<9;n++)
				now[m][n]=save_board[m][n];//����
		}
		if((search_all==1)&&(win_mode==1))
		{
			if(max>0)
				return max;
		}
		for(step=deep_now-1;step>=0;step=step-2)//��0�Ļ������Ľ��Ǿ�ȷ�ģ�����ÿ��������Ĺ�ֵ��׼ȷ
		{
			if(max>=maxmin[step])//beta��֦
				return max;
		}
	}
	return max;
}

int count_board()//�������Ϲ������˶��ٸ���
{
	int i=0,j=0;
	int num=0;
	for(i=1;i<9;i++)
	{
		for(j=1;j<9;j++)
		{
			if(now[i][j]!=0)
				num++;
		}
	}
	return num;
}

int score_board(short whose_turn)//�ۺϾ������ۺ���
{
	int special_pattern_stable_discs(short whose_turn);
	int edge_disc(short whose_turn);
	int special_pattern_balanced_edge(short whose_score,short whose_turn);
	int i=0,j=0;
	int num=0;
	if(search_all==1)//���о��б��׼
	{
		for(i=1;i<9;i++)
		{
			for(j=1;j<9;j++)
			{
				if(now[i][j]==whose_turn)
					num++;
				else if(now[i][j]==3-whose_turn)
					num--;
			}
		}
		return num;
	}
	//û���о��б��׼
	int already_lost=1;//��ֹ�Լ����ӱ��Է��Թ�
	for(i=1;i<9;i++)
	{
		for(j=1;j<9;j++)
		{
			if(now[i][j]==whose_turn)
			{
				already_lost=0;
				break;
			}
		}
		if(already_lost==0)//���ǡ�=����
			break;
	}
	int x=0;//��������λ�輫�����
	if((now[1][1]==0)&&(now[2][2]==whose_turn))
		x++;
	if((now[1][8]==0)&&(now[2][7]==whose_turn))
		x++;
	if((now[8][1]==0)&&(now[7][2]==whose_turn))
		x++;
	if((now[8][8]==0)&&(now[7][7]==whose_turn))
		x++;
	int c=0;//������C�������
	if((now[1][1]==0)&&(now[1][2]==whose_turn)&&(now[1][3]==0))
		c++;
	if((now[1][1]==0)&&(now[2][1]==whose_turn)&&(now[3][1]==0))
		c++;
	if((now[1][8]==0)&&(now[1][7]==whose_turn)&&(now[1][6]==0))
		c++;
	if((now[1][8]==0)&&(now[2][8]==whose_turn)&&(now[3][8]==0))
		c++;
	if((now[8][1]==0)&&(now[8][2]==whose_turn)&&(now[8][3]==0))
		c++;
	if((now[8][1]==0)&&(now[7][1]==whose_turn)&&(now[6][1]==0))
		c++;
	if((now[8][8]==0)&&(now[8][7]==whose_turn)&&(now[8][6]==0))
		c++;
	if((now[8][8]==0)&&(now[7][8]==whose_turn)&&(now[6][8]==0))
		c++;
	int cc=0;//������C�������
	if((now[1][1]==0)&&(now[1][2]==whose_turn)&&(now[1][3]==3-whose_turn))
		cc++;
	if((now[1][1]==0)&&(now[2][1]==whose_turn)&&(now[3][1]==3-whose_turn))
		cc++;
	if((now[1][8]==0)&&(now[1][7]==whose_turn)&&(now[1][6]==3-whose_turn))
		cc++;
	if((now[1][8]==0)&&(now[2][8]==whose_turn)&&(now[3][8]==3-whose_turn))
		cc++;
	if((now[8][1]==0)&&(now[8][2]==whose_turn)&&(now[8][3]==3-whose_turn))
		cc++;
	if((now[8][1]==0)&&(now[7][1]==whose_turn)&&(now[6][1]==3-whose_turn))
		cc++;
	if((now[8][8]==0)&&(now[8][7]==whose_turn)&&(now[8][6]==3-whose_turn))
		cc++;
	if((now[8][8]==0)&&(now[7][8]==whose_turn)&&(now[6][8]==3-whose_turn))
		cc++;
	/*
	//����Ҫ����
	if(now[4][4]==whose_turn)
	num+=1;
	if(now[4][5]==whose_turn)
	num+=1;
	if(now[5][4]==whose_turn)
	num+=1;
	if(now[5][5]==whose_turn)
	num+=1;
	*/
	//�ۺ����۾���
	int val_table[65] = {0,70,110,125,133,137,139,141,142};
	int val = 143;
	for(int cnt = 9; cnt < 65; ++cnt ){
		val_table[cnt] = val;
		++val;
	}
	num=num-edge_disc(whose_turn)+edge_disc(3-whose_turn);
	num=num+val_table[special_pattern_stable_discs(whose_turn)]-val_table[special_pattern_stable_discs(3-whose_turn)];
	//num=num+special_pattern_balanced_edge(whose_turn,whose_turn)-special_pattern_balanced_edge(3-whose_turn,whose_turn);
	if(already_lost==1)
		num=num-4500;
	//num=num-70*x-55*c-210*cc;
	num=num-7*x-5*c-15*cc;
	return num;
}

int pre_score_board(short whose_turn,int i,int j)//Ԥ��
{
	int edge_disc(short whose_turn);
	int num=0;
	num=num-edge_disc(whose_turn)+edge_disc(3-whose_turn);
	if(i==1)
	{
		if((j==1)||(j==8))
			num+=10;
		else if((j==2)||(j==7))
			num-=3;
	}
	else if(i==2)
	{
		if((j==1)||(j==8))
			num-=3;
		else if((j==2)||(j==7))
			num-=7;
	}
	else if(i==7)
	{
		if((j==1)||(j==8))
			num-=3;
		else if((j==2)||(j==7))
			num-=7;
	}
	else if(i==8)
	{
		if((j==1)||(j==8))
			num+=10;
		else if((j==2)||(j==7))
			num-=3;
	}
	return num;
}

int edge_disc(short whose_turn)//ɢ��
{
	int i=0,j=0,sum=0;
	bool edge[9][9]={0};
	for(i=2;i<8;i++)
	{
		for(j=2;j<8;j++)
		{
			if(now[i][j]==whose_turn)
			{
				if(now[i-1][j]==0)
					edge[i-1][j]=1;
				if(now[i+1][j]==0)
					edge[i+1][j]=1;
				if(now[i][j+1]==0)
					edge[i][j+1]=1;
				if(now[i][j-1]==0)
					edge[i][j-1]=1;
				if(now[i-1][j-1]==0)
					edge[i-1][j-1]=1;
				if(now[i-1][j+1]==0)
					edge[i-1][j+1]=1;
				if(now[i+1][j-1]==0)
					edge[i+1][j-1]=1;
				if(now[i+1][j+1]==0)
					edge[i+1][j+1]=1;
			}
		}
	}
	for(i=1;i<9;i++)
	{
		for(j=1;j<9;j++)
		{
			if(edge[i][j]==1)
				sum++;
		}
	}
	return sum;
}

int special_pattern_stable_discs(short whose_turn)//��ʽ1---�ȶ����ж�(ֻ�ǲ��ֳ����Σ�����ֱ�ȶ���)
{
	int i=0,j=0,sum=0;
	bool special[9][9]={0};
	//���¼���߽��ȶ���
	if(now[1][1]==whose_turn)
	{
		special[1][1]=1;
		for(i=2;i<8;i++)
		{
			if(now[i][1]==whose_turn)
				special[i][1]=1;
			else
				break;
		}
		for(i=2;i<8;i++)
		{
			if(now[1][i]==whose_turn)
				special[1][i]=1;
			else
				break;
		}
	}
	if(now[8][1]==whose_turn)
	{
		special[8][1]=1;
		for(i=2;i<8;i++)
		{
			if(now[8][i]==whose_turn)
				special[8][i]=1;
			else
				break;
		}
		for(i=7;i>1;i--)
		{
			if(now[i][1]==whose_turn)
				special[i][1]=1;
			else
				break;
		}
	}
	if(now[1][8]==whose_turn)
	{
		special[1][8]=1;
		for(i=2;i<8;i++)
		{
			if(now[i][8]==whose_turn)
				special[i][8]=1;
			else
				break;
		}
		for(i=7;i>1;i--)
		{
			if(now[1][i]==whose_turn)
				special[1][i]=1;
			else
				break;
		}
	}
	if(now[8][8]==whose_turn)
	{
		special[8][8]=1;
		for(i=7;i>1;i--)
		{
			if(now[8][i]==whose_turn)
				special[8][i]=1;
			else
				break;
		}
		for(i=7;i>1;i--)
		{
			if(now[i][8]==whose_turn)
				special[i][8]=1;
			else
				break;
		}
	}
	//���¼����и��ȶ���
	int m=0;
	bool flag=0;
	for(m=1;m<=8;m++)
	{
		flag=1;
		for(i=1;i<=m;i++)
		{
			if(now[i][m-i+1]!=whose_turn)
			{
				flag=0;
				break;
			}
		}
		if(flag==1)
		{
			for(i=1;i<=m;i++)
				special[i][m-i+1]=1;
		}
		else
			break;
	}
	for(m=1;m<=8;m++)
	{
		flag=1;
		for(i=1;i<=m;i++)
		{
			if(now[i][8-m+i]!=whose_turn)
			{
				flag=0;
				break;
			}
		}
		if(flag==1)
		{
			for(i=1;i<=m;i++)
				special[i][8-m+i]=1;
		}
		else
			break;
	}
	for(m=1;m<=8;m++)
	{
		flag=1;
		for(i=9-m;i<=8;i++)
		{
			if(now[i][i+m-8]!=whose_turn)
			{
				flag=0;
				break;
			}
		}
		if(flag==1)
		{
			for(i=9-m;i<=8;i++)
				special[i][i+m-8]=1;
		}
		else
			break;
	}
	for(m=1;m<=8;m++)
	{
		flag=1;
		for(i=9-m;i<=8;i++)
		{
			if(now[i][17-m-i]!=whose_turn)
			{
				flag=0;
				break;
			}
		}
		if(flag==1)
		{
			for(i=9-m;i<=8;i++)
				special[i][17-m-i]=1;
		}
		else
			break;
	}
	//���¼���߽ǲ����ȶ���
	flag=1;
	for(i=1;i<=8;i++)
	{
		if(now[1][i]==0)
		{
			flag=0;
			break;
		}
	}
	if(flag==1)
	{
		for(i=1;i<=8;i++)
		{
			if(now[1][i]==whose_turn)
				special[1][i]=1;
		}
	}
	flag=1;
	for(i=1;i<=8;i++)
	{
		if(now[8][i]==0)
		{
			flag=0;
			break;
		}
	}
	if(flag==1)
	{
		for(i=1;i<=8;i++)
		{
			if(now[8][i]==whose_turn)
				special[8][i]=1;
		}
	}
	flag=1;
	for(i=1;i<=8;i++)
	{
		if(now[i][1]==0)
		{
			flag=0;
			break;
		}
	}
	if(flag==1)
	{
		for(i=1;i<=8;i++)
		{
			if(now[i][1]==whose_turn)
				special[i][1]=1;
		}
	}
	flag=1;
	for(i=1;i<=8;i++)
	{
		if(now[i][8]==0)
		{
			flag=0;
			break;
		}
	}
	if(flag==1)
	{
		for(i=1;i<=8;i++)
		{
			if(now[i][8]==whose_turn)
				special[i][8]=1;
		}
	}	
	//���¼���
	for(i=1;i<9;i++)
	{
		for(j=1;j<9;j++)
		{
			if(special[i][j]==1)
				sum++;
		}
	}
	return sum;
}

int special_pattern_balanced_edge(short whose_score,short whose_turn)//��ʽ2---�о��еı߶�ʽ
{
	int a=0,b=0,c=0,d=0,sum=0;
	if((now[1][1]==0)&&(now[1][8]==0))
	{
		if(now[1][2]==whose_score)
			a+=1;
		else if(now[1][2]==3-whose_score)
			a+=2;
		if(now[1][3]==whose_score)
			a+=3;
		else if(now[1][3]==3-whose_score)
			a+=6;
		if(now[1][4]==whose_score)
			a+=9;
		else if(now[1][4]==3-whose_score)
			a+=18;
		if(now[1][5]==whose_score)
			a+=27;
		else if(now[1][5]==3-whose_score)
			a+=54;
		if(now[1][6]==whose_score)
			a+=81;
		else if(now[1][6]==3-whose_score)
			a+=162;
		if(now[1][7]==whose_score)
			a+=243;
		else if(now[1][7]==3-whose_score)
			a+=486;
	}
	if((now[8][1]==0)&&(now[8][8]==0))
	{
		if(now[8][2]==whose_score)
			b+=1;
		else if(now[8][2]==3-whose_score)
			b+=2;
		if(now[8][3]==whose_score)
			b+=3;
		else if(now[8][3]==3-whose_score)
			b+=6;
		if(now[8][4]==whose_score)
			b+=9;
		else if(now[8][4]==3-whose_score)
			b+=18;
		if(now[8][5]==whose_score)
			b+=27;
		else if(now[8][5]==3-whose_score)
			b+=54;
		if(now[8][6]==whose_score)
			b+=81;
		else if(now[8][6]==3-whose_score)
			b+=162;
		if(now[8][7]==whose_score)
			b+=243;
		else if(now[8][7]==3-whose_score)
			b+=486;
	}
	if((now[1][1]==0)&&(now[8][1]==0))
	{
		if(now[2][1]==whose_score)
			c+=1;
		else if(now[2][1]==3-whose_score)
			c+=2;
		if(now[3][1]==whose_score)
			c+=3;
		else if(now[3][1]==3-whose_score)
			c+=6;
		if(now[4][1]==whose_score)
			c+=9;
		else if(now[4][1]==3-whose_score)
			c+=18;
		if(now[5][1]==whose_score)
			c+=27;
		else if(now[5][1]==3-whose_score)
			c+=54;
		if(now[6][1]==whose_score)
			c+=81;
		else if(now[6][1]==3-whose_score)
			c+=162;
		if(now[7][1]==whose_score)
			c+=243;
		else if(now[7][1]==3-whose_score)
			c+=486;
	}
	if((now[1][8]==0)&&(now[8][8]==0))
	{
		if(now[2][8]==whose_score)
			d+=1;
		else if(now[2][8]==3-whose_score)
			d+=2;
		if(now[3][8]==whose_score)
			d+=3;
		else if(now[3][8]==3-whose_score)
			d+=6;
		if(now[4][8]==whose_score)
			d+=9;
		else if(now[4][8]==3-whose_score)
			d+=18;
		if(now[5][8]==whose_score)
			d+=27;
		else if(now[5][8]==3-whose_score)
			d+=54;
		if(now[6][8]==whose_score)
			d+=81;
		else if(now[6][8]==3-whose_score)
			d+=162;
		if(now[7][8]==whose_score)
			d+=243;
		else if(now[7][8]==3-whose_score)
			d+=486;
	}
	if(a==0)
		true;
	else if(a==364)//6ƽ��
		sum+=5;
	else if(a==607)//5
	{
		if(whose_score==whose_turn)
			sum+=490;
		else
			sum-=490;
	}
	else if(a==121)
	{
		if(now[2][6]==3-whose_score)
			sum+=1;
		else
			sum-=7;
	}
	else if(a==365)
	{
		if(whose_score==whose_turn)
			sum+=490;
		else
			sum-=490;
	}
	else if(a==363)
	{
		if(now[2][3]==whose_score)
			sum+=1;
		else
			sum-=7;
	}
	else if((a==361)||(a==355)||(a==337)||(a==283))
		sum-=25;
	else if((a==367)||(a==373)||(a==391)||(a==445))
		sum-=560;
	else if(a==120)//4
	{
		if((now[2][3]==3-whose_score)&&(now[2][6]==3-whose_score))
			sum+=5;
		else
			sum+=3;
	}
	else if(a==40)
	{
		if((now[2][5]==whose_score)&&(now[2][6]==whose_score))
			sum-=6;
	}
	else if(a==360)
	{
		if((now[2][3]==whose_score)&&(now[2][4]==whose_score))
			sum-=6;
	}
	else if((a==256)||(a==328)||(a==352))
		sum+=6;
	else if((a==354)||(a==336)||(a==282)||(a==334)||(a==280)||(a==118)||(a==274)||(a==112)||(a==94))
		sum-=15;
	else if(a==36)
		sum-=5;
	else if(a==84)
		sum+=3;
	else if((a==3)||(a==81))
		sum+=1;
	if(b==0)
		true;
	else if(b==364)//6ƽ��
		sum+=5;
	else if(b==607)//5
	{
		if(whose_score==whose_turn)
			sum+=490;
		else
			sum-=490;
	}
	else if(b==121)
	{
		if(now[7][6]==3-whose_score)
			sum+=1;
		else
			sum-=7;
	}
	else if(b==365)
	{
		if(whose_score==whose_turn)
			sum+=490;
		else
			sum-=490;
	}
	else if(b==363)
	{
		if(now[7][3]==whose_score)
			sum+=1;
		else
			sum-=7;
	}
	else if((b==361)||(b==355)||(b==337)||(b==283))
		sum-=25;
	else if((b==367)||(b==373)||(b==391)||(b==445))
		sum-=560;
	else if(b==120)//4
	{
		if((now[7][3]==3-whose_score)&&(now[7][6]==3-whose_score))
			sum+=5;
		else
			sum+=3;
	}
	else if(b==40)
	{
		if((now[7][5]==whose_score)&&(now[7][6]==whose_score))
			sum-=6;
	}
	else if(b==360)
	{
		if((now[7][3]==whose_score)&&(now[7][4]==whose_score))
			sum-=6;
	}
	else if((b==256)||(b==328)||(b==352))
		sum+=6;
	else if((b==354)||(b==336)||(b==282)||(b==334)||(b==280)||(b==118)||(b==274)||(b==112)||(b==94))
		sum-=15;
	else if(b==36)
		sum-=5;
	else if(b==84)
		sum+=3;
	else if((b==3)||(b==81))
		sum+=1;
	if(c==0)
		true;
	else if(c==364)//6ƽ��
		sum+=5;
	else if(c==607)//5
	{
		if(whose_score==whose_turn)
			sum+=490;
		else
			sum-=490;
	}
	else if(c==121)
	{
		if(now[6][2]==3-whose_score)
			sum+=1;
		else
			sum-=7;
	}
	else if(c==365)
	{
		if(whose_score==whose_turn)
			sum+=490;
		else
			sum-=490;
	}
	else if(c==363)
	{
		if(now[3][2]==whose_score)
			sum+=1;
		else
			sum-=7;
	}
	else if((c==361)||(c==355)||(c==337)||(c==283))
		sum-=25;
	else if((c==367)||(c==373)||(c==391)||(c==445))
		sum-=560;
	else if(c==120)//4
	{
		if((now[3][2]==3-whose_score)&&(now[6][2]==3-whose_score))
			sum+=5;
		else
			sum+=3;
	}
	else if(c==40)
	{
		if((now[5][2]==whose_score)&&(now[6][2]==whose_score))
			sum-=6;
	}
	else if(c==360)
	{
		if((now[3][2]==whose_score)&&(now[4][2]==whose_score))
			sum-=6;
	}
	else if((c==256)||(c==328)||(c==352))
		sum+=6;
	else if((c==354)||(c==336)||(c==282)||(c==334)||(c==280)||(c==118)||(c==274)||(c==112)||(c==94))
		sum-=15;
	else if(c==36)
		sum-=5;
	else if(c==84)
		sum+=3;
	else if((c==3)||(c==81))
		sum+=1;
	if(d==0)
		true;
	else if(d==364)//6ƽ��
		sum+=5;
	else if(d==607)//5
	{
		if(whose_score==whose_turn)
			sum+=490;
		else
			sum-=490;
	}
	else if(d==121)
	{
		if(now[6][7]==3-whose_score)
			sum+=1;
		else
			sum-=7;
	}
	else if(d==365)
	{
		if(whose_score==whose_turn)
			sum+=490;
		else
			sum-=490;
	}
	else if(d==363)
	{
		if(now[3][7]==whose_score)
			sum+=1;
		else
			sum-=7;
	}
	else if((d==361)||(d==355)||(d==337)||(d==283))
		sum-=25;
	else if((d==367)||(d==373)||(d==391)||(d==445))
		sum-=560;
	else if(d==120)//4
	{
		if((now[3][7]==3-whose_score)&&(now[6][7]==3-whose_score))
			sum+=5;
		else
			sum+=3;
	}
	else if(d==40)
	{
		if((now[5][7]==whose_score)&&(now[6][7]==whose_score))
			sum-=6;
	}
	else if(d==360)
	{
		if((now[3][7]==whose_score)&&(now[4][7]==whose_score))
			sum-=6;
	}
	else if((d==256)||(d==328)||(d==352))
		sum+=6;
	else if((d==354)||(d==336)||(d==282)||(d==334)||(d==280)||(d==118)||(d==274)||(d==112)||(d==94))
		sum-=15;
	else if(d==36)
		sum-=5;
	else if(d==84)
		sum+=3;
	else if((d==3)||(d==81))
		sum+=1;
	if((sum>10)&&(sum<50))
		sum=9;
	return sum;
}