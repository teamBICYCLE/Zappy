/*
** server.h for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Mon May 14 10:24:55 2012 Jonathan Machado
** Last update Wed Jul  4 17:53:40 2012 lois burg
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

typedef struct	s_users         t_users;
typedef struct	s_infos         t_infos;
typedef	struct  s_task_info	t_task_info;

typedef enum	e_direction
  {
    UNDEF = -1,
    NORTH,
    EAST,
    SOUTH,
    WEST
  }		t_direction;

typedef	enum	e_type
  {
    TPLAYER = 0,
    TEGG,
    TGHOST,
    TGRAPHICS,
    TFORMER_GHOST
  }		t_type;

struct		s_task_info
{
  char		*data;
  char		**args;
  char		*duplicate;
  bool		task_failure;
};

struct          s_users
{
  bool		first_message;
  t_type	type;
  bool		is_dead;
  /* server */
  int           socket;
  size_t        idx;
  t_list        *messages;
  t_ringbuffer  *readring;
  /* player */
  int		id;
  int		father_id;
  int		x;
  int		y;
  int		lvl;
  t_direction	dir;
  unsigned int	life;
  unsigned int 	inventory[NB_RESSOURCES];
  t_list	*tasks;
  t_team	*team;
};

struct          s_infos
{
  bool		end_game;
  int           ss;
  int           smax;
  fd_set        writefds;
  fd_set        readfds;
  t_list        *users;
  t_map		*map;
  t_team	*winning_team;
  t_arg_infos	world;
};

void    run(void);

void   	add_user(void);
void   	write_user(void *ptr);
void   	read_user(void *ptr);
void	reset_fd(t_infos *info);
void	remove_user(t_users *u);
void	loot_plyr(t_users *u);

void   	exec_cmd(t_users *u, t_task_info *ti);
void	update_map(int const loop);
void	send_world(void);

/* TOOLS */
int    	cmp_socket(void *a, void *b);
void	print_serv_conf(t_arg_infos *world_info);
char	**parse(char *str, const char *delim);
double	get_angle(int *x, int *y, t_direction dir);
int	get_case(int *x, int *y, t_direction dir);

void   	free_users(void *ptr);
void   	free_teams(void *ptr);
void	free_all(t_infos *info);
void	free_task_info(t_task_info *ti);

#endif /* __SERVER_H__ */
