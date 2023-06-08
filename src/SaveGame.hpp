#ifndef SAVE_GAME_H
#define SAVE_GAME_H
#include <memory>
#include <stack>
#include <string>
#include <vector>

class Command;
class GameBoard;
/**
 * Caretaker class for saving games, following the Memento design pattern.
 */
class SaveGame {
 private:
  typedef std::unique_ptr<Command> CommandPtr;
  typedef std::vector<CommandPtr> CommandPtrStack;

  /*
  * To store the commands previously called.
  */
  CommandPtrStack* m_Commands;

  /**
   * Pointer to the GameBoard the GameSave belongs to for communicating 
   * with the GameBoard.
   */
  GameBoard* m_GameBoard;

  /*
  * A string as buffer for file content.
  */
  std::vector<std::string> m_FileContents;

  /*
  * This deserialize a string, create it's corresponding command, the
  * add it to stack.
  */
  void AddCommandFromString(const std::string& line);

 public:
  /*
  * This function aappends a serializedstring into accumulated seralized 
  * strings.
  */
  void AddToSave(const std::string& serialised);

  /*
  * This function loads a previous saved game state from a text file 
  * with name 'filename'.
  */
  void LoadFromSave(const std::string& filename);

  /*
  * This function save current game state to a text file with name 
  * 'filename'.
  */
  void SaveGameFile(const std::string& filename);

  /*
  * SaveGame constructor, it uses the gameboard pointer to communicate with the
   * gameboard directly.
  */
  SaveGame(GameBoard* gb);

  /*
  * SaveGame destructor.
  */
  ~SaveGame();
};

#endif
