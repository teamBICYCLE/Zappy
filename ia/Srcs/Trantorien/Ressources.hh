//
// Ressources.hh for  in /home/carpen_t/projets/syst_Unix/Zappy/ia
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Thu Jul  5 16:31:00 2012 thibault carpentier
// Last update Mon Jul  9 12:08:35 2012 thibault carpentier
//

#ifndef _RESSOURCES_H_
# define _RESSOURCES_H_

#include <string>

namespace UserGlobal
{
  enum SoundDirection
    {
      NODIR = 0,
      FRONT = 1,
      FRONTLEFT = 2,
      LEFT = 3,
      BEHINDLEFT = 4,
      BEHIND = 5,
      BEHINDRIGHT = 6,
      RIGHT = 7,
      FRONTRIGHT = 8
    };

  enum Direction
    {
    NONE = 0,
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

  enum Orientation
    {
      GAUCHE = 0,
      DROITE
    };

}

namespace GlobalToString {

std::string const orientation[] = {"gauche", "droite"};

std::string const inventaireObject[] =
  {"nourriture", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame", "joueur"};
}

int const levels[8][8] =
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
