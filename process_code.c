#include"redirect_code.c"
#include"pipe_code.c"

char *joblist[1024];
int jobpid[1024], n=0, job_id, signal_no, i, status;

int process_func(char** token, char*input)
{
	for (i=0; i<1024; i++)
       joblist[i]=(char *)malloc(1024 * sizeof(char));
	int l=0;
	int f1=0,f2=0;
	pid_t pid;
	char* temp[1024];
	for (i=0;i<1024;i++)
         temp[i]=(char *)malloc(1024*sizeof(char));

	int pid_child;

	while(token[l])
	{
		strcpy(temp[l],token[l]);
		l++;

		if(!strcmp(temp[l-1],"<") || !strcmp(temp[l-1],">") || !strcmp(temp[l-1],">>"))
		{
				f1=1;
		}
		else if(!strcmp(temp[l-1],"|"))
		{
			f2=1;
		}
	}
	temp[l]=NULL;

	if(!f1 && !f2)
	{
		if(!strcmp(token[l-1],"&"))
		{
			if((pid=fork())!=0)
			{
        strcpy(joblist[n],token[0]);
        joblist[n][strlen(token[0])]='\0';
        //printf("%s should be printed...\n",joblist[n]);
        jobpid[n]=pid;
        n = n+1;
				//printf("forking child process failed\n");
				//exit(0);
			}
			else if(pid==0)
			{
				execvp(token[0], token);
			}
		}
		else
		{
			if((pid=fork())<0)
			{
				printf("forking child process failed\n");
				exit(0);
			}
			else if(pid==0) //child process
			{
				signal(SIGTSTP,SIG_IGN);

                                        waitpid(pid,&status,WUNTRACED);
                                        if(WSTOPSIG(status) == 18 || WSTOPSIG(status) == 20 || WSTOPSIG(status) == 24)
                                        {
                                                jobpid[n]=pid;
                                                strcpy(joblist[n],input);
                                                joblist[n][strlen(input)]='\0';
                                                jobpid[n]=pid;
                                                n++;
                                        }
				if(execvp(token[0],token)<0)
				{
					printf("exec failed\n");
					exit(0);
				}
			}
			else
			{
				while(wait(0)!=pid);      //wait for completion
				printf("%s with pid %d exited normally\n",token[0],pid);
			}
		}
		return pid_child;
	}
	else if(f2)
	{
		pipe_func(temp);
	}
	else
	{
		redirect_func(temp);
	}
}

int kjob_func(char**token)
{
  job_id = atoi(token[1]);
  signal_no = atoi(token[2]);
  kill(jobpid[job_id-1],signal_no);
}

int overkill_func(char**token)
{
  int pid;
  if(n==0)
  {
    printf("No background jobs!");
  }
  else
  {
    for(i=0;i<n;i++)
    {
      kill(jobpid[i], 9);
    }
    n=0;
  }
}

int fg_func(char**token)
{
  job_id = atoi(token[1]);
  kill(jobpid[job_id-1],SIGCONT);
  waitpid(jobpid[job_id],&status,WUNTRACED);
}
int bg_func(char**token)
{
	job_id = atoi(token[1]);
  kill(jobpid[job_id-1],SIGCONT);
}
int jobs_func(char**token)
{
	char buffer1[256];
					FILE *fd1;
					char state;

					for(i=1;i<=n;i++)
					{
									printf("[%d]       %s[%d]",i,joblist[i-1],jobpid[i-1]);
									sprintf(buffer1,"/proc/%d/stat",jobpid[i-1]);
									fd1 = fopen(buffer1,"r");
									fscanf(fd1,"%*d %*s %c",&state);
									//printf("c=%c",state);
									if(state =='S')
									printf("      Running\n");
									else if(state == 'Z' || state == 'T')
									printf("      Stopped\n");

					}
}
