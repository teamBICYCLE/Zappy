/*
** cmds.c for zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Tue Jun 12 15:51:42 2012 Jonathan Machado
** Last update Thu Jun 21 18:39:46 2012 lois burg
*/

#include <stdlib.h>
#include <string.h>
#include "protocol.h"
#include "task.h"
#include "cmds.h"
#include "graphics.h"
#include "log.h"

extern t_infos	g_info;

static t_cmd_ret	unknown_cmd(t_users *user, char **args, char *orig_cmd)
{
  (void)user;
  (void)args;
  (void)orig_cmd;
  return (FAILURE);
}

static t_tasksmap	g_commands[] =
  {
    {0, &connect_nbr_cmd, "connect_nbr"},
    {1, &inventory_cmd, "inventaire"},
    {7, &forward_cmd, "avance"},
    {7, &right_cmd, "droite"},
    {7, &left_cmd, "gauche"},
    {7, &see_cmd, "voir"},
    {7, &take_cmd, "prend"},
    {7, &put_cmd, "pose"},
    /* {7, , "expulse"}, */
    {7, &broadcast_cmd, "broadcast"},
    {42, &fork_cmd, "fork"},
    {300, &levelup_cmd, "incantation"},
    {0, &unknown_cmd, NULL}
  };

static t_graphicsmap	g_graphics_cmd[10] =
  {
    {"msz", &answer_msz},
    {"bct", &answer_bct},
    {"mct", &answer_mct},
    {"tna", &answer_tna},
    {"ppo", &answer_ppo},
    {"plv", &answer_plv},
    {"pin", &answer_pin},
    {"sgt", &answer_sgt},
    {"sst", &answer_sst},
    {NULL, &answer_suc}
  };

static void	add_task(t_users *u, char **args, char *orig_cmd)
{
  t_task	t;
  int		i;

  i = 0;
  while (g_commands[i].key != NULL &&
	 (!args[0] || strcmp(g_commands[i].key, args[0]) != 0))
    ++i;
  t.countdown = g_commands[i].countdown;
  t.f = g_commands[i].f;
  t.orig_cmd = orig_cmd;
  t.args = args;
  if (pretask_check(g_commands[i].key, u))
    push_back(u->tasks, new_link_by_param(&t, sizeof(t)));
  else
    {
      free(orig_cmd);
      free(args[0]);
      free(args);
    }
}

static void	answer_graphics(t_users *u, char **args, char *orig_cmd)
{
  int		i;

  i = 0;
  while (g_graphics_cmd[i].key != NULL &&
	 (!args[0] || strcmp(g_graphics_cmd[i].key, args[0])))
    ++i;
  if (args[0])
    (g_graphics_cmd[i].f)(u, &args[1]);
  else
    (g_graphics_cmd[i].f)(u, &args[0]);
  free(orig_cmd);
  free(args[0]);
  free(args);
}

static void	assign_client(t_users *u, char **args)
{
  t_link	*team_lnk;
  t_team	*team;
  bool		rmv;
  char		msg[LOG_MSG_SZ];

  rmv = false;
  if ((team_lnk = lookup(g_info.world.teams_names, args[0], &cmp_team)) &&
      ((t_team*)team_lnk->ptr)->free_slots > 0)
    {
      team = (t_team*)team_lnk->ptr;
      assign_pos(u, team);
      snprintf(msg, sizeof(msg),
	       "Player #%d joined game! Team: %s. Coordinates: %d-%d\n",
	       u->id, u->team->name, u->x, u->y);
      log_msg(stdout, msg);
    }
  else
    rmv = true;
  if (rmv)
    {
      u->life = 0;
      u->is_dead = true;
      push_back(u->messages, new_link_by_param(KO, sizeof(KO) + 1));
    }
}

void		exec_cmd(t_users *u, char **args, char *orig_cmd)
{
  if (u->first_message == false && u->type != TGRAPHICS &&
      u->tasks->size < 10)
    add_task(u, args, orig_cmd);
  else if (u->first_message == false && u->type == TGRAPHICS)
    answer_graphics(u, args, orig_cmd);
  else
    {
      if (args && args[0])
	{
	  if (!strcmp(args[0], GRAPHIC_USR))
	    {
	      u->type = TGRAPHICS;
	      greet_graphics(u);
	    }
	  else
	    assign_client(u, args);
	}
      u->first_message = false;
      free(orig_cmd);
      free(args[0]);
      free(args);
    }
}
