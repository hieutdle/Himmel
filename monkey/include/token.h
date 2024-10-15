#ifndef TOKEN_H
#define TOKEN_H
#include <unordered_map>

namespace monkey {
// typedef std::string TokenType
using TokenType = std::string;

/**
 * @brief Token is a data structure which represents the token.
 * It has two fields, one is its type, another is its literal.
 * They are nearly the same.
 */
class Token {
public:
  Token() = default;
  Token(TokenType type, std::string literal)
      : type(std::move(type)), literal(std::move(literal)) {}
  Token(TokenType type, const char ch)
      : type(std::move(type)), literal(std::string(1, ch)) {}

  TokenType type;
  std::string literal;
};

extern std::unordered_map<std::string, TokenType> keywords;

TokenType lookupIdent(std::string &ident);

const TokenType ILLEGAL = "ILLEGAL"; // a token we don't know
const TokenType END =
    "END"; // end of file, notice that the origin EOF has been taken in C++

// Identifiers + literals
const TokenType IDENT = "IDENT"; // add, foobar, x, y, ...
const TokenType INT = "INT";     // 123456

// Operators
const TokenType ASSIGN = "=";
const TokenType PLUS = "+";
const TokenType MINUS = "-";
const TokenType BANG = "!";
const TokenType ASTERISK = "*";
const TokenType SLASH = "/";

const TokenType LT = "<";
const TokenType GT = ">";

const TokenType EQ = "==";
const TokenType NE = "!=";

// Delimiters
const TokenType COMMA = ",";
const TokenType SEMICOLON = ";";

const TokenType LPAREN = "(";
const TokenType RPAREN = ")";
const TokenType LBRACE = "{";
const TokenType RBRACE = "}";

// Keywords
const TokenType FUNCTION = "FUNCTION";
const TokenType LET = "LET";
const TokenType TRUE = "TRUE";
const TokenType FALSE = "FALSE";
const TokenType IF = "IF";
const TokenType ELSE = "ELSE";
const TokenType RETURN = "RETURN";
} // namespace monkey

#endif // TOKEN_H
