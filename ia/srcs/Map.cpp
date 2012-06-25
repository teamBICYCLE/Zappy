//
// Map.cpp for  in /home/carpen_t/projets/syst_Unix/Zappy/ia
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon Jun 25 13:50:12 2012 thibault carpentier
// Last update Mon Jun 25 15:40:40 2012 thibault carpentier
//

#include "Map.hh"

#include <iostream>

Map::Map(void)
  : currentPos_(0, 0)
{}

Map::~Map(void)
{}


void Map::update(std::string &values)
{
  std::cout << values << std::endl;
}
