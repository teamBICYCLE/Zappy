/*
** broadcast_cmd.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Tue Jun 19 16:39:50 2012 lois burg
** Last update Wed Jun 20 17:33:35 2012 Jonathan Machado
*/

#include <string.h>
#include <stdio.h>
#include <math.h>
#include "graphics.h"
#include "server.h"
#include "cmds.h"

extern t_infos	g_info;

static int	get_angle(int xs, int ys, int xr, int yr)
{
  int		i;
  int		shorter;
  const	int	x[] = {
    xr, xr + g_info.map->x, xr - g_info.map->x, xr, xr, xr + g_info.map->x,
    xr - g_info.map->x, xr + g_info.map->x, xr - g_info.map->x};
  const int	y[] = {
    yr, yr, yr, yr + g_info.map->y, yr - g_info.map->y, yr + g_info.map->y,
    yr - g_info.map->y, yr - g_info.map->y, yr + g_info.map->y};
  const	int	dists[] = {
    pow(xs - x[0], 2) + pow(ys - y[0], 2), pow(xs - x[1], 2) + pow(ys - y[1], 2),
    pow(xs - x[2], 2) + pow(ys - y[2], 2), pow(xs - x[3], 2) + pow(ys - y[3], 2),
    pow(xs - x[4], 2) + pow(ys - y[4], 2), pow(xs - x[5], 2) + pow(ys - y[5], 2),
    pow(xs - x[6], 2) + pow(ys - y[6], 2), pow(xs - x[7], 2) + pow(ys - y[7], 2),
    pow(xs - x[8], 2) + pow(ys - y[8], 2)};

  i = 1;
  shorter = 0;
  while (i < 9)
    {
      if (dists[shorter] > dists[i])
	shorter = i;
      ++i;
    }
  return ((xs - x[shorter]) *  + (ys - y[shorter]) * );
}

static void	send_msg(const t_users *sender, t_users *recvr, const char *broadcast)
{
  char		msg[BASE_BROADCAST_SZ + strlen(broadcast) + 1];

  printf("angle : %d\n", get_angle(sender->x, sender->y, recvr->x, recvr->y));
  snprintf(msg, sizeof(msg), "message 0,%s\n", broadcast);
  push_back(recvr->messages, new_link_by_param(msg, strlen(msg) + 1));
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
  printf("Message to broadcast: %s\n", msg);
  i = 0;
  while (i < g_info.users->size)
    {
      if ((rcvr_lnk = get_link(g_info.users, i)))
	{
	  rcvr = (t_users*)rcvr_lnk->ptr;
	  if (rcvr != usr)
	    send_msg(usr, rcvr, msg);
	}
      ++i;
    }
  lookup(g_info.users, graphics_pbc(usr, msg), &notify_graphic);
  return (SUCCESS);
}
