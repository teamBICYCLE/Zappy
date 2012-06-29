//
// VirtualMachine.hh for  in /home/carpen_t/projets/c++/iabomber
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Fri May  4 14:47:20 2012 thibault carpentier
// Last update Thu Jun  7 12:00:02 2012 thibault carpentier
//

#ifndef  _VIRTUALMACHINE_H_
# define _VIRTUALMACHINE_H_

# include <map>
# include <sys/types.h>
# include <string>
# include "luainc.hh"

typedef void (*fctHook)(lua_State *); // typedef pour le debugger.

namespace LuaVirtualMachine
{
  class VirtualMachine
  {
  private:						// debug class
    class Debugger
      {
      public:
	Debugger(VirtualMachine &vm);			// init debug
	~Debugger(void);			        // destroy debug
	static int	setHook(lua_State *lua);	// set a debug flags from lua

      private:
	static void	setFctHook(void);			// init hookers
	Debugger(Debugger const &);
	Debugger& operator=(Debugger const &);
	VirtualMachine		&VM_;			// VM instance
      };

    lua_State		*vmState_;			// luaStack
    bool		isOk_;				// vm is ok ?
    Debugger		*debug_;			// debugger
    static VirtualMachine *single_;			// vm instance

    VirtualMachine(void);
    ~VirtualMachine(void);
    bool initVm(void);
    bool destroyVm(void);

    VirtualMachine(VirtualMachine const &other);
    VirtualMachine& operator=(VirtualMachine const &other);

  public:
    static VirtualMachine *getVm(void);		// singleton getter
    void addDebugger(Debugger *debug);		// stokcking the debugger (init in the initVM)
    Debugger *getDebug(void) const;			// getting constructor

    bool isFonctionnal(void) const;			// checking is the vm is correctly init
    lua_State *getLua(void) const;			// getting the luastack

    static int printDebug(lua_State *state);		// debugging fonction used in luascript
    static int panic(lua_State *state);		// fonction called when luapanic
  };
}

#endif /*!_VIRTUALMACHINE_H_*/
