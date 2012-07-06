//
// Ressources.hh for  in /home/carpen_t/projets/syst_Unix/Zappy/ia
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Thu Jul  5 16:31:00 2012 thibault carpentier
// Last update Fri Jul  6 14:51:38 2012 thibault carpentier
//

#ifndef _RESSOURCES_H_
# define _RESSOURCES_H_

enum Direction
  {
    NORD = 1,
    EST = 2,
    SUD = 3,
    OUEST = 4
  };

enum Ressources
  {
    NOURRITURE = 0,
    LINEMATE = 1,
    DERAUMERE = 2,
    SIBUR = 3,
    MENDIANE = 4,
    PHIRAS = 5,
    THYSTAME = 6,
    JOUEUR = 7
  };

std::string const g_values[] =
  {"nourriture", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame", "joueur"};

int const g_levels[8][8] =
  {
    {0, 1, 0, 0, 0, 0, 0, 1},
    {0, 1, 1, 1, 0, 0, 0, 2},
    {0, 2, 0, 1, 0, 2, 0, 2},
    {0, 1, 1, 2, 0, 1, 0, 4},
    {0, 1, 2, 1, 3, 0, 0, 4},
    {0, 1, 2, 3, 0, 1, 0, 6},
    {0, 2, 2, 2, 2, 2, 1, 6},
  };

#endif /*!_RESSOURCES_H_*/
