// Message.cpp

#include "Message.hh"
#include <utility>
#include <sstream>
#include <boost/regex.hpp>


Message::Message()
  : received_(std::make_pair<int, int>(-1, -1)), from_(std::make_pair<int, int>(-1, -1))
{
}

Message::Message(std::string init, const Position &position, UserGlobal::Direction dir)
  : received_(position), from_(std::make_pair<int, int>(-1, -1))
{
  boost::regex  regex("message ([0-9]), (.*)");
  boost::match_results<std::string::iterator>  what;

  if (boost::regex_search(init.begin(), init.end(), what, regex,
                          boost::regex_constants::match_default))
    {
      std::stringstream  ss(what[1]);
      unsigned int       from;

      ss >> from;
      message_ = what[2];
      from_ = received_;
      if (from != 0)
        {
          --from;
          from = (from + (2 * (dir - 1))) % 8;
          if (from == 7 || from == 0 || from == 1)
            from_.second -= 1;
          if (from == 1 || from == 2 || from == 3)
            from_.first -= 1;
          if (from == 3 || from == 4 || from == 5)
            from_.second += 1;
          if (from == 5 || from == 6 || from == 7)
            from_.first += 1;
        }
    }
}

Message::~Message()
{
}

Message::Message(const Message &orig)
  : received_(orig.received_), from_(orig.from_), message_(orig.message_)
{
}

Message &Message::operator =(const Message &orig)
{
  if (this != &orig)
    {
      received_ = orig.received_;
      from_ = orig.from_;
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

const Position &Message::getFrom() const
{
  return from_;
}
