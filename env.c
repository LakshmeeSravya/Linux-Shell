int setenv_func(char** token)
{
  setenv(token[1], token[2], 1);
}

int unsetenv_func(char** token)
{
  unsetenv(token[1]);
}
