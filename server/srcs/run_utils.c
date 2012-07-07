/*
** run_utils.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server/srcs
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Sat Jul  7 13:27:05 2012 lois burg
** Last update Sat Jul  7 13:52:11 2012 lois burg
*/

#include "server.h"

extern t_infos	g_info;

void	treat_clients(struct timeval *loop, int *sync)
{
  if (FD_ISSET(g_info.ss, &g_info.readfds))
    add_user();
  iterate(g_info.users, &read_user);
  if ((loop->tv_sec <= 0 && loop->tv_usec <= 0) || (*sync) != 0)
    {
      if (loop->tv_sec <= 0 && loop->tv_usec <= 0)
	++(*sync);
      update_map(*sync);
      (*loop) = g_info.world.smallest_t;
      (*sync) = 0;
    }
  iterate(g_info.users, &write_user);
}

void			handle_time(struct timeval *start, struct timeval *end,
				    struct timeval *loop, int *sync)
{
  int			diff;
  const time_t		ss = start->tv_sec;
  const time_t		es = end->tv_sec;
  const suseconds_t	sus = start->tv_usec;
  const suseconds_t	eus = end->tv_usec;
  int const		gs = g_info.world.smallest_t.tv_sec * 1000000;
  int const		gus = g_info.world.smallest_t.tv_usec;
  int const		st = gs + gus;

  (*sync) += (((es * 1000000 + eus) - (ss * 1000000 + sus)) / st);
  diff = (((es * 1000000 + eus) - (ss * 1000000 + sus)) % st);
  diff = (loop->tv_usec + loop->tv_sec * 1000000) - diff;
  if (diff < 0)
    {
      ++(*sync);
      diff += st;
    }
  loop->tv_usec = diff % 1000000;
  loop->tv_sec = diff / 1000000;
}
