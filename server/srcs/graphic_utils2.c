/*
** graphic_utils2.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Thu Jul 12 15:39:10 2012 lois burg
** Last update Sun Jul 15 12:17:43 2012 lois burg
*/

#include <stdlib.h>
#include <string.h>
#include "graphics.h"
#include "server.h"

extern t_infos	g_info;

char	*send_ghost(t_users *plyr, t_users *monitor)
{
  char	*msg;

  msg = graphics_enw(plyr);
  push_back(monitor->messages, new_link_by_param(msg, strlen(msg) + 1));
  msg = graphics_eht(plyr->id);
  return (msg);
}

int	set_case_content(const uint x, const uint y, char **args)
{
  int	i;

  i = 2;
  while (x < g_info.map->x && y < g_info.map->y &&
	 args[i] && contains_only_digits(args[i]))
    {
      g_info.map->cases[y][x].elements[i - 2] = strtol(args[i], NULL, 10);
      ++i;
    }
  return (i);
}
