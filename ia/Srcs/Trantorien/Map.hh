//
// Map.hh for  in /home/carpen_t/projets/syst_Unix/Zappy/ia
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon Jun 25 13:50:09 2012 thibault carpentier
// Last update Sun Jul  8 17:03:49 2012 thibault carpentier
//

#ifndef _MAP_H_
# define _MAP_H_

#define ABS(x) ((x) < 0 ? (-x) : (x))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#include <vector>
#include <string>
#include "Ressources.hh"

typedef std::pair<int, int> position;

class Map
{
private:
  position  mapsize_;
  position  offset_;
  UserGlobal::Direction currentOrientation_;
  position  currentPos_;
  std::vector<position> items_[UserGlobal::JOUEUR + 1];

private:

  int offset(int nbCaseStair);
  void formatValues(int &distance, int &incrStart);
  void analyse(const std::string &);
  void remember(const std::string &caseContent, int distance, int incrStart);
  int updatePosition(int, int);
  void forgetPrevData(int, int);

  // reflexion in progress
  // position calculateDistance(int distance, int partialPos) const;

  Map(Map const &);
  Map& operator=(Map const &);
  static const std::string REGEX_VALUE;
public:
  Map();
  Map(position);
  ~Map(void);

  void  setSize(const position & mapsize);
  void  setSize(const std::string & mapsize);

  void test(void) const;

  int	changeFrame(position p, UserGlobal::Direction d);
  std::vector<unsigned int> caseContent(position coord);
  void update(void);
  void changeDirection(const int &direction);
  void avancer(void);
  void voir(const std::string &);
  void prendre(const std::string &value);
  void poser(const std::string &value);
  const position &  getCurrentPos(void) const;
  const position &  getSize(void) const;
  position          getClosestItem(position pos, int object) const;
  UserGlobal::Direction getDirection(void) const;
  void  poser(int object);
  void  prendre(int object);
};

#endif /*!_MAP_H_*/
