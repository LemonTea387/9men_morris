#include "WinObserver.hpp"

#include <memory>

#include "../GameBoard.hpp"
#include "../Scene/WinScene.hpp"

namespace {
/**
 * A win function that can be called for the specific Player to Win, for ease of
 * use in the Notify() function of WinObserver.
 */
void Win(Player* player) {
  // Adds a new WinScene on top with the right Winner.
  Game::GetInstance().PushScene(std::make_unique<WinScene>(
      player->occupation == Token::Occupation::PEPE ? WinnerType::PEPE
                                                    : WinnerType::DOGE));
}
}  // namespace

WinObserver::WinObserver(GameBoard* gb) : Observer::Observer(gb) {}

void WinObserver::Notify(Tile* tileAffected) {
  auto currPlayer{m_Gameboard->GetCurrPlayer()};
  auto opponentPlayer{m_Gameboard->GetOpponentPlayer()};
  // Case 1 : Opponent has < 3 tiles left
  if (opponentPlayer->left < 3) {
    Win(currPlayer);
  }
  // Case 2 : It is currently move phase for opponent (Opponent has placed all
  // tokens), and opponent does not have valid moves
  // Here it relies on the MillCapture flag, as a special case of turn from the
  // GameBoard, as that will trigger a CAPTURE phase and will not progress to
  // the opponent in the next turn.
  if (!(m_Gameboard->GetHasMillCapture()) && opponentPlayer->placed == 9) {
    // Check until found at least 1 valid move
    bool validMoves = false;
    // Check through every tile of the opponent
    for (const auto tile : m_Gameboard->GetPlayerTiles(opponentPlayer)) {
      // If there's any valid moves from this token, it is not a win.
      if (m_Gameboard
              ->CalculateValidMoves(GameBoard::MOVE, opponentPlayer, tile)
              .size() > 0) {
        validMoves = true;
        break;
      }
    }

    if (!validMoves) {
      Win(currPlayer);
    }
  }
}
