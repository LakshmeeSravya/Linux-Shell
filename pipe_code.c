void pipe_func(char** temp)
{
  int fd[2],in,out;
  char* arr[1024];//args
	for (i=0;i<1024;i++)
         arr[i]=(char *)malloc(1024*sizeof(char));

	char* arr2[1024];
	for (i=0;i<1024;i++)
				arr2[i]=(char *)malloc(1024*sizeof(char));

  int i=0,j=0,ff=0;
  while(temp[i])
  {
    strcpy(arr[i],temp[i]);
    i++;
  }
  arr[i]=NULL;

  i=0;
  int pid=fork(),pid2;
  if(pid==0)
  {
    while(temp[i])
    {
      if(strcmp(arr[i],"|")==0)
      {
        ff=1;
      }

      if(ff==0)
      {
        strcpy(arr2[j],arr[i]);
        //printf("%s\n", arr[j]);
        j++;
      }
      else
      {
        arr2[j]=NULL;
        pipe(fd);
        out=fd[1];
        dup2(out,1);
        pid2=fork();
        if(pid2==0)
        {
          execvp(arr2[0],arr2);
        }
        else
          wait(NULL);
        close(fd[1]);

        in=fd[0];
        j=0;
        ff=0;
      }
      i++;
    }

    dup2(in,0);
    execvp(arr2[0],arr2);
  }
  else
    wait(NULL);
}
