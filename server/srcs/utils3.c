/*
** utils3.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Fri Jun 15 12:22:39 2012 lois burg
** Last update Wed Jul 11 11:16:18 2012 lois burg
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"
#include "protocol.h"
#include "cmds.h"
#include "graphics.h"

extern t_infos	g_info;

int		cmp_team(void *t1, void *t2)
{
  const char	*name = ((t_team*)t1)->name;

  return (strcmp(name, (const char *)t2));
}

int	cmp_id(void *usr, void *id)
{
  return (!(((t_users*)usr)->id == *(int*)id));
}

void	send_ok_ko(t_users *usr, t_cmd_ret s)
{
  if (s != IGNORE)
    {
      if (s == SUCCESS)
	push_back(usr->messages, new_link_by_param(OK, sizeof(OK) + 1));
      else
	push_back(usr->messages, new_link_by_param(KO, sizeof(KO) + 1));
    }
}

void	greet_clnt(const t_users *usr, const int wx, const int wy)
{
  char	msg[GREETINGS_CLIENT_SZ];

  memset(msg, 0, sizeof(msg));
  snprintf(msg, sizeof(msg), "%d\n", usr->team->free_slots);
  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
  snprintf(msg, sizeof(msg), "%d %d\n", wx, wy);
  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
}

void	loot_plyr(t_users *u)
{
  int	i;
  int	x;
  int	y;
  int	dx;
  int	dy;

  i = 0;
  while (i < NB_RESSOURCES)
    {
      while (u->inventory[i] > 0)
	{
	  dx = (rand() % 2) + 1;
	  dy = (rand() % 2) + 1;
	  if (rand() % 2 == 0)
	    dx *= -1;
	  if (rand() % 2 == 0)
	    dy *= -1;
	  x = ((u->x + dx) + g_info.map->x) % g_info.map->x;
	  y = ((u->y + dy) + g_info.map->y) % g_info.map->y;
	  ++g_info.map->cases[y][x].elements[i];
	  lookup(g_info.users, graphics_bct(x, y), &notify_graphic);
	  --u->inventory[i];
	}
      ++i;
    }
}
