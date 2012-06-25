//
// Map.hh for  in /home/carpen_t/projets/syst_Unix/Zappy/ia
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon Jun 25 13:50:09 2012 thibault carpentier
// Last update Mon Jun 25 15:38:37 2012 thibault carpentier
//

#ifndef _MAP_H_
# define _MAP_H_

#include <vector>
#include <string>

class Map
{
private:
  std::pair<int, int>currentPos_;
  std::vector<std::pair< std::string ,std::pair<int, int> > >map;

private:
  Map(Map const &);
  Map& operator=(Map const &);
public:
  Map(void);
  ~Map(void);

  void update(std::string &values);
};

#endif /*!_MAP_H_*/
