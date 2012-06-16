/*
** graphics.h for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Fri Jun 15 18:27:05 2012 lois burg
** Last update Sat Jun 16 12:41:25 2012 lois burg
*/

#ifndef		__GRAPHICS_H__
# define	__GRAPHICS_H__

# define	GRAPHICS_MSG_SZ	4096

int		notify_graphic(void *usr, void *msg);
char		*get_graphics_buf(void);

#endif /* !__GRAPHICS_H__*/
