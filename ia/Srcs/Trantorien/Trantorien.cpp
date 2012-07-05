// Trantorien.cpp

#include "Trantorien.hh"

#include <iostream>
#include <string>

Trantorien::Trantorien(const std::string ip, const std::string port)
  : FSM::VM<Trantorien>(*this, &Trantorien::isValid), network_(ip, port), map_(std::pair<int, int>(10, 10))
{
  std::string tmp;

  if (network_)
    std::cout << "successfully connected" << std::endl;
  else
    {
      //std::cout << network_.error().message() << std::endl;
      abort();
    }
  init("Scripts/conf.le", "Scripts/script.lua");

  addInteraction("IAAvance", &Trantorien::avance);
  addInteraction("IAVoir", &Trantorien::voir);
  addInteraction("IAInventaire", &Trantorien::inventaire);
  addInteraction("IAPrendre", &Trantorien::prendre);
  addInteraction("IATourner", &Trantorien::tourner);
  addInteraction("IAPoser", &Trantorien::poser);
  addInteraction("IACaseContent", &Trantorien::caseContent);
  addInteraction("IACurrentPosition", &Trantorien::currentPosition);
  addInteraction("IAgetInventoyValue", &Trantorien::getInventoryValue);
  addInteraction("IAExpulse", &Trantorien::expulse);
  setValidityTest(&Trantorien::isValid);

  //  getVM().getLua();
  joinTeam("toto");
  network_.getline();
  network_.getline();
}

Trantorien::~Trantorien()
{}

void Trantorien::run()
{
  FSM::VM<Trantorien>::run();
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
  if (ret == "ok")
    map_.avancer();
 return 0;
}

int Trantorien::voir(LuaVirtualMachine::VirtualMachine &vm)
{
  std::string ret;

  network_.cmd("voir");
  ret = network_.getline();
  if (ret != "ko")
    map_.voir(ret);
  map_.test();
  return 0;
}

int Trantorien::inventaire(LuaVirtualMachine::VirtualMachine &vm)
{
  std::string ret;
  unsigned int i;
  lua_State *state = vm.getLua();

  network_.cmd("inventaire");
  ret = network_.getline();
  if (ret != "ko")
    inventory_.update(ret);

  const std::vector<unsigned int> & inventory = inventory_.getIventory();
  for ( i = 0; i < inventory.size(); ++i)
    lua_pushinteger(state, inventory[i]);
  //  lua_pushstring(vm.getLua(), ret.c_str());
  return (i);
}

int Trantorien::prendre(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State               *state = vm.getLua();
  std::list<std::string>  answers;
  int i = 1;

  for (i = 1; i <= lua_gettop(state); ++i)
    {
      if (lua_isstring(state, i))
        {
          std::string object(lua_tostring(state, i));
          network_.cmd("prend " + object);
          std::string result = network_.getline();
          if (result == "ok")
            inventory_.prendre(object);
          answers.push_back(result);
        }
    }
  i = 0;
  while (!answers.empty())
    {
      lua_pushstring(state, answers.front().c_str());
      answers.pop_front();
      ++i;
    }
  return (i);
}

int Trantorien::tourner(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State *state = vm.getLua();
  int i;

  for (i = 1; i <= lua_gettop(state); ++i)
    {
      if (lua_isstring(state, i))
        {
          std::string direction(lua_tostring(state, i));
          network_.cmd(direction);
          std::string result = network_.getline();
          if (result == "ok")
            map_.changeDirection(direction);
        }
    }
  return (0);
}

int Trantorien::poser(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State *state = vm.getLua();
  int i;

  for (i = 1; i <= lua_gettop(state); ++i)
    {
      if (lua_isstring(state, i))
        {
          std::string object(lua_tostring(state, i));

          network_.cmd("pose " + object);
          std::string result = network_.getline();
          if (result == "ok")
            {
              inventory_.poser(object);
              map_.poser(object);
            }
          //lua_pushstring(state, result.c_str());
        }
    }
  return (0);
}

int Trantorien::caseContent(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State *state = vm.getLua();
  unsigned int nbRet = 0;


  if (lua_gettop(state) >= 2 && lua_isnumber(state, 1) && lua_isnumber(state, 2))
    {
      std::pair<int, int> position(lua_tonumber(state, 1), lua_tonumber(state, 2));
      std::vector<unsigned int> result = map_.caseContent(position);
      for (std::vector<unsigned int>::iterator it = result.begin(); it != result.end(); ++it)
	{
	  lua_pushinteger(state, (*it));
	  ++nbRet;
	}
    }
  return (nbRet);
}

int Trantorien::currentPosition(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State *state = vm.getLua();

  std::pair<int, int> position = map_.getCurrentPos();
  lua_pushinteger(state, position.first);
  lua_pushinteger(state, position.second);
  return (2);
}

int Trantorien::getInventoryValue(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State *state = vm.getLua();
  std::vector<unsigned int> inventory = inventory_.getInventory();

  if (lua_gettop(state) == 0)
    {
      for (std::vector<unsigned int>::iterator it = inventory.begin(); it != inventory.end(); ++it)
	{
	  lua_pushinteger(state, (*it));
	  return (inventory.size());
	}
    }
  else
    for (int i = 1; i < lua_gettop(state); ++i)
      {
  	// if (lua_isnumber(state, i))
  	//   {
  	//     lua_tonumber(state, i)
  	//     lua_pushinteger(state, j);
  	//   }
      }
  return (0);
}

int Trantorien::expulse(LuaVirtualMachine::VirtualMachine &vm)
{
  std::string ret;

  network_.cmd("expluse");
  ret = network_.getline();
  lua_pushstring(vm.getLua(), ret.c_str());
  return 1;
}
