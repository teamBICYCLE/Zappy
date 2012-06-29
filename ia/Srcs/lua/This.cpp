//
// This.cpp for  in /home/jonathan/Projets/iabomber
//
// Made by Jonathan Machado
// Login   <jonathan.machado@epitech.net>
//
// Started on  Sat May  5 16:27:48 2012 Jonathan Machado
// Last update Mon Jun  4 15:45:09 2012 thibault carpentier
//

#include "This.hh"

using namespace LuaVirtualMachine;

This::This(VirtualMachine &vm, int ref)
  : vm_(vm), oldRef_(0)
{
  lua_State *state = vm.getLua();
  if (vm.isFonctionnal())
    {
      lua_getglobal(state, "this");
      oldRef_ = luaL_ref(state, LUA_REGISTRYINDEX);
      lua_rawgeti(state, LUA_REGISTRYINDEX, ref);
      lua_setglobal(state, "this");
    }
}

This::~This(void)
{
  lua_State *state = vm_.getLua();
  if (oldRef_ > 0 && vm_.isFonctionnal())
    {
      lua_rawgeti(state, LUA_REGISTRYINDEX, oldRef_);
      lua_setglobal(state, "this");
      luaL_unref(state, LUA_REGISTRYINDEX, oldRef_);
    }
}
