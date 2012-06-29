//
// Faillure.hh for  in /home/carpen_t/projets/c++/iabomber
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Sat May 12 09:41:03 2012 thibault carpentier
// Last update Sat Jun 23 14:32:42 2012 thibault carpentier
//

#ifndef _FAILLURE_H_
# define _FAILLURE_H_

# include       <ostream>
# include       <stdexcept>

namespace LuaVirtualMachine
{
  class       Failure : public std::runtime_error
  {
  public:
    Failure(const std::string& func, const std::string& msg) throw();
    Failure(const Failure&) throw();
    Failure& operator=(const Failure&) throw();
    virtual ~Failure() throw();

  public:
    std::string               getFunc(void) const throw();
    std::string               getMsg(void) const throw();

  public:
    virtual const char*       what() const throw();

  private:
    std::string               mFunc;
    std::string               mMsg;
  };
}

#endif /*!_FAILLURE_H_*/
