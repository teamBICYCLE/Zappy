//
// Inventory.cpp for  in /home/carpen_t/projets/syst_Unix/Zappy/ia
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Fri Jun 22 10:46:29 2012 thibault carpentier
// Last update Fri Jul 13 15:12:11 2012 thibault carpentier
//

#include <iostream>
#include <sstream>
#include <boost/regex.hpp>
#include "Inventory.hh"
#include "TrantorienFailure.hh"
#include "Ressources.hh"

std::string const           Inventory::REGEX_VALUE = " *\\{( *[A-Za-z]+ +[0-9]+ *,)* *[A-Za-z]+ +[0-9]+ *\\}";

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

const std::vector<unsigned int> &Inventory::getInventory(void) const
{
  return (inventory_);
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
{}

void Inventory::update(const std::string &values)
{
  this->inventory_ = this->parse(values);
}


void Inventory::prendre(const std::string &value)
{
  for (unsigned int i = 0; i < (sizeof(GlobalToString::inventaireObject) / sizeof(std::string)); ++i)
    {
      if (GlobalToString::inventaireObject[i] == value)
        ++inventory_[i];
    }
}

void Inventory::poser(const std::string &value)
{
  for (unsigned int i = 0; i < (sizeof(GlobalToString::inventaireObject) / sizeof(std::string)); ++i)
    {
      if (GlobalToString::inventaireObject[i] == value)
        --inventory_[i];
    }
}

std::vector<unsigned int> Inventory::parse(const std::string &values)
{
  boost::regex regex(REGEX_VALUE);
  std::vector<unsigned int> ret;

  ret.resize(END);
  if (boost::regex_match(values, regex))
    {
      for (unsigned int i = 0; i < (sizeof(GlobalToString::inventaireObject) / sizeof(std::string)); ++i)
        {
          boost::regex extract(" *" + GlobalToString::inventaireObject[i] + " +([0-9]+)");
          boost::match_results<std::string::const_iterator> what;
          if (regex_search(values.begin(), values.end(), what, extract, boost::match_default))
            if (what.size() >= 1)
              {
                std::stringstream convert;
                convert << what[1];
                convert >> ret[i];
              }
        }
    }
  else
    throw TrantorienFailure("Inventory parse",
                            "Received \"" + values + "\" witch does not match with the regex " + REGEX_VALUE);
  return ret;
}
