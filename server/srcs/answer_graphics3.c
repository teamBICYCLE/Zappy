/*
** answer_graphics3.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Thu Jul  5 17:39:56 2012 lois burg
** Last update Thu Jul  5 17:57:18 2012 lois burg
*/

#include <stdlib.h>
#include <string.h>
#include "graphics.h"
#include "server.h"

extern t_infos	g_info;

void	answer_gkp(t_users *usr, char **args)
{
  int		id;
  char		*msg;
  t_link	*l;
  t_users	*p;

  if (args && args[0] &&
      contains_only_digits(args[0]))
    {
      id = strtol(args[0], NULL, 10);
      if ((l = lookup(g_info.users, &id, &cmp_id)))
	{
	  p = (t_users*)l->ptr;
	  if (p->type != TGRAPHICS && p->first_message == false)
	    {
	      msg = graphics_gkp(p);
	      remove_user(p);
	    }
	}
      else
	msg = graphics_sbp();
    }
  else
    msg = graphics_sbp();
  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
}
