/*
** graphic_utils.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Fri Jun 15 18:02:40 2012 lois burg
** Last update Thu Jun 21 18:14:17 2012 lois burg
*/

#include <string.h>
#include "server.h"
#include "graphics.h"

extern t_infos	g_info;

int	notify_graphic(void *usr, void *msg)
{
  if (((t_users*)usr)->type == TGRAPHICS)
    push_back(((t_users*)usr)->messages,
	      new_link_by_param(msg, strlen((const char *)msg) + 1));
  return (1);
}

char		*get_graphics_buf(void)
{
  static char	msg[GRAPHICS_MSG_SZ];

  memset(msg, 0, sizeof(msg));
  return (msg);
}

static void	send_world(t_users *usr)
{
  uint		x;
  uint		y;
  char		*msg;

  y = 0;
  while (y < g_info.map->y)
    {
      x = 0;
      while (x < g_info.map->x)
	{
	  msg = graphics_bct(x, y);
	  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
	  ++x;
	}
      ++y;
    }
}

static void	send_players(t_users *usr)
{
  uint		i;
  char		*msg;
  t_link	*plyr_lnk;
  t_users	*plyr;

  i = 0;
  while (i < g_info.users->size)
    {
      if ((plyr_lnk = get_link(g_info.users, i)))
	{
	  plyr = (t_users*)plyr_lnk->ptr;
	  if (plyr->team)
	    {
	      if (plyr->type == TEGG)
		msg = graphics_enw(plyr);
	      else if (plyr->type != TGRAPHICS)
		msg = graphics_pnw(plyr);
	      push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
	    }
	}
      ++i;
    }
}

void	greet_graphics(t_users *usr)
{
  char	*msg;

  msg = graphics_msz();
  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
  msg = graphics_sgt();
  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
  send_world(usr);
  msg = graphics_tna();
  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
  send_players(usr);
}
