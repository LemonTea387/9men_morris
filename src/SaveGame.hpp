#ifndef SAVE_GAME_H
#define SAVE_GAME_H
#include <string>
#include <vector>

class Command;
/**
 * Caretaker class for saving games, following the Memento design pattern.
 */
class SaveGame {
 private:
  std::vector<Command*> m_Commands;
  std::string m_FileContents;

 public:
  void AddToSave(const std::string& serialised, Command* command);
  void LoadFromSave(const std::string& filename);
  void SaveGameFile(const std::string& filename);
  SaveGame();
  ~SaveGame();
};

#endif
