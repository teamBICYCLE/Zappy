/*
** graphic_response4.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Sat Jun 16 12:53:28 2012 lois burg
** Last update Wed Jun 20 17:34:52 2012 lois burg
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "graphics.h"

extern	t_infos	g_info;

char	*graphics_enw(t_users *egg)
{
  char	*msg;

  msg = get_graphics_buf();
  snprintf(msg, GRAPHICS_MSG_SZ, "enw %d %d %d %d\n",
	   egg->id, egg->father_id, egg->x, egg->y);
  return (msg);
}

char	*graphics_eht(const int egg_id)
{
  char	*msg;

  msg = get_graphics_buf();
  snprintf(msg, GRAPHICS_MSG_SZ, "eht %d\n", egg_id);
  return (msg);
}

char	*graphics_ebo(const int egg_id)
{
  char	*msg;

  msg = get_graphics_buf();
  snprintf(msg, GRAPHICS_MSG_SZ, "ebo %d\n", egg_id);
  return (msg);
}

char	*graphics_edi(const int egg_id)
{
  char	*msg;

  msg = get_graphics_buf();
  snprintf(msg, GRAPHICS_MSG_SZ, "edi %d\n", egg_id);
  return (msg);
}

char	*graphics_sgt(void)
{
  char	*msg;

  msg = get_graphics_buf();
  snprintf(msg, GRAPHICS_MSG_SZ, "sgt %d\n", g_info.world.action_delay);
  return (msg);
}
