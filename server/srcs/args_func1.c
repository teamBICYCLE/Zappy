/*
** args_func1.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Mon Jun  4 15:57:46 2012 lois burg
** Last update Fri Jun 15 12:32:41 2012 lois burg
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "args.h"

void	get_port(t_arg_infos *infos, char *argv[])
{
  (void)argv;
  if (contains_only_digits(optarg))
    infos->port = strtol(optarg, NULL, 10);
  else
    invalid_param(infos, "-p: Invalid port. Must be a positive numeric value.");
}

void		get_world_x(t_arg_infos *infos, char *argv[])
{
  long int	nb;

  (void)argv;
  if (contains_only_digits(optarg) && (nb = strtol(optarg, NULL, 10)) >= 4)
    infos->x = nb;
  else
    invalid_param(infos, "-x: Invalid width. Must be >= 4.");
}

void		get_world_y(t_arg_infos *infos, char *argv[])
{
  long int	nb;

  (void)argv;
  if (contains_only_digits(optarg) && (nb = strtol(optarg, NULL, 10)) >= 4)
    infos->y = nb;
  else
    invalid_param(infos, "-y: Invalid height. Must be >= 4.");
}

void	get_teams_names(t_arg_infos *infos, char *argv[])
{
  int	i;

  i = optind;
  if (!strcmp(optarg, "GRAPHIC"))
    invalid_param(infos, "-n: Invalid team name.");
  else
    push_back(infos->teams_names, new_link_by_param(optarg, strlen(optarg) + 1));
  while (!infos->error && argv[i] && argv[i][0] != '-')
    {
      if (!strcmp(argv[i], "GRAPHIC"))
	invalid_param(infos, "-n: Invalid team name.");
      else if (is_in_list(infos->teams_names, argv[i], &cmp_team))
	invalid_param(infos, "-n: Team already added.");
      else
	push_back(infos->teams_names, new_link_by_param(argv[i], strlen(argv[i]) + 1));
      ++i;
    }
}

void		get_clients_per_team(t_arg_infos *infos, char *argv[])
{
  long int	nb;

  (void)argv;
  if (contains_only_digits(optarg) && (nb = strtol(optarg, NULL, 10)))
    infos->clients_per_team = nb;
  else
    invalid_param(infos, "-c: Invalid number. Must be > 0.");
}
