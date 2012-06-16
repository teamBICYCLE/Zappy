/*
** movement.c for  in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Thu Jun 14 13:38:06 2012 Jonathan Machado
** Last update Sat Jun 16 12:51:02 2012 lois burg
*/

#include <string.h>
#include "server.h"

extern char	*g_res_names[LAST];
extern t_infos	g_info;

bool	left_cmd(t_users *u, char **args)
{
  (void)args;
  --u->dir;
  if (u->dir == UNDEF)
    u->dir = WEST;
  return (true);
}

bool	right_cmd(t_users *u, char **args)
{
  (void)args;
  ++u->dir;
  u->dir %= WEST + 1;
  return (true);
}

bool	put_cmd(t_users *u, char **args)
{
  int	i;

  i = 0;
  if (args[1] != NULL)
    {
      while (strcmp(args[1], g_res_names[i]) != 0 && i < LAST)
	++i;
      if (i < LAST && u->inventory[i] > 0)
	{
	  --u->inventory[i];
	  ++g_info.map->cases[u->y][u->x].elements[i];
	  return (true);
	}
    }
  return (false);
}
