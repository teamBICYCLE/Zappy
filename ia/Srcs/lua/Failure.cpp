//
// Faillure.cpp for  in /home/carpen_t/projets/c++/iabomber
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Sat May 12 09:41:05 2012 thibault carpentier
// Last update Mon Jun  4 17:59:32 2012 thibault carpentier
//

#include "Failure.hh"

using namespace LuaVirtualMachine;

Failure::Failure(const std::string& func, const std::string& msg) throw()
  : std::runtime_error(msg), mFunc(func), mMsg(msg)
{}

Failure::~Failure() throw()
{}

Failure::Failure(const Failure& other) throw()
  : std::runtime_error(other.getMsg()), mFunc(other.getFunc()), mMsg(other.getMsg())
{}

Failure&   Failure::operator=(const Failure& other) throw()
{
  if (&other != this)
    {
      mFunc = other.getFunc();
      mMsg = other.getMsg();
    }
  return (*this);
}

std::string     Failure::getFunc(void) const throw()
{
  return (mFunc);
}

std::string     Failure::getMsg(void) const throw()
{
  return (mMsg);
}

const char      *Failure::what(void) const throw()
{
  return (("Lua Virutal Machine failure: " + mFunc + " failed - " + mMsg).c_str());
}
