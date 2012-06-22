// Trantorien.cpp

#include "Trantorien.hh"

#include <iostream>

Trantorien::Trantorien(const std::string ip, const std::string port)
  : FSM(), network_(ip, port)
{
  std::string tmp;

  if (network_)
    std::cout << "successfully connected" << std::endl;
  else
    {
      // std::cout << network_.error().message() << std::endl;
      abort();
    }
  states_.push_back(&Trantorien::avance);
  states_.push_back(&Trantorien::voir);
  setValidityTest(&Trantorien::isValid);

  // implementer dans la classe reseau
  std::getline(network_, tmp);
  std::cout << "1: " << tmp << std::endl;
  network_ << "toto" << std::endl;
  std::getline(network_, tmp);
  std::cout << "2: " << tmp << std::endl;
  std::getline(network_, tmp);
  std::cout << "3: " << tmp << std::endl;
  std::cout << "Coucou Abort();" << std::endl;
}

Trantorien::~Trantorien()
{
}

void Trantorien::run()
{
  FSM::run(*this);
}

bool Trantorien::isValid() const
{
  return network_;
}

FSMRetValue Trantorien::avance()
{
  std::string ret;

  network_ << "avance" << std::endl;
  std::getline(network_, ret);
  std::cout << "result avance: " << ret << std::endl;
  return OK;
}


FSMRetValue Trantorien::voir()
{
  std::string ret;

  network_ << "voir" << std::endl;
  std::getline(network_, ret);
  std::cout << "result voir: " << ret << std::endl;
  return OK;
}
