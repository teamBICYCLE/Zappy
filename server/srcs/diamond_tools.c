/*
** diamond_tools.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Wed Jun  6 19:20:53 2012 lois burg
** Last update Fri Jun  8 11:50:28 2012 lois burg
*/

#include <string.h>
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
  avg += (((double)rand() / (double)RAND_MAX) * RAND_RANGE);
  if (avg > dmap->max_val)
    dmap->max_val = avg;
  return (avg);
}

static double	**alloc_map(const int size)
{
  int		i;
  double	**map;

  i = 0;
  map = malloc(size * sizeof(*map));
  while (i < size)
    {
      map[i] = malloc(size * sizeof(**map));
      memset(map[i], 0, size * sizeof(**map));
      ++i;
    }
  return (map);
}

t_dmap		*new_dmap(const int size)
{
  t_dmap	*dmap;

  dmap = malloc(sizeof(*dmap));
  dmap->size = size;
  dmap->max_val = 0;
  dmap->step = dmap->size - 1;
  dmap->map = alloc_map(dmap->size);
  return (dmap);
}

void		free_dmap(t_dmap **dmap)
{
  double	**map = (*dmap)->map;
  const int	size = (*dmap)->size;
  int		i;

  i = 0;
  while (i < size)
    free(map[i++]);
  free(map);
  free(*dmap);
  *dmap = NULL;
}
