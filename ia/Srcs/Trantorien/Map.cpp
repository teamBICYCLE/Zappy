//
// Map.cpp for  in /home/carpen_t/projets/syst_Unix/Zappy/ia
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon Jun 25 13:50:12 2012 thibault carpentier
// Last update Sat Jul  7 15:58:39 2012 thibault carpentier
//

#include <sstream>
#include <boost/regex.hpp>
#include "Map.hh"
#include "TrantorienFailure.hh"

std::string const Map::REGEX_VALUE = " *\\{( *(joueur|linemate|deraumere|sibur|mendiane|phiras|thystame|nourriture) *([ ,]*|\\} *$){1} *)+ *\\} *";

Map::Map()
  : offset_(std::pair<int, int>(0, 0)), currentOrientation_(UserGlobal::EST), currentPos_(0, 0)
{
}

Map::Map(position mapsize)
  : mapsize_(mapsize), offset_(std::pair<int, int>(0, 0)), currentOrientation_(UserGlobal::EST), currentPos_(0, 0)
{}

Map::~Map(void)
{}

void Map::setSize(const position &mapsize)
{
  mapsize_ = mapsize;
}

void Map::setSize(const std::string &mapsize)
{
  std::stringstream  st(mapsize);
  position      size;

  st >> size.first;
  st >> size.second;
  setSize(size);
}

void	Map::changeDirection(const int &direction)
{
  if (direction == UserGlobal::DROITE)
    currentOrientation_ = (currentOrientation_ + 1 > UserGlobal::OUEST ?
                           UserGlobal::NORD : static_cast<UserGlobal::Direction>(currentOrientation_ + 1));
  else if (direction == UserGlobal::GAUCHE)
    currentOrientation_ = (currentOrientation_ - 1 < UserGlobal::NORD ?
                           UserGlobal::OUEST : static_cast<UserGlobal::Direction>(currentOrientation_ - 1));
}

int Map::updatePosition(int value, int size)
{
  int res;

  res = value;
  if (value >= size)
    res = value - size;
  else if (value < 0)
    res = value + size;
  return (res);
}

void Map::update(void)
{
  currentPos_.first += offset_.first;
  currentPos_.second += offset_.second;
}

void Map::avancer(void)
{
  switch (currentOrientation_)
    {
    case UserGlobal::NORD :
      currentPos_.second = updatePosition(currentPos_.second - 1, mapsize_.second);
      break;
    case UserGlobal::EST:
      currentPos_.first =  updatePosition(currentPos_.first + 1, mapsize_.first);
      break;
    case UserGlobal::SUD :
      currentPos_.second =  updatePosition(currentPos_.second + 1, mapsize_.second);
      break;
    case UserGlobal::OUEST :
      currentPos_.first =  updatePosition(currentPos_.first - 1, mapsize_.first);
      break;
    }
}

// temporary
#include <iostream>

int Map::offset(int nbCaseStair)
{

  int res = ((nbCaseStair -1) / 2);

  switch (currentOrientation_)
    {
    case UserGlobal::NORD :
      res = -res;
      break;
    case UserGlobal::EST :
      res = -res;
      break;
    default:
      break;
    }
  return (res);
}

void Map::formatValues(int &distance, int &incrStart)
{
  int savDistance = distance, savIncrStart = incrStart;

  switch (currentOrientation_)
    {
    case UserGlobal::NORD :
      distance = savIncrStart;
      incrStart = -savDistance;
      break;
    case UserGlobal::EST :
      distance = savDistance;
      incrStart = savIncrStart;
      break;
    case UserGlobal::SUD :
      distance = savIncrStart;
      incrStart = savDistance;
      break;
    case UserGlobal::OUEST :
      distance = -savDistance;
      incrStart = savIncrStart;
      break;
    }
}

void Map::forgetPrevData(int x, int y)
{
  for (unsigned int i = 0; i < (sizeof(GlobalToString::inventaireObject) / sizeof(std::string)); ++i)
    {
      unsigned int j = 0;
      while (j < items_[i].size())
        {
          if (items_[i][j].first == x && items_[i][j].second == y)
            items_[i].erase(items_[i].begin() + j);
          else
            ++j;
        }
    }

  (void)x;
  (void)y;
}

void Map::remember(const std::string &caseContent, int distance, int incrStart)
{
  formatValues(distance, incrStart);
  forgetPrevData(updatePosition(currentPos_.first + distance, mapsize_.first),
                 updatePosition(currentPos_.second + incrStart, mapsize_.second));
  for (unsigned int i = 0; i < (sizeof(GlobalToString::inventaireObject) / sizeof(std::string)); ++i)
    {
      boost::regex extract("(" + GlobalToString::inventaireObject[i] + ")");
      boost::match_results<std::string::const_iterator> what;
      std::string::const_iterator s1 = caseContent.begin();
      std::string::const_iterator s2 = caseContent.end();
      while(regex_search(s1, s2, what, extract, boost::match_default))
        {
          s1 = what[0].second;
          items_[i].push_back(position(updatePosition(currentPos_.first + distance, mapsize_.first),
                                       updatePosition(currentPos_.second + incrStart, mapsize_.second)));
        }
    }
}

void Map::test(void) const
{
  for (unsigned int i = 0;  i < (sizeof(GlobalToString::inventaireObject) / sizeof(std::string)); ++i)
    {
      std::vector<position>::const_iterator it;

      std::cout << "Item : " << GlobalToString::inventaireObject[i] << std::endl;
      for (it = items_[i].begin(); it != items_[i].end(); ++it)
        {
          std::cout << "X : " << (*it).first << " Y : " << (*it).second << std::endl;
        }
      std::cout << "end item" << std::endl;
    }
}

void Map::analyse(const std::string &values)
{
  // TEST
  //  currentOrientation_ = EST;

  size_t beginCaseParse = 0, endCaseParse = 0;
  unsigned int nbCaseStair = 1, savNbCaseStair = 0;
  int distance, incrStart, incrEnd;

  while (endCaseParse < std::string::npos)
    {
      if (nbCaseStair != savNbCaseStair)
        {
          incrStart = offset(nbCaseStair);
          incrEnd = -incrStart;
          savNbCaseStair = nbCaseStair;
          distance = incrStart > 0 ? incrStart : -incrStart;
        }
      endCaseParse = values.find(",", beginCaseParse);
      std::string caseSee(values, beginCaseParse, endCaseParse - beginCaseParse);
      remember(caseSee, distance, incrStart);
      beginCaseParse =  endCaseParse + 1;
      if (incrStart == incrEnd)
        nbCaseStair += 2;
      else
        {
          if (currentOrientation_ == UserGlobal::EST || currentOrientation_ == UserGlobal::NORD)
            ++incrStart;
          else
            --incrStart;
        }
    }
}

void Map::voir(const std::string &values)
{
  boost::regex regex(REGEX_VALUE);

  if (boost::regex_match(values, regex))
      analyse(values);
  else
    throw TrantorienFailure("Map voir", "Received " + values + " witch does not match with the regex " + REGEX_VALUE);
}

void Map::prendre(const std::string &value)
{
  for (unsigned int i = 0; i < (sizeof(GlobalToString::inventaireObject) / sizeof(std::string)); ++i)
    if (GlobalToString::inventaireObject[i] == value)
      for (std::vector<position>::iterator it = items_[i].begin(); it != items_[i].end(); ++it)
        {
          if ((*it).first == currentPos_.first && (*it).second == currentPos_.second)
            {
              items_[i].erase(it);
              return;
            }
        }
}

void Map::poser(const std::string &value)
{
  for (unsigned int i = 0; i < (sizeof(GlobalToString::inventaireObject) / sizeof(std::string)); ++i)
    if (GlobalToString::inventaireObject[i] == value)
      {
        items_[i].push_back(currentPos_);
        return;
      }
}

std::vector<unsigned int> Map::caseContent(position coord)
{
  std::vector<unsigned int> result;// = new std::vector<unsigned int>();
  for (unsigned int i = 0; i <= UserGlobal::JOUEUR; ++i)
    {
      unsigned int nbRessources = 0;
      for (std::vector<position>::iterator it = items_[i].begin(); it != items_[i].end(); ++it)
        if ((*it).first == currentPos_.first && (*it).second == currentPos_.second)
          ++nbRessources;
      result.push_back(nbRessources);
    }
  return (result);
}

position Map::getCurrentPos(void) const
{
  return (currentPos_);
}

position Map::getClosestItem(position pos, int object) const
{
  position res(-1, -1);
  position tmp(-1, -1);

  for (std::vector<position>::const_iterator it = items_[object].begin(); it != items_[object].end(); ++it)
    {
      if ((ABS(pos.first, (*it).first) + ABS(pos.first, (*it).second)) > (tmp.first + tmp.second))
	{
	  tmp.first = (ABS(pos.first, (*it).first));
	  tmp.second = (ABS(pos.second, (*it).second));
	  res.first = (*it).first;
	  res.second = (*it).second;
	}
    }
  return (res);
}

UserGlobal::Direction Map::getDirection() const
{
  return currentOrientation_;
}

//" *{( *(joueur|linemate|nourriture) *([ ,]*|} *$){1} *)+ *} *"

//         _____ _____ _____ _____ _____
//        |     |     |     |     |     |
//        |-2 -2|-1 -2|-0 -2|+1 -2|+2 -2|
//        |_____|_____|_____|_____|_____|
//              |     |     |     |
//              |-1 -1|-0 -1|+1 -1|
//              |_____|_____|_____|
//                    |     |
//                    |+0 -0|
//                    |_____|
//  _____                                _____
// |     |                              |     |
// |-2 -2|                              |+2 -2|
// |_____|_____                    _____|_____|
// |     |     |                  |     |     |
// |-2 -1|-1 -1|                  |+1 -1|+2 -1|
// |_____|_____|_____        _____| ____|_____|
// |     |     |     |      |     |     |     |
// |-2 -0|-1 -0|+0 +0|      |+0 +0|+1 -0|+2 +0|
// |_____|_____|_____|      |_____|_____|_____|
// |     |     |                  |     |     |
// |-2 +1|-1 +1|                  |+1 +1|+2 +1|
// |_____|_____|                  |_____|_____|
// |     |                              |     |
// |-2 +2|                              |+2 +2|
// |_____|                              |_____|
//                     _____
//                    |     |
//                    |+0 +0|
//               _____|_____|_____
//              |     |     |     |
//              |-1 +1|+0 +1|+1 +1|
//         _____|_____|_____|_____|_____
//        |     |     |     |     |     |
//        |-2 +2|-1 +2|-0 +2|+1 +2|+2 +2|
//        |_____|_____|_____|_____|_____|

// nbcase = 1;
// distance = +?- 0
// incrstart = 1 - 1 / 2
// nbcase += 2
//


//  __ __ __ __ __
// |  |  |  |  |  |
// | 4| 5| 6| 7| 8|
// |__|__|__|__|__|
//    |  |  |  |
//    | 1| 2| 3|
//    |__|__|__|
//       |  |
//       | 0|
//       |__|
