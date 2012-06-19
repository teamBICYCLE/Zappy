/*
** task.h for zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Mon Jun 11 16:05:02 2012 Jonathan Machado
** Last update Tue Jun 19 17:43:26 2012 lois burg
*/

#ifndef __TASK_H__
# define __TASK_H__

# include "cmds.h"
# include "server.h"

typedef void			(*t_graphicsf)(t_users *, char **);
typedef t_cmd_ret		(*t_taskf)(t_users *, char **, char *);
typedef struct s_graphicsmap	t_graphicsmap;
typedef struct s_tasksmap	t_tasksmap;
typedef struct s_task		t_task;

struct		s_graphicsmap
{
  char		*key;
  t_graphicsf	f;
};

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
  char		*orig_cmd;
  char	       	**args;
};

void	free_tasks(void *);

#endif /* __TASK_H__ */
