/*
** run.c for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Sat May 12 14:35:44 2012 Jonathan Machado
<<<<<<< HEAD
** Last update Thu Jun  7 16:59:34 2012 Jonathan Machado
=======
** Last update Wed Jun  6 17:27:17 2012 Jonathan Machado
>>>>>>> 2ccf6678672f14b280168bcc37b5dab0378c583d
*/

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include "diamond_generation.h"
#include "map.h"
#include "server.h"

extern t_infos		g_info;

static	void		server_quit(int i)
{
  (void)i;
  free_all(&g_info);
  if (g_info.ss != -1)
    close(g_info.ss);
  exit(EXIT_SUCCESS);
}

static void		init_world(void)
{
  g_info.ss = -1;
  g_info.users = new_list();
  g_info.tasks = new_list();
  signal(SIGINT, server_quit);
  signal(SIGQUIT, server_quit);
  signal(SIGTERM, server_quit);
  g_info.map = new_map(g_info.world_info.world_x, g_info.world_info.world_y);
  generate_map(g_info.world_info.world_x, g_info.world_info.world_y, time(NULL));
  // convertir la map en t_map
}

static void		init_network(int port)
{
  struct sockaddr_in    sin;
  struct protoent	*pe;

  memset(&sin, 0, sizeof(sin));
  pe = getprotobyname("TCP");
  if (pe == NULL)
    {
      perror("protocol error: ");
      exit(EXIT_FAILURE);
    }
  g_info.ss = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  bind(g_info.ss, (const struct sockaddr *)&sin, sizeof(sin));
  listen(g_info.ss, 5);
  g_info.smax = g_info.ss;
  endprotoent();
  printf("Listening on port %d...\n", port);
}

static void	set_fd(void *ptr)
{
  t_users	*user;

  user = ptr;
  FD_SET(user->socket, &g_info.writefds);
  FD_SET(user->socket, &g_info.readfds);
}
#include <time.h>
void		run(void)
{
  init_world();
  init_network(g_info.world_info.port);
  print_serv_conf(&g_info.world_info);
  while (1)
    {
      FD_ZERO(&g_info.writefds);
      FD_ZERO(&g_info.readfds);
      FD_SET(g_info.ss, &g_info.readfds);
      iterate(g_info.users, &set_fd);
      /* select non bloquant */
      if (select(g_info.smax + 1, &g_info.readfds,
		 &g_info.writefds, NULL, NULL) != -1)
	{
	  if (FD_ISSET(g_info.ss, &g_info.readfds))
	    add_user();
	  iterate(g_info.users, &read_user);
	  // mise a jour map + parcour des client avec pop des task faite
	  iterate(g_info.users, &write_user);
	  // sleep
	}
    }
}
