/*
** generate_pt.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Fri Jun  8 12:34:06 2012 lois burg
** Last update Sat Jun  9 12:05:54 2012 lois burg
*/

#include "diamond_generation.h"
#include "map.h"

void	generate_phiras(t_map *map, t_dmap *dmap)
{
  t_map_iteration	it;

  it.beg_x = 0;
  it.beg_y = 0;
  it.end_x = map->x;
  it.end_y = map->y;
  it.inc_x = 1;
  it.inc_y = 1;
  it.elem = PHIRAS;
  fill_map_lr(dmap, map, &it, (PHIRAS_PCTG * dmap->max_val) / 100.f);
}

void	generate_thystame(t_map *map, t_dmap *dmap)
{
  t_map_iteration	it;

  it.beg_x = map->x - 1;
  it.beg_y = 0;
  it.end_x = -1;
  it.end_y = map->y;
  it.inc_x = -1;
  it.inc_y = 1;
  it.elem = THYSTAME;
  fill_map_lr(dmap, map, &it, (THYSTAME_PCTG * dmap->max_val) / 100.f);
}
