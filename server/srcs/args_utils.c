/*
** args_utils.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Mon Jun 18 14:08:35 2012 lois burg
** Last update Thu Jul  5 11:19:19 2012 lois burg
*/

#include <string.h>
#include "args.h"

void		push_team(t_arg_infos *infos, const char *name)
{
  t_team	t;

  if (!strcmp(name, "GRAPHIC"))
    invalid_param(infos, "-n: Invalid team name.");
  else
    {
      t.name = strdup(name);
      t.free_slots = infos->clients_per_team;
      t.nb_max_lvl = 0;
      push_back(infos->teams_names, new_link_by_param(&t, sizeof(t)));
    }
}

int	update_teams_slots(void *t, void *val)
{
  ((t_team*)t)->free_slots = *(int*)val;
  return (1);
}
