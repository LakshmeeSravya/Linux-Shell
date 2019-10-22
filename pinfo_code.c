int pinfo_func(char** token)
{
  FILE *pointer;
  char f1[256],f2[256];
  int pid;
  char name[256],state;
  long unsigned int size;
  if(token[1]==NULL)
  {
    sprintf(f1,"/proc/%d/stat",getpid());//open the stat and exe files
    sprintf(f2,"/proc/%d/exe",getpid());
  }
  else
  {
    sprintf(f1,"/proc/%s/stat",token[1]);
    sprintf(f2,"/proc/%s/exe",token[1]);
  }
  if((pointer=fopen(f1,"r"))!=NULL)
  {
    /*scan the stat file*/
    fscanf(pointer,"%d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d",&pid,&state,&size);
    fclose(pointer);
    printf("pid -- %d\nProcess Status -- %c\nmemory -- %lu\n",pid,state,size);
    readlink(f2,name,256);
    printf("Executable Path -- %s\n",name);
  }
  else
    perror("No such process");
}
