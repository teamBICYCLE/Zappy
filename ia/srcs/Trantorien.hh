// Trantorien.hh

#ifndef _TRANTORIEN_HH_
#define _TRANTORIEN_HH_

#include "Inventory.hh"
#include "Network.hh"

#include "FSM.hpp"

class Trantorien : public FSM<Trantorien> {
public:
  Trantorien(const std::string ip, const std::string port);
  virtual ~Trantorien();


  void                  run();
private:
  bool                  isValid() const;

  FSMRetValue          avance();
  FSMRetValue          voir();

private:
  Inventory     inventory_;
  Network       network_;
};

#endif // _TRANDORIEN_HH_
