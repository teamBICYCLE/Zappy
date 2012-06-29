//
// Debugger.cpp for  in /home/carpen_t/projets/c++/iabomber
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Fri May  4 18:42:11 2012 thibault carpentier
// Last update Thu Jun  7 11:59:44 2012 thibault carpentier
//

#include <cstring>
#include <cstdio>
#include <iostream>
#include "VirtualMachine.hh"

using namespace LuaVirtualMachine;

std::map<int, fctHook> g_hookers;

void HookCall(lua_State *lua)
{
  lua_Debug ar;

  memset(&ar, 0, sizeof(ar));
  std::cout << "LUA CALL HOOKER ---- Call stack :" << std::endl;
  std::cout << "Level namewhat name nups linedefined short_src" << std::endl;
  for (int i = 0; lua_getstack(lua, i, &ar); ++i)
    {
      if (lua_getinfo(lua, "Snlu", &ar))
	std::cout << i << " "
		  <<  (ar.namewhat  == NULL ? "null" : ar.namewhat) << " "
		  << (ar.name == NULL ? "null" : ar.name) << " "
		  << ar.nups  << " " << ar.linedefined << " "
		  << (ar.short_src == NULL ? "null" : ar.short_src) << std::endl;
      memset(&ar, 0, sizeof(ar));
    }
}

void HookRet(lua_State *lua)
{
  lua_Debug ar;

  memset(&ar, 0, sizeof(ar));
  std::cout << "LUA RET HOOKER -----" << std::endl;
  for (int i = 0; lua_getstack(lua, i, &ar); ++i)
    {
      if (lua_getinfo(lua, "nSlu", &ar))
	std::cout << i << " "
		  <<  (ar.namewhat  == NULL ? "null" : ar.namewhat) << " "
		  << (ar.name == NULL ? "null" : ar.name) << " "
		  << ar.nups  << " " << ar.linedefined << " "
		  << (ar.short_src == NULL ? "null" : ar.short_src) << std::endl;
      memset(&ar, 0, sizeof(ar));
    }
}

static void HookLine(lua_State *lua)
{
  lua_Debug ar;

  memset(&ar, 0, sizeof(ar));
  std::cout << "LUA LINE HOOKER -----" << std::endl;
  if (lua_getinfo(lua, "Sl", &ar))
    std::cout << "currently at line " << ar.currentline << "@"
	      << (ar.source == NULL ? "null" : ar.source) << std::endl;

}

static void HookCount(lua_State *lua)
{
  std::cout << "LUA COUNT HOOKER --- (Calling Lua line hooker)"  << std::endl;
  HookLine(lua);
}


static void HookEvents(lua_State *lua, lua_Debug *debug)
{
  if (debug && g_hookers.find(debug->event) != g_hookers.end() && lua)
    g_hookers[debug->event](lua);
}


VirtualMachine::Debugger::Debugger(VirtualMachine &vm)
  : VM_(vm)
{
  setFctHook();
  if (vm.isFonctionnal())
    {
      vm.addDebugger(this);
      lua_sethook(vm.getLua(), HookEvents, 0, 0);
    }
}

void VirtualMachine::Debugger::setFctHook(void)
{
  g_hookers[LUA_HOOKCALL] = HookCall;
  g_hookers[LUA_HOOKRET] = HookRet;
  g_hookers[LUA_HOOKTAILRET] = HookRet;
  g_hookers[LUA_HOOKLINE] = HookLine;
  g_hookers[LUA_HOOKCOUNT] = HookCount;
}

VirtualMachine::Debugger::~Debugger(void)
{
  if (VM_.isFonctionnal())
    lua_sethook(VM_.getLua(), HookEvents, 0, 0);
}

int	VirtualMachine::Debugger::setHook(lua_State *lua)
{
  VirtualMachine	*VM;

  VM = VirtualMachine::getVm();
  if (VM->isFonctionnal())
    if (lua_gettop(lua) == 2 && lua_isnumber(lua, 1)
	&& lua_isnumber(lua, 2))
      lua_sethook(VM->getLua(), HookEvents, lua_tonumber(lua, 1), lua_tonumber(lua, 2));
  return 0;
}

