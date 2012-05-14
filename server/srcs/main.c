/*
** main.c for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Sat May 12 14:33:47 2012 Jonathan Machado
** Last update Mon May 14 19:39:14 2012 Jonathan Machado
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

int	main(int argc, char *argv[])
{
  int	port;

  if (argc == 2)
    {
      /*
      ** check des autres param
      ** remplissage sune struct arg_info ?
      */
      port = atoi(argv[1]);
      if (port > 0)
  	run(port);
    }
  else
    fprintf(stderr, "Usage : %s port\n", argv[0]);
  return (0);
}
