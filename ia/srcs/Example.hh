//
// Example.hh for  in /home/carpen_t/tmp/vm
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon Jun  4 15:15:32 2012 thibault carpentier
// Last update Thu Jun  7 15:54:48 2012 thibault carpentier
//

#ifndef _EXAMPLE_H_
# define _EXAMPLE_H_

# include <map>
# include <string>
# include "VirtualMachine.hh"
# include "Script.hh"

namespace LuaVirtualMachine
{
  class Example : public Script
  {
   # define FILE "demo.lua"
   # define EXAMPLE_GLOBALINT 9
   # define EXAMPLE_GLOBALNB 5.07
   # define EXAMPLE_GLOBALSTR "toto"

  private:
    Example(Example const &);
    Example& operator=(Example const &);

  public:
    Example();
    ~Example();

    void	initLua(void);
    virtual     int		scriptCalling(VirtualMachine &vm, int fctNb);
    virtual void	getReturn(VirtualMachine &vm, const std::string &strFunc);

  private:
    int noret(VirtualMachine &vm);
    int multipleRet(VirtualMachine &vm);
  private:
    typedef int (LuaVirtualMachine::Example::*luaCallMeth)(VirtualMachine &);
    std::map<int, luaCallMeth> meth_;
  };

}
#endif /*!_EXAMPLE_H_*/
