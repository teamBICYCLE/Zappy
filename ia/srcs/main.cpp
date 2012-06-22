//
// main.cpp for  in /home/carpen_t/tmp/vm
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon Jun  4 15:13:05 2012 thibault carpentier
// Last update Fri Jun 22 13:57:55 2012 thibault carpentier
//


#include <stdlib.h>
#include <iostream>
#include <boost/asio.hpp>
#include  "Network.hh"
#include "Inventory.hh"
#include "Example.hh"
#include "Trantorien.hh"

#include <cstdlib>

using namespace LuaVirtualMachine;

int main(int argc, char *argv[])
{
  Inventory eude;

  (void)argc;
  (void)argv;

  eude.update("{nourriture 10,linemate 0,deraumere 0,sibur 0,mendiane 0,phiras 0,thystame 0}");

  // Trantorien  joe("localhost", "4242");

  // sleep(2);
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
