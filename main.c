#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<limits.h>
#include<string.h>
#include<dirent.h>
#include<fcntl.h>
#include<time.h>
#include<grp.h>
#include<pwd.h>
#include<langinfo.h>
#include<stdint.h>
#include<locale.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#define length 1024
#define len 63

#include"pwd_code.c"
#include"echo_code.c"
#include"ls_code.c"
#include"cd_code.c"
#include"pinfo_code.c"
#include"process_code.c"
#include"env.c"

void sig_handler(int signo)
{
  if (signo == SIGINT)
    printf("received SIGINT\n");
}

int main()
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
  	printf("\ncan't catch SIGINT\n");

	int flag=0,p;
	char *username=getenv("USER");
	char hostname[HOST_NAME_MAX+1];
	int host_flag=gethostname(hostname,HOST_NAME_MAX);
	if(host_flag<0)
	{
		printf("Could not get hostname");
		exit(0);
	}
	char* prev_dir=malloc(sizeof(char) * 1024);
	char home_dir[1000];
	char dir[1000]="<";
	strcat(dir,username);
	strcat(dir,"@");
	strcat(dir,hostname);
	strcat(dir,":~");
	strcpy(home_dir,dir);

	int i;
	char input[length+1], cwd[length+1], home[length+1];
	char* relative=malloc(sizeof(char) * 1024);
	char* token[1024];
	for (i=0; i<1024; i++)
         token[i]=(char *)malloc(1024 * sizeof(char));
	char* temp=malloc(sizeof(char) * 1024);

	if(getcwd(home, len)==NULL)// gets the current working directory in variable home
	{
		printf ("Can not get present working directory\n");//if getcwd couldnt get the present working directory
	}

	while(1)
	{
		printf("%s>",dir);
		fgets(input,length,stdin);//scanning the input stream
		i=0;
		token[0]=strtok(input," \t\n\v\f\r");//split the input stream into separate words
		while(token[i]!=NULL)
		{
				i++;
				token[i]=strtok(NULL, " \t\n\v\f\r");
		}
		token[i+1]=NULL;

		pid_t pID = waitpid(p,NULL,WNOHANG);
		while(pID > 0)
		{
			 printf("Background-Process %d has exited\n",pID);
			 pID = 0;
		}

		if(!strcmp(token[0],"kjob"))
		{
			kjob_func(token);
		}

    if(!strcmp(token[0],"jobs"))
		{
			jobs_func(token);
		}

		if(!strcmp(token[0],"overkill"))
		{
			overkill_func(token);
		}

		if(!strcmp(token[0], "pwd"))
	  {
			pwd_func(home);
		}

		else if(!strcmp(token[0], "echo"))
		{
			echo_func(token);
		}

		else if(!strcmp(token[0], "cd"))
		{
			flag=cd_func(token,flag,home,prev_dir,temp,dir,home_dir);
		}

		else if(!strcmp(token[0], "ls"))
		{
			ls_func(token);
		}

		else if(!strcmp(token[0], "pinfo"))
		{
			pinfo_func(token);
		}

		else if(!strcmp(token[0], "setenv"))
		{
			//printf("Will execute setenv\n");
			setenv_func(token);
		}

		else if(!strcmp(token[0], "unsetenv"))
		{
			//printf("Will execute setenv\n");
			unsetenv_func(token);
		}

		else if(!strcmp(token[0],"fg"))
		{
			fg_func(token);
		}

    else if(!strcmp(token[0],"bg"))
		{
			bg_func(token);
		}

		else if(!strcmp(token[0],"quit"))
		{
			exit(0);
		}

		else
		{
			p=process_func(token, input);
		}
	}
  void handler(int sig)
{
        int pid = getpid();
        kill(pid,SIGTSTP);
        return;
}
	return 0;
}
