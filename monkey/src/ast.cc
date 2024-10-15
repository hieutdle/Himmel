#include <ast.h>
#include <string>
#include <utility>

namespace monkey {

std::string Statement::tokenLiteral() { return ""; }

std::string Expression::tokenLiteral() { return ""; }

std::string Program::tokenLiteral() {
  if (statements.empty()) {
    return "";
  }
  return statements[0]->tokenLiteral();
}

Identifier::Identifier(Token t, std::string s)
    : token{std::move(t)}, value{std::move(s)} {}
std::string Identifier::tokenLiteral() { return token.literal; }

LetStatement::LetStatement(Token t) : token{std::move(t)} {}
std::string LetStatement::tokenLiteral() { return token.literal; }

} // namespace monkey
