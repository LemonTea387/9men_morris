#include "../src/SaveGame.hpp"

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include "../src/Command/Command.hpp"
#include "../src/GameBoard.hpp"
#include "../src/SaveGame.hpp"

typedef std::stack<std::unique_ptr<Command>> CommandStack;

TEST(SaveGameTest, AddingSingleCommandToSave) {
  std::stack<std::unique_ptr<Command>> cs;
  GameBoard gb;
  SaveGame sg(&cs, &gb);
  ASSERT_EQ(sg.GetFileContents().size(), 0);
}

TEST(SaveGameTest, AddingMultipleCommandsToSave) {}

TEST(SaveGameTest, SavingToFile) {}
