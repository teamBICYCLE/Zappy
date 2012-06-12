/*
** actions.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Tue Jun 12 16:18:42 2012 lois burg
** Last update Tue Jun 12 17:17:22 2012 lois burg
*/

#include <stdio.h>
#include <string.h>
#include "cmds.h"
#include "server.h"

extern t_infos	g_info;

/* static void	see_lvl(const int usr_x, const int usr_y, */
/* 			const int lvl, const t_map *map) */
/* { */
/*   int		x; */
/*   int		y; */

/*   y = */
/* } */

void		see_cmd(t_users *usr, char **args)
{
  int		i;
  /* const t_map	*map = g_info.map; */

  (void)args;
  i = 0;
  while (usr && i <= usr->lvl)
    {
      /* see_lvl(usr->x, usr->y, usr->lvl); */
      ++i;
    }
}

void	inventory_cmd(t_users *usr, char **args)
{
  int	i;
  char	*res_str;
  char	val[INVENTORY_VAL_SZ];
  char	msg[INVENTORY_MSG_SZ];

  (void)args;
  i = 0;
  memset(msg, 0, sizeof(msg));
  strcat(msg, "{");
  while (i < LAST)
    {
      if ((res_str = map_ressource(i)))
	{
	  strcat(msg, res_str);
	  memset(val, 0, sizeof(val));
	  sprintf(val, "%d", usr->inventory[i]);
	  strcat(msg, val);
	}
      ++i;
      if (i < LAST)
	strcat(msg, ", ");
    }
  strcat(msg, "}\n");
  printf("Inventory: %s", msg);
  push_back(usr->messages, new_link_by_param(msg, strlen(msg)));
}
