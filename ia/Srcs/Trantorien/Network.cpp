// Network.cpp

#include "Network.hh"

#define WELCOME_MSG "BIENVENUE"
#define DEBUG

#include <iostream>

Network::Network(const std::string &ip, const std::string &port)
  : boost::asio::ip::tcp::iostream(ip, port)
{
  if (*this)
    std::cout << "Network: init OK" << std::endl;
  if (!*this || getline() != WELCOME_MSG)
    throw std::runtime_error("Network: failed to init");
}


Network::~Network()
{
  this->close();
}


void Network::cmd(const std::string &command)
{
  if (!*this)
    throw std::runtime_error("Network disconnected");
#ifdef DEBUG
  std::cout << "network out:" << command << std::endl;
#endif
  *this << command << std::endl;
}


std::string Network::getline()
{
  std::string str;

  if (!*this)
    throw std::runtime_error("Network disconnected");
  std::getline(*this, str);
#ifdef DEBUG
  std::cout << "network in: " << str << std::endl;
#endif
  return str;
}
