/*
** misc_cmds.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Tue Jun 19 11:23:07 2012 lois burg
** Last update Tue Jun 19 17:46:03 2012 lois burg
*/

#include <stdio.h>
#include <string.h>
#include "cmds.h"
#include "server.h"

t_cmd_ret	connect_nbr_cmd(t_users *usr, char **args, char *orig_cmd)
{
  char		msg[CONNECT_MSG_SZ];

  (void)args;
  (void)orig_cmd;
  memset(msg, 0, sizeof(msg));
  snprintf(msg, sizeof(msg), "%d\n", usr->team->free_slots);
  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
  return (IGNORE);
}
