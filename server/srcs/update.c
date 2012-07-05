/*
** update.c for  in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Tue Jun 12 17:39:39 2012 Jonathan Machado
** Last update Wed Jul  4 17:24:40 2012 Jonathan Machado
*/

#include <string.h>
#include "server.h"
#include "task.h"
#include "protocol.h"
#include "cmds.h"
#include "graphics.h"

extern t_infos		g_info;

static	void	do_task(void *ptr)
{
  t_users	*u;
  t_task	*t;
  t_cmd_ret	success;

  u = ptr;
  if (u->type != TGRAPHICS && u->life != 0 && u->tasks->size > 0)
    {
      t = u->tasks->head->ptr;
      if (t->countdown == 0)
	{
	  success = (t->f)(u, t->ti.args, t->ti.duplicate);
	  send_ok_ko(u, success);
	  delete_link(pop_front(u->tasks), &free_tasks);
	}
      else
	--t->countdown;
    }
}

static void	decr_and_notify(t_users *u)
{
  const size_t 	prev_food = u->inventory[FOOD];

  --u->life;
  if (u->life > 0)
    u->inventory[FOOD] = (u->life / 126) + 1;
  else
    u->inventory[FOOD] = 0;
  if (u->first_message == false && prev_food != u->inventory[FOOD])
    lookup(g_info.users, graphics_pin(u), &notify_graphic);
}

static	void	decr_life(void *ptr)
{
  t_users	*u;

  u = ptr;
  if (u->type == TPLAYER || u->type == TFORMER_GHOST)
    {
      if (u->life == 0)
	{
	  if (u->first_message == true)
	    remove_user(u);
	  else
	    {
	      if (u->is_dead == false)
		{
		  push_back(u->messages, new_link_by_param(DIE, sizeof(DIE)));
		  u->is_dead = true;
		}
	      else if (u->messages->size == 0)
		remove_user(u);
	    }
	}
      else
	decr_and_notify(u);
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
