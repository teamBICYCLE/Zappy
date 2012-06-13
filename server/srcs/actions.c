/*
** actions.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Tue Jun 12 16:18:42 2012 lois burg
** Last update Wed Jun 13 19:33:11 2012 lois burg
*/

#include <time.h>
#include <stdio.h>
#include <string.h>
#include "cmds.h"
#include "server.h"
#include "log.h"

extern t_infos	g_info;
extern char	*g_res_names[LAST];

static t_see_func	g_see_tab[5] =
  {
    &see_north,
    &see_east,
    &see_south,
    &see_west
  };

bool		see_cmd(t_users *usr, char **args)
{
  int		i;
  const t_map	*map = g_info.map;

  (void)args;
  i = 0;
  while (usr && i <= usr->lvl)
    {
      (g_see_tab[usr->dir])(usr->x, usr->y, i, map);
      ++i;
    }
  return (true);
}

bool	inventory_cmd(t_users *usr, char **args)
{
  int	i;
  char	val[INVENTORY_VAL_SZ];
  char	msg[INVENTORY_MSG_SZ];

  (void)args;
  i = 0;
  memset(msg, 0, sizeof(msg));
  strcat(msg, "{");
  while (i < NB_RESSOURCES)
    {
      if (i)
	strcat(msg, ", ");
      strcat(msg, g_res_names[i]);
      memset(val, 0, sizeof(val));
      sprintf(val, " %d", usr->inventory[i]);
      strcat(msg, val);
      ++i;
    }
  strcat(msg, "}\n");
  log_msg(stdout, msg);
  push_back(usr->messages, new_link_by_param(msg, strlen(msg)));
  return (true);
}
