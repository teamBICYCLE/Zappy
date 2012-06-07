/*
** map.h for zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Wed Jun  6 16:13:05 2012 Jonathan Machado
** Last update Thu Jun  7 16:36:44 2012 lois burg
*/

#ifndef __MAP_H__
# define __MAP_H__

typedef struct s_map	t_map;
typedef struct s_case  	t_case;

enum
  {
    FOOD = 0,
    PLAYER,
    EGG,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    LAST = THYSTAME + 2
  };

struct 		s_case
{
  unsigned int 	elements[LAST];
};

struct 		s_map
{
  unsigned int	x;
  unsigned int	y;
  t_case       	**cases;
};

t_map		*new_map(unsigned int, unsigned int);
void		free_map(t_map *);
void		dump_map(t_map *);

#endif /* __MAP_H__ */
