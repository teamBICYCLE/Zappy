//
// VirtualMachine.cpp for  in /home/carpen_t/projets/c++/iabomber
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Fri May  4 14:47:22 2012 thibault carpentier
// Last update Thu Jun  7 10:22:53 2012 thibault carpentier
//

#include <iostream>
#include <cstring>
#include <cassert>
#include <stdexcept>
#include "VirtualMachine.hh"
#include "Failure.hh"

using namespace LuaVirtualMachine;

VirtualMachine *VirtualMachine::single_ = NULL;

VirtualMachine *VirtualMachine::getVm(void)
{
  if (single_ ==  NULL)
    single_ = new VirtualMachine;
  return single_;
}

int VirtualMachine::printDebug(lua_State *state)
{
  lua_Debug debug;

  memset(&debug, '\0', sizeof(debug));
  lua_getstack(state, 1, &debug);
  lua_getinfo(state, "Snl", &debug);
  if (lua_gettop(state) == 1 && lua_isstring(state, 1))
    std::cout << "Debug lua script : |"<< lua_tostring(state, 1) << "| -- at file: "
	      << debug.source << " on line (" << debug.currentline << ")."
	      << std::endl;
  else
    throw Failure("Print Debug", "Invalid parameter (Not a string).");
  return (0);
}

int VirtualMachine::panic(lua_State *state)
{
  (void)state;
  throw Failure("Lua Panic", "Lua thow a panic exeption.");
  return (0);
}

VirtualMachine::VirtualMachine(void)
  : vmState_(NULL), isOk_(false), debug_(NULL)
{
  initVm();
}

VirtualMachine::~VirtualMachine(void)
{
  destroyVm();
}

bool VirtualMachine::initVm(void)
{
  vmState_ = lua_open();
  if (vmState_)
    {
      isOk_ = true;
      luaL_openlibs(vmState_);
      lua_atpanic(vmState_, VirtualMachine::panic);
      lua_pushcclosure(vmState_, printDebug, 0);
      lua_setglobal(vmState_, "printDebug");
      lua_pushcclosure(vmState_, Debugger::setHook, 0);
      lua_setglobal(vmState_, "setHook");
      lua_pushinteger(vmState_, LUA_MASKCOUNT);
      lua_setglobal(vmState_, "MASKCOUNT");
      lua_pushinteger(vmState_, LUA_MASKLINE);
      lua_setglobal(vmState_, "MASKLINE");
      lua_pushinteger(vmState_, LUA_MASKRET);
      lua_setglobal(vmState_, "MASKRET");
      lua_pushinteger(vmState_, LUA_MASKCALL);
      lua_setglobal(vmState_, "MASKCALL");
      addDebugger(new Debugger(*this));
      return (true);
    }
  throw Failure("Init VM", "Error on lua_open.");
  return (false);
}

bool VirtualMachine::destroyVm(void)
{
  if (vmState_)
    {
      if (debug_)
	delete debug_;
      lua_close(vmState_);
      vmState_ = NULL;
      isOk_ = false;
      return (true);
    }
  return (false);
}

bool VirtualMachine::isFonctionnal(void) const
{
  return (isOk_);
}

VirtualMachine::Debugger *VirtualMachine::getDebug(void) const
{
  return (debug_);
}

void VirtualMachine::addDebugger(Debugger *debug)
{
  debug_ = debug;
}

lua_State *VirtualMachine::getLua(void) const
{
  return (vmState_);
}
