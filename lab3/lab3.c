#include<stdio.h>
#include<unistd.h>
#include<signal.h>
void waiting();
void stop();
void alarming();
int wait_mark;
main()
{
	int pid1,pid2;
	if(pid1=fork())//创建子进程pid1
	{
		if(pid2=fork())//创建子进程pid2
        {
            wait_mark=1;
            signal(SIGINT,stop);//捕捉键盘信号，并转为stop信号
            signal(SIGALRM,alarming);
            waiting();

            kill(pid1,16);
            kill(pid2,17);

            wait(0);
            wait(0);
            printf("Parent(pid=%d) Process is killed!\n",getpid());
            exit(0);
        }
        else
        {
           wait_mark=1;
            signal(17,stop);
            signal(SIGINT,SIG_IGN);//键盘不响应
            signal(SIGQUIT,SIG_IGN);//中断不响应
            while(wait_mark!=0);
            lockf(1,1,0);
            printf("Child Process 2(pid=%d,ppid=%d) is killed by Parent!\n",getpid(),getppid());
            lockf(1,0,0);
            exit(0);
        }
    }
        else
        {
           wait_mark=1;
            signal(16,stop);
            signal(SIGINT,SIG_IGN);
            signal(SIGQUIT,SIG_IGN);
            while(wait_mark!=0);
            lockf(1,1,0);
            printf("Child Process 1(pid=%d,ppid=%d) is killed by Parent!\n",getpid(),getppid());
            lockf(1,0,0);
            exit(0);
        }
        
        
    
}
void waiting()
{
	sleep(5);
    if(wait_mark!=0)
    kill(getpid(),SIGALRM);
}
void alarming()
{
	wait_mark=0;
}
void stop()
{
	wait_mark=0;
}
