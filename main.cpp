/*
	���뻷����Dev-C++ 5.4.0 
	����޸ģ�2023 �� 1 �� 27 ��
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
int list_len(Student *p)//���������� 
{
	int i;
	for(i=0;p!=NULL;i++,p=p->next);
	return i;
}

int id_validity(char id[6])//ѧ�źϷ����ж� 1Ϊ�Ϸ� 0Ϊ�Ƿ� 
{
	int i;
	if(strlen(id)>4)
		return 0;
	if((id[0]>=65&&id[0]<=90)||(id[0]>=97&&id[0]<=122));//��һ������Ϊ��ĸ 
	else
		return 0;
	if((id[1]>=65&&id[1]<=90)||(id[1]>=97&&id[1]<=122)||(id[1]>=48&&id[1]<=57));//�ڶ�������Ϊ��ĸ������ 
	else
		return 0;
	for(i=2;i<4;i++)//�������ĸ�����Ϊ����
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

int id_examine(char kind,char id[6],Student *p)//ѧ�Ų��� 1Ϊ���� 0Ϊ�� -1Ϊ�Ƿ� kind==nΪ���������β(����ѧ����һ���ظ�)
{
	if(!id_validity(id))
	{
		printf("��ѧ�Ų��Ϸ�,����������.\n");
		fflush(stdin); 
		return -1;
	}
	if(kind=='n')//no tail ��� ��ȫ���� �������һ����ͬԪ�� 
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
	if(kind=='t')//tail ��� ȫ����
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

Student *get_i_n(char s,char a[20],Student *p)//��ȡ��ͬ id(i)�� name(n)������ڵ�
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

int ws_examine()//�Ƕ��ַ��ж� 1Ϊ�޶��ַ� 0Ϊ���ֺ����ַ�//��:Ҫ�����������ʱ,�� 2f ��Ϊ�Ƿ�����
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

int sex_validity(char *a)//�Ա�Ϸ����ж� 1Ϊ�Ϸ� 0Ϊ�Ƿ� 
{
	if(*a=='f'||*a=='m')
		return 1;
	else
	{
		*a='f'; 
		return 0;
	}
} 

int num_examine(int *p)//��������_�Ϸ����ж� 1Ϊ�������� 
{ 
	int x=scanf("%d",p);
	if(x==0)
	{
		fflush(stdin);
		return 0;//����ͷ���ַ� //�����ʵ��̫����,һ���ж������ַ�Χ�Ͳ����
	} 
	if(ws_examine()==0)
	{
		return -1;//����β���ַ� 
	}
	return 1;//�������� 
}

int get_num(float *p)//����ɼ�_�Ϸ����ж� 1Ϊ�������� 
{ 
	int x=scanf("%f",p);
	if(x==0)
	{
		fflush(stdin);
		return 0;//����ͷ���ַ� 
	} 
	if(ws_examine()==0)
	{
		return -1;//����β���ַ� 
	}
	return 1;//�������� 
}

int score_examine(float n)//�����ж� 1Ϊ�������� 0������
{
	if(n>=0&&n<=100)
		return 1;
	return 0;
}
void score_input(Student *last,int i)//ר�ŵĳɼ�����,������Ϣ¼����ɼ��޸� 
{
	int j;
	char sname[][9]={"Ӣ��","��ѧ","�������"};
	for(j=0;j<3;j++)
	{
		while(1)
		{
			printf("��%d��ѧ����%s�ɼ�:",i,sname[j]);
			switch(get_num(&last->score[j]))
			{
				case -1:
					printf("�ɼ��зǷ��ַ�,����������.\n");
					continue;
				case 0:
					printf("�ɼ����벻�Ϸ�,����������.\n");
					continue;
				case 1:
					break;
			}
			if(!score_examine(last->score[j]))
			{
				printf("�ɼ����벻�Ϸ�,����������.\n");
				fflush(stdin);
				continue;
			}
			break; 
		}
	}
}

void input(Student *head,Student *last,int i)//�����������뺯��
{
	char notail='n';
	while(1)
	{ 
		printf("��%d��ѧ����ѧ��:",i);
		scanf("%s",last->id);
		switch(id_examine(notail,last->id,head))//����Ĳ����������һ���ظ�(����β)
		{
		case -1:
			continue;
		case 0:
			printf("��ѧ���Ѵ���,����������.\n");
			continue;
		case 1:
			break;
		}
		break;
	}
	printf("��%d��ѧ��������:",i);
	scanf("%s",last->name);
	getchar(); 
	while(1)
	{
		printf("��%d��ѧ�����Ա�(f/m):",i);
		last->sex=getchar();
		if((!ws_examine())||(!sex_validity(&(last->sex))))
		{
			printf("�Ա����,�����������Ա�.\n");
			continue;
		}
		break;
	}
	score_input(last,i);
}

Student *build(Student *head)//���������� 
{
	int i,n;
	printf("�������ܹ�Ҫ¼�������:");
	while(1)
	{
		switch(num_examine(&n))
			{
				case -1:
					printf("�����зǷ��ַ�,����������.\n");
					continue;
				case 0:
					printf("�������벻�Ϸ�,����������.\n");
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
	printf("����¼��ɹ�,");
	return head; 
}

int cont(Student *p)//������������//����Ϊɶ������build����,�ڶ��ν���build������headָ��᲻֪��Ϊɶ��ɸ�ֵǰ�ĳ�ʼλ�� 
{//��ָ������ 
	Student *Head=p;
	for(;p->next!=NULL;p=p->next);//��p(head) ����������β��
	int i,n;
	printf("�������ܹ�Ҫ¼�������:");
	while(1)
	{
		switch(num_examine(&n))
			{
				case -1:
					printf("�����зǷ��ַ�,����������.\n");
					continue;
				case 0:
					printf("�������벻�Ϸ�,����������.\n");
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
	printf("����¼��ɹ�,"); 
	return 1; 
}
int all_output(Student *p)//ȫ����� 
{
	printf("ѧ��\t����\t�Ա�\tӢ��\t��ѧ\t�������\n");
	for(;p!=NULL;p=p->next)
	{
		printf("%s\t%s\t%c\t%.1f\t%.1f\t%.1f\n",p->id,p->name,p->sex,p->score[0],p->score[1],p->score[2]);
	}
	return 1;
} 

Student *output(Student *p)//������� 
{
	printf("ѧ��\t����\t�Ա�\tӢ��\t��ѧ\t�������\n");
	printf("%s\t%s\t%c\t%.1f\t%.1f\t%.1f\n",p->id,p->name,p->sex,p->score[0],p->score[1],p->score[2]);
	return p;
}

Student *id_find(Student *p)//ѧ�Ų��� 
{
	char tail='t',id[6],i='i';
	while(1)
	{ 
		printf("������ѧ����ѧ��:");
		scanf("%s",id);
		switch(id_examine(tail,id,p))
		{
		case -1:
			continue;
		case 0:
			{
				return get_i_n(i,id,p); 
				//Student *pp=get_i_n(i,id,p);
				//printf("ѧ��\t����\t�Ա�\tӢ��\t��ѧ\t�������\n");
				//printf("%s\t%s\t%c\t%.1f\t%.1f\t%.1f\n",pp->id,pp->name,pp->sex,pp->score[0],pp->score[1],pp->score[2]);
				//return 1;
			}
		case 1:
			printf("δ�ҵ���ѧ��,�����������ѧ����Ϣ.\n");
			fflush(stdin);
			continue;
		}
	}
}

int name_find(Student *p)//�������� 
{
	extern Student *namefind[10];
	int i=-1,j;
	for(j=0;j<10;j++)
		namefind[j]=NULL;
	char name[20],n='n';
	Student *pp;
	while(1)
	{
		printf("������ѧ��������:");
		scanf("%s",name);
		while(1)
		{
			pp=get_i_n(n,name,p);
			if(pp==NULL&&i==-1)
			{
				printf("δ�ҵ���ѧ��,�����������������Ϣ.\n");
				break;
			}
			if(i==-1)
			{ 
				printf("ѧ��\t����\t�Ա�\tӢ��\t��ѧ\t�������\n");
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
int id_sort(Student *p,int n)//ѧ������,�ӵ͵���
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
	printf("�������,");
	system("pause"); 
	return 1;
}

int sort(int course,Student *p,int n)//���ź��� 
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

int score_sort(Student *p,int n)//����
{
	int course;
	while(1)
	{ 
		printf("��������Ҫ�����ѧ��:\t1:Ӣ��\t2:��ѧ\t3:�������");
		scanf("%d",&course);
		course--;
		if(ws_examine()==0)
		{
			printf("����������ȷ��ѧ�����.\n");
			continue;
		} 
		switch(course)
		{
			case 0:break;
			case 1:break;
			case 2:break;
			default: 
			printf("����������ȷ��ѧ�����.\n");
			continue; 
		}
		break;
	}
	sort(course,p,n);
	printf("�������,");
	system("pause");
	return 1;
}
int name_alter(Student *head)//��Ҫ�ȵ���manefind�����Եõ������б�
{
	extern Student *namefind[10];
	int i,j,n;
	for(i=0;namefind[i]!=NULL;i++);
	if(i==1)
	{
		printf("������Ҫ�޸ĵ���Ϣ:\n");
		score_input(namefind[i-1],i);
	}
	else
	{
		while(1)
		{ 
			printf("��ȷ��Ҫ�޸ĵ�ѧ�����:\n");
			for(j=0;j<i;j++)
			{
				printf("%d: %s\t",j+1,namefind[j]->name);
			}
			printf("\t");
			scanf("%d",&n);
			if(n>i||(!ws_examine()))
			{
				printf("�������������ѧ�����!\n");
				fflush(stdin); 
				continue;
			}
			printf("������Ҫ�޸ĵ���Ϣ:\n");
			score_input(namefind[n-1],i);
			break; 
		}
	}
	printf("�޸����,");
	system("pause"); 
	return 1;
}

int id_alter(Student *p)//ѧ���޸�
{
	extern Student *head;
	int n=1;
	printf("������Ҫ�޸ĵ���Ϣ:\n");
	score_input(p,n);
	printf("�޸����,");
	system("pause"); 
	return 1;
}
//ɾ������ڵ������ַ�ʽ:��Ŀ��ڵ���һ����next��ΪĿ��ڵ��next;����Ŀ��ڵ����һ�������ݵ�Ŀ��ڵ�,freeĿ��ڵ����һ���ڵ� 
int name_del(Student *Head)//���ȵ���namefind����
{
	extern Student *namefind[10];
	extern Student *head;
	Student temp={" "," ",' ',{0.0,0.0,0.0},NULL};
	int i,j,n;
	char choice='n'; 
	for(i=0;namefind[i]!=NULL;i++);
	if(i==1)//ֻ�ҵ�һ������ 
	{
		fflush(stdin);
		printf("��ȷ���Ƿ�ɾ����ѧ������Ϣ(y/n):");
		while(1)
		{
			scanf("%c",&choice);
			fflush(stdin);
			switch(choice)
			{
				case 'y':
					if(Head==namefind[i-1])
					{
						if (list_len(head)==1)//������ֻʣһ���ڵ�ʱ,ֻ�Խڵ��ʼ��,��free.
						{
							*head=temp;
							rounds=0;//��ʱʹ������Ϣѡ���ɽ���һ������ 
							printf("ɾ���ɹ�,");
							system("pause");
							return 1;
						}
						*head=*(namefind[i-1]->next);//ɾ��ͷ�ڵ�����//����ֱ�ӻ�ͷ
						free(namefind[i-1]->next);
						printf("ɾ���ɹ�,");
						system("pause");
						return 1;
					}
					//ɾ�������ڵ����� 
					for(;Head->next!=namefind[i-1];Head=Head->next);//�ҵ�Ŀ��ڵ����һ�ڵ�
					Head->next=namefind[i-1]->next;
					namefind[i-1]->next=NULL;
					free(namefind[i-1]);
					printf("ɾ���ɹ�,");
					system("pause");
						return 1; 
				case 'n':
					return 0;
				default:
					printf("\n��������ȷ����Ϣ(y/n): ");
					continue;
			}
		}
	}
	else//�ҵ���ֹһ������ 
	{
		while(1)
		{ 
			printf("��ȷ��Ҫɾ����ѧ�����:\n");
			for(j=0;j<i;j++)
			{
				printf("%d: %s\t",j+1,namefind[j]->name);
			}
			printf("\t");
			scanf("%d",&n);
			if(n>i||(!ws_examine()))//������Ϸ������
			{
				printf("�������������ѧ�����!\n");
				fflush(stdin);
				continue; 
			}
			fflush(stdin);
			printf("��ȷ���Ƿ�ɾ����ѧ������Ϣ(y/n):");
			while(1)
			{	
				scanf("%c",&choice);
				fflush(stdin);
				switch(choice)
				{
					case 'y':
						if(Head==namefind[n-1])//ͷ�ڵ� 
						{
							*head=*(namefind[n-1]->next);//����ֱ�ӻ�ͷ too
							free(namefind[n-1]->next); 
							printf("ɾ���ɹ�,");
							system("pause");
							return 1;
						}
						for(;Head->next!=namefind[n-1];Head=Head->next);//������Ŀ��ڵ����һ�ڵ� 
						Head->next=namefind[n-1]->next;//һ��ڵ� 
						namefind[n-1]->next=NULL;
						free(namefind[n-1]); 
						printf("ɾ���ɹ�,");
						system("pause");
						return 1; 
					case 'n':
						break;
					default:
						printf("\n��������ȷ����Ϣ(y/n): ");
						continue;
				}
			}
		}
	}
	return 1;
}

int id_del(Student *Head)//����ɾ�� 
{
	Student temp={" "," ",' ',{0.0,0.0,0.0},NULL};
	Student *mid=output(id_find(Head));
	char choice='n';
	fflush(stdin);
	printf("��ȷ���Ƿ�ɾ����ѧ������Ϣ(y/n):");
	while(1)
	{	
		scanf("%c",&choice);
		fflush(stdin); 
		switch(choice)
		{
			case 'y':
				if(Head==mid)
				{
					if (list_len(head)==1)//������ֻʣһ���ڵ�ʱ,ֻ�Խڵ��ʼ��,��free.
					{
						*head=temp;
						rounds=0;
						printf("ɾ���ɹ�,");
						system("pause");
						return 1;
					}
					*head=*(mid->next);//ͷ�ڵ�//����ֱ�ӻ�ͷ also
					free(mid->next);
					printf("ɾ���ɹ�,");
					system("pause");
					return 1;
				} 
				for(;Head->next!=mid;Head=Head->next);//һ��ڵ� 
				Head->next=mid->next;
				mid->next=NULL;
				free(mid);
				printf("ɾ���ɹ�,");
				system("pause");
				return 1; 
			case 'n':
				return 0;
			default:
				printf("\n��������ȷ����Ϣ(y/n): ");
				continue;
		}
	}
}
int analysis(Student *head)
{
	Student *p=head; 
	int i;
	char sname[][9]={"Ӣ��","��ѧ","�������"};
	float sum=0,sta[3][13]={0};//max min average ���� % ���� % �п� % ���� % ���� %
	int total=list_len(p);
	for(i=0;i<3;i++)
	{
		p=head;
		sum=0;
		sort(i,p,total);//Ӣ��/����/����
		sta[i][0]=head->score[i];//max
		for(p=head;p->next!=NULL;p=p->next);//��p���������һ���ڵ�
		sta[i][1]=p->score[i];//min 
		for(p=head;p!=NULL;p=p->next) 
			sum+=p->score[i];//�ۼӼ����ܷ�
		sta[i][2]=sum/total;//average
		for(p=head;p!=NULL;p=p->next)
		{
			switch((int)((p->score[i])/10))//�ۼӼ���
			{
				case 10:
				case 9:
					sta[i][3]++;
					//printf("\n������������:%d\n",(int)sta[i][3]);
					break;//����
				case 8:
					sta[i][5]++;
					break;//����
				case 7:
					sta[i][7]++;
					break;//�п�
				case 6:
					sta[i][9]++;
					break;//����
				default:
					sta[i][11]++;
					break;//����
			}
		}//��ٷֱ�
		//printf("\n����Ӧ����%d�� �������Բ���:%d\n",i,(int)sta[i][3]);
		sta[i][4]=sta[i][3]/total*100;//����ٷֱ�
		//printf("\n�ѵ�������%d����?:%d  �ٴ�ӡ���ٷ�������:%.1f\n",i,(int)sta[i][3],sta[i][4]);
		sta[i][6]=sta[i][5]/total*100;//���ðٷֱ�
		sta[i][8]=sta[i][7]/total*100;//�пɰٷֱ�
		sta[i][10]=sta[i][9]/total*100;//����ٷֱ�
		sta[i][12]=sta[i][11]/total*100;//100-(��ͷ�ļ�������)Ҳ�� 
	}
	//printf("\n���ղ���,�ٴ�˵����ȥ��:%d\n",(int)sta[0][3]);
	printf("������:%d��\n",total);
	printf("\t\t%s\t%s\t%s\n",sname[0],sname[1],sname[2]);
	printf("��߷�:\t\t%.1f\t%.1f\t%.1f\n",sta[0][0],sta[1][0],sta[2][0]);
	printf("��ͷ�:\t\t%.1f\t%.1f\t%.1f\n",sta[0][1],sta[1][1],sta[2][1]);
	printf("ƽ����:\t\t%.1f\t%.1f\t%.1f\n",sta[0][2],sta[1][2],sta[2][2]);
	printf("�ɼ��ֲ�:\n");
	printf("90~100��:\t%d�� %.1f%%\t%d�� %.1f%%\t%d�� %.1f%%\n",(int)sta[0][3],sta[0][4],(int)sta[1][3],sta[1][4],(int)sta[2][3],sta[2][4]);
	printf("80~89��:\t%d�� %.1f%%\t%d�� %.1f%%\t%d�� %.1f%%\n",(int)sta[0][5],sta[0][6],(int)sta[1][5],sta[1][6],(int)sta[1][5],sta[1][6]);
	printf("70~79��:\t%d�� %.1f%%\t%d�� %.1f%%\t%d�� %.1f%%\n",(int)sta[0][7],sta[0][8],(int)sta[1][7],sta[1][8],(int)sta[2][7],sta[2][8]);
	printf("60~69��:\t%d�� %.1f%%\t%d�� %.1f%%\t%d�� %.1f%%\n",(int)sta[0][9],sta[0][10],(int)sta[1][9],sta[1][10],(int)sta[2][9],sta[2][10]);
	printf("60������:\t%d�� %.1f%%\t%d�� %.1f%%\t%d�� %.1f%%\n",(int)sta[0][11],sta[0][12],(int)sta[1][11],sta[1][12],(int)sta[2][11],sta[2][12]);
	printf("ͳ�����,");
	system("pause");
}
//�ļ�д�����ȡ
//����ֱ�ӽ��ṹ��д���ļ�,���Դ��ⲿֱ�Ӵ��ļ�Ϊ���� 
int save(Student *p)//����ӵ�������ͷ��ָ�� 
{
	FILE *fp=NULL;
	int i,len=list_len(p),size=sizeof(Student);
	if((fp=fopen("chengji.txt","wb"))==NULL)
	{
	    printf("��ʧ��\n");
		system("pause");
    	return 0;
	}
	for(i=0;i<len;i++)
	{
		fwrite(p,size,1,fp);
		p=p->next;
	}
	fclose(fp);
	printf("����ɹ�,");
	system("pause");
	return 1;
}

Student *load()//���Ը���input.cpp�е�build����//�ֲ���ɶʱ����FILEָ���,�����ٸ�FILEָ�뿪��λ��,��ֵ�� 
{
	extern Student *head;
	Student *p=NULL,*Head=head;
	int n,i;
	Student temp={"a000","0",'f',{0.0,0.0,0.0},head};//����Ϊ�˲���Ұָ��(Ϊɶ��ͻȻע�����)(��Ҫ�Ǻ������һ�����ָ��,˭֪���᲻��ָ������?)//c������û����ȷָ��0x0��NULL������(�ѵ�)
	for(Head=Head->next;Head!=NULL;Head=Head->next)//�����������//����head��ɾ
	{
		free(p);//freeһ����ָ�뽫��������κβ���
		p=Head;
	}
	FILE *fp=NULL;
	if((fp=fopen("chengji.txt","r"))==NULL)
	{
		printf("�򿪳ɼ��ļ�ʧ��,�����ļ����Ƿ���Ŀ���ļ�.\n");
		system("pause"); 
		return 0; 
	}
	else
	{
		printf("�򿪳ɼ��ļ��ɹ�\n");
	}
	for(n=0;temp.next!=NULL;n++)//�õ��ļ�������ĳ���
	{
		fread(&temp,sizeof(Student),1,fp);
	}
	fseek(fp,0,SEEK_SET);//��fp�������ļ���ͷ
	Student *last,*body=(Student*)malloc(sizeof(Student));//������build������һ����
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
	printf("����¼��ɹ�,");
	system("pause");
	return head;
}
int choice_find(Student *head)
{
	while(1)
	{
		int choice;
		printf("��ѡ���ѯ����:\n 1��ID��ѯ 2��������ѯ 0�˳�\t"); 
		scanf("%d",&choice);
		if(!ws_examine())
		{
			printf("����������ȷ������.\n");
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
				printf("����������ȷ������.\n");
				continue;
		}
	}
}

int choice_sort(Student *head)
{
	while(1)
	{
		int choice;
		printf("��ѡ������ʽ:\n 1��ID���� 2���ɼ����� 0�˳�\t");
		scanf("%d",&choice);
		if(!ws_examine())
		{
			printf("����������ȷ������.\n");
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
				printf("����������ȷ������.\n");
				continue;
		}
	}
}

int choice_alter(Student *head)
{
	while(1)
	{
		int choice;
		printf("��ѡ���������:\n 1��ID��ѯ 2��������ѯ 0�˳�\t");
		scanf("%d",&choice);
		if(!ws_examine())
		{
			printf("����������ȷ������.\n");
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
				printf("����������ȷ������.\n");
				continue;
		}
	}
}

int choice_del(Student *head)
{
	while(1)
	{
		int choice;
		printf("��ѡ���������:\n 1��ID��ѯ 2��������ѯ 0�˳�\t");
		scanf("%d",&choice);
		if(!ws_examine())
		{
			printf("����������ȷ������.\n");
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
				printf("����������ȷ������.\n");
				continue;
		}
	}
}
int home(Student *head)
{
	rounds=0;
	while(1)
	{
		system("cls");//���� 
		int choice=-1;
		printf("-----------------ѧ���ɼ�����ϵͳ-----------------\n");
		printf("**********����ѡ��ǰ��������ִ����Ӧ����**********\n");
		printf(" 1��Ϣ¼�� 2��Ϣ��ʾ 3��Ϣ��ѯ 4�ɼ����� 5��Ϣ�޸�\n");
		printf(" 6��Ϣɾ�� 7��Ϣͳ�� 8�����ļ� 9��ȡ�ļ�     0�˳�\t");
		scanf("%d",&choice);
		if(!ws_examine())//�Ϸ������ 
		{
			printf("����������ȷ������.");
			system("pause");
			continue;
		}
		switch(choice)
		{
			case 1://��Ϣ¼�� 
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
			case 2://��Ϣ��ʾ 
				all_output(head);
				system("pause");break;
			case 3://��Ϣ��ѯ 
				choice_find(head);
				system("pause");break;
			case 4://�ɼ����� 
				choice_sort(head);break;
			case 5://��Ϣ�޸� 
				choice_alter(head);break;
			case 6://��Ϣɾ�� 
				choice_del(head);break;
			case 7://��Ϣͳ�� 
				analysis(head);break;
			case 8://�����ļ� 
				save(head);break;
			case 9://��ȡ�ļ� 
				head=load();rounds++;break;
			case 0://�˳����� 
				return 0;
			default :
				fflush(stdin);
				printf("����������ȷ������.");
				system("pause");
				continue;
		}
		continue;
	}
}
//��Ϊͷ�ڵ���ɾ������ʱ���ܻᷢ������,������ʱ������const������Ϊ����,���������ܻ����Ժ��޸�
//�޸�ͷ�ڵ�ĵط�����ȥ��,������
//����ͷ�ļ������ã����ʼд��ʱ��û�н���һ����Ŀ������ֱ�Ӱ�����Դ�ļ� 
Student *namefind[10];
Student *head;
int rounds;
 
int main()
{
 	head=(Student*)malloc(sizeof(Student));
	head->next=NULL;//��������Ϊ����¼���ļ���ʱ�򲻳���
	home(head);
	return 0;
}
//������д��ʱ�򵥶�������ʹ�÷��� 
//	cont(head);//���������Ӷ���

//  ����  //head=build(head);
//  ���  //all_output(head);

// id���� //output(id_find(head));
//��������//name_find(head);

// id���� //id_sort(head,list_len(head));
//�ɼ�����//score_sort(head,list_len(head));

//�����޸�//
          /*name_find(head);
          name_alter(head);*/
// id�޸� //id_alter(output(id_find(head)));

//����ɾ��//
    /*while(1)
	{
		name_find(head); 
		if(!name_del(head))
			continue;
		break; 
	}*/
// idɾ�� //id_del(head);

//��Ϣͳ��//analysis(head); 
//�ļ�����//save(head);
//�ļ���ȡ//head=load();
