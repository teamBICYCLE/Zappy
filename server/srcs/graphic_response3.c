/*
** graphic_response3.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Sat Jun 16 12:36:22 2012 lois burg
** Last update Tue Jul  3 12:02:59 2012 lois burg
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "graphics.h"

char	*graphics_pie(const int x, const int y, const int success)
{
  char	*msg;

  msg = get_graphics_buf();
  snprintf(msg, GRAPHICS_MSG_SZ, "pie %d %d %d\n", x, y, success);
  return (msg);
}

char	*graphics_pfk(t_users *usr)
{
  char	*msg;

  msg = get_graphics_buf();
  snprintf(msg, GRAPHICS_MSG_SZ, "pfk %d\n", usr->id);
  return (msg);
}

char	*graphics_pdr(t_users *usr, const int res)
{
  char	*msg;

  msg = get_graphics_buf();
  snprintf(msg, GRAPHICS_MSG_SZ, "pdr %d %d\n", usr->id, res);
  return (msg);
}

char	*graphics_pgt(t_users *usr, const int res)
{
  char	*msg;

  msg = get_graphics_buf();
  snprintf(msg, GRAPHICS_MSG_SZ, "pgt %d %d\n", usr->id, res);
  return (msg);
}

char	*graphics_pdi(t_users *usr)
{
  char	*msg;

  msg = get_graphics_buf();
  snprintf(msg, GRAPHICS_MSG_SZ, "pdi %d\n", usr->id);
  return (msg);
}
