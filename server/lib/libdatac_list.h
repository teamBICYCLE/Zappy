/*
** list.h for lib_list in /home/jonathan/Projets/utils/lib_linked_list
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Mon Oct 24 10:06:47 2011 Jonathan Machado
** Last update Fri Apr 20 22:40:10 2012 Jonathan Machado
*/

#ifndef		__LIST_H__
# define	__LIST_H__

# include "libdatac_link.h"

typedef	struct s_list	t_list;
struct			s_list
{
  unsigned int	size;
  t_link		*head;
  t_link		*tail;
};

t_list		*new_list(void);

t_link		*pop_front(t_list *list);
t_link		*pop_end(t_list *list);
t_link		*pop_at(t_list *list, unsigned int pos);
void		push_front(t_list *list, t_link *new);
void		push_back(t_list *list, t_link *new);
t_link		*get_link(t_list *list, unsigned int pos);

int		is_in_list(t_list *list, void *ptr, int (*f)(void *, void *));
t_link		*lookup(t_list *list, void *ptr, int (*f)(void *, void *));
t_link		*lookup_and_pop(t_list *, void *, int (*f)(void *, void *));

t_list		*iterate(t_list *list, void (*f)(void *));

void		delete_list(t_list *list, void (*f)(void *));

#endif	/* __LIST_H__ */
