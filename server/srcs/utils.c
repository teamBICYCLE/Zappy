/*
** utils.c for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Mon May 14 20:10:30 2012 Jonathan Machado
** Last update Mon May 14 20:22:12 2012 Jonathan Machado
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "refstring.h"

int		cmp_socket(void *a, void *b)
{
  t_users	*u;
  int		*s;

  u = a;
  s = b;
  return (!(u->socket == *s));
}
