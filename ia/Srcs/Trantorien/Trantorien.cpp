//
// Trantorien.cpp for  in /home/carpen_t/projets/syst_Unix/Zappy/ia
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Fri Jul 13 11:39:41 2012 thibault carpentier
// Last update Sun Jul 15 15:40:18 2012 thibault carpentier
//


/*! \mainpage Classe API Lua-C++ Documentation
 *
 * \section intro_sec Introduction
 *
 * This documentation will help non-developpers or developpers to implements new Artificial Intelligence
 * on the Zappy.
 *
 * \section install_sec Mini tutorial :
 * Launch galaxy and draw your finite State Machine with the soft. Once done, generate the conf file and export it on light Esterel format (.le) <br/> Done forget that the first state drawed is the first state called.
 * <br/> Once done, open a lua file and develop function for each state in lua. this:nodename(this). Once done, launch and Enjoy !
 *
 * \subsection Warning
 * Warning, this documentation does not details the c++class but how to call the api functions from the lua. All the function named here have to have prefix "this:IA" when called in lua.
 *
 *
 * \section Global
 * Here is the Global List pused on the lua stack to use game variables easily
 *
 * <ul>
 * <li> functions: </li> <br/>
 * printDebug([int|string], ...) <br/><br/>
 * <li> Direction global </li> <br/>
 * NONE <br/>
 * NORD  <br/>
 * EST  <br/>
 * SUD  <br/>
 * OUEST  <br/>
 * GAUCHE   <br/>
 * DROITE <br/><br/>
 * <li>Items Global</li>
 * <br/>
 * NOURRITURE  <br/>
 * LINEMATE   <br/>
 * DERAUMERE  <br/>
 * SIBUR  <br/>
 * MENDIANE  <br/>
 * THIPRAS  <br/>
 * THYSTAME   <br/>
 * JOUEUR  <br/>
 * <br/>
 <li>Misc Globals</li><br/>
 * TEAMNAME <br/>
 * MAPX <br/>
 * MAPY <br/>
 * \section copyright Copyright and License
 *
 *  Copyright 2012, all rights reserved, TeamBicycle.
 *
 * <BR><BR>
 *
 */

#include "Trantorien.hh"

#include <cmath>
#include <iostream>
#include <string>
#include "TrantorienFailure.hh"

static const std::string PLAYER_DEAD_STRING = "mort";
static const std::string BROADCAST_TEXT_RCV = "message ";
static const std::string CURRENTLY_ELEVATE_STR = "elevation en cours";
static const std::string NEW_LEVEL = "niveau actuel :";
static const std::string COUNT_PLAYER = "Census !";
static const std::string COUNT_ME = "I'm alive!";

Trantorien::Trantorien(const std::string & ip, const std::string & port,
                       const std::string & lefile, const std::string & luafile,
                       const std::string & team,
                       char *av[])
  : FSM::VM<Trantorien>(*this, &Trantorien::isValid), network_(ip, port), map_(std::pair<int, int>(20, 20)), level_(1), av_(av), teamname(team)
{
  if (!network_)
    {
      throw std::runtime_error(network_.error().message());
    }
  init(lefile, luafile);

  addInteraction("IAAvance", &Trantorien::avance);
  addInteraction("IAVoir", &Trantorien::voir);
  addInteraction("IAInventaire", &Trantorien::inventaire);
  addInteraction("IAPrendre", &Trantorien::prendre);
  addInteraction("IATourner", &Trantorien::tourner);
  addInteraction("IAElevate", &Trantorien::elevate);
  addInteraction("IAPoser", &Trantorien::poser);
  addInteraction("IABroadcast", &Trantorien::broadcast);
  addInteraction("IACaseContent", &Trantorien::caseContent);
  addInteraction("IACurrentPosition", &Trantorien::currentPosition);
  addInteraction("IACurrentDirection", &Trantorien::currentDirection);
  addInteraction("IAgetInventoyValue", &Trantorien::getInventoryValue);
  addInteraction("IAExpulse", &Trantorien::expulse);
  addInteraction("IAGoto", &Trantorien::goTo);
  addInteraction("IAGetLevel", &Trantorien::getLevel);
  addInteraction("IAMissingRockOnCase", &Trantorien::missingRockOnCase);
  addInteraction("IAMissingRockInInventory", &Trantorien::missingRockInInventory);
  addInteraction("IAMissingRockInInventoryID", &Trantorien::missingRockInInventoryID);
  addInteraction("IAGetCLosestItem", &Trantorien::getClosestItem);
  addInteraction("IAChangeFrame", &Trantorien::changeFrame);
  addInteraction("IAMissingToElevate", &Trantorien::missingToElevate);
  addInteraction("IALastMsg", &Trantorien::LastMsg);
  addInteraction("IAMessageInQueue", &Trantorien::messageInQueue);
  addInteraction("IAreadLine", &Trantorien::readLine);
  addInteraction("IACanConnectPlayer", &Trantorien::canConnectPlayer);
  addInteraction("IAConnectPlayer", &Trantorien::connectPlayer);
  addInteraction("IALay", &Trantorien::lay);
  addInteraction("IANbMsgInQueue", &Trantorien::nbMessageInQueue);
  addInteraction("IACountPlayer", &Trantorien::countPlayer);
  addInteraction("IAGetItemWithLength", &Trantorien::getItemWithLength);

  setValidityTest(&Trantorien::isValid);

  lua_State *state = getVM().getLua();
  lua_pushinteger(state, UserGlobal::NONE);
  lua_setglobal(state, "NONE");
  lua_pushinteger(state, UserGlobal::NORD);
  lua_setglobal(state, "NORD");
  lua_pushinteger(state, UserGlobal::EST);
  lua_setglobal(state, "EST");
  lua_pushinteger(state, UserGlobal::SUD);
  lua_setglobal(state, "SUD");
  lua_pushinteger(state, UserGlobal::OUEST);
  lua_setglobal(state, "OUEST");

  lua_pushinteger(state, UserGlobal::NOURRITURE);
  lua_setglobal(state, "NOURRITURE");
  lua_pushinteger(state, UserGlobal::LINEMATE);
  lua_setglobal(state, "LINEMATE");
  lua_pushinteger(state, UserGlobal::DERAUMERE);
  lua_setglobal(state, "DERAUMERE");
  lua_pushinteger(state, UserGlobal::SIBUR);
  lua_setglobal(state, "SIBUR");
  lua_pushinteger(state, UserGlobal::MENDIANE);
  lua_setglobal(state, "MENDIANE");
  lua_pushinteger(state, UserGlobal::PHIRAS);
  lua_setglobal(state, "PHIRAS");
  lua_pushinteger(state, UserGlobal::THYSTAME);
  lua_setglobal(state, "THYSTAME");
  lua_pushinteger(state, UserGlobal::JOUEUR);
  lua_setglobal(state, "JOUEUR");

  lua_pushinteger(state, UserGlobal::GAUCHE);
  lua_setglobal(state, "GAUCHE");
  lua_pushinteger(state, UserGlobal::DROITE);
  lua_setglobal(state, "DROITE");

  lua_pushstring(state, team.c_str());
  lua_setglobal(state, "TEAMNAME");

  joinTeam(team);
  this->getline();
  map_.setSize(this->getline());

  lua_pushnumber(state, map_.getSize().first);
  lua_setglobal(state, "MAPX");
  lua_pushnumber(state, map_.getSize().second);
  lua_setglobal(state, "MAPY");
}

Trantorien::~Trantorien()
{}

template <>
int Trantorien::variableArgsCall<std::string, std::string>(LuaVirtualMachine::VirtualMachine &vm,
                                 std::function<std::string(lua_State *,
                                                           const std::string &)> fct)
{
  lua_State               *state = vm.getLua();
  std::list<std::string>  answers;
  int i = 1;

  for (i = 1; i <= lua_gettop(state); ++i)
    {
      if (lua_isstring(state, i))
        {
          std::string result = fct(state, lua_tostring(state, i));
          answers.push_back(result);
        }
    }
  i = 0;
  while (!answers.empty())
    {
      lua_pushstring(state, answers.front().c_str());
      answers.pop_front();
      ++i;
    }
  return (i);
}

template <>
int  Trantorien::variableArgsCall<int, std::string>(LuaVirtualMachine::VirtualMachine &vm,
                                 std::function<std::string(lua_State *,
                                                           const int &)> fct)
{
  lua_State               *state = vm.getLua();
  std::list<std::string>  answers;
  int i = 1;

  for (i = 1; i <= lua_gettop(state); ++i)
    {
      if (lua_isnumber(state, i))
        {
          std::string result = fct(state, lua_tointeger(state, i));
          answers.push_back(result);
        }
    }
  i = 0;
  while (!answers.empty())
    {
      lua_pushstring(state, answers.front().c_str());
      answers.pop_front();
      ++i;
    }
  return (i);
}

template <>
int  Trantorien::variableArgsCall<int, std::pair< int, int> >(LuaVirtualMachine::VirtualMachine &vm,
							      std::function<std::pair<int, int>(lua_State *,
									const int &)> fct)
{
  lua_State *state = vm.getLua();
  std::list<std::pair<int, int> >  answers;
  int i = 1;

  for (i = 1; i <= lua_gettop(state); ++i)
    {
      if (lua_isnumber(state, i))
        {
          std::pair<int, int> result = fct(state, lua_tointeger(state, i));
          answers.push_back(result);
        }
    }
  i = 0;
  while (!answers.empty())
    {
      lua_pushinteger(state, answers.front().first);
      lua_pushinteger(state, answers.front().second);
      answers.pop_front();
      i += 2;
    }
  return (i);
}


template <>
int Trantorien::variableArgsCall<int, int>(LuaVirtualMachine::VirtualMachine &vm,
                                 std::function<int(lua_State *,
                                                   const int &)> fct)
{
  lua_State               *state = vm.getLua();
  std::list<int>          answers;
  int i = 1;

  for (i = 1; i <= lua_gettop(state); ++i)
    {
      if (lua_isnumber(state, i))
        {
          int result = fct(state, lua_tonumber(state, i));
          answers.push_back(result);
        }
    }
  i = 0;
  while (!answers.empty())
    {
      lua_pushnumber(state, answers.front());
      answers.pop_front();
      ++i;
    }
  return (i);
}

void Trantorien::run()
{
  FSM::VM<Trantorien>::run();
}

void Trantorien::joinTeam(const std::string &teamName)
{
  this->cmd(teamName);
}

void Trantorien::cmd(const std::string &command)
{
  network_.cmd(command);
}

std::string Trantorien::getline()
{
  std::string     line = network_.getline();

  if (line == PLAYER_DEAD_STRING)
    {
      std::cerr << "MORT" << std::endl;
      abort();
    }
  else if (!line.compare(0, BROADCAST_TEXT_RCV.length(), BROADCAST_TEXT_RCV))
    {
      Message   msg(line, map_.getCurrentPos(), map_.getDirection(), map_.getSize());
      boost::regex	rgx(teamname + " " + COUNT_PLAYER + " *([0-9]+)");
      boost::match_results<std::string::const_iterator> what;

      if (regex_search(msg.getMessage().begin(), msg.getMessage().end(),
                       what, rgx, boost::match_default))
        {
          line = this->getline();
          this->cmd("broadcast " + teamname + " " + COUNT_ME + " " + what[1]);
          this->getline();
        }
      else
        {
          broadcastHistory_.push_back(msg);
          while (broadcastHistory_.size() > BROADCAST_MAX_SIZE)
            broadcastHistory_.pop_front();
          line = this->getline();
        }
    }
  else if (!line.compare(0, NEW_LEVEL.length(), NEW_LEVEL))
    ++level_;
  return line;
}

Message Trantorien::getBroadcastLine()
{
  if (!broadcastHistory_.empty())
    {
      Message line = broadcastHistory_.front();
      broadcastHistory_.pop_front();
      return line;
    }
  else
    return Message();
}

bool Trantorien::isValid() const
{
  return network_;
}

void Trantorien::droite()
{
  this->cmd("droite");
  this->getline();
  map_.changeDirection(UserGlobal::DROITE);
}

void Trantorien::gauche()
{
  this->cmd("gauche");
  this->getline();
  map_.changeDirection(UserGlobal::GAUCHE);
}

/*!
 *  \brief Makes tratoriens move.
 *  Makes the trantorien move forward.
 *  \param (void)
 *  \return (string) the server response, "ok" on success "ko" on failure.
 */
int Trantorien::avance(LuaVirtualMachine::VirtualMachine &vm)
{
  std::string ret;

  this->cmd("avance");
  ret = this->getline();
  if (ret == "ok")
    map_.avancer();
  lua_pushstring(vm.getLua(), ret.c_str());
 return 1;
}

/*!
 *  \brief Makes tratoriens see.
 *  Makes the trantorien move forward. This function update the content of the map in the API.
 *  \param (void)
 *  \return (string) the server response, map content on success "ko" on failure.
 */
int Trantorien::voir(LuaVirtualMachine::VirtualMachine &vm)
{
  std::string ret;

  this->cmd("voir");
  ret = this->getline();
  if (ret != "ko")
    map_.voir(ret);
  lua_pushstring(vm.getLua(), ret.c_str());
  return 1;
}


/*!
 *  \brief Return a recently updated inventory
 *   Return for each value of the inventory an integer according to his recently updated value.
 *  \param (void)
 *  \return (int, int, int, int ...) the values of the inventory.
 */
int Trantorien::inventaire(LuaVirtualMachine::VirtualMachine &vm)
{
  std::string ret;
  unsigned int i;
  lua_State *state = vm.getLua();

  this->cmd("inventaire");
  ret = this->getline();
  if (ret != "ko")
    inventory_.update(ret);

  const std::vector<unsigned int> & inventory = inventory_.getInventory();
  for ( i = 0; i < inventory.size(); ++i)
    lua_pushinteger(state, inventory[i]);
  return (i);
}

/*!
 *  \brief Take one or more item(s) on the map.
 *   Take one or more item(s) on the map and return the server answer.
 *  \param (Items Global(exept JOUEUR), ...)
 *  \return (string, ...) the server's answer(s).
 */
int Trantorien::prendre(LuaVirtualMachine::VirtualMachine &vm)
{
  return (
          variableArgsCall<int ,std::string>(vm,
                                             [&](lua_State * state, const int & object) ->
                                             std::string {
                                               if (object < UserGlobal::JOUEUR && object >= 0)
                                                 {
                                                   this->cmd("prend " + GlobalToString::inventaireObject[object]);
                                                   std::string result = this->getline();
                                                   if (result == "ok")
                                                     {
                                                       inventory_.prendre(GlobalToString::inventaireObject[object]);
                                                       map_.prendre(object);
                                                     }
                                                   return result;
                                                 }
                                               return ("ko");
                                             }));
}

/*!
 *  \brief turn the trantorien
 *  Turn the trantorien and update in the map's API the current direction of the trantorien
 *  \param (Direction global (GAUCHE DROITE), ...)
 *  \return (string, ...) the server's answer(s).
 */
int Trantorien::tourner(LuaVirtualMachine::VirtualMachine &vm)
{
  return (
          variableArgsCall<int, std::string>(vm,
                                             [&](lua_State * state, const int & direction) ->
                                             std::string {
                                               std::string result;
                                               if (direction >= UserGlobal::GAUCHE && direction <= UserGlobal::DROITE)
                                                 {
                                                   this->cmd(GlobalToString::orientation[direction]);
                                                   result = this->getline();
                                                   if (result == "ok")
                                                     map_.changeDirection(direction);
                                                 }
                                               return result;
                                             }));
}

/*!
 *  \brief elevate the trantorien
 *  The trantorien will start an incantation. On succeed, the level on the API is updated
 *  \param (void)
 *  \return (string) the server's answer(s).
 */
int Trantorien::elevate(LuaVirtualMachine::VirtualMachine &vm)
{
  this->cmd("incantation");
  std::string ret = this->getline();
  if (ret == CURRENTLY_ELEVATE_STR)
    if ((ret = this->getline()) != "ko")
      lua_pushstring(vm.getLua(), ret.c_str());
  this->cmd("voir");
  ret = this->getline();
  if (ret == "ko")
    ret = this->getline();
  return 1;
}

/*!
 *  \brief Make the trantorien talk
 *  The trantorien will yell the message to the others.
 *  \param (string) msg
 *  \return (void).
 */
int Trantorien::broadcast(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State *state = vm.getLua();

  if (lua_gettop(state) >= 1 && lua_isstring(state, 1))
    {
      std::string user = lua_tostring(vm.getLua(), 1);
      this->cmd("broadcast " + teamname + " " + user);
      this->getline();
      return 0;
    }
  else
    throw TrantorienFailure("Trantorien broadcast", "Invalid parameter: (void broadcast(string msg))");
}

/*!
 *  \brief Makes the trantorien drop one or more items on the map.
 *  This function update the API's maps
 *  \param (Items Global (Exept JOUEUR), ...)
 *  \return (string) the server's answer.
 */
int Trantorien::poser(LuaVirtualMachine::VirtualMachine &vm)
{
  return (
          variableArgsCall<int ,std::string>(vm,
                                             [&](lua_State * state, const int & object) ->
                                             std::string {
                                               if (object < UserGlobal::JOUEUR && object >= 0)
                                                 {
                                                   this->cmd("pose " + GlobalToString::inventaireObject[object]);
                                                   std::string result = this->getline();
                                                   if (result == "ok")
                                                     {
                                                       inventory_.poser(GlobalToString::inventaireObject[object]);
                                                       map_.poser(object);
                                                     }
                                                   return result;
                                                 }
                                               return ("ko");
                                             }));
}

/*!
 *  \brief Makes the trantorien drop one or more items on the map.
 *  This function update the API's maps
 *  \param (Items Global (Exept JOUEUR), ...)
 *  \return (string) the server's answer.
 */
int Trantorien::caseContent(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State *state = vm.getLua();
  unsigned int nbRet = 0;

  if (lua_gettop(state) >= 2 && lua_isnumber(state, 1) && lua_isnumber(state, 2))
    {
      std::pair<int, int> position(lua_tonumber(state, 1), lua_tonumber(state, 2));
      std::vector<unsigned int> result = map_.caseContent(position);
      for (std::vector<unsigned int>::iterator it = result.begin(); it != result.end(); ++it)
        {
          lua_pushinteger(state, (*it));
          ++nbRet;
        }
      return (nbRet);
    }
  throw TrantorienFailure("Tratorien caseContent", "Invalid parameter : (int x8 caseContent(int x, int y))");
}

/*!
 *  \brief Return the current position of the trantorien
 * return the current position according t the API's map of the trantorien
 *  \param (void)
 *  \return (int posX, int posY)
 */
int Trantorien::currentPosition(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State *state = vm.getLua();

  std::pair<int, int> position = map_.getCurrentPos();
  lua_pushinteger(state, position.first);
  lua_pushinteger(state, position.second);
  return (2);
}

/*!
 *  \brief Return the current position of the trantorien
 * return the current position according t the API's map of the trantorien
 *  \param (void)
 *  \return (int posX, int posY)
 */
int Trantorien::currentDirection(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_pushinteger(vm.getLua(), map_.getDirection());
  return (1);
}

/*!
 * \brief return one or more value of the inventory
 * Take the integer value of a non updated inventory.
 *  \param (void) or (ItemsGlobal (Exept JOUEUR), ...)
 *  \return if (void) all the values: int else one int for each value
 */
int Trantorien::getInventoryValue(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State *state = vm.getLua();
  std::vector<unsigned int> inventory = inventory_.getInventory();

  if (lua_gettop(state) == 0)
    {
      for (std::vector<unsigned int>::iterator it = inventory.begin(); it != inventory.end(); ++it)
        {
          lua_pushinteger(state, (*it));
        }
      return (inventory.size());
    }
  else
    {
      return (
            variableArgsCall<int, int>(vm,
                             [&](lua_State * state, int object) ->
            int {
            if (object < static_cast<int>(inventory.size()))
              return inventory[object];
            return -1;
      }));
    }
  return (0);
}

/*!
 * \brief expulse a trantorien
 *  Expule all others players on the case.
 *  \param (void)
 *  \return (string) the server's answer.
 */
int Trantorien::expulse(LuaVirtualMachine::VirtualMachine &vm)
{
  std::string ret;

  network_.cmd("expluse");
  ret = this->getline();
  lua_pushstring(vm.getLua(), ret.c_str());
  return 1;
}


/*!
 * \brief Makes one iteration to a direction
 *  Iter to a direction
 *  \param (int x, int y)
 *  \return (void)
 */
int Trantorien::goTo(LuaVirtualMachine::VirtualMachine & vm)
{
  const Position & from = map_.getCurrentPos();
  Position        to;
  UserGlobal::Direction dir = map_.getDirection();
  bool go[4] = {false, false, false, false};

  if (lua_gettop(vm.getLua()) == 2 && lua_isnumber(vm.getLua(), 1) && lua_isnumber(vm.getLua(), 2))
    {
      to.first = lua_tonumber(vm.getLua(), 1);
      to.second = lua_tonumber(vm.getLua(), 2);
    }
  else
    throw TrantorienFailure("Tratorien goTo", "Invalid parameter : (void (int x, int y))");
  if (to.first == map_.getCurrentPos().first && to.second == map_.getCurrentPos().second)
  return 0;
 if (to.second != from.second)
   {
     go[UserGlobal::NORD - 1]  = (to.second < from.second
                                  && from.second - to.second <= map_.getSize().second - (from.second - to.second))
         || to.second - from.second >= map_.getSize().second - (to.second - from.second);
     go[UserGlobal::SUD - 1]   = (to.second > from.second
                                  && to.second - from.second <= map_.getSize().second - (to.second - from.second))
         || from.second - to.second >= map_.getSize().second - (from.second - to.second);
  }
 if (to.first != from.first)
   {
     go[UserGlobal::OUEST - 1] = (to.first < from.first
                                  && from.first - to.first <= map_.getSize().first - (from.first - to.first))
         || to.first - from.first >= map_.getSize().first - (to.first - from.first);
     go[UserGlobal::EST - 1]   = (to.first > from.first
                                  && to.first - from.first <= map_.getSize().first - (to.first - from.first))
         || from.first - to.first >= map_.getSize().first - (from.first - to.first);
  }
 if (go[dir - 1])
   {
     avance(vm);
     return 0;
   }
 if (go[((dir - 1) + 1) % 4])
   {
     droite();
     return 0;
   }
 else
   {
     gauche();
     return 0;
   }
 return 0;
}

/*!
 * \brief return the current level of the trantorien
 *  Return the API's level of the trantorien
 *  \param (void)
 *  \return (int)
 */
int Trantorien::getLevel(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_pushnumber(vm.getLua(), level_);
  return (1);
}

/*!
 * \brief return the missing rock on the current position to elevate.
 *  Return the missing rock on the case to elevate the trantorien
 *  \param (void) or (ItemsGlobal, ...)
 *  \return (int, ...) in order : food, linemate, deraumere, sibur, mendiane, phiras, thystame, player.
 */
int Trantorien::missingRockOnCase(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State *state = vm.getLua();

  if (lua_gettop(state) == 0)
    {
      std::pair<int, int> position = map_.getCurrentPos();
      std::vector<unsigned int> result = map_.caseContent(position);
      int j = 0;
      for (std::vector<unsigned int>::iterator it = result.begin(); it != result.end(); ++it)
        {
          lua_pushinteger(state,  static_cast<int>(levels[level_ - 1][j] - (*it)));
          ++j;
        }
      return (j);
    }
  else
    {
      return (
              variableArgsCall<int, int >(vm,
                                          [&](lua_State * state, int object) ->
                                          int {
                                            int res = -1;
                                            std::pair<int, int> position = map_.getCurrentPos();
                                            std::vector<unsigned int> result = map_.caseContent(position);
                                            if (object <= UserGlobal::JOUEUR && object >= UserGlobal::NOURRITURE)
                                              res = levels[level_ - 1][object] -
                                                result[object];
                                            return (res);
                                          }));
    }
}

/*!
 * \brief return the most missing rock in the inventory
 *  Return the most missing rock in the inventory to elevate the trantorien
 *  \param (void)
 *  \return (Items global except JOUEUR)
 */
int Trantorien::missingRockInInventoryID(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State *state = vm.getLua();
  std::vector<int> tmp;
  std::vector<int>::const_iterator max;
  int       result;

  tmp.resize(inventory_.getInventory().size());
  for (unsigned int i = 0; i < tmp.size(); ++i) {
      tmp[i] = levels[level_ - 1][i] - inventory_.getInventory()[i];
    }

  max = std::max_element(tmp.begin(), tmp.end());
  result = max - tmp.begin();

  if (*max > 0)
    lua_pushinteger(state, result);
  else
    lua_pushinteger(state, -1);
  return (1);
}

/*!
 * \brief return the missing rock on the inventory
 *  Return the missing rock on the inventory to elevate the trantorien
 *  \param (void) or (ItemsGlobal, ...)
 *  \return (int, ...) in order : food, linemate, deraumere, sibur, mendiane, phiras, thystame.
 */
int Trantorien::missingRockInInventory(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State *state = vm.getLua();

  if (lua_gettop(state) == 0)
    {
      std::vector<unsigned int> result = inventory_.getInventory();
      int j = 0;
      for (std::vector<unsigned int>::iterator it = result.begin(); it != result.end(); ++it)
        {
          lua_pushinteger(state, static_cast<int>(levels[level_ - 1][j] - (*it)));
          ++j;
        }
      return (j);
    }
  else
    {
      return (
              variableArgsCall<int, int >(vm,
                                          [&](lua_State * state, int object) ->
                                          int {
                                            int res = -1;
                                            std::vector<unsigned int> result = inventory_.getInventory();
                                            if (object <= UserGlobal::JOUEUR && object >= UserGlobal::NOURRITURE)
                                              res = levels[level_ - 1][object] -
                                                result[object];
                                            return (res);
                                          }));
    }
}

/*!
 * \brief return the closest remembered item
 *  Returns the closest item that the trantorien have seen
 *  \param (void) or (ItemsGlobal, ...)
 *  \return (int x, int y)
 */
int Trantorien::getClosestItem(LuaVirtualMachine::VirtualMachine &vm)
{
  return (
          variableArgsCall<int, std::pair<int, int> >(vm,
                                                      [&](lua_State * state, int object) ->
                                                      std::pair<int, int> {
                                                        std::pair<int, int>result (-1, -1);
                                                        std::pair<int, int> position = map_.getCurrentPos();
                                                        if (object <= UserGlobal::JOUEUR &&
                                                            object >= UserGlobal::NOURRITURE)
                                                          result = map_.getClosestItem(position, object);
                                                        return (result);
                                                      }));
}

/*!
 * \brief return an item coordinates
 *  Returns a random item wich is in the specified range
 *  \param (Item global, int range)
 *  \return (int x, int y)
 */
int Trantorien::getItemWithLength(LuaVirtualMachine::VirtualMachine &vm)
{
  if (lua_gettop(vm.getLua()) == 2 && lua_isnumber(vm.getLua(), 1) && lua_isnumber(vm.getLua(), 2))
    {
      int object = lua_tonumber(vm.getLua(), 1);
      int range =  lua_tonumber(vm.getLua(), 2);
      std::pair<int, int> position = map_.getCurrentPos();
      std::vector<std::pair<int, int> >res = map_.getItemOnRange(position, object, range);

      std::default_random_engine generator;
      std::uniform_int_distribution<int> distribution(0, res.size());
      int pos = distribution(generator);

      if (res.size() != 0)
        {
          lua_pushnumber(vm.getLua(), res[pos].first);
          lua_pushnumber(vm.getLua(), res[pos].second);
        }
      else
        {
          lua_pushnumber(vm.getLua(), -1);
          lua_pushnumber(vm.getLua(), -1);
        }
      return (2);
    }
  else
    throw TrantorienFailure("Tratorien getItemWitchLength",
                            "Invalid parameter : (int, int getItemWithLength(int object, int range))");
}

/*!
 * \brief change the map referential
 *  Change the map referencial with x, y the new 0, 0 and direction global the new "normal" direction
 *  \param (int x, int y, Direction global)
 *  \return (void)
 */
int Trantorien::changeFrame(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State *state = vm.getLua();

  if (lua_gettop(state) >= 3 && lua_isnumber(state, 1) && lua_isnumber(state, 1) && lua_isnumber(state, 3))
    {
      int x = 0, y = 0;
      UserGlobal::Direction dir;

      x = lua_tonumber(state, 1);
      y = lua_tonumber(state, 2);
      dir = static_cast<UserGlobal::Direction>(lua_tonumber(state, 3));
      return (map_.changeFrame(Position(x, y), dir));
    }
  else
    throw TrantorienFailure("Tratorien changeFrame", "Invalid parameter : (int x8 caseContent(int x, int y))");
}

/*!
 * \brief get the rocks missing to elevate from inventory and the current case content
 *   get the rocks missing to elevate from inventory and the current case content
 *  \param (void)
 *  \return (nourriture, linemate, deraumere, sibur, mendiane, phiras, thystame)
 */
int Trantorien::missingToElevate(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State *state = vm.getLua();

  if (!lua_gettop(state))
    {
      std::pair<int, int> position = map_.getCurrentPos();
      std::vector<unsigned int> inventory = inventory_.getInventory();
      std::vector<unsigned int> map = map_.caseContent(position);
      int j = 0;
      for (std::vector<unsigned int>::iterator it = inventory.begin(),
             it1 = map.begin(); it1 != map.end() && it != inventory.end(); ++it, ++it1)
        {
          lua_pushinteger(state,
                          static_cast<int>(levels[level_ - 1][j] - ((*it) + (*it1))));
          ++j;
        }
      return (j);
    }
  else
    {
      return (
              variableArgsCall<int, int >(vm,
                                          [&](lua_State * state, int object) ->
                                          int {
                                            std::pair<int, int> position = map_.getCurrentPos();
                                            std::vector<unsigned int> inventory = inventory_.getInventory();
                                            std::vector<unsigned int> map = map_.caseContent(position);
                                            int res = -1;
                                            if (object <= UserGlobal::JOUEUR)
                                              res = levels[level_ - 1][object] -
                                                (inventory[object] + map[object]);
                                            return (res);
                                          }));
    }
}

int Trantorien::listen(LuaVirtualMachine::VirtualMachine &vm, const Message & msg)
{
  Position    orig(std::make_pair(-1, -1));
  std::string value = "";
  lua_State   *state = vm.getLua();
  UserGlobal::Direction ret = UserGlobal::NONE;

  orig = msg.getReceived();
  ret = msg.getDir()[0] ?
        UserGlobal::NORD : msg.getDir()[1] ?
          UserGlobal::EST : msg.getDir()[2] ?
            UserGlobal::SUD : msg.getDir()[3] ?
            UserGlobal::OUEST : UserGlobal::NONE;
  value = msg.getMessage();
  lua_pushinteger(state, orig.first);
  lua_pushinteger(state, orig.second);
  lua_pushinteger(state, ret);
  lua_pushstring(state, value.c_str());
  return 4;
}

/*!
 * \brief return the last message received
 *   returns the coordinates where message was received, the direction where i came from and the message content
 *  \param (string message_content)
 *  \return (nourriture, linemate, deraumere, sibur, mendiane, phiras, thystame)
 */
int Trantorien::LastMsg(LuaVirtualMachine::VirtualMachine &vm)
{
  Message msg;
  std::string str;

  if (lua_gettop(vm.getLua()) == 1 && lua_isstring(vm.getLua(), 1))
    str = teamname + " " + lua_tostring(vm.getLua(), 1);
  else
    throw TrantorienFailure("Tratorien LastMSG", "Invalid parameter : (string caseContent(string msg)");
  if (!broadcastHistory_.empty())
    {
      std::list<Message>::const_iterator it = std::find_if(broadcastHistory_.begin(),
                                                     broadcastHistory_.end(),
                                                     [&str](const Message & item) -> bool {
                                                     return item.getMessage() == str;
    });
  if (it != broadcastHistory_.end())
    msg = *it;
  broadcastHistory_.clear();
    }
  return listen(vm, msg);
}

/*!
 * \brief test if a message was received
 *   test if a message with specific content was received
 *  \param (string message_content)
 *  \return (boolean)
 */
int Trantorien::messageInQueue(LuaVirtualMachine::VirtualMachine &vm)
{
  if (lua_gettop(vm.getLua()) == 1 && lua_isstring(vm.getLua(), 1))
    {
      std::string   search = teamname + " " + lua_tostring(vm.getLua(), 1);

      std::list<Message>::const_iterator it = std::find_if(broadcastHistory_.begin(), broadcastHistory_.end(), [&search](const Message & msg) -> bool {
          return msg.getMessage() == search;
        });
      lua_pushboolean(vm.getLua(), it != broadcastHistory_.end());
      return 1;
    }
  else
    throw TrantorienFailure("Tratorien messageinqueue", "Invalid parameter : (string messageinqueue(string msg))");
}

/*!
 * \brief count the number of te given message
 *   count the messages with specific content.
 *  \param (string message_content)
 *  \return (int) numbers of contents.
 */
int Trantorien::nbMessageInQueue(LuaVirtualMachine::VirtualMachine &vm)
{
  if (lua_gettop(vm.getLua()) == 1 && lua_isstring(vm.getLua(), 1))
    {
      std::string search = teamname + " " + lua_tostring(vm.getLua(), 1);
      int res = std::count_if(broadcastHistory_.begin(), broadcastHistory_.end(), [&search](const Message & msg) -> bool {
          return msg.getMessage() == search;
        });
      lua_pushinteger(vm.getLua(), res);
      return (1);
    }
  else
    throw TrantorienFailure("Tratorien nbMessageInQueue", "Invalid parameter : (string caseContent(string msg))");
}

int Trantorien::nbMessageInQueue(const std::string &search)
{
  int res = std::count_if(broadcastHistory_.begin(), broadcastHistory_.end(), [&search](const Message & msg) -> bool {
      return msg.getMessage() == search;
    });
  return (res);
}


/*!
 * \brief Return the current return of the server
 *  Return the current return of the server
 *  \param (void)
 *  \return (string) the last answer of the server
 */
int Trantorien::readLine(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_pushstring(vm.getLua(), this->getline().c_str());
    return 1;
}

/*!
 * \brief connect nb player on the map
 *  connect nb new trantorien on the map with the same arguments
 *  \param (int) nb
 *  \return (void)
 */
int Trantorien::connectPlayer(LuaVirtualMachine::VirtualMachine &vm)
{
  pid_t pid;
  int nb = 0;
  lua_State *state = vm.getLua();

  if (lua_gettop(state) == 1 && lua_isnumber(state, 1))
    nb = lua_tointeger(state, 1);
  else
    throw TrantorienFailure("Tratorien connectplayer", "Invalid parameter : (void connectplayer(int nb))");
  for (int i = 0; i < nb; ++i)
    {
      if ((pid = fork()) == -1)
        abort();
      if (pid == 0)
        {
          if (execvp(av_[0], av_) == -1)
            abort();
          exit(0);
        }
    }
  return (0);
}

/*!
 * \brief check how many trantorien can be connected
 *  Return the numbers of available slots on the team
 *  \param (void)
 *  \return (int) nbslots
 */
int Trantorien::canConnectPlayer(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State *state = vm.getLua();
  std::stringstream convert;
  std::string ret;
  int nbr;

  this->cmd("connect_nbr");
  convert <<  this->getline();
  convert >> nbr;
  lua_pushinteger(state, nbr);
  return (1);
}


/*!
 * \brief Make the trantorien lay
 *  Make the trantorien lay and return the serveur answers
 *  \param (void)
 *  \return (string) answer
 */
int Trantorien::lay(LuaVirtualMachine::VirtualMachine &vm)
{
  std::string ret;

  this->cmd("fork");
  ret = this->getline();
  lua_pushstring(vm.getLua(), ret.c_str());
  return (1);
}

/*!
 * \brief a function tu count how any trantorien there is one the team
 *  Return an aproximate result of the number of player (some can be busy and can't answer to the call)
 *  \param (void)
 *  \return (int) nbplayer.
 */
int Trantorien::countPlayer(LuaVirtualMachine::VirtualMachine &vm)
{
  lua_State *state = vm.getLua();
  pid_t		pid = getpid();
  std::stringstream	ss;
  std::string		pidstr;

  ss << pid;
  ss >> pidstr;
  broadcastHistory_.clear();
  this->cmd("broadcast " + teamname + " " + COUNT_PLAYER + " " + pidstr);
  this->getline();
  for (int i = 0; i < 2; ++i) {

      this->cmd("voir");
      this->getline();
    }
  lua_pushinteger(state, nbMessageInQueue(teamname + " " + COUNT_ME + " " + pidstr) + 1);
  return (1);
}
