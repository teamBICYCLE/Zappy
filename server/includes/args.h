/*
** args.h for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Mon Jun  4 15:29:23 2012 lois burg
** Last update Thu Jun  7 19:04:06 2012 lois burg
*/

#ifndef		__ARGS_H__
# define	__ARGS_H__

# include	<stdbool.h>
# include	"libdatac_list.h"

typedef	struct s_arg_func	t_arg_func;
typedef	struct s_arg_infos	t_arg_infos;

struct	s_arg_func
{
  char	arg;
  void	(*fun)(t_arg_infos *world_infos, char *argv[]);
};

struct	s_arg_infos
{
  int			port;
  int			world_x;
  int			world_y;
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
int	contains_only_digits(char *str);
void	invalid_param(t_arg_infos *infos, const char *msg);

#endif /* !__ARGS_H__*/
