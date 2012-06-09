/*
** fill_map.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Sat Jun  9 10:14:51 2012 lois burg
** Last update Sat Jun  9 12:04:17 2012 lois burg
*/

#include <stdlib.h>
#include "diamond_generation.h"

void	fill_map_ud(t_dmap *dmap, t_map *map, t_map_iteration *it, const double pctg)
{
  int	x;
  int	y;
  int	cmp_gt;

  y = it->beg_y;
  while (y != it->end_y)
    {
      x = it->beg_x;
      while (x != it->end_x)
	{
	  cmp_gt = rand() % 2;
	  if (cmp_gt && dmap->map[y][x] >= pctg)
	    map->cases[y][x].elements[it->elem] += (rand() % 4) + 1;
	  else if (dmap->map[y][x] <= pctg)
	    map->cases[y][x].elements[it->elem] += (rand() % 4) + 1;
	  x += it->inc_x;
	}
      y += it->inc_y;
    }
}

void	fill_map_lr(t_dmap *dmap, t_map *map, t_map_iteration *it, const double pctg)
{
  int	x;
  int	y;
  int	cmp_gt;

  y = it->beg_y;
  while (y != it->end_y)
    {
      x = it->beg_x;
      while (x != it->end_x)
	{
	  cmp_gt = rand() % 2;
	  if (cmp_gt && dmap->map[y][x] >= pctg)
	    map->cases[x][y].elements[it->elem] += (rand() % 4) + 1;
	  else if (dmap->map[y][x] <= pctg)
	    map->cases[x][y].elements[it->elem] += (rand() % 4) + 1;
	  x += it->inc_x;
	}
      y += it->inc_y;
    }
}
