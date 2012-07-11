/*
** args_func2.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Mon Jun  4 16:07:36 2012 lois burg
** Last update Wed Jul 11 16:12:44 2012 lois burg
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "args.h"

static confParamFct_t	g_set_conf_param[3] =
  {
    &set_max_res_case, &set_food_pctg, &set_stones_pctg
  };

void		get_action_delay(t_arg_infos *infos, char *argv[])
{
  int		integer;
  double	decimal;
  long int	nb;

  (void)argv;
  if (contains_only_digits(optarg) && (nb = strtol(optarg, NULL, 10)) > 0 &&
      nb <= MAX_FREQUENCY)
    {
      infos->action_delay = nb;
      integer = 1 / infos->action_delay;
      decimal = (1.f / infos->action_delay) - integer;
      infos->smallest_t.tv_sec = integer;
      infos->smallest_t.tv_usec = (decimal + 0.0000001) * 1000000.f;
    }
  else
    invalid_param(infos, "-t: Invalid time. "
		  "Must be a positive, non-null integer <= 100,000.");
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
  printf("Usage: ./zappyd [-p PORT] [-x WIDTH] [-y HEIGHT] [-c CLIENTS]"
	 " [-t DELAY] [-s SEED] [-h] -n team1 team2 [... teamn]\n");
  printf("Options description:\n");
  printf("\t-p <int>: Port to use (default is 4242).\n");
  printf("\t-x <int>: World width (default is 20).\n");
  printf("\t-y <int>: World height (default is 20).\n");
  printf("\t-n <string> ...: Team names. This parameter is mandatory.\n");
  printf("\t-c <int>: Max clients number allowed per team (default is 1).\n");
  printf("\t-t <int>: Delay between actions (default is 100).\n");
  printf("\t-s <int>: The seed used to generate the map (default is time).\n");
  printf("\t-f <string>: The file to read the server configuration from.\n");
  printf("\t-h: Display this help and quits.\n");
  infos->help_showed = true;
}

void	set_seed(t_arg_infos *infos, char *argv[])
{
  (void)argv;
  if (contains_only_digits(optarg))
    {
      infos->seed = strtol(optarg, NULL, 10);
      infos->seed_spec = true;
    }
  else
    invalid_param(infos, "-s: Invalid seed. Must be a numeric value.");
}

void		read_conf(t_arg_infos *infos, char *argv[])
{
  int		i;
  FILE		*stream;
  char		*line;
  size_t	useless;
  bool		ret;

  (void)argv;
  i = 0;
  line = NULL;
  if ((stream = fopen(optarg, "r")) != NULL)
    while (infos->error == false && i < CONF_FILE_LINES &&
	   getline(&line, &useless, stream) != -1)
      {
	ret = false;
	if (line)
	  line[strlen(line) - 1] = 0;
	if (contains_only_digits(line))
	  ret = (g_set_conf_param[i])(strtol(line, NULL, 10));
	if (ret == false)
	  {
	    fprintf(stderr, "-f: Bad conf file (line %i).\n", i + 1);
	    infos->error = true;
	  }
	free(line);
	line = NULL;
	++i;
      }
  else
    {
      fprintf(stderr, "-f: Failed to open %s.\n", optarg);
      infos->error = true;
    }
}
