/*
** see_utils.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Wed Jun 13 12:25:27 2012 lois burg
** Last update Thu Jun 21 15:59:22 2012 lois burg
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cmds.h"

char		*see_north(const t_users *usr, char *content, const t_map *map)
{
  int		lvl;
  int		cases_left;
  int		x;
  int		y;

  lvl = 0;
  while (lvl <= usr->lvl)
    {
      cases_left = (lvl * 2) + 1;
      x = ((usr->x - lvl) + map->x) % map->x;
      y = ((usr->y - lvl) + map->y) % map->y;
      while (cases_left && content)
	{
	  content = case_content(&map->cases[y][x], content);
	  x = (x + 1) % map->x;
	  --cases_left;
	  if (cases_left)
	    strcat(content, ",");
	}
      ++lvl;
      if (lvl <= usr->lvl)
	strcat(content, ",");
    }
  return (content);
}

char		*see_east(const t_users *usr, char *content, const t_map *map)
{
  int		lvl;
  int		cases_left;
  int		x;
  int		y;

  lvl = 0;
  while (lvl <= usr->lvl)
    {
      cases_left = (lvl * 2) + 1;
      x = ((usr->x + lvl) + map->x) % map->x;
      y = ((usr->y - lvl) + map->y) % map->y;
      while (cases_left)
	{
	  content = case_content(&map->cases[y][x], content);
	  y = (y + 1) % map->y;
	  --cases_left;
	  if (cases_left)
	    strcat(content, ",");
	}
      ++lvl;
      if (lvl <= usr->lvl)
	strcat(content, ",");
    }
  return (content);
}

char		*see_south(const t_users *usr, char *content, const t_map *map)
{
  int		lvl;
  int		cases_left;
  int		x;
  int		y;

  lvl = 0;
  while (lvl <= usr->lvl)
    {
      cases_left = (lvl * 2) + 1;
      x = ((usr->x + lvl) + map->x) % map->x;
      y = ((usr->y + lvl) + map->y) % map->y;
      while (cases_left)
	{
	  content = case_content(&map->cases[y][x], content);
	  x = ((x - 1) + map->x) % map->x;
	  --cases_left;
	  if (cases_left)
	    strcat(content, ",");
	}
      ++lvl;
      if (lvl <= usr->lvl)
	strcat(content, ",");
    }
  return (content);
}

char	*see_west(const t_users *usr, char *content, const t_map *map)
{
  int		lvl;
  int		cases_left;
  int		x;
  int		y;

  lvl = 0;
  while (lvl <= usr->lvl)
    {
      cases_left = (lvl * 2) + 1;
      x = ((usr->x - lvl) + map->x) % map->x;
      y = ((usr->y + lvl) + map->y) % map->y;
      while (cases_left)
	{
	  content = case_content(&map->cases[y][x], content);
	  y = ((y - 1) + map->y) % map->y;
	  --cases_left;
	  if (cases_left)
	    strcat(content, ",");
	}
      ++lvl;
      if (lvl <= usr->lvl)
	strcat(content, ",");
    }
  return (content);
}
