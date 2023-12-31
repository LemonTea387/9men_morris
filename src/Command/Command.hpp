#ifndef COMMAND_H
#define COMMAND_H

#include <string>

#include "../Player.hpp"
#include "../Tile.hpp"

class SaveGame;

/**
 * The Command class acts as a base class for sophisticated Commands to perform
 * specific functionality on the GameBoard. This is used for utilization of
 * Command Pattern in the game, such that each 'move' is represented as an
 * atomic Command, which can be easily executed by the GameBoard. It acts as a
 * base template for any move to be represented in a way that GameBoard can
 * Execute without knowing specifically what type of move it is executing and is
 * expecting. The Command class is also an "Originator" in the Memento file
 * pattern.
 */
class Command {
 public:
  typedef Tile* TilePtr;
  typedef SaveGame* SaveGamePtr;
  /**
   * Command Constructor.
   */
  Command(TilePtr tile, Player* player)
      : m_AffectedTile{tile}, m_Player{player} {};

  /**
   * Virtual Command Destructor
   */
  virtual ~Command() {}

  /**
   * Getter for the affected tile of the Command, useful for checking what this
   * command did to the affected Tile.
   */
  TilePtr GetAffectedTile() { return m_AffectedTile; };

  /**
   * The main abstract Execute function, this is what GameBoard will call to
   * execute this Command. The specific implementations of this function has to
   * be done in any Derived Command class.
   */
  virtual void Execute() = 0;

  /**
   * The main abstract Undo function, this is what GameBoard will call to undo
   * this Command. The specific implementations of this function has to be done
   * in any Derived Command class.
   */
  virtual void Undo() = 0;

  /**
   * Adds command to the SaveGame memento class.
   */
  virtual void AddToSaveGame(SaveGamePtr) = 0;

  /**
   * Restores a Command from a string sequence that was previously saved
   * via AddToSaveGame.
   */
  virtual void RestoreFromSave(std::string save, GameBoard* gb) = 0;

 protected:
  /**
   * The affected tile's pointer.
   */
  TilePtr m_AffectedTile{nullptr};
  /**
   * The player affected by the Command.
   */
  Player* m_Player;
};

#endif
