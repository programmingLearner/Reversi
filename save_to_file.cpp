#include<iostream>
#include<string>
#include<cstring>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

extern short record_start[][9];
extern short record_whose_turn[100];
extern short record_i[100];
extern short record_j[100];

bool save_to_file()//����
{
	FILE *fp;
	char ch,filename[30];
	cout<<"��Ϊ���½����ļ��������ԡ�file����ʼ���ԡ�.txt����������Ҫ����30���ַ���"<<endl;
	scanf("%s",filename);
	if((fp=fopen(filename,"w"))==NULL)
	{
		printf("�޷��򿪸��ļ�,�����ԡ�\n");
		return 0;
	}
	//���ʼ����
	ch=record_start[0][0]+'0';
	fputc(ch,fp);
	int i=0,j=0;
	while(true)
	{
		j++;
		if(j==9)
		{
			j=0;
			i++;
			ch=10;
			fputc(ch,fp);
		}
		if(i==9)
			break;
		ch=record_start[i][j]+'0';
		fputc(ch,fp);
	}
	//������
	for(i=0;i<100;i++)
	{	
		ch=record_whose_turn[i]+'0';
		fputc(ch,fp);
		ch=record_i[i]+'0';
		fputc(ch,fp);
		ch=record_j[i]+'0';
		fputc(ch,fp);
		ch=10;
		fputc(ch,fp);
	}
	fclose(fp);
	return 1;
}