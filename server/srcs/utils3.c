/*
** utils3.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Fri Jun 15 12:22:39 2012 lois burg
** Last update Wed Jun 20 17:04:16 2012 lois burg
*/

#include <stdio.h>
#include <string.h>
#include "server.h"
#include "protocol.h"
#include "cmds.h"

int		cmp_team(void *t1, void *t2)
{
  const char	*name = ((t_team*)t1)->name;

  return (strcmp(name, (const char *)t2));
}

int	cmp_id(void *usr, void *id)
{
  return (!(((t_users*)usr)->id == *(int*)id));
}

void	send_ok_ko(t_users *usr, t_cmd_ret s)
{
  if (s != IGNORE)
    {
      if (s == SUCCESS)
	push_back(usr->messages, new_link_by_param(OK, sizeof(OK) + 1));
      else
	push_back(usr->messages, new_link_by_param(KO, sizeof(KO) + 1));
    }
}

void	greet_clnt(const t_users *usr, const int wx, const int wy)
{
  char	msg[GREETINGS_CLIENT_SZ];

  memset(msg, 0, sizeof(msg));
  snprintf(msg, sizeof(msg), "%d\n", usr->team->free_slots);
  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
  snprintf(msg, sizeof(msg), "%d %d\n", wx, wy);
  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
}
