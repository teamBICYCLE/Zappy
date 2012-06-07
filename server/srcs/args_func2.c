/*
** args_func2.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Mon Jun  4 16:07:36 2012 lois burg
** Last update Thu Jun  7 19:23:05 2012 lois burg
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "args.h"

void		get_action_delay(t_arg_infos *infos, char *argv[])
{
  int		integer;
  double	decimal;

  (void)argv;
  if (contains_only_digits(optarg) && strtol(optarg, NULL, 10) != 0)
    {
      infos->action_delay = strtol(optarg, NULL, 10);
      integer = 7 / infos->action_delay;
      decimal = (7.f / infos->action_delay) - integer;
      infos->smallest_t.tv_sec = integer;
      infos->smallest_t.tv_usec = decimal * 100000.f;
    }
  else
    invalid_param(infos, "-t: Invalid time. "
		  "Must be a positive, non-null numeric value.");
}

void	unknown_options(t_arg_infos *infos, char *argv[])
{
  (void)infos;
  (void)argv;
  fprintf(stderr, "%d: Unknown option.\n", optopt);
}

void	print_help(t_arg_infos *infos, char *argv[])
{
  (void)argv;
  printf("How does this server work ?\n");
  printf("Here are the valid options:\n");
  printf("\t-p <int>: Port to use (default is 4242).\n");
  printf("\t-x <int>: World width (default is 20).\n");
  printf("\t-y <int>: World height (default is 20).\n");
  printf("\t-n <string> ...: Team names. This parameter is mandatory.\n");
  printf("\t-c <int>: Max clients number allowed per team (default is 1).\n");
  printf("\t-t <int>: Delay between actions (default is 100).\n");
  printf("\t-s <int>: The seed used to generate the map (default is time).\n");
  printf("\t-h: Display this help and quits.\n");
  printf("Any invalid options will not stop ");
  infos->help_showed = true;
}

void	set_seed(t_arg_infos *infos, char *argv[])
{
  (void)argv;
  if (contains_only_digits(optarg))
    infos->seed = strtol(optarg, NULL, 10);
  else
    invalid_param(infos, "-s: Invalid seed. Must be a positive numeric value.");
}
