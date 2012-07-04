//
// Faillure.cpp for  in /home/carpen_t/projets/c++/iabomber
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Sat May 12 09:41:05 2012 thibault carpentier
// Last update Wed Jul  4 15:20:24 2012 thibault carpentier
//

#include "Failure.hh"

#include <cstring>
#include <iostream>

using namespace LuaVirtualMachine;

Failure::Failure(const std::string& func, const std::string& msg) throw()
  : std::exception(), mFunc(func), mMsg(msg),
    what_("Lua Virutal Machine failure: " + mFunc + " failed - " + mMsg)
{
}

Failure::~Failure() throw()
{}

Failure::Failure(const Failure& other) throw()
  : mFunc(other.getFunc()), mMsg(other.getMsg()), what_(other.what_)
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
  return what_.c_str();
}
