/*
** answer_graphics3.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Thu Jul  5 17:39:56 2012 lois burg
** Last update Thu Jul 12 14:45:24 2012 lois burg
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"
#include "server.h"
#include "cmds.h"

extern t_infos	g_info;

void		answer_gkp(t_users *usr, char **args)
{
  int		id;
  char		*msg;
  t_link	*l;
  t_users	*p;

  msg = graphics_sbp();
  if (args && args[0] &&
      contains_only_digits(args[0]))
    {
      id = strtol(args[0], NULL, 10);
      if ((l = lookup(g_info.users, &id, &cmp_id)))
	{
	  p = (t_users*)l->ptr;
	  if (p->type != TGRAPHICS && p->first_message == false)
	    {
	      msg = NULL;
	      remove_user(p);
	    }
	}
    }
  if (msg)
    push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
}

static void	set_plyr_inventory(t_users *p, char **args, char **msg)
{
  int		i;
  int		new_inventory[NB_RESSOURCES];

  i = 0;
  while (p->type != TGRAPHICS && p->first_message == false &&
	 contains_only_digits(args[i]) && i < NB_RESSOURCES)
    {
      new_inventory[i] = strtol(args[i], NULL, 10);
      ++i;
    }
  if (i == NB_RESSOURCES)
    {
      memcpy(p->inventory, new_inventory, sizeof(p->inventory));
      p->life = p->inventory[FOOD] * 126;
      *msg = NULL;
      lookup(g_info.users, graphics_pin(p), &notify_graphic);
    }
}

void		answer_gsi(t_users *usr, char **args)
{
  int		id;
  char		*msg;
  t_link	*l;
  t_users	*p;

  msg = graphics_sbp();
 if (carray_size((char const **)args) == NB_RESSOURCES + 1 &&
      contains_only_digits(args[0]))
    {
      id = strtol(args[0], NULL, 10);
      if ((l = lookup(g_info.users, &id, &cmp_id)))
	{
	  p = (t_users*)l->ptr;
	  set_plyr_inventory(p, &args[1], &msg);
	}
    }
  if (msg)
    push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
}

void		answer_gsc(t_users *usr, char **args)
{
  int		i;
  uint		x;
  uint		y;
  char		*msg;

  msg = graphics_sbp();
  if (carray_size((char const **)args) == NB_RESSOURCES + 2 &&
      contains_only_digits(args[0]) && contains_only_digits(args[1]))
    {
      x = strtol(args[0], NULL, 10);
      y = strtol(args[1], NULL, 10);
      i = 2;
      while (x < g_info.map->x && y < g_info.map->y &&
	     args[i] && contains_only_digits(args[i]))
	{
	  g_info.map->cases[y][x].elements[i - 2] = strtol(args[i], NULL, 10);
	  ++i;
	}
      if (i == NB_RESSOURCES + 2)
	{
	  msg = NULL;
	  lookup(g_info.users, graphics_bct(x, y), &notify_graphic);
	}
    }
  if (msg)
    push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
}

void		answer_glp(t_users *usr, char **args)
{
  int		id;
  char		*msg;
  t_link	*l;
  t_users	*p;
  char		lvlup[END_LEVELUP_MSG_SZ];

  msg = graphics_sbp();
  if (args && args[0] && contains_only_digits(args[0]))
    {
      id = strtol(args[0], NULL, 10);
      if ((l = lookup(g_info.users, &id, &cmp_id)) && (p = (t_users*)l->ptr))
	{
	  if (p->lvl < MAX_LVL)
	    {
	      ++p->lvl;
	      snprintf(lvlup, sizeof(lvlup), "niveau actuel : %d\n", p->lvl);
	      push_back(p->messages,
			new_link_by_param(lvlup, strlen(lvlup) + 1));
	      lookup(g_info.users, graphics_plv(p), &notify_graphic);
	      msg = NULL;
	    }
	}
    }
  if (msg)
    push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
}
