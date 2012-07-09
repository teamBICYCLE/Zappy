/*
** diamond_tools2.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Mon Jul  9 15:18:02 2012 lois burg
** Last update Mon Jul  9 15:35:59 2012 lois burg
*/

#include <stdlib.h>
#include "map.h"

static uint	g_necessary_ressources[NB_RESSOURCES] =
  {
    0, 9, 8, 10, 5, 6, 1
  };

void	prefill(t_map *map)
{
  int	i;
  uint	j;

  i = LINEMATE;
  while (i < NB_RESSOURCES)
    {
      j = 0;
      while (j < g_necessary_ressources[i])
	{
	  ++map->cases[rand() % map->y][rand() % map->x].elements[i];
	  ++j;
	}
      ++i;
    }
}
