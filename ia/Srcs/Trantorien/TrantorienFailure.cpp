//
// TrantorienTrantorienFailure.cpp for  in /home/carpen_t/projets/syst_Unix/Zappy/ia
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Sat Jun 23 14:35:32 2012 thibault carpentier
// Last update Sat Jun 23 15:38:38 2012 thibault carpentier
//

#include "TrantorienFailure.hh"

TrantorienFailure::TrantorienFailure(const std::string& func, const std::string& msg) throw()
  : std::runtime_error(msg), mFunc_(func), mMsg_(msg)
{}

TrantorienFailure::~TrantorienFailure() throw()
{}

TrantorienFailure::TrantorienFailure(const TrantorienFailure& other) throw()
  : std::runtime_error(other.getMsg()), mFunc_(other.getFunc()), mMsg_(other.getMsg())
{}

TrantorienFailure&   TrantorienFailure::operator=(const TrantorienFailure& other) throw()
{
  if (&other != this)
    {
      mFunc_ = other.getFunc();
      mMsg_ = other.getMsg();
    }
  return (*this);
}

std::string     TrantorienFailure::getFunc(void) const throw()
{
  return (mFunc_);
}

std::string     TrantorienFailure::getMsg(void) const throw()
{
  return (mMsg_);
}

const char      *TrantorienFailure::what(void) const throw()
{
  return (("Trantorien : " + mFunc_ + " failed - " + mMsg_).c_str());
}
