// Trantorien.cpp

#include "Trantorien.hh"

#include <iostream>
#include <string>

static const std::string PLAYER_DEAD_STRING = "mort";
static const std::string BROADCAST_TEXT_RCV = "message ";

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
  addInteraction("IAPose", &Trantorien::poser);
  addInteraction("IATourner", &Trantorien::tourner);
  addInteraction("IAElevate", &Trantorien::elevate);

  setValidityTest(&Trantorien::isValid);

  joinTeam("toto");
  this->getline();
  this->getline();
}

Trantorien::~Trantorien()
{}

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

  this->cmd("inventaire");
  ret = this->getline();
  if (ret != "ko")
    inventory_.update(ret);
  lua_pushstring(vm.getLua(), ret.c_str());
  return (1);
}

int Trantorien::prendre(LuaVirtualMachine::VirtualMachine &vm)
{
  return (
        variableArgsCall(vm,
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
        variableArgsCall(vm,
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
  lua_pushstring(vm.getLua(), ret.c_str());
  return 1;
}

int Trantorien::poser(LuaVirtualMachine::VirtualMachine &vm)
{
  return (
        variableArgsCall(vm,
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

int Trantorien::variableArgsCall(LuaVirtualMachine::VirtualMachine &vm,
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
