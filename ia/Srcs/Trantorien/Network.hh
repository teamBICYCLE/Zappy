// Network.hh
#ifndef _NETWORK_HH_
#define _NETWORK_HH_

#include <string>
#include <boost/asio.hpp>

//typedef boost::asio::ip::tcp::iostream Network;

class Network : public boost::asio::ip::tcp::iostream {
public:
  Network(const std::string & ip, const std::string & port);
  ~Network();

  void               cmd(const std::string & command);
  std::string        getline();
};

#endif // _NETWORK_HH_
