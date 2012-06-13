/*
** actions_utils.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Tue Jun 12 16:55:25 2012 lois burg
** Last update Wed Jun 13 13:20:03 2012 lois burg
*/

#include "cmds.h"
#include "server.h"

static t_res_str	g_res_str[10] =
  {
    {FOOD, "nourriture"},
    {LINEMATE, "linemate"},
    {DERAUMERE, "deraumere"},
    {SIBUR, "sibur"},
    {MENDIANE, "mendiane"},
    {PHIRAS, "phiras"},
    {THYSTAME, "thystame"},
    {PLAYER, "joueur"},
    {EGG, "oeuf"},
    {-1, NULL}
  };

char	*map_ressource(int res)
{
  int	i;

  i = 0;
  while (g_res_str[i].res != - 1 && g_res_str[i].res != res)
    ++i;
  return (g_res_str[i].res_str);
}
