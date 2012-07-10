// Message.cpp

#include "Message.hh"
#include <utility>
#include <sstream>
#include <boost/regex.hpp>


Message::Message()
  : received_(std::make_pair<int, int>(-1, -1)), dir_(4, false)
{
}

Message::Message(std::string init, const Position &position, UserGlobal::Direction dir,
                 const Position & mapSize)
  : received_(position), dir_(4, false)
{
  boost::regex  regex("message ([0-9]), *(.*)");
  boost::match_results<std::string::iterator>  what;

  if (boost::regex_search(init.begin(), init.end(), what, regex,
                          boost::regex_constants::match_default))
    {
      std::stringstream  ss(what[1]);
      unsigned int       from;
      Position            from_;

      ss >> from;
      message_ = what[2];
      from_ = received_;

      if (from != 0)
        {
          --from;
          from = (from + (2 * (dir - 1))) % 8;
          if (from == 7 || from == 0 || from == 1)
            dir_[UserGlobal::NORD - 1] = true;
          if (from == 1 || from == 2 || from == 3)
            dir_[UserGlobal::EST - 1] = true;
          if (from == 3 || from == 4 || from == 5)
            dir_[UserGlobal::SUD - 1] = true;
          if (from == 5 || from == 6 || from == 7)
            dir_[UserGlobal::OUEST - 1] = true;
        }
    }
}

Message::~Message()
{
}

Message::Message(const Message &orig)
  : received_(orig.received_), dir_(orig.dir_), message_(orig.message_)
{
}

Message &Message::operator =(const Message &orig)
{
  if (this != &orig)
    {
      received_ = orig.received_;
      dir_ = orig.dir_;
      message_ = orig.message_;
    }
  return *this;
}


const std::string &Message::getMessage() const
{
  return message_;
}


const Position &Message::getReceived() const
{
  return received_;
}

const std::vector<bool> &Message::getDir() const
{
  return dir_;
}


