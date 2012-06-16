/*
** answer_graphics2.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Sat Jun 16 17:59:16 2012 lois burg
** Last update Sat Jun 16 19:28:36 2012 lois burg
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "graphics.h"

extern t_infos	g_info;

void	answer_plv(t_users *usr, char **args)
{
  int		id;
  char		*msg;
  t_link	*plyr;

  if (args && args[0] &&
      contains_only_digits(args[0] + 1))
    {
      id = strtol(args[0] + 1, NULL, 10);
      if ((plyr = lookup(g_info.users, &id, &cmp_id)))
	msg = graphics_plv((t_users*)plyr->ptr);
      else
	msg = graphics_sbp();
    }
  else
    msg = graphics_sbp();
  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
}

void	answer_pin(t_users *usr, char **args)
{
  int		id;
  char		*msg;
  t_link	*plyr;

  if (args && args[0] &&
      contains_only_digits(args[0] + 1))
    {
      id = strtol(args[0] + 1, NULL, 10);
      if ((plyr = lookup(g_info.users, &id, &cmp_id)))
	msg = graphics_pin((t_users*)plyr->ptr);
      else
	msg = graphics_sbp();
    }
  else
    msg = graphics_sbp();
  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
}

void	answer_sgt(t_users *usr, char **args)
{
  char	*msg;

  (void)args;
  msg = graphics_sgt();
  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
}

void	answer_sst(t_users *usr, char **args)
{
  char	*msg;
  int	delay;

  if (args && args[0] &&
      contains_only_digits(args[0]))
    {
      delay = strtol(args[0], NULL, 10);
      if (delay != 0)
	{
	  g_info.world.action_delay = delay;
	  msg = graphics_sgt();
	}
      else
	msg = graphics_sbp();
    }
  else
    msg = graphics_sbp();
  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
}

void	answer_suc(t_users *usr, char **args)
{
  char	*msg;

  (void)args;
  msg = graphics_suc();
  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
}
