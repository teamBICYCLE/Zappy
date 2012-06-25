// Trantorien.cpp

#include "Trantorien.hh"

#include <iostream>
#include <string>

Trantorien::Trantorien(const std::string ip, const std::string port)
  : FSM(*this, &Trantorien::isValid), network_(ip, port)
{
  std::string tmp;

  if (network_)
    std::cout << "successfully connected" << std::endl;
  else
    {
      std::cout << network_.error().message() << std::endl;
      abort();
    }
  init("conf.cfg", "script.lua");

  addInteraction("IAAvance", &Trantorien::avance);
  addInteraction("IAVoir", &Trantorien::voir);
  addInteraction("IAInventaire", &Trantorien::inventaire);
  addInteraction("IAPrendre", &Trantorien::prendre);

  setValidityTest(&Trantorien::isValid);

  joinTeam("toto");
  network_.getline();
  network_.getline();
}

Trantorien::~Trantorien()
{
}

void Trantorien::run()
{
  FSM::run();
}

void Trantorien::joinTeam(const std::string &teamName)
{
  network_.cmd(teamName);
}

bool Trantorien::isValid() const
{
  return network_;
}

int Trantorien::avance(LuaVirtualMachine::VirtualMachine &vm)
{
  (void)vm;
  std::string ret;

  network_.cmd("avance");
  ret = network_.getline();
  return 0;
}

int Trantorien::voir(LuaVirtualMachine::VirtualMachine &vm)
{
  (void)vm;
  std::string ret;

  network_.cmd("voir");
  ret = network_.getline();
  if (ret != "ko")
    map_.update(ret);
  return 0;
}

int Trantorien::inventaire(LuaVirtualMachine::VirtualMachine &vm)
{
  std::string ret;

  network_.cmd("inventaire");
  ret = network_.getline();
  if (ret != "ko")
    inventory_.update(ret);
  lua_pushstring(vm.getLua(), ret.c_str());
  return (1);
}

int Trantorien::prendre(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State *state = vm.getLua();
  int i;

  for (i = 1; i <= lua_gettop(state); ++i)
    {
      if (lua_isstring(state, i))
	{
	  std::string object(lua_tostring(state, i));
	  network_.cmd("prend " + object);
	  std::string result = network_.getline();
	  if (result == "ok")
	    inventory_.prendre(object);
	  lua_pushstring(state, result.c_str());
	}
    }
  return (0);
}

int Trantorien::poser(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State *state = vm.getLua();
  int i;

  for (i = 1; i <= lua_gettop(state); ++i)
    {if (lua_isstring(state, i))
        {
          std::string object(lua_tostring(state, i));

          network_.cmd("pose " + object);
          std::string result = network_.getline();
          if (result == "OK")
            inventory_.poser(object);
          //lua_pushstring(state, result.c_str());
        }
    }
  return (0);
}
