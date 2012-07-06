/*
** refstring.c for  in /home/jonathan/Projets/Tek-2/C/my_irc_tb/serverdir
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Thu Apr 19 10:36:22 2012 Jonathan Machado
** Last update Fri Jul  6 17:39:16 2012 lois burg
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "refstring.h"

t_refstring	*new_refstring(char *str)
{
  t_refstring	*ret;

  ret = malloc(sizeof(*ret));
  if (ret)
    {
      ret->count = 0;
      ret->len = strlen(str);
      ret->str = str;
    }
  return (ret);
}

void	unref(t_refstring **str)
{
  --(*str)->count;
  if ((*str)->count == 0)
    {
      free((*str)->str);
      free(*str);
    }
}

t_refstring	*ref(t_refstring *str)
{
  ++str->count;
  return (str);
}
