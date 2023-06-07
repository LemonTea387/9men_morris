#include "SaveGame.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace {}

void SaveGame::AddToSave(const std::string &serialised, Command *command) {
  m_Commands.push_back(command);
  m_FileContents += serialised + "\n";
}

void SaveGame::LoadFromSave(const std::string &filename) {
  m_FileContents = "";
  m_Commands.clear();
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

  outfile << m_FileContents;
}

SaveGame::SaveGame() {}
SaveGame::~SaveGame() {}
