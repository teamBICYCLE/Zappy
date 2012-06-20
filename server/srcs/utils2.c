/*
** utils2.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Thu Jun  7 17:28:25 2012 lois burg
** Last update Tue Jun 19 16:53:59 2012 lois burg
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "cmds.h"

extern char	*g_res_names[LAST];
extern t_infos	g_info;

static char	**pvt_parse(char *tok, size_t sz, const char *delim)
{
  char	**cmd;

  if (!tok)
    cmd = malloc((sz + 1) * sizeof(*cmd));
  else
    cmd = pvt_parse(strtok(NULL, delim), sz + 1, delim);
  cmd[sz] = tok;
  return (cmd);
}

char	**parse(char *str, const char *delim)
{
  return (pvt_parse(strtok(str, delim), 0, delim));
}

static void	set_fd(void *ptr)
{
  t_users	*user;

  user = ptr;
  FD_SET(user->socket, &g_info.writefds);
  FD_SET(user->socket, &g_info.readfds);
}

void	reset_fd(t_infos *info)
{
  FD_ZERO(&info->writefds);
  FD_ZERO(&info->readfds);
  FD_SET(info->ss, &info->readfds);
  iterate(info->users, &set_fd);
}

size_t	case_content_sz(const t_case *c)
{
  int		i;
  uint		j;
  size_t	sz;

  sz = 0;
  i = 0;
  while (i < LAST)
    {
      j = 0;
      sz += 1;
      while (j < c->elements[i])
	{
	  sz += strlen(g_res_names[i]) + 1;
	  ++j;
	}
      ++i;
    }
  sz += 2;
  return (sz);
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
