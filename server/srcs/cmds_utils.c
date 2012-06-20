/*
** cmds_utils.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Wed Jun 20 15:54:02 2012 lois burg
** Last update Wed Jun 20 16:57:40 2012 lois burg
*/

#include <string.h>
#include <stdlib.h>
#include "server.h"
#include "graphics.h"
#include "cmds.h"

extern t_infos	g_info;

static int	find_team_egg(void *u, void *t)
{
  const t_users	*user = (t_users*)u;
  const t_team	*team = (t_team*)t;

  return (!(user && team && user->is_ghost &&
	    !strcmp(user->team->name, team->name)));
}

void		assign_pos(t_users *u, t_team *team)
{
  t_link	*ghost_lnk;
  t_users	*ghost;

  if ((ghost_lnk = lookup_and_pop(g_info.users, team, &find_team_egg)))
    {
      ghost = (t_users*)ghost_lnk->ptr;
      u->id = ghost->id;
      u->lvl = ghost->lvl;
      u->x = ghost->x;
      u->y = ghost->y;
      delete_link(ghost_lnk, &free_users);
      lookup(g_info.users, graphics_ebo(u->id), &notify_graphic);
    }
  else
    {
      u->x = rand() % g_info.map->x;
      u->y = rand() % g_info.map->y;
      ++g_info.map->cases[u->y][u->x].elements[PLAYER];
    }
  u->team = team;
  --team->free_slots;
  send_id_pos(u);
  lookup(g_info.users, graphics_pnw(u), &notify_graphic);
}
