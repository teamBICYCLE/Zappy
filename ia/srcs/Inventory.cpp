// Inventory.cpp

#include "Inventory.hh"

#include <iostream>

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
  std::vector<unsigned int> ret;

  return ret;
}
