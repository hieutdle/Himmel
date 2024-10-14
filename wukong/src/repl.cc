#include <iostream>
#include <lexer.h>
#include <string>
#include <token.h>

namespace wukong {
const std::string PROMPT = ">> ";

void Start(std::istream &in, std::ostream &out) {
  std::string line;

  while (true) {
    // Print the prompt and get user input
    out << PROMPT;
    if (!std::getline(in, line)) {
      return;
    }

    // Initialize the lexer with the input line
    Lexer lexer(line);

    // Process tokens until EOF is reached
    Token tok = lexer.nextToken();
    while (tok.type != END) {
      // Output the token's details (equivalent to Go's fmt.Printf)
      out << "Token Type: " << tok.type << ", Literal: " << tok.literal
          << std::endl;
      tok = lexer.nextToken();
    }
  }
}
} // namespace wukong
