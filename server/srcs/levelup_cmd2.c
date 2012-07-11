/*
** levelup_cmd2.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Thu Jun 21 18:10:06 2012 lois burg
** Last update Wed Jul 11 11:02:12 2012 lois burg
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "graphics.h"
#include "cmds.h"
#include "protocol.h"

extern t_infos	g_info;

void	check_end_game(t_users *p)
{
  /* p->lvl = MAX_LVL; */
  if (p->lvl == MAX_LVL)
    {
      ++p->team->nb_max_lvl;
      /* p->team->nb_max_lvl = NB_PLYR_MAX_LVL; */
      if (p->team->nb_max_lvl == NB_PLYR_MAX_LVL)
	{
	  g_info.end_game = true;
	  g_info.winner = p->team;
	}
    }
}

void		levelup_engaged(const int x, const int y, const int lvl)
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
	    push_back(plyr->messages,
		      new_link_by_param(LEVELUP_ENGAGED,
					sizeof(LEVELUP_ENGAGED) + 1));
	}
      ++i;
    }
}

void	send_world(void)
{
  uint	x;
  uint	y;

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
  char		lvlup_msg[END_LEVELUP_MSG_SZ];

  i = 0;
  snprintf(lvlup_msg, sizeof(lvlup_msg), "niveau actuel : %d\n", lvl);
  while (i < g_info.users->size)
    {
      if ((plyr_lnk = get_link(g_info.users, i)))
	{
	  plyr = (t_users*)plyr_lnk->ptr;
	  if (plyr->x == x && plyr->y == y && plyr->lvl == lvl)
	    {
	      push_back(plyr->messages,
			new_link_by_param(lvlup_msg, strlen(lvlup_msg) + 1));
	      lookup(g_info.users, graphics_plv(plyr), &notify_graphic);
	    }
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
