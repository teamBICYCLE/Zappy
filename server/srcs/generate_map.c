/*
** generate_ressources.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Fri Jun  8 11:28:02 2012 lois burg
** Last update Fri Jul 13 12:01:13 2012 lois burg
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "diamond_generation.h"
#include "map.h"

double		g_max_res_case = 3;
double		g_food_pctg = 40;
double		g_stones_pctg = 10;

static void	fill_map(t_map *map, t_dmap *dmap,
			 const int elem, const int pctg)
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
	    map->cases[y][x].elements[elem] += (rand() % (int)(g_max_res_case + 1));
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
  if ((map = new_map(x, y)))
    {
      prefill(map);
      if ((dmap = compute_dmap(x, y, seed++)) != NULL)
      	fill_map(map, dmap, FOOD, (g_food_pctg * dmap->max_val) / 100.f);
      if ((dmap = compute_dmap(x, y, seed++)) != NULL)
      	fill_map(map, dmap, LINEMATE, (g_stones_pctg * dmap->max_val) / 100.f);
      if ((dmap = compute_dmap(x, y, seed++)) != NULL)
      	fill_map(map, dmap, DERAUMERE, (g_stones_pctg * dmap->max_val) / 100.f);
      if ((dmap = compute_dmap(x, y, seed++)) != NULL)
      	fill_map(map, dmap, SIBUR, (g_stones_pctg * dmap->max_val) / 100.f);
      if ((dmap = compute_dmap(x, y, seed++)) != NULL)
      	fill_map(map, dmap, MENDIANE, (g_stones_pctg * dmap->max_val) / 100.f);
      if ((dmap = compute_dmap(x, y, seed++)) != NULL)
      	fill_map(map, dmap, PHIRAS, (g_stones_pctg * dmap->max_val) / 100.f);
      if ((dmap = compute_dmap(x, y, seed++)) != NULL)
      	fill_map(map, dmap, THYSTAME, (g_stones_pctg * dmap->max_val) / 100.f);
    }
  puts("Done!");
  return (map);
}
