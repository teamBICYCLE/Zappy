/*
** task.h for zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Mon Jun 11 16:05:02 2012 Jonathan Machado
** Last update Tue Jun 12 16:21:15 2012 Jonathan Machado
*/

#ifndef __TASK_H__
# define __TASK_H__
#include "server.h"

typedef bool			(*t_taskf)(t_users *, char **);
typedef struct s_tasksmap	t_tasksmap;
typedef struct s_task		t_task;

struct		s_tasksmap
{
  double	countdown;
  t_taskf      	f;
  char	       	*key;
};

struct		s_task
{
  double	countdown;
  t_taskf      	f;
  char	       	**args;
};

void	free_task(t_task *);

#endif /* __TASK_H__ */
