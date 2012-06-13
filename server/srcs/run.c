/*
** run.c for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Sat May 12 14:35:44 2012 Jonathan Machado
** Last update Wed Jun 13 18:04:40 2012 Jonathan Machado
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

static void		init_world(unsigned int const x, unsigned int const  y, int const seed)
{
  g_info.ss = -1;
  g_info.users = new_list();
  signal(SIGINT, server_quit);
  signal(SIGQUIT, server_quit);
  signal(SIGTERM, server_quit);
  g_info.map = generate_map(x, y, seed);
  //
  print_serv_conf(&g_info.world);
  printf("Minimum delay: %fs\n", g_info.world.smallest_t.tv_sec + (g_info.world.smallest_t.tv_usec / 100000.f));
}

static void		init_network(int const port)
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

void			run(void)
{
  struct timeval	loop;

  init_world(g_info.world.x, g_info.world.y, g_info.world.seed);
  init_network(g_info.world.port);
  loop = g_info.world.smallest_t;
  while (1)
    {
      reset_fd(&g_info);
      if (select(g_info.smax + 1, &g_info.readfds,
		 &g_info.writefds, NULL, &loop) != -1)
	{
	  // calculer le temp
	  if (FD_ISSET(g_info.ss, &g_info.readfds))
	    add_user();
	  iterate(g_info.users, &read_user);
	  if (loop.tv_sec <= 0 && loop.tv_usec <= 0)
	    {
	      update_map(1); // passer le sync
	      loop = g_info.world.smallest_t;
	    }
	  iterate(g_info.users, &write_user);
	  // soustraire a loop le temp mis
	}
    }
}
