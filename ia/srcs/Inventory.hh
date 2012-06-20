// Inventory.hh

//{nourriture 10,linemate 0,deraumere 0,sibur 0,mendiane 0,phiras 0,thystame 0}

#ifndef _INVENTORY_HH_
#define _INVENTORY_HH_

#include <string>
#include <vector>

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
  std::vector<unsigned int>  parse(const std::string & values);

private:
  std::vector<unsigned int> inventory_;
};

#endif // _INVENTORY_HH_
