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
  typedef std::stack<CommandPtr> CommandPtrStack;
  CommandPtrStack* m_Commands;
  GameBoard* m_GameBoard;
  std::vector<std::string> m_FileContents;

  void AddCommandFromString(const std::string& line);

 public:
  void AddToSave(const std::string& serialised);
  void PopSavedCommand();
  void LoadFromSave(const std::string& filename);
  void SaveGameFile(const std::string& filename);

  std::vector<std::string> GetFileContents() const { return m_FileContents; }
  SaveGame(std::stack<std::unique_ptr<Command>>* cps, GameBoard* gb);
  ~SaveGame();
};

#endif
