/*
** io.c for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Mon May 14 19:49:07 2012 Jonathan Machado
** Last update Mon Jul  2 18:34:33 2012 lois burg
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
  t_task_info	ti;

  memset(&ti, 0, sizeof(ti));
  ti.data = str;
  ti.duplicate = strdup(ti.data);
  ti.args = parse(ti.data, " \t\n");
  if (ti.args != NULL)
    exec_cmd(u, &ti);
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

  l = 0;
  user = ptr;
  if (l != -1 && user->messages->size > 0 &&
      FD_ISSET(user->socket, &g_info.writefds))
    {
      str = user->messages->head->ptr;
      l = send(user->socket, &str[user->idx], strlen(str) - user->idx, MSG_NOSIGNAL);
      if (l == -1)
	perror("send :");
      else
	{
	  user->idx += l;
	  if (user->idx >= strlen(str))
	    {
	      user->idx = 0;
	      free(str);
	      free(pop_front(user->messages));
	    }
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
	  if (user->team && user->type != TFORMER_GHOST)
	    ++user->team->free_slots;
	  l = lookup_and_pop(g_info.users, &user->socket, &cmp_socket);
	  if (user->type != TGRAPHICS)
	    lookup(g_info.users, graphics_pdi(l->ptr), &notify_graphic);
	  snprintf(msg, sizeof(msg), "User %d disconnected !\n", ((t_users*)l->ptr)->id);
	  log_msg(stdout, msg);
	  delete_link(l, &free_users);
	  user = NULL;
	}
      else if (user->type == TGRAPHICS)
	printf("-s-\n%s-e-\n", user->readring->data);
    }
  if (user != NULL && user->readring->end != 0 &&
      (str = get_data(user->readring)) != NULL)
    {
      puts("ok");
      handle_cmd(user, str);
    }
}
