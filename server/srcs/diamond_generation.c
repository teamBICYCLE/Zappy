/*
** diamond_generation.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Wed Jun  6 16:02:25 2012 lois burg
** Last update Wed Jul  4 17:32:19 2012 lois burg
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "diamond_generation.h"

static size_t	pow_two(size_t nbr)
{
  size_t	power;

  power = 1;
  while (power < nbr)
    power <<= 1;
  return (power);
}

static void	diamond_step(const int x, const int y, t_dmap *dmap)
{
  double	avg;
  double	**map = dmap->map;
  const int	s = dmap->step;

  avg = map[y][x] + map[y + s][x] + map[y + s][x + s] + map[y][x + s];
  avg /= 4;
  avg += (((double)rand() / (double)RAND_MAX) * 2 * NOISE) - NOISE;
  map[y + (s / 2)][x + (s / 2)] = avg;
  if (avg > dmap->max_val)
    dmap->max_val = avg;
}

static void	square_step(const int x, const int y, t_dmap *dmap, const int s)
{
  const int	half_step = dmap->step / 2;

  dmap->map[y][x + half_step] = avg_diamond(x + half_step, y, dmap, s);
  dmap->map[y + half_step][x] = avg_diamond(x, y + half_step, dmap, s);
  dmap->map[y + dmap->step][x + half_step] =
    avg_diamond(x + half_step, y + dmap->step, dmap, s);
  dmap->map[y + half_step][x + dmap->step] =
    avg_diamond(x + dmap->step, y + half_step, dmap, s);
}

static void	do_step(const int nb_iter, t_dmap *dmap, const int size)
{
  int		y;
  int		x;

  y = 0;
  while (y < nb_iter)
    {
      x = 0;
      while (x < nb_iter)
	{
	  diamond_step(x * dmap->step, y * dmap->step, dmap);
	  square_step(x * dmap->step, y * dmap->step, dmap, size);
	  ++x;
	}
      ++y;
    }
}

t_dmap		*compute_dmap(const int x, const int y, const int seed)
{
  const int	size = ODDIFY(pow_two(MAX(x, y)));
  int		nb_iter;
  t_dmap	*dmap;

  dmap = new_dmap(size);
  nb_iter = 1;
  srand(seed);
  dmap->map[0][0] = (rand() % RAND_RANGE);
  dmap->map[size - 1][0] = (rand() % RAND_RANGE);
  dmap->map[size - 1][size - 1] = (rand() % RAND_RANGE);
  dmap->map[0][size - 1] = (rand() % RAND_RANGE);
  while (dmap->step > 1)
    {
      do_step(nb_iter, dmap, size);
      dmap->step /= 2;
      nb_iter *= 2;
    }
  /* printf("Max value: %.1f\n", dmap->max_val); */

  /*TEMPORARY*/
  /* int i = 0, j = 0; */
  /* while (j < size) */
  /*   { */
  /*     i = 0; */
  /*     while (i < size) */
  /* 	{ */
  /* 	  printf("[%.1f]", dmap->map[j][i]); */
  /* 	  ++i; */
  /* 	  if (i < size) */
  /* 	    printf(" "); */
  /* 	} */
  /*     ++j; */
  /*     printf("\n"); */
  /*   } */
  return (dmap);
}
