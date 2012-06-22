//
// main.cpp for  in /home/carpen_t/tmp/vm
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon Jun  4 15:13:05 2012 thibault carpentier
// Last update Tue Jun  5 18:57:27 2012 thibault carpentier
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
  Trantorien  joe("localhost", "4242");

  joe.run();

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
