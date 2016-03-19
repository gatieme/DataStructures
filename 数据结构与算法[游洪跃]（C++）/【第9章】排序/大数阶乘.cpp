#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;
#define N 20000

int Input(int *result)								//计算m阶乘的计算
{

    int i, j, len, n, flag = 0, num;
    char ch[N];
    result[N-1] = 1;

    while( !flag )						//提示输入m，如果错误重新输入
    {
        cout<<"***********************************" <<std::endl;
        cout<<"请输入要求阶乘的数:";
        cin>>ch;
        cout<<"***********************************" <<std::endl;
        len = strlen(ch);
        for(i = 0 ; i < len; i++)
        {
            if(ch[i] < 47 || ch[i] > 58)
            {
                flag = 0;
                cout<<"\t\t\t\t  错误输入，请重输!!!\n";
                break;
            }
            flag = 1;
        }
    }
    num = atoi(ch);							//将输入的字符串转换成相应的数字
    for(i = 1; i <= num; i++)					//开始进行阶乘的计算
    {
        for(j = 0; j <= N-1; j++)			//开始相乘，result[N-1]存放的是个位数，result[N-2]是十位数，依次下去
        {
            result[j] = result[j] * i;
        }
        for(j = N-1; j >= 1; j--)
        {
            if(result[j] >= 10)
            {
                result[j-1] = result[j-1] + result[j]/10;	//如果result[j]大于10，开始向result[j-1]位进一
                result[j] = result[j] % 10;			//result[j]自己留个位数，依次下去
            }
		}
    }
    j = 0;
    while(result[j] == 0)						//从result[0]开始寻找阶乘高位开始的n值
    {
        j = j+1;
    }
    n = j;
    cout <<num <<"的阶乘为：" <<endl;
    return n;
}

// 程序欢迎界面
void Menu( )
{
    cout<<"***********************************************" <<std::endl;
	cout<<"**                   计算阶乘                **" <<std::endl;
	cout<<"***提醒:由于内存有限，尽量不要输入过大的数字***" <<std::endl;
    cout<<"*******              1.开始             *******" <<std::endl;
    cout<<"*******              2.退出             *******" <<std::endl;
    cout<<"***********************************************" <<std::endl;

    //system("cls");
}


void OutPut(int *result, int n)
{
    int j = n;
    //cout<<m<<"的阶乘是:";
    for( ;j <= N-1; j++)					//将阶乘从高位依次显示出来
    {
        if((j-n)%50==0)  cout<<endl;//每隔20位换行
        cout<<result[j];
    }
    cout<<"\n";
    system("pause");
    system("cls");
}


void End( )
{
    cout <<"\t\t************************************" <<endl;
    cout <<"\t\t****        用户结束            ****" <<endl;
    cout <<"\t\t************************************" <<endl;
}


int  main()
{
	int choice,flag=0, len;
	char str[N];
    int result[N]={NULL};
	while(!flag)
	{
		int f=0;
		while(!f)
		{
		    system("cls");
            Menu( );            // 菜单信息
			cin>>str;
			for(int i=0;str[i]!='\0';i++)
			{								//如果输入时非数字的字符，则提示重新输入
				if(str[i]>'9'||str[i]<'0')
				{
					cout<<"\t\t\t\t\t错误输入!!!\n\n";
					system("pause");
					f = 0;
				    break;
				}
				f = 1;
			}
		}
		choice = atoi(str);
        system("cls");
		switch(choice)
		{
		case 1:
			len = Input(result);						//开始进行m阶乘的计算
			OutPut(result, len);
			break;
		case 2:
			flag = 1;							//退出循环
            End( );
			break;
		default:							//输入非1，或2的数字，提示重新输入
			cout<<"\t\t\t\t\t错误输入!!!\n\n";
			system("pause");
			break;
		}
	}
}
