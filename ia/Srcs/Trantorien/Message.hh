// Message.hh

#ifndef MESSAGE_HH__
#define MESSAGE_HH__

#include <vector>
#include "Ressources.hh"
#include "Map.hh"

class Message {
public:
  Message();
  Message(std::string init, const Position & position, UserGlobal::Direction dir,
          const Position & mapSize);
  ~Message();
  Message(const Message & orig);
  Message & operator=(const Message & orig);

  const std::string & getMessage() const;
  const Position    & getReceived() const;
  const std::vector<bool> & getDir() const;

private:
  Position              received_;
  std::vector<bool>     dir_;
  std::string           message_;
};

#endif // MESSAGE_HH__
