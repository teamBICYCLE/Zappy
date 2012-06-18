/*
** cmds.c for zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Tue Jun 12 15:51:42 2012 Jonathan Machado
** Last update Mon Jun 18 18:04:01 2012 lois burg
*/

#include <stdlib.h>
#include <string.h>
#include "protocol.h"
#include "task.h"
#include "cmds.h"
#include "graphics.h"

extern t_infos	g_info;

static bool	unknown_cmd(t_users *user, char **args)
{
  (void)user;
  (void)args;
  return (false);
}

static t_tasksmap	g_commands[] =
  {
    /* {0, , "connect_nbr"}, */
    {1, &inventory_cmd, "inventaire"},
    /* {7, , "avance"}, */
    {7, &right_cmd, "droite"},
    {7, &left_cmd, "gauche"},
    {7, &see_cmd, "voir"},
    /* {7, , "prend"}, */
    {7, &put_cmd, "pose"},
    /* {7, , "expulse"}, */
    /* {7, , "broadcast"}, */
    /* {42, , "fork"}, */
    /* {300, , "incantation"}, */
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

static void	add_task(t_users *u, char **args)
{
  t_task	t;
  int		i;

  i = 0;
  while (g_commands[i].key != NULL &&
	 strcmp(g_commands[i].key, args[0]) != 0)
    ++i;
  t.countdown = g_commands[i].countdown;
  t.f = g_commands[i].f;
  t.args = args;
  push_back(u->tasks, new_link_by_param(&t, sizeof(t)));
}

static void	answer_graphics(t_users *u, char **args)
{
  int		i;

  i = 0;
  while (g_graphics_cmd[i].key != NULL &&
	 strcmp(g_graphics_cmd[i].key, args[0]))
    ++i;
  (g_graphics_cmd[i].f)(u, &args[1]);
}

static void	assign_client(t_users *u, char **args)
{
  t_link	*team;

  if ((team = lookup(g_info.world.teams_names, args[0], &cmp_team)))
    {
    }
  else
    {
      u->life = 0;
      u->is_dead = true;
      push_back(u->messages, new_link_by_param(KO, sizeof(KO) + 1));
    }
  free(args[0]);//j'aime pas trop devoir free comme ca... C'est parce que la tache est pas ajoutee car elle est invalide, du coup pas de free en sortant
  free(args);
}

void		exec_cmd(t_users *u, char **args)
{
  if (u->first_message == false && u->is_graphics == false)
    add_task(u, args);
  else if (u->first_message == false && u->is_graphics == true)
    answer_graphics(u, args);
  else
    {
      if (args && args[0])
	{
	  if (!strcmp(args[0], GRAPHIC_USR))
	    {
	      u->is_graphics = true;
	      greet_graphics(u);
	    }
	  else
	    assign_client(u, args);
	}
      u->first_message = false;
    }
}
