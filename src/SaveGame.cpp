#include "SaveGame.hpp"

#include <fstream>
#include <iostream>

void SaveGame::AddToSave(const std::string &serialised, Command *command) {
  m_Commands.push_back(command);
  m_FileContents += serialised + "\n";
}

void SaveGame::LoadFromSave(const std::string &filename) {}

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
