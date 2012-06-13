/*
** task.h for zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Mon Jun 11 16:05:02 2012 Jonathan Machado
** Last update Wed Jun 13 18:00:36 2012 Jonathan Machado
*/

#ifndef __TASK_H__
# define __TASK_H__
#include "server.h"

typedef bool			(*t_taskf)(t_users *, char **);
typedef struct s_tasksmap	t_tasksmap;
typedef struct s_task		t_task;

struct		s_tasksmap
{
  unsigned int	countdown;
  t_taskf      	f;
  char	       	*key;
};

struct		s_task
{
  unsigned int	countdown;
  t_taskf      	f;
  char	       	**args;
};

void	free_tasks(void *);

#endif /* __TASK_H__ */
