//
// Map.hh for  in /home/carpen_t/projets/syst_Unix/Zappy/ia
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon Jun 25 13:50:09 2012 thibault carpentier
// Last update Fri Jun 29 10:27:50 2012 thibault carpentier
//

#ifndef _MAP_H_
# define _MAP_H_

#include <vector>
#include <string>

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
  };

typedef std::pair<int, int> position;

class Map
{
private:
  position  mapsize_;
  position  offset_;
  Direction currentOrientation_;
  position  currentPos_;
  std::vector<position> items[THYSTAME];

private:
  void analyse(const std::string &);
  int updatePosition(int, int);

  Map(Map const &);
  Map& operator=(Map const &);
  static const std::string REGEX_VALUE;
public:
  Map(position);
  ~Map(void);

  void update(void);
  void changeDirection(const std::string &direction);
  void avancer(void);
  void voir(const std::string &);
};

#endif /*!_MAP_H_*/
