//
// Map.cpp for  in /home/carpen_t/projets/syst_Unix/Zappy/ia
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon Jun 25 13:50:12 2012 thibault carpentier
// Last update Wed Jun 27 14:16:25 2012 thibault carpentier
//

#include "Map.hh"

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

#include <iostream>
void Map::voir(const std::string &values)
{
  std::cout << values << std::endl;
}
