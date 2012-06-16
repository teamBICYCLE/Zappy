/*
** answer_grapphics1.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Sat Jun 16 17:22:31 2012 lois burg
** Last update Sat Jun 16 19:19:13 2012 lois burg
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "graphics.h"

extern t_infos	g_info;

void	answer_msz(t_users *usr, char **args)
{
  char	*msg;

  (void)args;
  msg = graphics_msz();
  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
}

void	answer_bct(t_users *usr, char **args)
{
  uint	x;
  uint	y;
  char	*msg;

  if (args && args[0] && args[1] &&
      contains_only_digits(args[0]) && contains_only_digits(args[1]))
    {
      x = strtol(args[0], NULL, 10);
      y = strtol(args[1], NULL, 10);
      if (x < g_info.map->x && y < g_info.map->y)
	msg = graphics_bct(x, y);
      else
	msg = graphics_sbp();
    }
  else
    msg = graphics_sbp();
  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
}

void	answer_mct(t_users *usr, char **args)
{
  uint	x;
  uint	y;
  char	*msg;

  (void)args;
  y = 0;
  while (y < g_info.map->y)
    {
      x = 0;
      while (x < g_info.map->x)
	{
	  msg = graphics_bct(x, y);
	  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
	  ++x;
	}
      ++y;
    }
}

void	answer_tna(t_users *usr, char **args)
{
  char	*msg;

  (void)args;
  msg = graphics_tna();
  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
}

void		answer_ppo(t_users *usr, char **args)
{
  int		id;
  char		*msg;
  t_link	*plyr;

  if (args && args[0] && args[0][0] == '#' &&
      contains_only_digits(args[0] + 1))
    {
      id = strtol(args[0] + 1, NULL, 10);
      if ((plyr = lookup(g_info.users, &id, &cmp_id)))
	msg = graphics_ppo((t_users*)plyr->ptr);
      else
	msg = graphics_sbp();
    }
  else
    msg = graphics_sbp();
  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
}
