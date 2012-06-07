/*
** utils2.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Thu Jun  7 17:28:25 2012 lois burg
** Last update Thu Jun  7 17:32:32 2012 lois burg
*/

#include <stdlib.h>
#include <string.h>

static char	**pvt_parse(char *str, char *tok, size_t sz, const char *delim)
{
  char	**cmd;

  if (!tok)
    cmd = malloc((sz + 1) * sizeof(*cmd));
  else
    cmd = pvt_parse(str, strtok(NULL, delim), sz + 1, delim);
  cmd[sz] = tok;
  return (cmd);
}

char	**parse(char *str, const char *delim)
{
  return (pvt_parse(str, strtok(str, delim), 0, delim));
}
