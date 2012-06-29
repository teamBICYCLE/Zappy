//
// Script.cpp for  in /home/carpen_t/projets/c++/iabomber
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Sat May  5 11:46:41 2012 thibault carpentier
// Last update Thu Jun  7 16:21:30 2012 thibault carpentier
//

#include <iostream>
#include <stdexcept>
#include "Script.hh"
#include "RestoreStack.hh"
#include "This.hh"
#include "VirtualMachine.hh"
#include "Failure.hh"

using namespace LuaVirtualMachine;

static int luaCallMeth(lua_State *lua)
{
  int nbRet = 0;
  int idx = lua_upvalueindex(1);
  bool success = false;

  if (lua_istable(lua, 1))
    {
      lua_rawgeti(lua, 1, 0);
      if (lua_islightuserdata(lua, -1))
	{
	  Script *script = static_cast<Script *>(lua_touserdata(lua, -1));
	  int methIdx = lua_tonumber(lua, idx);
	  if (script && methIdx <= script->getNbMeth())
	    {
	      lua_remove(lua, 1);
	      lua_remove(lua, -1);
	      nbRet = script->scriptCalling(script->getVM(), methIdx);
	      success = true;
	    }
	}
    }
  if (success == false)
    {
      lua_pushstring(lua, "LuaCallback -> Failed to call the class function");
      lua_error(lua);
    }
  return nbRet;
}

Script::Script(void)
  : VM_(*(VirtualMachine::getVm())), refThis_(0), nbArgs_(0), nbMethod_(0)
{
  if (VM_.isFonctionnal())
    {
      lua_newtable(VM_.getLua());
      refThis_ = luaL_ref(VM_.getLua(), LUA_REGISTRYINDEX);
      RestoreStack restore(VM_);

      lua_rawgeti(VM_.getLua(), LUA_REGISTRYINDEX, refThis_);
      lua_pushlightuserdata(VM_.getLua(), this);
      lua_rawseti(VM_.getLua(), -2, 0);
    }
}

Script::~Script(void)
{
  RestoreStack rs(VM_);

  if (VM_.isFonctionnal())
    {
      lua_rawgeti(VM_.getLua(), LUA_REGISTRYINDEX, refThis_);
      lua_pushnil(VM_.getLua());
      lua_rawseti(VM_.getLua(), -2, 0);
    }
}

int  Script::getNbMeth(void) const
{
  return (nbMethod_);
}

VirtualMachine &Script::getVM(void) const
{
  return (VM_);
}

void Script::addParam(int param)
{
  if (VM_.isFonctionnal())
    {
      lua_pushnumber(VM_.getLua(), param);
      ++nbArgs_;
    }
}

void Script::addParam(double param)
{
  if (VM_.isFonctionnal())
    {
      lua_pushnumber(VM_.getLua(), param);
      ++nbArgs_;
    }
}


void Script::addParam(const std::string &param)
{
  if (VM_.isFonctionnal())
    {
      lua_pushstring(VM_.getLua(), param.c_str());
      ++nbArgs_;
    }
}

void Script::addParam(float param)
{
  if (VM_.isFonctionnal())
    {
      lua_pushnumber(VM_.getLua(), param);
      ++nbArgs_;
    }
}

bool Script::compileFile(const std::string &filename)
{
  bool fSuccess = false;

  if (!VM_.isFonctionnal())
    return false;
  This luaThis(VM_, refThis_);
  if (luaL_loadfile(VM_.getLua(), filename.c_str()) == 0)
    if (lua_pcall(VM_.getLua(), 0, LUA_MULTRET, 0) == 0)
      fSuccess = true;
  if (!fSuccess)
    throw Failure("compileFile", "Error on compileFile");
  return fSuccess;
}

bool Script::selectFct(const std::string &fctName)
{
  bool success = false;

  if (VM_.isFonctionnal())
    {
      lua_rawgeti(VM_.getLua(), LUA_REGISTRYINDEX, refThis_);
      lua_pushstring(VM_.getLua(), fctName.c_str());
      lua_rawget(VM_.getLua(), -2);
      lua_remove(VM_.getLua(), -2);
      lua_rawgeti(VM_.getLua(), LUA_REGISTRYINDEX, refThis_);
      if (!lua_isfunction(VM_.getLua(), -2))
	lua_pop(VM_.getLua(), 2);
      else
	{
	  nbArgs_ = 0;
	  fctName_ = fctName;
	  success = true;
	}
    }
  return (success);
}


bool Script::callFct(int nbRet)
{
  if (VM_.isFonctionnal())
    {
      if (lua_isfunction(VM_.getLua(), (-1 * (nbArgs_ + 1) - 1)))
	{
	  if (lua_pcall(VM_.getLua(), nbArgs_ + 1, nbRet, 0))
	    throw Failure(lua_tostring(VM_.getLua(), -1), "Error, on lua_pcall");
	  getReturn(VM_, fctName_);
	  lua_pop(VM_.getLua(), nbRet);
	  return (true);
	}
    }
  return (false);
}

bool Script::fctExist(const std::string &filename)
{
  if (VM_.isFonctionnal())
    {
      RestoreStack restore(VM_);
      lua_rawgeti(VM_.getLua(), LUA_REGISTRYINDEX, refThis_);
      lua_pushstring(VM_.getLua(), filename.c_str());
      lua_rawget(VM_.getLua(), -2);
      lua_remove(VM_.getLua(), -2);
      if (lua_isfunction(VM_.getLua(), -1))
	return (true);
    }
  return (false);
}

int  Script::registerFct(const std::string &fctName)
{
  int methIdx = -1;
  RestoreStack rs(VM_);

  if (VM_.isFonctionnal())
    {
      methIdx = ++nbMethod_;
      lua_rawgeti(VM_.getLua(), LUA_REGISTRYINDEX, refThis_);
      lua_pushstring(VM_.getLua(), fctName.c_str());
      lua_pushnumber(VM_.getLua(), methIdx);
      lua_pushcclosure(VM_.getLua(), luaCallMeth, 1);
      lua_settable(VM_.getLua(), -3);
    }
  return (methIdx);
}

