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
#include "Message.hh"

const unsigned int BROADCAST_MAX_SIZE  = 10;

class Trantorien : public FSM::VM<Trantorien> {

public:
  Trantorien(const std::string & ip, const std::string & port,
             char *av[]);
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
  Message               getBroadcastLine();
  int                   listen(LuaVirtualMachine::VirtualMachine &vm, const Message & msg);

private:
  bool                  isValid() const;

  void         droite(void);
  void         gauche(void);
  int          avance(LuaVirtualMachine::VirtualMachine &);
  int          voir(LuaVirtualMachine::VirtualMachine &);
  int	       inventaire(LuaVirtualMachine::VirtualMachine&);
  int	       prendre(LuaVirtualMachine::VirtualMachine &);
  int	       poser(LuaVirtualMachine::VirtualMachine &);
  int	       tourner(LuaVirtualMachine::VirtualMachine &);
  int          elevate(LuaVirtualMachine::VirtualMachine & vm);
  int          broadcast(LuaVirtualMachine::VirtualMachine & vm);
  int	       caseContent(LuaVirtualMachine::VirtualMachine &);
  int	       currentPosition(LuaVirtualMachine::VirtualMachine &);
  int          currentDirection(LuaVirtualMachine::VirtualMachine &vm);
  int	       getInventoryValue(LuaVirtualMachine::VirtualMachine &);
  int	       expulse(LuaVirtualMachine::VirtualMachine &);
  int          goTo(LuaVirtualMachine::VirtualMachine &);
  int	       getLevel(LuaVirtualMachine::VirtualMachine &);
  int	       missingRockOnCase(LuaVirtualMachine::VirtualMachine &);
  int          missingRockInInventoryID(LuaVirtualMachine::VirtualMachine &vm);
  int	       missingRockInInventory(LuaVirtualMachine::VirtualMachine &);
  int	       getClosestItem(LuaVirtualMachine::VirtualMachine &);
  int	       changeFrame(LuaVirtualMachine::VirtualMachine &vm);
  int          missingToElevate(LuaVirtualMachine::VirtualMachine &vm);
  int          LastMsg(LuaVirtualMachine::VirtualMachine &vm);
  int          messageInQueue(LuaVirtualMachine::VirtualMachine &vm);
  int	       canConnectPlayer(LuaVirtualMachine::VirtualMachine &vm);
  int	       connectPlayer(LuaVirtualMachine::VirtualMachine &vm);

private:
  Inventory               inventory_;
  Network                 network_;
  Map                     map_;
  std::list<Message>      broadcastHistory_;
  unsigned int		  level_;
  char			  **av_;
};

#endif // _TRANDORIEN_HH
