/*
** generate_ressources.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Fri Jun  8 11:28:02 2012 lois burg
** Last update Sat Jun  9 11:19:22 2012 lois burg
*/

#include "diamond_generation.h"
#include "map.h"

t_map	*generate_ressources(const int x, const int y, t_dmap *dmap)
{
  t_map	*map;

  map = new_map(x, y);
  generate_food(map, dmap);
  generate_linemate(map, dmap);
  generate_deraumere(map, dmap);
  generate_sibur(map, dmap);
  generate_mendiane(map, dmap);
  generate_phiras(map, dmap);
  generate_thystame(map, dmap);
  return (map);
}
