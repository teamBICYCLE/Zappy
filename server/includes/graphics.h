/*
** graphics.h for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Fri Jun 15 18:27:05 2012 lois burg
** Last update Thu Jun 21 18:21:06 2012 lois burg
*/

#ifndef		__GRAPHICS_H__
# define	__GRAPHICS_H__

# include	"server.h"

# define	GRAPHICS_MSG_SZ	4096

int		notify_graphic(void *usr, void *msg);
char		*get_graphics_buf(void);
void		greet_graphics(t_users *usr);

/* TOOLS */
int	cmp_id(void *usr, void *id);
void	send_graphic_result(t_users *usr, const int success);

/* ANSWER FUNC */
void	answer_msz(t_users *u, char **args);
void	answer_bct(t_users *u, char **args);
void	answer_mct(t_users *u, char **args);
void	answer_tna(t_users *u, char **args);
void	answer_ppo(t_users *u, char **args);
void	answer_plv(t_users *u, char **args);
void	answer_pin(t_users *u, char **args);
void	answer_sgt(t_users *u, char **args);
void	answer_sst(t_users *u, char **args);
void	answer_suc(t_users *u, char **args);

/* GRAPHICS FUNC */
char	*graphics_msz(void);
char	*graphics_bct(const int x, const int y);
char	*graphics_tna(void);
char	*graphics_pnw(t_users *usr);
char	*graphics_ppo(t_users *usr);
char	*graphics_plv(t_users *usr);
char	*graphics_pin(t_users *usr);
char	*graphics_pex(t_users *usr);
char	*graphics_pbc(t_users *usr, const char *broadcast);
char	*graphics_pic(t_users *usr);
char	*graphics_pie(const int x, const int y, const int success);
char	*graphics_pfk(t_users *usr);
char	*graphics_pdr(t_users *usr, const int res);
char	*graphics_pgt(t_users *usr, const int res);
char	*graphics_pdi(t_users *usr);
char	*graphics_enw(t_users *egg);
char	*graphics_eht(const int egg_id);
char	*graphics_ebo(const int egg_id);
char	*graphics_edi(const int egg_id);
char	*graphics_sgt(void);
char	*graphics_seg(const char *win_team);
char	*graphics_smg(const char *serv_msg);
char	*graphics_suc(void);
char	*graphics_sbp(void);

#endif /* !__GRAPHICS_H__*/
