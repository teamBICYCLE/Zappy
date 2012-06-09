/*
** generate_fldsm.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Fri Jun  8 12:32:42 2012 lois burg
** Last update Sat Jun  9 12:05:28 2012 lois burg
*/

#include "diamond_generation.h"
#include "map.h"

void			generate_food(t_map *map, t_dmap *dmap)
{
  t_map_iteration	it;

  it.beg_x = 0;
  it.beg_y = 0;
  it.end_x = map->x;
  it.end_y = map->y;
  it.inc_x = 1;
  it.inc_y = 1;
  it.elem = FOOD;
  fill_map_ud(dmap, map, &it, (FOOD_PCTG * dmap->max_val) / 100.f);
}

void			generate_linemate(t_map *map, t_dmap *dmap)
{
  t_map_iteration	it;

  it.beg_x = map->x - 1;
  it.beg_y = 0;
  it.end_x = -1;
  it.end_y = map->y;
  it.inc_x = -1;
  it.inc_y = 1;
  it.elem = LINEMATE;
  fill_map_ud(dmap, map, &it, (LINEMATE_PCTG * dmap->max_val) / 100.f);
}

void			generate_deraumere(t_map *map, t_dmap *dmap)
{
  t_map_iteration	it;

  it.beg_x = 0;
  it.beg_y = map->y - 1;
  it.end_x = map->x;
  it.end_y = -1;
  it.inc_x = 1;
  it.inc_y = -1;
  it.elem = DERAUMERE;
  fill_map_ud(dmap, map, &it, (DERAUMERE_PCTG * dmap->max_val) / 100.f);
}

void			generate_sibur(t_map *map, t_dmap *dmap)
{
  t_map_iteration	it;

  it.beg_x = map->x - 1;
  it.beg_y = map->y - 1;
  it.end_x = -1;
  it.end_y = -1;
  it.inc_x = -1;
  it.inc_y = -1;
  it.elem = SIBUR;
  fill_map_ud(dmap, map, &it, (SIBUR_PCTG * dmap->max_val) / 100.f);
}

void			generate_mendiane(t_map *map, t_dmap *dmap)
{
  t_map_iteration	it;

  it.beg_x = map->x - 1;
  it.beg_y = map->y - 1;
  it.end_x = -1;
  it.end_y = -1;
  it.inc_x = -1;
  it.inc_y = -1;
  it.elem = MENDIANE;
  fill_map_ud(dmap, map, &it, (MENDIANE_PCTG * dmap->max_val) / 100.f);
}
