/*
** see_utils.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Wed Jun 13 12:25:27 2012 lois burg
** Last update Wed Jun 13 19:24:44 2012 lois burg
*/

#include <stdio.h>
#include <string.h>
#include "cmds.h"

char		*see_north(const int usr_x, const int usr_y,
			   const int lvl, const t_map *map)
{
  int		cases_left;
  int		x;
  const int	y = ((usr_y - lvl) + map->y) % map->y;
  char		content[4096];

  cases_left = (lvl * 2) + 1;
  x = ((usr_x - lvl) + map->x ) % map->x;
  while (cases_left)
    {
      memset(content, 0, sizeof(content));
      printf("Case %d %d: %s\n", x, y, case_content(&map->cases[y][x], content));
      x = (x + 1) % map->x;
      --cases_left;
    }
  return (NULL);
}

char	*see_east(const int usr_x, const int usr_y,
		  const int lvl, const t_map *map)
{
  int		cases_left;
  const int	x = ((usr_x + lvl) + map->x) % map->x;
  int		y;
  char		content[4096];

  cases_left = (lvl * 2) + 1;
  y = ((usr_y - lvl) + map->y ) % map->y;
  while (cases_left)
    {
      memset(content, 0, sizeof(content));
      printf("Case %d %d: %s\n", x, y, case_content(&map->cases[y][x], content));
      y = (y + 1) % map->y;
      --cases_left;
    }
  return (NULL);
}

char	*see_south(const int usr_x, const int usr_y,
		   const int lvl, const t_map *map)
{
  int		cases_left;
  int		x;
  const int	y = ((usr_y + lvl) + map->y) % map->y;
  char		content[4096];

  cases_left = (lvl * 2) + 1;
  x = ((usr_x - lvl) + map->x ) % map->x;
  while (cases_left)
    {
      memset(content, 0, sizeof(content));
      printf("Case %d %d: %s\n", x, y, case_content(&map->cases[y][x], content));
      x = (x + 1) % map->x;
      --cases_left;
    }
  return (NULL);
}

char	*see_west(const int usr_x, const int usr_y,
		  const int lvl, const t_map *map)
{
  int		cases_left;
  const int	x = ((usr_x - lvl) + map->x) % map->x;
  int		y;
  char		content[4096];

  cases_left = (lvl * 2) + 1;
  y = ((usr_y - lvl) + map->y ) % map->y;
  while (cases_left)
    {
      memset(content, 0, sizeof(content));
      printf("Case %d %d: %s\n", x, y, case_content(&map->cases[y][x], content));
      y = (y + 1) % map->y;
      --cases_left;
    }
  return (NULL);
}
