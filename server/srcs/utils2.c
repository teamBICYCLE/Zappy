/*
** utils2.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Thu Jun  7 17:28:25 2012 lois burg
** Last update Wed Jun 13 18:22:12 2012 Jonathan Machado
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"

extern t_infos		g_info;

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
