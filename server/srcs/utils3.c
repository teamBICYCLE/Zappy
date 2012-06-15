/*
** utils3.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Fri Jun 15 12:22:39 2012 lois burg
** Last update Fri Jun 15 12:23:51 2012 lois burg
*/

#include <string.h>

int	cmp_team(void *t1, void *t2)
{
  return (strcmp((const char*)t1, (const char *)t2));
}
