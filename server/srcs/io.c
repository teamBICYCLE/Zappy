/*
** io.c for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Mon May 14 19:49:07 2012 Jonathan Machado
** Last update Wed Jun 13 13:25:12 2012 lois burg
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "server.h"
#include "refstring.h"
#include "protocol.h"

extern t_infos	g_info;

static void	handle_cmd(t_users *u, char *str)
{
  char		**cmd;
  int		i;

  (void)u;
  printf("%i -> %s\n", u->socket, str);
  cmd = parse(str, " \t\n");
  puts("Parsed command:");
  i = 0;
  while (cmd && cmd[i])
    {
      printf("%s\n", cmd[i]);
      ++i;
    }
  /* check cmd null */
  add_task(u, cmd);
}
#include "cmds.h"
void		add_user(void)
{
  t_users	new;

  new.socket = accept(g_info.ss, NULL, NULL);
  if (new.socket != -1)
    {
      g_info.smax = g_info.smax < new.socket ? new.socket : g_info.smax;
      new.x = 0;
      new.y = 0;
      new.lvl = 1;
      new.dir = NORTH;
      memset(&new.inventory, 0, sizeof(new.inventory));
      new.inventory[FOOD] = 10;
      new.life = new.inventory[FOOD] * 126;
      new.idx = 0;
      new.messages = new_list();
      new.first_message = true;
      push_back(new.messages, new_link_by_param(GREETINGS, sizeof(GREETINGS)));
      new.readring = new_ringbuffer(4096);
      new.tasks = new_list();
      push_front(g_info.users, new_link_by_param(&new, sizeof(new)));
      //TEMP
      g_info.map->cases[0][0].elements[PLAYER] = 1;
      inventory_cmd(&new, NULL);
      see_cmd(&new, NULL);
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

  user = ptr;
  if (FD_ISSET(user->socket, &g_info.readfds))
    {
      if (read_data(user->socket, user->readring) == 0)
	{
	  l = lookup_and_pop(g_info.users, &user->socket, &cmp_socket);
	  free_users(l->ptr);
	}
      else
	{
	  str = get_data(user->readring);
	  if (str)
	    handle_cmd(user, str);
	}
    }
}
