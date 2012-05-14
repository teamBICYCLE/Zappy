/*
** link.c for lib_list in /home/jonathan/Projets/utils/lib_linked_list
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Mon Oct 24 10:18:44 2011 Jonathan Machado
** Last update Tue Apr 17 17:26:17 2012 romain sylvian
*/

#include <stdlib.h>
#include <string.h>
#include "libdatac_link.h"

t_link		*new_link(void)
{
  t_link       	*new;

  new = NULL;
  new = malloc(sizeof(*new));
  if (new)
    memset(new, 0, sizeof(*new));
  return (new);
}

t_link		*new_link_by_param(void *ptr, size_t s)
{
  t_link       	*new;

  new = NULL;
  new = new_link();
  if (ptr != NULL)
    {
      new->ptr = malloc(s);
      new->ptr = memcpy(new->ptr, ptr, s);
    }
  return (new);
}

void		delete_link(t_link *link, void (*f)(void*))
{
  if (link != NULL)
    {
      if (f != NULL)
	f(link->ptr);
      link->ptr = NULL;
      free(link);
      link = NULL;
    }
}

