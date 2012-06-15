/*
** graphic_utils.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Fri Jun 15 18:02:40 2012 lois burg
** Last update Fri Jun 15 18:48:03 2012 lois burg
*/

#include <string.h>
#include "server.h"

int	notify_graphic(void *usr, void *msg)
{
  if (((t_users*)usr)->is_graphics)
    push_back(((t_users*)usr)->messages,
	      new_link_by_param(msg, strlen((const char *)msg) + 1));
  return (1);
}
