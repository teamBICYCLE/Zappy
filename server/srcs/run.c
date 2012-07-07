/*
** run.c for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Sat May 12 14:35:44 2012 Jonathan Machado
** Last update Sat Jul  7 13:43:07 2012 lois burg
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

void		leave(const char *msg)
{
  perror(msg);
  free_all(&g_info);
  if (g_info.ss != -1)
    close(g_info.ss);
  exit(EXIT_FAILURE);
}

static void		init_world(const uint x, const uint y, int const seed)
{
  if (signal(SIGINT, server_quit) == SIG_ERR ||
      signal(SIGQUIT, server_quit) == SIG_ERR ||
      signal(SIGTERM, server_quit) == SIG_ERR)
    perror("signal failed: ");
  if ((g_info.map = generate_map(x, y, seed)) == NULL)
    leave("Failed to generate map");
  print_serv_conf(&g_info.world);
}

static void		init_network(int const port)
{
  struct sockaddr_in    sin;
  struct protoent	*pe;
  const int		o = 1;

  g_info.users = new_list();
  memset(&sin, 0, sizeof(sin));
  if ((pe = getprotobyname("TCP")) == NULL)
    leave("protocol error: ");
  g_info.ss = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  setsockopt(g_info.ss, SOL_SOCKET, SO_REUSEADDR, (const char *)&o, sizeof(o));
  if (bind(g_info.ss, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
    leave("bind failed: ");
  if (listen(g_info.ss, 5) == -1)
    leave("listen failed: ");
  g_info.smax = g_info.ss;
  endprotoent();
  printf("Listening on port %d...\n", port);
}

void			run(void)
{
  int			sync;
  struct timeval	loop;
  struct timeval	start;
  struct timeval	end;

  init_network(g_info.world.port);
  init_world(g_info.world.x, g_info.world.y, g_info.world.seed);
  loop = g_info.world.smallest_t;
  sync = 0;
  while (1)
    {
      reset_fd(&g_info);
      if (select(g_info.smax + 1, &g_info.readfds,
		 &g_info.writefds, NULL, &loop) != -1)
	{
	  gettimeofday(&start, NULL);
	  treat_clients(&loop, &sync);
	  gettimeofday(&end, NULL);
	  handle_time(&start, &end, &loop, &sync);
	}
      if (g_info.end_game == true)
	reset_game();
    }
}
