/*
** reset_game.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Thu Jul  5 12:48:32 2012 lois burg
** Last update Thu Jul  5 12:54:31 2012 lois burg
*/

#include <stdio.h>
#include "graphics.h"
#include "server.h"

extern t_infos	g_info;

void	reset_game(void)
{
  printf("Team %s won!\n", g_info.winner->name);
  g_info.end_game = false;
  lookup(g_info.users, graphics_seg(g_info.winner->name), &notify_graphic);
}
