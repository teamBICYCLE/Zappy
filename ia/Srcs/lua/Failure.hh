//
// Faillure.hh for  in /home/carpen_t/projets/c++/iabomber
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Sat May 12 09:41:03 2012 thibault carpentier
// Last update Fri Jul 13 12:37:29 2012 thibault carpentier
//

#ifndef _FAILURE_H_
# define _FAILURE_H_

# include       <ostream>
# include       <stdexcept>

namespace LuaVirtualMachine
{
  class       Failure : public std::exception
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
    std::string		      what_;
  };
}

#endif /*!_FAILLURE_H_*/
