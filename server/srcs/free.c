/*
** free.c for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Mon May 14 19:51:15 2012 Jonathan Machado
** Last update Mon Jul  2 16:18:03 2012 lois burg
*/

#include <stdlib.h>
#include "server.h"
#include "task.h"

void	free_task_info(t_task_info *ti)
{
  free(ti->data);
  free(ti->args);
  free(ti->duplicate);
}

void		free_tasks(void *ptr)
{
  t_task	*t;

  t = ptr;
  free_task_info(&t->ti);
  free(ptr);
}

void		free_users(void *ptr)
{
  t_users	*u;

  u = ptr;
  if (u->socket != -1)
    close(u->socket);
  delete_list(u->messages, &free);
  delete_ringbuffer(u->readring);
  delete_list(u->tasks, &free_tasks);
  free(ptr);
}

void		free_teams(void *ptr)
{
  t_team	*t;

  t = (t_team*)ptr;
  free(t->name);
  free(t);
}

void	free_all(t_infos *info)
{
  delete_list(info->users, &free_users);
  delete_list(info->world.teams_names, &free_teams);
  free_map(info->map);
}
