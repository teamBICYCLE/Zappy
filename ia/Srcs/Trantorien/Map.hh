//
// Map.hh for  in /home/carpen_t/projets/syst_Unix/Zappy/ia
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon Jun 25 13:50:09 2012 thibault carpentier
// Last update Fri Jul  6 14:41:02 2012 thibault carpentier
//

#ifndef _MAP_H_
# define _MAP_H_

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

  std::vector<unsigned int> caseContent(position coord);
  void update(void);
  void changeDirection(const int &direction);
  void avancer(void);
  void voir(const std::string &);
  void prendre(const std::string &value);
  void poser(const std::string &value);
  position getCurrentPos(void) const;
  UserGlobal::Direction getDirection(void) const;
};

#endif /*!_MAP_H_*/
