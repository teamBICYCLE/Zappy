/*
** diamond_tools.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Wed Jun  6 19:20:53 2012 lois burg
** Last update Thu Jun  7 11:05:18 2012 lois burg
*/

#include <stdlib.h>
#include "diamond_generation.h"

static void	add_avg(double *avg, double *sum, const double val)
{
  *avg += val;
  *sum += 1;
}

double		avg_diamond(const int x, const int y, t_dmap *dmap, const int size)
{
  double	avg;
  double	sum;
  const int	half_step = dmap->step / 2;

  avg = 0;
  sum = 0;
  if (x - half_step >= 0)
    add_avg(&avg, &sum, dmap->map[y][x - half_step]);
  if (y - half_step >= 0)
    add_avg(&avg, &sum, dmap->map[y - half_step][x]);
  if (x + half_step < size)
    add_avg(&avg, &sum, dmap->map[y][x + half_step]);
  if (y + half_step < size)
    add_avg(&avg, &sum, dmap->map[y + half_step][x]);
  avg /= sum;
  avg += (((double)rand() / (double)RAND_MAX) * 2 * RAND_RANGE) - RAND_RANGE;
  return (avg);
}
