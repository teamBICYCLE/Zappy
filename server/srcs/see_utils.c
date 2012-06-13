/*
** see_utils.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Wed Jun 13 12:25:27 2012 lois burg
** Last update Wed Jun 13 16:57:11 2012 lois burg
*/

#include <stdio.h>
#include <string.h>
#include "cmds.h"

static t_see_dir	g_see_tab[5] =
  {
    {NORTH, &see_north},
    {EAST, &see_east},
    {SOUTH, &see_south},
    {WEST, &see_west},
    {-1, NULL}
  };

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
  (void)usr_x;(void)usr_y;(void)lvl;(void)map;
  return (NULL);
}

char	*see_south(const int usr_x, const int usr_y,
		   const int lvl, const t_map *map)
{
  (void)usr_x;(void)usr_y;(void)lvl;(void)map;
  return (NULL);
}

char	*see_west(const int usr_x, const int usr_y,
		  const int lvl, const t_map *map)
{
  (void)usr_x;(void)usr_y;(void)lvl;(void)map;
  return (NULL);
}

char	*see_lvl(const t_users *usr, const int lvl_to_see, const t_map *map)
{
  int	i;
  char	*content;

  i = 0;
  content = NULL;
  while (g_see_tab[i].dir != -1 && g_see_tab[i].dir != usr->dir)
    ++i;
  if (g_see_tab[i].f)
    content = (g_see_tab[i].f)(usr->x, usr->y, lvl_to_see, map);
  return (content);
}
