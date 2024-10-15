// parser_test.cpp
#include "gtest/gtest.h"
#include <ast.h>
#include <lexer.h>
#include <parser.h>
#include <string>
#include <vector>

#include "test_utils.h"

using namespace monkey;

class ParserTest : public BasicTest{
protected:
  static void TestLetStatement(Statement *stmt,
                               const std::string &expectedIdentifier) {
    // Check if the statement is of type LetStatement and has the "let" token
    ASSERT_EQ(stmt->tokenLiteral(), "let")
        << "tokenLiteral() should return 'let'.";

    // Perform a dynamic cast to check if the statement is of type
    // `LetStatement`.
    const auto *letStmt = dynamic_cast<const LetStatement *>(stmt);
    ASSERT_NE(letStmt, nullptr) << "Statement is not a LetStatement.";

    // Check the identifier value in the LetStatement (name)
    EXPECT_EQ(letStmt->name->value, expectedIdentifier)
        << "LetStatement Name is incorrect.";

    // Check if the token literal for the name is correct
    EXPECT_EQ(letStmt->name->tokenLiteral(), expectedIdentifier)
        << "LetStatement tokenLiteral is incorrect.";
  }
};

TEST_F(ParserTest, TestLetStatements) {
  // Input source code to parse
  const std::string input = R"(
        let x = 5;
        let y = 10;
        let foobar = 838383;
    )";

  // Create a lexer and parser based on the input
  Lexer lexer(input);
  Parser parser(&lexer);

  // Call the parser's parseProgram() function
  const std::unique_ptr<Program> program = parser.parseProgram();

  // Test for null return value
  ASSERT_NE(program, nullptr) << "parseProgram() returned nullptr.";

  // Test the number of statements parsed
  ASSERT_EQ(program->statements.size(), 3)
      << "program.statements does not contain 3 statements.";

  // Expected identifiers from the parsed `let` statements
  const std::vector<std::string> expectedIdentifiers = {"x", "y", "foobar"};

  // Loop over each expected identifier and test the corresponding statement
  for (size_t i = 0; i < expectedIdentifiers.size(); ++i) {
    TestLetStatement(program->statements[i].get(), expectedIdentifiers[i]);
  }
}
