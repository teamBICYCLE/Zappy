/*
** server.h for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Mon May 14 10:24:55 2012 Jonathan Machado
** Last update Tue Jun 12 17:22:00 2012 lois burg
*/

#ifndef __SERVER_H__
# define __SERVER_H__

# include <stdbool.h>
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

typedef enum	e_direction
  {
    NORTH = 0,
    EAST,
    SOUTH,
    WEST
  }		t_direction;

struct          s_users
{
  int		x;
  int		y;
  t_direction	dir;
  int		lvl;
  int		inventory[LAST];
  int           socket;
  t_list        *messages;
  t_ringbuffer  *readring;
  t_list	*tasks;
  size_t        idx;
  bool		first_message;
};

struct          s_infos
{
  int           ss;
  int           smax;
  fd_set        writefds;
  fd_set        readfds;
  t_list        *users;
  t_map		*map;
  t_arg_infos	world;
};

void    run(void);

void   	add_user(void);
void   	write_user(void *ptr);
void   	read_user(void *ptr);

void   	add_task(t_users *u, char ** args);

/* TOOLS */
int    	cmp_socket(void *a, void *b);
void	print_serv_conf(t_arg_infos *world_info);
char	**parse(char *str, const char *delim);

void   	free_users(void *ptr);
void	free_all(t_infos *info);

#endif /* __SERVER_H__ */
