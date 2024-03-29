/*
** log.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Wed Jun 13 11:46:06 2012 lois burg
** Last update Tue Jun 19 11:38:58 2012 lois burg
*/

#include <string.h>
#include <time.h>
#include <stdio.h>

void		log_msg(FILE *stream, const char *msg)
{
  time_t	now;
  char		*date;

  now = time(NULL);
  if ((date = ctime(&now)) != NULL)
  {
    date[strlen(date) - 1] = 0;
    fprintf(stream, "[\033[1;32m%s\033[0m] - ", date);
  }
  else
    fprintf(stream, "[ERROR] - ");
  fprintf(stream, msg);
}
