/*
** diamond_generation.h for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Wed Jun  6 16:02:39 2012 lois burg
** Last update Mon Jul  9 16:50:47 2012 lois burg
*/

#ifndef		__DIAMOND_GENERATION_H__
# define	__DIAMOND_GENERATION_H__

# include	"map.h"

# define	RAND_RANGE	300
# define	NOISE		150
# define	MAX_RES_CASE	3

# define	MAX(x, y)	(((x) > (y)) ? (x) : (y))
# define	ODDIFY(x)	((x % 2) ? (x) : (x + 1))

/* Percentage for each ressources */
# define	FOOD_PCTG	40.f
# define	LINEMATE_PCTG	10.f
# define	DERAUMERE_PCTG	10.f
# define	SIBUR_PCTG	10.f
# define	MENDIANE_PCTG	10.f
# define	PHIRAS_PCTG	10.f
# define	THYSTAME_PCTG	10.f

/* Useless structure to avoid more than 4 parameters */
typedef	struct	s_dmap	t_dmap;
struct	s_dmap
{
  double	max_val;
  int		size;
  int		step;
  double	**map;
};

typedef	struct	s_map_iteration	t_map_iteration;
struct	s_map_iteration
{
  int		beg_x;
  int		beg_y;
  int		end_x;
  int		end_y;
  int		inc_x;
  int		inc_y;
  int		elem;
};

double		avg_diamond(const int x, const int y, t_dmap *map, const int size);
t_dmap		*new_dmap(const int size);
void		free_dmap(t_dmap **dmap);
t_map		*generate_map(const int x, const int y, int seed);
t_dmap		*compute_dmap(const int x, const int y, const int seed);

#endif /* !__DIAMOND_GENERATION_H__*/
