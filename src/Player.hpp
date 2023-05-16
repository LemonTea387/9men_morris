#ifndef PLAYER_H
#define PLAYER_H

#include "Token.hpp"

struct Player {
  Token::Occupation occupation;
  int placed{0};
  int left{9};
};

#endif
