/*
** see_utils_count.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Thu Jun 14 14:33:04 2012 lois burg
** Last update Sat Jul 14 12:40:43 2012 lois burg
*/

#include "cmds.h"
#include "server.h"

size_t		see_count_north(const int usr_x, const int usr_y,
				const int usr_lvl, const t_map *map)
{
  int		cases_left;
  size_t	sz;
  int		lvl;
  int		x;
  int		y;

  sz = 0;
  lvl = 0;
  while (lvl <= usr_lvl)
    {
      x = ((usr_x - lvl) + map->x) % map->x;
      y = ((usr_y - lvl) + map->y) % map->y;
      cases_left = (lvl * 2) + 1;
      while (cases_left)
	{
	  sz += case_content_sz(&map->cases[y][x]);
	  x = (x + 1) % map->x;
	  --cases_left;
	}
      ++lvl;
    }
  return (sz);
}

size_t		see_count_east(const int usr_x, const int usr_y,
			       const int usr_lvl, const t_map *map)
{
  int		cases_left;
  size_t	sz;
  int		lvl;
  int		x;
  int		y;

  sz = 0;
  lvl = 0;
  while (lvl <= usr_lvl)
    {
      x = ((usr_x + lvl) + map->x) % map->x;
      y = ((usr_y - lvl) + map->y) % map->y;
      cases_left = (lvl * 2) + 1;
      while (cases_left)
	{
	  sz += case_content_sz(&map->cases[y][x]);
	  y = (y + 1) % map->y;
	  --cases_left;
	}
      ++lvl;
    }
  return (sz);
}

size_t		see_count_south(const int usr_x, const int usr_y,
				const int usr_lvl, const t_map *map)
{
  int		cases_left;
  size_t	sz;
  int		lvl;
  int		x;
  int		y;

  sz = 0;
  lvl = 0;
  while (lvl <= usr_lvl)
    {
      x = ((usr_x + lvl) + map->x) % map->x;
      y = ((usr_y + lvl) + map->y) % map->y;
      cases_left = (lvl * 2) + 1;
      while (cases_left)
	{
	  sz += case_content_sz(&map->cases[y][x]);
	  x = ((x - 1) + map->x) % map->x;
	  --cases_left;
	}
      ++lvl;
    }
  return (sz);
}

size_t		see_count_west(const int usr_x, const int usr_y,
			       const int usr_lvl, const t_map *map)
{
  int		cases_left;
  size_t	sz;
  int		lvl;
  int		x;
  int		y;

  sz = 0;
  lvl = 0;
  while (lvl <= usr_lvl)
    {
      x = ((usr_x - lvl) + map->x) % map->x;
      y = ((usr_y + lvl) + map->y) % map->y;
      cases_left = (lvl * 2) + 1;
      while (cases_left)
	{
	  sz += case_content_sz(&map->cases[y][x]);
	  y = ((y - 1) + map->y) % map->y;
	  --cases_left;
	}
      ++lvl;
    }
  return (sz);
}
