#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int questionNum;//题目数量
int symbolNum;//运算符种类数
char symbolType[5];//运算符种类
int maxNum;//数字最大值
int brackets;//是否有括号
int decimal;//是否有小数
int outputMode;//用户选择输出方式
float number[5];//数字
char symbol[4];//运算符
int bracketsPosition;//括号位置
void getNumber()//随机数字
{
    for (int i=0;i<5;i++)
    {
        if(decimal==0)//随机整数
        {
            number[i]=rand()%(maxNum+1);
        }
        else//随机小数
        {
            number[i]=rand()%maxNum;
            number[i]=number[i]+rand()%100*0.01;
        }
    }
}
void getSymbol()//随机符号
{
    for (int i=0;i<4;i++)
    {
        symbol[i]=symbolType[rand()%symbolNum];
    }
}
void outputScreen()//直接在屏幕打印
{
    if(decimal==1)//整数
    {
        if(brackets==1)//无括号
        {
            printf("                 ");
            printf("%.0f%c%.0f%c%.0f%c%.0f%c%.0f=\n",number[0],symbol[0],number[1],symbol[1],number[2],symbol[2],number[3],symbol[3],number[4]);
        }
        if(brackets==2)//有括号
        {
            bracketsPosition=rand()%4;
            if(bracketsPosition==0)//一二数间括号
            {
                printf("                 ");
                printf("（%.0f%c%.0f）%c%.0f%c%.0f%c%.0f=\n",number[0],symbol[0],number[1],symbol[1],number[2],symbol[2],number[3],symbol[3],number[4]);
            }
            if(bracketsPosition==1)//二三数间括号
            {
                printf("                 ");
                printf("%.0f%c(%.0f%c%.0f)%c%.0f%c%.0f=\n",number[0],symbol[0],number[1],symbol[1],number[2],symbol[2],number[3],symbol[3],number[4]);
            }
            if(bracketsPosition==2)//三四数间括号
            {
                printf("                 ");
                printf("%.0f%c%.0f%c(%.0f%c%.0f)%c%.0f=\n",number[0],symbol[0],number[1],symbol[1],number[2],symbol[2],number[3],symbol[3],number[4]);
            }
            if(bracketsPosition==3)//四五数间括号
            {
                printf("                 ");
                printf("%.0f%c%.0f%c%.0f%c(%.0f%c%.0f)=\n",number[0],symbol[0],number[1],symbol[1],number[2],symbol[2],number[3],symbol[3],number[4]);
            }
        }

    }
    if(decimal==2)//小数
    {
        if(brackets==1)//无括号
        {
            printf("                 ");
            printf("%.2f%c%.2f%c%.2f%c%.2f%c%.2f=\n",number[0],symbol[0],number[1],symbol[1],number[2],symbol[2],number[3],symbol[3],number[4]);
        }
        if(brackets==2)//有括号
        {
            printf("                 ");
            bracketsPosition=rand()%4;
        if(bracketsPosition==0)//一二数间括号
        {
            printf("                 ");
            printf("（%.2f%c%.2f）%c%.2f%c%.2f%c%.2f=\n",number[0],symbol[0],number[1],symbol[1],number[2],symbol[2],number[3],symbol[3],number[4]);
        }
        if(bracketsPosition==1)//二三数间括号
        {
            printf("                 ");
            printf("%.2f%c(%.2f%c%.2f)%c%.2f%c%.2f=\n",number[0],symbol[0],number[1],symbol[1],number[2],symbol[2],number[3],symbol[3],number[4]);
        }
        if(bracketsPosition==2)//三四数间括号
        {
            printf("                 ");
            printf("%.2f%c%.2f%c(%.2f%c%.2f)%c%.2f=\n",number[0],symbol[0],number[1],symbol[1],number[2],symbol[2],number[3],symbol[3],number[4]);
        }
        if(bracketsPosition==3)//四五数间括号
        {
            printf("                 ");
            printf("%.2f%c%.2f%c%.2f%c(%.2f%c%.2f)=\n",number[0],symbol[0],number[1],symbol[1],number[2],symbol[2],number[3],symbol[3],number[4]);
        }
        }
    }
}

int main()
{
    printf(" -------------------------------------------------\n");
    printf("                 四则运算生成程序                 \n");
    printf(" 请设置题目数量:\n");
    printf(" -------------------------------------------------\n");
    printf(" ");
    scanf("%d",&questionNum);
    printf(" -------------------------------------------------\n");
    printf(" 请设置运算符种类数:1.一种 2.二种 3.三种 4.四种  \n");
    printf(" -------------------------------------------------\n");
    printf(" ");
    scanf("%d",&symbolNum);
    printf(" -------------------------------------------------\n");
    printf(" 请连续输入使用的运算符：直接输入+-*/\n");
    printf(" -------------------------------------------------\n");
    printf(" ");
    scanf("%s",symbolType);
    printf(" 请设置单个数字的最大数值：\n");
    printf(" -------------------------------------------------\n");
    printf(" ");
    scanf("%d",&maxNum);
    printf(" -------------------------------------------------\n");
    printf(" 请选择是否有括号：1.没有 2.有\n");
    printf(" -------------------------------------------------\n");
    printf(" ");
    scanf("%d",&brackets);
    printf(" -------------------------------------------------\n");
    printf(" 请选择是否有小数：1.没有 2.有\n");
    printf(" -------------------------------------------------\n");
    printf(" ");
    scanf("%d",&decimal);
    printf(" -------------------------------------------------\n");
    printf(" 请选择输出方式：1.直接打印到屏幕 2.输出到文件\n");
    printf(" -------------------------------------------------\n");
    printf(" ");
    scanf("%d",&outputMode);
    printf(" -------------------------------------------------\n");
    if(outputMode==1)
    {
        printf(" 生成算式如下\n");
    }
    if(outputMode==2)
    {
        printf(" 生成文件成功\n");
    }
    srand((int)time(0));//随机数不同
    FILE *fp;
    fp=fopen("四则运算.txt","w");//文件写操作
    for(int t=0;t<questionNum;t++)
    {
        getNumber();//随机数字
        getSymbol();//随机符号
        for(int i=0;i<4;i++)
        {
            if((symbol[i]=='/')&&(number[i+1]==0))//除数不为0
            {
                number[i+1]++;
            }
        }
        if(outputMode==1)//输出到屏幕
        {
            outputScreen();
        }
        if(outputMode==2)//输出到文件
        {
            if(decimal==1)//整数
            {
                if(brackets==1)//无括号
                {
                    fprintf(fp,"%.0f%c%.0f%c%.0f%c%.0f%c%.0f=\n",number[0],symbol[0],number[1],symbol[1],number[2],symbol[2],number[3],symbol[3],number[4]);
                }
                if(brackets==2)//有括号
                {
                    bracketsPosition=rand()%4;
                    if(bracketsPosition==0)//一二数间括号
                    {
                        fprintf(fp,"（%.0f%c%.0f）%c%.0f%c%.0f%c%.0f=\n",number[0],symbol[0],number[1],symbol[1],number[2],symbol[2],number[3],symbol[3],number[4]);
                    }
                    if(bracketsPosition==1)//二三数间括号
                    {
                        fprintf(fp,"%.0f%c(%.0f%c%.0f)%c%.0f%c%.0f=\n",number[0],symbol[0],number[1],symbol[1],number[2],symbol[2],number[3],symbol[3],number[4]);
                    }
                    if(bracketsPosition==2)//三四数间括号
                    {
                        fprintf(fp,"%.0f%c%.0f%c(%.0f%c%.0f)%c%.0f=\n",number[0],symbol[0],number[1],symbol[1],number[2],symbol[2],number[3],symbol[3],number[4]);
                    }
                    if(bracketsPosition==2)//四五数间括号
                    {
                        fprintf(fp,"%.0f%c%.0f%c%.0f%c(%.0f%c%.0f)=\n",number[0],symbol[0],number[1],symbol[1],number[2],symbol[2],number[3],symbol[3],number[4]);
                    }
                }
            }
            if(decimal==2)//小数
            {
                if(brackets==1)//无括号
                {
                    fprintf(fp,"%.2f%c%.2f%c%.2f%c%.2f%c%.2f=\n",number[0],symbol[0],number[1],symbol[1],number[2],symbol[2],number[3],symbol[3],number[4]);
                }
                if(brackets==2)//有括号
                {
                    bracketsPosition=rand()%4;
                    if(bracketsPosition==0)//一二数间括号
                    {
                        fprintf(fp,"（%.2f%c%.2f）%c%.2f%c%.2f%c%.2f=\n",number[0],symbol[0],number[1],symbol[1],number[2],symbol[2],number[3],symbol[3],number[4]);
                    }
                    if(bracketsPosition==1)//二三数间括号
                    {
                        fprintf(fp,"%.2f%c(%.2f%c%.2f)%c%.2f%c%.2f=\n",number[0],symbol[0],number[1],symbol[1],number[2],symbol[2],number[3],symbol[3],number[4]);
                    }
                    if(bracketsPosition==2)//三四数间括号
                    {
                        fprintf(fp,"%.2f%c%.2f%c(%.2f%c%.2f)%c%.2f=\n",number[0],symbol[0],number[1],symbol[1],number[2],symbol[2],number[3],symbol[3],number[4]);
                    }
                    if(bracketsPosition==3)//四五数间括号
                    {
                        fprintf(fp,"%.2f%c%.2f%c%.2f%c(%.2f%c%.2f)=\n",number[0],symbol[0],number[1],symbol[1],number[2],symbol[2],number[3],symbol[3],number[4]);
                    }
                }
            }
        }

    }
    fclose(fp);//关闭文件
    printf(" -------------------------------------------------\n");
    return 0;
}

