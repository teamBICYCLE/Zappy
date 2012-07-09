/*
** reset_game.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Thu Jul  5 12:48:32 2012 lois burg
** Last update Mon Jul  9 14:28:35 2012 lois burg
*/

#include <time.h>
#include <stdio.h>
#include "graphics.h"
#include "server.h"
#include "diamond_generation.h"
#include "log.h"

extern t_infos	g_info;

static int	find_player(void *p, void *useless)
{
  const t_users	*u = (t_users*)p;

  (void)useless;
  return (!(u->type != TGRAPHICS));
}

void		reset_game(void)
{
  t_link	*l;
  t_users	*u;
  int		seed;

  printf("Team %s won!\n", g_info.winner->name);
  lookup(g_info.users, graphics_seg(g_info.winner->name), &notify_graphic);
  while ((l = lookup_and_pop(g_info.users, NULL, &find_player)) != NULL)
    {
      u = (t_users*)l->ptr;
      u->team->free_slots = g_info.world.clients_per_team;
      u->team->nb_max_lvl = 0;
      lookup(g_info.users, graphics_pdi(u), &notify_graphic);
      delete_link(l, &free_users);
    }
  free_map(g_info.map);
  if (g_info.world.seed_spec == true)
    seed = g_info.world.seed;
  else
    seed = time(NULL);
  if ((g_info.map = generate_map(g_info.world.x, g_info.world.y, seed)) == NULL)
    leave("Failed to generate map");
  g_info.winner = NULL;
  g_info.end_game = false;
  log_msg(stdout, "Game restarted!\n");
}
