#include "../src/SaveGame.hpp"

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

// MockCommand class
class Command {
 public:
  int m_Val;
  Command(int val) : m_Val(val) {}
  ~Command() {}
};

TEST(SaveGameTest, AddingSingleCommandToSave) {}

TEST(SaveGameTest, AddingMultipleCommandsToSave) {}

TEST(SaveGameTest, SavingToFile) {}
