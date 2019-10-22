int i,j;
int echo_func(char** token)
{
  i=1;
  while(token[i]!=NULL)
  {
    if(token[i][0]=='"')//if the parametr for echo is withinn quotes
    {                //print everything within quotes
      for(j=1;j<strlen(token[i])-1;j++)
        printf("%c",token[i][j]);
    }
    else
    {
      printf("%s",token[i]);//if echo has a single paramter without quotes
    }
    printf(" ");
    i++;
  }
  printf("\n");
}
