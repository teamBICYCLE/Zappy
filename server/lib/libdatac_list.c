/*
** list.c for lib_list in /home/jonathan/Projets/utils/lib_linked_list
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Mon Oct 24 14:47:22 2011 Jonathan Machado
** Last update Fri Jul  6 17:41:49 2012 lois burg
*/

#include <stdlib.h>
#include <string.h>
#include "libdatac_list.h"

void	push_back(t_list *list, t_link *new)
{
  if (list != NULL && new != NULL)
    {
      new->prev = list->tail;
      new->next = NULL;
      if (list->tail != NULL)
	list->tail->next = new;
      if (list->head == NULL)
	list->head = new;
      list->tail = new;
      list->size += 1;
    }
}

void	push_front(t_list *list, t_link *new)
{
  if (list != NULL)
    {
      if (new != NULL)
	{
	  new->prev = NULL;
	  new->next = list->head;
	  if (list->head != NULL)
	    list->head->prev = new;
	  if (list->tail == NULL)
	    list->tail = new;
	  list->head = new;
	  list->size += 1;
	}
    }
}

t_link		*get_link(t_list *list, unsigned int pos)
{
  unsigned int	i;
  t_link	*ret;

  i = 0;
  ret = NULL;
  if (list != NULL)
    {
      if (list->size > pos)
	{
	  ret = list->head;
	  if (pos == list->size - 1)
	    ret = list->tail;
	  else
	    while (i < pos)
	      {
		ret = ret->next;
		++i;
	      }
	}
    }
  return (ret);
}

int		is_in_list(t_list *list, void *ptr, int (*f)(void *, void *))
{
  t_link	*cur;

  cur = NULL;
  if (list != NULL)
    {
      cur = list->head;
      while (cur)
	{
	  if (f(cur->ptr, ptr) == 0)
	    return (1);
	  cur = cur->next;
	}
    }
  return (0);
}

t_link		*lookup(t_list *list, void *ptr, int (*f)(void *, void *))
{
  t_link	*cur;

  cur = NULL;
  if (list != NULL)
    {
      cur = list->head;
      while (cur)
	{
	  if (f(cur->ptr, ptr) == 0)
	    return (cur);
	  cur = cur->next;
	}
    }
  return (NULL);
}
