/*
** actions.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Tue Jun 12 16:18:42 2012 lois burg
** Last update Wed Jun 20 13:50:20 2012 lois burg
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

static t_see_pair	g_see_tab[5] =
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
  snprintf(log, sizeof(log), "Inventory of user #%lu: %s", usr->idx, msg);
  log_msg(stdout, log);
  push_back(usr->messages, new_link_by_param(msg, strlen(msg) + 1));
  return (IGNORE);
}

static t_cmd_ret	hatch_egg(t_users *usr, char **args, char *orig_cmd)
{
  (void)args;
  (void)orig_cmd;
  usr->is_egg = false;
  usr->is_ghost = true;
  usr->dir = rand() % (WEST + 1);
  if (usr->team)
    ++usr->team->free_slots;
  lookup(g_info.users, graphics_eht(usr->id), &notify_graphic);
  return (IGNORE);
}

t_cmd_ret	fork_cmd(t_users *usr, char **args, char *orig_cmd)
{
  t_users	new;
  t_task	t;

  (void)args;
  (void)orig_cmd;
  memset(&t, 0, sizeof(t));
  memset(&new, 0, sizeof(new));
  new.is_egg = true;
  new.id = g_player_id++;
  new.lvl = 1;
  new.messages = new_list();
  new.tasks = new_list();
  new.readring = new_ringbuffer(4096);
  new.team = usr->team;
  new.inventory[FOOD] = 10;
  new.life = new.inventory[FOOD] * 126 * 500;/* temporaire */
  t.countdown = 600;
  t.f = &hatch_egg;
  push_back(new.tasks, new_link_by_param(&t, sizeof(t)));
  push_back(g_info.users, new_link_by_param(&new, sizeof(new)));
  lookup(g_info.users, graphics_enw(usr, new.id), &notify_graphic);
  return (SUCCESS);
}