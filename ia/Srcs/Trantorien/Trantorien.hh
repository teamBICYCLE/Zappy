// Trantorien.hh

#ifndef _TRANTORIEN_HH_
#define _TRANTORIEN_HH_

#include <string>
#include <list>
#include <functional>
#include "FSM/VM.hpp"
#include "Inventory.hh"
#include "Network.hh"
#include "Map.hh"
#include "Ressources.hh"

class Trantorien : public FSM::VM<Trantorien> {

public:
  Trantorien(const std::string ip, const std::string port);
  virtual ~Trantorien();


  void                  run();

private: // print infos
  template <typename X, typename Y>
  int          variableArgsCall(LuaVirtualMachine::VirtualMachine & vm,
                                std::function<Y(lua_State *,
                                                          const X &)> fct);
  void                  dump() const;

private: // server interactions
  void                  joinTeam(const std::string & teamName);
  void                  cmd(const std::string & command);
  std::string           getline();
  std::string           getBroadcastLine();

private:
  bool                  isValid() const;

  int          avance(LuaVirtualMachine::VirtualMachine &);
  int          voir(LuaVirtualMachine::VirtualMachine &);
  int	       inventaire(LuaVirtualMachine::VirtualMachine&);
  int	       prendre(LuaVirtualMachine::VirtualMachine &);
  int	       poser(LuaVirtualMachine::VirtualMachine &);
  int	       tourner(LuaVirtualMachine::VirtualMachine &);
  int          elevate(LuaVirtualMachine::VirtualMachine & vm);
  int	       caseContent(LuaVirtualMachine::VirtualMachine &);
  int	       currentPosition(LuaVirtualMachine::VirtualMachine &);
  int	       getInventoryValue(LuaVirtualMachine::VirtualMachine &);
  int	       expulse(LuaVirtualMachine::VirtualMachine &);
  int	       getLevel(LuaVirtualMachine::VirtualMachine &);

private:
  Inventory               inventory_;
  Network                 network_;
  Map                     map_;
  std::list<std::string>  broadcastHistory_;
  unsigned int		  level_;
};

#endif // _TRANDORIEN_HH_
