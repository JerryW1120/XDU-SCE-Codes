#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
typedef struct
   {
	   char number[20];
       char name[20];
       char sex[50];
       char name_of_book[100];
       struct readers *next;
   }readers;
   readers *rhead;
typedef struct
   {
	   char serial_number[20];
       char name[20];
       int num1, num2;               //1：总数；2：在架上的数
       char productor[50];
       char name_of_reader[5][20];
       struct books *next;
   }books;
    books *bhead;
    FILE *fp1, *fp2;
    readers *rp1, *rp2;
    books *bp1, *bp2;
    int chushihua();
    int student();
    int administrator();
    int Bborrow();
    int Breturn();
    int Bsearch();
    int Bdelete();
    int Rdelete();
    int Badd();
    int Radd();
    int Brepair();
    int Rreapir();
    int main()
    {
        char ch;
        char putpassword[20] ,password[20] = "1718012";
        chushihua();
        printf("\n\t\t\t**********************欢迎使用图书馆系统**********************\n");
        printf("\t\t\t*                          1.学生模块                        *\n");
        printf("\t\t\t*                          2.管理员                          *\n");
        printf("\t\t\t*                          0.退出                            *\n");
        printf("\t\t\t**************************************************************\n");
        printf("请选择（1/2/0）:");
        ch = getche();
        switch( ch )
        {
            case'1':student();
                //调用学生模块
            break;
            case'2':
                printf("\n请输入密码：");

                while(1)
                {
                    gets( putpassword );
                    if( ( strcmp( putpassword, password ) == 0 ) || ( strcmp( putpassword, "0" ) == 0 ) )
                        break;
                    else
                        printf("输入错误，请重新输入，或输入0以退出");
                }
                if( ( strcmp( putpassword, password ) == 0 ) )
                {
                    administrator();//管理员模块
                    break;
                }
                else
                break;
            case'0':
            break;
            default:printf("\n输入错误，请重新选择\n\n\n");
                break;
        }
        printf("\n再见！请按任意键退出。");
                getch();
        return 0;
   }


int student()
{
        char ch;
        printf("\n\t\t\t***************************学生界面***************************\n");
        printf("\t\t\t*                           1.借书                           *\n");
        printf("\t\t\t*                           2.还书                           *\n");
        printf("\t\t\t*                           3.查询                           *\n");
        printf("\t\t\t*                           0.退出                           *\n");
        printf("\t\t\t**************************************************************\n");
        printf("请选择（1/2/3/0）:");
        ch = getche();
        switch( ch )
        {
            case'1':Bborrow();
                //调用借书模块
            break;
            case'2':Breturn();
                //调用还书模块
            break;
            case'3':Bsearch();
                //调用查询模块
            break;
            case'0':
            break;
            default:printf("\n输入错误，请重新选择\n\n\n");
                break;
        }
        return 1;
   }

int Bborrow()     //借书
{
    int i, count = 0;
    char inputname[100], bname[100], ch;
    fp1 = fopen( "readers.txt", "r" );
    fp2 = fopen( "books.txt", "r" );
    printf("\n\t\t\t************************请输入您的姓名************************\t\t\n");
    printf("\t\t\t**************************************************************\n");
    printf( "\t\t\t\t\t\t    " );
    scanf("%s", inputname);
    while( rp1 != NULL )
	{
		if( strcmp( inputname, rp1 -> name ) == 0 )
		{
		    count ++;
		    break;
		}
		else
            rp1 = rp1 -> next;
        readers *rp1 = ( readers * )malloc( sizeof( readers ) );
   	}

   	if( count == 0 )
   		printf("学生信息不存在");
   	else
   	{
   	    count = 0;
   		if( strcmp( rp1 -> name_of_book, "NULL" ) != 0 )
   			printf( "您有书未还，请先还书");

   		else
   		{
   			printf("\n\t\t\t***********************请输入想借的书名***********************\t\t\n");
   			printf( "\t\t\t\t\t     " );
            scanf("%s", bname);
            while( bp1 != NULL )
			{
				if( strcmp( bname, bp1 -> name ) == 0 )
				{
                    count ++;
                    break;
				}
                else
                    bp1 = bp1 -> next;
   				books *b=( books * )malloc( sizeof( books ) );
   			}
            if( count == 0 )
   			printf("图书信息不存在");
            else
            	{
            		if( bp1 -> num2 == 0 )
                	printf("书已借完");
            		else
                	{
                     	printf( "\n%s ",bp1 -> serial_number );
                     	printf( "%s ",bp1 -> name );
                     	printf( "馆藏%d本 ",bp1 -> num1 );
                     	printf( "在架上%d本 ",bp1 -> num2 );
                    	printf( "%s  借阅者：",bp1 -> productor );
                        for( i = 0; strcmp(bp1 -> name_of_reader[i] , "NULL") != 0; i ++)
                    		printf( "%s ",bp1 -> name_of_reader[i] );
                    	printf("\n\n确认要借吗？  [Y->确认，其余任意键否认]\n");
                    	printf( "\n\t\t\t\t\t\t\t" );
                    	ch = getche();
                    	if( tolower( ch ) == 'y' )
                        {
                            printf("\n借书成功！\n");
                            bp1-> num2 --;
                            strcpy( bp1 -> name_of_reader[i], rp1 -> name );
                            strcpy( rp1 ->name_of_book, bp1 ->name );
                            fclose(fp1);
                            fclose(fp2);
                            rp1 = rhead;
                            bp1 = bhead;
                            fp1 = fopen( "readers.txt", "w" );
                            fp2 = fopen( "books.txt", "w" );
                            while( rp1 != NULL )
                            {
                                fprintf( fp1, "%s %s %s %s\n", rp1 -> number, rp1 -> name, rp1 -> sex, rp1 -> name_of_book );
                                rp1 = rp1 -> next;
                            }
                            while( bp1 != NULL )
                            {
                                fprintf( fp2,"%s %s %d %d %s ", bp1 -> serial_number, bp1 -> name, bp1 -> num1, bp1 -> num2 , bp1 -> productor );
                                for ( i = 0; i < 5; i ++ )
                                    fprintf( fp2, "%s ", bp1 -> name_of_reader[i] );
                                fprintf( fp2, "\n");
                                bp1 = bp1 -> next;
                            }
                            free( rp1 );
                            rp1 = NULL;
                            free( bp1 );
                            bp1 = NULL;
                        }
                        else
                            printf("借书失败");
                	}
        		}
   		}
	}
	fclose(fp1);
	fclose(fp2);
	   return 1;
}

int Breturn()   //还书
{
    int i, count = 0;
    char inputname[100], ch;
    fp1 = fopen( "readers.txt", "r" );
    fp2 = fopen( "books.txt", "r" );
    printf("\n\t\t\t************************请输入您的姓名************************\t\t\n");
    printf("\t\t\t**************************************************************\n");
    printf( "\t\t\t\t\t\t    " );
    scanf("%s", inputname);
   while( rp1 != NULL )
	{
		if( strcmp( inputname, rp1 -> name ) == 0 )
		{
		    count ++;
		    break;
		}
		else
            rp1 = rp1 -> next;
   	}
   		//读取学生信息

   	if( count == 0 )
   		printf("学生信息不存在");
   	else
   	{
   	    count = 0;
   		if( strcmp( rp1 -> name_of_book, "NULL" ) == 0 )
   			printf( "您还未借书");

   		else
   		{
                printf( "您所借的书是:  %s\n", rp1 -> name_of_book );
                printf("\n确认要还吗？  [Y->确认，其余任意键否认]\n");
                printf( "\n\t\t\t\t\t\t\t" );
                ch = getche();
                if( tolower( ch ) == 'y' )
                {
                    printf("\n还书成功！\n");
                    while( bp1 != NULL )
                    {
                        if( strcmp( rp1 -> name_of_book, bp1 -> name ) == 0)
                            break;
                        else
                            bp1 = bp1 -> next;
                            books *bp1 = ( books * )malloc( sizeof( books ) );
                    }
                    bp1 -> num2 ++;
                    for( i = 0; i <= 5; i ++ )
                    {
                        if ( strcmp( bp1 -> name_of_reader[i], inputname ) == 0 )
                        {
                            strcpy( bp1 -> name_of_reader[i], "NULL" );
                        }
                    }
                    strcpy( rp1 ->name_of_book, "NULL" );
                    fclose(fp1);
                    fclose(fp2);
                    rp1 = rhead;
                    bp1 = bhead;
                    fp1 = fopen( "readers.txt", "w" );
                    fp2 = fopen( "books.txt", "w" );
                    while( rp1 != NULL )
                    {
                        fprintf( fp1, "%s %s %s %s\n", rp1 -> number, rp1 -> name, rp1 -> sex, rp1 -> name_of_book );
                        rp1 = rp1 -> next;
                    }
                    while( bp1 != NULL )
                    {
                        fprintf( fp2,"%s %s %d %d %s ", bp1 -> serial_number, bp1 -> name, bp1 -> num1, bp1 -> num2 , bp1 -> productor );
                        for ( i = 0; i < 5; i ++ )
                            fprintf( fp2, "%s ", bp1 -> name_of_reader[i] );
                        fprintf( fp2, "\n");
                        bp1 = bp1 -> next;
                    }
                    free( rp1 );
                    rp1 = NULL;
                    free( bp1 );
                    bp1 = NULL;
                }
                else
                    printf("还书失败");

        }
   	}


    fclose(fp1);
	fclose(fp2);
    return 1;
}

int Bsearch()
{
    int i, count = 0;
    char bname[100];
    char ch;
    fp2 = fopen( "books.txt", "r" );
    printf("\n\t\t\t**********************请输入想查询的书名**********************\t\t\n");
    printf( "\t\t\t\t\t     " );
    scanf("%s", bname);
    while( bp1 != NULL )
    {
       if( strcmp( bname, bp1 -> name ) == 0 )
        {
            count ++;
            break;
        }
        else
        bp1 = bp1 -> next;
    }

            	//链表,需要拿结构体中所有的编号与输入的书号进行比较
    if( count == 0 )
    printf("图书信息不存在");
                //若存在，则先判断其结构体中剩余数量是否为0，
    else
    {
        printf( "%s ",bp1 -> serial_number );
        printf( "%s ",bp1 -> name );
        printf( "馆藏%d本 ",bp1 -> num1 );
        printf( "在架上%d本 ",bp1 -> num2 );
        printf( "%s ",bp1 -> productor );
        printf("借阅者：");
        for( i = 0; i < 5; i ++)
            if( strcmp(bp1 -> name_of_reader[i] , "NULL") != 0 )
                printf( "%s ",bp1 -> name_of_reader[i] );
    }
	fclose(fp2);
    return 1;
}

int administrator()
{
        char ch;
        printf("\n\t\t\t**************************管理员模块**************************\n");
        printf("\t\t\t*                         1.增添学生信息                     *\n");
        printf("\t\t\t*                         2.修改学生信息                     *\n");
        printf("\t\t\t*                         3.删除学生信息                     *\n");
        printf("\t\t\t*                         4.增添图书信息                     *\n");
        printf("\t\t\t*                         5.修改图书信息                     *\n");
        printf("\t\t\t*                         6.删除图书信息                     *\n");
        printf("\t\t\t*                         0.退出                             *\n");
        printf("\t\t\t**************************************************************\n");
        printf("请选择（1/2/3/4/5/6/0）:");
        ch = getche();
        switch( ch )
        {
            case'1':Radd();
            break;
            case'2':Rrepair();
            break;
            case'3':Rdelete();
            break;
            case'4':Badd();
            break;
            case'5':Brepair();
            break;
            case'6':Bdelete();
            break;
            case'0':
            break;
            default:printf("\n输入错误，请重新选择\n\n\n");
                break;
        }
        return 1;
   }

int Radd()
{
    int add_flag;
    char ch;
    rp1 = rhead;
    while( rp1 -> next != NULL )
        rp1  = rp1 -> next;
    ch = 'y';
    while( tolower(ch) =='y' )
    {
        rp2 = ( struct readers *) malloc (sizeof(readers));
        printf("\n\t\t\t\t\t\t增添学生信息");
        printf("\n请按如下格式输入：\n");
        printf("学号：");
        gets( rp2 -> number );
        printf("姓名：");
        gets( rp2 -> name );
        printf("性别：");
        gets( rp2 -> sex );
        rp2 -> next = NULL;
        strcpy( rp2 -> name_of_book, "NULL" );
        printf("\n请确认上述输入[y/Y],否则按其他任意键继续\n");
        ch = getche();
        if( tolower(ch) == 'y' )
        {
            rp1 ->next = rp2;
            rp1 = rp2;
            rp2 = NULL;
            fp1 = fopen("readers.txt", "w");
            rp1 = rhead;
            while( rp1 != NULL )
            {
                fprintf( fp1, "%s %s %s %s\n", rp1 -> number, rp1 -> name, rp1 -> sex, rp1 -> name_of_book );
                rp1 = rp1 -> next;
            }
            fclose( fp1 );
            printf("\n增添学生信息成功！！......按任意键继续......");
            getch();
            putch( '\n' );
            add_flag = 1;
        }
        else
        {
            printf("\n未能增添学生信息！！！......按任意键继续......");
            getch();
            putch( '\n' );
            add_flag = 2;
        }
        printf("\n是否增添下一个学生信息，如果增加，键入[y/Y]；否则按任意键退出管理员系统");
        ch = getch();
        }
        rp1 = NULL;
        return add_flag;
}

int Rrepair()
{
    int count = 0, i;
    char ch, stu_name[20], newnumber[20], newname[100], newsex[50];
    chushihua();
    fp1 = fopen( "readers.txt", "r" );
    printf("\n请输入待修改学生的名字（按回车键确认）：\n\t\t\t\t\t\t");
    gets(stu_name);
    while( rp1 != NULL )
        {
            if( strcmp(  stu_name, rp1 -> name ) == 0)
                {
                    count ++;
                    break;
                }
            else
                rp1 = rp1 -> next;
                readers *rp1 = ( readers * )malloc( sizeof( readers ) );
        }


   	if( count == 0 )
   		printf("学生信息不存在");
    else
        while(1)
        {
            printf("\n您要修改的学生的原始信息是：\n");
            printf("%s\t%s\t%s\t%s", rp1 -> number, rp1 -> name, rp1 -> sex, rp1 -> name_of_book );
            printf("\n1.学号  2.姓名  3.性别  \n");
            printf("请选择：");
            ch = getche();
            switch( ch )
            {
                case'1':printf("\n请输入新的信息（回车结束）：");
                        gets( newnumber );
                        printf("是否确认？[y/n]");
                        ch = getche();
                        if( tolower(ch) == 'y')
                            strcpy( rp1 -> number, newnumber );
                        break;
                case'2':printf("\n请输入新的信息（回车结束）：");
                        gets( newname );
                        printf("是否确认？[y/n]");
                        ch = getche();
                        if( tolower(ch) == 'y')
                            strcpy( rp1 -> name, newname );
                        break;

                case'3':printf("\n请输入新的信息（回车结束）：");
                        gets( newsex );
                        printf("是否确认？[y/n]");
                        ch = getche();
                        if( tolower(ch) == 'y')
                            strcpy( rp1 -> sex, newsex );
                        break;
                default: printf("\n输入错误，请重新输入：\n");
                break;
            }
            if( tolower(ch) == 'y')
            {
                printf("\n修改成功！\n");
                printf("\n您修改后的学生的信息是：\n");
                printf(" %s %s %s %s", rp1 -> number, rp1 -> name, rp1 -> sex, rp1 -> name_of_book );
                fp1 = fopen("readers.txt", "w");
                rp1 = rhead;
                while( rp1 != NULL )
                {
                    fprintf( fp1, "%s %s %s %s\n", rp1 -> number, rp1 -> name, rp1 -> sex, rp1 -> name_of_book );
                    rp1 = rp1 -> next;

                }
                fclose( fp1 );

            }
            else
            {
                printf("\n\n修改失败。\n");
            }

            break;
        }
        return 1;
    }

int Rdelete()
{
    char ch,stu_name[10];
    int delete_flag, count = 0;
    ch = 'y';
    while( tolower(ch) == 'y' )
    {
        printf("\n请输入待删除学生的名字（按回车键确认）：");
        gets(stu_name);
        rp1 = rhead;
        rp2 = NULL;
        while( rp1 != NULL )
        {
            if( strcmp( rp1 -> name, stu_name ) )
            {
                rp2 = rp1;
                rp1 = rp1 -> next;
                count ++;
            }
            else
            {
                printf( "\n您要删除的学生姓名是：%s\n", rp1 -> name );
                printf("\n请您再次确认[y/Y]:");
                ch = getche();
                if( tolower(ch) == 'y' )
                {
                    if( count == 0 )
                        rp1 = rp1 -> next;
                    else
                        rp2 -> next = rp1 -> next;
                    printf("\n\n删除成功！\n");
                    delete_flag = 3;
                    break;
                }
                else
                {
                    printf("\n\n删除失败！\n");
                    delete_flag = 4;
                    break;
                }
            }
        }
        if( rp1 == NULL)
        {
            printf("\n不存在您要删除的信息，请按任意键继续......\n");
            delete_flag = 5;
            getch();
        }
        printf("\n是否继续删除下一个学生信息[y/Y],不删除按其他任意键退出管理员系统......\n");
        ch = getche();
    }
    fp1 = fopen("readers.txt", "w");
    if( count != 0 )
        rp1 = rhead;
    while( rp1 != NULL )
    {
        fprintf( fp1, "%s %s %s %s\n", rp1 -> number, rp1 -> name, rp1 -> sex, rp1 -> name_of_book );
        rp1 = rp1 -> next;     //写不到文件里去
    }
    fclose( fp1 );
    return delete_flag;
}

int Badd()
{
    int i;
    char ch;
    bp1 = bhead;
    while( bp1 -> next != NULL )
        bp1  = bp1 -> next;
    ch = 'y';
    while( tolower(ch) =='y' )
    {
        bp2 = ( struct books *) malloc (sizeof(books));
        printf("\n\t\t\t\t\t\t增添图书信息");
        printf("\n请按如下格式输入：\n");
        printf("书号：");
        gets( bp2 -> serial_number );
        printf("书名：");
        gets( bp2 -> name );
        printf("出版社：");
        gets( bp2 -> productor );
        printf("数量：");
        scanf( "%d", &( bp2 -> num1 ) );
        bp2 -> num2 = bp2 -> num1;
        for ( i = 0; i < 5; i ++ )
            strcpy( bp2 -> name_of_reader[i] , "NULL" );
        bp2 -> next = NULL;
        printf("\n 请确认上述输入[y/Y],否则按其他任意键继续");
        ch = getche();
        if( tolower(ch) == 'y' )
        {
            bp1 -> next = bp2;
            bp1 = bp2;
            bp2 = NULL;
            fp2 = fopen("books.txt", "w");
            bp1 = bhead;
            while( bp1 != NULL )
            {
                fprintf( fp2,"%s %s %d %d %s ", bp1 -> serial_number, bp1 -> name, bp1 -> num1, bp1 -> num2 , bp1 -> productor );
                for ( i = 0; i < 5; i ++ )
                    fprintf( fp2, "%s ", bp1 -> name_of_reader[i] );
                fprintf( fp2, "\n");
                bp1 = bp1 -> next;
                }    //写进去之后有乱码
                free( bp1 );
                bp1 = NULL;
            printf("\n\n追加图书信息成功！！......按任意键继续......");
            getch();
            putch( '\n' );

        }
        else
        {
            printf("\n\n未能追加图书信息！！！......按任意键继续......");
            getch();
            putch( '\n' );
        }
        printf("\n是否增加下一个图书信息，如果增加，键入[y/Y]；否则按任意键退出管理员系统......");
        ch = getch();
        }
        bp1 = NULL;
        fclose( fp2 );
        return 1;
}

int Brepair()
{
    int count = 0, i;
    char ch, book_name[20], newserial_number[20], newname[100], newproductor[50];
    int newnum1;
    chushihua();
    fp2 = fopen( "books.txt", "r" );

    printf("\n请输入待修改书的书名（按回车键确认）：");
    gets(book_name);
    while( bp1 != NULL )
        {
            if( strcmp(  book_name, bp1 -> name ) == 0)
                {
                    count ++;
                    break;
                }
            else
                bp1 = bp1 -> next;
                books *bp1 = ( books * )malloc( sizeof( books ) );
        }

   		//读取书的信息

   	if( count == 0 )
   		printf("\n图书信息不存在");
    else
        while(1)
        {
            printf("\n您要修改的书的原始信息是：\n");
            printf("%s\t%s\t馆藏%d本\t在架上%d本\t%s\t\n",bp1 -> serial_number, bp1 -> name, bp1 -> num1, bp1 -> num2, bp1 -> productor );
            printf("\n请输入编号以修改相应信息：\n");
            printf("1.书号  2.书名  3.馆藏数  4.出版社  \n");
            printf("请选择：");
            ch = getche();
            switch( ch )
            {
                case'1':printf("\n请输入新的信息（回车结束）：");
                        gets( newserial_number );
                        printf("\n是否确认？[y/n]");
                        ch = getche();
                        if( tolower(ch) == 'y')
                            strcpy( bp1 -> serial_number, newserial_number );
                        break;
                case'2':printf("\n请输入新的信息（回车结束）：");
                        gets( newname );
                        printf("\n是否确认？[y/n]");
                        ch = getche();
                        if( tolower(ch) == 'y')
                            strcpy( bp1 -> name, newname );
                        break;
                case'3':printf("\n请输入新的信息（回车结束）：");
                        scanf( "%d", &( newnum1 ) );
                        printf("\n是否确认？[y/n]");
                        ch = getche();
                        if( tolower(ch) == 'y')
                            bp1 -> num1 = newnum1;
                        break;
                case'4':printf("\n请输入新的信息（回车结束）：");
                        gets( newproductor );
                        printf("\n是否确认？[y/n]");
                        ch = getche();
                        if( tolower(ch) == 'y')
                            strcpy( bp1 -> productor, newproductor );
                        break;
                default: printf("\n输入错误，请重新输入：\n");
                break;
            }
            if( tolower(ch) == 'y')
            {
                printf("\n修改成功！\n");
                printf("\n您修改后的图书的信息是：\n");
                printf("%s\t%s\t馆藏%d本\t%s\t\n",bp1 -> serial_number, bp1 -> name, bp1 -> num1, bp1 -> productor );
                fp2 = fopen("books.txt", "w");
                bp1 = bhead;
                while( bp1 != NULL )
                    {
                        fprintf( fp2,"%s %s %d %d %s ", bp1 -> serial_number, bp1 -> name, bp1 -> num1, bp1 -> num2 , bp1 -> productor );
                        for ( i = 0; i < 5; i ++ )
                            fprintf( fp2, "%s ", bp1 -> name_of_reader[i] );
                        fprintf( fp2, "\n");
                        bp1 = bp1 -> next;
                    }
                      //可以显示在屏幕上，但是写不进文件里
            fclose( fp2 );
            }
            else
            {
                printf("\n\n修改失败。\n");
            }
            break;
        }

        return 1;
    }

int Bdelete()
{
    char ch,book_name[100];
    int i, delete_flag, count = 0;
    ch = 'y';
    while( tolower(ch) == 'y' )
    {
        printf("\n\n请输入待删除书的书名（按回车键确认）：");
        gets(book_name);
        bp1 =bhead;
        bp2 = NULL;
        while( bp1 != NULL )
        {
            if( strcmp( bp1 -> name, book_name ) )
            {
                bp2 = bp1;
                bp1 = bp1 -> next;
                count ++;
            }
            else
            {
                printf( "\n您要删除的书是：%s\n", bp1 -> name );
                printf("\n请您再次确认[y/Y]:");
                ch = getche();
                if( tolower(ch) == 'y' )
                {
                    printf("\n\n删除成功！");
                    if( count != 0 )
                        bp2 -> next = bp1 -> next;
                    else
                        bp1 = bp1 -> next;
                    delete_flag = 3;
                    break;
                }
                else
                {
                    printf("\n\n删除失败！");
                    delete_flag = 4;
                    break;
                }
            }
        }
        if( bp1 == NULL)
        {
            printf("\n不存在您要删除的信息，请按任意键继续......\n");
            delete_flag = 5;
            getch();
        }
        printf("\n\n是否继续删除下一个图书信息[y/Y],不删除按其他任意键退出管理员系统......\n");
        ch = getche();
    }
    fp2 = fopen("books.txt", "w");
    if( count != 0 )
        bp1 = bhead;
    while( bp1 != NULL )
    {
        fprintf( fp2,"%s %s %d %d %s ", bp1 -> serial_number, bp1 -> name, bp1 -> num1, bp1 -> num2 , bp1 -> productor );
        for ( i = 0; i < 5; i ++ )
            fprintf( fp2, "%s ", bp1 -> name_of_reader[i] );
        fprintf( fp2, "\n");
        bp1 = bp1 -> next;
    }
        free( bp1 );
        bp1 = NULL;
    fclose( fp2 );
    return delete_flag;
}

int chushihua()
{
    int i;
    fp1 = fopen("readers.txt", "r");
    fp2 = fopen("books.txt", "r");
    if ( ( fp1 == NULL ) || ( fp2 == NULL ) )
    {
        printf("未能初始化信息");
        fclose( fp1 );
        fclose( fp2 );
        return 0;
    }
    else
    {
        rp1 = ( readers *)malloc( sizeof(readers) );
        rhead = rp1;
         while( !feof(fp1) )
        {
            fscanf( fp1,"%s %s %s %s", rp1 -> number, rp1 -> name, rp1 -> sex, rp1 -> name_of_book );
            rp2 = rp1;
            rp1 = ( readers *)malloc( sizeof(readers) );
            rp2 -> next = rp1;
        }
        rp1 -> next = NULL;
        rp2 = NULL;
        free( rp1 );
        rp1 = NULL;
        rp1 = rhead;

        bp1 = ( books *)malloc( sizeof(books) );
        bhead = bp1;
         while( fscanf( fp2,"%s", bp1 -> serial_number) != EOF)
        {
            fscanf( fp2,"%s %d %d %s ", bp1 -> name, &(bp1 -> num1), &(bp1 -> num2), bp1 -> productor );
            for ( i = 0; i < 5; i ++ )
                fscanf( fp2, "%s", bp1 -> name_of_reader[i] );
            bp2 = bp1;
            bp1 = ( books *)malloc( sizeof(books) );
            bp2 -> next = bp1;
        }
        bp1 -> next = NULL;
        bp2 = NULL;
        free( bp1 );
        bp1 = NULL;
        bp1 = bhead;
    }

    fclose( fp1 );
    fclose( fp2 );
    return 1;
}

