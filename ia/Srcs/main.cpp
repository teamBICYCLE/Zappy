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

namespace po = boost::program_options;

int main(int argc, char *argv[])
{
  po::options_description desc("Usage:" + std::string(argv[0]) + " <le-file> <lua-file> [options]");
  po::positional_options_description  po;
  po::variables_map vm;

  desc.add_options()
      ("help,h", "produce help message")
      ("host,i", po::value<std::string>()->default_value("localhost"), "Specifie the host ip address")
      ("port,p", po::value<std::string>()->default_value("4242"), "Specifie the port or service to connect on")
      ("team,n", po::value<std::string>()->default_value("toto"), "team to join")
      ("le-file,c", po::value<std::string>()->required(), "LightEsterel file witch describes the finite state machine rules")
      ("lua-file,l", po::value<std::string>()->required(), "lua file witch codes the finite state machine states")
      ;
  po.add("le-file", 1).add("lua-file", 2);
  try {
    po::store(po::command_line_parser(argc, argv).options(desc).positional(po).run(), vm);
    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 0;
      }
    po::notify(vm);
  }
  catch (std::exception & e)
  {
    std::cout << e.what() << std::endl;
    std::cout << desc << std::endl;
    return 1;
  }
  try
  {
    Trantorien  joe(vm["host"].as<std::string>(),
                    vm["port"].as<std::string>(),
                    vm["le-file"].as<std::string>(),
                    vm["lua-file"].as<std::string>(),
                    vm["team"].as<std::string>(), argv);

    joe.run();
  }
  catch (std::exception &e)
  {
    std::cerr << "FATAL ERROR: " << e.what() << std::endl;
  }
  return (EXIT_SUCCESS);
}
