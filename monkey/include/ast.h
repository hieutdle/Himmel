#ifndef AST_H
#define AST_H
#include <memory>
#include <string>
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
 * `let a = 3;` is a statement. It should inherit
 * from Node.
 */
class Statement : public Node {
public:
  std::string tokenLiteral() override;
};

/**
 * @brief Represent the expression, for example,
 * `let a = 3`. `a` is the expression and also,
 * `3` is the expression. It should inherit from
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
  std::vector<std::unique_ptr<Statement>> statements{};

  std::string tokenLiteral() override;
};
} // namespace monkey
#endif // AST_H
