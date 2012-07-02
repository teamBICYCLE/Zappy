// Lexeme.hh

#ifndef _LEXEME_HH_
# define _LEXEME_HH_

# include <fstream>
# include <iostream>
# include <list>
# include <map>
# include <string>

namespace FSM {
class Lexeme {
  enum LexType  {WORD, EOL, END, STATE, TRANSITION,MODULE, AUTOMATON, COLON,
                 ARROW, SEMICOLON, O_HOOK, C_HOOK};
public:
  Lexeme(const std::string & item);
  Lexeme(const Lexeme & orgin);
  Lexeme &    operator=(const Lexeme & orig);
  ~Lexeme();

  bool                        is(LexType type) const;


  static std::list<Lexeme>    lex(std::ifstream & input);
  static std::map<LexType, std::string> regexMap_;

private:
  std::list<LexType>    types_;
  std::string           value_;

  // debug fct. To delete
private:
  void    printMatchs() const;
};
}

#endif // _LEXEME_HH_
