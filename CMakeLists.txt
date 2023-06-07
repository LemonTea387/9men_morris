cmake_minimum_required(VERSION 3.16)

option(SHOW_TERMINAL "Displays the terminal on Windows" ON)

project(
  EverythingNMM
  VERSION 0.0.1
  DESCRIPTION "A Nine Men's Morris Game made in C++ for the FIT3077 unit in Monash University (Malaysia)."
  LANGUAGES CXX
)
include(FetchContent)

# Fetch SFML library
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG        2.5.1
)

FetchContent_MakeAvailable(SFML)

# Fetch Google Testing library
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(EverythingNMM 
  src/main.cpp
  src/Tile.hpp
  src/Tile.cpp
  src/Token.hpp
  src/Token.cpp
  src/Scene/Scene.hpp
  src/Scene/Scene.cpp
  src/Scene/MenuScene.hpp
  src/Scene/MenuScene.cpp
  src/Scene/GameScene.hpp
  src/Scene/GameScene.cpp
  src/Scene/WinScene.hpp
  src/Scene/WinScene.cpp
  src/Scene/CreditsScene.hpp
  src/Scene/CreditsScene.cpp
  src/Scene/SaveScene.cpp
  src/Scene/SaveScene.hpp
  src/Scene/LoadScene.cpp
  src/Scene/LoadScene.hpp
  src/Command/Command.hpp
  src/Command/PlaceCommand.hpp
  src/Command/PlaceCommand.cpp
  src/Command/MoveCommand.cpp
  src/Command/MoveCommand.hpp
  src/Command/CaptureCommand.cpp
  src/Command/CaptureCommand.hpp
  src/Observer/Observer.hpp
  src/Observer/MillObserver.hpp
  src/Observer/MillObserver.cpp
  src/Observer/WinObserver.hpp
  src/Observer/WinObserver.cpp
  src/Game.hpp
  src/Game.cpp
  src/GameBoard.hpp
  src/GameBoard.cpp
  src/Scene/ui/Button.hpp
  src/Scene/ui/Button.cpp
  src/Scene/ui/TextField.hpp
  src/Scene/ui/TextField.cpp
  src/GameBoardUtils.hpp
  src/GameBoardUtils.cpp
  src/AssetManager.hpp
  src/AssetManager.cpp
  src/Tile.cpp 
  src/SaveGame.hpp
  src/SaveGame.cpp
  src/Serializable.hpp
)

if(MSVC)
  # Microsoft Documentation recommends these two lines
  # for having better debugging experience
  # Source: https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170#edit-and-continue-for-cmake-projects
  target_compile_options(EverythingNMM PUBLIC "/ZI")
  target_link_options(EverythingNMM PUBLIC "/INCREMENTAL")


  # Changed the subsystem on Windows so that the Command Line does not show up.
  if (NOT SHOW_TERMINAL)
    target_link_options(EverythingNMM PUBLIC "/SUBSYSTEM:WINDOWS")
  endif()
endif()

target_compile_features(EverythingNMM PRIVATE cxx_std_17)
target_link_libraries(EverythingNMM sfml-graphics)

add_subdirectory(tests)
