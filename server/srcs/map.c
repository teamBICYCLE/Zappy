/*
** case.c for map in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Wed Jun  6 16:54:05 2012 Jonathan Machado
** Last update Wed Jun  6 17:23:07 2012 Jonathan Machado
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "map.h"

t_map		*new_map(const unsigned int x, const unsigned int y)
{
  unsigned int	i;
  t_map		*map;

  i = 0;
  map = malloc(sizeof(*map));
  map->x = x;
  map->y = y;
  map->cases = malloc(y * sizeof(*map->cases));
  while (i < y)
    {
      map->cases[i] = malloc(x * sizeof(**map->cases));
      memset(map->cases[i], 0, x * sizeof(**map->cases));
      ++i;
    }
  return (map);
}

void		free_map(t_map *map)
{
  unsigned int	i;

  i = 0;
  while (i < map->y)
    {
      free(map->cases[i]);
      ++i;
    }
  free(map->cases);
  free(map);
  map = NULL;
}

void		dump_map(t_map *map)
{
  unsigned int	x;
  unsigned int	y;

  y = 0;
  while (y < map->y)
    {
      x = 0;
      while (x < map->x)
	{
	  printf("Case %u %u\n", x , y);
	  printf("Elements : \n");
	  ++x;
	}
      ++y;
    }
}
