/*
** ringbuffer.c for ringbuffer in /home/sylvia_r//Desktop/projet/tek2/my_irc_tb/lib
**
** Made by romain sylvian
** Login   <sylvia_r@epitech.net>
**
** Started on  Tue Apr 17 17:22:39 2012 romain sylvian
** Last update Tue Jun 26 17:21:15 2012 Jonathan Machado
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "ringbuffer.h"

t_ringbuffer	*new_ringbuffer(size_t size)
{
  t_ringbuffer	*ret;

  ret = malloc(sizeof(*ret));
  if (ret)
    {
      memset(ret, 0, sizeof(*ret));
      ret->data = malloc((size) * sizeof(*ret->data));
      if (ret->data == NULL)
	return NULL;
      memset(ret->data, 0, size);
      ret->size = size;
      ret->end = 0;
    }
  return (ret);
}

void		delete_ringbuffer(t_ringbuffer *ring)
{
  free(ring->data);
  free(ring);
}

int		read_data(int fd, t_ringbuffer *ring)
{
  int		l;

  if ((l = read(fd, ring->data, ring->size - ring->end - 1)) <= 0)
    return ((ring->size - ring->end - 1 == 0 ? 1 : 0));
  ring->end += l;
  ring->data[ring->end] = 0;
  return (1);
}

char		*get_data(t_ringbuffer *ring)
{
  char		*s;
  char		*ret;

  if ((s = strchr(ring->data, '\n')) != NULL)
    {
      ret = malloc(strlen(ring->data) * sizeof(*ret));
      if (ret)
	{
	  memcpy(ret, ring->data, strlen(ring->data) - 1);
	  ret[strlen(ring->data) - 1] = 0;
	  if (strlen(ret) && ret[strlen(ret) - 1] == '\r')
	    ret[strlen(ret) - 1] = 0;
	  memmove(ring->data, s + 1, ring->size - strlen(ring->data));
	}
      return (ret);
    }
  return (NULL);
}
