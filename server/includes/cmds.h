/*
** cmds.h for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Tue Jun 12 17:04:55 2012 lois burg
** Last update Tue Jun 12 17:19:50 2012 lois burg
*/

#ifndef		__CMDS_H__
# define	__CMDS_H__

# include	"server.h"

# define	INVENTORY_MSG_SZ	1024
# define	INVENTORY_VAL_SZ	15

/* CMDS */
void		see_cmd(t_users *usr, char **args);
void		inventory_cmd(t_users *usr, char **args);

/* TOOLS */
typedef	struct	s_res_str	t_res_str;
struct	s_res_str
{
  int	res;
  char	*res_str;
};

char		*map_ressource(int res);

#endif /* !__CMDS_H__*/
