/*
** args_conf.c for zappy in /home/burg_l//Work/tek2/unix/Zappy/server
**
** Made by lois burg
** Login   <burg_l@epitech.net>
**
** Started on  Wed Jul 11 14:39:17 2012 lois burg
** Last update Wed Jul 11 15:23:38 2012 lois burg
*/

#include <stdio.h>
#include <stdbool.h>

extern double	g_max_res_case;
extern double	g_food_pctg;
extern double	g_stones_pctg;

bool	set_max_res_case(double val)
{
  bool	ret;

  ret = true;
  if (val >= 0)
    g_max_res_case = (int)val;
  else
    {
      fprintf(stderr, "Max ressources per cases invalid "
	      "(should be > 0, value is %f).\n", val);
      ret = false;
    }
  return (ret);
}

bool	set_food_pctg(double val)
{
  bool	ret;

  ret = true;
  if (val >= 0 && val <= 100)
    g_food_pctg = val;
  else
    {
      fprintf(stderr, "Food percentage invalid (should be between "
	      "0 and 100, value is %f).\n", val);
      ret = false;
    }
  return (ret);
}

bool	set_stones_pctg(double val)
{
  bool	ret;

  ret = true;
  if (val >= 0 && val <= 100)
    g_stones_pctg = val;
  else
    {
      fprintf(stderr, "Stones percentage invalid (should be between "
	      "0 and 100, value is %f).\n", val);
      ret = false;
    }
  return (ret);
}
