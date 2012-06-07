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
#include "Example.hh"

using namespace LuaVirtualMachine;


int main(int ac, char *av[])
{
  (void)ac;
  (void)av;
  Example toto;

  toto.compileFile(FILE);

  toto.selectFct("oneRet");
  toto.callFct(1);

  toto.selectFct("multRet");
  toto.addParam(12);
  toto.addParam("totopar");
  toto.callFct(5);
  return (EXIT_SUCCESS);
}
