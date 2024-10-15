#include <string>
#include <token.h>
#include <unordered_map>

namespace monkey {
std::unordered_map<std::string, TokenType> keywords({
    {"let", LET},
    {"fn", FUNCTION},
    {"true", TRUE},
    {"false", FALSE},
    {"if", IF},
    {"else", ELSE},
    {"return", RETURN},
});

TokenType lookupIdent(std::string &ident) {
  if (!keywords.contains(ident))
    return IDENT;
  return keywords[ident];
}

} // namespace monkey
