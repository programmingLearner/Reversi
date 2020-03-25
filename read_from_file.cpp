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

bool read_from_file()//读盘
{
	FILE *fp;
	char filename[30],ch='0';
	cout<<"请输入您之前保存的文件名，以“file”开始，以“.txt”结束，不超过30个字符。"<<endl;
	scanf("%s",filename);
	if((fp=fopen(filename,"r"))==NULL)
	{
		printf("无法打开该文件,请重试。\n");
		return 0;
	}
	ch=fgetc(fp);
	record_start[0][0]=ch-'0';
	int i=0,j=0;
	while(true)
	{
		j++;
		if(j==9)
		{
			j=0;
			i++;
			ch=fgetc(fp);
		}
		if(i==9)
			break;
		ch=fgetc(fp);
		record_start[i][j]=ch-'0';
	}
	for(i=0;i<100;i++)
	{		
		ch=fgetc(fp);
		record_whose_turn[i]=ch-'0';	
		ch=fgetc(fp);
		record_i[i]=ch-'0';	
		ch=fgetc(fp);
		record_j[i]=ch-'0';
		ch=fgetc(fp);
	}
	fclose(fp);
	return 1;
}