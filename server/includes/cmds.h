/*
** cmds.h for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Tue Jun 12 17:04:55 2012 lois burg
** Last update Fri Jun 15 14:47:25 2012 Jonathan Machado
*/

#ifndef		__CMDS_H__
# define	__CMDS_H__

# include	"server.h"

# define	INVENTORY_MSG_SZ	1024
# define	INVENTORY_VAL_SZ	15

/* CMDS */
bool   	see_cmd(t_users *usr, char **args);
bool   	inventory_cmd(t_users *usr, char **args);
bool	right_cmd(t_users *u, char **args);
bool	left_cmd(t_users *u, char **args);
bool	put_cmd(t_users *u, char **args);

/* TOOLS */
char		*case_content(const t_case *c, char *buf);
size_t		case_content_sz(const t_case *c);

/* SEE TOOLS */

typedef	char	*(*t_see_func)(const t_users *usr, char *content, const t_map *map);
typedef	size_t	(*t_see_count_fun)(const int usr_x, const int usr_y,
				   const int lvl, const t_map *map);
typedef	struct	s_see_pair	t_see_pair;
struct			s_see_pair
{
  t_see_count_fun	cf;
  t_see_func		f;
};

char	*see_north(const t_users *usr, char *content, const t_map *map);
char	*see_east(const t_users *usr, char *content, const t_map *map);
char	*see_south(const t_users *usr, char *content, const t_map *map);
char	*see_west(const t_users *usr, char *content, const t_map *map);

size_t	see_count_north(const int usr_x, const int usr_y, const int usr_lvl, const t_map *map);
size_t	see_count_east(const int usr_x, const int usr_y, const int usr_lvl, const t_map *map);
size_t	see_count_south(const int usr_x, const int usr_y, const int usr_lvl, const t_map *map);
size_t	see_count_west(const int usr_x, const int usr_y, const int usr_lvl, const t_map *map);

#endif /* !__CMDS_H__*/
