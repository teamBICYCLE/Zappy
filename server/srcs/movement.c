/*
** movement.c for  in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Thu Jun 14 13:38:06 2012 Jonathan Machado
** Last update Sun Jun 17 16:36:39 2012 lois burg
*/

#include <string.h>
#include "graphics.h"
#include "server.h"

extern char	*g_res_names[LAST];
extern t_infos	g_info;

bool	left_cmd(t_users *u, char **args)
{
  (void)args;
  --u->dir;
  if (u->dir == UNDEF)
    u->dir = WEST;
  lookup(g_info.users, graphics_ppo(u), &notify_graphic);
  return (true);
}

bool	right_cmd(t_users *u, char **args)
{
  (void)args;
  ++u->dir;
  u->dir %= WEST + 1;
  lookup(g_info.users, graphics_ppo(u), &notify_graphic);
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
	  lookup(g_info.users, graphics_pdr(u, i), &notify_graphic);
	  lookup(g_info.users, graphics_pin(u), &notify_graphic);
	  lookup(g_info.users, graphics_bct(u->x, u->y), &notify_graphic);
	  return (true);
	}
    }
  return (false);
}
