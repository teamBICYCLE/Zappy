// VM.hpp

#ifndef _VM_HH_
#define _VM_HH_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

#include "lua/Script.hh"
#include "lua/Failure.hh"

namespace FSM {
template <typename X>
class VM : public LuaVirtualMachine::Script {
  public:

  // Types
  typedef bool          (X::* ValidityTest)(void) const;
  typedef int           (X::* ContextInteraction)(LuaVirtualMachine::VirtualMachine &);

  // constructor / destructor
  VM(X & context, ValidityTest test): context_(context), currentState_(0), keepRunning_(test) {}

  virtual ~VM() {}

  // initializers
  void    init(const std::string & conf, const std::string & luaFile);
  void    init2(const std::string & conf, const std::string & luaFile);


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
}

// ========================================== //

template <typename X>
void FSM::VM<X>::init(const std::string &conf, const std::string &luaFile)
{
  init2(conf, luaFile);

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
void FSM::VM<X>::init2(const std::string &confPath, const std::string &luaFilePath)
{
  std::ifstream       confStream(confPath);
  std::string         line;
 //std::list<Lexemes>  lexemes;

  if (!confStream.good())
    throw LuaVirtualMachine::Failure("Open configuration file", "could not be open");
  try {
   // lexemes = lex(confStream);
//    parse(lexemes);
  }
  catch (LuaVirtualMachine::Failure & e) {
    std::cout << e.what() << std::endl;
  }
}

template <typename X>
void FSM::VM<X>::addState(const std::string &stateName)
{
  std::vector<int>  toto;

  states_.push_back( std::make_pair(stateName, toto));
}

template <typename X>
void FSM::VM<X>::addInteraction(const std::string &fctName, ContextInteraction fct)
{
  int   fctId = registerFct(fctName);

  if (fctId == -1)
    throw LuaVirtualMachine::Failure(fctName, "couldnt be register");
  if (static_cast<int>(contextFunctions_.size()) <= fctId)
    contextFunctions_.resize(fctId + 1);
  this->contextFunctions_[fctId] = fct;
}

template <typename X>
int FSM::VM<X>::scriptCalling(LuaVirtualMachine::VirtualMachine &vm, int methIdx)
{
//  if (contextFunctions_.size() > static_cast<unsigned int>(methIdx))
    return (context_.*contextFunctions_[methIdx])(vm);
//  else
//    throw LuaVirtualMachine::Failure("API Function", "Script tried to call an unknown function");
}

template <typename X>
void FSM::VM<X>::getReturn(LuaVirtualMachine::VirtualMachine &vm, const std::string &fctName)
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
void FSM::VM<X>::setValidityTest(VM::ValidityTest test)
{
  keepRunning_ = test;
}

template <typename X>
void FSM::VM<X>::run()
{
  while ((context_.*keepRunning_)())
    {
      selectFct(states_[currentState_].first);
      callFct(1);
    }
}

#endif // _VM_HH_
