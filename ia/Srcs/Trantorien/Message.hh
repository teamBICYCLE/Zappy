// Message.hh

#ifndef MESSAGE_HH__
#define MESSAGE_HH__

#include "Ressources.hh"
#include "Map.hh"

class Message {
public:
  Message();
  Message(std::string init, const Position & position, UserGlobal::Direction dir);
  ~Message();
  Message(const Message & orig);
  Message & operator=(const Message & orig);

  const std::string & getMessage() const;
  const Position    & getReceived() const;
  const Position    & getFrom() const;

private:
  Position    received_;
  Position    from_;
  std::string message_;
};

#endif // MESSAGE_HH__
