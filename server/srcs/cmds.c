/*
** cmds.c for zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Tue Jun 12 15:51:42 2012 Jonathan Machado
** Last update Fri Jun 15 14:47:44 2012 Jonathan Machado
*/

#include <string.h>
#include "protocol.h"
#include "task.h"
#include "cmds.h"

static bool	unknown_cmd(t_users *user, char **args)
{
  (void)args;
  push_back(user->messages, new_link_by_param(KO, sizeof(KO)));
  return (true);
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

void		add_task(t_users *u, char ** args)
{
  int		i;
  t_task	t;

  i = 0;
  if (u->first_message == false)
    {
      while (g_commands[i].key != NULL &&
	     strcmp(g_commands[i].key, args[0]) != 0)
	++i;
      t.countdown = g_commands[i].countdown;
      t.f = g_commands[i].f;
      t.args = args;
      push_back(u->tasks, new_link_by_param(&t, sizeof(t)));
    }
  else
    {
      // l'ajoute a un oeuf avec ses positions et init sa vie puis suprimer l'oeuf
      // passer u->first_message = false
    }
}
