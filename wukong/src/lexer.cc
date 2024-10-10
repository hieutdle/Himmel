#include <lexer.h>

bool isLetter(char ch) {
  return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_';
}

bool isDigit(char ch) { return '0' <= ch && ch <= '9'; }

void Lexer::skipWhitespace() {
  while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
    readChar();
  }
}

void Lexer::readChar() {
  if (readPosition >= input.size()) {
    ch = '\0'; // End of input
  } else {
    ch = input[readPosition];
  }
  position = readPosition;
  ++readPosition;
}

// const means that the peekChar() function cannot modify any of the class’s
// member variables, such as input or readPosition
char Lexer::peekChar() const {
  if (readPosition >= input.size()) {
    return '\0';
  }
  return input[readPosition];
}

Token Lexer::nextToken() {
  Token tok;

  skipWhitespace();

  switch (ch) {
  case '=':
    if (peekChar() == '=') {
      readChar();
      tok = Token(EQ, "==");
    } else {
      tok = Token(ASSIGN, ch);
    }
    break;
  case '+':
    tok = Token(PLUS, ch);
    break;
  case '-':
    tok = Token(MINUS, ch);
    break;
  case '!': {
    if (peekChar() == '=') {
      readChar();
      tok = Token(NEQ, "!=");
    } else {
      tok = Token(BANG, ch);
    }
    break;
  }
  case '/':
    tok = Token(SLASH, ch);
    break;
  case '*':
    tok = Token(ASTERISK, ch);
    break;
  case '<':
    tok = Token(LT, ch);
    break;
  case '>':
    tok = Token(GT, ch);
    break;
  case ';':
    tok = Token(SEMICOLON, ch);
    break;
  case ',':
    tok = Token(COMMA, ch);
    break;
  case '(':
    tok = Token(LPAREN, ch);
    break;
  case ')':
    tok = Token(RPAREN, ch);
    break;
  case '{':
    tok = Token(LBRACE, ch);
    break;
  case '}':
    tok = Token(RBRACE, ch);
    break;
  case '\0': // End of file/input
    tok.literal = "";
    tok.type = END;
    break;
  default: {
    if (isLetter(ch)) {
      tok.literal = readIdentifier();
      tok.type = lookupIdent(tok.literal);
      return tok;
    }
    if (isDigit(ch)) {
      tok.literal = readNumber();
      tok.type = INT;
      return tok;
    }
    tok = Token(ILLEGAL, ch);
  }
  }

  readChar(); // Move to the next character
  return tok;
}

std::string Lexer::readIdentifier() {
  size_t start = position;
  while (isLetter(ch)) {
    readChar();
  }
  return input.substr(start, position - start);
}

std::string Lexer::readNumber() {
  size_t start = position;
  while (isDigit(ch)) {
    readChar();
  }
  return input.substr(start, position - start);
}
