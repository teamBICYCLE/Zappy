/*
** list2.c for  in /home/jonathan/Projets/Tek-2/C/my_irc_tb
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Fri Apr 20 22:42:35 2012 Jonathan Machado
** Last update Fri Jul  6 16:10:42 2012 lois burg
*/

#include <stdlib.h>
#include <string.h>
#include "libdatac_list.h"

t_link		*lookup_and_pop(t_list *list, void *ptr,
				int (*f)(void *, void *))
{
  unsigned int	i;
  t_link	*cur;

  i = 0;
  cur = NULL;
  if (list != NULL)
    {
      cur = list->head;
      while (cur)
	{
	  if (f(cur->ptr, ptr) == 0)
	    return (pop_at(list, i));
	  cur = cur->next;
	  ++i;
	}
    }
  return (NULL);
}

t_list		*iterate(t_list *list, void (*f)(void *))
{
  t_link	*cur;
  t_link	*next;

  cur = NULL;
  if (list != NULL)
    {
      cur = list->head;
      while (cur)
	{
	  next = cur->next;
	  f(cur->ptr);
	  cur = next;
	}
    }
  return (list);
}

static void	delete_link_list(t_link *link, void (*f)(void *))
{
  if (link != NULL)
    {
      if (link->next != NULL)
	delete_link_list(link->next, f);
      delete_link(link, f);
    }
}

void	delete_list(t_list *list, void (*f)(void *))
{
  if (list != NULL)
    {
      if (list->head != NULL)
	list->head->prev = NULL;
      if (list->tail != NULL)
	list->tail->next = NULL;
      delete_link_list(list->head, f);
      free(list);
      list = NULL;
    }
}
