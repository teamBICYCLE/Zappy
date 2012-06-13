/*
** log.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Wed Jun 13 11:46:06 2012 lois burg
** Last update Wed Jun 13 12:21:30 2012 lois burg
*/

#include <string.h>
#include <time.h>
#include <stdio.h>

void		log_msg(FILE *stream, const char const *msg)
{
  time_t	now;
  char		*date;

  now = time(NULL);
  date = ctime(&now);
  date[strlen(date) - 1] = 0;
  fprintf(stream, "[\033[1;32m%s\033[0m] - ", date);
  fprintf(stream, msg);
}
