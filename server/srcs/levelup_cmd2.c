/*
** levelup_cmd2.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Thu Jun 21 18:10:06 2012 lois burg
** Last update Thu Jun 21 18:24:27 2012 lois burg
*/

#include "server.h"
#include "graphics.h"

extern t_infos	g_info;

static void	send_world(void)
{
  uint		x;
  uint		y;

  y = 0;
  while (y < g_info.map->y)
    {
      x = 0;
      while (x < g_info.map->x)
	{
	  lookup(g_info.users, graphics_bct(x, y), &notify_graphic);
	  ++x;
	}
      ++y;
    }
}

static void	send_plyr_lvl(const int x, const int y, const int lvl)
{
  uint		i;
  t_users	*plyr;
  t_link	*plyr_lnk;

  i = 0;
  while (i < g_info.users->size)
    {
      if ((plyr_lnk = get_link(g_info.users, i)))
	{
	  plyr = (t_users*)plyr_lnk->ptr;
	  if (plyr->x == x && plyr->y == y && plyr->lvl == lvl)
	    lookup(g_info.users, graphics_plv(plyr), &notify_graphic);
	}
      ++i;
    }
}

void	send_graphic_result(t_users *usr, const int success)
{
  lookup(g_info.users, graphics_pie(usr->x, usr->y, success), &notify_graphic);
  send_plyr_lvl(usr->x, usr->y, usr->lvl);
  send_world();
}
