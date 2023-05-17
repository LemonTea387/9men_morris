#include "WinObserver.hpp"

#include <memory>

#include "../GameBoard.hpp"
#include "../Scene/WinScene.hpp"

namespace {
void Win(Player* player) {
  Game::GetInstance().PopScene();
  Game::GetInstance().PushScene(std::make_unique<WinScene>(
      player->occupation == Token::Occupation::PEPE ? WinnerType::PEPE
                                                    : WinnerType::DOGE));
}
}  // namespace

WinObserver::WinObserver(GameBoard* gb) : Observer::Observer(gb) {}

void WinObserver::Notify(Tile* tileAffected) {
  // Case 1 : Opponent has < 3 tiles left
  if (m_Gameboard->GetOpponentPlayer()->left < 3) {
    // WIN?
    Win(m_Gameboard->GetCurrPlayer());
  }
  // Case 2 : It is currently move phase for opponent, and opponent can't move
  if (!(m_Gameboard->GetMillCapture()) &&
      m_Gameboard->GetState() == GameBoard::MOVE) {
    // Check until found at least 1 valid move
    bool validMoves = false;
    for (const auto& tile :
         m_Gameboard->GetPlayerTiles(m_Gameboard->GetOpponentPlayer())) {
      if (m_Gameboard->CalculateValidMoves(m_Gameboard->GetState(), tile)
              .size() > 0) {
        validMoves = true;
        break;
      }
    }

    if (!validMoves) {
      // WIN?
      Win(m_Gameboard->GetCurrPlayer());
    }
  }
}
