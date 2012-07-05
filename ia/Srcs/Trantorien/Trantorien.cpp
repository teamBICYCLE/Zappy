// Trantorien.cpp

#include "Trantorien.hh"

#include <iostream>
#include <string>

static const std::string PLAYER_DEAD_STRING = "mort";
static const std::string BROADCAST_TEXT_RCV = "message ";
static const std::string CURRENTLY_ELEVATE_STR = "elevation en cours";

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
  addInteraction("IAElevate", &Trantorien::elevate);
  addInteraction("IAPoser", &Trantorien::poser);
  addInteraction("IACaseContent", &Trantorien::caseContent);
  addInteraction("IACurrentPosition", &Trantorien::currentPosition);
  addInteraction("IAgetInventoyValue", &Trantorien::getInventoryValue);
  setValidityTest(&Trantorien::isValid);

  //  getVM().getLua();
  joinTeam("toto");
  this->getline();
  this->getline();
}

Trantorien::~Trantorien()
{}

template <>
int Trantorien::variableArgsCall<std::string>(LuaVirtualMachine::VirtualMachine &vm,
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
int Trantorien::variableArgsCall<int>(LuaVirtualMachine::VirtualMachine &vm,
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
        variableArgsCall<std::string>(vm,
                         [&](lua_State * state, const std::string & object) ->
        std::string {
             this->cmd("prend " + object);
             std::string result = this->getline();
             if (result == "ok")
                 inventory_.prendre(object);
           return result;
  }));
}

int Trantorien::tourner(LuaVirtualMachine::VirtualMachine &vm)
{
  return (
        variableArgsCall<std::string>(vm,
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
    ret = this->getline();
  lua_pushstring(vm.getLua(), ret.c_str());
  return 1;
}

int Trantorien::poser(LuaVirtualMachine::VirtualMachine &vm)
{
  return (
        variableArgsCall<std::string>(vm,
                         [&](lua_State * state, const std::string & object) ->
        std::string {
           std::string result;

           this->cmd("pose " + object);
           result = this->getline();
           if (result == "ok")
             {
               inventory_.poser(object);
               map_.poser(object);
             }
           return result;
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
            variableArgsCall<int>(vm,
                             [&](lua_State * state, int object) ->
            int {
            if (object < static_cast<int>(inventory.size()))
              return inventory[object];
            return -1;
      }));
    }
  return (0);
}
