//
// Trantorien.hh for  in /home/carpen_t/projets/syst_Unix/Zappy/ia
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Fri Jul 13 11:39:37 2012 thibault carpentier
// Last update Fri Jul 13 16:31:14 2012 thibault carpentier
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


/*! \mainpage Classe API Lua-C++ Documentation
 *
 * \section intro_sec Introduction
 *
 * This documentation will help non-developpers or developpers to implements new Artificial Intelligence
 * on the Zappy.
 *
 * \section install_sec Mini tutorial :
 * Launch galaxy and draw your finite State Machine with the soft. Once done, generate the conf file and export it on light Esterel format (.le) <br/> Done forget that the first state drawed is the first state called.
<br/> Once done, open a lua file and develop function for each state in lua. this:nodename(this). Once done, launch and Enjoy !
 *
 * \subsection running Running the program
 *
 * \section copyright Copyright and License
 *
 *  Copyright 2012, all rights reserved, TeamBicycle.
 *
 * <BR><BR>
 *
 */


const unsigned int BROADCAST_MAX_SIZE  = 1000;

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
private:
  Inventory               inventory_;
  Network                 network_;
  Map                     map_;
  std::list<Message>      broadcastHistory_;
  unsigned int		  level_;
  char			  **av_;
};

#endif // _TRANDORIEN_HH
