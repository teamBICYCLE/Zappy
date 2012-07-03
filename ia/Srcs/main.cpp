//
// main.cpp for  in /home/carpen_t/tmp/vm
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon Jun  4 15:13:05 2012 thibault carpentier
// Last update Mon Jul  2 15:33:57 2012 thibault carpentier
//

#include <cstdlib>
#include <iostream>
#include "Trantorien/Map.hh"
#include "Trantorien/Trantorien.hh"

int main(int argc, char *argv[])
{


  Map jaques(std::pair<int, int>(2, 2));

  jaques.test();
  jaques.voir("{ joueur sibur, nourriture nourriture linemate linemate deraumere deraumere deraumere sibur sibur sibur sibur sibur sibur mendiane mendiane mendiane phiras phiras phiras phiras phiras thystame, nourriture nourriture nourriture linemate linemate linemate linemate linemate linemate linemate linemate deraumere deraumere deraumere deraumere deraumere deraumere deraumere sibur sibur sibur sibur sibur mendiane mendiane, nourriture nourriture linemate linemate deraumere deraumere deraumere sibur sibur sibur sibur sibur sibur mendiane mendiane mendiane phiras phiras phiras phiras phiras thystame, joueur sibur, nourriture nourriture nourriture nourriture nourriture linemate linemate linemate linemate linemate linemate deraumere deraumere deraumere deraumere sibur sibur sibur sibur sibur sibur mendiane mendiane mendiane mendiane phiras phiras thystame, joueur sibur, nourriture nourriture nourriture nourriture nourriture linemate linemate linemate linemate linemate linemate deraumere deraumere deraumere deraumere sibur sibur sibur sibur sibur sibur mendiane mendiane mendiane mendiane phiras phiras thystame, joueur sibur}");



	      //{joueur sibur sibur,, sibur, sibur, sibur, sibur, sibur sibur, sibur, sibur, sibur, sibur, nourriture, nourriture, nourriture, sibur, sibur}");
  jaques.test();
  jaques.prendre("sibur");
  //jaques.test();
  //  jaques.poser("nourriture");
  //jaques.test();
//  jaques.avancer();
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
