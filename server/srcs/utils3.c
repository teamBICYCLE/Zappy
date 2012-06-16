/*
** utils3.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Fri Jun 15 12:22:39 2012 lois burg
** Last update Sat Jun 16 19:22:07 2012 lois burg
*/

#include <string.h>
#include "server.h"

int	cmp_team(void *t1, void *t2)
{
  return (strcmp((const char*)t1, (const char *)t2));
}

int	cmp_id(void *usr, void *id)
{
  return (!(((t_users*)usr)->id == *(int*)id));
}
