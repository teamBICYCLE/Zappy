// FSM.hh

#ifndef _FSM_HH_
#define _FSM_HH_

#include <vector>

enum FSMRetValue {OK = 0, KO, ERR};

template <typename X>
class FSM {
  public:
  typedef FSMRetValue  (X::* FSMState)(void);
  typedef bool         (X::* ValidityTest)(void) const;

  FSM(): currentState_(0), keepRunning_(nullptr) {}
  virtual ~FSM() {}

  void    addState(FSMState state);
  void    setValidityTest(ValidityTest test);

protected:
  void                      run(X & context);
  std::vector<FSMState>     states_;
  unsigned int              currentState_;
  ValidityTest              keepRunning_;
};

template <typename X>
void      FSM<X>::run(X & context)
{
  unsigned int     transTable[][3] =
  {
    {1, 0, 0},
    {0, 1, 1}
  };



  while (/* no error */!keepRunning_ || (context.*keepRunning_)())
    currentState_ = transTable[currentState_][(context.*states_[currentState_])(/*params*/)];
}

template <typename X>
void      FSM<X>::setValidityTest(ValidityTest test)
{
  keepRunning_ = test;
}


#endif // _FSM_HH_
