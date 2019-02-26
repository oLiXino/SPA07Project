#pragma once

#include "PQLParser.h"
#include <string>

struct QueryToken {
  TokenType type;
  std::string name;
  QueryToken() : type(TokenType::Keyword), name(""){};
  QueryToken(const TokenType type, const std::string &name)
      : type(type), name(name) {}
};
