#include "SaveGame.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Command/CaptureCommand.hpp"
#include "Command/Command.hpp"
#include "Command/MoveCommand.hpp"
#include "Command/PlaceCommand.hpp"
#include "GameBoard.hpp"

void SaveGame::AddToSave(const std::string &serialised) {
  m_FileContents.push_back(serialised);
}

void SaveGame::LoadFromSave(const std::string &filename) {
  // Clear string and stack
  m_FileContents.clear();
  while (!m_Commands->empty()) {
    m_Commands->back()->Undo();
    m_Commands->pop_back();
  }

  std::ifstream inputfile{filename};

  std::string line;
  while (inputfile) {
    std::getline(inputfile, line);
    if (line.size() > 0) {
      m_FileContents.push_back(line);
      AddCommandFromString(line);
    }
  }
}

void SaveGame::AddCommandFromString(const std::string &line) {
  std::stringstream stream;
  stream << line;
  Command *command;

  switch (line.at(0)) {
    case 'P':
      command = new PlaceCommand(nullptr, nullptr);
      break;
    case 'C':
      command = new CaptureCommand(nullptr, nullptr);
      break;
    case 'M':
      command = new MoveCommand(nullptr, nullptr, nullptr);
      break;

    default:
      return;
  }
  command->RestoreFromSave(line, m_GameBoard);
  m_GameBoard->ExecuteCommand(command);
  m_GameBoard->ProgressTurn();
  m_GameBoard->HighlightValidMoves();
}

void SaveGame::SaveGameFile(const std::string &filename) {
  m_FileContents.clear();
  for (auto &command : *m_Commands) {
    command->AddToSaveGame(this);
  }
  std::ofstream outfile{filename.c_str()};

  if (!outfile) {
    std::cerr << "Could not access file " << filename << "!" << std::endl;
    return;
  }

  for (const auto s : m_FileContents) outfile << s << "\n";
}

SaveGame::SaveGame(GameBoard *gb)
    : m_Commands(&(gb->m_CommandsHistory)), m_GameBoard(gb) {}
SaveGame::~SaveGame() {}
