/*
** free.c for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Mon May 14 19:51:15 2012 Jonathan Machado
** Last update Mon May 14 20:30:02 2012 Jonathan Machado
*/

#include <stdlib.h>
#include "server.h"

void		free_tasks(void *ptr)
{
  free(ptr);
}

void		free_users(void *ptr)
{
  t_users	*u;

  u = ptr;
  close(u->socket);
   delete_list(u->messages, &free);
  delete_ringbuffer(u->readring);
  free(ptr);
}

void	free_all(t_infos *info)
{
  delete_list(info->tasks, &free_tasks);
  delete_list(info->users, &free_users);
}
