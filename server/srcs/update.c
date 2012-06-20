/*
** update.c for  in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Tue Jun 12 17:39:39 2012 Jonathan Machado
** Last update Wed Jun 20 15:48:49 2012 lois burg
*/

#include <string.h>
#include "server.h"
#include "task.h"
#include "protocol.h"
#include "cmds.h"
#include "graphics.h"

extern t_infos		g_info;

static	int	cmp_ptr(void *a, void *b)
{
  return (a != b);
}

static	void	do_task(void *ptr)
{
  t_users	*u;
  t_task	*t;
  t_cmd_ret	success;

  u = ptr;
  if (!u->is_graphics && u->life != 0 && u->tasks->size > 0)
    {
      t = u->tasks->head->ptr;
      if (t->countdown == 0)
	{
	  success = (t->f)(u, t->args, t->orig_cmd);
	  send_ok_ko(u, success);
	  delete_link(pop_front(u->tasks), &free_tasks);
	}
      else
	--t->countdown;
    }
}

static	void	decr_life(void *ptr)
{
  t_users	*u;

  u = ptr;
  if (!u->is_graphics && !u->is_egg && !u->is_ghost)
    {
      if (u->life == 0)
	{
	  if (u->is_dead == false)
	    {
	      push_back(u->messages, new_link_by_param(DIE, sizeof(DIE)));
	      u->is_dead = true;
	    }
	  else if (u->messages->size == 0)
	    {
	      if (u->team)
		++u->team->free_slots;
	      lookup(g_info.users, graphics_pdi(u), &notify_graphic);
	      delete_link(lookup_and_pop(g_info.users, ptr, &cmp_ptr), &free_users);
	    }
	}
      else
	{
	  --u->life;
	  u->inventory[FOOD] = u->life / 126;
	}
    }
}

void	update_map(int const loop)
{
  int	i;

  i = 0;
  while (i < loop)
    {
      iterate(g_info.users, &do_task);
      iterate(g_info.users, &decr_life);
      /* regen map*/
      ++i;
    }
}
