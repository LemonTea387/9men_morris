#include "SaveGame.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Command/Command.hpp"

namespace {}

void SaveGame::AddToSave(const std::string &serialised) {
  m_FileContents.push_back(serialised);
}

void SaveGame::PopSavedCommand() { m_FileContents.pop_back(); }

void SaveGame::LoadFromSave(const std::string &filename) {
  // Clear stack
  while (!m_Commands->empty()) {
    m_Commands->pop();
  }

  std::ifstream inputfile{filename};

  std::string line;
  while (inputfile) {
    std::getline(inputfile, line);
    AddCommandFromString(line);
  }
}

void SaveGame::AddCommandFromString(const std::string &line) {
  std::stringstream stream;
  stream << line;
}

void SaveGame::SaveGameFile(const std::string &filename) {
  std::ofstream outfile{filename.c_str()};

  if (!outfile) {
    std::cerr << "Could not access file " << filename << "!" << std::endl;
    return;
  }

  for (const auto s : m_FileContents) outfile << s << "\n";
}

SaveGame::SaveGame(std::stack<std::unique_ptr<Command>> *cps)
    : m_Commands(cps) {}
SaveGame::~SaveGame() {}
