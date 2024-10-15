#ifndef PARSER_H
#define PARSER_H
#include <ast.h>
#include <lexer.h>
#include <memory>

namespace monkey {
class Parser {
public:
  Parser() = delete;
  explicit Parser(Lexer *l);

  /**
   * @brief get the next token
   *
   */
  void nextToken();

  /**
   * @brief Parse the program
   *
   * @return unique_ptr<Program>
   */
  std::unique_ptr<Program> parseProgram();

  /**
   * @brief Parse the statement
   *
   * @return unique_ptr<Statement>
   */
  std::unique_ptr<Statement> parseStatement();

  /**
   * @brief Parse the let statement
   *
   * @return unique_ptr<LetStatement>
   */
  std::unique_ptr<LetStatement> parseLetStatement();

  /**
   * @brief A helper function to tell whether
   * `currentToken == t`
   *
   */
  bool currentTokenIs(const TokenType &t) const;

  /**
   * @brief A helper function to tell whether
   * `peekToken == t`
   *
   */
  bool peekTokenIs(const TokenType &t) const;

  /**
   * @brief If `peekTokenIs(t)` is true, call
   * `nextToken`
   *
   */
  bool expectPeek(const TokenType &t);

private:
  Lexer *lexer;
  Token currentToken; // current token
  Token peekToken;    // next token
};
} // namespace monkey
#endif // PARSER_H
