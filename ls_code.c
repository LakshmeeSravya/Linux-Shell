char date[255];
struct passwd *pwd;
struct tm  *tm;
struct group *grp;

int ls_func(char** token)
{
  struct stat s;
  if(token[1]==NULL)
  {
    char *pointer=malloc(sizeof(char)*1024);
    DIR *dp=NULL; // represents a directory stream
    struct dirent *sd=NULL;//describes a directory entry
    getcwd(pointer,length);//gets the current working directory
    dp=opendir((const char*)pointer);//opens the dir and returns the pointer to the dir stream
    while((sd=readdir(dp))!=NULL)//returns a pointer to dp
    {
      if(!( strcmp(sd->d_name,".") == 0 || strcmp(sd->d_name,"..") == 0 ))
        printf("%s  \t ",sd->d_name);
    }
    closedir(dp);
    printf("\n");
  }
  else if (!strcmp(token[1], "-l"))
  {
    char *pointer=malloc(sizeof(char)*1024);// represents a directory stream
    DIR *dp=NULL;
    struct dirent *sd=NULL;
    getcwd(pointer,length);
    dp=opendir((const char*)pointer);//opens the dir and returns the pointer to the dir stream
    while((sd=readdir(dp))!=NULL)
    {
      if(!( strcmp(sd->d_name,".") == 0 || strcmp(sd->d_name,"..") == 0 ))
      {
        if(stat(sd->d_name, &s)==-1)
          continue;
        (S_ISDIR(s.st_mode)) ? printf("d") : printf(" ");
        (S_IRUSR & s.st_mode) ? printf("r") : printf("-");
        (S_IWUSR & s.st_mode) ? printf("w") : printf("-");
        (S_IXUSR & s.st_mode) ? printf("x") : printf("-");
        (S_IRGRP & s.st_mode) ? printf("r") : printf("-");
        (S_IRGRP & s.st_mode) ? printf("r") : printf("-");
        (S_IRGRP & s.st_mode) ? printf("r") : printf("-");
        (S_IWGRP & s.st_mode) ? printf("w") : printf("-");
        (S_IXGRP & s.st_mode) ? printf("x") : printf("-");
        (S_IROTH & s.st_mode) ? printf("r") : printf("-");
        (S_IWOTH & s.st_mode) ? printf("w") : printf("-");
        (S_IXOTH & s.st_mode) ? printf("x") : printf("-");
        if((pwd=getpwuid(s.st_uid))!=NULL)
          printf(" %-8.8s", pwd->pw_name);
        else
          printf(" %-8d", s.st_uid);
        if((grp=getgrgid(s.st_gid))!=NULL)
          printf(" %-8.8s", grp->gr_name);
        else
          printf(" %-8d", s.st_gid);
        printf(" %9jd ", (intmax_t)s.st_size);

        tm = localtime(&s.st_mtime);
        strftime(date, sizeof(date), nl_langinfo(D_T_FMT), tm);
        printf("%s ", date);
        printf(" %d ", sd->d_type);
        printf("%s \n", sd->d_name);
      }
    }
    closedir(dp);
  }
  else if(!strcmp(token[1], "-a"))
  {
    char *pointer=malloc(sizeof(char)*1024);
    DIR *dp=NULL; // represents a directory stream
    struct dirent *sd=NULL;
    getcwd(pointer,length);
    dp=opendir((const char*)pointer);//opens the dir and returns the pointer to the dir stream
    while((sd=readdir(dp))!=NULL)
    {
      printf("%s  \t ",sd->d_name);
    }
    closedir(dp);
    printf("\n");
  }
  else if(!strcmp(token[1],"-al") || !strcmp(token[1],"-la")||!strcmp(token[1],"-a-l") || !strcmp(token[1],"-l-a") || (!strcmp(token[1],"-l") && !strcmp(token[2],"-a"))
   || (!strcmp(token[1],"-a") && !strcmp(token[2],"-l")))
  {
    char *pointer=malloc(sizeof(char)*1024);
    DIR *dp=NULL; // represents a directory stream
    struct dirent *sd=NULL;
    getcwd(pointer,length);
    dp=opendir((const char*)pointer);//opens the dir and returns the pointer to the dir stream
    while((sd=readdir(dp))!=NULL)
    {
      if(stat(sd->d_name, &s)==-1)
        continue;
      (S_ISDIR(s.st_mode)) ? printf("d") : printf(" ");
      (S_IRUSR & s.st_mode) ? printf("r") : printf("-");
      (S_IWUSR & s.st_mode) ? printf("w") : printf("-");
      (S_IXUSR & s.st_mode) ? printf("x") : printf("-");
      (S_IRGRP & s.st_mode) ? printf("r") : printf("-");
      (S_IRGRP & s.st_mode) ? printf("r") : printf("-");
      (S_IRGRP & s.st_mode) ? printf("r") : printf("-");
      (S_IWGRP & s.st_mode) ? printf("w") : printf("-");
      (S_IXGRP & s.st_mode) ? printf("x") : printf("-");
      (S_IROTH & s.st_mode) ? printf("r") : printf("-");
      (S_IWOTH & s.st_mode) ? printf("w") : printf("-");
      (S_IXOTH & s.st_mode) ? printf("x") : printf("-");
      if((pwd=getpwuid(s.st_uid))!=NULL)
        printf(" %-8.8s", pwd->pw_name);
      else
        printf(" %-8d", s.st_uid);
      if((grp=getgrgid(s.st_gid))!=NULL)
        printf(" %-8.8s", grp->gr_name);
      else
        printf(" %-8d", s.st_gid);
      printf(" %9jd ", (intmax_t)s.st_size);

      tm = localtime(&s.st_mtime);
      strftime(date, sizeof(date), nl_langinfo(D_T_FMT), tm);
      printf("%s ", date);
      printf(" %d ", sd->d_type);
      printf("%s \n", sd->d_name);
    }
    closedir(dp);
  }
}
