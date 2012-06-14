/*
** update.c for  in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Tue Jun 12 17:39:39 2012 Jonathan Machado
** Last update Wed Jun 13 18:58:50 2012 Jonathan Machado
*/

#include "server.h"
#include "task.h"
#include "protocol.h"

extern t_infos		g_info;

static	void	do_task(void *ptr)
{
  t_users	*u;
  t_task	*t;

  u = ptr;
  if (u->life != 0 && u->tasks->size > 0)
    {
      t = u->tasks->head->ptr;
      if (t->countdown == 0)
	{
	  t->f(u, t->args);
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
  if (u->life == 0)
    {
      push_back(u->messages, new_link_by_param(DIE, sizeof(DIE)));
      // suprimer le bonhome quand u->message->size == 0;
    }
  else
    --u->life;
}

void	update_map(int const loop)
{
  int	i;

  i = 0;
  while (i < loop)
    {
      iterate(g_info.users, &do_task);
      iterate(g_info.users, &decr_life);
      // regen map
      ++i;
    }
}
