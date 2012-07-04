//
// Map.cpp for  in /home/carpen_t/projets/syst_Unix/Zappy/ia
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon Jun 25 13:50:12 2012 thibault carpentier
// Last update Sat Jun 30 16:08:58 2012 thibault carpentier
//

#include <boost/regex.hpp>
#include "Map.hh"
#include "TrantorienFailure.hh"

std::string const Map::values_[] =
  {"nourriture", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};
std::string const Map::REGEX_VALUE = " *\\{( *(joueur|linemate|deraumere|sibur|mendiane|phiras|thystame|nourriture) *([ ,]*|\\} *$){1} *)+ *\\} *";

Map::Map(position mapsize)
  : mapsize_(mapsize), offset_(std::pair<int, int>(0, 0)), currentOrientation_(EST), currentPos_(0, 0)
{}

Map::~Map(void)
{}

void	Map::changeDirection(const std::string &direction)
{
  if (direction == "droite")
    currentOrientation_ = (currentOrientation_ + 1 > OUEST ?
                           NORD : static_cast<Direction>(currentOrientation_ + 1));
  else if (direction == "gauche")
    currentOrientation_ = (currentOrientation_ - 1 < NORD ?
                           OUEST : static_cast<Direction>(currentOrientation_ - 1));
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
    case NORD :
      currentPos_.second = updatePosition(currentPos_.second - 1, mapsize_.second);
      break;
    case EST:
      currentPos_.first =  updatePosition(currentPos_.first + 1, mapsize_.first);
      break;
    case SUD :
      currentPos_.second =  updatePosition(currentPos_.second + 1, mapsize_.second);
      break;
    case OUEST :
      currentPos_.first =  updatePosition(currentPos_.first - 1, mapsize_.first);
      break;
    }
  //  std::cout << currentPos_.first << " " << currentPos_.second << std::endl;
}

// temporary
#include <iostream>

int Map::offset(int nbCaseStair)
{

  int res = ((nbCaseStair -1) / 2);

  switch (currentOrientation_)
    {
    case NORD :
      res = -res;
      break;
    case EST :
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
    case NORD :
      distance = savIncrStart;
      incrStart = -savDistance;
      break;
    case EST :
      distance = savDistance;
      incrStart = savIncrStart;
      break;
    case SUD :
      distance = savIncrStart;
      incrStart = savDistance;
      break;
    case OUEST :
      distance = -savDistance;
      incrStart = savIncrStart;
      break;
    }
}

void Map::remember(const std::string &caseContent, int distance, int incrStart)
{
  formatValues(distance, incrStart);
  for (unsigned int i = 0; i < (sizeof(values_) / sizeof(std::string)); ++i)
    {
      //std::cout << "testing " << values_[i] << std::endl;
      boost::regex extract("(" + values_[i] + ")");
      boost::match_results<std::string::const_iterator> what;
      regex_search(caseContent.begin(), caseContent.end(), what, extract, boost::match_default);
      if (what[1] != "")
        ;//	addPosition(i, distance, incrStart);
    }
//  std::cout << " X : " << distance
//	    << " Y : " << incrStart
//	    << std::endl;
}

void Map::analyse(const std::string &values)
{
  // TEST
  currentOrientation_ = EST;

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
      //std::cout <<"result : "<< caseSee << std::endl;
      // std::cout << "Je me situe a l'etage : " << distance
      // 		<< " comportant " << nbCaseStair << " cases."
      // 		<< "Je vais avoir un offset de  : " << incrStart
      // 		<< std::endl;
      remember(caseSee, distance, incrStart);
      beginCaseParse =  endCaseParse + 1;
      if (incrStart == incrEnd)
        nbCaseStair += 2;
      else
        {
          if (currentOrientation_ == EST || currentOrientation_ == NORD)
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
    {
      std::cout << values << std::endl;
      analyse(values);
    }
  else
    throw TrantorienFailure("Map voir", "Received " + values + " witch does not match with the regex " + REGEX_VALUE);
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
