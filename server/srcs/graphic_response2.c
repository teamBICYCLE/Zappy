/*
** graphic_response2.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Sat Jun 16 11:43:52 2012 lois burg
** Last update Sat Jun 16 19:27:25 2012 lois burg
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "graphics.h"

extern	t_infos	g_info;

char	*graphics_plv(t_users *usr)
{
  char	*msg;

  msg = get_graphics_buf();
  snprintf(msg, GRAPHICS_MSG_SZ, "plv %d %d\n", usr->id, usr->lvl);
  return (msg);
}

char	*graphics_pin(t_users *usr)
{
  int	i;
  int	idx;
  char	*msg;

  msg = get_graphics_buf();
  idx = snprintf(msg, GRAPHICS_MSG_SZ, "pin %d %d %d", usr->id, usr->x, usr->y);
  i = 0;
  while (i < NB_RESSOURCES)
    {
      idx += snprintf(msg + idx, GRAPHICS_MSG_SZ - idx, " %d", usr->inventory[i]);
      ++i;
    }
  snprintf(msg + idx, GRAPHICS_MSG_SZ - idx, "\n");
  return (msg);
}

char	*graphics_pex(t_users *usr)
{
  char	*msg;

  msg = get_graphics_buf();
  snprintf(msg, GRAPHICS_MSG_SZ, "pex %d\n", usr->id);
  return (msg);
}

char	*graphics_pbc(t_users *usr, const char *broadcast)
{
  char	*msg;

  msg = get_graphics_buf();
  snprintf(msg, GRAPHICS_MSG_SZ, "pbc %d %s\n", usr->id, broadcast);
  return (msg);
}

char		*graphics_pic(t_users *usr)
{
  uint		i;
  int		idx;
  t_link	*plyr;
  char		*msg;

  msg = get_graphics_buf();
  idx = snprintf(msg, GRAPHICS_MSG_SZ, "pic %d %d %d %d\n",
		 usr->x, usr->y, usr->lvl, usr->id);
  i = 0;
  while (i < g_info.users->size)
    {
      if ((plyr = get_link(g_info.users, i)) &&
	  ((t_users*)plyr->ptr)->x == usr->x &&
	  ((t_users*)plyr->ptr)->y == usr->y)
	idx += snprintf(msg + idx, GRAPHICS_MSG_SZ - idx, " %d",
			((t_users*)plyr->ptr)->id);
      ++i;
    }
  snprintf(msg + idx, GRAPHICS_MSG_SZ - idx, "\n");
  return (msg);
}
