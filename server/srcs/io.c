/*
** io.c for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Mon May 14 19:49:07 2012 Jonathan Machado
** Last update Tue Jun 26 17:05:30 2012 Jonathan Machado
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "server.h"
#include "refstring.h"
#include "protocol.h"
#include "log.h"
#include "graphics.h"

int		g_player_id = 1;
extern t_infos	g_info;

static void	handle_cmd(t_users *u, char *str)
{
  char		*orig_cmd;
  char		**cmd;

  (void)u;
  orig_cmd = strdup(str);
  cmd = parse(str, " \t\n");
  if (cmd != NULL && cmd[0] == NULL)
    free(str);
  if (cmd != NULL)
    exec_cmd(u, cmd, orig_cmd);
}

void		add_user(void)
{
  t_users	new;
  char		log[LOG_MSG_SZ];

  memset(&new, 0, sizeof(new));
  new.socket = accept(g_info.ss, NULL, NULL);
  if (new.socket != -1)
    {
      g_info.smax = g_info.smax < new.socket ? new.socket : g_info.smax;
      new.id = g_player_id++;
      new.lvl = 1;
      new.dir = NORTH;
      new.inventory[FOOD] = 10;
      new.life = (new.inventory[FOOD] * 126) * 500;/* * 500 temporaire */
      new.messages = new_list();
      new.first_message = true;
      push_back(new.messages, new_link_by_param(GREETINGS, sizeof(GREETINGS)));
      new.readring = new_ringbuffer(4096);
      new.tasks = new_list();
      push_back(g_info.users, new_link_by_param(&new, sizeof(new)));
      snprintf(log, sizeof(log), "New user connected ! Welcome %d.\n", new.id);
      log_msg(stdout, log);
    }
  else
    perror("socket :");
}

void		write_user(void *ptr)
{
  int		l;
  t_users      	*user;
  char		*str;

  user = ptr;
  if (user->messages->size > 0 &&
      FD_ISSET(user->socket, &g_info.writefds))
    {
      str = user->messages->head->ptr;
      l = send(user->socket, &str[user->idx], strlen(str) - user->idx, 0);
      if (l == -1)
	perror("send :");
      user->idx += l;
      if (user->idx >= strlen(str))
	{
	  user->idx = 0;
	  free(str);
	  free(pop_front(user->messages));
	}
    }
}

void		read_user(void *ptr)
{
  char		*str;
  t_users      	*user;
  t_link	*l;
  char		msg[LOG_MSG_SZ];

  user = ptr;
  if (FD_ISSET(user->socket, &g_info.readfds))
    {
      if (read_data(user->socket, user->readring) == 0)
	{
	  if (user->team)
	    ++user->team->free_slots;
	  l = lookup_and_pop(g_info.users, &user->socket, &cmp_socket);
	  lookup(g_info.users, graphics_pdi(l->ptr), &notify_graphic);
	  snprintf(msg, sizeof(msg), "User %d disconnected !\n", ((t_users*)l->ptr)->id);
	  log_msg(stdout, msg);
	  delete_link(l, &free_users);
	}
      else if ((str = get_data(user->readring)) != NULL)
	handle_cmd(user, str);
    }
}
