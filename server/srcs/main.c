/*
** main.c for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Sat May 12 14:33:47 2012 Jonathan Machado
** Last update Wed Jul  4 17:54:34 2012 lois burg
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"

t_infos			g_info;

int	main(int argc, char *argv[])
{
  memset(&g_info, 0, sizeof(g_info));
  parse_args(argc, argv, &g_info.world);
  if (!g_info.world.help_showed)
    {
      if (g_info.world.teams_names->size &&
	  !g_info.world.error)
	{
	  if (g_info.world.teams_names->size >= 2)
	    run();
	  else
	    fprintf(stderr, "Error: At least two teams are needed.\n");
	}
      else
	fprintf(stderr, "Usage : %s [-p port] [-x world_x] [-y world_y] "\
		"[-c max_clients] [-t speed] -n team1 team2...\n", argv[0]);
    }
  delete_list(g_info.world.teams_names, &free_teams);
  return (0);
}
