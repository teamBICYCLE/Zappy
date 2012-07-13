//
// TrantorienFailure.hh for  in /home/carpen_t/projets/syst_Unix/Zappy/ia
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Sat Jun 23 14:35:31 2012 thibault carpentier
// Last update Fri Jul 13 12:37:17 2012 thibault carpentier
//

#ifndef _TRANDORIEN_FAILURE_H_
# define _TRATORIEN_FAILURE_H_

# include       <ostream>
# include       <stdexcept>

class       TrantorienFailure : public std::runtime_error
{
public:
  TrantorienFailure(const std::string& func, const std::string& msg) throw();
  TrantorienFailure(const TrantorienFailure&) throw();
  TrantorienFailure& operator=(const TrantorienFailure&) throw();
  virtual ~TrantorienFailure() throw();

public:
  std::string               getFunc(void) const throw();
  std::string               getMsg(void) const throw();

public:
  virtual const char*       what() const throw();

private:
  std::string               mFunc_;
  std::string               mMsg_;
  std::string		    what_;
};


#endif /*!_FAILLURE_H_*/
