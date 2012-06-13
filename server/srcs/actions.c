/*
** actions.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Tue Jun 12 16:18:42 2012 lois burg
** Last update Wed Jun 13 18:58:40 2012 Jonathan Machado
*/

#include <time.h>
#include <stdio.h>
#include <string.h>
#include "cmds.h"
#include "server.h"
#include "log.h"

extern t_infos	g_info;

bool		see_cmd(t_users *usr, char **args)
{
  int		i;
  const t_map	*map = g_info.map;

  (void)args;
  i = 0;
  while (usr && i <= usr->lvl)
    {
      see_lvl(usr, i, map);
      ++i;
    }
  return (true);
}

bool	inventory_cmd(t_users *usr, char **args)
{
  int	i;
  char	*res_str;
  char	val[INVENTORY_VAL_SZ];
  char	msg[INVENTORY_MSG_SZ];

  (void)args;
  i = 0;
  memset(msg, 0, sizeof(msg));
  strcat(msg, "{");
  while (i < NB_RESSOURCES)
    {
      if ((res_str = map_ressource(i)))
	{
	  if (i)
	    strcat(msg, ", ");
	  strcat(msg, res_str);
	  memset(val, 0, sizeof(val));
	  sprintf(val, " %d", usr->inventory[i]);
	  strcat(msg, val);
	}
      ++i;
    }
  strcat(msg, "}\n");
  log_msg(stdout, msg);
  push_back(usr->messages, new_link_by_param(msg, strlen(msg)));
  return (true);
}
