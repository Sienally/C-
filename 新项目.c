//购物系统（客户端）

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

//用户结构 
typedef struct User
{
	struct User *next;
	int user_id;
	char *user_password;
	int user_monney;
}User;

//登录页面
int enter_page(User *u,int *audit)
{
	endloop://标识符
	while(1)
	{
		
		printf("欢迎登录！\n");
		printf("\n-1返回 2注册账号\n");
		
		
		int a=0;//存账号
		char *b = (char*)malloc(sizeof(char));//存密码
		
		
		//账号
		printf("\n请输入账号：");
		scanf("%d",&a);
		if(a == -1) return -1;
		if(a == 2)
		{
			system("cls");
			create_user(u);
			continue;//刷新界面
		}
		
		
		//密码
		printf("\n请输入密码：");
		scanf("%s",b);
		
		while(strlen(b) < 9 || strlen(b) > 10)
		{
			if(strcmp(b,"-1") == 0) return 0;
			if(strcmp(b,"2") == 0)
			{
				system("cls");
				create_user(u);
				goto endloop;//刷新界面
			}
			printf("格式错误！密码应在9-10个字母或数字\n");
			scanf("%s",b);
		}
	
		//检视账号和密码 
		
		int  zh = 0, mm = 0;
		User *p = u;
		while(p != NULL)
		{
			if(p->user_id == a)
			{
				zh = 1;
				while(p != NULL)
				{
					if(strcmp(p->user_password,b) == 0)
					{
						mm = 1;
						printf("登陆成功！");
						*audit = p->user_id;
						getchar();
						getchar();
						system("cls");
						return *audit;
					}
				}
			}
			p = p->next;
		}
		if(zh == 0) printf("该账号不存在！\n");
		if(mm == 0 && zh == 1) printf("密码错误！\n");
		
		
		printf("\n\n\n重新登陆(按1)\t\t\t没有账号？尝试注册一个(需要请按2)\n");
		
		//重新登陆
		int c=0;
		scanf("%d",&c);
		if(c == 1)
		{
			system("cls");
			enter_page(u,audit);
		}
		
		//跳转注册
		else if(c == 2) 
		{
	 		system("cls");	
		 	create_user(u);
	   
		}else if(c == -1)
		{
			return 0;
		}else
		{
			while(c != -1 && c!= 1 && c != 2)
			{
				printf("无效操作！\n");
				scanf("%d",&c);
			}
		}
		system("cls");
 	}
	return 0;
}

//创建账号
void create_user(User *u)
{
	printf("注册账号\n\n\n");
	printf("\n-1取消 1返回\n");
	
	User *user = (User*)malloc(sizeof(User));
	
	user->user_password = (char*)malloc(sizeof(char));
	
	//账号
	printf("\n请输入账号：");
	scanf("%d",&user->user_id);
	if(user->user_id == -1)
	{
		free(user);
		return;
	}
	//返回登录
	else if(user->user_id == 1)
	{
		system("cls");
		return ;
	}
	
	
	//密码
	printf("\n请输入密码：");
	scanf("%s",user->user_password);
	
	while(strlen(user->user_password) < 9 || strlen(user->user_password) > 10)
	{
		if(strcmp(user->user_password,"-1") == 0)
		{
			free(user);
			return;
		}
		printf("格式错误！请重试:");
		scanf("%s",user->user_password);
	}

	//入栈 
	user->next = u->next;
	u->next = user;
	
	
	printf("注册成功！");
	getchar();
	getchar();
	system("cls");
	return 0;
	
}

//遍历账号 
void view_account(User *u)
{
	int a = 0;//标识符,辨别账号是否为空
	User *p = u;
	//判断是否为头节点
	if(p->next == NULL)
	{
		printf("无账号！\n");
		return ;
	}
	//从第一个结点开始
	p = p->next;
	while(p != NULL)
	{
		printf("%d ",p->user_id);
		p = p->next;
		a = 1;
	}
	if(a == 0)
	{
		printf("无账号!\n");
	}
}

//充值
void enter_monney(User *u)
{

}

//初始化头节点 
User *init_user()
{
	User *u = (User*)malloc(sizeof(User));
	u->next = NULL;
	u->user_id = 0;
	u->user_password = 0;
	u->user_monney = 0;
	return u;
}
//已购商品栏
//商店
//我的收藏

//切换账号
int change_user(User *u,int *audit)
{
	
	
	//遍历所有的账号
	User *p = u;
	
	int c = 0;//标识符,判断是否为空
	
	int arry[1000], count = 0;//存放账号id
	
	
	//依次存放id进数组
	while(p->next != NULL)
	{
		p = p->next;
		c = 1;
		arry[count] = p->user_id;
		count++;
	}
	
	
	if(c == 0)
	{
		int a = 0;
		printf("无可切换账号！\n试试创建一个账号(2)\n");
		scanf("%d",&a);
		if(a == 2)
		{
			system("cls");
			create_user(u);
		}
	}
	else if(c == 1)
	{
		printf("3退出登录\n\n\n");
		printf("可切换账号：");

		
		//输出所有id
		for(int i = 0;i < count;i++)
		{
			printf("\t%d",arry[i]);
			if(arry[i] == *audit)
			{
				printf("(当前帐号)");
			}
		}
	
		printf("\n请选择要切换账号的id：");
	
		int a = 0;
	    
	    int flag = 1;
		while(flag)
		{
			//退出登录
			scanf("%d",&a);
			if(a == 3)
			{
				system("cls");
				*audit = 0;
				enter_page(u,audit);
				return;
			}
			
			//不允许切换当前账号
			else if(a == *audit)
			{
				printf("已是当前账号！\n");
				continue;
			}
			
			else 
			{
				flag = 0;
			}
		}
	
		char *b = (char*)malloc(sizeof(char));//暂存密码
		int zh = 0, mm = 0;//账号，密码状态
	
		User *q = u;
		while(q->next != NULL)
		{
			q = q->next;
			//外层循环，查找账号
			if(q->user_id == a)
			{
				printf("请输入密码：");
				scanf("%s",b);
				while(q->user_id != NULL)
				{
				    q = q->next;
					//内层循环，核对密码
					if(strcmp(q->user_password,b) == 0)
					{
						printf("账号切换成功！\n");
						mm = 1;
						*audit = q->user_id;
						getchar();
						getchar();
						return 1;
					}
					
				}
				zh = 1;
			}
		
		}
		if(zh == 0)
		{	
			printf("账号不存在！\n");
			getchar();
			getchar();
		}
		if(mm == 0 && zh == 1)
		{
			printf("密码错误！");
			getchar();
			getchar();
		}
	}
	return 0;
}
int main() 
{
	//创建栈的头节点
	User *u = init_user();
	
	
	//登录状态
	int audit = 0;//默认未登录状态
	
	
	
	int flag = 1;
	//登录模式
	while(flag)
	{

		printf("请选择登录模式：\n\n游客登陆(0)\t登录账号(1)\t退出(-1)\n");
		int a;
		scanf("%d",&a);
	
		
	    
		//登录界面拦截
		switch(a)
		{
			case 1:
				system("cls");
				audit = enter_page(u,&audit);
				if(audit != -1)
				{
					system("cls");
					flag = 0;
				}

				
			    if(audit == -1)
				{
					system("cls");
					continue;
				}
				break;
			
			case 0:
				system("cls");
				audit = 1001;
				flag = 0;
				break;

			
			case -1:
				return 0;
			
			default:
				system("cls");
				printf("无效操作！请重试\n");
				getchar();
				getchar();
				system("cls");
				
		}
			
	}
	
	//进入主页面
	while(audit)
	{
		headloop:
		system("cls");
		printf("当前账号：%d\n",audit);
		printf("1.我的收藏\n");
		printf("2.商店\n");
		printf("3.已购商品栏\n");
		printf("4.充值\n"); 
		printf("5.切换账号\n");
		printf("\n\n\n\n\n\n\n\n-1退出程序\n");
		
		int a=0;
		scanf("%d",&a);
		system("cls");
		switch(a)
		{
			case 5:
				change_user(u,&audit);
				break;
			case -1:
				return 0;
				break;
				
			default:
				printf("无效操作！");
				getchar();
				getchar();
				system("cls");
		}
	}
	return 0;
}