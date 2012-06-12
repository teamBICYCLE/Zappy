/*
** free.c for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Mon May 14 19:51:15 2012 Jonathan Machado
** Last update Tue Jun 12 16:48:16 2012 Jonathan Machado
*/

#include <stdlib.h>
#include "server.h"
#include "task.h"

void		free_tasks(void *ptr)
{
  t_task	*t;

  t = ptr;
  free(t->args[0]);
  free(t->args);
  free(ptr);
}

void		free_users(void *ptr)
{
  t_users	*u;

  u = ptr;
  close(u->socket);
  delete_list(u->messages, &free);
  delete_ringbuffer(u->readring);
  delete_list(u->tasks, &free_tasks);
  free(ptr);
}

void	free_all(t_infos *info)
{
  delete_list(info->users, &free_users);
  delete_list(info->world.teams_names, &free);
  free_map(info->map);
}
