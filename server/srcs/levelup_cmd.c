/*
** levelup_cmd.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Thu Jun 21 11:44:28 2012 lois burg
** Last update Sun Jul 15 18:12:03 2012 lois burg
*/

#include "log.h"
#include "cmds.h"
#include "graphics.h"

extern t_infos	g_info;
extern int	g_res_to_restore[NB_RESSOURCES];
static uint	g_lvl_req[7][LAST] =
  {
    {0, 1, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0, 0, 0, 2, 0},
    {0, 2, 0, 1, 0, 2, 0, 2, 0},
    {0, 1, 1, 2, 0, 1, 0, 4, 0},
    {0, 1, 2, 1, 3, 0, 0, 4, 0},
    {0, 1, 2, 3, 0, 1, 0, 6, 0},
    {0, 2, 2, 2, 2, 2, 1, 6, 0}
  };

static bool	check_plyr_lvl(const int x, const int y, const int lvl)
{
  uint		i;
  t_users	*plyr;
  t_link	*plyr_lnk;
  bool		valid;

  i = 0;
  valid = true;
  while (valid && i < g_info.users->size)
    {
      if ((plyr_lnk = get_link(g_info.users, i)))
	{
	  plyr = (t_users*)plyr_lnk->ptr;
	  if (plyr->type == TPLAYER || plyr->type == TFORMER_GHOST)
	    {
	      if (plyr->x == x && plyr->y == y && plyr->lvl != lvl)
		valid = false;
	    }
	}
      ++i;
    }
  return (valid);
}

static void	lvlup_plyr(const int x, const int y, const int lvl)
{
  uint		i;
  t_users	*plyr;
  t_link	*plyr_lnk;
  char		msg[LOG_MSG_SZ];

  i = 0;
  while (i < g_info.users->size)
    {
      if ((plyr_lnk = get_link(g_info.users, i)))
	{
	  plyr = (t_users*)plyr_lnk->ptr;
	  if (plyr->x == x && plyr->y == y && plyr->lvl == lvl &&
	      (plyr->type == TPLAYER || plyr->type == TFORMER_GHOST))
	    {
	      ++plyr->lvl;
	      check_end_game(plyr);
	      snprintf(msg, sizeof(msg), "Level up! Player #%d (%d-%d)"
		       " is level %d!\n",
		       plyr->id, plyr->x, plyr->y, plyr->lvl);
	      log_msg(stdout, msg);
	    }
	}
      ++i;
    }
}

static void	decr_res(const int x, const int y, const int lvl)
{
  int		res;

  res = LINEMATE;
  while (res < PLAYER)
    {
      g_info.map->cases[y][x].elements[res] -= g_lvl_req[lvl - 1][res];
      g_res_to_restore[res] += g_lvl_req[lvl - 1][res];
      ++res;
    }
}

bool	check_levelup(t_users *summoner)
{
  bool	valid;
  int	res;

  valid = true;
  res = LINEMATE;
  while (valid && res <= PLAYER)
    {
      if (g_info.map->cases[summoner->y][summoner->x].elements[res] !=
	  g_lvl_req[summoner->lvl - 1][res])
	valid = false;
      ++res;
    }
  if (valid)
    valid = check_plyr_lvl(summoner->x, summoner->y, summoner->lvl);
  return (valid);
}

t_cmd_ret	levelup_cmd(t_users *usr, char **args, char *orig_cmd)
{
  (void)args;
  (void)orig_cmd;
  if (check_levelup(usr))
    {
      decr_res(usr->x, usr->y, usr->lvl);
      lvlup_plyr(usr->x, usr->y, usr->lvl);
      send_graphic_result(usr, 1);
      return (IGNORE);
    }
  else
    send_graphic_result(usr, 0);
  return (FAILURE);
}
