/*
** angle.c<2> for  in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Wed Jun 27 15:52:02 2012 Jonathan Machado
** Last update Wed Jul  4 17:22:45 2012 Jonathan Machado
*/

#include <string.h>
#include <stdio.h>
#include <math.h>
#include "graphics.h"
#include "server.h"
#include "cmds.h"

extern t_infos	g_info;

static	t_dir_mov	g_dir_tab[4] =
  {
    {0, -1},
    {1, 0},
    {0, 1},
    {-1, 0}
  };

static struct
{
  double min;
  double max;
  int	idx;
} range[8] = {
  {0, 0, 5},
  {0, 90, 4},
  {90, 90, 3},
  {90, 180, 2},
  {180, 180, 1},
  {180, 270, 8},
  {270, 270, 7},
  {270, 360, 6}
};

static int	get_dist(int x1, int y1, int x2, int y2)
{
  return (pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double	get_angle(int *x, int *y, t_direction dir)
{
  int		i;
  int		shorter;
  double       	size;
  double	angle;
  const	int	xx[] = { x[1], x[1] + g_info.map->x, x[1] - g_info.map->x,
			 x[1], x[1], x[1] + g_info.map->x, x[1] - g_info.map->x,
			 x[1] + g_info.map->x, x[1] - g_info.map->x };
  const int	yy[] = { y[1], y[1], y[1], y[1] + g_info.map->y,
			 y[1] - g_info.map->y, y[1] +  g_info.map->y,
			 y[1] - g_info.map->y, y[1] - g_info.map->y,
			 y[1] + g_info.map->y};

  i = 1;
  shorter = 0;
  while (i < 9)
    {
      if (get_dist(x[0], y[0], xx[shorter], yy[shorter]) >
	  get_dist(x[0], y[0], xx[i], yy[i]))
	shorter = i;
      ++i;
    }
  size = sqrt(pow(xx[shorter], 2) + pow(yy[shorter], 2));
  angle = ((atan2((yy[shorter] - y[0]) / size, (xx[shorter] - x[0]) / size) -
	    atan2(g_dir_tab[dir].dy, g_dir_tab[dir].dx)) / M_PI * 180);
  return (angle < 0 ? 360 + angle : angle);
}

int		get_case(int *x, int *y, t_direction dir)
{
  int		i;
  double const	angle = get_angle(x, y, dir);

  i = 0;
  if (x[0] == x[1] && y[0] == y[1])
    return (0);
  while (i < 8)
    {
      if (range[i].min != range[i].max &&
	  range[i].min < angle && range[i].max > angle)
	return (range[i].idx);
      else if (range[i].min == angle)
	return (range[i].idx);
      ++i;
    }
  return (-1);
}
