char cwd[1024];
char* relative;

char *remove_str(char *str1,char *str2)
{
	int i;
	char *result;
	if ((result = malloc(sizeof(char) * 1024)) == NULL)
		return (NULL);
	int str1len=strlen(str1);
	int str2len=strlen(str2);
	int j=0;
	for(i=str2len;i<str1len;i++)
	{
		result[j]=str1[i];
		j++;
	}
	result[j]='\0';
	return result;
}

int pwd_func(char* home)
{
	if(getcwd(cwd, 1024)==NULL)
	{
		printf ("Can not get present working directory\n");
	}
	else
	{
		printf("/~");
		relative = remove_str(cwd, home);//gets the relative path of the present directory
		printf("%s\n",relative);
	}
	return 1;
}
