/*
** server.h for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Mon May 14 10:24:55 2012 Jonathan Machado
** Last update Fri Jun  8 10:17:36 2012 lois burg
*/

#ifndef __SERVER_H__
# define __SERVER_H__

# include <sys/socket.h>
# include <signal.h>
# include <unistd.h>
# include <sys/select.h>
# include "map.h"
# include "libdatac_list.h"
# include "ringbuffer.h"
# include "args.h"

typedef void (*sighandler_t)(int);

typedef struct s_users          t_users;
typedef struct s_infos          t_infos;

struct          s_users
{
  int           socket;
  t_list        *messages;
  t_ringbuffer  *readring;
  size_t        idx;
};

struct          s_infos
{
  int           ss;
  int           smax;
  fd_set        writefds;
  fd_set        readfds;
  t_list        *users;
  t_list	*tasks;
  t_map		*map;
  t_arg_infos	world;
};

void    run(void);

void   	add_user(void);
void   	write_user(void *ptr);
void   	read_user(void *ptr);

/* TOOLS */
int    	cmp_socket(void *a, void *b);
void	print_serv_conf(t_arg_infos *world_info);
char	**parse(char *str, const char *delim);

void   	free_tasks(void *ptr);
void   	free_users(void *ptr);
void	free_all(t_infos *info);

#endif /* __SERVER_H__ */
