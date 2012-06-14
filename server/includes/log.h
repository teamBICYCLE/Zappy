/*
** log.h for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Wed Jun 13 12:00:10 2012 lois burg
** Last update Thu Jun 14 11:40:34 2012 lois burg
*/

#ifndef		__LOG_H__
# define	__LOG_H__

# include	<stdio.h>

# define	LOG_MSG_SZ	1024

void		log_msg(FILE *stream, const char const *msg);

#endif /* !__LOG_H__*/



