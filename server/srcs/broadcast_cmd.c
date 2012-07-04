/*
** broadcast_cmd.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Tue Jun 19 16:39:50 2012 lois burg
** Last update Wed Jul  4 17:38:43 2012 lois burg
*/

#include <string.h>
#include <stdio.h>
#include "graphics.h"
#include "server.h"
#include "cmds.h"

extern t_infos	g_info;

static void	send_msg(const t_users *sender, t_users *rcvr, const char *broadcast)
{
  char		msg[BASE_BROADCAST_SZ + strlen(broadcast) + 1];
  int		x[2];
  int		y[2];

  x[0] = sender->x;
  x[1] = rcvr->x;
  y[0] = sender->y;
  y[1] = rcvr->y;
  snprintf(msg, sizeof(msg), "message %i,%s\n",
	   get_case(x, y, rcvr->dir), broadcast);
  push_back(rcvr->messages, new_link_by_param(msg, strlen(msg) + 1));
}

t_cmd_ret	broadcast_cmd(t_users *usr, char **args, char *orig_cmd)
{
  char		*msg;
  uint		i;
  t_users	*rcvr;
  t_link	*rcvr_lnk;

  (void)usr;
  (void)args;
  msg = strtok(orig_cmd, " \t");
  msg = strtok(NULL, "");
  if (msg == NULL)
    return (FAILURE);
  printf("Message to broadcast: %s\n", msg);
  i = 0;
  while (i < g_info.users->size)
    {
      if ((rcvr_lnk = get_link(g_info.users, i)))
	{
	  rcvr = (t_users*)rcvr_lnk->ptr;
	  if (rcvr != usr && rcvr->type != TGRAPHICS)
	    send_msg(usr, rcvr, msg);
	}
      ++i;
    }
  lookup(g_info.users, graphics_pbc(usr, msg), &notify_graphic);
  return (SUCCESS);
}
