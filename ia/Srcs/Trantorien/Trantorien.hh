// Trantorien.hh

#ifndef _TRANTORIEN_HH_
#define _TRANTORIEN_HH_

#include "FSM/VM.hpp"
#include "Inventory.hh"
#include "Network.hh"
#include "Map.hh"

class Trantorien : public FSM::VM<Trantorien> {
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
  int	       tourner(LuaVirtualMachine::VirtualMachine &);

private:
  Inventory     inventory_;
  Network       network_;
  Map		map_;
};

#endif // _TRANDORIEN_HH_
