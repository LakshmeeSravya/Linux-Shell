void redirect_func(char **temp)
{
	int i,j,in,out,ff;
  char* arr[1024];//args
	for (i=0;i<1024;i++)
         arr[i]=(char *)malloc(1024*sizeof(char));

	char* arr2[1024];
	for (i=0;i<1024;i++)
				arr2[i]=(char *)malloc(1024*sizeof(char));

	i=0;
	while(temp[i])
	{
		strcpy(arr[i],temp[i]);
		i++;
	}
	arr[i]=NULL;

	int pid=fork();
	i=0;
	j=0;
	if(pid==0)
	{
	while(temp[i])
	{
		ff=0;
		if(strcmp(arr[i],">")==0)
		{
			out=open(arr[i+1], O_WRONLY| O_TRUNC | O_CREAT,0644);
			dup2(out,1);
			close(out);
			i++;
			ff=1;
		}

		else if(strcmp(arr[i],">>")==0)
		{
			out = open(arr[i+1], O_APPEND | O_RDWR | O_CREAT,0644);
			dup2(out,1);
			close(out);
			i++;
			ff=1;
		}

		else if(strcmp(arr[i],"<")==0)
		{
			in=open(arr[i+1],O_RDONLY);
			if(in==-1)
			{
				printf("%s does not exist\n", arr[i+1]);
				return;
			}
			dup2(in,0);
			close(in);
			i++;
			ff=1;
		}

		if(ff==0)
		{
			strcpy(arr2[j],arr[i]);
			j++;
		}
		i++;
	}
	arr2[j]=NULL;
	execvp(arr[0],arr2);
	}
	else
		wait(NULL);

	return;
}
