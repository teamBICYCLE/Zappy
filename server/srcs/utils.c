/*
** utils.c for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Mon May 14 20:10:30 2012 Jonathan Machado
** Last update Wed Jul 11 15:10:30 2012 lois burg
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

bool	contains_only_digits(char *str)
{
  int	i;
  bool	good;

  i = 0;
  good = true;
  while (good && str && str[i])
    {
      if (!isdigit(str[i]))
	good = false;
      ++i;
    }
  if (strlen(str) == 0)
    good = false;
  return (good);
}

static	void	prt_team_name(void *t)
{
  const t_team	*team = (t_team*)t;

  printf("\tName: %s, slots: %d\n", team->name, team->free_slots);
}

void	print_serv_conf(t_arg_infos *world)
{
  if (world)
    {
      printf("Server configuration:\n");
      printf("\tMax client: %d\n", world->clients_per_team);
      printf("\tWorld size:\n\t\tX: %d\n\t\tY: %d\n",
	     world->x, world->y);
      printf("\tDelay: %d\n", world->action_delay);
      printf("Teams:\n");
      iterate(world->teams_names, &prt_team_name);
    }
  else
    fprintf(stderr, "Invalid world information (nullptr).\n");
}

void	invalid_param(t_arg_infos *infos, const char *msg)
{
  fprintf(stderr, "%s\n", msg);
  infos->error = true;
}
