//
// Example.cpp for  in /home/carpen_t/tmp/vm
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon Jun  4 15:15:33 2012 thibault carpentier
// Last update Tue Jun  5 18:59:13 2012 thibault carpentier
//

#include <iostream>
#include "Example.hh"

using namespace LuaVirtualMachine;

Example::Example(void)
{
  if (getVM().isFonctionnal())
    initLua();
  else
    return;				// exeption
}

Example::~Example(void)
{}

void	Example::initLua(void)
{
  lua_State *state = getVM().getLua();

  lua_pushinteger(state, EXAMPLE_GLOBALINT);
  lua_setglobal(state, "GLOBALINT");
  lua_pushstring(state, EXAMPLE_GLOBALSTR);
  lua_setglobal(state, "GLOBALSTR");
  lua_pushnumber(state, EXAMPLE_GLOBALNB);
  lua_setglobal(state, "GLOBALNB");

  meth_[registerFct("noRet")] = &Example::noret;
  meth_[registerFct("multipleRet")] = &Example::multipleRet;
}

int Example::scriptCalling(VirtualMachine &vm, int fctNb)
{
  if (meth_.find(fctNb) != meth_.end())
    return ((this->*meth_[fctNb])(vm));
  return (-1);			// normalement impossible mais peut etre une exeption ici
}

// ici pour handle les retours des fonctions des script
void Example::getReturn(VirtualMachine &vm, const std::string &strFunc)
{
  if (vm.isFonctionnal())
    {
      lua_State	*state = vm.getLua();

      if (strFunc == "oneRet")
	{
	  if (lua_gettop(state) == 1 && lua_isnumber(state, 1))
	    std::cout << strFunc << " returned : " <<  (lua_tonumber(state, 1)) << std::endl;
	}
      else if (strFunc == "multRet")
	{
	  std::cout << strFunc << " retuned multiple numbers : " << std::endl;
	  for (int i = 1; i <= lua_gettop(state); ++i)
	    {
	      if (lua_isnumber(state, i))
		std::cout << lua_tonumber(state, i) << std::endl;
	    }
	  std::cout << "end of return " << std::endl;
	}
      return;
    }
}

int Example::noret(VirtualMachine &vm)
{
  (void)vm;
  std::cout << "THIS IS NO RET !" << std::endl;
  return (0);
}

int Example::multipleRet(VirtualMachine &vm)
{
  std::cout << "multiple ret" << std::endl;
  lua_pushnumber(vm.getLua(), 5);
  lua_pushnumber(vm.getLua(), 4);
  return (2);
}
