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

int main(int argc, char *argv[])
{
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
