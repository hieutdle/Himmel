#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <token.h>

class Lexer {
public:
  Lexer() = delete; // you cannot create a Lexer object without passing
                    // arguments (i.e., Lexer lexer)
  explicit Lexer(std::string i)
      : input(std::move(i)), position{}, readPosition{}, ch{} {
    readChar();
  }
  Lexer(const Lexer &) = delete; // deletes the copy constructor
  Lexer(Lexer &&) = delete;      // deletes the move constructor

  Token nextToken();            // Returns the next token from the input
  void readChar();              // Advances to the next character
  std::string readIdentifier(); // Reads an identifier
  std::string readNumber();     // Reads a number
  void skipWhitespace();        // Skips whitespace characters
  char peekChar() const;        // Peeks at the next character without advancing

private:
  std::string input;   // The source input string
  size_t position;     // Current position in input (points to current char)
  size_t readPosition; // Current reading position in input (after current char)
  char ch;             // Current character under examination
};

#endif // LEXER_H
