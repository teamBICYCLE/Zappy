// Network.cpp

#include "Network.hh"

#define WELCOME_MSG "BIENVENUE"
#define DEBUG

#include <iostream>

Network::Network(const std::string &ip, const std::string &port)
  : boost::asio::ip::tcp::iostream(ip, port)
{
  if (!*this || getline() != WELCOME_MSG)
    {
      std::cout << "could not connect" << std::endl;
      throw std::exception();
    }
}


Network::~Network()
{
  this->close();
}


void Network::cmd(const std::string &command)
{
#ifdef DEBUG
  std::cout << "network out:" << command << std::endl;
#endif
  *this << command << std::endl;
}


std::string Network::getline()
{
  std::string str;

  std::getline(*this, str);
#ifdef DEBUG
  std::cout << "network in: " << str << std::endl;
#endif
  return str;
}
