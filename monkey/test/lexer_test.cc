#include <gtest/gtest.h>
#include <lexer.h>
#include <token.h>

using namespace monkey;

class LexerTest : public testing::Test {};

TEST_F(LexerTest, TestNextToken) {
  const std::string input = R"(let five = 5;
let ten = 10;

let add = fn(x, y) {
	x + y;
};

let result = add(five, ten);
!-/*5;
5 < 10 > 5;

if (5 < 10) {
	return true;
} else {
	return false;
}

10 == 10;
10 != 9;
)";

  struct Test {
    TokenType expectedType;
    std::string expectedLiteral;
  };

  const std::vector<Test> tests = {
      {LET, "let"},      {IDENT, "five"},    {ASSIGN, "="},
      {INT, "5"},        {SEMICOLON, ";"},   {LET, "let"},
      {IDENT, "ten"},    {ASSIGN, "="},      {INT, "10"},
      {SEMICOLON, ";"},  {LET, "let"},       {IDENT, "add"},
      {ASSIGN, "="},     {FUNCTION, "fn"},   {LPAREN, "("},
      {IDENT, "x"},      {COMMA, ","},       {IDENT, "y"},
      {RPAREN, ")"},     {LBRACE, "{"},      {IDENT, "x"},
      {PLUS, "+"},       {IDENT, "y"},       {SEMICOLON, ";"},
      {RBRACE, "}"},     {SEMICOLON, ";"},   {LET, "let"},
      {IDENT, "result"}, {ASSIGN, "="},      {IDENT, "add"},
      {LPAREN, "("},     {IDENT, "five"},    {COMMA, ","},
      {IDENT, "ten"},    {RPAREN, ")"},      {SEMICOLON, ";"},
      {BANG, "!"},       {MINUS, "-"},       {SLASH, "/"},
      {ASTERISK, "*"},   {INT, "5"},         {SEMICOLON, ";"},
      {INT, "5"},        {LT, "<"},          {INT, "10"},
      {GT, ">"},         {INT, "5"},         {SEMICOLON, ";"},
      {IF, "if"},        {LPAREN, "("},      {INT, "5"},
      {LT, "<"},         {INT, "10"},        {RPAREN, ")"},
      {LBRACE, "{"},     {RETURN, "return"}, {TRUE, "true"},
      {SEMICOLON, ";"},  {RBRACE, "}"},      {ELSE, "else"},
      {LBRACE, "{"},     {RETURN, "return"}, {FALSE, "false"},
      {SEMICOLON, ";"},  {RBRACE, "}"},      {INT, "10"},
      {EQ, "=="},        {INT, "10"},        {SEMICOLON, ";"},
      {INT, "10"},       {NE, "!="},         {INT, "9"},
      {SEMICOLON, ";"},  {END, ""}};

  Lexer lexer(input);

  for (size_t i = 0; i < tests.size(); ++i) {
    Token tok = lexer.nextToken();

    // Check if the token type matches the expected type
    EXPECT_EQ(tok.type, tests[i].expectedType)
        << "tests[" << i << "] - TokenType wrong. token=" << tok.literal
        << ". expected=" << tests[i].expectedType << ", got=" << tok.type;

    // Check if the token literal matches the expected literal
    EXPECT_EQ(tok.literal, tests[i].expectedLiteral)
        << "tests[" << i << "] - literal wrong. token=" << tok.literal
        << ". expected=" << tests[i].expectedLiteral << ", got=" << tok.literal;
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  // Set GoogleTest to stop on first failure
  GTEST_FLAG_SET(break_on_failure, true);

  return RUN_ALL_TESTS();
}
