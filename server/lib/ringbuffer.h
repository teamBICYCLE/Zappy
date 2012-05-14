/*
** ringbuffer.h for ringbuffer in /home/sylvia_r//Desktop/projet/tek2/my_irc_tb/lib
**
** Made by romain sylvian
** Login   <sylvia_r@epitech.net>
**
** Started on  Tue Apr 17 17:15:28 2012 romain sylvian
** Last update Sat Apr 21 00:59:42 2012 romain sylvian
*/

#ifndef		__RINGBUFFER_H__
# define	__RINGBUFFER_H__

# include	<stddef.h>

typedef struct	s_ringbuffer t_ringbuffer;

struct		s_ringbuffer
{
  char		*data;
  size_t	size;
  size_t	end;
};

void		delete_ringbuffer(t_ringbuffer *ring);
t_ringbuffer	*new_ringbuffer(size_t size);
char		*get_data(t_ringbuffer *ring);
int		read_data(int fd, t_ringbuffer *ring);

#endif /*!__RINGBUFFER_H__*/
