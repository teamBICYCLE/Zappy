// Trantorien.cpp

#include "Trantorien.hh"

#include <iostream>

Trantorien::Trantorien(const std::string ip, const std::string port)
  : FSM(*this, &Trantorien::isValid), network_(ip, port)
{
  std::string tmp;

  if (network_)
    std::cout << "successfully connected" << std::endl;
  else
    {
      // std::cout << network_.error().message() << std::endl;
      abort();
    }
  init("conf.cfg", "script.lua");
  addInteraction("avance", &Trantorien::avance);
  addInteraction("voir", &Trantorien::voir);
  setValidityTest(&Trantorien::isValid);

  joinTeam("toto");
  network_.getline();
  network_.getline();
}

Trantorien::~Trantorien()
{
}

void Trantorien::run()
{
  FSM::run();
}

void Trantorien::joinTeam(const std::string &teamName)
{
  network_.cmd(teamName);
}

bool Trantorien::isValid() const
{
  return network_;
}

int Trantorien::avance()
{
  std::string ret;

  network_.cmd("avance");
  ret = network_.getline();
  return 0;
}


int Trantorien::voir()
{
  std::string ret;

  network_.cmd("voir");
  ret = network_.getline();
  return 0;
}
