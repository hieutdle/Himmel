#include <parser.h>

namespace monkey {
Parser::Parser(Lexer *l) : lexer{l} {
  // Read two tokens, set `currentToken` and `peekToken`.
  nextToken();
  nextToken();
}

void Parser::nextToken() {
  currentToken = peekToken;
  peekToken = lexer->nextToken();
}

std::unique_ptr<Program> Parser::parseProgram() {
  auto program = std::make_unique<Program>();

  // Keep parsing statements until we hit EOF.
  while (currentToken.type != END) {
    // Parse the current statement.
    if (auto stmt = parseStatement()) {
      program->statements.push_back(std::move(stmt));
    }
    nextToken();
  }

  return std::move(program);
}

std::unique_ptr<Statement> Parser::parseStatement() {
  if (currentToken.type == LET) {
    return std::move(parseLetStatement());
  }
  return nullptr;
}

std::unique_ptr<LetStatement> Parser::parseLetStatement() {
  // Create a new LetStatement and set its token to the current token
  auto stmt = std::make_unique<LetStatement>(currentToken);

  // Ensure the next token is an identifier
  if (!expectPeek(IDENT)) {
    return nullptr; // Return null if the expected token is not found
  }

  // Create the identifier and set its token and value
  stmt->name = std::make_unique<Identifier>(currentToken, currentToken.literal);

  // Ensure the next token is the assignment operator
  if (!expectPeek(ASSIGN)) {
    return nullptr; // Return null if the expected token is not found
  }

  // Skipping the expression parsing until we encounter a semicolon
  while (!currentTokenIs(SEMICOLON)) {
    nextToken();
  }

  return stmt; // Return the parsed LetStatement
}

bool Parser::currentTokenIs(const TokenType &t) const {
  return currentToken.type == t;
}

bool Parser::peekTokenIs(const TokenType &t) const {
  return peekToken.type == t;
}

bool Parser::expectPeek(const TokenType &t) {
  if (peekTokenIs(t)) {
    nextToken();
    return true;
  }
  return false;
}
} // namespace monkey