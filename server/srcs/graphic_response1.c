/*
** graphic_response1.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Fri Jun 15 18:26:54 2012 lois burg
** Last update Fri Jun 15 19:02:38 2012 lois burg
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "graphics.h"

extern	t_infos	g_info;

char		*graphics_msz(void)
{
  static char	msg[GRAPHICS_MSG_SZ];

  memset(msg, 0, sizeof(msg));
  snprintf(msg, sizeof(msg), "msz %d %d\n", g_info.world.x, g_info.world.y);
  return (msg);
}

char		*graphics_bct(const int x, const int y)
{
  int		i;
  int		idx;
  static char	msg[GRAPHICS_MSG_SZ];

  memset(msg, 0, sizeof(msg));
  idx = snprintf(msg, sizeof(msg), "bct %d %d", x, y);
  i = 0;
  while (i < NB_RESSOURCES)
    {
      idx += snprintf(msg + idx, sizeof(msg + idx), " %d",
		      g_info.map->cases[y][x].elements[i]);
      ++i;
    }
  snprintf(msg + idx, sizeof(msg + idx), "\n");
  return (msg);
}

char		*graphics_tna(void)
{
  uint		i;
  int		idx;
  t_link	*team;
  static char	msg[GRAPHICS_MSG_SZ];

  memset(msg, 0, sizeof(msg));
  i = 0;
  idx = 0;
  while (i < g_info.world.teams_names->size)
    {
      if ((team = get_link(g_info.world.teams_names, i)))
	idx += snprintf(msg + idx, sizeof(msg + idx), "tna %s\n",
			(char*)team->ptr);
      ++i;
    }
  return (msg);
}

char		*graphics_pnw(t_users *usr)
{
  static char	msg[GRAPHICS_MSG_SZ];

  memset(msg, 0, sizeof(msg));
  snprintf(msg, sizeof(msg), "pnw #%d %d %d %d %d [TEAM A AJOUTER]\n",
	   usr->id, usr->x, usr->y, usr->dir, usr->lvl/* , usr->team */);
  return (msg);
}

char		*graphics_ppo(t_users *usr)
{
  static char	msg[GRAPHICS_MSG_SZ];

  memset(msg, 0, sizeof(msg));
  snprintf(msg, sizeof(msg), "ppo #%d %d %d %d\n",
	   usr->id, usr->x, usr->y, usr->dir);
  return (msg);
}
