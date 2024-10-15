// main.cc
#include <iostream>
#include <pwd.h>
#include <repl.h>
#include <unistd.h>

int main() {
  // Get the current user's username
  const passwd *pw = getpwuid(getuid());
  const std::string userName = pw ? pw->pw_name : "User";

  // Welcome message
  std::cout << "Hello " << userName
            << "! This is the Monkey programming language!" << std::endl;
  std::cout << "Feel free to type in commands" << std::endl;

  // Start the REPL (Read-Eval-Print Loop)
  monkey::Start(std::cin, std::cout);

  return 0;
}
