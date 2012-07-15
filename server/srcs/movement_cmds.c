/*
** movement.c for  in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Thu Jun 14 13:38:06 2012 Jonathan Machado
** Last update Sun Jul 15 11:17:31 2012 lois burg
*/

#include <string.h>
#include "graphics.h"
#include "server.h"
#include "cmds.h"

extern int		g_res_to_restore[NB_RESSOURCES];
extern char		*g_res_names[LAST];
extern t_infos		g_info;
static	t_dir_mov	g_dir_tab[4] =
  {
    {0, -1},
    {1, 0},
    {0, 1},
    {-1, 0}
  };

t_cmd_ret	left_cmd(t_users *u, char **args, char *orig_cmd)
{
  (void)args;
  (void)orig_cmd;
  --u->dir;
  if (u->dir == UNDEF)
    u->dir = WEST;
  lookup(g_info.users, graphics_ppo(u), &notify_graphic);
  return (SUCCESS);
}

t_cmd_ret	right_cmd(t_users *u, char **args, char *orig_cmd)
{
  (void)args;
  (void)orig_cmd;
  ++u->dir;
  u->dir %= WEST + 1;
  lookup(g_info.users, graphics_ppo(u), &notify_graphic);
  return (SUCCESS);
}

t_cmd_ret	forward_cmd(t_users *u, char **args, char *orig_cmd)
{
  (void)args;
  (void)orig_cmd;
  --g_info.map->cases[u->y][u->x].elements[PLAYER];
  u->x = ((u->x + g_dir_tab[u->dir].dx) + g_info.map->x) % g_info.map->x;
  u->y = ((u->y + g_dir_tab[u->dir].dy) + g_info.map->y) % g_info.map->y;
  ++g_info.map->cases[u->y][u->x].elements[PLAYER];
  lookup(g_info.users, graphics_ppo(u), &notify_graphic);
  return (SUCCESS);
}

t_cmd_ret	put_cmd(t_users *u, char **args, char *orig_cmd)
{
  int		i;

  (void)orig_cmd;
  i = 0;
  if (args != NULL && args[0] != NULL && args[1] != NULL)
    {
      while (i < NB_RESSOURCES && strcmp(args[1], g_res_names[i]) != 0)
	++i;
      if (i < NB_RESSOURCES && u->inventory[i] > 0)
	{
	  --u->inventory[i];
	  ++g_info.map->cases[u->y][u->x].elements[i];
	  if (i == FOOD && (int)u->life - 126 >= 0)
	    u->life -= 126;
	  else if (i == FOOD)
	    u->life = 0;
	  lookup(g_info.users, graphics_pdr(u, i), &notify_graphic);
	  lookup(g_info.users, graphics_pin(u), &notify_graphic);
	  lookup(g_info.users, graphics_bct(u->x, u->y), &notify_graphic);
	  return (SUCCESS);
	}
    }
  return (FAILURE);
}

t_cmd_ret	take_cmd(t_users *u, char **args, char *orig_cmd)
{
  int		i;

  (void)orig_cmd;
  i = 0;
  if (args != NULL && args[0] != NULL && args[1] != NULL)
    {
      while (i < NB_RESSOURCES && strcmp(args[1], g_res_names[i]) != 0)
	++i;
      if (i < NB_RESSOURCES && g_info.map->cases[u->y][u->x].elements[i] > 0)
	{
	  ++u->inventory[i];
	  --g_info.map->cases[u->y][u->x].elements[i];
	  if (i == FOOD)
	    {
	      u->life += 126;
	      g_res_to_restore[FOOD] += 1;
	    }
	  lookup(g_info.users, graphics_pgt(u, i), &notify_graphic);
	  lookup(g_info.users, graphics_pin(u), &notify_graphic);
	  lookup(g_info.users, graphics_bct(u->x, u->y), &notify_graphic);
	  return (SUCCESS);
	}
    }
  return (FAILURE);
}
