// Trantorien.hh

#ifndef _TRANTORIEN_HH_
#define _TRANTORIEN_HH_

#include "VirtualMachine.hh"
#include "Inventory.hh"
#include "Network.hh"
#include "FSM.hpp"
#include "Script.hh"

class Trantorien : public FSM<Trantorien> {
public:
  Trantorien(const std::string ip, const std::string port);
  virtual ~Trantorien();


  void                  run();

private: // print infos
  void                  dump() const;

private: // server interactions
  void                  joinTeam(const std::string & teamName);

private:
  bool                  isValid() const;

  int          avance(LuaVirtualMachine::VirtualMachine &);
  int          voir(LuaVirtualMachine::VirtualMachine &);
  int	       inventaire(LuaVirtualMachine::VirtualMachine&);
  int	       prendre(LuaVirtualMachine::VirtualMachine &);
  int	       poser(LuaVirtualMachine::VirtualMachine &);
private:
  Inventory     inventory_;
  Network       network_;
};

#endif // _TRANDORIEN_HH_
