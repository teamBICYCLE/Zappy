//
// main.cpp for  in /home/carpen_t/tmp/vm
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon Jun  4 15:13:05 2012 thibault carpentier
//

#include <cstdlib>
#include <iostream>
#include <exception>
#include <fstream>
#include <boost/program_options.hpp>
#include "Trantorien/Trantorien.hh"
#include "Trantorien/Map.hh"
#include "FSM/Lexeme.hh"

int main(int argc, char *argv[])
{
  // Trantorien  joe("localhost", "4242", "Scripts/conf.le", "Scripts/script.lua",argv);
  // LuaVirtualMachine::VirtualMachine *vm = LuaVirtualMachine::VirtualMachine::getVm();

  // joe.connect_player(*vm);
std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< LANCEMENT DU TRANTORIEN >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
  if (argc > 2)
    {
      try
      {
        Trantorien  joe("localhost", "4242", argv);

        joe.run();
      }
      catch (std::exception &e)
      {
        std::cerr << "FATAL ERROR: " << e.what() << std::endl;
      }
    }
  else
    std::cout << argv[0] << " conf.le script.lua" << std::endl;
  return (EXIT_SUCCESS);
}
