/*
** ringbuffer.c for ringbuffer in /home/sylvia_r//Desktop/projet/tek2/my_irc_tb/lib
**
** Made by romain sylvian
** Login   <sylvia_r@epitech.net>
**
** Started on  Tue Apr 17 17:22:39 2012 romain sylvian
** Last update Tue Jul  3 18:32:12 2012 lois burg
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
  /* unsigned int i = 0; */
  /* char		toto[4096]; */

  l = 0;
  if (ring->size - ring->end - 1 > 0)
    if ((l = read(fd, &ring->data[ring->end], ring->size - ring->end - 1)) <= 0)
      return (l);
    /* printf("Toto: [%s]. l = %d\n", ring->data, l); */
  /* strncpy(&ring->data[ring->end], toto, l); */
  ring->end += l;
  ring->data[ring->end] = 0;
  /* for (i = 0; i < ring->end; ++i) */
  /*   printf("[%d] ", ring->data[i]); */
  /* printf("\n"); */
  /* printf("Ring: [%s]. End: %lu\n", ring->data, ring->end); */
  return (l);
}

char		*get_data(t_ringbuffer *ring)
{
  char		*s;
  char		*ret;

  if ((s = strchr(ring->data, '\n')) != NULL)
    {
      ret = malloc((s - ring->data + 1) * sizeof(*ret));
      if (ret)
	{
	  memcpy(ret, ring->data, s - ring->data);
	  ret[s - ring->data] = 0;
	  memmove(ring->data, s + 1, ring->size - strlen(ret) - 1);
	  	  /* printf("get_data end: %lu\n", ring->end); */
	  ring->end -= (strlen(ret) + 1);
	  	  /* printf("get_data end: %lu. [%lu]\n", ring->end, strlen(ret) + 1); */
	  if (strlen(ret) && ret[strlen(ret) - 1] == '\r')
	    ret[strlen(ret) - 1] = 0;
	}
      return (ret);
    }
  return (NULL);
}
