/*
** actions.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Tue Jun 12 16:18:42 2012 lois burg
** Last update Mon Jul  9 11:27:01 2012 lois burg
*/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "cmds.h"
#include "server.h"
#include "log.h"
#include "graphics.h"
#include "task.h"

extern int	g_player_id;
extern t_infos	g_info;
extern char	*g_res_names[LAST];

static t_see_pair	g_see_tab[4] =
  {
    {&see_count_north, &see_north},
    {&see_count_east, &see_east},
    {&see_count_south, &see_south},
    {&see_count_west, &see_west}
  };

t_cmd_ret	see_cmd(t_users *usr, char **args, char *orig_cmd)
{
  t_cmd_ret	success;
  const t_map	*map = g_info.map;
  char		*content;

  (void)args;
  (void)orig_cmd;
  success = IGNORE;
  if ((content = calloc((g_see_tab[usr->dir].cf)(usr->x, usr->y, usr->lvl, map),
			sizeof(*content))))
    {
      strcat(content, "{");
      (g_see_tab[usr->dir].f)(usr, content, map);
      strcat(content, "}\n");
      push_back(usr->messages, new_link_by_param(content, strlen(content) + 1));
    }
  else
    success = FAILURE;
  free(content);
  return (success);
}

t_cmd_ret	inventory_cmd(t_users *usr, char **args, char *orig_cmd)
{
  int		i;
  char		val[INVENTORY_VAL_SZ];
  char		msg[INVENTORY_MSG_SZ];
  char		log[LOG_MSG_SZ];

  (void)args;
  (void)orig_cmd;
  i = 0;
  memset(msg, 0, sizeof(msg));
  strcat(msg, "{");
  while (i < NB_RESSOURCES)
    {
      if (i)
	strcat(msg, ", ");
      strcat(msg, g_res_names[i]);
      memset(val, 0, sizeof(val));
      sprintf(val, " %d", usr->inventory[i]);
      strcat(msg, val);
      ++i;
    }
  strcat(msg, "}\n");
  snprintf(log, sizeof(log), "Inventory of user #%d: %s", usr->id, msg);
  log_msg(stdout, log);
  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
  return (IGNORE);
}

static t_cmd_ret	hatch_egg(t_users *usr, char **args, char *orig_cmd)
{
  (void)args;
  (void)orig_cmd;
  usr->type = TGHOST;
  usr->readring = new_ringbuffer(4096);
  if (usr->readring == NULL)
    remove_user(usr);
  else
    {
      usr->dir = rand() % (WEST + 1);
      if (usr->team)
	++usr->team->free_slots;
      --g_info.map->cases[usr->y][usr->x].elements[EGG];
      ++g_info.map->cases[usr->y][usr->x].elements[PLAYER];
      lookup(g_info.users, graphics_eht(usr->id), &notify_graphic);
    }
  return (IGNORE);
}

static void	init_egg(t_users *egg, t_users *father)
{
  egg->socket = -1;
  egg->type = TEGG;
  egg->id = g_player_id++;
  egg->father_id = father->id;
  egg->lvl = 1;
  egg->x = father->x;
  egg->y = father->y;
  egg->tasks = new_list();
  egg->messages = new_list();
  egg->team = father->team;
  egg->inventory[FOOD] = 10;
  egg->life = egg->inventory[FOOD] * 126;
}

t_cmd_ret	fork_cmd(t_users *usr, char **args, char *orig_cmd)
{
  t_users	new;
  t_task	t;

  (void)args;
  (void)orig_cmd;
  memset(&t, 0, sizeof(t));
  memset(&new, 0, sizeof(new));
  init_egg(&new, usr);
  t.countdown = 600;
  t.f = &hatch_egg;
  ++g_info.map->cases[new.y][new.x].elements[EGG];
  push_back(new.tasks, new_link_by_param(&t, sizeof(t)));
  push_back(g_info.users, new_link_by_param(&new, sizeof(new)));
  lookup(g_info.users, graphics_enw(&new), &notify_graphic);
  return (SUCCESS);
}
