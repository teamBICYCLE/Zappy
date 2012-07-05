/*
** graphic_response5.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Sat Jun 16 15:13:51 2012 lois burg
** Last update Thu Jul  5 17:52:57 2012 lois burg
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "graphics.h"

char	*graphics_seg(const char *win_team)
{
  char	*msg;

  msg = get_graphics_buf();
  snprintf(msg, GRAPHICS_MSG_SZ, "seg %s\n", win_team);
  return (msg);
}

char	*graphics_smg(const char *serv_msg)
{
  char	*msg;

  msg = get_graphics_buf();
  snprintf(msg, GRAPHICS_MSG_SZ, "smg %s\n", serv_msg);
  return (msg);
}

char	*graphics_suc(void)
{
  char	*msg;

  msg = get_graphics_buf();
  snprintf(msg, GRAPHICS_MSG_SZ, "suc\n");
  return (msg);
}

char	*graphics_sbp(void)
{
  char	*msg;

  msg = get_graphics_buf();
  snprintf(msg, GRAPHICS_MSG_SZ, "sbp\n");
  return (msg);
}

char	*graphics_gkp(t_users *u)
{
  char	*msg;

  msg = get_graphics_buf();
  snprintf(msg, GRAPHICS_MSG_SZ, "gkp %d\n", u->id);
  return (msg);
}
