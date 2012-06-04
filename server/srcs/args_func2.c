/*
** args_func2.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Mon Jun  4 16:07:36 2012 lois burg
** Last update Mon Jun  4 17:03:36 2012 lois burg
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "args.h"

void	get_action_delay(t_arg_infos *infos, char *argv[])
{
  (void)argv;
  if (contains_only_digits(optarg))
    infos->action_delay = strtol(optarg, NULL, 10);
  else
    fprintf(stderr, "-t: Invalid time.\n");
}

void	unknown_options(t_arg_infos *infos, char *argv[])
{
  (void)infos;
  (void)argv;
  fprintf(stderr, "%d: Unknown option.\n", optopt);
}
