cmake_minimum_required(VERSION 3.16)

option(SHOW_TERMINAL "Displays the terminal on Windows" OFF)

project(
  EverythingNMM
  VERSION 0.0.1
  DESCRIPTION "A Nine Men's Morris Game made in C++ for the FIT3077 unit in Monash University (Malaysia)."
  LANGUAGES CXX
)
include(FetchContent)

FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG        2.5.1
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

FetchContent_MakeAvailable(SFML)
add_executable(EverythingNMM 
  src/main.cpp
  src/Scene/Scene.hpp
  src/Scene/MenuScene.hpp
  src/Scene/MenuScene.cpp
  src/Game.hpp
  src/Game.cpp
  )
target_link_libraries(EverythingNMM sfml-graphics)
