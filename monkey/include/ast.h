#ifndef AST_H
#define AST_H
#include <memory>
#include <string>
#include <token.h>
#include <vector>

namespace monkey {
/**
 * @brief Every node in the AST has to implement
 * this abstract class.
 *
 */
class Node {
public:
  /**
   * @brief the literal value of the token
   *
   * @return std::string
   */
  virtual std::string tokenLiteral() = 0;

  virtual ~Node() = default;
};

/**
 * @brief Represent the statements, for example,
 * `let a = 8;` is a statement. It should inherit
 * from Node.
 */
class Statement : public Node {
public:
  std::string tokenLiteral() override;
};

/**
 * @brief Represent the expression, for example,
 * `let a = 8`. `a` is the expression and also,
 * `8` is the expression. It should inherit from
 * Node.
 */

class Expression : public Node {
public:
  std::string tokenLiteral() override;
};

/**
 * @brief This class is the entry point of the AST.
 * it composes a consecutive statements.
 *
 */
class Program : public Node {
public:
  std::string tokenLiteral() override;

  std::vector<std::unique_ptr<Statement>> statements{};
};

/**
 * @brief Identifier class. It is an expression.
 * It is inherited from `Expression` class.
 *
 */
class Identifier : public Expression {
public:
  Identifier() = default;
  Identifier(Token, std::string);

  std::string tokenLiteral() override;

  Token token;
  std::string value;
};

/**
 * @brief LetStatement represents let statement,
 * for example `let a = 8`.
 *
 */
class LetStatement : public Statement {
public:
  LetStatement() = default;

  explicit LetStatement(Token);

  std::string tokenLiteral() override;

  std::unique_ptr<Identifier> name;
  std::unique_ptr<Expression> value;
  Token token;
};

} // namespace monkey
#endif // AST_H
