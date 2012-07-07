/*
** utils4.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server/srcs
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Sat Jul  7 14:07:59 2012 lois burg
** Last update Sat Jul  7 14:09:35 2012 lois burg
*/

#include <stdlib.h>
#include "server.h"

extern int	g_player_id;

void	init_new_user(t_users *new)
{
  new->id = g_player_id++;
  new->lvl = 1;
  new->dir = rand() % (WEST + 1);
  new->inventory[FOOD] = 5;
  new->life = (new->inventory[FOOD] * 126);
  new->messages = new_list();
  new->first_message = true;
  new->readring = new_ringbuffer(4096);
  new->tasks = new_list();
}
