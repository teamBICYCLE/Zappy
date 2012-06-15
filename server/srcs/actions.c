/*
** actions.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Tue Jun 12 16:18:42 2012 lois burg
** Last update Thu Jun 14 15:46:02 2012 lois burg
*/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "cmds.h"
#include "server.h"
#include "log.h"

extern t_infos	g_info;
extern char	*g_res_names[LAST];

static t_see_pair	g_see_tab[5] =
  {
    {&see_count_north, &see_north},
    {&see_count_east, &see_east},
    {&see_count_south, &see_south},
    {&see_count_west, &see_west}
  };

bool		see_cmd(t_users *usr, char **args)
{
  bool		success;
  const t_map	*map = g_info.map;
  char		*content;

  (void)args;
  success = true;
  if ((content = calloc((g_see_tab[usr->dir].cf)(usr->x, usr->y, usr->lvl, map),
			sizeof(*content))))
    {
      strcat(content, "{");
      (g_see_tab[usr->dir].f)(usr, content, map);
      strcat(content, "}\n");
      push_back(usr->messages, new_link_by_param(content, strlen(content) + 1));
    }
  else
    success = false;
  free(content);
  return (success);
}

bool	inventory_cmd(t_users *usr, char **args)
{
  int	i;
  char	val[INVENTORY_VAL_SZ];
  char	msg[INVENTORY_MSG_SZ];
  char	log[LOG_MSG_SZ];

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
  memset(log, 0, sizeof(log));
  snprintf(log, sizeof(log), "Inventory of user #%lu: %s", usr->idx, msg);
  log_msg(stdout, log);
  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
  return (true);
}
