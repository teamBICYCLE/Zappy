/*
** utils2.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Thu Jun  7 17:28:25 2012 lois burg
** Last update Wed Jun 13 19:05:06 2012 lois burg
*/

#include <stdlib.h>
#include <string.h>
#include "cmds.h"

extern char	*g_res_names[LAST];

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

char	*case_content(const t_case *c, char *buf)
{
  int	i;
  uint	j;

  i = 0;
  while (i < LAST)
    {
      j = 0;
      while (j < c->elements[i])
	{
	  strcat(buf, " ");
	  strcat(buf, g_res_names[i]);
	  ++j;
	}
      ++i;
    }
  return (buf);
}
