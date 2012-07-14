/*
** actions_utils.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Tue Jun 12 16:55:25 2012 lois burg
** Last update Sat Jul 14 12:35:07 2012 lois burg
*/

#include <string.h>
#include "cmds.h"
#include "server.h"

char	*g_res_names[LAST] =
  {
    "nourriture",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame",
    "joueur",
    "oeuf"
  };

size_t	case_content_sz(const t_case *c)
{
  int		i;
  uint		j;
  size_t	sz;

  sz = 0;
  i = FOOD;
  while (i < EGG)
    {
      j = 0;
      sz += 1;
      while (j < c->elements[i])
	{
	  sz += strlen(g_res_names[i]) + 1;
	  ++j;
	}
      ++i;
    }
  sz += 2;
  return (sz);
}

char	*case_content(const t_case *c, char *buf)
{
  int	i;
  uint	j;

  i = 0;
  while (i < EGG)
    {
      j = 0;
      while (j < c->elements[i])
	{
	  strcat(buf, " ");
	  strcat(buf, g_res_names[i]);
	  ++j;
	}
      ++i;
    }
  return (buf);
}
