//
// RestoreStack.hh for  in /home/jonathan/Projets/iabomber
//
// Made by Jonathan Machado
// Login   <jonathan.machado@epitech.net>
//
// Started on  Sat May  5 16:19:00 2012 Jonathan Machado
// Last update Tue Jun  5 18:50:21 2012 thibault carpentier
//

#ifndef __RESTORESTACK_H__
# define __RESTORESTACK_H__
# include "luainc.hh"
# include "VirtualMachine.hh"

namespace LuaVirtualMachine
{
  class RestoreStack
  {
  public:
    RestoreStack(VirtualMachine &vm);
    ~RestoreStack(void);

  private:
    RestoreStack(RestoreStack const&);
    RestoreStack &operator=(RestoreStack const&);

    lua_State		*state_;
    int			iTop_;
  };
}


#endif /* __RESTORESTACK_H__ */
