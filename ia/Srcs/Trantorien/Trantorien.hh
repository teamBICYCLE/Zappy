//
// Trantorien.hh for  in /home/carpen_t/projets/syst_Unix/Zappy/ia
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Fri Jul 13 11:39:37 2012 thibault carpentier
// Last update Sat Jul 14 15:01:14 2012 thibault carpentier
//

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

const unsigned int BROADCAST_MAX_SIZE  = 1000;

class Trantorien : public FSM::VM<Trantorien> {

public:
  Trantorien(const std::string & ip, const std::string & port,
             const std::string & lefile, const std::string & luafile,
             const std::string & team, char *av[]);
  virtual ~Trantorien();

  void                  run();

private:
  template <typename X, typename Y>
  int          variableArgsCall(LuaVirtualMachine::VirtualMachine & vm,
                                std::function<Y(lua_State *,
                                                          const X &)> fct);
  void                  dump() const;

  void                  joinTeam(const std::string & teamName);
  void                  cmd(const std::string & command);
  std::string           getline();
  Message               getBroadcastLine();
  int                   listen(LuaVirtualMachine::VirtualMachine &vm, const Message & msg);

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
  int	       getItemWithLength(LuaVirtualMachine::VirtualMachine &vm);
  int	       changeFrame(LuaVirtualMachine::VirtualMachine &vm);
  int          missingToElevate(LuaVirtualMachine::VirtualMachine &vm);
  int          LastMsg(LuaVirtualMachine::VirtualMachine &vm);
  int          messageInQueue(LuaVirtualMachine::VirtualMachine &vm);
  int          readLine(LuaVirtualMachine::VirtualMachine &vm);
  int	       canConnectPlayer(LuaVirtualMachine::VirtualMachine &vm);
  int	       connectPlayer(LuaVirtualMachine::VirtualMachine &vm);
  int	       lay(LuaVirtualMachine::VirtualMachine &vm);
  int	       nbMessageInQueue(LuaVirtualMachine::VirtualMachine &vm);
  int	       nbMessageInQueue(const std::string &);
  int	       countPlayer(LuaVirtualMachine::VirtualMachine &vm);

  Inventory               inventory_;
  Network                 network_;
  Map                     map_;
  std::list<Message>      broadcastHistory_;
  unsigned int		  level_;
  char			  **av_;
  std::string             teamname;
  int                     playerNumber;
};

#endif // _TRANDORIEN_HH
