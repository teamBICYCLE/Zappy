//
// Inventory.hh for  in /home/carpen_t/projets/syst_Unix/Zappy/ia
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Fri Jun 22 10:46:34 2012 thibault carpentier
// Last update Fri Jun 22 12:34:02 2012 thibault carpentier
//

//{nourriture 10,linemate 0,deraumere 0,sibur 0,mendiane 0,phiras 0,thystame 0}

#ifndef _INVENTORY_HH_
#define _INVENTORY_HH_

#include <string>
#include <vector>
#include <QtCore/QString>

class Inventory {

  enum itemType {NOURRITURE = 0,
                 LINEMATE,
                 DERAUMERE,
                 SIBUR,
                 MENDIANE,
                 PHIRAS,
                 THYSTAME,
                 END};

public:
  Inventory();
  Inventory(const std::string & values);
  Inventory(const Inventory & source);
  Inventory &   operator=(const Inventory & source);
  ~Inventory();

  void      update(const std::string & values);

private:
  static std::string const REGEX_VALUE;
  std::vector<unsigned int>  parse(const std::string & values);

private:
  std::vector<unsigned int> inventory_;
};

#endif // _INVENTORY_HH_
