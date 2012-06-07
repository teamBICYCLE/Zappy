/*
** main.c for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Sat May 12 14:33:47 2012 Jonathan Machado
** Last update Thu Jun  7 16:53:16 2012 lois burg
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

t_infos			g_info;

int	main(int argc, char *argv[])
{
  parse_args(argc, argv, &g_info.world_info);
  if (!g_info.world_info.help_showed)
    {
      if (g_info.world_info.teams_names->size &&
	  !g_info.world_info.error)
	{
	  if (g_info.world_info.teams_names->size >= 2)
	    run();
	  else
	    fprintf(stderr, "Error: At least two teams are needed to run the game.\n");
	}
      else
	fprintf(stderr, "Usage : %s [-p port] [-x world_x] [-y world_y] "\
		"[-c max_clients] [-t speed] -n team1 team2...\n", argv[0]);
    }
  free(g_info.world_info.teams_names);
  return (0);
}
