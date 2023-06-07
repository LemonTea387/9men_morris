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

TEST(SaveGameTest, AddingSingleCommandToSave) {
  SaveGame sg;

  // Initially, there should be no commands in the savegame
  auto commands = sg.GetCommands();
  ASSERT_EQ(commands.size(), 0);

  constexpr int MAGIC_VALUE = 12;
  Command command(MAGIC_VALUE);

  // Add Something to Save
  sg.AddToSave("Test Message", &command);

  // SaveGame should now have 1 command, which is nullptr
  commands = sg.GetCommands();
  ASSERT_EQ(commands.size(), 1);
  ASSERT_EQ(commands.back(), &command);

  // File contents should be as before.
  const auto filecontents = sg.GetFileContents();
  ASSERT_EQ(filecontents, "Test Message\n");
}

TEST(SaveGameTest, AddingMultipleCommandsToSave) {
  SaveGame sg;
  Command command1(1);
  Command command2(2);
  // Add Something to Save
  sg.AddToSave("Test Message 1", &command1);
  sg.AddToSave("Test Message 2", &command2);
  const auto commands = sg.GetCommands();
  ASSERT_EQ(commands.size(), 2);
  ASSERT_EQ(commands.at(0), &command1);
  ASSERT_EQ(commands.at(1), &command2);

  // File contents should be following
  const auto filecontents = sg.GetFileContents();
  ASSERT_EQ(filecontents, "Test Message 1\nTest Message 2\n");
}

TEST(SaveGameTest, SavingToFile) {
  SaveGame sg;
  sg.AddToSave("Test Message 1", nullptr);
  sg.AddToSave("Test Message 2", nullptr);

  const std::string filename = "SavingToFileTest.txt";
  // Remove file if exists first
  std::filesystem::remove(filename);

  // Save the file
  sg.SaveGameFile(filename);

  // Make sure it exists now
  ASSERT_TRUE(std::filesystem::exists(filename));

  std::ifstream inputfile{filename};
  std::string line;

  // First Command
  std::getline(inputfile, line);
  ASSERT_EQ(line, "Test Message 1");

  // Second Command
  std::getline(inputfile, line);
  ASSERT_EQ(line, "Test Message 2");
}
