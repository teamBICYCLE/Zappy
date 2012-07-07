// VM.hpp

#ifndef _VM_HH_
#define _VM_HH_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <boost/regex.hpp>

#include "lua/Script.hh"
#include "lua/Failure.hh"

//#define DEBUG

namespace FSM {
template <typename X>
class VM : public LuaVirtualMachine::Script {
  public:

  // Types
  typedef bool          (X::* ValidityTest)(void) const;
  typedef int           (X::* ContextInteraction)(LuaVirtualMachine::VirtualMachine &);
  typedef std::vector< std::pair< std::string, std::vector< int > > > StateVector;

  // constructor / destructor
  VM(X & context, ValidityTest test): context_(context), currentState_(0), keepRunning_(test)
  {
    //retCode_.push_back("SELF");
  }

  virtual ~VM() {}

  // initializers
  void    init(const std::string & conf, const std::string & luaFile);
private:
  void    readConfFile(const std::string & conf, const std::string & luaFile);
  void    createStates(std::istream & stream);
  void    setRetValueGlobals();

public:
  void    addState(const std::string & stateName);
  void    addLink(const std::string & startState, const std::string & answer,
                  const std::string & finalState);
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
  StateVector               states_;
  std::vector<std::string>  retCode_;
  unsigned int              currentState_;
  ValidityTest              keepRunning_;
};
}

// ========================================== //

template <typename X>
void FSM::VM<X>::init(const std::string &conf, const std::string &luaFile)
{
  readConfFile(conf, luaFile);
  compileFile(luaFile);
  std::cout << "Finite State Machine: init OK" << std::endl;
}

template <typename X>
void FSM::VM<X>::readConfFile(const std::string &confPath, const std::string &luaFilePath)
{
  std::ifstream       confStream(confPath);
  std::string         line;

  if (!confStream.good())
    throw LuaVirtualMachine::Failure("Open configuration file", "could not be open");
  createStates(confStream);
  setRetValueGlobals();
}

template <typename X>
void FSM::VM<X>::createStates(std::istream &stream)
{
  boost::regex    state("state: *([a-zA-Z][a-zA-Z0-9_-]*)");
  boost::regex    link("([a-zA-Z][a-zA-Z0-9_-]*) *\\[([A-Z]+)] *-> *([a-zA-Z][a-zA-Z0-9_-]*)");
  std::string     line;

  while (std::getline(stream, line))
    {
      boost::match_results<std::string::iterator>  what;

#ifdef DEBUG
      std::cout << "line: " << line << std::endl;
#endif
      if (boost::regex_search(line.begin(), line.end(), what, state,
                          boost::regex_constants::match_default))
        {
#ifdef DEBUG
          std::cout << "MATCHED with " << state.expression() << std::endl;
          std::cout << "Extracted: " << what[1] << std::endl;
#endif
          addState(what[1]);
        }
      else if (boost::regex_search(line.begin(), line.end(), what, link,
                                   boost::regex_constants::match_default))
        {
#ifdef DEBUG
          std::cout << "MATCHED with " << link.expression() << std::endl;
          std::cout << "Extracted: " << what[1] << " && " << what[2] << " && " << what[3] << std::endl;
          addLink(what[1], what[2], what[3]);
#endif
        }
#ifdef DEBUG
      else
        std::cout << "DID NOT MATCHED" << std::endl;
#endif
    }
}

template <typename X>
void FSM::VM<X>::setRetValueGlobals()
{
  lua_State   *state = getVM().getLua();

  for (unsigned int i = 0; i < retCode_.size(); ++i) {
      lua_pushinteger(state, i);
      lua_setglobal(state, retCode_[i].c_str());
    }
}

template <typename X>
void FSM::VM<X>::addState(const std::string &stateName)
{
  std::vector<int>  toto;

  if (std::find_if(states_.begin(), states_.end(),
               [stateName](const std::pair<std::string, std::vector<int> > & pair)
               -> bool {return pair.first == stateName;}) == states_.end())
    states_.push_back( std::make_pair(stateName, toto));
}

template <typename X>
void FSM::VM<X>::addLink(const std::string &startState, const std::string &answer, const std::string &finalState)
{
  StateVector::iterator               toEdit, toPoint;
  std::vector<std::string>::iterator  answerPos;

  // create answer in retCode array
  answerPos = std::find(retCode_.begin(), retCode_.end(), answer);
  if (answerPos == retCode_.end())
    {
      retCode_.push_back(answer);
      answerPos = retCode_.begin() + (retCode_.size() - 1);
      for (int i = 0; i < static_cast<int>(states_.size()); ++i) {
          states_[i].second.resize(retCode_.size(), i);
        }
    }
  // find position in states array of start and pointed state

  if ((toEdit = std::find_if(states_.begin(), states_.end(),
               [startState](const std::pair<std::string, std::vector<int> > & pair)
               -> bool {return pair.first == startState;})) == states_.end())
    throw LuaVirtualMachine::Failure("add link", startState + " state doesnt exists.");
  if ((toPoint = std::find_if(states_.begin(), states_.end(),
                   [finalState](const std::pair<std::string, std::vector<int> > & pair)
                   -> bool {return pair.first == finalState;})) == states_.end())
    throw LuaVirtualMachine::Failure("add link", finalState + " state doesnt exists.");

  // push
  (*toEdit).second[std::distance(retCode_.begin(), answerPos)] = std::distance(states_.begin(), toPoint);
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
