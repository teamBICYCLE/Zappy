// Lexeme.cpp

#include "Lexeme.hh"

#include <algorithm>
#include <boost/regex.hpp>

using namespace FSM;

std::map<Lexeme::LexType, std::string>  Lexeme::regexMap_ = {
  {WORD, "[a-zA-Z0-9]+"},
  {EOL, "\n"},
  {END, "end"},
  {STATE, "state"},
  {TRANSITION, "transition"},
  {MODULE, "module"},
  {AUTOMATON, "automaton"},
  {COLON, ":"},
  {ARROW, "->"},
  {SEMICOLON, ";"},
  {O_HOOK, "\\["},
  {C_HOOK, "]"}
};

Lexeme::Lexeme(const std::string & item)
  : value_(item)
{
  std::for_each(regexMap_.begin(), regexMap_.end(),
                [&](std::pair<LexType, std::string> obj) -> void {
      boost::regex regex(obj.second);

      std::cout << "test: " << obj.second  << std::endl;
      if (boost::regex_match(item, regex))
        this->types_.push_back(obj.first);
  });
}

Lexeme::Lexeme(const Lexeme &orig)
  : types_(orig.types_), value_(orig.value_)
{
}

Lexeme &Lexeme::operator =(const Lexeme &orig)
{
  if (this != &orig)
    {
      this->types_ = orig.types_;
      this->value_ = orig.value_;
    }
  return *this;
}

Lexeme::~Lexeme()
{
}

bool Lexeme::is(Lexeme::LexType type) const
{
  return std::find(types_.begin(), types_.end(), type) != types_.end();
}

void Lexeme::printMatchs() const
{
  std::cout << "lex " << value_ << std::endl;
  std::for_each(types_.begin(), types_.end(), [](LexType type) -> void
  {std::cout << "match: " << regexMap_[type] << std::endl;}
  );
}

std::list<Lexeme> Lexeme::lex(std::ifstream &input)
{
  std::list<Lexeme> list;
  std::string       item;

  while (input >> item)
    {
      Lexeme  lexeme(item);

      list.push_back(lexeme);
    }
  std::for_each(
        list.begin(), list.end(),
        [](Lexeme e) -> void {e.printMatchs();}
  );
  return list;
}
