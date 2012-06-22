//
// Inventory.cpp for  in /home/carpen_t/projets/syst_Unix/Zappy/ia
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Fri Jun 22 10:46:29 2012 thibault carpentier
// Last update Fri Jun 22 13:57:33 2012 thibault carpentier
//

#include <iostream>
#include <boost/regex.hpp>
#include "Inventory.hh"


std::string const           Inventory::REGEX_VALUE = " *\\{( *[A-Za-z]+ *[0-9]+ *,)* *[A-Za-z]+ *[0-9]+ *\\}";
//" *\\{[A-Za-z]+ *[0-9]+ *,";
Inventory::Inventory()
{
  this->inventory_.resize(END);
}

Inventory::Inventory(const std::string &values)
{
  this->update(values);
}

Inventory::Inventory(const Inventory &source)
{
  this->inventory_ = source.inventory_;
}

Inventory &Inventory::operator=(const Inventory &source)
{
  if (this != &source)
    {
      this->inventory_ = source.inventory_;
    }
  return *this;
}

Inventory::~Inventory()
{
}

void Inventory::update(const std::string &values)
{
  this->inventory_ = this->parse(values);
}

std::vector<unsigned int> Inventory::parse(const std::string &values)
{
  boost::regex regex(REGEX_VALUE);
  std::vector<unsigned int> ret;

  if (boost::regex_match(values, regex))
    std::cout << values << std::endl;
  return ret;
}
