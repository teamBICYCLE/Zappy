/*
** movement.c for  in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Thu Jun 14 13:38:06 2012 Jonathan Machado
** Last update Tue Jun 19 15:30:21 2012 lois burg
*/

#include <string.h>
#include "graphics.h"
#include "server.h"
#include "cmds.h"

extern char	*g_res_names[LAST];
extern t_infos	g_info;

t_cmd_ret	left_cmd(t_users *u, char **args)
{
  (void)args;
  --u->dir;
  if (u->dir == UNDEF)
    u->dir = WEST;
  lookup(g_info.users, graphics_ppo(u), &notify_graphic);
  return (SUCCESS);
}

t_cmd_ret	right_cmd(t_users *u, char **args)
{
  (void)args;
  ++u->dir;
  u->dir %= WEST + 1;
  lookup(g_info.users, graphics_ppo(u), &notify_graphic);
  return (SUCCESS);
}

t_cmd_ret	forward_cmd(t_users *u, char **args)
{
  int		dx;
  int		dy;

  (void)args;
  dx = 0;
  dy = 0;
  if (u->dir == NORTH || u->dir == SOUTH)
    {
      if (u->dir == NORTH)
	dy = -1;
      else
	dy = 1;
    }
  else
    {
      if (u->dir == EAST)
	dx = 1;
      else
	dx = 1;
    }
  u->x = ((u->x + dx) + g_info.map->x) % g_info.map->x;
  u->y = ((u->y + dy) + g_info.map->y) % g_info.map->y;
  return (SUCCESS);
}

t_cmd_ret	put_cmd(t_users *u, char **args)
{
  int		i;

  i = 0;
  if (args != NULL && args[0] != NULL && args[1] != NULL)
    {
      while (i < NB_RESSOURCES && strcmp(args[1], g_res_names[i]) != 0)
	++i;
      if (i < NB_RESSOURCES && u->inventory[i] > 0)
	{
	  --u->inventory[i];
	  ++g_info.map->cases[u->y][u->x].elements[i];
	  lookup(g_info.users, graphics_pdr(u, i), &notify_graphic);
	  lookup(g_info.users, graphics_pin(u), &notify_graphic);
	  lookup(g_info.users, graphics_bct(u->x, u->y), &notify_graphic);
	  return (SUCCESS);
	}
    }
  return (FAILURE);
}

t_cmd_ret	take_cmd(t_users *u, char **args)
{
  int		i;

  i = 0;
  if (args != NULL && args[0] != NULL && args[1] != NULL)
    {
      while (i < NB_RESSOURCES && strcmp(args[1], g_res_names[i]) != 0)
	++i;
      if (i < NB_RESSOURCES && g_info.map->cases[u->y][u->x].elements[i] > 0)
	{
	  ++u->inventory[i];
	  --g_info.map->cases[u->y][u->x].elements[i];
	  lookup(g_info.users, graphics_pdr(u, i), &notify_graphic);
	  lookup(g_info.users, graphics_pin(u), &notify_graphic);
	  lookup(g_info.users, graphics_bct(u->x, u->y), &notify_graphic);
	  return (SUCCESS);
	}
    }
  return (FAILURE);
}
