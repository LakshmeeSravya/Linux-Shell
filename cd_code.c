char* get_parent_dir(char* dir)
{
	char* result;
	if ((result = malloc(sizeof(char) * 1024)) == NULL)
		return (NULL);
	int l=strlen(dir);
	int i;
	for(i=l-1;i>=0;i--)
	{
		if(dir[i]=='/')
			break;
	}
	int k;
	for(k=0;k<i;k++)
	{
		result[k]=dir[k];
	}
	result[k+1]='\0';
	return result;
}

int cd_func(char** token,int flag,char* home,char* prev_dir,char* temp,char* dir,char* home_dir)
{
  char* temp2=malloc(sizeof(char) * 1024);
  char* prev_dir2=malloc(sizeof(char) * 1024);
  strcpy(temp2,temp);
  strcpy(prev_dir2,prev_dir);
  getcwd(temp,len);
  strcpy(prev_dir,dir);

  if(token[1]==NULL || !strcmp(token[1],"~"))
  {
    chdir(home);
    strcpy(dir,home_dir);
  }

  else if(!strcmp(token[1],".."))
  {
    if(strcmp(dir,home)!=0)
    {
      chdir(get_parent_dir(temp));
      strcpy(dir,get_parent_dir(dir));
    }
  }

  else if(!strcmp(token[1],"-"))
  {
    if(flag)
    {
      chdir(temp2);
      strcpy(dir,prev_dir2);
      printf("/~");
      relative=remove_str(temp2,home);
      printf("%s\n",relative);
    }
    else
      printf(" cd: OLDPWD not set\n");
  }
  else
  {
    flag=chdir(token[1]);
    if(flag==0)
    {
      chdir(token[1]);
      strcat(dir,"/");
      strcat(dir,token[1]);
    }
  }
  flag=1;
  return flag;
}
