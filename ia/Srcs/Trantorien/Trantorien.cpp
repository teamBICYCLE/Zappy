// Trantorien.cpp

#include "Trantorien.hh"

#include <iostream>
#include <string>

static const std::string PLAYER_DEAD_STRING = "mort";
static const std::string BROADCAST_TEXT_RCV = "message ";
static const std::string CURRENTLY_ELEVATE_STR = "elevation en cours";

Trantorien::Trantorien(const std::string ip, const std::string port)
  : FSM::VM<Trantorien>(*this, &Trantorien::isValid), network_(ip, port), map_(std::pair<int, int>(20, 20)), level_(1)
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
  addInteraction("IAElevate", &Trantorien::elevate);
  addInteraction("IAPoser", &Trantorien::poser);
  addInteraction("IACaseContent", &Trantorien::caseContent);
  addInteraction("IACurrentPosition", &Trantorien::currentPosition);
  addInteraction("IAgetInventoyValue", &Trantorien::getInventoryValue);
  addInteraction("IAExpulse", &Trantorien::expulse);
  addInteraction("IAGetLevel", &Trantorien::getLevel);
  addInteraction("IAMissingRockOnCase", &Trantorien::missingRockOnCase);
  addInteraction("IAMissingRockInInventory", &Trantorien::missingRockInInventory);
  addInteraction("IAGetCLosestItem", &Trantorien::getClosestItem);
  setValidityTest(&Trantorien::isValid);

  lua_State *state = getVM().getLua();
  lua_pushinteger(state, NORD);
  lua_setglobal(state, "NORD");
  lua_pushinteger(state, EST);
  lua_setglobal(state, "EST");
  lua_pushinteger(state, SUD);
  lua_setglobal(state, "SUD");
  lua_pushinteger(state, OUEST);
  lua_setglobal(state, "OUEST");

  lua_pushinteger(state, NOURRITURE);
  lua_setglobal(state, "NOURRITURE");
  lua_pushinteger(state, LINEMATE);
  lua_setglobal(state, "LINEMATE");
  lua_pushinteger(state, DERAUMERE);
  lua_setglobal(state, "DERAUMERE");
  lua_pushinteger(state, SIBUR);
  lua_setglobal(state, "SIBUR");
  lua_pushinteger(state, MENDIANE);
  lua_setglobal(state, "MENDIANE");
  lua_pushinteger(state, PHIRAS);
  lua_setglobal(state, "PHIRAS");
  lua_pushinteger(state, THYSTAME);
  lua_setglobal(state, "THYSTAME");

  joinTeam("toto");
  this->getline();
  this->getline();
}

Trantorien::~Trantorien()
{}

template <>
int Trantorien::variableArgsCall<std::string, std::string>(LuaVirtualMachine::VirtualMachine &vm,
                                 std::function<std::string(lua_State *,
                                                           const std::string &)> fct)
{
  lua_State               *state = vm.getLua();
  std::list<std::string>  answers;
  int i = 1;

  for (i = 1; i <= lua_gettop(state); ++i)
    {
      if (lua_isstring(state, i))
        {
          std::string result = fct(state, lua_tostring(state, i));
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

template <>
int  Trantorien::variableArgsCall<int, std::string>(LuaVirtualMachine::VirtualMachine &vm,
                                 std::function<std::string(lua_State *,
                                                           const int &)> fct)
{
  lua_State               *state = vm.getLua();
  std::list<std::string>  answers;
  int i = 1;

  for (i = 1; i <= lua_gettop(state); ++i)
    {
      if (lua_isnumber(state, i))
        {
          std::string result = fct(state, lua_tointeger(state, i));
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


template <>
int Trantorien::variableArgsCall<int, int>(LuaVirtualMachine::VirtualMachine &vm,
                                 std::function<int(lua_State *,
                                                   const int &)> fct)
{
  lua_State               *state = vm.getLua();
  std::list<int>          answers;
  int i = 1;

  for (i = 1; i <= lua_gettop(state); ++i)
    {
      if (lua_isnumber(state, i))
        {
          int result = fct(state, lua_tonumber(state, i));
          answers.push_back(result);
        }
    }
  i = 0;
  while (!answers.empty())
    {
      lua_pushnumber(state, answers.front());
      answers.pop_front();
      ++i;
    }
  return (i);
}

void Trantorien::run()
{
  FSM::VM<Trantorien>::run();
}

void Trantorien::joinTeam(const std::string &teamName)
{
  this->cmd(teamName);
}

void Trantorien::cmd(const std::string &command)
{
  network_.cmd(command);
}

std::string Trantorien::getline()
{
  std::string     line = network_.getline();

  if (line == PLAYER_DEAD_STRING)
    {
      abort();
    }
  else if (!line.compare(0, BROADCAST_TEXT_RCV.length(), BROADCAST_TEXT_RCV))
    {
      std::cout << "received broadcast: " << line << std::endl;
      broadcastHistory_.push_back(line);
      line = this->getline();
    }
  return line;
}

std::string Trantorien::getBroadcastLine()
{
  std::string line;

  if (!broadcastHistory_.empty())
    {
      line = broadcastHistory_.front();
      broadcastHistory_.pop_front();
      return line;
    }
  else
    return "";
}

bool Trantorien::isValid() const
{
  return network_;
}

int Trantorien::avance(LuaVirtualMachine::VirtualMachine &vm)
{
  std::string ret;

  this->cmd("avance");
  ret = this->getline();
  if (ret == "ok")
    map_.avancer();
  lua_pushstring(vm.getLua(), ret.c_str());
 return 1;
}

int Trantorien::voir(LuaVirtualMachine::VirtualMachine &vm)
{
  std::string ret;

  this->cmd("voir");
  ret = this->getline();
  if (ret != "ko")
    map_.voir(ret);
  map_.test();
  lua_pushstring(vm.getLua(), ret.c_str());
  return 1;
}

int Trantorien::inventaire(LuaVirtualMachine::VirtualMachine &vm)
{
  std::string ret;
  unsigned int i;
  lua_State *state = vm.getLua();

  this->cmd("inventaire");
  ret = this->getline();
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
  return (
	  variableArgsCall<int ,std::string>(vm,
					     [&](lua_State * state, const int & object) ->
					     std::string {
					       if (object < THYSTAME)
						 {
						   this->cmd("prend " + g_values[object]);
						   std::string result = this->getline();
						   if (result == "ok")
						     inventory_.prendre(g_values[object]);
						   return result;
						 }
					       return ("ko");
					     }));
}

int Trantorien::tourner(LuaVirtualMachine::VirtualMachine &vm)
{
  return (
        variableArgsCall<std::string, std::string>(vm,
                         [&](lua_State * state, const std::string & direction) ->
        std::string {
           this->cmd(direction);
           std::string result = this->getline();
           if (result == "ok")
              map_.changeDirection(direction);
           return result;
}));
}

int Trantorien::elevate(LuaVirtualMachine::VirtualMachine &vm)
{
  this->cmd("incantation");
  std::string ret = this->getline();
  if (ret == CURRENTLY_ELEVATE_STR)
    if ((ret = this->getline()) != "ko")
      ++level_;
  lua_pushstring(vm.getLua(), ret.c_str());
  return 1;
}

int Trantorien::poser(LuaVirtualMachine::VirtualMachine &vm)
{
  return (
	  variableArgsCall<int ,std::string>(vm,
					     [&](lua_State * state, const int & object) ->
					     std::string {
					       if (object < THYSTAME)
						 {
						   this->cmd("pose " + g_values[object]);
						   std::string result = this->getline();
						   if (result == "ok")
						     inventory_.prendre(g_values[object]);
						   return result;
						 }
					       return ("ko");
					     }));
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
        }
      return (inventory.size());
    }
  else
    {
      return (
            variableArgsCall<int, int>(vm,
                             [&](lua_State * state, int object) ->
            int {
            if (object < static_cast<int>(inventory.size()))
              return inventory[object];
            return -1;
      }));
    }
  return (0);
}

int Trantorien::expulse(LuaVirtualMachine::VirtualMachine &vm)
{
  std::string ret;

  network_.cmd("expluse");
  ret = this->getline();
  lua_pushstring(vm.getLua(), ret.c_str());
  return 1;
}

int Trantorien::getLevel(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_pushnumber(vm.getLua(), level_);
  return (1);
}

int Trantorien::missingRockOnCase(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State *state = vm.getLua();

  std::pair<int, int> position = map_.getCurrentPos();
  std::vector<unsigned int> result = map_.caseContent(position);

  int j = 0;
  for (std::vector<unsigned int>::iterator it = result.begin(); it != result.end(); ++it)
    {
      lua_pushinteger(state, g_levels[level_ - 1][j] - (*it));
      ++j;
    }
  return (j);
}

int Trantorien::missingRockInInventory(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State *state = vm.getLua();
  std::vector<unsigned int> result = inventory_.getIventory();

  int j = 0;
  for (std::vector<unsigned int>::iterator it = result.begin(); it != result.end(); ++it)
    {
      lua_pushinteger(state, g_levels[level_ - 1][j] - (*it));
      ++j;
    }
  return (j);
}

int Trantorien::getClosestItem(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State *state = vm.getLua();
  std::pair<int, int> position = map_.getCurrentPos();

  //  map_.seekClosest(position)
  return (0);
}
