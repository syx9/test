#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<conio.h>
#include<math.h>
using namespace std;

typedef struct BOOK//ͼ��ṹ��
{
     float price;//���޻�������
     int state,date,id;//״̬���������
     char bname[50],author[50],chuban[50],bman[50];//���������ߡ������硢��š�������
     struct BOOK *next;
}BOOK;
typedef struct READER//���߽ṹ��
{
     BOOK book[15];//������Ŀ
     char rname[50],num[20];//������ѧ��
     int much;//��������
     float money;
     struct READER *next;
}READERD;
BOOK *headLink;//�����ͷָ�룬����ȫ�֣�
READER *rheadlink;
int total;
/**********************************************************
                     ���к�������
**********************************************************/
void CreateHeadBook();//���������ͷ
void CreateHeadReader();//���������ͷ
BOOK *MallocBNode();//�����½�㲢��ʼ��
READER *MallocRNode();//�����½�㲢��ʼ��
void InsertBookNode(BOOK *t);//�ڱ�β����һ�����
void InsertReaderNode(READER *t);
void ReadBook();//���ļ���������
void ReadReader();
void DesplayBNode(BOOK *t);//���һ��������Ϣ
void DesplayRNode(READER *t);
void Mmenu();//���˵�
void chaxun();//��ѯ
void Borrow();//����
void jie();
void yonghu();//�û�
void rbook(char name[50]);//������ߵ�ͼ��
void tianjia();//������û�
void GetReader(READER *r);
void luru();
void GetBoook(BOOK *p);
void InsertoneReader(char name[50],char num[20],int n);//���һ������
void yonghu();
void luru();

/************************************
�������ܣ����������ͷ
************************************/
void CreateHeadBook()
{
	BOOK *p;
	p = (BOOK*)malloc(sizeof(BOOK));
	headLink = p;//����ͷָ�븳��ֵ
	p->next = NULL;
}
void CreateHeadReader()
{
     READER *p;
	p = (READER*)malloc(sizeof(READER));
	rheadlink=p;//����ͷָ�븳��ֵ
	p->next = NULL;
}


/************************************
�������ܣ����һ��������Ϣ
************************************/
void DesplayBNode(BOOK *t)
{
	printf("\n\t%d\t", t->id);
	printf("%s\t", t->bname);
	printf("%s\t", t->author);
	printf("%s\t", t->chuban);
	//printf("%.2f\t", t->price);
	//printf("%d\t",t->state);
	//printf("%s\t",t->bman);
	printf("%d",t->date);
}
void DesplayRNode(READER *t)
{
	printf("\n\t%s\t", t->rname);
	printf("%s\t", t->num);
	if(t->much==0)
          printf("\n\n        ......���û�δ��ͼ��");
     else
     {
          printf("\n\n        -������Ŀ��Ϣ��");
          printf("\n\n             ���\t����\t����\t������\t״̬\t�ѽ�ʱ��\t���޻�������");
         FILE *fp;
	BOOK *p;
	fp = fopen("E:\\book.txt", "r");
	if (!fp)
	{
		printf("�ļ�������!\n");
		return;
	}
	p = MallocBNode();
	while (fscanf(fp, "%d%s%s%s%f%d%s%d", &(p->id), p->bname, p->author, p->chuban, &(p->price),&(p->state),p->bman,&(p->date) )>0)
	{
		InsertBookNode(p);
		if(strcmp(p->bman,t->rname)==0)
          {
               printf("\n             %d\t%s\t%s\t%s\t%d\t%.1f\t",p->id,p->bname,p->author,p->chuban,p->date,p->price);
               {
                    if(p->date>30)
                      t->money=t->money+(p->date%30)*0.5;
                }
           }

		p = MallocBNode();
	}
	fclose(fp);


     }
     printf("\n\n      ���𹲼�%.1fԪ",t->money);
}

/************************************
�������ܣ�����һ���½�㣬�������ʼ��
************************************/
BOOK *MallocBNode()
{
     BOOK *p;
     int i;
     p=(BOOK*)malloc(sizeof(BOOK));
     if(p==NULL)
          return NULL;
      p->id = 0;
	for (i = 0; i<50; i++)
		p->bname[50] = '\0';
	for (i = 0; i<50 ;i++)
		p->author[50] = '\0';
	for (i = 0; i<50; i++)
		p->chuban[i] = '\0';
     for (i = 0; i<50; i++)
		p->bman[i] = '\0';
	p->price=0.0;
	p->state=1;
	p->next=NULL;//�����ڲ�����ʱֱ�Ӳ��ڱ�β
	return p;
}
READER *MallocRNode()
{
     READER *r;
     int i;
     r=(READER*)malloc(sizeof(READER));
     if(r==NULL)
          return NULL;
     for (i = 0; i<50; i++)
		r->rname[i] = '\0';
	for (i = 0; i<50; i++)
		r->num[50] = '\0';
     r->much=0;
     r->money=0.0;
     r->next=NULL;
     return r;
}

/************************************
�������ܣ��ڱ�β����һ�����
************************************/
void InsertBookNode(BOOK *t)
{
	BOOK *p;
	p = headLink;//��ͷָ��ǰ���Ѹ�ֵ
	while (p->next)
	{
		p = p->next;
	}
	p->next = t;
}
void InsertReaderNode(READER *t)
{
     READER *r;
	r=rheadlink;//��ͷָ��ǰ���Ѹ�ֵ
	while (r->next)
	{
		r=r->next;
	}
	r->next = t;
}

/************************************
�������ܣ����ļ���������
************************************/
void ReadBook()
{
	FILE *fp;
	BOOK *p;
	fp = fopen("E:\\book.txt", "r");
	if (!fp)
	{
		printf("�ļ�������!\n");
		return;
	}
	p = MallocBNode();
	while (fscanf(fp, "%d%s%s%s%f%d%s%d", &(p->id), p->bname, p->author, p->chuban, &(p->price),&(p->state),p->bman,&(p->date) )>0)
	{
		InsertBookNode(p);
		total=p->id;
		p = MallocBNode();
	}
	fclose(fp);
}
void ReadReader()
{
	FILE *fr;
	READER *r;
	fr = fopen("E:\\reader.txt", "r");
	if (!fr)
	{
		printf("�ļ�������!\n");
		return;
	}
	r= MallocRNode();//�����½ڵ㲢��ʼ��
	while (fscanf(fr, "%s%s%d", r->rname, r->num, &(r->much) )>0)
	{
		InsertReaderNode(r);
		r= MallocRNode();
	}
	fclose(fr);
}


/************************************
�������ܣ���ʼ����
************************************/
void start()//������
{
     system("cls");
     printf("\n\n");
     printf("         ***** ��ӭʹ��ͼ��ݹ���ϵͳ *****                      ^_^/* \n");
     printf("          ********************************\n\n");
     printf("\n\n");
     printf("                  173401010401\n\n");
     printf("                     ���ڷ�\n\n");
     printf("          ********************************\n");
     system("pause");
     system("cls");
     Mmenu();
}
/************************************
�������ܣ����˵�
************************************/
void Mmenu()
{
    int choise;
    printf("\n\n");
    printf("          ****************************************************************\n");
    printf("          ----------------------------------------------------------------\n\n\n");
    printf("                                      [ϵͳ����]\n\n");
    printf("                                   ---1.��ѯ����---\n\n");
    printf("                                   ---2.�û���Ϣ---\n\n");
    printf("                                   ---3.¼������---\n\n");
    printf("                                   ---4.�˳�ϵͳ---\n\n");
    printf("          =================================================================\n\n\n");
    printf("          ��ѡ����Ҫ���еĲ������:");
    scanf("%d",&choise);
    system("cls");
    switch(choise)
    {
         case 1:chaxun();break;
         case 2:yonghu();break;
         case 3:luru();break;
         case 4:start();break;
    }
}


/************************************
�������ܣ���ѯ����
************************************/
void chaxun()
{
     BOOK *p;
     p=headLink->next;
     int k,x,bookid;
     char bookname[50],authorname[50],publicname[50];
     printf("\n          ����ѯ���ġ�----------------------------------------------------------------\n\n\n");
     printf("          ------��ѡ���ѯ��ʽ:\n\n");
     printf("                                   ---1.��Ų�ѯ---\n\n");
     printf("                                   ---2.������ѯ---\n\n");
     printf("                                   ---3.���߲�ѯ---\n\n");
     printf("                                   ---4.�������ѯ---\n\n");
     printf("          -�����ѯ��ʽ���: ");scanf("%d",&k);
     if(k==1)
     {
          printf("\n\n\n          -�������:");scanf("%d",&bookid);
          printf("\n\t���\t����\t����\t������\t���\n");//���޻�������\t�Ƿ񱻽���\t������\t���ʱ��
          while(p!=NULL&&bookid!=p->id)
          {
               p=p->next;
          }
          if(!p)
          {
               printf("\n\n\n\n          \nû�д���ţ�\n                                 ....�����������");
               system("pause");
               system("cls");
               chaxun();

          }
          else
          {
               DesplayBNode(p);
          }
     }
     if(k==2)
     {
          int t=0;
          printf("\n\n\n          -��������:");scanf("%s",bookname);
          printf("\n\t���\t����\t����\t������\t���\n");//���޻�������\t�Ƿ񱻽���\t������\t���ʱ��
          while(p!=NULL)
          {
               if(!strcmp(bookname,p->bname))
               {
                    t++;
                    DesplayBNode(p);

               }
               p=p->next;
          }
          if(t==0)
          {
               printf("\n\n\n\n          \nû�д�������\n                                 ....�����������");
               system("pause");
               system("cls");
               chaxun();
          }
     }
     if(k==3)
     {
          int t=0;
          printf("\n\n\n          -��������:");scanf("%s",authorname);
          printf("\n\t���\t����\t����\t������\t���\n");//���޻�������\t�Ƿ񱻽���\t������\t���ʱ��
          while(p!=NULL)
          {
               if(!strcmp(authorname,p->author))
               {
                    t++;
                    DesplayBNode(p);

               }
               p=p->next;
          }
          if(t==0)
          {
               printf("\n\n\n\n          \nû�д����ߣ�\n                                 ....�����������");
               system("pause");
               system("cls");
               chaxun();
          }
     }
     if(k==4)
     {
          int t=0;
          printf("\n\n\n          -���������:");
          scanf("%s",publicname);
          printf("\n\t���\t����\t����\t������\t���\n");//���޻�������\t�Ƿ񱻽���\t������\t���ʱ��
          while(p!=NULL)
          {
               if(!strcmp(publicname,p->chuban))
               {
                    t++;
                    DesplayBNode(p);

               }
               p=p->next;
          }
          if(t==0)
          {
               printf("\n\n\n\n          \nû�д˳����磡\n                                 ....�����������");
               system("pause");
               system("cls");
               chaxun();
          }
     }
     printf("\n          =================================================================\n\n");
     printf("          #�Ƿ����# ��������� ��1.�ǡ�or��0.��:");scanf("%d",&x);
     if(x==0)
     {
          printf("          ���������˵���");
          system("pause");
          system("cls");
          Mmenu();
     }

     if(x==1)
          {
               printf("          �����Ĳ�����");
               Borrow();
          }
}
void Borrow()
{
     READER *r;
     r=rheadlink->next;
     char num[20],name[50];
     int n,i;
     printf("\n          =================================================================\n\n");
     printf("            -����������ѧ�ź�����-");scanf("%s%s",num,name);
     while(r!=NULL&&strcmp(num,r->num)!=0)
          {
               r=r->next;
          }
     if(!r)
        {
           printf("\n\n          -��ϵͳ������δ�ڱ�ͼ����޽��ļ�¼");
           printf("\n\n                                            ��ע��������Ϣ-");
           printf("          ��ע�����û���");
          system("pause");
          system("cls");
          tianjia();
          system("pause");
          system("cls");
          jie();
           printf("\n\n          -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n\n");
        }
     else
     {
          jie();
     }

}
void jie()
{

     char num[20],name[50];
     int n,i;
     printf("            -����������ѧ�š������ͽ�������-\n\n");scanf("%s%s%d",num,name,&n);

     FILE *fr;
     READER *r;
     fr=fopen("E:\\reader.txt","r");
     if (!fr)
	{
		printf("�ļ�������!\n");
		return;
	}
	r = MallocRNode();//�����½ڵ㲢��ʼ��
	while (fscanf(fr, "%s%s%d%.1f", r->rname, r->num, &(r->much),&(r->money) )>0)
	{
		InsertReaderNode(r);//�ڱ�λ����һ���ڵ�
		if(strcmp(r->num,num)==0)//��������ĵ�������������ѧ����ͬ
          {
               n=n+r->much;
               break;
          }
		r= MallocRNode();
	}
	fclose(fr);
	printf("            -��������Ҫ���ĵ����-\n");
	int m;
	scanf("%d",&m);
	printf("\n\n           ���ĳɹ���");

}


/************************************
�������ܣ��û���ѯ
************************************/
void yonghu()
{
     READER *r;
     r=rheadlink->next;
     int k,x;
     char rnum[20];
     printf("\n          ���û���Ϣ��----------------------------------------------------------------\n\n\n");
     printf("          ------����������ѧ��:\n\n");scanf("%s",rnum);
     printf("\n\n");
     while(r!=NULL&&strcmp(rnum,r->num)!=0)
          {
               r=r->next;
          }
          if(!r)
          {
               printf("\n\n\n\n          \n����δע�ᣡ\n                                 ....�Ƿ�ע��");
               printf("\n\n               ���������ѡ�� ��1.�ǡ�or��0.��");scanf("%d",&k);
               if(k==0)
               {
                    printf("          ���������˵���");
                    system("pause");
                    system("cls");
                    Mmenu();
               }
               if(k==1)
               {
                    printf("          ��ע�����û���");
                    system("pause");
                    system("cls");
                    tianjia();
                    system("pause");
                    system("cls");
                    Mmenu();
               }

          }
     else
     {
          DesplayRNode(r);
     }


}
void tianjia()
{
     ReadReader();
     READER *r;
     r=MallocRNode();
     GetReader(r);
     printf("\n\n           ע����ɣ�");
}
void GetReader(READER *r)
{
     printf("         -������������");scanf("%s",r->rname);
     printf("         -������ѧ�ţ�");scanf("%s",r->num);
     r->much=0;
     FILE *fr;
     fr=fopen("E:\\reader.txt","a");
     fprintf(fr,"\n%s\t%s\t%d\t%.1f\t",r->rname,r->num,r->much);
     fclose(fr);
}
void rbook(char name[50])
{
     FILE *fp;
	BOOK *p;
	fp = fopen("E:\\book.txt", "r");
	if (!fp)
	{
		printf("�ļ�������!\n");
		return;
	}
	p = MallocBNode();
	while (fscanf(fp, "%d%s%s%s%f%d%s%d", &(p->id), p->bname, p->author, p->chuban, &(p->price),&(p->state),p->bman,&(p->date) )>0)
	{
		InsertBookNode(p);
		if(strcmp(p->bman,name)==0)
               printf("\n             %d\t%s\t%s\t%s\t%.1f\t",p->id,p->bname,p->author,p->chuban,p->price);
		p = MallocBNode();
	}
	fclose(fp);

}



/************************************
�������ܣ�����¼��
************************************/
void luru()
{
     ReadBook();
     int x;
     BOOK *p;
     printf("\n          ��¼�����顿----------------------------------------------------------------\n\n\n");
     p=MallocBNode();
     GetBoook(p);
     InsertBookNode(p);
     printf("\n\n           ¼��ɹ���");
     printf("\n\n             -�Ƿ����¼��ͼ�� ��������š�1.�ǡ�or��0.�񡿣�");scanf("%d",&x);
     if(x==0)
     {
          printf("          ���������˵���");
          system("pause");
          system("cls");
          Mmenu();
     }
     if(x==1)
     {
          printf("          ������������");
          system("pause");
          system("cls");
          luru();
     }
}
void GetBoook(BOOK *p)
{
     ReadBook();

     printf("         -������������");scanf("%s",p->bname);
     printf("         -���������ߣ�");scanf("%s",p->author);
     printf("         -����������磺");scanf("%s",p->chuban);
     p->price=0.5;
     p->state=1;
     p->id=total+1;
     strcpy(p->bman,"nobody");
     p->date=0;
     FILE *fp;
     fp=fopen("E:\\book.txt","a");
     fprintf(fp,"\n%d\t%s\t%s\t%s\t%.1f\t%d\t%s\t%d",p->id,p->bname,p->author,p->chuban,p->price,p->state,p->bman,p->date);
     fclose(fp);

}

int main()
{
   CreateHeadBook();//���������ͷ
   CreateHeadReader();
   ReadBook();
   ReadReader();
   start();

}
