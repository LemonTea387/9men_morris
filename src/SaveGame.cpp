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

void SaveGame::PopSavedCommand() { m_FileContents.pop_back(); }

void SaveGame::LoadFromSave(const std::string &filename) {
  // Clear string and stack
  m_FileContents.clear();
  while (!m_Commands->empty()) {
    m_Commands->top()->Undo();
    m_Commands->pop();
  }

  std::ifstream inputfile{filename};
  std::cout << "Loading file " << filename << std::endl;

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
  std::cout << "Line: " << line << "\n";
  command->RestoreFromSave(line, m_GameBoard);
  m_Commands->push(std::unique_ptr<Command>(command));
  m_Commands->top()->Execute();
  m_GameBoard->ProgressTurn();
  m_GameBoard->HighlightValidMoves();
}

void SaveGame::SaveGameFile(const std::string &filename) {
  std::ofstream outfile{filename.c_str()};

  if (!outfile) {
    std::cerr << "Could not access file " << filename << "!" << std::endl;
    return;
  }

  for (const auto s : m_FileContents) outfile << s << "\n";
}

SaveGame::SaveGame(std::stack<std::unique_ptr<Command>> *cps, GameBoard *gb)
    : m_Commands(cps), m_GameBoard(gb) {}
SaveGame::~SaveGame() {}
