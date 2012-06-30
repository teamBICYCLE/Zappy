/*
** args.h for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Mon Jun  4 15:29:23 2012 lois burg
** Last update Fri Jun 29 16:19:09 2012 lois burg
*/

#ifndef		__ARGS_H__
# define	__ARGS_H__

# include	<sys/time.h>
# include	<stdbool.h>
# include	"libdatac_list.h"

# define	MAX_FREQUENCY	1000000

typedef	struct	s_arg_func	t_arg_func;
typedef	struct	s_arg_infos	t_arg_infos;
typedef	struct	s_team		t_team;

struct	s_team
{
  char	*name;
  int	free_slots;
};

struct	s_arg_func
{
  char	arg;
  void	(*fun)(t_arg_infos *world_infos, char *argv[]);
};

struct	s_arg_infos
{
  int			port;
  int			x;
  int			y;
  t_list		*teams_names;
  int			clients_per_team;
  int			action_delay;
  struct timeval	smallest_t;
  bool			help_showed;
  int			seed;
  bool			error;
};

void	parse_args(int argc, char *argv[], t_arg_infos *infos);

/* ARGS FUNC */
void	get_port(t_arg_infos *infos, char *argv[]);
void	get_world_x(t_arg_infos *infos, char *argv[]);
void	get_world_y(t_arg_infos *infos, char *argv[]);
void	get_teams_names(t_arg_infos *infos, char *argv[]);
void	get_clients_per_team(t_arg_infos *infos, char *argv[]);
void	get_action_delay(t_arg_infos *infos, char *argv[]);
void	unknown_options(t_arg_infos *infos, char *argv[]);
void	print_help(t_arg_infos *infos, char *argv[]);
void	set_seed(t_arg_infos *infos, char *argv[]);

/* TOOLS */
bool	contains_only_digits(char *str);
void	invalid_param(t_arg_infos *infos, const char *msg);
int	cmp_team(void *t1, void *t2);
void	push_team(t_arg_infos *infos, const char *name);
int	update_teams_slots(void *t, void *val);

#endif /* !__ARGS_H__*/
