#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct//分别为顾客、订单和商品定义结构体
{
	int c_custkey;    	   
	char c_mkgsegment[20]; //市场部门
}customer;				   

typedef struct
{
	int o_orderkey;    	 
	int o_custkey;    	 
	char o_orderdate[10];//订货日期
}orders;				 

typedef struct
{
	int l_orderkey;
	double l_extendedprice;//额外价格
	char l_shipdate[10];//发货日期
}lineitem; 

typedef struct//定义查询结果的结构体
{
	int l_orderkey;//订单号
	char o_orderdate[10];//订货日期
	double l_extendedprice;//额外价格
}select_result;


customer * read_customer_txt() //读取顾客信息
{
	FILE * fp;
	customer *a=NULL;
	a = (customer *)malloc(101*sizeof(customer));
	int i=0;
	char b;
	fp = fopen("customer.txt","r");
	if(NULL==fp)
	{
		printf("cannot open customer.txt!");
		return NULL;
	}
	while(!feof(fp))
	{

		fscanf(fp,"%d%c%s",&a[i].c_custkey,&b,&a[i].c_mkgsegment);

		i++;
	}
	fclose(fp);
	return a;
}
orders * read_orders_txt()//读取订单信息
{
	int i =0;
	orders * a=NULL;
	a = (orders * )malloc(4001*sizeof(orders));
	char b,c;
	long long d;
	FILE *fp;
	fp = fopen("orders.txt","r");
	if(fp == NULL)
	{
		printf("cannot open orders.txt!");
		return NULL;
	}
	while(!feof(fp))
	{

		fscanf(fp,"%d%c%lld%c%s",&a[i].o_orderkey,&b,&d,&c,&a[i].o_orderdate);
		a[i].o_custkey=d%100;

		i++;
	}
	fclose(fp);
	return a;
}

lineitem * read_lineitem_txt()//读取商品信息
{
	FILE * fp;
	lineitem * a=NULL;
	a = (lineitem *)malloc(1001*sizeof(lineitem));
	int i=0;
	char b,c;
	fp = fopen("lineitem.txt","r");
	if(fp==NULL)
	{
		printf("cannot open lineitem.txt!");
		return NULL;
	}
	while(!feof(fp))
	{

		fscanf(fp,"%d%c%lf%c%s",&a[i].l_orderkey,&c,&a[i].l_extendedprice,&b,&a[i].l_shipdate);

		i++;
	}
	fclose(fp);
	return a;
}

select_result * Select(customer * cus,orders * ord,lineitem * item,char * order_date,char * ship_date,char * mktsegment)//进行选择
{
    select_result * re=NULL;
    re=(select_result *)malloc(4001*sizeof(select_result));
    int i,j,k;
    int n=0;
    for(i=0;i<100;i++)
    {
        if(strcmp(cus[i].c_mkgsegment,mktsegment)==0)
        {
            for(j=0;j<4000;j++)
            {
                if(cus[i].c_custkey==ord[j].o_custkey&&strcmp(ord[j].o_orderdate,order_date)<0)
                {
                    for(k=0;k<1000;k++)
                    {
                        if(ord[j].o_orderkey==item[k].l_orderkey&&strcmp(item[k].l_shipdate,ship_date)>0)
                        {
                            re[n].l_extendedprice=item[k].l_extendedprice;
                            strcpy(re[n].o_orderdate,ord[j].o_orderdate);
                            re[n].l_orderkey=item[k].l_orderkey;
                        
                            if(n>0 && re[n-1].l_orderkey==re[n].l_orderkey)
                            {
                                re[n-1].l_extendedprice+=re[n].l_extendedprice;
                                n--;
                            }
                            n++;
                        }
                    }
                }
            }
        }
    }
    return re;
}



int change_argv_to_number(char s[])//将命令行里读入的数字字符串转化为整形数字
{
	int i=0;
	int number=0;
	while(s[i]!='\0')
	{
		if(i==0)
			number = (s[i]-48);
		else
			number = number*10 + (s[i]-48);

		i++;
	}
	return number;
}

int main(int argc,char * argv[])//argc表示输入内容的总个数，argv[]内保存着输入的内容
{
	int i,j;
	int num;

	int limit=3;
	char order_date[10];
	char ship_date[10];
	char mktsegment[20];
	select_result *result=NULL;
	customer * cus = NULL;//指向客户表的指针
	orders * ord = NULL;//指向订单表的指针
	lineitem * item = NULL;//指向 产品表的指针
	cus = read_customer_txt();//读取customer.txt的内容 ，导入客户表
	ord = read_orders_txt();//读取orders.txt的内容 ，导入订单表
	item = read_lineitem_txt();//读取lineitem.txt的内容 ，导入产品表
	num = change_argv_to_number(argv[4]);//总共计算的次数

	for(i=0;num>0;num--,i=i+4)
	{

        limit = change_argv_to_number(argv[8+i]);
	result=Select(cus,ord,item,argv[6+i],argv[7+i],argv[5+i]);
	printf("l_orderkey|o_orderdate|revenue\n");
		for(j=0;j<limit;j++)
		{
			if(result[j].l_extendedprice==0||result[j].l_orderkey>4000)
			{
				printf("null      |null       |null   \n");
			}
			else
               	 	{
			printf("%-10d|%-11s|	 %-20.2lf\n",result[j].l_orderkey,result[j].o_orderdate,result[j].l_extendedprice);		
                	}
		}
	free(result);
	result = NULL;
	}
	return 0;
}
