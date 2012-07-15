/*
** io.c for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Mon May 14 19:49:07 2012 Jonathan Machado
** Last update Sun Jul 15 18:53:03 2012 Thomas Duplomb
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
  else
    free_task_info(&ti);
}

void		remove_user(t_users *u)
{
  t_link	*l;
  char		msg[LOG_MSG_SZ];

  l = lookup_and_pop(g_info.users, &u->id, &cmp_id);
  if (u->first_message == false)
    {
      if (u->team && u->type == TPLAYER)
	++u->team->free_slots;
      if (u->type == TPLAYER || u->type == TFORMER_GHOST)
	lookup(g_info.users, graphics_pdi(u), &notify_graphic);
      if (u->life > 0)
	snprintf(msg, sizeof(msg), "User %d disconnected (kicked?)!\n", u->id);
      else
	snprintf(msg, sizeof(msg), "User %d died a horrible death!\n", u->id);
      loot_plyr(u);
    }
  else
    snprintf(msg, sizeof(msg), "User %d left!\n", u->id);
  log_msg(stdout, msg);
  delete_link(l, &free_users);
}

void		add_user(void)
{
  t_users	new;
  char		log[LOG_MSG_SZ];

  memset(&new, 0, sizeof(new));
  if ((new.socket = accept(g_info.ss, NULL, NULL)) != -1)
    {
      g_info.smax = g_info.smax < new.socket ? new.socket : g_info.smax;
      init_new_user(&new);
      if (new.tasks != NULL && new.messages != NULL && new.readring != NULL)
	{
	  push_back(new.messages, new_link_by_param(GREETINGS, sizeof(GREETINGS)));
	  push_back(g_info.users, new_link_by_param(&new, sizeof(new)));
	  snprintf(log, sizeof(log), "New user connected ! Welcome %d.\n", new.id);
	}
      else
	{
	  snprintf(log, sizeof(log), "Memory exhausted for user #%d.\n", new.id);
	  close(new.socket);
	}
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
  if (user->type != TEGG && user->type != TGHOST && user->messages->size > 0 &&
      FD_ISSET(user->socket, &g_info.writefds))
    {
      str = user->messages->head->ptr;
      if ((l = send(user->socket, &str[user->idx],
		    strlen(str) - user->idx, MSG_NOSIGNAL)) == -1)
	{
	  perror("send :");
	  remove_user(user);
	}
      else if ((user->idx += l) >= strlen(str))
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

  user = ptr;
  if (user != NULL && user->readring != NULL &&
      FD_ISSET(user->socket, &g_info.readfds))
    {
      if (read_data(user->socket, user->readring) <= 0)
	{
	  remove_user(user);
	  user = NULL;
	}
    }
  if (user != NULL && user->readring != NULL && user->readring->end != 0 &&
      user->is_dead == false && (str = get_data(user->readring)) != NULL)
    handle_cmd(user, str);
}
