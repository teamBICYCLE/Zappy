/*
** cmds_utils.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Wed Jun 20 15:54:02 2012 lois burg
** Last update Sun Jul 15 12:07:38 2012 lois burg
*/

#include <string.h>
#include <stdlib.h>
#include "server.h"
#include "graphics.h"
#include "cmds.h"
#include "protocol.h"

extern t_infos	g_info;

static int	find_team_egg(void *u, void *t)
{
  const t_users	*user = (t_users*)u;
  const t_team	*team = (t_team*)t;

  return (!(user && team && user->type == TGHOST &&
	    !strcmp(user->team->name, team->name)));
}

void		assign_pos(t_users *u, t_team *team)
{
  t_link	*ghost_lnk;
  t_users	*ghost;

  u->x = rand() % g_info.map->x;
  u->y = rand() % g_info.map->y;
  if ((ghost_lnk = lookup_and_pop(g_info.users, team, &find_team_egg)))
    {
      ghost = (t_users*)ghost_lnk->ptr;
      u->id = ghost->id;
      u->lvl = ghost->lvl;
      u->x = ghost->x;
      u->y = ghost->y;
      u->type = TFORMER_GHOST;
      delete_link(ghost_lnk, &free_users);
      lookup(g_info.users, graphics_ebo(u->id), &notify_graphic);
    }
  else
    ++g_info.map->cases[u->y][u->x].elements[PLAYER];
  u->inventory[FOOD] = 10;
  u->life = (u->inventory[FOOD] * 126);
  u->team = team;
  --team->free_slots;
  greet_clnt(u, g_info.map->x, g_info.map->y);
  lookup(g_info.users, graphics_pnw(u), &notify_graphic);
}

bool	pretask_check(const char *cmd, t_users *u)
{
  bool	valid;

  valid = true;
  if (cmd && !strcmp(cmd, "fork"))
    lookup(g_info.users, graphics_pfk(u), &notify_graphic);
  else if (cmd && !strcmp(cmd, "incantation"))
    {
      if (check_levelup(u))
	{
	  push_back(u->messages,
		    new_link_by_param(LEVELUP_ENGAGED,
				      sizeof(LEVELUP_ENGAGED) + 1));
	  lookup(g_info.users, graphics_pic(u), &notify_graphic);
	}
      else
	{
	  valid = false;
	  push_back(u->messages, new_link_by_param(KO, sizeof(KO) + 1));
	}
    }
  return (valid);
}
