/*
** args.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Mon Jun  4 15:29:04 2012 lois burg
** Last update Thu Jun  7 10:39:02 2012 lois burg
*/

#include <stdlib.h>
#include <unistd.h>
#include "args.h"

static	t_arg_func	g_arg_func_tab[] =
  {
    {'p', &get_port},
    {'x', &get_world_x},
    {'y', &get_world_y},
    {'n', &get_teams_names},
    {'c', &get_clients_per_team},
    {'t', &get_action_delay},
    {'h', &print_help},
    {'?', &unknown_options},
    {-1, NULL}
  };

static void	init_args_infos(t_arg_infos *infos)
{
  infos->port = 24542;
  infos->world_x = 20;
  infos->world_y = 20;
  infos->teams_names = new_list();
  infos->clients_per_team = 1;
  infos->action_delay = 100;
  infos->help_showed = false;
}

void	parse_args(int argc, char *argv[], t_arg_infos *infos)
{
  int	i;
  int	opt;

  init_args_infos(infos);
  while ((opt = getopt(argc, argv, "p:x:y:n:c:t:h")) != -1)
    {
      i = 0;
      while (g_arg_func_tab[i].arg != -1 && g_arg_func_tab[i].arg != opt)
	++i;
      if (g_arg_func_tab[i].fun)
	(g_arg_func_tab[i].fun)(infos, argv);
    }
}
