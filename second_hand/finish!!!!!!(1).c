//所引用的头文件
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
//卖家结构体
typedef struct
   {
	   char number[20];
	   char name[20];
       char password[50];
       char telenumber[15];
       char name_of_goods[5][100];
       struct seller *next;
   }seller;
seller *shead;//头指针
//买家结构体
typedef struct
    {
        char name[20];
        char number[20];
        char password[50];
        struct buyer *next;
    }buyer;
buyer *bhead;//头指针
//商品结构体
typedef struct
   {
       char name[100];
       char label[50];
       char wanted;
       char tele_of_seller[15];
       int price;
       struct goods *next;
    }goods;
goods *ghead;//头指针
//全局变量
FILE *fp1, *fp2, *fp3;
seller *sp1, *sp2;
buyer *bp1, *bp2;
goods *gp1, *gp2;
//函数声明
int chushihua();
void buy();
void sell();
void choose_of_sellers();
void choose_of_buyers();
void registerbuyer();
void registerseller();
int loginbuyer();
int loginseller();
void add_goods_of_seller();
void revise_of_sellers();
void revise_of_buyers();
void search_of_sellers();
void search_of_buyers();
int delete_of_goods();
void change_info_of_goods( int sh );
void fprintf_of_sellers();
void fprintf_of_buyers();
void fprintf_of_goods();
//主函数部分
int main()
{
    char ch;
    chushihua();
    while(1)
    {
        printf("\n\t\t\t**********************欢迎使用西电二手交易系统**********************\n");
        printf("\t\t\t                          1.我是买家                        \n");
        printf("\t\t\t                          2.我是卖家                          \n");
        printf("\t\t\t                          0.退出                            \n");
        printf("\t\t\t**************************************************************\n");
        printf("请选择（1/2/0）:\n");
        ch = getche();
        switch( ch )
        {
        case'1':buy();//调用买家模块
                fprintf_of_buyers();//退出时把新信息写入buyers.txt文本
                fprintf_of_goods();//退出时把新信息写入goods.txt文本
                continue;
        case'2':sell();//调用卖家模块
                fprintf_of_sellers();//退出时把新信息写入sellers.txt文本
                fprintf_of_goods();//退出时把新信息写入goods.txt文本
                continue;
        default:printf("再见！请按任意键退出。\n");
                return 0;
        }
    }
}
void buy()//买家账号管理
{
	    printf("\n\t\t\t**********************买家系统账号界面：**********************\n");
        printf("\t\t\t                          1.注册                       \n");
        printf("\t\t\t                          2.登陆                          \n");
        printf("\t\t\t                          0.退出                            \n");
        printf("\t\t\t**************************************************************\n");
        int ch;
       while(1)
	    {
            printf("请选择：\n");
            scanf("%d",&ch);
            if(ch==1)
        	{
        		registerbuyer();//买家注册函数
			}
            else if (ch==2)
			{
				if(loginbuyer()==0)
					{
						choose_of_buyers();//买家系统的选择界面
						break;
					}
				else
					{
						printf("登陆失败！您的账户或者密码不匹配\n");
						continue;
					}
			}
            else
                break;
		}
}
void sell()//卖家账号管理
{
	    printf("\n\t\t\t**********************卖家系统账号界面：**********************\n");
        printf("\t\t\t                          1.注册                       \n");
        printf("\t\t\t                          2.登陆                          \n");
        printf("\t\t\t                          0.退出                            \n");
        printf("\t\t\t**************************************************************\n");
        int ch;
       while(1)
	    {
		printf("请选择：\n");
        scanf("%d",&ch);
        if(ch==1)
        	{
        		registerseller();//卖家注册函数
        		break;
			}
		else if (ch==2)
			{
				if(loginseller()==0)
					{
						choose_of_sellers();//卖家系统选择界面
						break;
					}
				else
					{
						printf("登陆失败！您的账户或者密码不匹配\n");
						continue;
					}
			}
		else
			break;
		}
}
void choose_of_sellers()//卖家功能函数选择
{
    int ch;
        while(1)
        {
            printf("\n\t\t\t**********************卖家系统：**********************\n");
            printf("\t\t\t                          1.增添                       \n");
            printf("\t\t\t                          2.修改                          \n");
            printf("\t\t\t                          3.查询                          \n");
            printf("\t\t\t                          4.删除                          \n");
            printf("\t\t\t                          0.退出                            \n");
            printf("\t\t\t**************************************************************\n");
            scanf("%d",&ch);
        	if(ch==1)
        		{
        			add_goods_of_seller();//增加商品
        			continue;
				}
			else if(ch==2)
				{
					revise_of_sellers();//修改卖家或其所卖商品的信息
                    continue;
				}
			else if( ch == 3 )
                {
                    search_of_sellers();//卖家查询自己所卖的商品
                    continue;
                }
            else if( ch == 4 )
                {
                    delete_of_goods();//删除商品
                    continue;
                }
            else
				break;
		}

}
void choose_of_buyers()//买家功能函数选择
{
		int ch;
        while(1)
        {
            printf("\n\t\t\t**********************买家系统：**********************\n");
            printf("\t\t\t                          1.查询                       \n");
            printf("\t\t\t                          2.修改                          \n");
            printf("\t\t\t                          0.退出                            \n");
            printf("\t\t\t**************************************************************\n");
            scanf("%d",&ch);
        	if(ch==1)
        		{
        			search_of_buyers();//买家查询特定标签的商品
        			continue;
				}
			else if(ch==2)
				{
					revise_of_buyers();//修改买家账号的信息
					continue;
				}
            else
				break;
		}
}
int chushihua()//从txt文本里将数据导出成为链表
{
    int i;
    fp1 = fopen("sellers.txt", "r");
    fp2 = fopen("buyers.txt", "r");
    fp3 = fopen("goods.txt", "r");
    if ( ( fp1 == NULL ) || ( fp2 == NULL ) || ( fp3 == NULL ) )
    {
        printf("未能初始化信息");
        fclose( fp1 );
        fclose( fp2 );
        fclose( fp3 );
        return 0;
    }
    else
    {
//sellers.txt
        sp1 = ( seller *)malloc( sizeof(seller) );
        shead = sp1;
         while( !feof(fp1) )
        {
            fscanf( fp1,"%s %s %s %s", sp1 -> number, sp1 -> name, sp1 -> password, sp1 ->telenumber );
            for ( i = 0; i < 5; i ++ )
                fscanf( fp1, "%s", sp1 -> name_of_goods[i] );
            sp2 = sp1;
            sp1 = ( seller *)malloc( sizeof(seller) );
            sp2 -> next = sp1;
        }
        sp2 -> next = NULL;
        sp2 = NULL;
        free( sp1 );
        sp1 = shead;
//buyers.txt
        bp1 = ( buyer *)malloc( sizeof(buyer) );
        bhead = bp1;
         while( fscanf( fp2,"%s", bp1 -> number) != EOF)
        {
            fscanf( fp2,"%s %s ", bp1 -> name, bp1 -> password );
            bp2 = bp1;
            bp1 = ( buyer *)malloc( sizeof(buyer) );
            bp2 -> next = bp1;
        }
        bp2 -> next = NULL;
        bp2 = NULL;
        free( bp1 );
        bp1 = bhead;
//goods.txt
        gp1 = ( goods *)malloc( sizeof(goods) );
        ghead = gp1;
         while( fscanf( fp3,"%s", gp1 -> name) != EOF)
        {
            fscanf( fp3,"%s %c %s %d", gp1 -> label, &(gp1 -> wanted), gp1 -> tele_of_seller, &(gp1 -> price) );
            gp2 = gp1;
            gp1 = ( goods *)malloc( sizeof(goods) );
            gp2 -> next = gp1;
        }
        gp2 -> next = NULL;
        gp2 = NULL;
        free( gp1 );
        gp1 = ghead;
    }

    fclose( fp1 );
    fclose( fp2 );
    fclose( fp3 );
    return 0;
}
void registerbuyer()//买家注册函数
{
    chushihua();
    char ch = 'y';
    bp1 = bhead;
    while( bp1 -> next != NULL )
        bp1  = bp1 -> next;
    while( tolower(ch) =='y' )
    {
        bp2 = ( struct buyer *) malloc (sizeof(buyer));
        printf("\n请按如下格式输入：\n");
        printf("姓名：");
        getchar();
        gets( bp2 -> name );
        printf("学号：");
        gets( bp2 -> number );
        printf("密码：");
        gets( bp2 -> password );
        bp2 -> next = NULL;
        printf("\n 请确认上述输入[y/Y],否则按其他任意键继续");
        ch = getche();
        if( tolower(ch) == 'y' )
        {
            bp1 -> next = bp2;
            bp1 = bp2;
            bp2 = NULL;
            fp2 = fopen("buyers.txt", "w");
            bp1 = bhead;
            while( bp1 != NULL )
            {
                fprintf( fp2,"%s %s %s ", bp1 -> number, bp1 -> name, bp1 -> password );
                fprintf( fp2, "\n");
                bp1 = bp1 -> next;
            }
            free( bp1 );
            bp1 = NULL;
            printf("\n注册信息成功！！......按任意键继续......");
            getch();
            putch( '\n' );
            break;
        }
        else
        {
            printf("\n注册失败！！！......按任意键继续......");
            getch();
            putch( '\n' );
        }

    }
        bp1 = NULL;
        fclose( fp2 );
        return 0;
}
void registerseller()//卖家注册函数
{
    chushihua();
    int i;
    char ch = 'y';
    sp1 = shead;
    while( sp1 -> next != NULL )
        sp1  = sp1 -> next;
    while( tolower(ch) =='y' )
    {
        sp2 = ( struct seller *) malloc (sizeof(seller));
        printf("\n请按如下格式输入：\n");
        printf("学号：");
        getchar();
        gets( sp2 -> number );
        printf("姓名：");
        gets( sp2 -> name );
        printf("密码：");
        gets( sp2 -> password );
        printf("手机号：");
        gets( sp2 -> telenumber );
        for ( i = 0; i < 5; i ++ )
            strcpy( sp2 -> name_of_goods[i] , "NULL" );
        sp2 -> next = NULL;
        printf("\n请确认上述输入[y/Y],否则按其他任意键继续");
        ch = getche();
        if( tolower(ch) == 'y' )
        {
            sp1 -> next = sp2;
            sp1 = sp2;
            sp2 = NULL;
            fp1 = fopen("sellers.txt", "w");
                sp1 = shead;
                while( sp1 != NULL )
                {
                    fprintf( fp1, "%s %s %s %s ", sp1 -> number, sp1 -> name, sp1 -> password, sp1 -> telenumber );
                    for ( i = 0; i < 5; i ++ )
                        fprintf( fp1, "%s ", sp1 -> name_of_goods[i] );
                    fprintf( fp1, "\n");
                    sp1 = sp1 -> next;
                }
                free( sp1 );
                fclose( fp1 );
            printf("\n注册成功！！......按任意键继续......");
            getch();
            ch = 'a';
            putch( '\n' );
        }
        else
        {
            printf("\n注册失败！！！......按任意键继续......");
            getch();
            ch = 'a';
            putch( '\n' );
        }

    }

}
int loginbuyer()//买家登陆函数
{
	chushihua();
	int count=0;char name1[20];char password1[50];
	getchar();
	printf("\n请输入您的账户名：\n");
	gets(name1);
	buyer *a=bhead;
    while( a != NULL )
        {
            if( strcmp( name1, a -> name ) == 0)
                {
                    count ++;
                    break;
                }
            else
                a = a -> next;
        }
    if(count==0)
	{
		printf("登陆失败！您的账户不存在\n");
		return 1;
	}
    printf("请输入您的密码：\n");
    scanf("%s",password1);
    if( strcmp( password1, a -> password ) == 0)
    	{
    		printf("登陆成功！\n");
    		bp1 = a;
    		return 0;
		}
	else
		{
			printf("登陆失败！您的账户与密码不匹配\n");
    		return 1;
    	}
}
int loginseller()//卖家登陆函数
{
	chushihua();
	int count=0;char name1[20];char password1[50];
	getchar();
	printf("\n请输入您的账户名：\n");
	gets(name1);
	seller *a=shead;
    while( a != NULL )
        {
            if( strcmp( name1, a -> name ) == 0)
                {
                    count ++;
                    break;
                }
            else
                a = a -> next;
        }
    if(count==0)
	{
		printf("登陆失败！您的账户不存在\n");
		return 1;
	}
    printf("请输入您的密码：\n");
    scanf("%s",password1);
    if( strcmp( password1, a -> password ) == 0)
    	{
    		printf("登陆成功！\n");
    		sp1 = a;
    		return 0;
		}
	else
		{
			printf("登陆失败！您的账户与密码不匹配\n");
    		return 1;
    	}
}
void add_goods_of_seller()//卖家添加商品
{
	int ch,i;
	FILE *fp;
	goods *gp3;
	goods *g666=ghead;
	fp = fopen("goods.txt", "a");
	gp3 = ( goods *)malloc( sizeof(goods) );
	while(1){
	printf("请输入下列商品的信息：\n");
	printf("商品的名字：\n");
	scanf("%s",gp3->name);
	printf("请选择下列标签中的一个：\n");
	printf("1.日用百货 2.电子机械 3.经史典籍\n");
	scanf("%d",&ch);
	if(ch!=1&&ch!=2&&ch!=3)
		{
			printf("输入错误 请重新输入\n");
			continue;
		}
	else
		{
			if(ch==1)
				strcpy (gp3->label,"日用百货");
			else {
			if(ch==2)
				strcpy (gp3->label,"电子机械");
			else
				strcpy (gp3->label,"经史典籍");
				}
		}
	printf("请输入商品价格\n");
	scanf("%d",&gp3->price);
	gp3->wanted='N';
	strcpy( gp3 -> tele_of_seller, sp1 -> telenumber);
	for(i=0;i<5;i++)
	 {
		 if(strcmp(sp1->name_of_goods[i],"NULL")==0)
	 		{
	 			strcpy(sp1->name_of_goods[i],gp3->name);
	 			break;
            }
	 }

	if(i==5)
	 	{
	 		printf("您该账号下拥有的商品已满" );
		 }
	else{	 
	fprintf(fp,"%s %s %c %s %d\n",gp3->name,gp3->label,gp3->wanted,gp3->tele_of_seller,gp3->price);//追加至goods.txt
	while(g666->next!=NULL)
	{
		g666=g666->next;
    }
	 g666->next=gp3;
	 gp3->next=NULL;} 
	fclose(fp);
	free(gp3); 
    break;

} 
}
void revise_of_sellers()//卖家修改商品
{

    char newnumber[20], newname[20], newpassword[50], newtelenumber[15];
    char ch;
    int i, sh;
    while(1)
    {
        printf("\n您的原始信息是：\n");
        printf(" %s %s %s %s\n", sp1 -> number, sp1 -> name, sp1 -> password, sp1 -> telenumber );
        for ( i = 0; i < 5; i ++ )
            printf( "%s ", sp1 -> name_of_goods[i] );
        printf("1.学号  2.姓名  3.密码  4.电话号码  5.商品\n");
        printf("请选择：");
        ch = getche();
        switch( ch )
        {
            case'1':printf("\n请输入新的信息（回车结束）：");
                    scanf( "%s", newnumber );
                    printf("是否确认？[y/n]");
                    ch = getche();
                    if( tolower(ch) == 'y')
                        strcpy( sp1 -> number, newnumber );
                    break;

            case'2':printf("\n请输入新的信息（回车结束）：");
                    scanf( "%s", newname );
                    printf("是否确认？[y/n]");
                    ch = getche();
                    if( tolower(ch) == 'y')
                        strcpy( sp1 -> name, newname );
                    break;

            case'3':printf("\n请输入新的信息（回车结束）：");
                    scanf( "%s", newpassword );
                    printf("是否确认？[y/n]");
                    ch = getche();
                    if( tolower(ch) == 'y')
                        strcpy( sp1 -> password, newpassword );
                    break;

            case'4':printf("\n请输入新的信息（回车结束）：");
                    scanf( "%s", newtelenumber );
                    printf("是否确认？[y/n]");
                    ch = getche();
                    if( tolower(ch) == 'y')
                    {
                        gp1 = ghead;
                        while( gp1 != NULL )
                        {
                            if( strcmp( gp1 -> tele_of_seller, sp1 -> telenumber ) == 0)
                                strcpy( gp1 -> tele_of_seller, newtelenumber );
                            gp1 = gp1 -> next;
                        }
                        strcpy( sp1 -> telenumber, newtelenumber );
                    }
                    break;
            case'5':printf("\n请选择要修改的商品编号（回车结束）：");
                    scanf( "%d", &sh );
                    change_info_of_goods( sh );
                    break;
            default: printf("\n输入错误，请重新输入：\n");
                    break;
            }
            printf("\n请您再次确认[y/n]");
            ch = getche();
            if( tolower(ch) == 'y')
            {
                printf("\n修改成功！\n");
                printf("\n您修改后的信息是：\n");
                printf("%s %s %s %s ", sp1 -> number, sp1 -> name, sp1 -> password , sp1 -> telenumber );
                for ( i = 0; i < 5; i ++ )
                    printf( "%s ", sp1 -> name_of_goods[i] );
            }
            else
            {
                printf("\n修改失败。\n");
            }
            break;
        }
}
void revise_of_buyers( )//买家修改个人信息
{

    char newnumber[20], newname[20],newpassword[50];
    char ch;
    int count = 0, i;

    while(1)
    {
        printf("\n您的原始信息是：\n");
        printf(" %s %s %s\n", bp1 -> number, bp1 -> name, bp1 -> password );
        printf("1.学号  2.姓名  3.密码  \n");
        printf("请选择：");
        ch = getche();
        switch( ch )
        {
            case'1':printf("\n请输入新的信息（回车结束）：");
                    scanf( "%s", newnumber );
                    printf("是否确认？[y/n]");
                    ch = getche();
                    if( tolower(ch) == 'y')
                        strcpy( bp1 -> number, newnumber );
                    break;
            case'2':printf("\n请输入新的信息（回车结束）：");
                    scanf( "%s", newname );
                    printf("是否确认？[y/n]");
                    ch = getche();
                    if( tolower(ch) == 'y')
                        strcpy( bp1 -> name, newname );
                    break;

            case'3':printf("\n请输入新的信息（回车结束）：");
                    scanf( "%s", newpassword );
                    printf("是否确认？[y/n]");
                    ch = getche();
                    if( tolower(ch) == 'y')
                        strcpy( bp1 -> password, newpassword );
                    break;
            default: printf("\n输入错误，请重新输入：\n");
                    break;
        }
        if( tolower(ch) == 'y')
        {
            printf("\n修改成功！\n");
            printf("\n您修改后的信息是：\n");
            printf(" %s %s %s", bp1 -> number, bp1 -> name, bp1 -> password );
        }
        else
        {
            printf("\n修改失败。\n");
        }
        break;
    }
}
void search_of_sellers()//卖家查询自己所卖的商品
{
	int flag=0;
	char *s0=sp1->name_of_goods[0];
	char *s1=sp1->name_of_goods[1];
	char *s2=sp1->name_of_goods[2];
	char *s3=sp1->name_of_goods[3];
	char *s4=sp1->name_of_goods[4];
	goods *g1=ghead;
	while(g1->next!=NULL)
		{
			if(strcmp(g1->name,s0)==0||strcmp(g1->name,s1)==0||strcmp(g1->name,s2)==0||strcmp(g1->name,s3)==0||strcmp(g1->name,s4)==0)
				{
					printf("商品名字为：\t");
					printf("%s\n",g1->name);
					printf("商品所属标签为：\t");
					printf("%s\n",g1->label);
					printf("商品是否有人想要：\t");
					printf("%c\n",g1->wanted);
					printf("商品所留电话为：\t");
					printf("%s\n",g1->tele_of_seller);
					printf("商品的价格为：\t");
					printf("%d\n\n",g1->price);
					g1=g1->next;
					flag=1;
				}
			else
				g1=g1->next;

		}
	if(strcmp(g1->name,s0)==0||strcmp(g1->name,s1)==0||strcmp(g1->name,s2)==0||strcmp(g1->name,s3)==0||strcmp(g1->name,s4)==0)
				{
					printf("商品名字为：\t\t");
					printf("%s\n",g1->name);
					printf("商品所属标签为：\t");
					printf("%s\n",g1->label);
					printf("商品是否有人想要：\t");
					printf("%c\n",g1->wanted);
					printf("商品所留电话为：\t");
					printf("%s\n",g1->tele_of_seller);
					printf("商品的价格为：\t\t");
					printf("%d\n\n",g1->price);
					g1=g1->next;
					flag=1;
				}
	if(flag==0)
			{
				printf("您暂无销售中的商品\n");
			}
}
void search_of_buyers()//买家查询商品
{
	int flag1=0,flag2=0,flag3=0;
	goods *a=ghead;
	printf("您需要哪种类型的商品？\n");
	printf("1.日用百货 2.电子机械 3.经史典籍\n");
	int ch;
	scanf("%d",&ch);
	if(ch==1)
		{
			while(a->next!=NULL)
				{
					if(strcmp("日用百货",a->label)==0)
						{
							printf("商品名字:%s\n",a->name);
							printf("商品标签:%s\n",a->label);
							printf("是否有人想要该商品:%c\n",a->wanted);
							printf("卖家电话为：%s\n",a->tele_of_seller);
							printf("商品价格:%d\n\n",a->price);
							a=a->next;
							flag1=1;
						}
					else
						a=a->next;
				}
					if(strcmp("日用百货",a->label)==0)
						{
							printf("商品名字:%s\n",a->name);
							printf("商品标签:%s\n",a->label);
							printf("是否有人想要该商品:%c\n",a->wanted);
							printf("卖家电话为：%s\n",a->tele_of_seller);
							printf("商品价格:%d\n\n",a->price);
							flag1=1;
						}
					if(flag1==0)
						printf("无日用百货类的商品\n");
		}
	else if(ch==2)
		{
			while(a->next!=NULL)
				{
					if(strcmp("电子器械",a->label)==0)
						{
							printf("商品名字:%s\n",a->name);
							printf("商品标签:%s\n",a->label);
							printf("是否有人想要该商品:%c\n",a->wanted);
							printf("卖家电话为：%s\n",a->tele_of_seller);
							printf("商品价格:%d\n\n",a->price);
							a=a->next;
							flag2=1;
						}
					else
						a=a->next;
				}
					if(strcmp("电子机械",a->label)==0)
						{
							printf("商品名字:%s\n",a->name);
							printf("商品标签:%s\n",a->label);
							printf("是否有人想要该商品:%c\n",a->wanted);
							printf("卖家电话为：%s\n",a->tele_of_seller);
							printf("商品价格:%d\n\n",a->price);
							flag2=1;
						}
					if(flag2==0)
						printf("无电子机械类的商品\n");
		}
	else if(ch==3)
		{
			while(a->next!=NULL)
				{
					if(strcmp("经史典籍",a->label)==0)
						{
							printf("商品名字:%s\n",a->name);
							printf("商品标签:%s\n",a->label);
							printf("是否有人想要该商品:%c\n",a->wanted);
							printf("卖家电话为：%s\n",a->tele_of_seller);
							printf("商品价格:%d\n\n",a->price);
							a=a->next;
							flag3=1;
						}
					else
						a=a->next;
				}
					if(strcmp("经史典籍",a->label)==0)
						{
							printf("商品名字:%s\n",a->name);
							printf("商品标签:%s\n",a->label);
							printf("是否有人想要该商品:%c\n",a->wanted);
							printf("卖家电话为：%s\n",a->tele_of_seller);
							printf("商品价格:%d\n\n",a->price);
							flag3=1;
						}
					if(flag3==0)
						printf("无经史典籍类的商品\n");
		}
	else
		printf("无此标签的商品\n");
}
int delete_of_goods( )//卖家删除自己所卖的商品
{
    int i;
    char name[100];
    char ch;
    while( 1 )
    {
        printf("\n请输入待删除商品的名字（按回车键确认）：");
        getchar();
        gets( name );
        gp1 = ghead;
        gp2 = NULL;

        while( gp1 != NULL )
        {
            if( (strcmp( gp1 -> name, name ) == 0) && (strcmp( gp1 -> tele_of_seller, sp1 -> telenumber ) == 0) )
            {
                printf( "\n您要删除的商品名是：%s\n", gp1 -> name );
                printf("请您再次确认[y/Y]:");
                ch = getche();
                if( tolower(ch) == 'y' )
                {
                    if( gp1 == ghead )
                        ghead = ghead -> next;
                    else
                        gp2 -> next = gp1 -> next;
                    for( i = 0; i < 5; i ++ )
                        if( strcmp( sp1 -> name_of_goods[i], gp1 -> name ) == 0 )
                            strcpy( sp1 -> name_of_goods[i], "NULL" );
                    printf("删除成功！");
                    break;
                }
            }
            else
            {
                gp2 = gp1;
                gp1 = gp1 -> next;
            }
        }

        if( gp1 == NULL)
        {
            printf("\n不存在您要删除的信息，请按任意键继续......\n");
            getch();
        }
        break;
    }
    return 1;
}
void change_info_of_goods( int sh )//更改商品信息
{
    char ch, newname[100], newlabel[50];
    int newprice, i;
    gp1 = ghead;
    printf("%s", sp1 -> name_of_goods[sh-1]);
    while( gp1 != NULL )
        {
            if( (strcmp( sp1 -> name_of_goods[sh-1], gp1 -> name ) == 0) && (strcmp( sp1 -> telenumber, gp1 -> tele_of_seller ) == 0) )
                break;
            else
                gp1 = gp1 -> next;
        }
    while(1)
    {
        printf("\n请选择您需要修改的信息：\n");
        printf("1.名字  2.标签  3.价格  \n");
        printf("请选择：");
        ch = getche();
        switch( ch )
        {
            case'1':getchar();
                    printf("\n请输入新的信息（回车结束）：");
                    gets( newname );
                    printf("是否确认？[y/n]");
                    ch = getche();
                    if( tolower(ch) == 'y')
                        strcpy( gp1 -> name, newname );
                        strcpy( sp1 -> name_of_goods[sh-1], newname );
                    break;

            case'2':getchar();
                    printf("\n请输入新的信息（回车结束）：");
                    gets( newlabel );
                    printf("是否确认？[y/n]");
                    ch = getche();
                    if( tolower(ch) == 'y')
                        strcpy( gp1 -> label, newlabel );
                    break;

            case'3':getchar();
                    printf("\n请输入新的信息（回车结束）：");
                    scanf( "%d", &( newprice ) );
                    printf("是否确认？[y/n]");
                    ch = getche();
                    if( tolower(ch) == 'y')
                        gp1 -> price = newprice;
                    break;
            default: printf("\n输入错误，请重新输入：\n");
                    break;
        }
        break;
    }
}
void fprintf_of_sellers()//将信息写入sellers.txt
{
    int i;
    fp1 = fopen("sellers.txt", "w");
    sp1 = shead;
    while( sp1 != NULL )
    {
        fprintf( fp1, "%s %s %s %s ", sp1 -> number, sp1 -> name, sp1 -> password, sp1 -> telenumber );
        for ( i = 0; i < 5; i ++ )
            fprintf( fp1, "%s ", sp1 -> name_of_goods[i] );
        fprintf( fp1, "\n");
        sp1 = sp1 -> next;
    }
    fclose( fp1 );
    free( sp1 );
}
void fprintf_of_buyers()//将信息写入buyers.txt
{
    fp2 = fopen("buyers.txt", "w");
    bp1 = bhead;
    while( bp1 != NULL )
    {
        fprintf( fp2, "%s %s %s\n", bp1 -> number, bp1 -> name, bp1 -> password );
        bp1 = bp1 -> next;
    }
    fclose( fp2 );
    free( bp1 );
}
void fprintf_of_goods()//将信息写入goods.txt
{
    fp3 = fopen("goods.txt", "w");
    gp1 = ghead;
    while( gp1 != NULL )
    {
        fprintf( fp3, "%s %s %c %s %d\n", gp1 -> name, gp1 -> label, gp1 -> wanted, gp1 -> tele_of_seller, gp1 -> price );
        gp1 = gp1 -> next;
    }
    fclose( fp3 );
    free( gp1 );
}
