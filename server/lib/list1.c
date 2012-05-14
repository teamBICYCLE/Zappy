/*
** list1.c for  in /home/jonathan/Projets/Tek-2/C/my_irc_tb
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Fri Apr 20 22:41:25 2012 Jonathan Machado
** Last update Sun Apr 22 16:16:59 2012 Jonathan Machado
*/

#include <stdlib.h>
#include <string.h>
#include "libdatac_list.h"

t_list		*new_list(void)
{
  t_list	*new;

  new = NULL;
  new = malloc(sizeof(*new));
  if (new)
    new = memset(new, 0, sizeof(*new));
  return (new);
}

t_link		*pop_front(t_list *list)
{
  t_link	*ret;

  ret = NULL;
  if (list != NULL)
    {
      if (list->head != NULL)
	{
	  ret = list->head;
	  if (ret->next != NULL)
	    ret->next->prev = NULL;
	  list->head = ret->next;
	  if (ret->next == NULL)
	    {
	      list->head = NULL;
	      list->tail = NULL;
	    }
	  list->size -= 1;
	}
    }
  return (ret);
}

t_link		*pop_end(t_list *list)
{
  t_link	*ret;

  ret = NULL;
  if (list != NULL)
    {
      if (list->tail != NULL)
	{
	  ret = list->tail;
	  if (ret->prev != NULL)
	    ret->prev->next = NULL;
	  list->tail = ret->prev;
	  if (ret->prev == NULL)
	    {
	      list->head = NULL;
	      list->tail = NULL;
	    }
	  ret->prev = NULL;
	  list->size -= 1;
	}
  }
  return (ret);
}

static t_link	*other(t_list *list, unsigned int pos)
{
  unsigned int	i;
  t_link	*ret;

  i = 0;
  ret = list->head;
  while (i < pos)
    {
      ret = ret->next;
      ++i;
    }
  ret->next->prev = ret->prev;
  ret->prev->next = ret->next;
  ret->prev = NULL;
  list->size -= 1;
  return (ret);
}

t_link		*pop_at(t_list *list, unsigned int pos)
{
  t_link	*ret;

  ret = NULL;
  if (list != NULL)
    {
      if (pos == 0)
	ret = pop_front(list);
      else if (pos == list->size - 1)
	ret = pop_end(list);
      else if (list->size > pos)
	ret = other(list, pos);
    }
  return (ret);
}
