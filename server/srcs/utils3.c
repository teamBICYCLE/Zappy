/*
** utils3.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Fri Jun 15 12:22:39 2012 lois burg
** Last update Mon Jun 18 14:31:14 2012 lois burg
*/

#include <string.h>
#include "server.h"
#include "protocol.h"

int		cmp_team(void *t1, void *t2)
{
  const char	*name = ((t_team*)t1)->name;

  return (strcmp(name, (const char *)t2));
}

int	cmp_id(void *usr, void *id)
{
  return (!(((t_users*)usr)->id == *(int*)id));
}

void	send_ok_ko(t_users *usr, bool s)
{
  if (s)
    push_back(usr->messages, new_link_by_param(OK, sizeof(OK) + 1));
  else
    push_back(usr->messages, new_link_by_param(KO, sizeof(KO) + 1));
}
