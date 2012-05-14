/*
** link.h for lib_list in /home/jonathan/Projets/utils/lib_linked_list
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Mon Oct 24 10:10:53 2011 Jonathan Machado
** Last update Tue Apr 17 14:17:35 2012 romain sylvian
*/

#ifndef		__LINK_H__
# define	__LIST_H__

typedef struct t_link	t_link;

struct			t_link
{
  void		*ptr;
  t_link	*next;
  t_link	*prev;
};

t_link	*new_link(void);
t_link	*new_link_by_copy(t_link *link);
t_link	*new_link_by_param(void *ptr, size_t s);
void   	delete_link(t_link *link, void (*f)(void*));

#endif /* __LIST_H__ */
