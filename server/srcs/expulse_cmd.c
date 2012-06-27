/*
** expulse_cmd.c for  in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Wed Jun 27 16:46:56 2012 Jonathan Machado
** Last update Wed Jun 27 17:42:21 2012 Jonathan Machado
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cmds.h"
#include "server.h"
#include "log.h"
#include "graphics.h"

extern t_infos	g_info;

static	t_dir_mov	g_dir_tab[4] =
  {
    {0, -1},
    {1, 0},
    {0, 1},
    {-1, 0}
  };

static int	expulse(t_users *sender, t_users *recvr)
{
  char		msg[EXPULSE_MSG_SZ];
  int		x[2];
  int		y[2];

  recvr->x = (recvr->x + g_dir_tab[sender->dir].dx + g_info.map->x) % g_info.map->x; ;
  recvr->y = (recvr->y + g_dir_tab[sender->dir].dy + g_info.map->y) % g_info.map->y;;
  x[0] = sender->x;
  y[0] = sender->y;
  x[1] = recvr->x;
  y[1] = recvr->y;
  snprintf(msg, sizeof(msg), "deplacement: %i\n", get_case(x, y, recvr->dir));
  push_back(recvr->messages, new_link_by_param(msg, strlen(msg) + 1));
  lookup(g_info.users, graphics_ppo(recvr), &notify_graphic);
  return (1);
}

t_cmd_ret	expulse_cmd(t_users *usr, char **args, char *orig_cmd)
{
  uint		i;
  int		nb;
  t_users	*rcvr;
  t_link	*rcvr_lnk;

  i = 0;
  nb = 0;
  (void)orig_cmd;
  (void)args;
  while (i < g_info.users->size)
    {
      if ((rcvr_lnk = get_link(g_info.users, i)))
	{
	  rcvr = (t_users*)rcvr_lnk->ptr;
	  if (rcvr != usr && rcvr->type != TGRAPHICS &&
	      rcvr->x == usr->x && rcvr->y == usr->y)
	    nb += expulse(usr, rcvr);
	}
      ++i;
    }
  if (nb == 0)
    return (FAILURE);
  lookup(g_info.users, graphics_pex(usr), &notify_graphic);
  return (SUCCESS);
}
