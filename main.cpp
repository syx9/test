#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<conio.h>
#include<math.h>
using namespace std;

typedef struct BOOK//图书结构体
{
     float price;//超限基本罚金
     int state,date,id;//状态、借出天数
     char bname[50],author[50],chuban[50],bman[50];//书名、作者、出版社、书号、借阅人
     struct BOOK *next;
}BOOK;
typedef struct READER//读者结构体
{
     BOOK book[15];//所借书目
     char rname[50],num[20];//姓名、学号
     int much;//所借书数
     float money;
     struct READER *next;
}READERD;
BOOK *headLink;//链表表头指针，适用全局；
READER *rheadlink;
int total;
/**********************************************************
                     所有函数声明
**********************************************************/
void CreateHeadBook();//建立链表表头
void CreateHeadReader();//建立链表表头
BOOK *MallocBNode();//申请新结点并初始化
READER *MallocRNode();//申请新结点并初始化
void InsertBookNode(BOOK *t);//在表尾插入一个结点
void InsertReaderNode(READER *t);
void ReadBook();//从文件读入数据
void ReadReader();
void DesplayBNode(BOOK *t);//输出一个结点的信息
void DesplayRNode(READER *t);
void Mmenu();//主菜单
void chaxun();//查询
void Borrow();//借阅
void jie();
void yonghu();//用户
void rbook(char name[50]);//输出读者的图书
void tianjia();//添加新用户
void GetReader(READER *r);
void luru();
void GetBoook(BOOK *p);
void InsertoneReader(char name[50],char num[20],int n);//添加一个读者
void yonghu();
void luru();

/************************************
函数功能：建立链表表头
************************************/
void CreateHeadBook()
{
	BOOK *p;
	p = (BOOK*)malloc(sizeof(BOOK));
	headLink = p;//给表头指针赋初值
	p->next = NULL;
}
void CreateHeadReader()
{
     READER *p;
	p = (READER*)malloc(sizeof(READER));
	rheadlink=p;//给表头指针赋初值
	p->next = NULL;
}


/************************************
函数功能：输出一个结点的信息
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
          printf("\n\n        ......此用户未借图书");
     else
     {
          printf("\n\n        -所借书目信息：");
          printf("\n\n             书号\t书名\t作者\t出版社\t状态\t已借时间\t超限基础罚金");
         FILE *fp;
	BOOK *p;
	fp = fopen("E:\\book.txt", "r");
	if (!fp)
	{
		printf("文件不存在!\n");
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
     printf("\n\n      罚金共计%.1f元",t->money);
}

/************************************
函数功能：申请一个新结点，并将其初始化
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
	p->next=NULL;//便于在插入结点时直接插在表尾
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
函数功能：在表尾插入一个结点
************************************/
void InsertBookNode(BOOK *t)
{
	BOOK *p;
	p = headLink;//表头指针前面已赋值
	while (p->next)
	{
		p = p->next;
	}
	p->next = t;
}
void InsertReaderNode(READER *t)
{
     READER *r;
	r=rheadlink;//表头指针前面已赋值
	while (r->next)
	{
		r=r->next;
	}
	r->next = t;
}

/************************************
函数功能：从文件读入数据
************************************/
void ReadBook()
{
	FILE *fp;
	BOOK *p;
	fp = fopen("E:\\book.txt", "r");
	if (!fp)
	{
		printf("文件不存在!\n");
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
		printf("文件不存在!\n");
		return;
	}
	r= MallocRNode();//申请新节点并初始化
	while (fscanf(fr, "%s%s%d", r->rname, r->num, &(r->much) )>0)
	{
		InsertReaderNode(r);
		r= MallocRNode();
	}
	fclose(fr);
}


/************************************
函数功能：初始界面
************************************/
void start()//主界面
{
     system("cls");
     printf("\n\n");
     printf("         ***** 欢迎使用图书馆管理系统 *****                      ^_^/* \n");
     printf("          ********************************\n\n");
     printf("\n\n");
     printf("                  173401010401\n\n");
     printf("                     崔钰凡\n\n");
     printf("          ********************************\n");
     system("pause");
     system("cls");
     Mmenu();
}
/************************************
函数功能：主菜单
************************************/
void Mmenu()
{
    int choise;
    printf("\n\n");
    printf("          ****************************************************************\n");
    printf("          ----------------------------------------------------------------\n\n\n");
    printf("                                      [系统功能]\n\n");
    printf("                                   ---1.查询借阅---\n\n");
    printf("                                   ---2.用户信息---\n\n");
    printf("                                   ---3.录入新书---\n\n");
    printf("                                   ---4.退出系统---\n\n");
    printf("          =================================================================\n\n\n");
    printf("          请选择您要进行的操作序号:");
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
函数功能：查询借阅
************************************/
void chaxun()
{
     BOOK *p;
     p=headLink->next;
     int k,x,bookid;
     char bookname[50],authorname[50],publicname[50];
     printf("\n          【查询借阅】----------------------------------------------------------------\n\n\n");
     printf("          ------请选择查询方式:\n\n");
     printf("                                   ---1.书号查询---\n\n");
     printf("                                   ---2.书名查询---\n\n");
     printf("                                   ---3.作者查询---\n\n");
     printf("                                   ---4.出版社查询---\n\n");
     printf("          -输入查询方式序号: ");scanf("%d",&k);
     if(k==1)
     {
          printf("\n\n\n          -输入书号:");scanf("%d",&bookid);
          printf("\n\t书号\t书名\t作者\t出版社\t库存\n");//超限基础罚款\t是否被借阅\t借阅人\t借出时间
          while(p!=NULL&&bookid!=p->id)
          {
               p=p->next;
          }
          if(!p)
          {
               printf("\n\n\n\n          \n没有此书号！\n                                 ....按任意键返回");
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
          printf("\n\n\n          -输入书名:");scanf("%s",bookname);
          printf("\n\t书号\t书名\t作者\t出版社\t库存\n");//超限基础罚款\t是否被借阅\t借阅人\t借出时间
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
               printf("\n\n\n\n          \n没有此书名！\n                                 ....按任意键返回");
               system("pause");
               system("cls");
               chaxun();
          }
     }
     if(k==3)
     {
          int t=0;
          printf("\n\n\n          -输入作者:");scanf("%s",authorname);
          printf("\n\t书号\t书名\t作者\t出版社\t库存\n");//超限基础罚款\t是否被借阅\t借阅人\t借出时间
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
               printf("\n\n\n\n          \n没有此作者！\n                                 ....按任意键返回");
               system("pause");
               system("cls");
               chaxun();
          }
     }
     if(k==4)
     {
          int t=0;
          printf("\n\n\n          -输入出版社:");
          scanf("%s",publicname);
          printf("\n\t书号\t书名\t作者\t出版社\t库存\n");//超限基础罚款\t是否被借阅\t借阅人\t借出时间
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
               printf("\n\n\n\n          \n没有此出版社！\n                                 ....按任意键返回");
               system("pause");
               system("cls");
               chaxun();
          }
     }
     printf("\n          =================================================================\n\n");
     printf("          #是否借阅# 请输入序号 【1.是】or【0.否】:");scanf("%d",&x);
     if(x==0)
     {
          printf("          【返回主菜单】");
          system("pause");
          system("cls");
          Mmenu();
     }

     if(x==1)
          {
               printf("          【借阅操作】");
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
     printf("            -请输入您的学号和姓名-");scanf("%s%s",num,name);
     while(r!=NULL&&strcmp(num,r->num)!=0)
          {
               r=r->next;
          }
     if(!r)
        {
           printf("\n\n          -经系统鉴定您未在本图书馆无借阅记录");
           printf("\n\n                                            将注册您的信息-");
           printf("          【注册新用户】");
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
     printf("            -请输入您的学号、姓名和借阅数量-\n\n");scanf("%s%s%d",num,name,&n);

     FILE *fr;
     READER *r;
     fr=fopen("E:\\reader.txt","r");
     if (!fr)
	{
		printf("文件不存在!\n");
		return;
	}
	r = MallocRNode();//申请新节点并初始化
	while (fscanf(fr, "%s%s%d%.1f", r->rname, r->num, &(r->much),&(r->money) )>0)
	{
		InsertReaderNode(r);//在表位插入一个节点
		if(strcmp(r->num,num)==0)//如果读者文档中有人与输入学号相同
          {
               n=n+r->much;
               break;
          }
		r= MallocRNode();
	}
	fclose(fr);
	printf("            -请输入您要借阅的书号-\n");
	int m;
	scanf("%d",&m);
	printf("\n\n           借阅成功！");

}


/************************************
函数功能：用户查询
************************************/
void yonghu()
{
     READER *r;
     r=rheadlink->next;
     int k,x;
     char rnum[20];
     printf("\n          【用户信息】----------------------------------------------------------------\n\n\n");
     printf("          ------请输入您的学号:\n\n");scanf("%s",rnum);
     printf("\n\n");
     while(r!=NULL&&strcmp(rnum,r->num)!=0)
          {
               r=r->next;
          }
          if(!r)
          {
               printf("\n\n\n\n          \n此人未注册！\n                                 ....是否注册");
               printf("\n\n               请输入序号选择 【1.是】or【0.否】");scanf("%d",&k);
               if(k==0)
               {
                    printf("          【返回主菜单】");
                    system("pause");
                    system("cls");
                    Mmenu();
               }
               if(k==1)
               {
                    printf("          【注册新用户】");
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
     printf("\n\n           注册完成！");
}
void GetReader(READER *r)
{
     printf("         -请输入姓名：");scanf("%s",r->rname);
     printf("         -请输入学号：");scanf("%s",r->num);
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
		printf("文件不存在!\n");
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
函数功能：新书录入
************************************/
void luru()
{
     ReadBook();
     int x;
     BOOK *p;
     printf("\n          【录入新书】----------------------------------------------------------------\n\n\n");
     p=MallocBNode();
     GetBoook(p);
     InsertBookNode(p);
     printf("\n\n           录入成功！");
     printf("\n\n             -是否继续录入图书 请输入序号【1.是】or【0.否】：");scanf("%d",&x);
     if(x==0)
     {
          printf("          【返回主菜单】");
          system("pause");
          system("cls");
          Mmenu();
     }
     if(x==1)
     {
          printf("          【继续操作】");
          system("pause");
          system("cls");
          luru();
     }
}
void GetBoook(BOOK *p)
{
     ReadBook();

     printf("         -请输入书名：");scanf("%s",p->bname);
     printf("         -请输入作者：");scanf("%s",p->author);
     printf("         -请输入出版社：");scanf("%s",p->chuban);
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
   CreateHeadBook();//建立链表表头
   CreateHeadReader();
   ReadBook();
   ReadReader();
   start();

}
