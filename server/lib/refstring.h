/*
** refstring.h for  in /home/jonathan/Projets/Tek-2/C/my_irc_tb/serverdir
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Thu Apr 19 10:02:41 2012 Jonathan Machado
** Last update Sun Apr 22 14:06:47 2012 Jonathan Machado
*/

#ifndef __REFSTRING_H__
# define __REFSTRING_H__

typedef struct	s_refstring t_refstring;

struct		s_refstring
{
  size_t	count;
  size_t	len;
  char		*str;
};

t_refstring	*new_refstring(char *);
void		unref(t_refstring **);
t_refstring	*ref(t_refstring *);

#endif /* __REFSTRING_H__ */
