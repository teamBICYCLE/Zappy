/*
** args_func3.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server/srcs
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Thu Jul 12 14:49:29 2012 lois burg
** Last update Fri Jul 13 12:10:08 2012 lois burg
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "args.h"

static confParamFct_t	g_set_conf_param[3] =
  {
    &set_max_res_case, &set_food_pctg, &set_stones_pctg
  };

static void	apply_conf(FILE *stream, t_arg_infos *infos)
{
  int		i;
  char		*line;
  size_t	useless;
  bool		ret;

  i = 0;
  line = NULL;
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
}

void		read_conf(t_arg_infos *infos, char *argv[])
{
  FILE		*stream;

  (void)argv;
  if ((stream = fopen(optarg, "r")) != NULL)
    apply_conf(stream, infos);
  else
    {
      fprintf(stderr, "-f: Failed to open %s.\n", optarg);
      infos->error = true;
    }
}

void		compute_smallest_time(t_arg_infos *infos)
{
  int		integer;
  double	decimal;

  integer = 1 / infos->action_delay;
  decimal = (1.f / infos->action_delay) - integer;
  infos->smallest_t.tv_sec = integer;
  infos->smallest_t.tv_usec = (decimal + 0.0000001) * 1000000.f;
}
