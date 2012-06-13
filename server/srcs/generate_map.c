/*
** generate_ressources.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Fri Jun  8 11:28:02 2012 lois burg
** Last update Wed Jun 13 18:33:04 2012 Jonathan Machado
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "diamond_generation.h"
#include "map.h"

static void	fill_map(t_map *map, t_dmap *dmap, const int elem, const int pctg)
{
  uint	x;
  uint	y;

  y = 0;
  while (y < map->y)
    {
      x = 0;
      while (x < map->x)
	{
	  if (dmap->map[y][x] <= pctg)
	    map->cases[y][x].elements[elem] += (rand() % 3) + 1;
	  ++x;
	}
      ++y;
    }
  free_dmap(&dmap);
}

t_map		*generate_map(const int x, const int y, int seed)
{
  t_map		*map;
  t_dmap	*dmap;

  puts("Generating map...");
  map = new_map(x, y);
  dmap = compute_dmap(x, y, seed++);
  fill_map(map, dmap, FOOD, (FOOD_PCTG * dmap->max_val) / 100.f);
  dmap = compute_dmap(x, y, seed++);
  fill_map(map, dmap, LINEMATE, (LINEMATE_PCTG * dmap->max_val) / 100.f);
  dmap = compute_dmap(x, y, seed++);
  fill_map(map, dmap, DERAUMERE, (DERAUMERE_PCTG * dmap->max_val) / 100.f);
  dmap = compute_dmap(x, y, seed++);
  fill_map(map, dmap, SIBUR, (SIBUR_PCTG * dmap->max_val) / 100.f);
  dmap = compute_dmap(x, y, seed++);
  fill_map(map, dmap, MENDIANE, (MENDIANE_PCTG * dmap->max_val) / 100.f);
  dmap = compute_dmap(x, y, seed++);
  fill_map(map, dmap, PHIRAS, (PHIRAS_PCTG * dmap->max_val) / 100.f);
  dmap = compute_dmap(x, y, seed++);
  fill_map(map, dmap, THYSTAME, (THYSTAME_PCTG * dmap->max_val) / 100.f);
  puts("Done!");
  return (map);
}
