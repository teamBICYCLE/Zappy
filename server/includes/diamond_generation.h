/*
** diamond_generation.h for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Wed Jun  6 16:02:39 2012 lois burg
** Last update Wed Jun  6 19:36:51 2012 lois burg
*/

#ifndef		__DIAMOND_GENERATION_H__
# define	__DIAMOND_GENERATION_H__

# define	RAND_RANGE	20
# define	MAX(x, y)	((x > y) ? (x) : (y))
# define	ODDIFY(x)	((x % 2) ? (x) : (x + 1))

/* Useless structure to avoid more than 4 parameters */
typedef	struct	s_dmap	t_dmap;
struct	s_dmap
{
  int		step;
  double	**map;
};

void		generate_map(int x, int y, int seed);
double		avg_diamond(const int x, const int y, t_dmap *map, const int size);

#endif /* !__DIAMOND_GENERATION_H__*/
