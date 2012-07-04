/*
** run.c for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Sat May 12 14:35:44 2012 Jonathan Machado
** Last update Tue Jul  3 18:45:35 2012 lois burg
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

static void		leave(const char *msg)
{
  perror(msg);
  free_all(&g_info);
  if (g_info.ss != -1)
    close(g_info.ss);
  exit(EXIT_FAILURE);
}

static void		init_world(unsigned int const x, unsigned int const  y, int const seed)
{
  g_info.ss = -1;
  g_info.users = new_list();
  if (signal(SIGINT, server_quit) == SIG_ERR ||
      signal(SIGQUIT, server_quit) == SIG_ERR ||
      signal(SIGTERM, server_quit) == SIG_ERR)
    perror("signal failed: ");
  g_info.map = generate_map(x, y, seed);
  /**/
  print_serv_conf(&g_info.world);
  // printf("Minimum delay: %fs\n", g_info.world.smallest_t.tv_sec + (g_info.world.smallest_t.tv_usec / 1000000.f));
  /* dump_map(map); */
}

static void		init_network(int const port)
{
  struct sockaddr_in    sin;
  struct protoent	*pe;
  const int		opt = 1;

  memset(&sin, 0, sizeof(sin));
  if ((pe = getprotobyname("TCP")) == NULL)
    leave("protocol error: ");
  g_info.ss = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  setsockopt(g_info.ss, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(opt));
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
  int			diff;
  struct timeval	loop;
  struct timeval	start;
  struct timeval	end;

  init_world(g_info.world.x, g_info.world.y, g_info.world.seed);
  init_network(g_info.world.port);
  loop = g_info.world.smallest_t;
  sync = 0;
  while (1)
    {
      /* printf("Nb clients: %u\n", g_info.users->size); */
      reset_fd(&g_info);
      //printf("delay: %ld %lds\n", loop.tv_sec, loop.tv_usec); //debug
      if (select(g_info.smax + 1, &g_info.readfds,
		 &g_info.writefds, NULL, &loop) != -1)
	{
	  //	  printf("deblock at: %fs\n-------------\n", loop.tv_sec + (loop.tv_usec / 1000000.f)); // debug
	  gettimeofday(&start, NULL); // start

	  if (FD_ISSET(g_info.ss, &g_info.readfds))
	    add_user();
	  iterate(g_info.users, &read_user);
	  if ((loop.tv_sec <= 0 && loop.tv_usec <= 0) || sync != 0)
	    {
	      if (loop.tv_sec <= 0 && loop.tv_usec <= 0)
		++sync;
	      //	      printf("Sync: %d\n", sync);
	      update_map(sync);
	      loop = g_info.world.smallest_t;
	      sync = 0;
	    }
	  iterate(g_info.users, &write_user);

	  // a metre dans fonction ?
	  gettimeofday(&end, NULL);
	  sync += (((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) /
	  	   (g_info.world.smallest_t.tv_sec * 1000000 + g_info.world.smallest_t.tv_usec));
	  diff = (((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) %
		  (g_info.world.smallest_t.tv_sec * 1000000 + g_info.world.smallest_t.tv_usec));
	  diff = (loop.tv_usec + loop.tv_sec * 1000000) - diff;
	  if (diff < 0)
	    {
	      ++sync;
	      diff += (g_info.world.smallest_t.tv_usec +
		       g_info.world.smallest_t.tv_sec * 1000000);
	    }
	  loop.tv_usec = diff % 1000000;
	  loop.tv_sec = diff / 1000000;
	}
    }
}
