cmake_minimum_required(VERSION 3.16)
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

FetchContent_MakeAvailable(SFML)
add_executable(EverythingNMM src/main.cpp)
target_link_libraries(EverythingNMM sfml-graphics)
