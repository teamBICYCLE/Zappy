//
// Script.hh for  in /home/carpen_t/projets/c++/iabomber
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Sat May  5 11:46:39 2012 thibault carpentier
// Last update Mon Jun  4 15:58:45 2012 thibault carpentier
//

#ifndef _SCRIPT_H_
# define _SCRIPT_H_

# include "VirtualMachine.hh"

namespace LuaVirtualMachine
{
  class Script
  {

  public:
    Script(void);
    virtual ~Script(void);

    int getNbMeth(void) const;					// get nb Methods
    VirtualMachine &getVM(void) const;				// get Virtual Machine

    bool	compileFile(const std::string &filename);		// Get lua file and launch main.
    int	registerFct(const std::string &fctName);		// Add a cpp fct to the "table object"
    virtual int scriptCalling(VirtualMachine &vm, int methIdx) = 0; // Method too overwrite to
    // determine witch cpp is called
    virtual void getReturn(VirtualMachine &vm, const std::string &fctName) = 0; // Method to get lua return

    bool	fctExist(const std::string &fctName); // check if fct exist on the "table object"
    bool	selectFct(const std::string &fctName); // Select a fct to call
    void	addParam(int param);		       // add a param to the selected fct
    void	addParam(const std::string &param);    // add a param to the selected fct
    void	addParam(float param);		       // add a param to the selected fct
    void	addParam(double param);		       // add a param to the selected fct
    bool	callFct(int nbRet = 0);		       // Call the selected fct

  private:			// unused constructors
    Script(Script const &other);
    Script& operator=(Script const &other);

    VirtualMachine	&VM_;		// Virtual Machine
    int		 refThis_;	// "Object Table"
    int		 nbArgs_;	// nb arguments to the selected fonction
    int		 nbMethod_;	// nb of fct in the "Object Table"
    std::string	 fctName_;	// Name of the selected fct
  };
}

#endif /*!_SCRIPT_H_*/
