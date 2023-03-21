/*
	编译环境：Dev-C++ 5.4.0 
	最后修改：2023 年 1 月 27 日
*/
typedef struct student{
	char id[6];
	char name[20];
	char sex;
	float score[3];
	struct student *next;
}Student;
extern Student *head;
extern int rounds;

#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
int list_len(Student *p)//返回链表长度 
{
	int i;
	for(i=0;p!=NULL;i++,p=p->next);
	return i;
}

int id_validity(char id[6])//学号合法性判断 1为合法 0为非法 
{
	int i;
	if(strlen(id)>4)
		return 0;
	if((id[0]>=65&&id[0]<=90)||(id[0]>=97&&id[0]<=122));//第一个必须为字母 
	else
		return 0;
	if((id[1]>=65&&id[1]<=90)||(id[1]>=97&&id[1]<=122)||(id[1]>=48&&id[1]<=57));//第二个可以为字母或数字 
	else
		return 0;
	for(i=2;i<4;i++)//第三、四个必须为数字
	{
		if(id[i]>=48&&id[i]<=57);
		else
		{
			if((id[i]=='\0')&&(i>=3))
				return 1; 
			return 0;
		}
	}
	return 1; 
}

int id_examine(char kind,char id[6],Student *p)//学号查重 1为不重 0为重 -1为非法 kind==n为不检查链表尾(允许学号有一个重复)
{
	if(!id_validity(id))
	{
		printf("该学号不合法,请重新输入.\n");
		fflush(stdin); 
		return -1;
	}
	if(kind=='n')//no tail 检查 非全体检查 允许出现一个相同元素 
		{
			int i=0;
			while(p!=NULL)
			{
				if(!strcmp(id,p->id))
					i++;
				p=p->next;
			}
			if(i==1)
				return 1;
			else
				return 0;
		}
	if(kind=='t')//tail 检查 全体检查
		while(p!=NULL)
		{
			if(!strcmp(id,p->id))
			{
				return 0; 
			}
			p=p->next; 
		} 
	return 1;
}

Student *get_i_n(char s,char a[20],Student *p)//提取相同 id(i)或 name(n)的链表节点
{
	if(s=='i')
	{ 
		while(p!=NULL)
		{
			if(!strcmp(a,p->id))
			{
				return p;
			}
			p=p->next;
		}
	}
	if(s=='n')
	{
		while(p!=NULL)
		{
			if(!strcmp(a,p->name))
			{
				return p;
			}
			p=p->next;
		}
		return NULL;
	} 
}

int ws_examine()//非多字符判断 1为无多字符 0为数字后有字符//例:要求仅输入数字时,将 2f 定为非法输入
{
	int i=0; 
	while(getchar()!='\n')
	{
		i++; 
	}
	if(i!=0)
		return 0;
	return 1; 
}

int sex_validity(char *a)//性别合法性判断 1为合法 0为非法 
{
	if(*a=='f'||*a=='m')
		return 1;
	else
	{
		*a='f'; 
		return 0;
	}
} 

int num_examine(int *p)//输入数字_合法性判断 1为数字正常 
{ 
	int x=scanf("%d",p);
	if(x==0)
	{
		fflush(stdin);
		return 0;//数字头有字符 //这个其实不太有用,一般判定个数字范围就差不多了
	} 
	if(ws_examine()==0)
	{
		return -1;//数字尾有字符 
	}
	return 1;//数字正常 
}

int get_num(float *p)//输入成绩_合法性判断 1为数字正常 
{ 
	int x=scanf("%f",p);
	if(x==0)
	{
		fflush(stdin);
		return 0;//数字头有字符 
	} 
	if(ws_examine()==0)
	{
		return -1;//数字尾有字符 
	}
	return 1;//数字正常 
}

int score_examine(float n)//分数判断 1为分数正常 0不正常
{
	if(n>=0&&n<=100)
		return 1;
	return 0;
}
void score_input(Student *last,int i)//专门的成绩输入,用于信息录入与成绩修改 
{
	int j;
	char sname[][9]={"英语","数学","程序设计"};
	for(j=0;j<3;j++)
	{
		while(1)
		{
			printf("第%d个学生的%s成绩:",i,sname[j]);
			switch(get_num(&last->score[j]))
			{
				case -1:
					printf("成绩有非法字符,请重新输入.\n");
					continue;
				case 0:
					printf("成绩输入不合法,请重新输入.\n");
					continue;
				case 1:
					break;
			}
			if(!score_examine(last->score[j]))
			{
				printf("成绩输入不合法,请重新输入.\n");
				fflush(stdin);
				continue;
			}
			break; 
		}
	}
}

void input(Student *head,Student *last,int i)//链表内容输入函数
{
	char notail='n';
	while(1)
	{ 
		printf("第%d个学生的学号:",i);
		scanf("%s",last->id);
		switch(id_examine(notail,last->id,head))//这里的查重允许出现一个重复(不查尾)
		{
		case -1:
			continue;
		case 0:
			printf("该学号已存在,请重新输入.\n");
			continue;
		case 1:
			break;
		}
		break;
	}
	printf("第%d个学生的姓名:",i);
	scanf("%s",last->name);
	getchar(); 
	while(1)
	{
		printf("第%d个学生的性别(f/m):",i);
		last->sex=getchar();
		if((!ws_examine())||(!sex_validity(&(last->sex))))
		{
			printf("性别错误,请重新输入性别.\n");
			continue;
		}
		break;
	}
	score_input(last,i);
}

Student *build(Student *head)//创建链表函数 
{
	int i,n;
	printf("请输入总共要录入的人数:");
	while(1)
	{
		switch(num_examine(&n))
			{
				case -1:
					printf("数字有非法字符,请重新输入.\n");
					continue;
				case 0:
					printf("数字输入不合法,请重新输入.\n");
					continue;
				case 1:
					break;
			}
			break; 
	} 
	Student *last,*body=(Student*)malloc(sizeof(Student));
	for(i=1;i<=n;i++)
	{
		last=(Student*)malloc(sizeof(Student));
		if(i==1)
		{
			head=last;
			last->next=NULL;
		}
		else
		{
			body->next=last;
		}
		input(head,last,i);
		body=last;
	} 
	printf("数据录入成功,");
	return head; 
}

int cont(Student *p)//后续接续函数//别问为啥不复用build函数,第二次进入build函数后head指针会不知道为啥变成赋值前的初始位置 
{//被指针气晕 
	Student *Head=p;
	for(;p->next!=NULL;p=p->next);//将p(head) 调整到链表尾部
	int i,n;
	printf("请输入总共要录入的人数:");
	while(1)
	{
		switch(num_examine(&n))
			{
				case -1:
					printf("数字有非法字符,请重新输入.\n");
					continue;
				case 0:
					printf("数字输入不合法,请重新输入.\n");
					continue;
				case 1:
					break;
			}
			break; 
	}
	Student *last,*body=(Student*)malloc(sizeof(Student));
	for(i=1;i<=n;i++)
	{
		if(i==1)
		{
			last=(Student*)malloc(sizeof(Student)); 
			p->next=last;
			last->next=NULL; 
		}
		else
		{
			body->next=last; 
		}
		input(Head,last,i);
		body=last; 
	}
	printf("数据录入成功,"); 
	return 1; 
}
int all_output(Student *p)//全部输出 
{
	printf("学号\t姓名\t性别\t英语\t数学\t程序设计\n");
	for(;p!=NULL;p=p->next)
	{
		printf("%s\t%s\t%c\t%.1f\t%.1f\t%.1f\n",p->id,p->name,p->sex,p->score[0],p->score[1],p->score[2]);
	}
	return 1;
} 

Student *output(Student *p)//单独输出 
{
	printf("学号\t姓名\t性别\t英语\t数学\t程序设计\n");
	printf("%s\t%s\t%c\t%.1f\t%.1f\t%.1f\n",p->id,p->name,p->sex,p->score[0],p->score[1],p->score[2]);
	return p;
}

Student *id_find(Student *p)//学号查找 
{
	char tail='t',id[6],i='i';
	while(1)
	{ 
		printf("请输入学生的学号:");
		scanf("%s",id);
		switch(id_examine(tail,id,p))
		{
		case -1:
			continue;
		case 0:
			{
				return get_i_n(i,id,p); 
				//Student *pp=get_i_n(i,id,p);
				//printf("学号\t姓名\t性别\t英语\t数学\t程序设计\n");
				//printf("%s\t%s\t%c\t%.1f\t%.1f\t%.1f\n",pp->id,pp->name,pp->sex,pp->score[0],pp->score[1],pp->score[2]);
				//return 1;
			}
		case 1:
			printf("未找到该学生,请检查您输入的学号信息.\n");
			fflush(stdin);
			continue;
		}
	}
}

int name_find(Student *p)//姓名查找 
{
	extern Student *namefind[10];
	int i=-1,j;
	for(j=0;j<10;j++)
		namefind[j]=NULL;
	char name[20],n='n';
	Student *pp;
	while(1)
	{
		printf("请输入学生的姓名:");
		scanf("%s",name);
		while(1)
		{
			pp=get_i_n(n,name,p);
			if(pp==NULL&&i==-1)
			{
				printf("未找到该学生,请检查您输入的姓名信息.\n");
				break;
			}
			if(i==-1)
			{ 
				printf("学号\t姓名\t性别\t英语\t数学\t程序设计\n");
				i=0;
			}
			if(pp!=NULL)
			{ 
				printf("%s\t%s\t%c\t%.1f\t%.1f\t%.1f\n",pp->id,pp->name,pp->sex,pp->score[0],pp->score[1],pp->score[2]);
				namefind[i]=pp;
				i++;
				p=pp->next;
			}
			else
				break; 
		}
		namefind[i+1]=NULL;
		return 1;
	}
}
int id_sort(Student *p,int n)//学号排序,从低到高
{
	int i,j;
	Student *pp;
	Student temp,*ptemp;
	for(i=1;i<=n-1;i++,p=p->next)
	{
		for(j=i+1,pp=p->next;j<=n;j++,pp=pp->next)
			if(strcmp(p->id,pp->id)>0)
			{
				temp=*pp;
				*pp=*p;
				*p=temp;
				ptemp=pp->next;
				pp->next=p->next;
				p->next=ptemp;
			}
	}
	printf("排序完成,");
	system("pause"); 
	return 1;
}

int sort(int course,Student *p,int n)//鸡排核心 
{
	int i,j;
	Student *pp;
	Student temp,*ptemp;
	for(i=1;i<=n-1;i++,p=p->next)
	{
		for(j=i+1,pp=p->next;j<=n;j++,pp=pp->next)
			if((p->score[course])<(pp->score[course]))
			{
				 temp=*p;
				 *p=*pp;
				 *pp=temp;
				 ptemp=p->next;
				 p->next=pp->next;
				 pp->next=ptemp;
			} 
	}
}

int score_sort(Student *p,int n)//绩排
{
	int course;
	while(1)
	{ 
		printf("请输入需要排序的学科:\t1:英语\t2:数学\t3:程序设计");
		scanf("%d",&course);
		course--;
		if(ws_examine()==0)
		{
			printf("请您输入正确的学科序号.\n");
			continue;
		} 
		switch(course)
		{
			case 0:break;
			case 1:break;
			case 2:break;
			default: 
			printf("请您输入正确的学科序号.\n");
			continue; 
		}
		break;
	}
	sort(course,p,n);
	printf("排序完成,");
	system("pause");
	return 1;
}
int name_alter(Student *head)//需要先调用manefind函数以得到姓名列表
{
	extern Student *namefind[10];
	int i,j,n;
	for(i=0;namefind[i]!=NULL;i++);
	if(i==1)
	{
		printf("请输入要修改的信息:\n");
		score_input(namefind[i-1],i);
	}
	else
	{
		while(1)
		{ 
			printf("请确认要修改的学生序号:\n");
			for(j=0;j<i;j++)
			{
				printf("%d: %s\t",j+1,namefind[j]->name);
			}
			printf("\t");
			scanf("%d",&n);
			if(n>i||(!ws_examine()))
			{
				printf("请检查您所输入的学生序号!\n");
				fflush(stdin); 
				continue;
			}
			printf("请输入要修改的信息:\n");
			score_input(namefind[n-1],i);
			break; 
		}
	}
	printf("修改完成,");
	system("pause"); 
	return 1;
}

int id_alter(Student *p)//学号修改
{
	extern Student *head;
	int n=1;
	printf("请输入要修改的信息:\n");
	score_input(p,n);
	printf("修改完成,");
	system("pause"); 
	return 1;
}
//删除链表节点有两种方式:将目标节点上一个的next改为目标节点的next;复制目标节点的下一个的内容到目标节点,free目标节点的下一个节点 
int name_del(Student *Head)//需先调用namefind函数
{
	extern Student *namefind[10];
	extern Student *head;
	Student temp={" "," ",' ',{0.0,0.0,0.0},NULL};
	int i,j,n;
	char choice='n'; 
	for(i=0;namefind[i]!=NULL;i++);
	if(i==1)//只找到一个姓名 
	{
		fflush(stdin);
		printf("请确认是否删除该学生的信息(y/n):");
		while(1)
		{
			scanf("%c",&choice);
			fflush(stdin);
			switch(choice)
			{
				case 'y':
					if(Head==namefind[i-1])
					{
						if (list_len(head)==1)//在链表只剩一个节点时,只对节点初始化,不free.
						{
							*head=temp;
							rounds=0;//此时使输入信息选项变成建立一个链表 
							printf("删除成功,");
							system("pause");
							return 1;
						}
						*head=*(namefind[i-1]->next);//删除头节点的情况//这里直接换头
						free(namefind[i-1]->next);
						printf("删除成功,");
						system("pause");
						return 1;
					}
					//删除其他节点的情况 
					for(;Head->next!=namefind[i-1];Head=Head->next);//找到目标节点的上一节点
					Head->next=namefind[i-1]->next;
					namefind[i-1]->next=NULL;
					free(namefind[i-1]);
					printf("删除成功,");
					system("pause");
						return 1; 
				case 'n':
					return 0;
				default:
					printf("\n请输入正确的信息(y/n): ");
					continue;
			}
		}
	}
	else//找到不止一个姓名 
	{
		while(1)
		{ 
			printf("请确认要删除的学生序号:\n");
			for(j=0;j<i;j++)
			{
				printf("%d: %s\t",j+1,namefind[j]->name);
			}
			printf("\t");
			scanf("%d",&n);
			if(n>i||(!ws_examine()))//对输入合法性审查
			{
				printf("请检查您所输入的学生序号!\n");
				fflush(stdin);
				continue; 
			}
			fflush(stdin);
			printf("请确认是否删除该学生的信息(y/n):");
			while(1)
			{	
				scanf("%c",&choice);
				fflush(stdin);
				switch(choice)
				{
					case 'y':
						if(Head==namefind[n-1])//头节点 
						{
							*head=*(namefind[n-1]->next);//这里直接换头 too
							free(namefind[n-1]->next); 
							printf("删除成功,");
							system("pause");
							return 1;
						}
						for(;Head->next!=namefind[n-1];Head=Head->next);//调整到目标节点的上一节点 
						Head->next=namefind[n-1]->next;//一般节点 
						namefind[n-1]->next=NULL;
						free(namefind[n-1]); 
						printf("删除成功,");
						system("pause");
						return 1; 
					case 'n':
						break;
					default:
						printf("\n请输入正确的信息(y/n): ");
						continue;
				}
			}
		}
	}
	return 1;
}

int id_del(Student *Head)//姓名删除 
{
	Student temp={" "," ",' ',{0.0,0.0,0.0},NULL};
	Student *mid=output(id_find(Head));
	char choice='n';
	fflush(stdin);
	printf("请确认是否删除该学生的信息(y/n):");
	while(1)
	{	
		scanf("%c",&choice);
		fflush(stdin); 
		switch(choice)
		{
			case 'y':
				if(Head==mid)
				{
					if (list_len(head)==1)//在链表只剩一个节点时,只对节点初始化,不free.
					{
						*head=temp;
						rounds=0;
						printf("删除成功,");
						system("pause");
						return 1;
					}
					*head=*(mid->next);//头节点//这里直接换头 also
					free(mid->next);
					printf("删除成功,");
					system("pause");
					return 1;
				} 
				for(;Head->next!=mid;Head=Head->next);//一般节点 
				Head->next=mid->next;
				mid->next=NULL;
				free(mid);
				printf("删除成功,");
				system("pause");
				return 1; 
			case 'n':
				return 0;
			default:
				printf("\n请输入正确的信息(y/n): ");
				continue;
		}
	}
}
int analysis(Student *head)
{
	Student *p=head; 
	int i;
	char sname[][9]={"英语","数学","程序设计"};
	float sum=0,sta[3][13]={0};//max min average 优秀 % 良好 % 尚可 % 及格 % 寄了 %
	int total=list_len(p);
	for(i=0;i<3;i++)
	{
		p=head;
		sum=0;
		sort(i,p,total);//英排/数排/程排
		sta[i][0]=head->score[i];//max
		for(p=head;p->next!=NULL;p=p->next);//将p调整到最后一个节点
		sta[i][1]=p->score[i];//min 
		for(p=head;p!=NULL;p=p->next) 
			sum+=p->score[i];//累加计算总分
		sta[i][2]=sum/total;//average
		for(p=head;p!=NULL;p=p->next)
		{
			switch((int)((p->score[i])/10))//累加计数
			{
				case 10:
				case 9:
					sta[i][3]++;
					//printf("\n额啊你给我正常点:%d\n",(int)sta[i][3]);
					break;//优秀
				case 8:
					sta[i][5]++;
					break;//良好
				case 7:
					sta[i][7]++;
					break;//尚可
				case 6:
					sta[i][9]++;
					break;//及格
				default:
					sta[i][11]++;
					break;//寄了
			}
		}//求百分比
		//printf("\n这里应该有%d回 呃啊测试测试:%d\n",i,(int)sta[i][3]);
		sta[i][4]=sta[i][3]/total*100;//优秀百分比
		//printf("\n难道是这里%d错了?:%d  再打印个百分数看看:%.1f\n",i,(int)sta[i][3],sta[i][4]);
		sta[i][6]=sta[i][5]/total*100;//良好百分比
		sta[i][8]=sta[i][7]/total*100;//尚可百分比
		sta[i][10]=sta[i][9]/total*100;//及格百分比
		sta[i][12]=sta[i][11]/total*100;//100-(上头的加起来的)也行 
	}
	//printf("\n最终测试,再错说不过去了:%d\n",(int)sta[0][3]);
	printf("总人数:%d人\n",total);
	printf("\t\t%s\t%s\t%s\n",sname[0],sname[1],sname[2]);
	printf("最高分:\t\t%.1f\t%.1f\t%.1f\n",sta[0][0],sta[1][0],sta[2][0]);
	printf("最低分:\t\t%.1f\t%.1f\t%.1f\n",sta[0][1],sta[1][1],sta[2][1]);
	printf("平均分:\t\t%.1f\t%.1f\t%.1f\n",sta[0][2],sta[1][2],sta[2][2]);
	printf("成绩分布:\n");
	printf("90~100分:\t%d人 %.1f%%\t%d人 %.1f%%\t%d人 %.1f%%\n",(int)sta[0][3],sta[0][4],(int)sta[1][3],sta[1][4],(int)sta[2][3],sta[2][4]);
	printf("80~89分:\t%d人 %.1f%%\t%d人 %.1f%%\t%d人 %.1f%%\n",(int)sta[0][5],sta[0][6],(int)sta[1][5],sta[1][6],(int)sta[1][5],sta[1][6]);
	printf("70~79分:\t%d人 %.1f%%\t%d人 %.1f%%\t%d人 %.1f%%\n",(int)sta[0][7],sta[0][8],(int)sta[1][7],sta[1][8],(int)sta[2][7],sta[2][8]);
	printf("60~69分:\t%d人 %.1f%%\t%d人 %.1f%%\t%d人 %.1f%%\n",(int)sta[0][9],sta[0][10],(int)sta[1][9],sta[1][10],(int)sta[2][9],sta[2][10]);
	printf("60分以下:\t%d人 %.1f%%\t%d人 %.1f%%\t%d人 %.1f%%\n",(int)sta[0][11],sta[0][12],(int)sta[1][11],sta[1][12],(int)sta[2][11],sta[2][12]);
	printf("统计完成,");
	system("pause");
}
//文件写入与读取
//由于直接将结构体写入文件,所以从外部直接打开文件为乱码 
int save(Student *p)//这里接的是链表头的指针 
{
	FILE *fp=NULL;
	int i,len=list_len(p),size=sizeof(Student);
	if((fp=fopen("chengji.txt","wb"))==NULL)
	{
	    printf("打开失败\n");
		system("pause");
    	return 0;
	}
	for(i=0;i<len;i++)
	{
		fwrite(p,size,1,fp);
		p=p->next;
	}
	fclose(fp);
	printf("保存成功,");
	system("pause");
	return 1;
}

Student *load()//可以复用input.cpp中的build函数//又不是啥时候都有FILE指针的,还得再给FILE指针开个位置,不值当 
{
	extern Student *head;
	Student *p=NULL,*Head=head;
	int n,i;
	Student temp={"a000","0",'f',{0.0,0.0,0.0},head};//这里为了不留野指针(为啥会突然注意这个)(主要是后面会检查一遍这个指针,谁知道会不会指到空呢?)//c语言中没有明确指明0x0和NULL的区别(搜的)
	for(Head=Head->next;Head!=NULL;Head=Head->next)//清空链表内容//留下head不删
	{
		free(p);//free一个空指针将不会进行任何操作
		p=Head;
	}
	FILE *fp=NULL;
	if((fp=fopen("chengji.txt","r"))==NULL)
	{
		printf("打开成绩文件失败,请检查文件夹是否有目标文件.\n");
		system("pause"); 
		return 0; 
	}
	else
	{
		printf("打开成绩文件成功\n");
	}
	for(n=0;temp.next!=NULL;n++)//得到文件中链表的长度
	{
		fread(&temp,sizeof(Student),1,fp);
	}
	fseek(fp,0,SEEK_SET);//将fp调整到文件开头
	Student *last,*body=(Student*)malloc(sizeof(Student));//复用了build函数的一部分
	for(i=1;i<=n;i++)
	{
		last=(Student*)malloc(sizeof(Student));
		if(i==1)
		{
			head=last;
			last->next=NULL;
		}
		else
		{
			body->next=last;
		}
		fread(last,sizeof(Student),1,fp);
		body=last;
	}
	fclose(fp);
	printf("数据录入成功,");
	system("pause");
	return head;
}
int choice_find(Student *head)
{
	while(1)
	{
		int choice;
		printf("请选择查询类型:\n 1、ID查询 2、姓名查询 0退出\t"); 
		scanf("%d",&choice);
		if(!ws_examine())
		{
			printf("请您输入正确的数字.\n");
			continue;
		}
		switch(choice)
		{
			case 1:
				output(id_find(head));
				return 1;
			case 2:
				name_find(head);
				return 1;
			case 0:
				return 0;
			default :
				fflush(stdin);
				printf("请您输入正确的数字.\n");
				continue;
		}
	}
}

int choice_sort(Student *head)
{
	while(1)
	{
		int choice;
		printf("请选择排序方式:\n 1、ID排序 2、成绩排序 0退出\t");
		scanf("%d",&choice);
		if(!ws_examine())
		{
			printf("请您输入正确的数字.\n");
			continue;
		}
		switch(choice)
		{
			case 1:
				id_sort(head,list_len(head));
				return 1;
			case 2:
				score_sort(head,list_len(head));
				return 1;
			case 0:
				return 0;
			default :
				fflush(stdin);
				printf("请您输入正确的数字.\n");
				continue;
		}
	}
}

int choice_alter(Student *head)
{
	while(1)
	{
		int choice;
		printf("请选择查找类型:\n 1、ID查询 2、姓名查询 0退出\t");
		scanf("%d",&choice);
		if(!ws_examine())
		{
			printf("请您输入正确的数字.\n");
			continue;
		}
		switch(choice)
		{
			case 1:
				id_alter(output(id_find(head)));
				return 1;
			case 2:
				name_find(head);
				name_alter(head);
				return 1;
			case 0:
				return 0;
			default :
				fflush(stdin);
				printf("请您输入正确的数字.\n");
				continue;
		}
	}
}

int choice_del(Student *head)
{
	while(1)
	{
		int choice;
		printf("请选择查找类型:\n 1、ID查询 2、姓名查询 0退出\t");
		scanf("%d",&choice);
		if(!ws_examine())
		{
			printf("请您输入正确的数字.\n");
			continue;
		}
		switch(choice)
		{
			case 1:
				id_del(head);
				return 1;
			case 2:
				while(1)
				{
					name_find(head);
					if(!name_del(head))
						continue;
					break;
				}
				return 1;
			case 0:
				return 0;
			default :
				fflush(stdin);
				printf("请您输入正确的数字.\n");
				continue;
		}
	}
}
int home(Student *head)
{
	rounds=0;
	while(1)
	{
		system("cls");//清屏 
		int choice=-1;
		printf("-----------------学生成绩管理系统-----------------\n");
		printf("**********输入选项前的数字以执行相应操作**********\n");
		printf(" 1信息录入 2信息显示 3信息查询 4成绩排序 5信息修改\n");
		printf(" 6信息删除 7信息统计 8保存文件 9读取文件     0退出\t");
		scanf("%d",&choice);
		if(!ws_examine())//合法性审查 
		{
			printf("请您输入正确的数字.");
			system("pause");
			continue;
		}
		switch(choice)
		{
			case 1://信息录入 
				if(rounds==0)
				{
					head=build(head);
					rounds++;
				}
				else
				{
					cont(head);
				}
				system("pause");break;
			case 2://信息显示 
				all_output(head);
				system("pause");break;
			case 3://信息查询 
				choice_find(head);
				system("pause");break;
			case 4://成绩排序 
				choice_sort(head);break;
			case 5://信息修改 
				choice_alter(head);break;
			case 6://信息删除 
				choice_del(head);break;
			case 7://信息统计 
				analysis(head);break;
			case 8://保存文件 
				save(head);break;
			case 9://读取文件 
				head=load();rounds++;break;
			case 0://退出程序 
				return 0;
			default :
				fflush(stdin);
				printf("请您输入正确的数字.");
				system("pause");
				continue;
		}
		continue;
	}
}
//因为头节点在删除操作时可能会发生更改,所以暂时不能用const将其设为常量,此隐患可能会在以后修改
//修改头节点的地方多了去了,不改了
//关于头文件的引用：在最开始写的时候没有建立一个项目，所以直接包括的源文件 
Student *namefind[10];
Student *head;
int rounds;
 
int main()
{
 	head=(Student*)malloc(sizeof(Student));
	head->next=NULL;//这两句是为了在录入文件的时候不出错
	home(head);
	return 0;
}
//下面是写的时候单独函数的使用方法 
//	cont(head);//在链表后面加东西

//  输入  //head=build(head);
//  输出  //all_output(head);

// id查找 //output(id_find(head));
//姓名查找//name_find(head);

// id排名 //id_sort(head,list_len(head));
//成绩排名//score_sort(head,list_len(head));

//姓名修改//
          /*name_find(head);
          name_alter(head);*/
// id修改 //id_alter(output(id_find(head)));

//姓名删除//
    /*while(1)
	{
		name_find(head); 
		if(!name_del(head))
			continue;
		break; 
	}*/
// id删除 //id_del(head);

//信息统计//analysis(head); 
//文件保存//save(head);
//文件读取//head=load();
