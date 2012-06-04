/*
** args_func1.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Mon Jun  4 15:57:46 2012 lois burg
** Last update Mon Jun  4 17:05:28 2012 lois burg
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
    fprintf(stderr, "-p: Invalid port number.\n");
}

void	get_world_x(t_arg_infos *infos, char *argv[])
{
  (void)argv;
  if (contains_only_digits(optarg))
    infos->world_x = strtol(optarg, NULL, 10);
  else
    fprintf(stderr, "-x: Invalid size.\n");
}

void	get_world_y(t_arg_infos *infos, char *argv[])
{
  (void)argv;
  if (contains_only_digits(optarg))
    infos->world_y = strtol(optarg, NULL, 10);
  else
    fprintf(stderr, "-y: Invalid size.\n");
}

void	get_teams_names(t_arg_infos *infos, char *argv[])
{
  int	i;

  i = optind;
  push_back(infos->teams_names, new_link_by_param(optarg, strlen(optarg)));
  while (argv[i] && argv[i][0] != '-')
    {
      push_back(infos->teams_names, new_link_by_param(argv[i], strlen(argv[i])));
      ++i;
    }
}

void	get_clients_per_team(t_arg_infos *infos, char *argv[])
{
  (void)argv;
  if (contains_only_digits(optarg))
    infos->clients_per_team = strtol(optarg, NULL, 10);
  else
    fprintf(stderr, "-c: Invalid number.\n");
}
