/*
** graphic_utils2.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Thu Jul 12 15:39:10 2012 lois burg
** Last update Thu Jul 12 15:43:31 2012 lois burg
*/

#include <string.h>
#include "graphics.h"
#include "server.h"

char	*send_ghost(t_users *plyr, t_users *monitor)
{
  char	*msg;

  msg = graphics_enw(plyr);
  push_back(monitor->messages, new_link_by_param(msg, strlen(msg) + 1));
  msg = graphics_eht(plyr->id);
  return (msg);
}
