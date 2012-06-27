//
// main.cpp for  in /home/carpen_t/tmp/vm
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon Jun  4 15:13:05 2012 thibault carpentier
// Last update Wed Jun 27 14:18:54 2012 thibault carpentier
//


#include <stdlib.h>
#include <iostream>
#include <boost/asio.hpp>
#include  "Network.hh"
#include "Inventory.hh"
#include "Example.hh"
#include "Trantorien.hh"
#include <string>
#include "Map.hh"

#include <cstdlib>

using namespace LuaVirtualMachine;

int main(int argc, char *argv[])
{


  Map jaques(std::pair<int, int>(10, 5));

  jaques.voir("{ joueur sibur phiras,, sibur, linemate}");
  // jaques.avancer();
  // jaques.avancer();
  // Inventory eude;

//  (void)argc;
//  (void)argv;

  // eude.update("{nourriture 1,linemate 2,deraumere 3 ,sibur  4 ,mendiane    5 ,phiras   6}");// , thystame 7}");

   // Trantorien  joe("localhost", "4242");

   // joe.run();

//  Example toto;

//  toto.compileFile(FILE);

//  toto.selectFct("oneRet");
//  toto.callFct(1);

//  toto.selectFct("multRet");
//  toto.addParam(12);
//  toto.addParam("totopar");
//  toto.callFct(5);
//  return (EXIT_SUCCESS);
}
