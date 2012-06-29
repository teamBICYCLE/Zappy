// FSM.hh

#ifndef _FSM_HH_
#define _FSM_HH_

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "Script.hh"
#include "Failure.hh"

enum FSMRetValue {OK = 0, KO, ERR};

template <typename X>
class FSM : public LuaVirtualMachine::Script {
  public:

  // Types
  typedef bool          (X::* ValidityTest)(void) const;
  typedef int           (X::* ContextInteraction)(LuaVirtualMachine::VirtualMachine &);

  // constructor / destructor
  FSM(X & context, ValidityTest test): context_(context), currentState_(0), keepRunning_(test) {}

  virtual ~FSM() {}

  // initializers
  void    init(const std::string & conf, const std::string & luaFile);

  void    addState(const std::string & stateName);
  void    addInteraction(const std::string & fctName, ContextInteraction fct);

  // lua handlers
  virtual int scriptCalling(LuaVirtualMachine::VirtualMachine &vm, int methIdx);
  virtual void getReturn(LuaVirtualMachine::VirtualMachine &vm, const std::string &fctName);

  // setter
  void    setValidityTest(ValidityTest test);

protected:
  void                      run();

  X &                       context_;
  std::vector< ContextInteraction >
  contextFunctions_;
  std::vector< std::pair< std::string, std::vector< int > > >
  states_;
  unsigned int              currentState_;
  ValidityTest              keepRunning_;
};

// ========================================== //

template <typename X>
void FSM<X>::init(const std::string &conf, const std::string &luaFile)
{
  int     transitions[] = {1, 0, 0};
  int     transitions2[] = {2, 1, 1};
  int     transitions3[] = {0, 2, 2};
  std::vector<int>  toto(transitions, transitions + sizeof(transitions) / sizeof(int));
  std::vector<int>  tata(transitions2, transitions2 + sizeof(transitions2) / sizeof(int));
  std::vector<int>  tete(transitions3, transitions3 + sizeof(transitions3) / sizeof(int));

  states_.resize(3);
  states_[0] = std::make_pair("avance", toto );
  states_[1] = std::make_pair("voir", tata );
  states_[2] = std::make_pair("prendre", tete );
  compileFile(luaFile);
  std::cout << "init done" << std::endl;
}

template <typename X>
void FSM<X>::addState(const std::string &stateName)
{
  std::vector<int>  toto;

  states_.push_back( std::make_pair(stateName, toto));
}

template <typename X>
void FSM<X>::addInteraction(const std::string &fctName, ContextInteraction fct)
{
  int   fctId = registerFct(fctName);

  if (fctId == -1)
    throw LuaVirtualMachine::Failure(fctName, "couldnt be register");
  if (static_cast<int>(contextFunctions_.size()) <= fctId)
    contextFunctions_.resize(fctId + 1);
  this->contextFunctions_[fctId] = fct;
}

template <typename X>
int FSM<X>::scriptCalling(LuaVirtualMachine::VirtualMachine &vm, int methIdx)
{
//  if (contextFunctions_.size() > static_cast<unsigned int>(methIdx))
    return (context_.*contextFunctions_[methIdx])(vm);
//  else
//    throw LuaVirtualMachine::Failure("API Function", "Script tried to call an unknown function");
}

template <typename X>
void FSM<X>::getReturn(LuaVirtualMachine::VirtualMachine &vm, const std::string &fctName)
{
  if (vm.isFonctionnal())
    {
      lua_State *state = vm.getLua();

      if (lua_gettop(state) != 1)
        throw LuaVirtualMachine::Failure(fctName, "not exactly one value was returned");
      else if (!lua_isnumber(state, 1) && !lua_isnil(state, 1))
        throw LuaVirtualMachine::Failure(fctName, "value returned was not an integer");
      currentState_ = (states_[currentState_].second)[lua_tonumber(state, 1)];
    }
}

template <typename X>
void FSM<X>::setValidityTest(FSM::ValidityTest test)
{
  keepRunning_ = test;
}

template <typename X>
void FSM<X>::run()
{
  while ((context_.*keepRunning_)())
    {
      selectFct(states_[currentState_].first);
      callFct(1);
    }
}

#endif // _FSM_HH_