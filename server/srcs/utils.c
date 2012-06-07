/*
** utils.c for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Mon May 14 20:10:30 2012 Jonathan Machado
** Last update Thu Jun  7 19:08:45 2012 lois burg
*/

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "refstring.h"

int		cmp_socket(void *a, void *b)
{
  t_users	*u;
  int		*s;

  u = a;
  s = b;
  return (!(u->socket == *s));
}

int	contains_only_digits(char *str)
{
  int	i;
  int	good;

  i = 0;
  good = 1;
  while (good && str && str[i])
    {
      if (!isdigit(str[i]))
	good = 0;
      ++i;
    }
  return (good);
}

static	void	prt_team_name(void *name)
{
  printf("\tName: %s\n", (char*)name);
}

void	print_serv_conf(t_arg_infos *world_info)
{
  if (world_info)
    {
      printf("Server configuration:\n");
      printf("\tMax client: %d\n", world_info->clients_per_team);
      printf("\tWorld size:\n\t\tX: %d\n\t\tY: %d\n",
	     world_info->world_x, world_info->world_y);
      printf("\tDelay: %d\n", world_info->action_delay);
      printf("Teams:\n");
      iterate(world_info->teams_names, &prt_team_name);
    }
  else
    fprintf(stderr, "Invalid world information (nullptr).\n");
}

void	invalid_param(t_arg_infos *infos, const char *msg)
{
  fprintf(stderr, "%s\n", msg);
  infos->error = true;
}
