/*
** diamond_generation.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Wed Jun  6 16:02:25 2012 lois burg
** Last update Thu Jun  7 14:03:00 2012 lois burg
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

static void	diamond_step(const int x, const int y, const int s, double **map)
{
  double	avg;

  avg = map[y][x] + map[y + s][x] + map[y + s][x + s] + map[y][x + s];
  avg /= 4;
  map[y + (s / 2)][x + (s / 2)] =
    avg + (((double)rand() / (double)RAND_MAX) * RAND_RANGE);
}

static void	square_step(const int x, const int y, t_dmap *dmap, const int size)
{
  const int	half_step = dmap->step / 2;

  dmap->map[y][x + half_step] = avg_diamond(x + half_step, y, dmap, size);
  dmap->map[y + half_step][x] = avg_diamond(x, y + half_step, dmap, size);
  dmap->map[y + dmap->step][x + half_step] =
    avg_diamond(x + half_step, y + dmap->step, dmap, size);
  dmap->map[y + half_step][x + dmap->step] =
    avg_diamond(x + dmap->step, y + half_step, dmap, size);
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
	  diamond_step(x * dmap->step, y * dmap->step, dmap->step, dmap->map);
	  square_step(x * dmap->step, y * dmap->step, dmap, size);
	  ++x;
	}
      ++y;
    }
}

static double	**alloc_map(int size)
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

void		generate_map(const int x, const int y, int seed)
{
  const int	size = ODDIFY(pow_two(MAX(x, y)));
  int		nb_iter;
  t_dmap	dmap;

  printf("Generating map of size %d...\n", size - 1);
  dmap.map = alloc_map(size);
  nb_iter = 1;
  dmap.step = size - 1;
  srand(seed);
  dmap.map[0][0] = rand() % RAND_RANGE;
  dmap.map[size - 1][0] = rand() % RAND_RANGE;
  dmap.map[size - 1][size - 1] = rand() % RAND_RANGE;
  dmap.map[0][size - 1] = rand() % RAND_RANGE;
  printf("map[0][0] = %.1f\n", dmap.map[0][0]);
  printf("map[s][0] = %.1f\n", dmap.map[size - 1][0]);
  printf("map[s][s] = %.1f\n", dmap.map[size - 1][size - 1]);
  printf("map[0][s] = %.1f\n", dmap.map[0][size - 1]);
  while (dmap.step > 1)
    {
      do_step(nb_iter, &dmap, size);
      dmap.step /= 2;
      nb_iter *= 2;
    }

  //TEMPORARY
  int i = 0, j = 0;
  while (j < size)
    {
      i = 0;
      while (i < size)
  	{
  	  printf("[%.1f]", dmap.map[j][i]);
  	  ++i;
  	  if (i < size)
  	    printf(" ");
  	}
      ++j;
      printf("\n");
    }
  free(dmap.map);
}
