#ifndef PLAYER_H
#define PLAYER_H

#include "Token.hpp"

/**
 * The simple Player's data representation that stores specific player data such
 * as player's occupation(the character selected), and placement/captured count.
 */
struct Player {
  /**
   * This represents the identity of the Player
   */
  Token::Occupation occupation;

  /**
   * How many tokens have the player placed.
   */
  int placed{0};

  /**
   * The player has X tokens left, this may be changed to captured to record the
   * amount of tokens being captured instead.
   */
  int left{9};
};

#endif
