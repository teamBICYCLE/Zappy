/*
** diamond_generation.h for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Wed Jun  6 16:02:39 2012 lois burg
** Last update Sat Jun  9 12:04:50 2012 lois burg
*/

#ifndef		__DIAMOND_GENERATION_H__
# define	__DIAMOND_GENERATION_H__

# include	"map.h"

# define	RAND_RANGE	30
# define	MAX(x, y)	((x > y) ? (x) : (y))
# define	ODDIFY(x)	((x % 2) ? (x) : (x + 1))

/* Percentage for each ressources */
# define	FOOD_PCTG	50.f
# define	LINEMATE_PCTG	40.f
# define	DERAUMERE_PCTG	40.f
# define	SIBUR_PCTG	40.f
# define	MENDIANE_PCTG	40.f
# define	PHIRAS_PCTG	40.f
# define	THYSTAME_PCTG	40.f

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
t_map		*generate_map(const int x, const int y, const int seed);
t_map		*generate_ressources(const int x, const int y, t_dmap *dmap);
void		fill_map_ud(t_dmap *dmap, t_map *map, t_map_iteration *it, const double pctg);
void		fill_map_lr(t_dmap *dmap, t_map *map, t_map_iteration *it, const double pctg);

/* RESSOURCES FUNC */
void	generate_food(t_map *map, t_dmap *dmap);
void	generate_linemate(t_map *map, t_dmap *dmap);
void	generate_deraumere(t_map *map, t_dmap *dmap);
void	generate_sibur(t_map *map, t_dmap *dmap);
void	generate_mendiane(t_map *map, t_dmap *dmap);
void	generate_phiras(t_map *map, t_dmap *dmap);
void	generate_thystame(t_map *map, t_dmap *dmap);

#endif /* !__DIAMOND_GENERATION_H__*/
